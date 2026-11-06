// render_bench.cpp — GDI vs Direct2D benchmark through the IRenderer seam.
//
// Builds a CAD-like scene (stroked polylines, tessellated filled circles,
// stroked cubic beziers, self-intersecting filled stars) and renders it through
// the SAME IRenderer calls in three modes:
//
//   gdi           GdiRenderer  — the engine's current presentation path
//   d2d           D2DRenderer  — geometry rebuilt every frame (no cache)
//   d2d-retained  D2DRenderer  — persistent Path objects (retained geometry)
//
// Usage:
//   render_bench.exe                 interactive (space cycles mode, ESC exits)
//   render_bench.exe auto [scale]    benchmark all modes ~5s each, write results
//
// Writes per-mode averages to render_bench_results.txt in the working directory.

#include <windows.h>
#include <windowsx.h>
#include <vector>
#include <string>
#include <cmath>
#include <cstdio>
#include <chrono>

#include "IRenderer.h"
#include "GdiRenderer.h"
#include "D2DRenderer.h"

using acr::Vec2;
using acr::Mat3;
using acr::Stroke;
using acr::Fill;
using acr::FillRule;
using acr::Path;
using acr::IRenderer;
using acr::GdiRenderer;
using acr::D2DRenderer;
using acr::Color;
using acr::TextStyle;

using Clock = std::chrono::steady_clock;

// ---------------------------------------------------------------------------
// Deterministic scene generation
// ---------------------------------------------------------------------------
static unsigned g_seed = 0x1234567u;
static float rnd() {
    g_seed = g_seed * 1103515245u + 12345u;
    return (float)((g_seed >> 16) & 0x7fff) / 32768.0f;
}
static double frnd(double a, double b) { return a + (b - a) * rnd(); }

struct Scene {
    struct Line  { std::vector<Vec2> pts; Stroke stroke; };
    struct Poly  { std::vector<Vec2> pts; Path path; Fill fill; };   // fill polygon
    struct Curve { std::vector<Vec2> ctrl; Path path; Stroke stroke; };

    std::vector<Line>  lines;
    std::vector<Poly>  circles;   // tessellated to polygons (like the engine)
    std::vector<Poly>  stars;     // self-intersecting (fill-rule demo)
    std::vector<Curve> beziers;

    size_t PrimitiveCount() const {
        return lines.size() + circles.size() + stars.size() + beziers.size();
    }
};

static void TessellateCircle(Path& p, std::vector<Vec2>& pts,
                             double cx, double cy, double r, int segs) {
    for (int i = 0; i < segs; ++i) {
        double a = (double)i / segs * 2.0 * 3.141592653589793;
        Vec2 v(cx + r * cos(a), cy + r * sin(a));
        pts.push_back(v);
        if (i == 0) p.MoveTo(v); else p.LineTo(v);
    }
    p.Close();
}

static Scene BuildScene(int W, int H, int scale) {
    Scene sc;
    int nc = 2000 * scale, nb = 1500 * scale, nl = 4000 * scale;

    Stroke solid{ 1.5, Color(0.45f, 0.85f, 0.95f), false, {} };
    Stroke outline{ 0.0, Color(0.95f, 0.95f, 0.95f), true, {} };
    Stroke bezierStroke{ 2.0, Color(0.95f, 0.6f, 0.2f), false, {} };
    Fill circFill{ FillRule::EvenOdd, Color(0.30f, 0.75f, 0.95f) };
    Fill starFill{ FillRule::EvenOdd, Color(0.95f, 0.35f, 0.25f) };
    Fill starFillW{ FillRule::NonZero, Color(0.4f, 0.9f, 0.4f) };

    for (int i = 0; i < nc; ++i) {
        double cx = frnd(0, (float)W), cy = frnd(0, (float)H), r = frnd(3, 30);
        Scene::Poly c;
        TessellateCircle(c.path, c.pts, cx, cy, r, 48);
        c.fill = circFill;
        sc.circles.push_back(std::move(c));
    }
    for (int i = 0; i < nb; ++i) {
        Scene::Curve c;
        c.ctrl = { Vec2(frnd(0, W), frnd(0, H)), Vec2(frnd(0, W), frnd(0, H)),
                   Vec2(frnd(0, W), frnd(0, H)), Vec2(frnd(0, W), frnd(0, H)) };
        c.path.MoveTo(c.ctrl[0]);
        c.path.BezierTo(c.ctrl[1], c.ctrl[2], c.ctrl[3]);
        c.stroke = bezierStroke;
        sc.beziers.push_back(std::move(c));
    }
    for (int i = 0; i < nl; ++i) {
        Scene::Line l;
        int nseg = 2 + (int)(rnd() * 6);
        double x = frnd(0, W), y = frnd(0, H);
        for (int s = 0; s <= nseg; ++s) {
            l.pts.push_back(Vec2(x, y));
            x += frnd(-60, 60); y += frnd(-60, 60);
        }
        l.stroke = solid;
        sc.lines.push_back(std::move(l));
    }

    // Two self-intersecting pentagrams: even-odd (hollow centre) vs winding.
    {
        Scene::Poly s1, s2;
        int order[5] = { 0, 2, 4, 1, 3 };
        for (int k = 0; k < 2; ++k) {
            double cx = W * (0.20 + 0.20 * k), cy = H * 0.82, R = 130.0;
            Scene::Poly& target = (k == 0) ? s1 : s2;
            std::vector<Vec2> star;
            for (int i = 0; i < 5; ++i) {
                double a = -1.5707963 + i * 2.0 * 3.14159265 / 5.0;
                star.push_back(Vec2(cx + R * cos(a), cy + R * sin(a)));
            }
            target.path.MoveTo(star[order[0]]);
            for (int i = 1; i < 5; ++i) target.path.LineTo(star[order[i]]);
            target.path.Close();
            for (int i = 0; i < 5; ++i) target.pts.push_back(star[order[i]]);
            target.fill = (k == 0) ? starFill : starFillW;
        }
        sc.stars.push_back(std::move(s1));
        sc.stars.push_back(std::move(s2));
    }
    return sc;
}

