#include "test_common.h"

#include "core/utils/CPlane.h"

namespace {
void test_plane_basic() {
    CPlane p(CVector(0, 0, 0), CVector(0, 0, 1));
    double dist = p.dist_to_point(CVector(0, 0, 5));
    expect_near(dist, 5.0, 1e-6, "CPlane dist_to_point");

    CVector cp = p.closest_point(CVector(1, 2, 3));
    expect_near(cp.x, 1.0, 1e-6, "CPlane closest x");
    expect_near(cp.y, 2.0, 1e-6, "CPlane closest y");
    expect_near(cp.z, 0.0, 1e-6, "CPlane closest z");
}

struct Register {
    Register() { add_test("CPlane basic", test_plane_basic); }
} register_test;
}  // namespace
