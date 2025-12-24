#include "test_common.h"

#include "core/rectangle/CRectangle.h"

namespace {
void test_rectangle_construct() {
    CRectangle rect;
    (void)rect;
    expect_true(true, "CRectangle construct");
}

struct Register {
    Register() { add_test("CRectangle construct", test_rectangle_construct); }
} register_test;
}  // namespace
