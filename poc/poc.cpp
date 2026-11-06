// AndyCAD rendering proof-of-concept — Direct2D retained-mode renderer.
//
// Demonstrates the two pain points and the two SetPixel use-cases:
//   1) Filling objects                -> D2D FillGeometry (incl. self-intersecting fills)
//   2) Splines / curves               -> kept as curves, no per-frame tessellation
//   3) Transparency (SetPixel)        -> D2D alpha compositing
//   4) Texture processing (SetPixel)  -> D2D bitmap brush (GPU texture sampling)
//
// Plus a benchmark: "retained" (cache geometry, redraw with a view transform)
// vs "immediate" (re-flatten curves every frame, like the current GDI path).
//
// Keys:  R = retained   T = re-tessellate every frame
//        +/- = entity count       ESC = exit
// Writes per-second stats to poc_results.txt in the working directory.

#include <windows.h>
#include <d2d1.h>
#include <dwrite.h>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cwchar>
#include <chrono>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

using Clock = std::chrono::steady_clock;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------
static unsigned g_seed = 0x1234567u;
static float rnd() {                              // deterministic pseudo-random [0,1)
    g_seed = g_seed * 1103515245u + 12345u;
    return (float)((g_seed >> 16) & 0x7fff) / 32768.0f;
}
static float frnd(float a, float b) { return a + (b - a) * rnd(); }

static void FlattenCubic(const D2D1_POINT_2F& p0, const D2D1_POINT_2F& p1,
                         const D2D1_POINT_2F& p2, const D2D1_POINT_2F& p3,
                         int n, std::vector<D2D1_POINT_2F>& out) {
    for (int i = 0; i <= n; ++i) {
        float t = (float)i / n, u = 1.0f - t;
        float x = u*u*u*p0.x + 3*u*u*t*p1.x + 3*u*t*t*p2.x + t*t*t*p3.x;
        float y = u*u*u*p0.y + 3*u*u*t*p1.y + 3*u*t*t*p2.y + t*t*t*p3.y;
        out.push_back(D2D1::Point2F(x, y));
    }
}

static ID2D1PathGeometry* MakeBezierGeom(ID2D1Factory* f,
        D2D1_POINT_2F p0, D2D1_POINT_2F c1, D2D1_POINT_2F c2, D2D1_POINT_2F p1, bool closed) {
    ID2D1PathGeometry* g = nullptr;
    f->CreatePathGeometry(&g);
    ID2D1GeometrySink* s = nullptr;
    g->Open(&s);
    s->BeginFigure(p0, closed ? D2D1_FIGURE_BEGIN_FILLED : D2D1_FIGURE_BEGIN_HOLLOW);
    D2D1_BEZIER_SEGMENT seg = D2D1::BezierSegment(c1, c2, p1);
    s->AddBezier(seg);
    s->EndFigure(closed ? D2D1_FIGURE_END_CLOSED : D2D1_FIGURE_END_OPEN);
    s->Close();
    s->Release();
    return g;
}

static ID2D1PathGeometry* MakePolylineGeom(ID2D1Factory* f,
        const std::vector<D2D1_POINT_2F>& pts, bool closed) {
    ID2D1PathGeometry* g = nullptr;
    f->CreatePathGeometry(&g);
    ID2D1GeometrySink* s = nullptr;
    g->Open(&s);
    if (!pts.empty()) {
        s->BeginFigure(pts[0], closed ? D2D1_FIGURE_BEGIN_FILLED : D2D1_FIGURE_BEGIN_HOLLOW);
        if (pts.size() > 1) s->AddLines(&pts[1], (UINT32)(pts.size() - 1));
        s->EndFigure(closed ? D2D1_FIGURE_END_CLOSED : D2D1_FIGURE_END_OPEN);
    }
    s->Close();
    s->Release();
    return g;
}

