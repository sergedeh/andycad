#include "test_common.h"

#include "CLine.h"

namespace {
void test_line_box() {
    CVector b(0, 0, 0);
    CVector e(5, 0, 0);
    CLine line(b, e);

    expect_true(line.box.containpts(b), "CLine box contains begin");
    expect_true(line.box.containpts(e), "CLine box contains end");
}

struct Register {
    Register() { add_test("CLine basic", test_line_box); }
} register_test;
}  // namespace
