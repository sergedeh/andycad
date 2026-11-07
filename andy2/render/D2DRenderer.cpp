// D2DRenderer.cpp — Direct2D backend implementation.

#include "D2DRenderer.h"

#include <cmath>
#include <vector>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

namespace acr {

namespace {
inline D2D1_FILL_MODE ToD2dFill(FillRule r) {
    return r == FillRule::NonZero ? D2D1_FILL_MODE_WINDING : D2D1_FILL_MODE_ALTERNATE;
}

// Build a native path geometry from a recorded Path command list.
ID2D1PathGeometry* BuildGeometry(ID2D1Factory* f, const Path& p,
                                 D2D1_FILL_MODE mode, bool filled) {
    ID2D1PathGeometry* g = nullptr;
    if (FAILED(f->CreatePathGeometry(&g))) return nullptr;
    ID2D1GeometrySink* s = nullptr;
    if (FAILED(g->Open(&s))) { g->Release(); return nullptr; }
    s->SetFillMode(mode);

    bool figureOpen = false;
    bool figureClosed = false;
    D2D1_FIGURE_BEGIN begin = filled ? D2D1_FIGURE_BEGIN_FILLED : D2D1_FIGURE_BEGIN_HOLLOW;

    for (const auto& c : p.cmds) {
        switch (c.type) {
        case Path::Type::Move:
            if (figureOpen) {
                s->EndFigure(figureClosed ? D2D1_FIGURE_END_CLOSED : D2D1_FIGURE_END_OPEN);
            }
            s->BeginFigure(D2D1::Point2F((FLOAT)c.a.x, (FLOAT)c.a.y), begin);
            figureOpen = true; figureClosed = false;
            break;
        case Path::Type::Line:
            s->AddLine(D2D1::Point2F((FLOAT)c.c.x, (FLOAT)c.c.y));
            break;
        case Path::Type::Bezier: {
            D2D1_BEZIER_SEGMENT seg = D2D1::BezierSegment(
                D2D1::Point2F((FLOAT)c.a.x, (FLOAT)c.a.y),
                D2D1::Point2F((FLOAT)c.b.x, (FLOAT)c.b.y),
                D2D1::Point2F((FLOAT)c.c.x, (FLOAT)c.c.y));
            s->AddBezier(seg);
            break;
        }
        case Path::Type::Close:
            figureClosed = true;
            break;
        }
    }
    if (figureOpen)
        s->EndFigure(figureClosed ? D2D1_FIGURE_END_CLOSED : D2D1_FIGURE_END_OPEN);
    s->Close();
    s->Release();
    return g;
}
} // namespace

D2DRenderer::D2DRenderer(HWND hwnd) : m_hwnd(hwnd) {
    D2D1_FACTORY_OPTIONS opts = {};
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, opts, &m_factory);
    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                        reinterpret_cast<IUnknown**>(&m_dwrite));
    m_cur = D2D1::Matrix3x2F::Identity();
}

D2DRenderer::D2DRenderer() : m_hwnd(nullptr) {
    D2D1_FACTORY_OPTIONS opts = {};
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, opts, &m_factory);
    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                        reinterpret_cast<IUnknown**>(&m_dwrite));
    m_cur = D2D1::Matrix3x2F::Identity();
}

void D2DRenderer::SetAntialias(bool on) {
    if (m_rt)
        m_rt->SetAntialiasMode(on ? D2D1_ANTIALIAS_MODE_PER_PRIMITIVE : D2D1_ANTIALIAS_MODE_ALIASED);
}

bool D2DRenderer::BindDC(HDC hdc, const RECT& rc) {
    if (!m_hwnd && !m_dcRt) {
        if (!CreateDeviceResources()) return false;
    }
    if (!m_dcRt) return false;
    return SUCCEEDED(m_dcRt->BindDC(hdc, &rc));
}

D2DRenderer::~D2DRenderer() {
    DiscardDeviceResources();
    for (auto& kv : m_formats) kv.second->Release();
    m_formats.clear();
    if (m_fmt) { m_fmt->Release(); m_fmt = nullptr; }
    if (m_dwrite) { m_dwrite->Release(); m_dwrite = nullptr; }
    if (m_factory) { m_factory->Release(); m_factory = nullptr; }
}

