# AndyCAD — Rendering Inventory

Prepared by static analysis of `andy2/`. Everything below is about the **presentation layer**:
what GDI primitives the entity `draw()` methods use, so we can define the seam for a
GPU/accelerated renderer without changing the engine (model/controller) logic.

## 0. Architecture (as-is, confirmed)

- `CDraw` is a **controller** (`Draw.h`: `class CDraw : public CTVector, public CSubject, public CObserver`).
  It dispatches commands (`AddLine`, `AddCircle`, `rotate`, `fill`, `save`, `open`, `undo`, …) and
  holds entity members (`CCercle pCircle`, `CLine pLine`, `CRectangle pRectangle`, `CBezier pBezier`, …).
- **Rendering lives in the entities** through a polymorphic `virtual void draw(CDC*)` on `CFigure`,
  overridden per entity. The `CDC*` is threaded through only because MFC requires it.
- The view (`CCadView`) double-buffers via a memory `CDC` and blits with `BitBlt`/`StretchBlt`.

This is the good news: the rendering seam can be drawn **at the `CDC` boundary inside the entity
`draw()` methods**, leaving the controller and view logic untouched.

## 1. Entity draw methods (the seam surface)

| Entity | Method(s) | Location |
|---|---|---|
| Base | `CFigure::draw(CDC*)` | `Figure.cpp:144` |
| Line | `CLine::draw` · `CLine::Fill(CDC*, CPoint, COLORREF)` | `Line.cpp:157` · `Line.cpp:850` |
| Circle/arc | `CCercle` (draw via tessellated `Polyline` + path fill) | `Cercle.cpp` |
| Rectangle | `CRectangle::draw` | `rectangle.cpp:179` |
| Bezier | `CBezier::draw` (+ `Render`) | `Bezier.cpp:1741` (dup `Bezier1.cpp:1008`) |
| Spline | `CSpline::draw` | `Spline.cpp:233` |
| Text | `CTextCad::draw` | `Textcad.cpp:1698` (+ `Textcad1.cpp:122`, `Textcad_2.cpp:141`) |
| Image | `CImage::draw` · `CImage::drawTrans` | `image.cpp:242` · `image.cpp:983` |
| Dimensions | `CDim::draw` · `CDimL::draw` · `CDimA` | `dim.cpp:877` · `diml.cpp:253` |
| QLine | `CQLine::draw` | `qline.cpp:308` |
| Block/library | `CLibS::draw` | `Libs.cpp:237` |
| Bounding box | `CAABB::draw` (debug) | `AABB.cpp:639` |
| CAM / FFD | `CCAM::draw` (empty) · `CFFD::draw` | `CAM.cpp:204` · `FFD.cpp:291` |
| Fill command | `CDraw::fill` · `CDraw::unfill` | `Draw.cpp:5400` · `Draw.cpp:4390` |

## 2. Complete GDI primitive surface

This is the full set of `CDC` calls the new renderer must cover. Grouped by category.

### 2.1 Vector / stroke
- `MoveTo`, `LineTo`
- `Polyline` — **heavy use** (circles/arcs/splines are tessellated to polylines)
- `Polygon`
- `PolyBezier`, `PolyBezierTo` — native cubic-bezier drawing
- `Ellipse`, `Rectangle` — shapes + control-point markers
- `SetPixel` — per-pixel (see §3)
- **No** `Arc`/`ArcTo`/`AngleArc`/`Chord`/`Pie` found → curves are *never* drawn with GDI's arc
  primitives; they are tessellated to polylines/beziers first.

### 2.2 Path construction + fill
- `BeginPath`, `EndPath`
- `FillPath`, `StrokePath`, `StrokeAndFillPath`
- `FlattenPath` — converts bezier segments inside a path to lines before stroke
- `CloseFigure` — **only in commented-out code** (paths are filled without an explicit close)

### 2.3 Text
- `TextOut`, `DrawText` (`DT_CALCRECT`, `DT_WORDBREAK`, `DT_NOCLIP`)
- `GetTextExtent`, `GetTextMetrics`
- `SetTextAlign` (`TA_BASELINE`), `SetTextColor`, `SetBkColor`, `SetBkMode` (`TRANSPARENT`/`OPAQUE`)
- Text is also drawn **into a path** then `StrokeAndFillPath` (outlined/filled text glyphs).

