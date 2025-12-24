#include "test_common.h"

#include "core/cvector/CCVector.h"

namespace {
void test_ccvector_basic() {
    CCVector a(0.1, 0.2, 0.3);
    CCVector b(0.2, 0.3, 0.4);
    CCVector c = a + b;

    expect_near(c.r, 0.3, 1e-6, "CCVector + r");
    expect_near(c.g, 0.5, 1e-6, "CCVector + g");
    expect_near(c.b, 0.7, 1e-6, "CCVector + b");

    int rgb = a.toRGB();
    expect_true(rgb >= 0, "CCVector toRGB");
}

struct Register {
    Register() { add_test("CCVector basic", test_ccvector_basic); }
} register_test;
}  // namespace
