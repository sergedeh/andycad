// view_renderer_check.cpp — standalone check for the Direct2D DC-mode path
// used by the CAD view (ViewRenderer + D2DRenderer::BindDC).
//
// Paints a GDI background into a memory DC set up like the view (MM_ISOTROPIC,
// zoom, offset origin), draws a filled path and a stroked line through a
// Direct2D batch, then reads pixels back to confirm that:
//   1. GDI content outside the Direct2D shapes is preserved,
//   2. the shapes land where GDI would have put the same logical points,
//   3. the DC's GDI mapping is restored after the batch.
//
// Build (x64 Developer Command Prompt):
//   cl /nologo /EHsc /std:c++20 view_renderer_check.cpp ViewRenderer.cpp D2DRenderer.cpp user32.lib gdi32.lib

#include <windows.h>
#include <cstdio>
#include <cstdlib>

#include "D2DRenderer.h"
#include "ViewRenderer.h"

static int g_failures = 0;

static void Expect(bool cond, const char* what) {
    std::printf("%s %s\n", cond ? "PASS" : "FAIL", what);
    if (!cond) ++g_failures;
}

static bool Near(COLORREF c, COLORREF want) {
    auto d = [](int a, int b) { return a > b ? a - b : b - a; };
    return d(GetRValue(c), GetRValue(want)) < 24 && d(GetGValue(c), GetGValue(want)) < 24 &&
           d(GetBValue(c), GetBValue(want)) < 24;
}