### 2.4 Images / blitting
- `BitBlt`, `StretchBlt` (double-buffer present; image draw)
- Image file decode is via the bundled **CxImage** stack; screen draw goes through memory DCs.

### 2.5 Transform / mapping (the zoom/pan model)
- `SetMapMode` — `MM_TEXT`, `MM_ISOTROPIC`, `MM_ANISOTROPIC`, `MM_TWIPS`
- `SetWindowExt` / `SetViewportExt`, `SetWindowOrg` / `SetViewportOrg`
- Zoom/pan = `MM_ISOTROPIC` + window/viewport extents + origins (world→device transform in GDI).
- `LPtoDP` / `DPtoLP` used in fill/hit code.

### 2.6 Pens (stroke styles)
- `CreatePen` with: `PS_SOLID`, `PS_COSMETIC`, `PS_GEOMETRIC`, `PS_DOT`, `PS_DASH`, `PS_NULL`
- **Custom line types**: `CreatePen(lstyle, lwidth, &lplb /*LOGBRUSH*/, dwStyleCount, lpStyle)` —
  user-defined dash patterns must be preserved.

### 2.7 Brushes (fill styles)
- `CreateSolidBrush`
- `CreateBrushIndirect` (`LOGBRUSH` — pattern/hatch brushes)
- Stock: `GetStockObject(WHITE_BRUSH | WHITE_PEN | GRAY_BRUSH | BLACK_BRUSH | BLACK_PEN | SYSTEM_FONT | DEFAULT_PALETTE)`

### 2.8 State
- `SetROP2` — `R2_NOTXORPEN` (rubber-band/preview XOR) and `R2_COPYPEN`
- `SelectPalette` / `RealizePalette` — **~60 sites** in `cadView.cpp` (legacy 8-bit palette path)
- `PALETTERGB` (legacy color macro)
- **No** `SaveDC`/`RestoreDC`, **no** `SelectClipRgn`/`IntersectClipRect`/`SelectClipPath` found;
  state (ROP2, map mode, colors) is saved/restored manually.
- `SetPolyFillMode` **never called** → default **ALTERNATE** fill rule.

## 3. Fill — the actual bottleneck (three mechanisms)

1. **Filled entities (path fill).** Closed figures (circles, rectangles, beziers, text) do
   `BeginPath → (tessellated Polyline/PolyBezier) → EndPath → FillPath / StrokeAndFillPath`.
   A `cl` (closed/fill) flag selects stroke vs fill. This is CPU rasterization of the path.

2. **Click-to-fill (flood fill).** `CLine::Fill(CDC*, CPoint, COLORREF)` is a classic scanline
   flood fill using **`GetPixel`/`SetPixel` in a loop** (`Line.cpp:850-913`). Per-pixel GDI calls
   (and `GetPixel` round-trips to the device) — the slowest possible fill, O(area).

3. **Software triangle rasterizer.** `Triangle.cpp` fills triangles with `SetPixel` in a scanline
   loop (3D mesh shading). Also per-pixel CPU work.

> The modern equivalent of #2 is **not** a faster flood fill — it's filling the **vector region**
> by winding rule (even-odd / non-zero), which is exactly what GPU fill does in one draw call.

## 4. Curve / spline cost

- Circles/arcs → tessellated to `Polyline` **at draw time** (no cache).
- Beziers → sometimes native `PolyBezier`, sometimes `FlattenPath`→`Polyline`.
- No retained tessellation cache; segment count scales with quality, and every zoom/pan re-issues
  the calls through GDI.

## 5. Draft renderer seam (`IRenderer` + `IPath`)

Designed to drop in **behind the entity `draw()` methods**, replacing `CDC`. Modeled on the GDI
path API you already use, so it maps 1:1; backends can be GDI (now), Direct2D or Skia (later).

