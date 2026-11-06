// GdiRenderer.cpp — GDI backend implementation.

#include "GdiRenderer.h"

#include <cmath>

namespace acr {

namespace {
// Simple FNV-1a over bytes, used for dash/font keys.
inline uint32_t Fnv1a(const void* data, size_t n, uint32_t seed) {
    const unsigned char* p = (const unsigned char*)data;
    uint32_t h = seed;
    for (size_t i = 0; i < n; ++i) { h ^= p[i]; h *= 16777619u; }
    return h;
}
inline int RoundI(double v) { return (int)(v + 0.5); }
} // namespace

GdiRenderer::GdiRenderer(HDC hdc) : m_hdc(hdc) {
    m_devW = GetDeviceCaps(hdc, HORZRES);
    m_devH = GetDeviceCaps(hdc, VERTRES);
}

GdiRenderer::~GdiRenderer() {
    for (auto& kv : m_pens)    DeleteObject(kv.second);
    for (auto& kv : m_brushes) DeleteObject(kv.second);
    for (auto& kv : m_fonts)   DeleteObject(kv.second);
    m_pens.clear(); m_brushes.clear(); m_fonts.clear();
}

bool GdiRenderer::BeginFrame() { return true; }
bool GdiRenderer::EndFrame()   { return true; }

void GdiRenderer::Clear(const Color& bg) {
    HBRUSH b = BrushFor(bg);
    RECT rc = { 0, 0, m_devW, m_devH };
    FillRect(m_hdc, &rc, b);
}

void GdiRenderer::SetTransform(const Mat3& m) {
    SetGraphicsMode(m_hdc, GM_ADVANCED);
    XFORM x;
    x.eM11 = (FLOAT)m.m11; x.eM12 = (FLOAT)m.m12;
    x.eM21 = (FLOAT)m.m21; x.eM22 = (FLOAT)m.m22;
    x.eDx  = (FLOAT)m.dx;  x.eDy  = (FLOAT)m.dy;
    SetWorldTransform(m_hdc, &x);
}

void GdiRenderer::Push() { SaveDC(m_hdc); }
void GdiRenderer::Pop()  { RestoreDC(m_hdc, -1); }

void GdiRenderer::DrawPolyline(const Vec2* pts, size_t n, const Stroke& s) {
    if (n < 2) return;
    HPEN pen = PenFor(s);
    HGDIOBJ old = SelectObject(m_hdc, pen);
    std::vector<POINT> p = ToPoints(pts, n);
    ::Polyline(m_hdc, p.data(), (int)p.size());
    SelectObject(m_hdc, old);
}

void GdiRenderer::DrawPolygon(const Vec2* pts, size_t n, const Fill& f, const Stroke* outline) {
    if (n < 2) return;
    ::BeginPath(m_hdc);
    POINT p0 = { RoundI(pts[0].x), RoundI(pts[0].y) };
    MoveToEx(m_hdc, p0.x, p0.y, nullptr);
    std::vector<POINT> rest = ToPoints(pts + 1, n - 1);
    ::Polyline(m_hdc, rest.data(), (int)rest.size());
    ::CloseFigure(m_hdc);
    ::EndPath(m_hdc);

    SetPolyFillMode(m_hdc, f.rule == FillRule::NonZero ? WINDING : ALTERNATE);
    HGDIOBJ ob = SelectObject(m_hdc, BrushFor(f.color));
    ::FillPath(m_hdc);
    if (outline) {
        HGDIOBJ op = SelectObject(m_hdc, PenFor(*outline));
        ::StrokePath(m_hdc);
        SelectObject(m_hdc, op);
    }
    SelectObject(m_hdc, ob);
}

void GdiRenderer::DrawBezier(const Vec2* pts, size_t n, const Stroke& s) {
    if (n < 4) return;
    HPEN pen = PenFor(s);
    HGDIOBJ old = SelectObject(m_hdc, pen);
    std::vector<POINT> p = ToPoints(pts, n);
    ::PolyBezier(m_hdc, p.data(), (DWORD)p.size());
    SelectObject(m_hdc, old);
}

void GdiRenderer::DrawEllipse(const Rect2& r, const Fill& f, const Stroke* outline) {
    HGDIOBJ ob = SelectObject(m_hdc, BrushFor(f.color));
    HGDIOBJ op = SelectObject(m_hdc, outline ? PenFor(*outline) : (HGDIOBJ)GetStockObject(NULL_PEN));
    ::Ellipse(m_hdc, RoundI(r.x0), RoundI(r.y0), RoundI(r.x1), RoundI(r.y1));
    SelectObject(m_hdc, op);
    SelectObject(m_hdc, ob);
}

void GdiRenderer::DrawRect(const Rect2& r, const Fill& f, const Stroke* outline) {
    HGDIOBJ ob = SelectObject(m_hdc, BrushFor(f.color));
    HGDIOBJ op = SelectObject(m_hdc, outline ? PenFor(*outline) : (HGDIOBJ)GetStockObject(NULL_PEN));
    ::Rectangle(m_hdc, RoundI(r.x0), RoundI(r.y0), RoundI(r.x1), RoundI(r.y1));
    SelectObject(m_hdc, op);
    SelectObject(m_hdc, ob);
}

void GdiRenderer::DrawDot(const Vec2& p, const Color& c) {
    SetPixel(m_hdc, RoundI(p.x), RoundI(p.y), ToColorref(c));
}

void GdiRenderer::FillPath(const Path& path, const Fill& f) {
    if (path.Empty()) return;
    ::BeginPath(m_hdc);
    Replay(path, m_hdc);
    ::EndPath(m_hdc);
    SetPolyFillMode(m_hdc, f.rule == FillRule::NonZero ? WINDING : ALTERNATE);
    HGDIOBJ ob = SelectObject(m_hdc, BrushFor(f.color));
    ::FillPath(m_hdc);
    SelectObject(m_hdc, ob);
}

void GdiRenderer::StrokePath(const Path& path, const Stroke& s) {
    if (path.Empty()) return;
    ::BeginPath(m_hdc);
    Replay(path, m_hdc);
    ::EndPath(m_hdc);
    HGDIOBJ op = SelectObject(m_hdc, PenFor(s));
    ::StrokePath(m_hdc);
    SelectObject(m_hdc, op);
}

Rect2 GdiRenderer::MeasureText(const std::wstring& text, const TextStyle& ts) {
    HFONT font = FontFor(ts);
    HGDIOBJ old = SelectObject(m_hdc, font);
    RECT rc = { 0, 0, 0, 0 };
    DrawTextW(m_hdc, text.c_str(), -1, &rc, DT_CALCRECT | DT_NOCLIP);
    SelectObject(m_hdc, old);
    return Rect2(0, 0, rc.right, rc.bottom);
}

void GdiRenderer::DrawTextAt(const Vec2& at, const std::wstring& text, const TextStyle& ts) {
    HFONT font = FontFor(ts);
    HGDIOBJ old = SelectObject(m_hdc, font);
    SetTextColor(m_hdc, ToColorref(ts.color));
    SetBkMode(m_hdc, TRANSPARENT);
    TextOutW(m_hdc, RoundI(at.x), RoundI(at.y), text.c_str(), (int)text.size());
    SelectObject(m_hdc, old);
}

// ---------------------------------------------------------------------------
// Private helpers
// ---------------------------------------------------------------------------
COLORREF GdiRenderer::ToColorref(const Color& c) {
    auto b = [](float v) { int i = (int)(v * 255.0f + 0.5f); return i < 0 ? 0 : (i > 255 ? 255 : i); };
    return RGB(b(c.r), b(c.g), b(c.b));
}

uint32_t GdiRenderer::PackRgb(const Color& c) {
    auto b = [](float v) { int i = (int)(v * 255.0f + 0.5f); return i < 0 ? 0 : (i > 255 ? 255 : i); };
    return ((uint32_t)b(c.r) << 16) | ((uint32_t)b(c.g) << 8) | (uint32_t)b(c.b);
}

uint64_t GdiRenderer::StrokeKey(const Stroke& s) {
    uint32_t rgb = PackRgb(s.color);
    uint32_t w   = (uint32_t)(s.width * 16.0 + 0.5);      // Q4 width
    uint32_t dashHash = 0;
    if (!s.dash.empty())
        dashHash = Fnv1a(s.dash.data(), s.dash.size() * sizeof(double), 0x811c9dc5u) & 0x7FFFFu;
    uint64_t key = ((uint64_t)rgb << 32)
                 | ((uint64_t)w << 20)
                 | ((uint64_t)(s.cosmetic ? 1u : 0u) << 19)
                 | (uint64_t)dashHash;
    return key;
}

uint64_t GdiRenderer::FontKey(const TextStyle& ts) {
    uint32_t h = Fnv1a(ts.family.data(), ts.family.size() * sizeof(wchar_t), 0x811c9dc5u);
    return ((uint64_t)h << 32) | ((uint64_t)(ts.size * 4.0 + 0.5));
}

HPEN GdiRenderer::PenFor(const Stroke& s) {
    uint64_t key = StrokeKey(s);
    auto it = m_pens.find(key);
    if (it != m_pens.end()) return it->second;

    HPEN pen = nullptr;
    if (!s.dash.empty()) {
        // NOTE: exact custom line-types (the engine's lpStyle arrays) need
        // ExtCreatePen + EXTLOGPEN; approximate with PS_DOT for now.
        pen = CreatePen(PS_DOT, s.cosmetic ? 1 : RoundI(s.width), ToColorref(s.color));
    } else if (s.cosmetic || s.width <= 0.0) {
        pen = CreatePen(PS_COSMETIC | PS_SOLID, 1, ToColorref(s.color));
    } else {
        pen = CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_ROUND | PS_JOIN_ROUND,
                        RoundI(s.width), ToColorref(s.color));
    }
    if (pen) m_pens[key] = pen;
    return pen;
}

