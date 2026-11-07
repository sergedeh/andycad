// RenderTypes.h — backend-neutral 2D value types for the AndyCAD renderer seam.
//
// These replace the GDI-specific CDC/COLORREF/CPoint/CRect surface in the
// presentation layer (see rendering-inventory.md §5). Nothing here depends on
// GDI, MFC, or Direct2D, so entity geometry code can be written once against
// these types and rendered by any backend (GdiRenderer / D2DRenderer / Skia).

#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace acr {

// ---------------------------------------------------------------------------
// Points / rects
// ---------------------------------------------------------------------------
struct Vec2 {
    double x = 0.0, y = 0.0;
    Vec2() = default;
    Vec2(double x_, double y_) : x(x_), y(y_) {}
};

struct Rect2 {
    double x0 = 0.0, y0 = 0.0, x1 = 0.0, y1 = 0.0;
    Rect2() = default;
    Rect2(double x0_, double y0_, double x1_, double y1_)
        : x0(x0_), y0(y0_), x1(x1_), y1(y1_) {}
    double Width()  const { return x1 - x0; }
    double Height() const { return y1 - y0; }
};

// ---------------------------------------------------------------------------
// Color (straight alpha, components 0..1)
// ---------------------------------------------------------------------------
struct Color {
    float r = 0.0f, g = 0.0f, b = 0.0f, a = 1.0f;
    Color() = default;
    Color(float r_, float g_, float b_, float a_ = 1.0f)
        : r(r_), g(g_), b(b_), a(a_) {}
};

// ---------------------------------------------------------------------------
// Fill rule (even-odd = GDI "alternate", non-zero = GDI "winding")
// ---------------------------------------------------------------------------
enum class FillRule { EvenOdd, NonZero };

// ---------------------------------------------------------------------------
// Stroke / Fill / TextStyle
// ---------------------------------------------------------------------------
struct Stroke {
    double width = 0.0;             // 0 => hairline (cosmetic)
    Color  color;
    bool   cosmetic = false;        // PS_COSMETIC vs PS_GEOMETRIC
    std::vector<double> dash;       // empty => solid line (custom lpStyle)
};

struct Fill {
    FillRule rule = FillRule::EvenOdd;
    Color    color;
};

struct TextStyle {
    std::wstring family = L"Segoe UI";
    double       size   = 12.0;
    Color        color;
};

// ---------------------------------------------------------------------------
// 3x2 affine transform, matching D2D1::Matrix3x2F / GDI XFORM layout:
//   x' = x*m11 + y*m21 + dx,   y' = x*m12 + y*m22 + dy
// (operator* is only exact for scale/translate; use FromTriangles for
// general affines.)
// ---------------------------------------------------------------------------
struct Mat3 {
    double m11 = 1.0, m12 = 0.0;
    double m21 = 0.0, m22 = 1.0;
    double dx  = 0.0, dy  = 0.0;

    static Mat3 Identity() { return Mat3(); }
    static Mat3 Translation(double dx_, double dy_) {
        Mat3 m; m.dx = dx_; m.dy = dy_; return m;
    }
    static Mat3 Scale(double sx, double sy) {
        Mat3 m; m.m11 = sx; m.m22 = sy; return m;
    }
    static Mat3 ScaleAround(double sx, double sy, const Vec2& center) {
        return Translation(center.x, center.y) * Scale(sx, sy) *
               Translation(-center.x, -center.y);
    }

    Mat3 operator*(const Mat3& o) const {
        Mat3 r;
        r.m11 = m11 * o.m11 + m12 * o.m21;
        r.m12 = m11 * o.m12 + m12 * o.m22;
        r.m21 = m21 * o.m11 + m22 * o.m21;
        r.m22 = m21 * o.m12 + m22 * o.m22;
        r.dx  = m11 * o.dx  + m12 * o.dy  + dx;
        r.dy  = m21 * o.dx  + m22 * o.dy  + dy;
        return r;
    }

    Vec2 Transform(const Vec2& p) const {
        return Vec2(p.x * m11 + p.y * m21 + dx,
                    p.x * m12 + p.y * m22 + dy);
    }

    // The affine map taking src[i] to dst[i] for three points. Returns false
    // when the source points are collinear (no unique map).
    static bool FromTriangles(const Vec2 src[3], const Vec2 dst[3], Mat3& out) {
        double ux = src[1].x - src[0].x, uy = src[1].y - src[0].y;
        double vx = src[2].x - src[0].x, vy = src[2].y - src[0].y;
        double det = ux * vy - uy * vx;
        if (det > -1e-12 && det < 1e-12) return false;
        double ax = dst[1].x - dst[0].x, ay = dst[1].y - dst[0].y;
        double bx = dst[2].x - dst[0].x, by = dst[2].y - dst[0].y;
        // Solve [ux uy; vx vy] * [m11 m12; m21 m22] = [ax ay; bx by].
        out.m11 = ( vy * ax - uy * bx) / det;
        out.m12 = ( vy * ay - uy * by) / det;
        out.m21 = (-vx * ax + ux * bx) / det;
        out.m22 = (-vx * ay + ux * by) / det;
        out.dx = dst[0].x - (src[0].x * out.m11 + src[0].y * out.m21);
        out.dy = dst[0].y - (src[0].x * out.m12 + src[0].y * out.m22);
        return true;
    }
};

// ---------------------------------------------------------------------------
// Texture source for FillPathWithTexture: straight-alpha pixels, 0xAARRGGBB,
// top row first. `key` identifies the owner (the figure) and `revision`
// changes whenever the pixels change, so backends can upload once and cache.
// ---------------------------------------------------------------------------
enum class TextureLayout { Stretch, Tile };

struct TextureSource {
    const void*          key = nullptr;
    std::uint64_t        revision = 0;
    const std::uint32_t* pixels = nullptr;
    int                  width = 0;
    int                  height = 0;
};

// ---------------------------------------------------------------------------
// Path — a backend-neutral command recorder (replaces BeginPath/EndPath +
// MoveTo/LineTo/PolyBezierTo/CloseFigure). Backends consume the recorded
// command list to build their native geometry / path.
// ---------------------------------------------------------------------------
class Path {
public:
    enum class Type { Move, Line, Bezier, Close };

    struct Cmd {
        Type  type = Type::Move;
        Vec2  a;                  // Move/Line: point; Bezier: c1
        Vec2  b;                  // Bezier: c2
        Vec2  c;                  // Line/Bezier: end point
    };

    std::vector<Cmd> cmds;
    bool closed = false;
    // Monotonic revision, bumped on every mutation. Backends use it to detect
    // staleness of a retained-geometry cache keyed by `const Path*`.
    std::uint64_t revision = 0;

    void MoveTo(const Vec2& p)       { cmds.push_back({ Type::Move, p, {}, {} }); ++revision; }
    void LineTo(const Vec2& p)       { cmds.push_back({ Type::Line, p, {}, p }); ++revision; }
    void BezierTo(const Vec2& c1, const Vec2& c2, const Vec2& p) {
        cmds.push_back({ Type::Bezier, c1, c2, p }); ++revision;
    }
    void Close()                     { cmds.push_back({ Type::Close, {}, {}, {} }); closed = true; ++revision; }
    void Clear()                     { cmds.clear(); closed = false; ++revision; }
    bool Empty() const               { return cmds.empty(); }
};

} // namespace acr
