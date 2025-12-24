#include "test_common.h"

#include "core/utils/CPoint.hpp"

namespace {
void test_point_basic() {
    CPoint p1(1, 2);
    CPoint p2(3, 4);
    CPoint p3 = p1 + p2;

    expect_near(p3.x, 4.0, 1e-6, "CPoint + x");
    expect_near(p3.y, 6.0, 1e-6, "CPoint + y");
}

struct Register {
    Register() { add_test("CPoint basic", test_point_basic); }
} register_test;
}  // namespace
