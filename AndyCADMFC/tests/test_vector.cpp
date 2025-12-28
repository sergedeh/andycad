#include "test_common.h"

#include <cmath>
#include "core/vector/CVector.h"

namespace {
void test_vector_basic() {
    CVector v1(1, 2, 3);
    CVector v2(4, 5, 6);
    CVector v3 = v1 + v2;

    expect_near(v3.x, 5.0, 1e-6, "CVector + x");
    expect_near(v3.y, 7.0, 1e-6, "CVector + y");
    expect_near(v3.z, 9.0, 1e-6, "CVector + z");

    CVector v4 = v2 - v1;
    expect_near(v4.x, 3.0, 1e-6, "CVector - x");
    expect_near(v4.y, 3.0, 1e-6, "CVector - y");
    expect_near(v4.z, 3.0, 1e-6, "CVector - z");

    double dot = v1.dot(v2);
    expect_near(dot, 32.0, 1e-6, "CVector dot");

    double mag = v1.absc(v1);
    expect_near(mag, std::sqrt(14.0), 1e-6, "CVector absc");
}

struct Register {
    Register() { add_test("CVector basic", test_vector_basic); }
} register_test;
}  // namespace
