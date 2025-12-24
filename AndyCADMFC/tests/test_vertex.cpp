#include "test_common.h"

#include "core/vertex/CVertex.h"

namespace {
void test_vertex_basic() {
    CVertex v;
    expect_true(v.getMesh() == nullptr, "CVertex default mesh");

    CVertex v2(CVector(1, 2, 3));
    expect_near(v2.v.x, 1.0, 1e-6, "CVertex v.x");
    expect_near(v2.v.y, 2.0, 1e-6, "CVertex v.y");
    expect_near(v2.v.z, 3.0, 1e-6, "CVertex v.z");
}

struct Register {
    Register() { add_test("CVertex basic", test_vertex_basic); }
} register_test;
}  // namespace