// Self-intersecting pentagram, to show even-odd (holes) vs winding fill.
static ID2D1PathGeometry* MakeStarGeom(ID2D1Factory* f, D2D1_POINT_2F c, float R,
                                       D2D1_FILL_MODE mode) {
    D2D1_POINT_2F pts[5];
    for (int i = 0; i < 5; ++i) {
        float a = (float)(-1.5707963f + i * 2.0 * 3.14159265 / 5.0);
        pts[i] = D2D1::Point2F(c.x + R * cosf(a), c.y + R * sinf(a));
    }
    ID2D1PathGeometry* g = nullptr;
    f->CreatePathGeometry(&g);
    ID2D1GeometrySink* s = nullptr;
    g->Open(&s);
    s->SetFillMode(mode);
    s->BeginFigure(pts[0], D2D1_FIGURE_BEGIN_FILLED);
    int order[5] = { 0, 2, 4, 1, 3 };
    for (int i = 1; i < 5; ++i) s->AddLine(pts[order[i]]);
    s->EndFigure(D2D1_FIGURE_END_CLOSED);
    s->Close();
    s->Release();
    return g;
}

// ---------------------------------------------------------------------------
// App state
// ---------------------------------------------------------------------------
struct Ent { ID2D1Geometry* geom; ID2D1Brush* brush; float stroke; };
struct BezCtrl { D2D1_POINT_2F p0, c1, c2, p1; bool closed; };

struct App {
    ID2D1Factory*          factory = nullptr;   // long-lived
    IDWriteFactory*        dwrite  = nullptr;   // long-lived
    IDWriteTextFormat*     fmt     = nullptr;   // long-lived

    ID2D1HwndRenderTarget* rt      = nullptr;   // device resource
    ID2D1SolidColorBrush* solid   = nullptr;   // device resource (opaque)
    ID2D1SolidColorBrush* alpha   = nullptr;   // device resource (transparent)
    ID2D1Bitmap*          bitmap  = nullptr;   // device resource (texture)
    ID2D1BitmapBrush*     tex     = nullptr;   // device resource (texture fill)

    std::vector<Ent>      circles, beziers, lines;   // factory-level geometries
    std::vector<BezCtrl>  bezCtrl;
    ID2D1Geometry*        starAlt = nullptr;
    ID2D1Geometry*        starWnd = nullptr;

    bool   immediate = false;
    int    scale = 1;
    float  zoom = 1.0f, panx = 0.0f, pany = 0.0f, t = 0.0f;

    int    frames = 0;
    double accFrameMs = 0, accPrepMs = 0;
    Clock::time_point secStart;
    bool   autoExit = false;
    Clock::time_point exitAt;
    FILE*  log = nullptr;
};
static App g;

// ---------------------------------------------------------------------------
// Resource management
// ---------------------------------------------------------------------------
static void ReleaseScene() {
    for (auto& e : g.circles) e.geom->Release();
    for (auto& e : g.beziers) e.geom->Release();
    for (auto& e : g.lines)   e.geom->Release();
    g.circles.clear(); g.beziers.clear(); g.lines.clear(); g.bezCtrl.clear();
    if (g.starAlt) { g.starAlt->Release(); g.starAlt = nullptr; }
    if (g.starWnd) { g.starWnd->Release(); g.starWnd = nullptr; }
}

