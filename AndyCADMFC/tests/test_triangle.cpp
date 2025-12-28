#include "test_common.h"

#include "core/triangle/CTriangle.h"

namespace {
void test_triangle_default() {
    CTriangle t;
    expect_true(t.mesh == nullptr, "CTriangle default mesh");
}

struct Register {
    Register() { add_test("CTriangle default", test_triangle_default); }
} register_test;
}  // namespace
