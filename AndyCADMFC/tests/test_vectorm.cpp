#include "test_common.h"

#include "core/vectorm/CVectorm.h"

namespace {
void test_vectorm_basic() {
    CVectorm a(1.0f, 0.0f, 0.0f);
    CVectorm b(0.0f, 1.0f, 0.0f);

    CVectorm c = crossProduct(a, b);
    expect_near(c.x, 0.0, 1e-6, "CVectorm cross x");
    expect_near(c.y, 0.0, 1e-6, "CVectorm cross y");
    expect_near(c.z, 1.0, 1e-6, "CVectorm cross z");

    float mag = vectorMag(a);
    expect_near(mag, 1.0, 1e-6, "CVectorm magnitude");
}

struct Register {
    Register() { add_test("CVectorm basic", test_vectorm_basic); }
} register_test;
}  // namespace
