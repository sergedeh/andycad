// RenderTests.h — automated colour / texture / transparency tests.
#pragma once

class CCadView;

// If ANDYCAD_RUN_RENDER_TESTS names a folder, runs the render tests (every
// object type x solid colour, transparency, texture, tiled texture, texture
// with transparency; GDI and Direct2D), writes report.md, results.csv and a
// PNG per case to that folder, then closes the app. Returns true when it ran.
bool RunRenderTestsIfRequested(CCadView* view);
