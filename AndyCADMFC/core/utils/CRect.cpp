#include "CRect.hpp"
#include "../vector/CVector.h"

Rect::Rect(const CVector& topLeft, const CVector& bottomRight)
    : left(topLeft.x),
      top(topLeft.y),
      right(bottomRight.x),
      bottom(bottomRight.y) {}