static void BuildScene(int W, int H) {
    ReleaseScene();
    int nc = 2000 * g.scale;
    int nb = 1500 * g.scale;
    int nl = 4000 * g.scale;

    for (int i = 0; i < nc; ++i) {
        float x = frnd(0, (float)W), y = frnd(0, (float)H), r = frnd(3, 30);
        ID2D1EllipseGeometry* ge = nullptr;
        g.factory->CreateEllipseGeometry(D2D1::Ellipse(D2D1::Point2F(x, y), r, r), &ge);
        ID2D1Brush* b = g.solid;
        if      (i % 4 == 1) b = g.alpha;   // transparency case
        else if (i % 4 == 2) b = g.tex;     // texture-fill case
        g.circles.push_back({ ge, b, 0.0f });
    }
    for (int i = 0; i < nb; ++i) {
        D2D1_POINT_2F p0 = D2D1::Point2F(frnd(0,(float)W), frnd(0,(float)H));
        D2D1_POINT_2F c1 = D2D1::Point2F(frnd(0,(float)W), frnd(0,(float)H));
        D2D1_POINT_2F c2 = D2D1::Point2F(frnd(0,(float)W), frnd(0,(float)H));
        D2D1_POINT_2F p1 = D2D1::Point2F(frnd(0,(float)W), frnd(0,(float)H));
        bool closed = (i % 5 == 0);
        ID2D1Geometry* ge = MakeBezierGeom(g.factory, p0, c1, c2, p1, closed);
        g.beziers.push_back({ ge, closed ? g.alpha : g.solid, closed ? 0.0f : 2.0f });
        g.bezCtrl.push_back({ p0, c1, c2, p1, closed });
    }
    for (int i = 0; i < nl; ++i) {
        std::vector<D2D1_POINT_2F> pts;
        int nseg = 2 + (int)(rnd() * 6);
        float x = frnd(0,(float)W), y = frnd(0,(float)H);
        for (int s = 0; s <= nseg; ++s) {
            pts.push_back(D2D1::Point2F(x, y));
            x += frnd(-60, 60); y += frnd(-60, 60);
        }
        g.lines.push_back({ MakePolylineGeom(g.factory, pts, false), g.solid, 1.0f });
    }
    g.starAlt = MakeStarGeom(g.factory, D2D1::Point2F((float)W*0.20f,(float)H*0.82f), 130.0f, D2D1_FILL_MODE_ALTERNATE);
    g.starWnd = MakeStarGeom(g.factory, D2D1::Point2F((float)W*0.40f,(float)H*0.82f), 130.0f, D2D1_FILL_MODE_WINDING);
}

static void DiscardDeviceResources() {
    if (g.tex)    { g.tex->Release();    g.tex    = nullptr; }
    if (g.bitmap) { g.bitmap->Release(); g.bitmap = nullptr; }
    if (g.alpha)  { g.alpha->Release();  g.alpha  = nullptr; }
    if (g.solid)  { g.solid->Release();  g.solid  = nullptr; }
    if (g.rt)     { g.rt->Release();     g.rt     = nullptr; }
}

static HRESULT CreateDeviceResources(HWND hwnd) {
    HRESULT hr = S_OK;
    RECT rc; GetClientRect(hwnd, &rc);
    D2D1_RENDER_TARGET_PROPERTIES rtp = D2D1::RenderTargetProperties();
    D2D1_HWND_RENDER_TARGET_PROPERTIES htp =
        D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right, rc.bottom));
    hr = g.factory->CreateHwndRenderTarget(rtp, htp, &g.rt);
    if (FAILED(hr)) return hr;

    g.rt->CreateSolidColorBrush(D2D1::ColorF(0.30f, 0.75f, 0.95f, 1.00f), &g.solid);
    g.rt->CreateSolidColorBrush(D2D1::ColorF(0.95f, 0.35f, 0.25f, 0.35f), &g.alpha); // 35% alpha

    // procedural 32x32 texture, premultiplied BGRA
    unsigned char tex[32 * 32 * 4];
    for (int y = 0; y < 32; ++y) for (int x = 0; x < 32; ++x) {
        int i = (y * 32 + x) * 4;
        bool c = (((x / 8) + (y / 8)) % 2) == 0;
        tex[i+0] = c ? 60 : 230;   // B
        tex[i+1] = c ? 210 : 60;   // G
        tex[i+2] = c ? 90 : 40;    // R
        tex[i+3] = 255;            // A
    }
    D2D1_BITMAP_PROPERTIES bp = D2D1::BitmapProperties(
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
    hr = g.rt->CreateBitmap(D2D1::SizeU(32, 32), tex, 32 * 4, &bp, &g.bitmap);
    if (FAILED(hr)) return hr;
    D2D1_BITMAP_BRUSH_PROPERTIES bbp = {};
    bbp.extendModeX = D2D1_EXTEND_MODE_WRAP;
    bbp.extendModeY = D2D1_EXTEND_MODE_WRAP;
    bbp.interpolationMode = D2D1_BITMAP_INTERPOLATION_MODE_LINEAR;
    hr = g.rt->CreateBitmapBrush(g.bitmap, bbp, &g.tex);
    return hr;
}

