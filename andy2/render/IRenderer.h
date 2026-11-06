// IRenderer.h — the presentation seam for AndyCAD entities.
//
// This is the backend-neutral device interface that replaces `CDC*` inside the
// entity draw() methods (rendering-inventory.md §5). An entity emits geometry
// through an IRenderer; the concrete backend decides how it is rasterized:
//
//   * GdiRenderer   — faithful mapping onto the existing GDI surface (HDC).
//   * D2DRenderer   — Direct2D (GPU-accelerated) backend.
//
// The design maps 1:1 onto the GDI primitives the engine already uses, so the
// migration is mechanical: BeginPath/EndPath/FillPath -> Path + FillPath,
// Polyline -> DrawPolyline, PolyBezier -> DrawBezier, Ellipse/Rectangle ->
// DrawEllipse/DrawRect, TextOut -> DrawText, SetPixel markers -> DrawDot.

#pragma once

#include "RenderTypes.h"

namespace acr {

class IRenderer {
public:
    virtual ~IRenderer() = default;

    // Frame lifecycle. D2D requires BeginDraw/EndDraw around a frame; GDI is a
    // no-op pair. Return false if the target must be recreated (D2D device lost).
    virtual bool BeginFrame() = 0;
    virtual bool EndFrame()   = 0;
    virtual void Clear(const Color& bg) = 0;

    // World -> device transform and state stack (replaces SetMapMode +
    // SetWindowExt/ViewportExt + manual save/restore).
    virtual void SetTransform(const Mat3& worldToDevice) = 0;
    virtual void Push() = 0;   // SaveDC
    virtual void Pop()  = 0;   // RestoreDC

    // Immediate primitives.
    virtual void DrawPolyline(const Vec2* pts, size_t n, const Stroke&) = 0;
    virtual void DrawPolygon  (const Vec2* pts, size_t n, const Fill&,
                               const Stroke* outline = nullptr) = 0;
    virtual void DrawBezier   (const Vec2* pts, size_t n, const Stroke&) = 0; // n = 1 + 3*k
    virtual void DrawEllipse  (const Rect2&, const Fill&, const Stroke* outline = nullptr) = 0;
    virtual void DrawRect     (const Rect2&, const Fill&, const Stroke* outline = nullptr) = 0;
    virtual void DrawDot      (const Vec2&, const Color&) = 0;   // replaces SetPixel markers

    // Path fill/stroke (replaces BeginPath/EndPath/FillPath/StrokeAndFillPath).
    virtual void FillPath  (const Path&, const Fill&)   = 0;
    virtual void StrokePath(const Path&, const Stroke&) = 0;

    // Text (replaces TextOut/DrawText/GetTextExtent/GetTextMetrics).
    // (Named DrawTextAt to avoid the DrawText macro defined by <windows.h>.)
    virtual Rect2 MeasureText(const std::wstring&, const TextStyle&) = 0;
    virtual void  DrawTextAt (const Vec2& at, const std::wstring&, const TextStyle&) = 0;
};

} // namespace acr