// ---------------------------------------------------------------------------
// Render one scene through any IRenderer
// ---------------------------------------------------------------------------
static void RenderScene(IRenderer* r, const Scene& sc, bool retained,
                        double zoom, double panx, double pany, int W, int H,
                        const std::wstring& hud) {
    Mat3 view = Mat3::ScaleAround(zoom, zoom, Vec2(W / 2.0, H / 2.0)) *
                Mat3::Translation(panx, pany);

    r->BeginFrame();
    r->SetTransform(view);
    r->Clear(Color(0.045f, 0.05f, 0.06f));

    if (retained) {
        for (auto& c : sc.circles) r->FillPath(c.path, c.fill);
        for (auto& s : sc.stars)   r->FillPath(s.path, s.fill);
        for (auto& b : sc.beziers) r->StrokePath(b.path, b.stroke);
        for (auto& l : sc.lines)   r->DrawPolyline(l.pts.data(), l.pts.size(), l.stroke);
    } else {
        for (auto& c : sc.circles) r->DrawPolygon(c.pts.data(), c.pts.size(), c.fill, nullptr);
        for (auto& s : sc.stars)   r->DrawPolygon(s.pts.data(), s.pts.size(), s.fill, nullptr);
        for (auto& b : sc.beziers) r->DrawBezier(b.ctrl.data(), b.ctrl.size(), b.stroke);
        for (auto& l : sc.lines)   r->DrawPolyline(l.pts.data(), l.pts.size(), l.stroke);
    }

    r->SetTransform(Mat3::Identity());
    TextStyle hudStyle{ L"Consolas", 16.0, Color(0.95f, 0.95f, 0.95f) };
    r->DrawTextAt(Vec2(10, 10), hud, hudStyle);
    r->EndFrame();
}

// ---------------------------------------------------------------------------
// App state
// ---------------------------------------------------------------------------
struct App {
    HWND hwnd = nullptr;
    Scene scene;
    int   scale = 1;
    int   mode = 0;                 // 0=gdi 1=d2d 2=d2d-retained
    bool  retained() const { return mode == 2; }

    GdiRenderer* gdi = nullptr;
    D2DRenderer* d2d = nullptr;

    HDC   memDC = nullptr;
    HBITMAP memBmp = nullptr;
    HGDIOBJ oldBmp = nullptr;

    float t = 0.0f;

    int    frames = 0;
    double accMs = 0.0;
    bool   autoMode = false;
    int    phase = 0;
    Clock::time_point phaseStart;
    FILE*  log = nullptr;

    static const char* ModeName(int m) {
        return m == 0 ? "gdi" : (m == 1 ? "d2d" : "d2d-retained");
    }
};
static App g;

static void ReleaseGdi() {
    if (g.gdi) { delete g.gdi; g.gdi = nullptr; }
    if (g.memDC) {
        SelectObject(g.memDC, g.oldBmp);
        DeleteObject(g.memBmp);
        DeleteDC(g.memDC);
        g.memDC = nullptr; g.memBmp = nullptr;
    }
}

static void EnsureBackends() {
    if (g.mode == 0 && !g.gdi) {
        HDC win = GetDC(g.hwnd);
        g.memDC = CreateCompatibleDC(win);
        g.memBmp = CreateCompatibleBitmap(win, 1280, 800);
        g.oldBmp = SelectObject(g.memDC, g.memBmp);
        ReleaseDC(g.hwnd, win);
        g.gdi = new GdiRenderer(g.memDC);
    }
    if (g.mode != 0 && !g.d2d) {
        g.d2d = new D2DRenderer(g.hwnd);
        g.d2d->CreateDeviceResources();
    }
}