// ---------------------------------------------------------------------------
// Render
// ---------------------------------------------------------------------------
static void Render(HWND hwnd) {
    if (!g.rt) CreateDeviceResources(hwnd);
    RECT rc; GetClientRect(hwnd, &rc);
    int W = rc.right, H = rc.bottom;
    if (W == 0 || H == 0) return;

    auto t0 = Clock::now();
    double prepMs = 0.0;

    // animated view (zoom + pan), exactly the CAD interaction
    g.t += 0.008f;
    g.zoom = 1.6f + 1.2f * sinf(g.t * 0.7f);
    g.panx = 120.0f * sinf(g.t * 0.4f);
    g.pany =  80.0f * cosf(g.t * 0.5f);
    D2D1::Matrix3x2F view =
        D2D1::Matrix3x2F::Scale(g.zoom, g.zoom, D2D1::Point2F((float)W/2, (float)H/2)) *
        D2D1::Matrix3x2F::Translation(g.panx, g.pany);

    g.rt->BeginDraw();
    g.rt->SetTransform(view);
    g.rt->Clear(D2D1::ColorF(0.045f, 0.05f, 0.06f, 1.0f));

    if (g.immediate) {
        // Simulate the current GDI behavior: flatten every curve to a polyline each frame.
        auto p0 = Clock::now();
        for (size_t i = 0; i < g.bezCtrl.size(); ++i) {
            std::vector<D2D1_POINT_2F> pts;
            FlattenCubic(g.bezCtrl[i].p0, g.bezCtrl[i].c1, g.bezCtrl[i].c2, g.bezCtrl[i].p1, 48, pts);
            ID2D1PathGeometry* ge = MakePolylineGeom(g.factory, pts, g.bezCtrl[i].closed);
            if (g.bezCtrl[i].closed) g.rt->FillGeometry(ge, g.alpha);
            else                     g.rt->DrawGeometry(ge, g.solid, 2.0f);
            ge->Release();
        }
        prepMs = std::chrono::duration<double, std::milli>(Clock::now() - p0).count();
    } else {
        for (auto& e : g.beziers) {
            if (e.stroke == 0.0f) g.rt->FillGeometry(e.geom, e.brush);
            else                  g.rt->DrawGeometry(e.geom, e.brush, e.stroke);
        }
    }

    for (auto& e : g.circles) g.rt->FillGeometry(e.geom, e.brush);
    for (auto& e : g.lines)   g.rt->DrawGeometry(e.geom, e.brush, e.stroke);

    // self-intersecting fill: even-odd (left, hollow center) vs winding (right, solid)
    g.rt->FillGeometry(g.starAlt, g.alpha);
    g.rt->FillGeometry(g.starWnd, g.solid);

    // HUD (screen space)
    g.rt->SetTransform(D2D1::Matrix3x2F::Identity());
    wchar_t buf[256];
    swprintf_s(buf, L"%s  ents=%d  frame=%.2fms  tessellation=%.2fms   [R]retained [T]tessellate  [+/-]scale  [ESC]exit",
               g.immediate ? L"MODE: re-tessellate every frame" : L"MODE: retained (cached geometry)",
               (int)(g.circles.size() + g.beziers.size() + g.lines.size()),
               g.accFrameMs, prepMs);
    g.rt->DrawTextW(buf, (UINT32)wcslen(buf), g.fmt,
                    D2D1::RectF(10, 10, (float)W, 40), g.solid);

    HRESULT hr = g.rt->EndDraw();
    if (hr == (HRESULT)D2DERR_RECREATE_TARGET) { DiscardDeviceResources(); return; }

    // stats: flush every 60 rendered frames
    double frameMs = std::chrono::duration<double, std::milli>(Clock::now() - t0).count();
    g.frames++;
    g.accFrameMs += frameMs;
    g.accPrepMs += prepMs;
    if (g.frames >= 60) {
        double avgFrame = g.accFrameMs / g.frames;
        double avgPrep  = g.accPrepMs / g.frames;
        if (g.log) fprintf(g.log, "%s ents=%d frame=%.2fms tessellation=%.2fms\n",
                           g.immediate ? "immediate" : "retained",
                           (int)(g.circles.size() + g.beziers.size() + g.lines.size()),
                           avgFrame, avgPrep);
        g.frames = 0; g.accFrameMs = 0; g.accPrepMs = 0;
    }
}

