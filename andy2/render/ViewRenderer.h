// ViewRenderer.h — opt-in Direct2D rendering for the CAD view.
//
// The view keeps its GDI back buffer (a memory DC). When enabled, figures
// that support the IRenderer path (CFigure::canRender) are drawn into that
// same memory DC through a Direct2D DC render target, in batches; every other
// figure keeps drawing with GDI. GDI-only decorations (selection handles,
// rotate marker) are drawn after each batch via CFigure::drawOverlay.
//
// Enable with the environment variable ANDYCAD_RENDERER=d2d. GDI remains the
// default until the remaining figure types are migrated.

#pragma once

#include <windows.h>

#include "RenderTypes.h"

namespace acr {

class D2DRenderer;

// The process-wide view renderer, or nullptr when Direct2D rendering is off
// or unavailable.
D2DRenderer* ViewRenderer();

// Start a Direct2D batch on `hdc`. The world->device transform is taken from
// the DC's current GDI mapping (map mode, window/viewport origin and extents),
// so figures pass the same logical coordinates they would give GDI.
bool BeginViewBatch(D2DRenderer* r, HDC hdc);

// Finish the batch and restore the DC's GDI state. Returns false if Direct2D
// failed (e.g. device lost); the caller should redraw that batch with GDI.
bool EndViewBatch(D2DRenderer* r);

// Logical->device affine from three mapped points (origin, +1000 x, +1000 y),
// as produced by LPtoDP. Exposed for tests.
Mat3 TransformFromMappedPoints(const POINT& o, const POINT& x1000, const POINT& y1000);

} // namespace acr
