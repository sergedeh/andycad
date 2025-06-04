#ifndef GTEST_LITE_H
#define GTEST_LITE_H
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdlib>

namespace gtest {
struct TestInfo {
    const char* case_name;
    const char* test_name;
    void (*func)();
};

inline int& failure_count() {
    static int f = 0;
    return f;
}

inline std::vector<TestInfo>& registry() {
    static std::vector<TestInfo> r;
    return r;
}

inline void RegisterTest(const char* case_name, const char* test_name, void(*func)()) {
    registry().push_back({case_name, test_name, func});
}

inline void ReportFailure(const char* expr, const char* file, int line) {
    std::cout << file << ":" << line << ": Failure\n  Expected: " << expr << std::endl;
    failure_count()++;
}

inline int RunAllTests() {
    failure_count() = 0;
    for (auto& t : registry()) {
        std::cout << "[ RUN      ] " << t.case_name << "." << t.test_name << std::endl;
        t.func();
    }
    std::cout << "[==========] " << registry().size() << " tests ran." << std::endl;
    std::cout << "[  PASSED  ] " << (registry().size() - failure_count()) << " tests." << std::endl;
    if (failure_count()) std::cout << "[  FAILED  ] " << failure_count() << " tests." << std::endl;
    return failure_count();
}
}

#define TEST(case_name, test_name) \
    void case_name##_##test_name(); \
    namespace { \
    struct case_name##_##test_name##_registrar { \
        case_name##_##test_name##_registrar() { \
            gtest::RegisterTest(#case_name, #test_name, &case_name##_##test_name); \
        } \
    } case_name##_##test_name##_registrar_instance; \
    } \
    void case_name##_##test_name()

#define EXPECT_TRUE(x) do { if(!(x)) gtest::ReportFailure(#x, __FILE__, __LINE__); } while(0)
#define EXPECT_EQ(a,b) do { if(!((a)==(b))) gtest::ReportFailure(#a " == " #b, __FILE__, __LINE__); } while(0)
#define EXPECT_NEAR(a,b,eps) do { if(!(std::fabs((a)-(b)) <= (eps))) gtest::ReportFailure("fabs(" #a "-" #b ") <= " #eps, __FILE__, __LINE__); } while(0)

#endif // GTEST_LITE_H