```cpp
// 2D point / rect / color value types (thin, backend-neutral)
struct Vec2  { double x, y; };
struct Rect2 { double x0, y0, x1, y1; };

enum class FillRule { Alternate /*even-odd*/, Winding /*non-zero*/ };

struct Stroke {
    double width;                 // 0 = hairline (cosmetic)
    Color  color;
    bool   isCosmetic;            // PS_COSMETIC vs PS_GEOMETRIC
    std::vector<double> dash;     // custom line type (lpStyle)
    // + cap/join when we have them
};

struct Fill {
    FillRule rule;
    Color    color;               // solid brush
    // + pattern/hatch (LOGBRUSH) later
};

struct TextStyle { /* font, size, align, opaque/transparent, color */ };

// --- Path builder (replaces BeginPath/EndPath/MoveTo/LineTo/BezierTo/CloseFigure) ---
class IPath {
public:
    virtual ~IPath() = default;
    virtual void MoveTo  (const Vec2&) = 0;
    virtual void LineTo  (const Vec2&) = 0;
    virtual void BezierTo(const Vec2& c1, const Vec2& c2, const Vec2& end) = 0;
    virtual void Polyline(const Vec2* pts, size_t n) = 0;
    virtual void Close() = 0;
};

// --- Renderer device (replaces CDC in draw methods) ---
class IRenderer {
public:
    virtual ~IRenderer() = default;

    // Transform (replaces SetMapMode/SetWindowExt/SetViewportExt/SetWindowOrg/SetViewportOrg)
    virtual void SetTransform(const double worldToDevice[3][3]) = 0;
    virtual void Push() = 0;      // replaces SaveDC (we'll introduce it)
    virtual void Pop()  = 0;      // replaces RestoreDC

    // Immediate primitives (thin wrappers; superseded by retained mode later)
    virtual void DrawPolyline(const Vec2* pts, size_t n, const Stroke&) = 0;
    virtual void DrawPolygon  (const Vec2* pts, size_t n, const Fill&, const Stroke* outline = nullptr) = 0;
    virtual void DrawBezier   (const Vec2* pts, size_t n, const Stroke&) = 0; // n = 1 + 3*k
    virtual void DrawEllipse  (const Rect2&, const Fill&, const Stroke* outline = nullptr) = 0;
    virtual void DrawRect     (const Rect2&, const Fill&, const Stroke* outline = nullptr) = 0;
    virtual void DrawDot      (const Vec2&, const Color&) = 0;   // replaces SetPixel markers

    // Path fill/stroke (replaces BeginPath/EndPath/FillPath/StrokeAndFillPath)
    virtual IPath& NewPath(FillRule) = 0;
    virtual void   FillPath  (const IPath&, const Fill&) = 0;
    virtual void   StrokePath(const IPath&, const Stroke&) = 0;

    // Text (replaces TextOut/DrawText/GetTextExtent/GetTextMetrics)
    virtual Rect2 MeasureText(const std::wstring&, const TextStyle&) = 0;
    virtual void  DrawText  (const Vec2& at, const std::wstring&, const TextStyle&) = 0;

    // Image (replaces BitBlt/StretchBlt for entity images)
    virtual void DrawImage(const ImageHandle&, const Rect2& dst, const Rect2& src, float alpha) = 0;
};
```

### Migration notes
- **XOR rubber-banding** (`R2_NOTXORPEN`) should move out of the scene renderer into a separate
  **overlay layer** (preview/handles/snap markers) drawn last, cleared by redraw — no XOR needed.
- **Palette** (`SelectPalette`/`RealizePalette`) disappears entirely; colors become 32-bit `Color`.
- **Curves** get a retained **tessellation cache** per entity (invalidated on edit), so splines stop
  re-tessellating on every redraw; adaptive tessellation scales segments with zoom.
- **Flood fill** (`CLine::Fill`) is replaced by **vector region fill** (even-odd/non-zero) — no
  `GetPixel`/`SetPixel`.
- **`Triangle.cpp` rasterizer** is replaced by a GPU triangle pipeline (indexed buffers + depth).

## 6. Suggested first migration slice (to prove it out)

Pick 3 entities — `CLine`, `CCercle` (fill), `CBezier` (fill + high segment count) — and:
1. Implement `IRenderer`/`IPath` over **Direct2D** (or Skia).
2. Rewrite those three `draw()` methods against it.
3. Add a retained tessellation cache for `CCercle`/`CBezier`.
4. Benchmark: 100k primitives, zoom/pan, and fill of a complex region — GDI vs new backend.
