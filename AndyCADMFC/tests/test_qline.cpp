#include "test_common.h"

#include "core/qline/CQLine.h"

namespace {
void test_qline_construct() {
    CQLine q;
    (void)q;
    expect_true(true, "CQLine construct");
}

struct Register {
    Register() { add_test("CQLine construct", test_qline_construct); }
} register_test;
}  // namespace
