#include "test_common.h"

#include "core/edge/CEdge.h"

namespace {
void test_edge_default() {
    CEdge e;
    expect_true(e.Start() == nullptr, "CEdge Start nullptr");
    expect_true(e.End() == nullptr, "CEdge End nullptr");
}

struct Register {
    Register() { add_test("CEdge default", test_edge_default); }
} register_test;
}  // namespace
