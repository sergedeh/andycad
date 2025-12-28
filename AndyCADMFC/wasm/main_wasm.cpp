#include "CDC_WASM.h"
#include "draw/CDraw.h"

#ifdef ANDYCAD_WASM
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#endif

namespace {
struct WasmApp {
    CDraw draw;
    CDC_WASM dc;
    bool mouse_down = false;
    bool f_prev_line = false;
    CVector start = CVector(0, 0, 0);
    CVector current = CVector(0, 0, 0);
};

WasmApp& app() {
    static WasmApp instance;
    return instance;
}

#ifdef ANDYCAD_WASM
void clear_canvas() {
    EM_ASM({
        var canvas = Module['canvas'];
        if (!Module.ctx2d) {
            Module.ctx2d = canvas.getContext('2d');
        }
        var ctx = Module.ctx2d;
        if (!canvas.width) canvas.width = 800;
        if (!canvas.height) canvas.height = 600;
        ctx.setTransform(1, 0, 0, 1, 0, 0);
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        ctx.fillStyle = '#fff';
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        ctx.fillStyle = '#000';
    });
}

void render_scene(bool preview_line) {
    clear_canvas();
    app().draw.display(&app().dc, &app().dc);
    if (preview_line) {
        app().dc.BeginPath();
        app().dc.MoveTo((int)app().start.x, (int)app().start.y);
        app().dc.LineTo((int)app().current.x, (int)app().current.y);
        app().dc.EndPath();
    }
}

EM_BOOL on_mouse_down(int /*eventType*/, const EmscriptenMouseEvent* e, void* /*userData*/) {
    app().mouse_down = true;
    app().f_prev_line = false;
    app().start = CVector(e->canvasX, e->canvasY, 0);
    app().current = app().start;
    app().draw.Create(&app().dc, "Line", app().start);
    render_scene(true);
    return EM_TRUE;
}

EM_BOOL on_mouse_move(int /*eventType*/, const EmscriptenMouseEvent* e, void* /*userData*/) {
    if (!app().mouse_down) {
        return EM_FALSE;
    }
    app().current = CVector(e->canvasX, e->canvasY, 0);
    app().f_prev_line = app().draw.add("Line", app().f_prev_line, &app().dc, app().current);
    render_scene(true);
    return EM_TRUE;
}

EM_BOOL on_mouse_up(int /*eventType*/, const EmscriptenMouseEvent* e, void* /*userData*/) {
    if (!app().mouse_down) {
        return EM_FALSE;
    }
    app().mouse_down = false;
    app().current = CVector(e->canvasX, e->canvasY, 0);
    app().draw.finaladd(&app().dc, "Line", app().current, "");
    render_scene(false);
    return EM_TRUE;
}
#endif
}  // namespace

int main() {
    app().draw.Init();
#ifdef ANDYCAD_WASM
    render_scene(false);
    emscripten_set_mousedown_callback("#canvas", nullptr, 1, on_mouse_down);
    emscripten_set_mousemove_callback("#canvas", nullptr, 1, on_mouse_move);
    emscripten_set_mouseup_callback("#canvas", nullptr, 1, on_mouse_up);
#endif
    return 0;
}
