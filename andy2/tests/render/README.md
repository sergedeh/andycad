# Colour, texture and transparency tests

Two runners, both in `RenderTests.cpp`, both built into the app. Each one runs the
same five objects (rectangle, circle, polygon, image, block with a rectangle
inside) and checks pixels against what the fill should look like on white.

## Automated (`ANDYCAD_RUN_RENDER_TESTS`)

Calls the figure methods the UI ends up in (`setLcolor`, `setTexture`, the
"Transparency" notification at 50%, `setTiled`) and draws each case off-screen
with GDI and with Direct2D. Writes `report.md`, `results.csv` and
`<object>_<case>_<gdi|d2d>.png`.

```
set ANDYCAD_RUN_RENDER_TESTS=%CD%\tests\render
Release\andycad.exe
```

## Through the UI (`ANDYCAD_RUN_UI_TESTS`)

Drives the running app with window messages: Select tool, a mouse click on the
object's outline, a right click on a colour-bar swatch (fill colour), a click on
a pattern-bar button (texture; its source is pointed at `texture_checker.png`),
and Format > Transparency with the slider dragged to 50 and OK. Pixels are read
back from the window. Uses the renderer the app was started with, so run it twice:

```
set ANDYCAD_RUN_UI_TESTS=%CD%\tests\render
Release\andycad.exe
set ANDYCAD_RENDERER=d2d
Release\andycad.exe
```

Writes `ui_gdi.md` / `ui_d2d.md`, matching `.csv` files and `ui_*.png`. Keep the
window visible while it runs (about 20 seconds); it closes itself.

Case numbers in the PNG names: 0 solid colour, 1 colour at 50%, 2 texture,
3 texture at 50%, 4 tiled texture (automated only: there is no UI command for
tiling yet).
