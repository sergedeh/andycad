#include "test_common.h"

#include "core/aabb/CAABB.h"
#include "core/vector/CVector.h"

namespace {
void test_aabb_basic() {
    CAABB box;
    box.empty();
    expect_true(box.isEmpty(), "CAABB empty");

    box.add(CVector(1, 2, 3));
    box.add(CVector(4, 6, 5));

    expect_true(!box.isEmpty(), "CAABB non-empty after add");
    expect_true(box.containpts(CVector(2, 3, 4)), "CAABB containpts true");
    expect_true(!box.containpts(CVector(10, 10, 10)), "CAABB containpts false");
    expect_near(box.volume(), 24.0, 1e-6, "CAABB volume");
}

struct Register {
    Register() { add_test("CAABB basic", test_aabb_basic); }
} register_test;
}  // namespace
