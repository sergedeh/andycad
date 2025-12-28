#include "CDC_WASM.h"
#include <cstdlib>

#ifdef ANDYCAD_WASM
#include <emscripten/emscripten.h>
#endif

namespace {
#ifdef ANDYCAD_WASM
void ensure_ctx() {
    EM_ASM({
        if (!Module.ctx2d) {
            var canvas = Module['canvas'];
            canvas.width = canvas.width || 800;
            canvas.height = canvas.height || 600;
            Module.ctx2d = canvas.getContext('2d');
            Module.ctx2d.lineWidth = 1;
            Module.ctx2d.strokeStyle = '#000';
            Module.ctx2d.fillStyle = '#000';
            Module.ctx2d.fillStyle = '#fff';
            Module.ctx2d.fillRect(0, 0, canvas.width, canvas.height);
            Module.ctx2d.fillStyle = '#000';
        }
    });
}
#endif
}  // namespace

void CDC_WASM::Polyline(LPPOINT points, int count) {
#ifdef ANDYCAD_WASM
    if (!points || count <= 0) return;
    BeginPath();
    MoveTo(points[0].x, points[0].y);
    for (int i = 1; i < count; ++i) {
        LineTo(points[i].x, points[i].y);
    }
    EndPath();
#endif
}

void CDC_WASM::Polyline(const void* points, int count) {
    Polyline(static_cast<LPPOINT>(const_cast<void*>(points)), count);
}

void CDC_WASM::Rectangle(int x, int y, int w, int h) {
#ifdef ANDYCAD_WASM
    ensure_ctx();
    EM_ASM({
        var ctx = Module.ctx2d;
        ctx.strokeRect($0, $1, $2, $3);
    }, x, y, w, h);
#endif
}

void CDC_WASM::BeginPath() {
#ifdef ANDYCAD_WASM
    ensure_ctx();
    EM_ASM({ Module.ctx2d.beginPath(); });
#endif
}

void CDC_WASM::EndPath() {
#ifdef ANDYCAD_WASM
    ensure_ctx();
    EM_ASM({ Module.ctx2d.stroke(); });
#endif
}

void CDC_WASM::FillPath() {
#ifdef ANDYCAD_WASM
    ensure_ctx();
    EM_ASM({ Module.ctx2d.fill(); });
#endif
}

void* CDC_WASM::SelectObject(void* obj) { return obj; }
CPen* CDC_WASM::SelectObject(CPen* obj) { return obj; }
CBrush* CDC_WASM::SelectObject(CBrush* obj) { return obj; }
HDC CDC_WASM::GetSafeHdc() { return nullptr; }

void CDC_WASM::MoveTo(int x, int y) {
#ifdef ANDYCAD_WASM
    ensure_ctx();
    EM_ASM({ Module.ctx2d.moveTo($0, $1); }, x, y);
#endif
}

void CDC_WASM::LineTo(int x, int y) {
#ifdef ANDYCAD_WASM
    ensure_ctx();
    EM_ASM({ Module.ctx2d.lineTo($0, $1); }, x, y);
#endif
}

void CDC_WASM::TextOut(int x, int y, const char* s) {
#ifdef ANDYCAD_WASM
    ensure_ctx();
    EM_ASM({
        var ctx = Module.ctx2d;
        var str = UTF8ToString($2);
        ctx.fillText(str, $0, $1);
    }, x, y, s);
#endif
}

void CDC_WASM::TextOut(int x, int y, const std::string& s) {
    TextOut(x, y, s.c_str());
}

int CDC_WASM::SetROP2(int /*mode*/) { return 0; }

void CDC_WASM::Ellipse(int x1, int y1, int x2, int y2) {
#ifdef ANDYCAD_WASM
    ensure_ctx();
    int cx = (x1 + x2) / 2;
    int cy = (y1 + y2) / 2;
    int rx = std::abs(x2 - x1) / 2;
    int ry = std::abs(y2 - y1) / 2;
    EM_ASM({
        var ctx = Module.ctx2d;
        ctx.beginPath();
        ctx.ellipse($0, $1, $2, $3, 0, 0, Math.PI * 2);
        ctx.stroke();
    }, cx, cy, rx, ry);
#endif
}
