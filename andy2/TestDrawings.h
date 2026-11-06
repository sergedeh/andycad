// TestDrawings.h — see TestDrawings.cpp.
#pragma once

class CCadView;

// If ANDYCAD_MAKE_TEST_DRAWINGS names a folder, writes the image test drawings
// there, then closes the app. Returns true when it ran.
bool MakeImageTestDrawingsIfRequested(CCadView* view);
