#ifndef ANDYCAD_CORE_UTILS_CSIZE_HPP
#define ANDYCAD_CORE_UTILS_CSIZE_HPP
#pragma once

struct CSize {
    double cx = 0;
    double cy = 0;

    CSize() = default;
    CSize(double x, double y) : cx(x), cy(y) {}

};

#endif // ANDYCAD_CORE_UTILS_CSIZE_HPP
