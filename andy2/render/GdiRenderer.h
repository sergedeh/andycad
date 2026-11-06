// GdiRenderer.h — GDI backend for IRenderer (faithful 1:1 mapping).
//
// Wraps a borrowed HDC so it can be dropped into the MFC engine via
// `hdc->GetSafeHdc()` with zero changes to how entities emit geometry, and it
// also runs standalone in the benchmark over a plain memory DC.
//
// GDI has no per-pixel alpha, so Color::a is ignored (matching the current
// GDI-only presentation path). Pens/brushes/fonts are cached to avoid the
// per-entity object churn the legacy draw() methods suffer from.

#pragma once

#include <map>
#include <vector>
#include <windows.h>

#include "IRenderer.h"

namespace acr {

class GdiRenderer : public IRenderer {
public:
    explicit GdiRenderer(HDC hdc);
    ~GdiRenderer() override;

    bool BeginFrame() override;
    bool EndFrame() override;
    void Clear(const Color& bg) override;

    void SetTransform(const Mat3& m) override;
    void Push() override;
    void Pop() override;

    void DrawPolyline(const Vec2* pts, size_t n, const Stroke& s) override;
    void DrawPolygon  (const Vec2* pts, size_t n, const Fill& f, const Stroke* outline) override;
    void DrawBezier   (const Vec2* pts, size_t n, const Stroke& s) override;
    void DrawEllipse  (const Rect2& r, const Fill& f, const Stroke* outline) override;
    void DrawRect     (const Rect2& r, const Fill& f, const Stroke* outline) override;
    void DrawDot      (const Vec2& p, const Color& c) override;

    void FillPath  (const Path& p, const Fill& f) override;
    void StrokePath(const Path& p, const Stroke& s) override;

    Rect2 MeasureText(const std::wstring& text, const TextStyle& ts) override;
    void  DrawTextAt (const Vec2& at, const std::wstring& text, const TextStyle& ts) override;

private:
    HDC  m_hdc = nullptr;
    int  m_devW = 0, m_devH = 0;

    std::map<uint64_t, HPEN>   m_pens;
    std::map<uint32_t, HBRUSH> m_brushes;
    std::map<uint64_t, HFONT>  m_fonts;

    HPEN   PenFor(const Stroke& s);
    HBRUSH BrushFor(const Color& c);
    HFONT  FontFor(const TextStyle& ts);

    static std::vector<POINT> ToPoints(const Vec2* pts, size_t n);
    static void Replay(const Path& p, HDC hdc);
    static void CloseIfOpen(const Path& p, HDC hdc);

    static COLORREF ToColorref(const Color& c);
    static uint32_t PackRgb(const Color& c);
    static uint64_t StrokeKey(const Stroke& s);
    static uint64_t FontKey(const TextStyle& ts);
};

} // namespace acr
