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

    SelectObject(mem, oldBmp);
    DeleteObject(bmp);
    DeleteObject(white);
    DeleteObject(blue);
    DeleteDC(mem);

    std::printf("%s (%d failure%s)\n", g_failures ? "FAILED" : "ALL PASSED", g_failures, g_failures == 1 ? "" : "s");
    return g_failures ? 1 : 0;
}