// ---------------------------------------------------------------------------
// Window
// ---------------------------------------------------------------------------
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_SIZE: {
        if (g.rt) { RECT rc; GetClientRect(hwnd, &rc);
            g.rt->Resize(D2D1::SizeU(rc.right, rc.bottom)); }
        return 0;
    }
    case WM_KEYDOWN: {
        RECT rc; GetClientRect(hwnd, &rc);
        if (wp == 'R') g.immediate = false;
        else if (wp == 'T') g.immediate = true;
        else if (wp == VK_OEM_PLUS || wp == VK_ADD) { if (g.scale < 4) { g.scale++; BuildScene(rc.right, rc.bottom); } }
        else if (wp == VK_OEM_MINUS || wp == VK_SUBTRACT) { if (g.scale > 1) { g.scale--; BuildScene(rc.right, rc.bottom); } }
        else if (wp == VK_ESCAPE) PostQuitMessage(0);
        return 0;
    }
    case WM_ERASEBKGND: return 1;
    case WM_PAINT: {
        PAINTSTRUCT ps; BeginPaint(hwnd, &ps);
        Render(hwnd);
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_TIMER:
        if (g.autoExit && Clock::now() >= g.exitAt) { PostQuitMessage(0); return 0; }
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    case WM_DESTROY: PostQuitMessage(0); return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    g.immediate = (pCmdLine && wcsstr(pCmdLine, L"immediate") != nullptr);
    g.autoExit  = (pCmdLine && wcsstr(pCmdLine, L"auto") != nullptr);
    if (g.autoExit) g.exitAt = Clock::now() + std::chrono::seconds(15);
    g.log = fopen("poc_results.txt", "w");
    if (g.log) setvbuf(g.log, nullptr, _IONBF, 0);
    if (g.log) fprintf(g.log, "andycad Direct2D PoC — fill/spline/transparency/texture benchmark\n");

    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g.factory);
    if (FAILED(hr)) return 1;
    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                             reinterpret_cast<IUnknown**>(&g.dwrite));
    if (FAILED(hr)) return 1;
    g.dwrite->CreateTextFormat(L"Consolas", nullptr, DWRITE_FONT_WEIGHT_NORMAL,
                               DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
                               16.0f, L"en-us", &g.fmt);

    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = L"AndyCadPoc";
    RegisterClassExW(&wc);

    RECT wr = { 0, 0, 1280, 800 };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
    HWND hwnd = CreateWindowExW(0, L"AndyCadPoc", L"AndyCAD Direct2D PoC",
                                WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                                wr.right - wr.left, wr.bottom - wr.top,
                                nullptr, nullptr, hInst, nullptr);

    CreateDeviceResources(hwnd);   // create rt + brushes + texture BEFORE the scene
    g.secStart = Clock::now();
    BuildScene(1280, 800);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    SetTimer(hwnd, 1, 10, nullptr);   // ~100fps drive

    MSG m;
    while (GetMessageW(&m, nullptr, 0, 0)) { TranslateMessage(&m); DispatchMessageW(&m); }

    ReleaseScene();
    DiscardDeviceResources();
    g.fmt->Release(); g.dwrite->Release(); g.factory->Release();
    if (g.log) fclose(g.log);
    return 0;
}
