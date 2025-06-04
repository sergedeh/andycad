#ifndef ANDYCAD_CORE_UTILS_CPOINT_HPP
#define ANDYCAD_CORE_UTILS_CPOINT_HPP
#pragma once

struct CPoint {
    double x = 0;
    double y = 0;

    CPoint() = default;
    CPoint(double x, double y) : x(x), y(y) {}

};

#endif // ANDYCAD_CORE_UTILS_CPOINT_HPP