HBRUSH GdiRenderer::BrushFor(const Color& c) {
    uint32_t rgb = PackRgb(c);
    auto it = m_brushes.find(rgb);
    if (it != m_brushes.end()) return it->second;
    HBRUSH b = CreateSolidBrush(ToColorref(c));
    m_brushes[rgb] = b;
    return b;
}

HFONT GdiRenderer::FontFor(const TextStyle& ts) {
    uint64_t key = FontKey(ts);
    auto it = m_fonts.find(key);
    if (it != m_fonts.end()) return it->second;
    HFONT f = CreateFontW(-RoundI(ts.size), 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                          DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                          DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, ts.family.c_str());
    m_fonts[key] = f;
    return f;
}

std::vector<POINT> GdiRenderer::ToPoints(const Vec2* pts, size_t n) {
    std::vector<POINT> out;
    out.reserve(n);
    for (size_t i = 0; i < n; ++i) out.push_back({ RoundI(pts[i].x), RoundI(pts[i].y) });
    return out;
}

void GdiRenderer::Replay(const Path& p, HDC hdc) {
    for (const auto& c : p.cmds) {
        switch (c.type) {
        case Path::Type::Move:
            MoveToEx(hdc, RoundI(c.a.x), RoundI(c.a.y), nullptr);
            break;
        case Path::Type::Line:
            LineTo(hdc, RoundI(c.c.x), RoundI(c.c.y));
            break;
        case Path::Type::Bezier: {
            POINT b[3] = {
                { RoundI(c.a.x), RoundI(c.a.y) },
                { RoundI(c.b.x), RoundI(c.b.y) },
                { RoundI(c.c.x), RoundI(c.c.y) },
            };
            PolyBezierTo(hdc, b, 3);
            break;
        }
        case Path::Type::Close:
            CloseFigure(hdc);
            break;
        }
    }
}

} // namespace acr
