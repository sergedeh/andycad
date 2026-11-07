// GlyphOutline.cpp — see GlyphOutline.h.

#include "GlyphOutline.h"

#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <cmath>
#include <map>
#include <string>

#pragma comment(lib, "dwrite.lib")

namespace acr {

namespace {

// Collects a glyph outline as flattened closed loops.
class LoopSink : public IDWriteGeometrySink {
public:
    explicit LoopSink(double tol) : m_tol(tol > 0.05 ? tol : 0.05) {}
    std::vector<std::vector<Vec2>> loops;

    // IUnknown (stack object: no real ref counting)
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID, void** p) override { *p = nullptr; return E_NOINTERFACE; }
    ULONG STDMETHODCALLTYPE AddRef() override { return 1; }
    ULONG STDMETHODCALLTYPE Release() override { return 1; }

    void STDMETHODCALLTYPE SetFillMode(D2D1_FILL_MODE) override {}
    void STDMETHODCALLTYPE SetSegmentFlags(D2D1_PATH_SEGMENT) override {}
    void STDMETHODCALLTYPE BeginFigure(D2D1_POINT_2F p, D2D1_FIGURE_BEGIN) override {
        loops.emplace_back();
        loops.back().push_back(Vec2(p.x, p.y));
        m_last = p;
    }
    void STDMETHODCALLTYPE AddLines(const D2D1_POINT_2F* pts, UINT32 n) override {
        for (UINT32 i = 0; i < n; ++i) {
            loops.back().push_back(Vec2(pts[i].x, pts[i].y));
            m_last = pts[i];
        }
    }
    void STDMETHODCALLTYPE AddBeziers(const D2D1_BEZIER_SEGMENT* b, UINT32 n) override {
        for (UINT32 i = 0; i < n; ++i) {
            D2D1_POINT_2F p0 = m_last, p1 = b[i].point1, p2 = b[i].point2, p3 = b[i].point3;
            // Segment count from the control polygon length vs tolerance.
            double len = hypot(p1.x - p0.x, p1.y - p0.y) + hypot(p2.x - p1.x, p2.y - p1.y) +
                         hypot(p3.x - p2.x, p3.y - p2.y);
            int steps = (int)ceil(sqrt(len / m_tol));
            if (steps < 2) steps = 2;
            if (steps > 64) steps = 64;
            for (int s = 1; s <= steps; ++s) {
                double t = (double)s / steps, u = 1 - t;
                double x = u * u * u * p0.x + 3 * u * u * t * p1.x + 3 * u * t * t * p2.x + t * t * t * p3.x;
                double y = u * u * u * p0.y + 3 * u * u * t * p1.y + 3 * u * t * t * p2.y + t * t * t * p3.y;
                loops.back().push_back(Vec2(x, y));
            }
            m_last = p3;
        }
    }
    void STDMETHODCALLTYPE EndFigure(D2D1_FIGURE_END) override {
        // Drop a closing point that repeats the start.
        auto& l = loops.back();
        if (l.size() > 1 && fabs(l.front().x - l.back().x) < 1e-6 && fabs(l.front().y - l.back().y) < 1e-6)
            l.pop_back();
    }
    HRESULT STDMETHODCALLTYPE Close() override { return S_OK; }

private:
    double m_tol;
    D2D1_POINT_2F m_last = { 0, 0 };
};

IDWriteFactory* Factory() {
    static IDWriteFactory* f = nullptr;
    if (!f)
        DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                            reinterpret_cast<IUnknown**>(&f));
    return f;
}

IDWriteFontFace* Face(const std::wstring& family, int weight, bool italic) {
    static std::map<std::wstring, IDWriteFontFace*> cache;
    std::wstring key = family + L"|" + std::to_wstring(weight) + (italic ? L"|i" : L"|n");
    auto it = cache.find(key);
    if (it != cache.end()) return it->second;
    IDWriteFontFace* face = nullptr;
    IDWriteFontCollection* fonts = nullptr;
    if (Factory() && SUCCEEDED(Factory()->GetSystemFontCollection(&fonts, FALSE)) && fonts) {
        UINT32 index = 0;
        BOOL exists = FALSE;
        fonts->FindFamilyName(family.c_str(), &index, &exists);
        if (!exists) fonts->FindFamilyName(L"Arial", &index, &exists);
        IDWriteFontFamily* fam = nullptr;
        if (exists && SUCCEEDED(fonts->GetFontFamily(index, &fam)) && fam) {
            IDWriteFont* font = nullptr;
            if (SUCCEEDED(fam->GetFirstMatchingFont((DWRITE_FONT_WEIGHT)weight, DWRITE_FONT_STRETCH_NORMAL,
                                                    italic ? DWRITE_FONT_STYLE_ITALIC : DWRITE_FONT_STYLE_NORMAL,
                                                    &font)) && font) {
                font->CreateFontFace(&face);
                font->Release();
            }
            fam->Release();
        }
        fonts->Release();
    }
    cache[key] = face;
    return face;
}

} // namespace

bool GlyphOutlines(const GlyphDraw* glyphs, size_t n, double tolerancePx,
                   std::vector<std::vector<std::vector<Vec2>>>& out) {
    out.assign(n, {});
    if (!Factory()) return false;
    for (size_t i = 0; i < n; ++i) {
        const GlyphDraw& g = glyphs[i];
        if (g.ch == 0 || g.ch == L' ' || g.ch == L'\r' || g.ch == L'\n' || g.emPixels <= 0) continue;
        IDWriteFontFace* face = Face(g.family, g.weight, g.italic);
        if (!face) continue;
        UINT32 cp = (UINT32)g.ch;
        UINT16 index = 0;
        if (FAILED(face->GetGlyphIndices(&cp, 1, &index))) continue;
        LoopSink sink(tolerancePx);
        if (FAILED(face->GetGlyphRunOutline((FLOAT)g.emPixels, &index, nullptr, nullptr, 1,
                                            FALSE, FALSE, &sink)))
            continue;
        const Mat3& m = g.deviceMatrix;
        for (auto& loop : sink.loops) {
            if (loop.size() < 3) continue;
            std::vector<Vec2> dev;
            dev.reserve(loop.size());
            for (const Vec2& p : loop)
                dev.push_back(m.Transform(p));
            out[i].push_back(std::move(dev));
        }
    }
    return true;
}

} // namespace acr
