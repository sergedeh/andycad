// D2DRenderer.h — Direct2D backend for IRenderer (GPU-accelerated).
//
// Mirrors GdiRenderer's surface 1:1. Two features matter for the migration:
//
//   * Curves (bezier) stay as curves — no per-frame tessellation to polylines.
//   * FillPath/StrokePath cache the native ID2D1PathGeometry keyed by the
//     Path object, so a persistent (retained) Path is built once and re-issued
//     as a transform-only draw each frame. This is the "retained tessellation
//     cache per entity" from rendering-inventory.md §4.

#pragma once

#include <map>
#include <vector>
#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>

#include "IRenderer.h"

namespace acr {

class D2DRenderer : public IRenderer {
public:
    explicit D2DRenderer(HWND hwnd);
    ~D2DRenderer() override;

    bool CreateDeviceResources();
    void DiscardDeviceResources();

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
    HWND                 m_hwnd = nullptr;
    ID2D1Factory*        m_factory = nullptr;
    ID2D1HwndRenderTarget* m_rt = nullptr;
    IDWriteFactory*      m_dwrite = nullptr;
    IDWriteTextFormat*   m_fmt = nullptr;

    std::map<uint32_t, ID2D1SolidColorBrush*> m_brushes;
    std::map<uint64_t, ID2D1StrokeStyle*>     m_styles;
    std::map<uint64_t, IDWriteTextFormat*>    m_formats;

    struct GeomEntry {
        uint64_t revision = 0;
        bool filled = false;
        int  fillMode = 0;
        ID2D1PathGeometry* geom = nullptr;
    };
    std::map<const Path*, GeomEntry> m_geoms;

    std::vector<D2D1_MATRIX_3X2_F> m_stack;
    D2D1_MATRIX_3X2_F m_cur;

    ID2D1SolidColorBrush* BrushFor(const Color& c);
    ID2D1StrokeStyle*     StyleFor(const Stroke& s);
    IDWriteTextFormat*    FormatFor(const TextStyle& ts);
    ID2D1PathGeometry*    GeometryFor(const Path& p, bool filled, D2D1_FILL_MODE mode);

    static uint32_t PackRgba(const Color& c);
    static uint64_t StyleKey(const Stroke& s);
    static uint64_t FontKey(const TextStyle& ts);
    static D2D1_POINT_2F Pt(const Vec2& v);
    static D2D1_COLOR_F  ColorF(const Color& c);
    static D2D1_MATRIX_3X2_F Mat(const Mat3& m);
};

} // namespace acr