bool D2DRenderer::CreateDeviceResources() {
    if (!m_factory) return false;
    if (!m_hwnd) {
        // DC render target: GDI-compatible, so it can draw into the view's
        // memory DC and keep whatever GDI already painted there.
        D2D1_RENDER_TARGET_PROPERTIES dcp = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
            0, 0, D2D1_RENDER_TARGET_USAGE_NONE, D2D1_FEATURE_LEVEL_DEFAULT);
        if (FAILED(m_factory->CreateDCRenderTarget(&dcp, &m_dcRt))) return false;
        m_rt = m_dcRt;
    } else {
    RECT rc; GetClientRect(m_hwnd, &rc);
    if (rc.right == 0) rc.right = 1;
    if (rc.bottom == 0) rc.bottom = 1;

    D2D1_RENDER_TARGET_PROPERTIES rtp = D2D1::RenderTargetProperties();
    D2D1_HWND_RENDER_TARGET_PROPERTIES htp =
        D2D1::HwndRenderTargetProperties(m_hwnd, D2D1::SizeU(rc.right, rc.bottom));
    HRESULT hr = m_factory->CreateHwndRenderTarget(rtp, htp, &m_hwndRt);
    if (FAILED(hr)) return false;
    m_rt = m_hwndRt;
    }

    if (m_dwrite && !m_fmt) {
        m_dwrite->CreateTextFormat(L"Segoe UI", nullptr, DWRITE_FONT_WEIGHT_NORMAL,
                                   DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
                                   16.0f, L"en-us", &m_fmt);
    }
    return true;
}

void D2DRenderer::DiscardDeviceResources() {
    for (auto& kv : m_textures) if (kv.second.bitmap) kv.second.bitmap->Release();
    m_textures.clear();
    for (auto& kv : m_geoms) if (kv.second.geom) kv.second.geom->Release();
    m_geoms.clear();
    for (auto& kv : m_brushes) kv.second->Release();
    m_brushes.clear();
    for (auto& kv : m_styles) kv.second->Release();
    m_styles.clear();
    if (m_hwndRt) { m_hwndRt->Release(); m_hwndRt = nullptr; }
    if (m_dcRt) { m_dcRt->Release(); m_dcRt = nullptr; }
    m_rt = nullptr;
}

bool D2DRenderer::BeginFrame() {
    if (!m_rt) return false;
    m_rt->BeginDraw();
    return true;
}

bool D2DRenderer::EndFrame() {
    if (!m_rt) return false;
    HRESULT hr = m_rt->EndDraw();
    if (hr == (HRESULT)D2DERR_RECREATE_TARGET) {
        // Device lost: drop device-dependent resources; they are rebuilt on
        // the next BindDC()/CreateDeviceResources().
        DiscardDeviceResources();
        return false;
    }
    return SUCCEEDED(hr);
}

void D2DRenderer::Clear(const Color& bg) {
    m_rt->Clear(ColorF(bg));
}

void D2DRenderer::SetTransform(const Mat3& m) {
    m_cur = Mat(m);
    m_rt->SetTransform(m_cur);
}

void D2DRenderer::Push() { m_stack.push_back(m_cur); }
void D2DRenderer::Pop() {
    if (!m_stack.empty()) {
        m_cur = m_stack.back();
        m_stack.pop_back();
        m_rt->SetTransform(m_cur);
    }
}

void D2DRenderer::DrawPolyline(const Vec2* pts, size_t n, const Stroke& s) {
    if (n < 2 || !m_rt) return;
    Path p;
    p.MoveTo(pts[0]);
    for (size_t i = 1; i < n; ++i) p.LineTo(pts[i]);
    ID2D1PathGeometry* g = BuildGeometry(m_factory, p, D2D1_FILL_MODE_ALTERNATE, false);
    if (!g) return;
    m_rt->DrawGeometry(g, BrushFor(s.color), (FLOAT)(s.width > 0 ? s.width : 1.0),
                       StyleFor(s));
    g->Release();
}

void D2DRenderer::DrawPolygon(const Vec2* pts, size_t n, const Fill& f, const Stroke* outline) {
    if (n < 2 || !m_rt) return;
    Path p;
    p.MoveTo(pts[0]);
    for (size_t i = 1; i < n; ++i) p.LineTo(pts[i]);
    p.Close();
    ID2D1PathGeometry* g = BuildGeometry(m_factory, p, ToD2dFill(f.rule), true);
    if (!g) return;
    ID2D1SolidColorBrush* brush = BrushFor(f.color);
    m_rt->FillGeometry(g, brush);
    if (outline)
        m_rt->DrawGeometry(g, BrushFor(outline->color),
                           (FLOAT)(outline->width > 0 ? outline->width : 1.0), StyleFor(*outline));
    g->Release();
}

