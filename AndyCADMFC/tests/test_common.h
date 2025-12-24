#ifndef ANDYCAD_TEST_COMMON_H
#define ANDYCAD_TEST_COMMON_H

struct TestCase {
    const char* name;
    void (*fn)();
};

void add_test(const char* name, void (*fn)());
int run_all_tests();

void expect_true(bool cond, const char* msg);
void expect_near(double a, double b, double eps, const char* msg);

#endif
