#include "test_common.h"

#include "core/quadtree/CQuadTree.h"

namespace {
void test_quadtree_default() {
    CQuadTree q;
    expect_true(q.bounds.isEmpty(), "CQuadTree bounds empty");
}

struct Register {
    Register() { add_test("CQuadTree default", test_quadtree_default); }
} register_test;
}  // namespace
