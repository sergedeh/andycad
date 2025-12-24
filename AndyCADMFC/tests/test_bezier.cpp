#include "test_common.h"

#include "core/bezier/CBezier.h"

namespace {
void test_bezier_construct() {
    CBezier b;
    (void)b;
    expect_true(true, "CBezier construct");
}

struct Register {
    Register() { add_test("CBezier construct", test_bezier_construct); }
} register_test;
}  // namespace
