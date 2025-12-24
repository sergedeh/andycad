#include "test_common.h"

#include "core/tvector/CTVector.h"

namespace {
void test_tvector_construct() {
    CTVector t;
    (void)t;
    expect_true(true, "CTVector construct");
}

struct Register {
    Register() { add_test("CTVector construct", test_tvector_construct); }
} register_test;
}  // namespace