void D2DRenderer::DrawBezier(const Vec2* pts, size_t n, const Stroke& s) {
    if (n < 4 || !m_rt) return;
    Path p;
    p.MoveTo(pts[0]);
    for (size_t k = 1; k + 2 < n; k += 3)
        p.BezierTo(pts[k], pts[k + 1], pts[k + 2]);
    ID2D1PathGeometry* g = BuildGeometry(m_factory, p, D2D1_FILL_MODE_ALTERNATE, false);
    if (!g) return;
    m_rt->DrawGeometry(g, BrushFor(s.color), (FLOAT)(s.width > 0 ? s.width : 1.0),
                       StyleFor(s));
    g->Release();
}

void D2DRenderer::DrawEllipse(const Rect2& r, const Fill& f, const Stroke* outline) {
    if (!m_rt) return;
    D2D1_ELLIPSE e = D2D1::Ellipse(
        D2D1::Point2F((FLOAT)((r.x0 + r.x1) * 0.5), (FLOAT)((r.y0 + r.y1) * 0.5)),
        (FLOAT)((r.x1 - r.x0) * 0.5), (FLOAT)((r.y1 - r.y0) * 0.5));
    m_rt->FillEllipse(&e, BrushFor(f.color));
    if (outline)
        m_rt->DrawEllipse(&e, BrushFor(outline->color),
                          (FLOAT)(outline->width > 0 ? outline->width : 1.0), StyleFor(*outline));
}

void D2DRenderer::DrawRect(const Rect2& r, const Fill& f, const Stroke* outline) {
    if (!m_rt) return;
    D2D1_RECT_F rc = D2D1::RectF((FLOAT)r.x0, (FLOAT)r.y0, (FLOAT)r.x1, (FLOAT)r.y1);
    m_rt->FillRectangle(&rc, BrushFor(f.color));
    if (outline)
        m_rt->DrawRectangle(&rc, BrushFor(outline->color),
                            (FLOAT)(outline->width > 0 ? outline->width : 1.0), StyleFor(*outline));
}

void D2DRenderer::DrawDot(const Vec2& p, const Color& c) {
    if (!m_rt) return;
    D2D1_ELLIPSE e = D2D1::Ellipse(Pt(p), 1.5f, 1.5f);
    m_rt->FillEllipse(&e, BrushFor(c));
}

void D2DRenderer::FillPath(const Path& p, const Fill& f) {
    if (p.Empty() || !m_rt) return;
    ID2D1PathGeometry* g = GeometryFor(p, true, ToD2dFill(f.rule));
    if (g) m_rt->FillGeometry(g, BrushFor(f.color));
}

void D2DRenderer::StrokePath(const Path& p, const Stroke& s) {
    if (p.Empty() || !m_rt) return;
    ID2D1PathGeometry* g = GeometryFor(p, false, D2D1_FILL_MODE_ALTERNATE);
    if (g) DrawStrokeGeometry(g, s);
}

