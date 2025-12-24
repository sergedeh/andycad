#include "test_common.h"

#include "core/circle/Cercle.h"

namespace {
void test_circle_construct() {
    CCercle c;
    (void)c;
    expect_true(true, "CCercle construct");
}

struct Register {
    Register() { add_test("CCercle construct", test_circle_construct); }
} register_test;
}  // namespace
