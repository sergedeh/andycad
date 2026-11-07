// RenderTests.h — automated colour / texture / transparency tests.
#pragma once

class CCadView;

// If ANDYCAD_RUN_RENDER_TESTS names a folder, runs the render tests (every
// object type x solid colour, transparency, texture, tiled texture, texture
// with transparency; GDI and Direct2D), writes report.md, results.csv and a
// PNG per case to that folder, then closes the app. Returns true when it ran.
bool RunRenderTestsIfRequested(CCadView* view);

// If ANDYCAD_RUN_UI_TESTS names a folder, schedules the UI tests to run once
// the message loop is up: for every object type it selects the shape with a
// mouse click, picks a fill colour on the colour bar (right click), a texture
// on the pattern bar, and 50% on the Transparency dialog's slider, then reads
// the pixels back from the window. Uses whichever renderer the app runs with
// (ANDYCAD_RENDERER=d2d for Direct2D). Writes ui_<renderer>.md/.csv and PNGs,
// then closes the app. Returns true when scheduled.
bool RunUITestsIfRequested(CCadView* view);
