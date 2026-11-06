// RenderCompat.h — thin bridges from engine types (COLORREF) into the neutral
// renderer value types. Kept separate so RenderTypes.h/IRenderer.h stay free of
// <windows.h> and MFC.

#pragma once

#include "RenderTypes.h"
#include <windows.h>

namespace acr {

// COLORREF (0x00BBGGRR) -> straight-alpha Color.
inline Color ColorFromColorref(COLORREF c) {
    return Color(GetRValue(c) / 255.0f,
                 GetGValue(c) / 255.0f,
                 GetBValue(c) / 255.0f,
                 1.0f);
}

} // namespace acr