ID2D1Bitmap* D2DRenderer::TextureFor(const TextureSource& tex) {
    if (!m_rt || !tex.pixels || tex.width <= 0 || tex.height <= 0) return nullptr;
    auto it = m_textures.find(tex.key);
    if (it != m_textures.end() && it->second.revision == tex.revision && it->second.bitmap)
        return it->second.bitmap;

    // Direct2D wants premultiplied alpha.
    std::vector<uint32_t> pm((size_t)tex.width * tex.height);
    for (size_t i = 0; i < pm.size(); ++i) {
        uint32_t p = tex.pixels[i];
        uint32_t a = p >> 24;
        uint32_t r = ((p >> 16) & 0xFF) * a / 255;
        uint32_t g = ((p >> 8) & 0xFF) * a / 255;
        uint32_t b = (p & 0xFF) * a / 255;
        pm[i] = (a << 24) | (r << 16) | (g << 8) | b;
    }
    D2D1_BITMAP_PROPERTIES props = D2D1::BitmapProperties(
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
    ID2D1Bitmap* bmp = nullptr;
    if (FAILED(m_rt->CreateBitmap(D2D1::SizeU(tex.width, tex.height), pm.data(),
                                  tex.width * 4, props, &bmp)))
        return nullptr;   // e.g. larger than the device's maximum bitmap size
    if (it != m_textures.end() && it->second.bitmap) it->second.bitmap->Release();
    m_textures[tex.key] = TexEntry{ tex.revision, bmp };
    return bmp;
}

void D2DRenderer::FillPathWithTexture(const Path& outline, const TextureSource& tex,
                                      const Mat3& texelToWorld, TextureLayout layout,
                                      float opacity) {
    if (outline.Empty() || !m_rt) return;
    ID2D1Bitmap* bmp = TextureFor(tex);
    if (!bmp) return;
    ID2D1PathGeometry* g = GeometryFor(outline, true, D2D1_FILL_MODE_ALTERNATE);
    if (!g) return;
    D2D1_EXTEND_MODE ext = layout == TextureLayout::Tile ? D2D1_EXTEND_MODE_WRAP
                                                         : D2D1_EXTEND_MODE_CLAMP;
    float op = opacity < 0 ? 0.0f : (opacity > 1 ? 1.0f : opacity);
    ID2D1BitmapBrush* brush = nullptr;
    HRESULT hr = m_rt->CreateBitmapBrush(
        bmp,
        D2D1::BitmapBrushProperties(ext, ext, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR),
        D2D1::BrushProperties(op, Mat(texelToWorld)),
        &brush);
    if (FAILED(hr) || !brush) return;
    m_rt->FillGeometry(g, brush);
    brush->Release();
}

void D2DRenderer::ForgetTexture(const void* key) {
    auto it = m_textures.find(key);
    if (it == m_textures.end()) return;
    if (it->second.bitmap) it->second.bitmap->Release();
    m_textures.erase(it);
}

double D2DRenderer::WorldStrokeWidth(const Stroke& s) const {
    // One device pixel, expressed in world units of the current transform.
    double det = (double)m_cur._11 * m_cur._22 - (double)m_cur._12 * m_cur._21;
    double scale = det < 0 ? -det : det;
    scale = scale > 0 ? sqrt(scale) : 1.0;
    double onePixel = 1.0 / scale;
    if (s.cosmetic || s.width <= 0) return onePixel;
    // Like GDI geometric pens, never thinner than one device pixel (thinner
    // aliased lines drop out entirely when zoomed out).
    return s.width > onePixel ? s.width : onePixel;
}

void D2DRenderer::DrawStrokeGeometry(ID2D1Geometry* g, const Stroke& s) {
    double w = WorldStrokeWidth(s);
    ID2D1StrokeStyle* style = nullptr;
    if (!s.dash.empty()) {
        // GDI user-style dash lengths are absolute; Direct2D custom dashes are
        // multiples of the stroke width, so normalise them.
        Stroke norm = s;
        norm.width = w;
        for (double& d : norm.dash) d = w > 0 ? d / w : d;
        style = StyleFor(norm);
    }
    m_rt->DrawGeometry(g, BrushFor(s.color), (FLOAT)w, style);
}

Rect2 D2DRenderer::MeasureText(const std::wstring& text, const TextStyle& ts) {
    if (!m_rt) return Rect2();
    IDWriteTextFormat* fmt = FormatFor(ts);
    IDWriteTextLayout* layout = nullptr;
    m_dwrite->CreateTextLayout(text.c_str(), (UINT32)text.size(), fmt, 10000.0f, 10000.0f, &layout);
    if (!layout) return Rect2();
    DWRITE_TEXT_METRICS m = {};
    layout->GetMetrics(&m);
    layout->Release();
    return Rect2(0, 0, m.widthIncludingTrailingWhitespace, m.height);
}

void D2DRenderer::DrawTextAt(const Vec2& at, const std::wstring& text, const TextStyle& ts) {
    if (!m_rt) return;
    IDWriteTextFormat* fmt = FormatFor(ts);
    D2D1_RECT_F rc = D2D1::RectF((FLOAT)at.x, (FLOAT)at.y, 10000.0f, 10000.0f);
    // NOTE: ID2D1RenderTarget's method is `DrawText`, which <windows.h> aliases
    // to DrawTextW (Unicode) / DrawTextA (MBCS) — write it unadorned so the macro
    // resolves to the name the SDK actually emitted for the active charset.
    m_rt->DrawText(text.c_str(), (UINT32)text.size(), fmt, &rc, BrushFor(ts.color));
}

// ---------------------------------------------------------------------------
// Private helpers
// ---------------------------------------------------------------------------
ID2D1SolidColorBrush* D2DRenderer::BrushFor(const Color& c) {
    if (!m_rt) return nullptr;
    uint32_t k = PackRgba(c);
    auto it = m_brushes.find(k);
    if (it != m_brushes.end()) return it->second;
    ID2D1SolidColorBrush* b = nullptr;
    m_rt->CreateSolidColorBrush(ColorF(c), &b);
    m_brushes[k] = b;
    return b;
}

ID2D1StrokeStyle* D2DRenderer::StyleFor(const Stroke& s) {
    if (!m_rt) return nullptr;
    if (s.dash.empty()) return nullptr;   // solid => D2D default
    uint64_t k = StyleKey(s);
    auto it = m_styles.find(k);
    if (it != m_styles.end()) return it->second;
    D2D1_STROKE_STYLE_PROPERTIES props = D2D1::StrokeStyleProperties(
        D2D1_CAP_STYLE_ROUND, D2D1_CAP_STYLE_ROUND, D2D1_CAP_STYLE_FLAT,
        D2D1_LINE_JOIN_ROUND, 10.0f, D2D1_DASH_STYLE_CUSTOM, 0.0f);
    std::vector<FLOAT> dash;
    dash.reserve(s.dash.size());
    for (double v : s.dash) dash.push_back((FLOAT)v);
    ID2D1StrokeStyle* st = nullptr;
    m_factory->CreateStrokeStyle(props, dash.data(), (UINT32)dash.size(), &st);
    m_styles[k] = st;
    return st;
}

IDWriteTextFormat* D2DRenderer::FormatFor(const TextStyle& ts) {
    uint64_t k = FontKey(ts);
    auto it = m_formats.find(k);
    if (it != m_formats.end()) return it->second;
    IDWriteTextFormat* f = nullptr;
    m_dwrite->CreateTextFormat(ts.family.c_str(), nullptr, DWRITE_FONT_WEIGHT_NORMAL,
                               DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
                               (FLOAT)ts.size, L"en-us", &f);
    m_formats[k] = f;
    return f;
}

ID2D1PathGeometry* D2DRenderer::GeometryFor(const Path& p, bool filled, D2D1_FILL_MODE mode) {
    auto it = m_geoms.find(&p);
    if (it != m_geoms.end() && it->second.revision == p.revision &&
        it->second.filled == filled && it->second.fillMode == (int)mode) {
        return it->second.geom;
    }
    ID2D1PathGeometry* g = BuildGeometry(m_factory, p, mode, filled);
    if (it != m_geoms.end() && it->second.geom) it->second.geom->Release();
    GeomEntry e{ p.revision, filled, (int)mode, g };
    m_geoms[&p] = e;
    return g;
}

uint32_t D2DRenderer::PackRgba(const Color& c) {
    auto b = [](float v) { int i = (int)(v * 255.0f + 0.5f); return i < 0 ? 0 : (i > 255 ? 255 : i); };
    return ((uint32_t)b(c.a) << 24) | ((uint32_t)b(c.r) << 16) |
           ((uint32_t)b(c.g) << 8) | (uint32_t)b(c.b);
}

uint64_t D2DRenderer::StyleKey(const Stroke& s) {
    uint32_t h = 0x811c9dc5u;
    for (double v : s.dash) {
        unsigned char bytes[8];
        memcpy(bytes, &v, 8);
        for (unsigned char by : bytes) { h ^= by; h *= 16777619u; }
    }
    return ((uint64_t)h << 32) | (uint64_t)(s.width * 16.0 + 0.5);
}

uint64_t D2DRenderer::FontKey(const TextStyle& ts) {
    uint32_t h = 0x811c9dc5u;
    for (wchar_t ch : ts.family) {
        unsigned char bytes[2] = { (unsigned char)(ch & 0xFF), (unsigned char)(ch >> 8) };
        h ^= bytes[0]; h *= 16777619u; h ^= bytes[1]; h *= 16777619u;
    }
    return ((uint64_t)h << 32) | ((uint64_t)(ts.size * 4.0 + 0.5));
}

D2D1_POINT_2F D2DRenderer::Pt(const Vec2& v) {
    return D2D1::Point2F((FLOAT)v.x, (FLOAT)v.y);
}

D2D1_COLOR_F D2DRenderer::ColorF(const Color& c) {
    return D2D1::ColorF(c.r, c.g, c.b, c.a);
}

D2D1_MATRIX_3X2_F D2DRenderer::Mat(const Mat3& m) {
    return D2D1::Matrix3x2F((FLOAT)m.m11, (FLOAT)m.m12, (FLOAT)m.m21,
                            (FLOAT)m.m22, (FLOAT)m.dx, (FLOAT)m.dy);
}

} // namespace acr
