#include "AndyCADMFC/core/utils/CRect.hpp"
#include "gtest/gtest.h"

TEST(Primitives, CPoint) {
    CPoint p1;
    EXPECT_EQ(p1.x, 0);
    EXPECT_EQ(p1.y, 0);
    CPoint p2(3.0, 4.0);
    EXPECT_EQ(p2.x, 3.0);
    EXPECT_EQ(p2.y, 4.0);
}

TEST(Primitives, CSize) {
    CSize s1;
    EXPECT_EQ(s1.cx, 0);
    EXPECT_EQ(s1.cy, 0);
    CSize s2(5.0, 6.0);
    EXPECT_EQ(s2.cx, 5.0);
    EXPECT_EQ(s2.cy, 6.0);
}

TEST(Primitives, RectBasics) {
    Rect r1(0, 0, 10, 10);
    EXPECT_EQ(r1.width(), 10);
    EXPECT_EQ(r1.height(), 10);
    EXPECT_TRUE(r1.contains({5,5}));
    EXPECT_TRUE(!r1.contains({10,10}));

    r1.normalize();
    EXPECT_TRUE(!r1.isEmpty());

    Rect r2 = r1.operator Rect();
    EXPECT_TRUE(r2.left < r1.left);
    EXPECT_TRUE(r2.right > r1.right);
}

int main() {
    return gtest::RunAllTests();
}