int main() {
    _putenv_s("ANDYCAD_RENDERER", "d2d");
    acr::D2DRenderer* r = acr::ViewRenderer();
    Expect(r != nullptr, "Direct2D view renderer is created when ANDYCAD_RENDERER=d2d");
    if (!r) return 1;

    const int W = 400, H = 300;
    HDC screen = GetDC(nullptr);
    HDC mem = CreateCompatibleDC(screen);
    HBITMAP bmp = CreateCompatibleBitmap(screen, W, H);
    HGDIOBJ oldBmp = SelectObject(mem, bmp);
    ReleaseDC(nullptr, screen);

    // GDI background: white, plus a blue marker square in the top-left corner.
    RECT all = { 0, 0, W, H };
    HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));
    FillRect(mem, &all, white);
    RECT marker = { 5, 5, 25, 25 };
    HBRUSH blue = CreateSolidBrush(RGB(0, 0, 255));
    FillRect(mem, &marker, blue);

    // View-like mapping: isotropic, 2x zoom, origin in the middle of the bitmap.
    SetMapMode(mem, MM_ISOTROPIC);
    SetWindowExtEx(mem, 100, 100, nullptr);
    SetViewportExtEx(mem, 200, 200, nullptr);
    SetViewportOrgEx(mem, W / 2, H / 2, nullptr);
    SetWindowOrgEx(mem, 0, 0, nullptr);

    // Where GDI puts logical (10,10)-(40,40) and logical (-60,0).
    POINT gdi[3] = { { 10, 10 }, { 40, 40 }, { -60, 0 } };
    LPtoDP(mem, gdi, 3);

    Expect(acr::BeginViewBatch(r, mem), "BeginViewBatch binds the memory DC");

    acr::Path fillPath;
    fillPath.MoveTo(acr::Vec2(10, 10));
    fillPath.LineTo(acr::Vec2(40, 10));
    fillPath.LineTo(acr::Vec2(40, 40));
    fillPath.LineTo(acr::Vec2(10, 40));
    fillPath.Close();
    acr::Fill fill;
    fill.color = acr::Color(1.0f, 0.0f, 0.0f, 1.0f);
    r->FillPath(fillPath, fill);

    acr::Path line;
    line.MoveTo(acr::Vec2(-60, -30));
    line.LineTo(acr::Vec2(-60, 30));
    acr::Stroke stroke;
    stroke.cosmetic = true;
    stroke.color = acr::Color(0.0f, 0.6f, 0.0f, 1.0f);
    r->StrokePath(line, stroke);

    // Horizontal hairline at logical y = 45 (spans x -20..20).
    acr::Path hline;
    hline.MoveTo(acr::Vec2(-20, 45));
    hline.LineTo(acr::Vec2(20, 45));
    r->StrokePath(hline, stroke);

    Expect(acr::EndViewBatch(r), "EndViewBatch presents without device errors");
    Expect(GetMapMode(mem) == MM_ISOTROPIC, "GDI map mode restored after the batch");

    // Read back in device pixels.
    SetMapMode(mem, MM_TEXT);
    SetViewportOrgEx(mem, 0, 0, nullptr);
    int cx = (gdi[0].x + gdi[1].x) / 2, cy = (gdi[0].y + gdi[1].y) / 2;
    Expect(Near(GetPixel(mem, cx, cy), RGB(255, 0, 0)), "filled path lands at the GDI-mapped position");
    Expect(Near(GetPixel(mem, gdi[1].x + 6, gdi[1].y + 6), RGB(255, 255, 255)), "no fill outside the path");
    Expect(Near(GetPixel(mem, 15, 15), RGB(0, 0, 255)), "earlier GDI content is preserved");
    for (int dx = -2; dx <= 2; ++dx) {
        COLORREF c = GetPixel(mem, gdi[2].x + dx, gdi[2].y);
        std::printf("  x%+d: %d,%d,%d\n", dx, GetRValue(c), GetGValue(c), GetBValue(c));
    }
    Expect(Near(GetPixel(mem, gdi[2].x, gdi[2].y), RGB(0, 153, 0)), "cosmetic stroke drawn at the mapped x");
    Expect(Near(GetPixel(mem, gdi[2].x + 4, gdi[2].y), RGB(255, 255, 255)), "cosmetic stroke stays ~1px wide under 2x zoom");
    {
        int hy = H / 2 + 90;   // logical 45 at 2x zoom from the centre
        int hits = 0;
        for (int dy = -2; dy <= 2; ++dy)
            if (Near(GetPixel(mem, W / 2, hy + dy), RGB(0, 153, 0))) ++hits;
        std::printf("  horizontal hairline rows hit: %d\n", hits);
        Expect(hits == 1, "horizontal cosmetic stroke drawn exactly one pixel tall");
    }

    // ---- Textures: a 2x2 image (red, blue / green, transparent) ----
    {
        const uint32_t px[4] = { 0xFFFF0000u, 0xFF0000FFu,     // top: red, blue
                                 0xFF00FF00u, 0x00000000u };   // bottom: green, clear
        acr::TextureSource tex;
        tex.key = &px; tex.revision = 1; tex.pixels = px; tex.width = 2; tex.height = 2;

        // Re-apply the view mapping and paint a white background in device space.
        RECT bgRect = { 0, 0, W, H };
        FillRect(mem, &bgRect, white);
        SetMapMode(mem, MM_ISOTROPIC);
        SetWindowExtEx(mem, 100, 100, nullptr);
        SetViewportExtEx(mem, 200, 200, nullptr);
        SetViewportOrgEx(mem, W / 2, H / 2, nullptr);

        // Stretch the image over logical (0,0)-(40,40) => texel 1 = 20 units.
        acr::Path quad;
        quad.MoveTo(acr::Vec2(0, 0)); quad.LineTo(acr::Vec2(40, 0));
        quad.LineTo(acr::Vec2(40, 40)); quad.LineTo(acr::Vec2(0, 40)); quad.Close();
        acr::Vec2 src[3] = { {0, 0}, {2, 0}, {0, 2} };
        acr::Vec2 dst[3] = { {0, 0}, {40, 0}, {0, 40} };
        acr::Mat3 t2w;
        Expect(acr::Mat3::FromTriangles(src, dst, t2w), "texel-to-world affine solves");

        // Same image tiled at half size over logical (-60,0)-(-20,40).
        acr::Path tileQuad;
        tileQuad.MoveTo(acr::Vec2(-60, 0)); tileQuad.LineTo(acr::Vec2(-20, 0));
        tileQuad.LineTo(acr::Vec2(-20, 40)); tileQuad.LineTo(acr::Vec2(-60, 40)); tileQuad.Close();
        acr::Vec2 tdst[3] = { {-60, 0}, {-40, 0}, {-60, 20} };
        acr::Mat3 tile;
        acr::Mat3::FromTriangles(src, tdst, tile);

        // Half-opacity copy over logical (60,0)-(100,40).
        acr::Path halfQuad;
        halfQuad.MoveTo(acr::Vec2(60, 0)); halfQuad.LineTo(acr::Vec2(100, 0));
        halfQuad.LineTo(acr::Vec2(100, 40)); halfQuad.LineTo(acr::Vec2(60, 40)); halfQuad.Close();
        acr::Vec2 hdst[3] = { {60, 0}, {100, 0}, {60, 40} };
        acr::Mat3 half;
        acr::Mat3::FromTriangles(src, hdst, half);

        Expect(acr::BeginViewBatch(r, mem), "texture batch begins");
        r->FillPathWithTexture(quad, tex, t2w, acr::TextureLayout::Stretch, 1.0f);
        r->FillPathWithTexture(tileQuad, tex, tile, acr::TextureLayout::Tile, 1.0f);
        r->FillPathWithTexture(halfQuad, tex, half, acr::TextureLayout::Stretch, 0.5f);
        Expect(acr::EndViewBatch(r), "texture batch presents");

        // Sample texel centres in logical space, read in device space.
        auto at = [&](double lx, double ly) {
            POINT p = { (LONG)lx, (LONG)ly };
            LPtoDP(mem, &p, 1);
            int sm = SetMapMode(mem, MM_TEXT);
            POINT vo; SetViewportOrgEx(mem, 0, 0, &vo);
            COLORREF c = GetPixel(mem, p.x, p.y);
            SetViewportOrgEx(mem, vo.x, vo.y, nullptr);
            SetMapMode(mem, MM_ISOTROPIC);
            SetWindowExtEx(mem, 100, 100, nullptr);
            SetViewportExtEx(mem, 200, 200, nullptr);
            (void)sm;
            return c;
        };
        Expect(Near(at(10, 10), RGB(255, 0, 0)), "stretched texel (0,0) is red");
        Expect(Near(at(30, 10), RGB(0, 0, 255)), "stretched texel (1,0) is blue");
        Expect(Near(at(10, 30), RGB(0, 255, 0)), "stretched texel (0,1) is green");
        Expect(Near(at(30, 30), RGB(255, 255, 255)), "transparent texel shows the background");
        Expect(Near(at(-55, 5), RGB(255, 0, 0)) && Near(at(-35, 5), RGB(255, 0, 0)) &&
               Near(at(-35, 25), RGB(255, 0, 0)), "tiled image repeats every 20 units");
        Expect(Near(at(70, 10), RGB(255, 128, 128)), "half opacity blends red with white");
    }

    SelectObject(mem, oldBmp);
    DeleteObject(bmp);
    DeleteObject(white);
    DeleteObject(blue);
    DeleteDC(mem);

    std::printf("%s (%d failure%s)\n", g_failures ? "FAILED" : "ALL PASSED", g_failures, g_failures == 1 ? "" : "s");
    return g_failures ? 1 : 0;
}
