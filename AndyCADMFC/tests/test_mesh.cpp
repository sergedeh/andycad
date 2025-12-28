#include "test_common.h"

#include "core/mesh/CMesh.h"

namespace {
void test_mesh_default() {
    CMesh m;
    expect_true(m.Vcount() == 0, "CMesh Vcount default");
    expect_true(m.Ecount() == 0, "CMesh Ecount default");
}

struct Register {
    Register() { add_test("CMesh default", test_mesh_default); }
} register_test;
}  // namespace
