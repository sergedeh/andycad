// GlyphOutline.h — DirectWrite glyph outlines as polylines (for "convert to curves").
#pragma once

#include <vector>
#include "RenderTypes.h"

namespace acr {

// Outline of each glyph in `glyphs`, in device pixels (each glyph's
// deviceMatrix applied): one entry per glyph, each a list of closed loops,
// curves flattened to within `tolerancePx`. Spaces and missing glyphs give
// an empty list. Returns false if DirectWrite is unavailable.
bool GlyphOutlines(const GlyphDraw* glyphs, size_t n, double tolerancePx,
                   std::vector<std::vector<std::vector<Vec2>>>& out);

} // namespace acr