static void Render() {
    EnsureBackends();
    RECT rc; GetClientRect(g.hwnd, &rc);
    int W = rc.right ? rc.right : 1280, H = rc.bottom ? rc.bottom : 800;

    g.t += 0.008f;
    double zoom = 1.6 + 1.2 * sin(g.t * 0.7);
    double panx = 120.0 * sin(g.t * 0.4);
    double pany = 80.0 * cos(g.t * 0.5);

    wchar_t buf[256];
    swprintf_s(buf, L"%hs  ents=%zu  frame=%.2fms", App::ModeName(g.mode),
               g.scene.PrimitiveCount(), g.accMs);

    auto t0 = Clock::now();

    if (g.mode == 0) {
        RenderScene(g.gdi, g.scene, false, zoom, panx, pany, W, H, buf);
        // present the memory DC
        HDC win = GetDC(g.hwnd);
        BitBlt(win, 0, 0, W, H, g.memDC, 0, 0, SRCCOPY);
        ReleaseDC(g.hwnd, win);
    } else {
        RenderScene(g.d2d, g.scene, g.retained(), zoom, panx, pany, W, H, buf);
    }

    double frameMs = std::chrono::duration<double, std::milli>(Clock::now() - t0).count();
    g.frames++;
    g.accMs += frameMs;
}

static void RecordPhase() {
    if (g.frames == 0) return;
    double avg = g.accMs / g.frames;
    if (g.log) {
        fprintf(g.log, "%s ents=%zu frame=%.2fms\n", App::ModeName(g.mode),
                g.scene.PrimitiveCount(), avg);
        fflush(g.log);
    }
    g.frames = 0;
    g.accMs = 0.0;
}

static void NextMode() {
    RecordPhase();
    g.mode = (g.mode + 1) % 3;
    if (!g.autoMode) InvalidateRect(g.hwnd, nullptr, FALSE);
}

// ---------------------------------------------------------------------------
// Window
// ---------------------------------------------------------------------------
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
    case WM_KEYDOWN:
        if (wp == VK_SPACE) NextMode();
        else if (wp == VK_ESCAPE) PostQuitMessage(0);
        return 0;
    case WM_ERASEBKGND: return 1;
    case WM_PAINT: {
        PAINTSTRUCT ps; BeginPaint(hwnd, &ps);
        Render();
        EndPaint(hwnd, &ps);
        return 0;
    }
    case WM_TIMER:
        if (g.autoMode) {
            if (Clock::now() - g.phaseStart >= std::chrono::seconds(5)) {
                RecordPhase();
                g.phase++;
                if (g.phase >= 3) { PostQuitMessage(0); return 0; }
                g.mode = g.phase;
                g.phaseStart = Clock::now();
            }
        }
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    case WM_DESTROY: PostQuitMessage(0); return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

int WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, PWSTR cmd, int nCmdShow) {
    std::wstring c = cmd ? cmd : L"";
    g.autoMode = c.find(L"auto") != std::wstring::npos;
    // optional scale multiplier
    {
        size_t p = c.find(L"auto");
        if (p != std::wstring::npos) {
            std::wstring rest = c.substr(p + 4);
            int s = rest.empty() ? 1 : _wtoi(rest.c_str());
            if (s < 1) s = 1;
            g.scale = s;
        }
    }
    g.log = fopen("render_bench_results.txt", "w");
    if (g.log) {
        fprintf(g.log, "andycad IRenderer benchmark — GDI vs Direct2D (fill/spline/bezier)\n");
        setvbuf(g.log, nullptr, _IONBF, 0);
    }

    g.scene = BuildScene(1280, 800, g.scale);

    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpszClassName = L"AndyCadRenderBench";
    RegisterClassExW(&wc);

    RECT wr = { 0, 0, 1280, 800 };
    AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
    HWND hwnd = CreateWindowExW(0, L"AndyCadRenderBench", L"AndyCAD IRenderer benchmark",
                                WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                                wr.right - wr.left, wr.bottom - wr.top,
                                nullptr, nullptr, hInst, nullptr);
    g.hwnd = hwnd;
    g.phaseStart = Clock::now();
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    SetTimer(hwnd, 1, 10, nullptr);

    MSG m;
    while (GetMessageW(&m, nullptr, 0, 0)) { TranslateMessage(&m); DispatchMessageW(&m); }

    RecordPhase();
    ReleaseGdi();
    if (g.d2d) { delete g.d2d; g.d2d = nullptr; }
    if (g.log) fclose(g.log);
    return 0;
}
