#include "test_common.h"

#include "core/ray/CRay.h"

namespace {
void test_ray_intersect() {
    CVector a(0, 0, 0);
    CVector b(10, 0, 0);
    CVector c(0, 0, 0);
    CVector d(0, 10, 0);

    CRay r1(a, b, false);
    CRay r2(c, d, false);
    CVector inter = r1.Intersect(r2);

    expect_near(inter.x, 0.0, 1e-6, "CRay intersect x");
    expect_near(inter.y, 0.0, 1e-6, "CRay intersect y");
}

struct Register {
    Register() { add_test("CRay intersect", test_ray_intersect); }
} register_test;
}  // namespace
