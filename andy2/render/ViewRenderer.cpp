// ViewRenderer.cpp — see ViewRenderer.h.

#include "ViewRenderer.h"
#include "D2DRenderer.h"

#include <cstdlib>
#include <cstring>

namespace acr {

namespace {
D2DRenderer* g_renderer = nullptr;
bool         g_checked = false;
HDC          g_batchDC = nullptr;
int          g_savedDC = 0;

bool EnabledByEnvironment() {
    char* v = nullptr;
    size_t n = 0;
    if (_dupenv_s(&v, &n, "ANDYCAD_RENDERER") != 0 || !v) return false;
    bool on = _stricmp(v, "d2d") == 0 || _stricmp(v, "direct2d") == 0;
    free(v);
    return on;
}

SIZE TargetSize(HDC hdc) {
    SIZE sz = { 0, 0 };
    HGDIOBJ bmp = GetCurrentObject(hdc, OBJ_BITMAP);
    BITMAP bm = {};
    if (bmp && GetObject(bmp, sizeof(bm), &bm) && bm.bmWidth > 1 && bm.bmHeight > 1) {
        sz.cx = bm.bmWidth;
        sz.cy = bm.bmHeight;
        return sz;
    }
    // Window DC: use the client area of the owning window.
    HWND wnd = WindowFromDC(hdc);
    RECT rc = {};
    if (wnd && GetClientRect(wnd, &rc)) {
        sz.cx = rc.right - rc.left;
        sz.cy = rc.bottom - rc.top;
    }
    return sz;
}
} // namespace

D2DRenderer* ViewRenderer() {
    if (!g_checked) {
        g_checked = true;
        if (EnabledByEnvironment()) {
            g_renderer = new D2DRenderer();
            if (!g_renderer->CreateDeviceResources()) {
                delete g_renderer;
                g_renderer = nullptr;
                OutputDebugStringA("AndyCAD: Direct2D unavailable, using GDI\n");
            }
        }
    }
    return g_renderer;
}

Mat3 TransformFromMappedPoints(const POINT& o, const POINT& x1000, const POINT& y1000) {
    Mat3 m;
    m.m11 = (x1000.x - o.x) / 1000.0;
    m.m12 = (x1000.y - o.y) / 1000.0;
    m.m21 = (y1000.x - o.x) / 1000.0;
    m.m22 = (y1000.y - o.y) / 1000.0;
    m.dx = o.x;
    m.dy = o.y;
    return m;
}

bool BeginViewBatch(D2DRenderer* r, HDC hdc) {
    if (!r || !hdc || g_batchDC) return false;
    SIZE sz = TargetSize(hdc);
    if (sz.cx <= 0 || sz.cy <= 0) return false;

    POINT pts[3] = { { 0, 0 }, { 1000, 0 }, { 0, 1000 } };
    if (!LPtoDP(hdc, pts, 3)) return false;
    Mat3 m = TransformFromMappedPoints(pts[0], pts[1], pts[2]);
    // GDI addresses pixels by their top-left corner; Direct2D samples pixel
    // centres. Shift half a pixel so integer device coordinates hit the same
    // pixels GDI would (1px lines on the pixel, fills excluding right/bottom).
    m.dx += 0.5;
    m.dy += 0.5;

    // Direct2D works in device pixels; neutralise the GDI mapping while the
    // DC render target is bound, and restore it in EndViewBatch.
    g_savedDC = SaveDC(hdc);
    if (!g_savedDC) return false;
    SetMapMode(hdc, MM_TEXT);
    SetWindowOrgEx(hdc, 0, 0, nullptr);
    SetViewportOrgEx(hdc, 0, 0, nullptr);

    RECT rc = { 0, 0, sz.cx, sz.cy };
    if (!r->BindDC(hdc, rc) || !r->BeginFrame()) {
        RestoreDC(hdc, g_savedDC);
        g_savedDC = 0;
        return false;
    }
    r->SetTransform(m);
    // Match GDI's aliased output while both renderers share the back buffer.
    r->SetAntialias(false);
    g_batchDC = hdc;
    return true;
}

bool EndViewBatch(D2DRenderer* r) {
    if (!g_batchDC) return false;
    bool ok = r && r->EndFrame();
    RestoreDC(g_batchDC, g_savedDC);
    g_batchDC = nullptr;
    g_savedDC = 0;
    return ok;
}

} // namespace acr
