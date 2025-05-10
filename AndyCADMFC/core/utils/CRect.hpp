#pragma once
#include <algorithm>
#include <cmath>
#include "CPoint.hpp" // define Point as { int x, y; } or Vec2 for doubles
#include "CSize.hpp"  // define Size as { double cx, cy; }

struct Rect {
    double left = 0;
    double top = 0;
    double right = 0;
    double bottom = 0;

    Rect() = default;
    Rect(double l, double t, double r, double b)
        : left(l), top(t), right(r), bottom(b) {}

    Rect(CPoint topLeft, CSize sz)
        : left(topLeft.x), top(topLeft.y),
          right(topLeft.x + sz.cx), bottom(topLeft.y + sz.cy) {}

    double width() const { return std::abs(right - left); }
    double height() const { return std::abs(bottom - top); }

    CPoint topLeft() const { return {static_cast<int>(left), static_cast<int>(top)}; }
    CPoint bottomRight() const { return {static_cast<int>(right), static_cast<int>(bottom)}; }

    void normalize() {
        if (left > right) std::swap(left, right);
        if (top > bottom) std::swap(top, bottom);
    }

    bool isEmpty() const {
        return width() <= 0 || height() <= 0;
    }

    bool contains(CPoint pt) const {
        return pt.x >= left && pt.x < right && pt.y >= top && pt.y < bottom;
    }
    operator Rect() const {
    double size = 5.0; // or whatever buffer makes sense
    return Rect(left - size, top - size, right + size, bottom + size);
}
};

