// RenderContext.hpp
#pragma once
#include <string>
#include "../vector/CVector.h"

struct RenderContext {
    virtual void drawLine(const CVector& start, const CVector& end) = 0;
    virtual void drawText(const CVector& pos, const std::string& text) = 0;
    virtual ~RenderContext() = default;
};
