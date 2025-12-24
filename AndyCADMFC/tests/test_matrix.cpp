#include "test_common.h"

#include "core/matrix/CMatrix.h"

namespace {
void test_matrix_switchrow() {
    double m[4] = {1, 2, 3, 4};
    CMatrix mat;

    int res = mat.switchrow(m, 1, 1, 0, 1, 0, 1);
    expect_true(res == 1, "CMatrix switchrow result");
    expect_near(m[0], 3.0, 1e-6, "CMatrix switchrow m[0]");
    expect_near(m[1], 4.0, 1e-6, "CMatrix switchrow m[1]");
    expect_near(m[2], 1.0, 1e-6, "CMatrix switchrow m[2]");
    expect_near(m[3], 2.0, 1e-6, "CMatrix switchrow m[3]");
}

struct Register {
    Register() { add_test("CMatrix switchrow", test_matrix_switchrow); }
} register_test;
}  // namespace
