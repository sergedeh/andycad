#include "test_common.h"

#include <cmath>
#include <iostream>
#include <vector>

namespace {
std::vector<TestCase> registry;
int failures = 0;

const double kDefaultEps = 1e-6;
}  // namespace

void add_test(const char* name, void (*fn)()) {
    registry.push_back(TestCase{name, fn});
}

void expect_true(bool cond, const char* msg) {
    if (!cond) {
        std::cerr << "FAIL: " << msg << std::endl;
        ++failures;
    }
}

void expect_near(double a, double b, double eps, const char* msg) {
    if (std::abs(a - b) > eps) {
        std::cerr << "FAIL: " << msg << " (expected " << b << ", got " << a
                  << ")" << std::endl;
        ++failures;
    }
}

int run_all_tests() {
    for (const auto& test : registry) {
        try {
            test.fn();
        } catch (...) {
            std::cerr << "FAIL: " << test.name << " threw exception" << std::endl;
            ++failures;
        }
    }

    if (failures == 0) {
        std::cout << "All tests passed." << std::endl;
        return 0;
    }
    std::cerr << failures << " test(s) failed." << std::endl;
    return 1;
}
