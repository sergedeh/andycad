#include "test_common.h"

#include "core/utils/CPoint.hpp"
#include "core/utils/CRect.hpp"
#include "core/vector/CVector.h"

namespace {
void test_rect_basic() {
    CPoint p1(10, 20);
    CPoint p2(30, 45);
    CRect rect(p1, p2);

    expect_near(rect.Width(), 20.0, 1e-6, "CRect width");
    expect_near(rect.Height(), 25.0, 1e-6, "CRect height");
    expect_true(rect.PtInRect(CPoint(15, 25)), "CRect PtInRect true");
    expect_true(!rect.PtInRect(CPoint(5, 5)), "CRect PtInRect false");

    CVector v1(1, 2, 0);
    CVector v2(5, 6, 0);
    CRect rectv(v1, v2);
    expect_near(rectv.Width(), 4.0, 1e-6, "CRect(CVector) width");
    expect_near(rectv.Height(), 4.0, 1e-6, "CRect(CVector) height");
}

struct Register {
    Register() { add_test("CRect basic", test_rect_basic); }
} register_test;
}  // namespace
