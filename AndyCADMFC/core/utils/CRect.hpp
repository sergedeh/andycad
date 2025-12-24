#pragma once
#include <algorithm>
#include <cmath>
#include "CPoint.hpp" // define Point as { int x, y; } or Vec2 for doubles
#include "CSize.h"  // define Size as { double cx, cy; }

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

    Rect(CPoint topLeft, CPoint bottomRight)
        : left(topLeft.x), top(topLeft.y),
        right(bottomRight.x), bottom(bottomRight.y) {}
    
    // Constructor from CVector - implemented after CVector is defined
    Rect(const class CVector& topLeft, const class CVector& bottomRight);

    double width() const { return std::abs(right - left); }
    double height() const { return std::abs(bottom - top); }

    // MFC Compatibility
    double Width() const { return width(); }
    double Height() const { return height(); }
    bool PtInRect(CPoint pt) const { return contains(pt); }
    CPoint CenterPoint() const { return CPoint((left + right) * 0.5, (top + bottom) * 0.5); }
    bool IsRectEmpty() const { return isEmpty(); }
    void SetRectEmpty() { left = 0; top = 0; right = 0; bottom = 0; }

    // MFC specific cases
    void SetRect(double l, double t, double r, double b) {
        left = l; top = t; right = r; bottom = b;
    }
    void SetRect(CPoint p1, CPoint p2) {
        left = p1.x; top = p1.y; right = p2.x; bottom = p2.y;
    }

    CPoint TopLeft() const { return {left, top}; }
    CPoint BottomRight() const { return {right, bottom}; }
    CPoint topLeft() const { return {left, top}; }     // Keep both for convenience
    CPoint bottomRight() const { return {right, bottom}; }

    void normalize() {
        if (left > right) std::swap(left, right);
        if (top > bottom) std::swap(top, bottom);
    }
    void NormalizeRect() { normalize(); }

    bool isEmpty() const {
        return width() <= 0 || height() <= 0;
    }

    bool contains(CPoint pt) const {
        return pt.x >= left && pt.x <= right && pt.y >= top && pt.y <= bottom;
    }
    
    // Union
    void UnionRect(const Rect* lpRect1, const Rect* lpRect2) {
        left = std::min(lpRect1->left, lpRect2->left);
        top = std::min(lpRect1->top, lpRect2->top);
        right = std::max(lpRect1->right, lpRect2->right);
        bottom = std::max(lpRect1->bottom, lpRect2->bottom);
    }

    bool operator==(const Rect& other) const {
        return left == other.left && top == other.top && right == other.right && bottom == other.bottom;
    }
    bool operator!=(const Rect& other) const {
        return !(*this == other);
    }
};

// For compatibility with old MFC-style naming
using CRect = Rect;
