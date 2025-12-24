#ifndef ANDYCAD_CORE_UTILS_CPOINT_HPP
#define ANDYCAD_CORE_UTILS_CPOINT_HPP
#pragma once

struct CPoint {
    double x = 0;
    double y = 0;

    CPoint() = default;
    CPoint(double x, double y) : x(x), y(y) {}
    
    // Constructor from CVector - implemented after CVector is defined
    CPoint(const class CVector& v);

    // Operator overloads that might be needed
    CPoint operator+(const CPoint& other) const { return CPoint(x + other.x, y + other.y); }
    CPoint operator-(const CPoint& other) const { return CPoint(x - other.x, y - other.y); }
    bool operator==(const CPoint& other) const { return x == other.x && y == other.y; }
    bool operator!=(const CPoint& other) const { return !(*this == other); }
};
typedef CPoint CGPoint;

inline CPoint CGPointv(double x, double y) {
    return CPoint(x, y);
}

inline CPoint CGPointv(CPoint p) {
    return p;
}

#endif // ANDYCAD_CORE_UTILS_CPOINT_HPP
