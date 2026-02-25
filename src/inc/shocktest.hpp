// -------------------------------------------------------------
//
// !\file shocktest.hpp
// !\brief Lightweight unit testing framework (header-only)
// !\author Colin J.D. Stewart
//
// -------------------------------------------------------------
//
//          Copyright (c) 2025-2026. Colin J.D. Stewart
//                   All rights reserved
//
// -------------------------------------------------------------

#ifndef SHOCKTEST_HPP
#define SHOCKTEST_HPP

#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <sstream>
#include <chrono>
#include <stdexcept>

#define SHOCKTEST_VERSION "0.2.0"

namespace shocktest
{

//
// !\brief Represents a single test case.
//
struct TestCase {
    std::string name;
    std::function<void()> func;
    bool expect_fail;  // true if the test is expected to fail ("bad weather")
};

//
// !\brief Returns the registry of test cases.
//
inline std::vector<TestCase>& registry() {
    static std::vector<TestCase> tests;
    return tests;
}

//
// !\brief Registers a test with an expected failure flag.
//
inline void register_test(const std::string& name, std::function<void()> fn, bool expect_fail = false) {
    registry().push_back({ name, fn, expect_fail });
}

//
// !\brief Runs all tests and prints a weather report.
//
inline int run_all() {
    using namespace std::chrono;

    // Fixed-width labels for alignment.
    static constexpr const char* LABEL_RUN  = "\033[32m[ RUN      ]\033[0m";   // Always green.
    static constexpr const char* LABEL_PASS = "\033[32m[       OK ]\033[0m";   // Green when pass.
    static constexpr const char* LABEL_FAIL = "\033[31m[  FAILED  ]\033[0m";    // Red when fail.
    static constexpr const char* LABEL_HEADER = "\033[32m[==========]\033[0m";

    int failures = 0;
    int total = static_cast<int>(registry().size());
    long long total_time_ms = 0;

    std::cout << LABEL_HEADER << " Running " << total << " tests\n";

    for (const auto& test : registry()) {
        // Simply show BADWEATHER if flagged, otherwise GOODWEATHER.
        std::string weatherLabel = test.expect_fail ? "\033[31mBADWEATHER\033[0m " : "\033[32mGOODWEATHER\033[0m ";

        auto start = steady_clock::now();
        std::cout << LABEL_RUN << " " << weatherLabel << test.name << " ... " << std::endl << std::flush;
        
        try {
            test.func();
            auto end = steady_clock::now();
            auto dt = duration_cast<milliseconds>(end - start).count();
            total_time_ms += dt;
            if (test.expect_fail) {
                std::cout << "\n" << LABEL_FAIL << " " << weatherLabel << test.name
                          << " - expected failure but none was thrown (" << dt << " ms)" << std::endl;
                ++failures;
            } else {
                std::cout << LABEL_PASS << " " << weatherLabel << test.name << " (" << dt << " ms)" << std::endl;
            }
        } catch (const std::exception& e) {
            auto end = steady_clock::now();
            auto dt = duration_cast<milliseconds>(end - start).count();
            total_time_ms += dt;
            if (test.expect_fail) {
                std::cout << LABEL_PASS << " " << weatherLabel << test.name << " (" << dt << " ms) - " << e.what() << std::endl;
            } else {
                std::cout << "\n" << LABEL_FAIL << " " << weatherLabel << test.name
                          << " - " << e.what() << " (" << dt << " ms)" << std::endl;
                ++failures;
            }
        } catch (...) {
            auto end = steady_clock::now();
            auto dt = duration_cast<milliseconds>(end - start).count();
            total_time_ms += dt;
            if (test.expect_fail) {
                std::cout << LABEL_PASS << " " << weatherLabel << test.name << " (" << dt << " ms) - unknown error" << std::endl;
            } else {
                std::cout << "\n" << LABEL_FAIL << " " << weatherLabel << test.name
                          << " - unknown error (" << dt << " ms)" << std::endl;
                ++failures;
            }
        }
    }

    std::cout << LABEL_HEADER << " " << total << " tests ran.\n";
    if (failures == 0) {
        std::cout << "\033[32m[  PASSED  ]\033[0m " << total << " test(s) (" << total_time_ms << " ms total)" << std::endl;
    } else {
        std::cout << "\033[31m[  FAILED  ]\033[0m " << failures << " test(s), out of " << total << " (" << total_time_ms << " ms total)" << std::endl;
    }
    return failures;
}

//
//!\brief Captures output written to a standard stream while executing fn.
//
template <typename Fn>
inline std::string capture_stream(std::ostream& stream, Fn&& fn) {
    std::ostringstream sink;
    std::streambuf* old_buf = stream.rdbuf(sink.rdbuf());
    try {
        fn();
    } catch (...) {
        stream.rdbuf(old_buf);
        throw;
    }
    stream.rdbuf(old_buf);
    return sink.str();
}

//
//!\brief Verifies captured output from a named stream matches expected text.
//
inline void expect_stream_eq(
    const char* stream_name,
    const std::string& actual,
    const std::string& expected
) {
    if (actual != expected) {
        std::ostringstream oss;
        oss << stream_name << " mismatch. Expected: \"" << expected
            << "\", got: \"" << actual << "\"";
        throw std::runtime_error(oss.str());
    }
}

// --- Macros ---

//
// !\brief SHOCKTEST_CASE registers a test expected to pass (good weather).
//
#define SHOCKTEST_GOODWEATHER(name) \
    static void test_##name(); \
    struct test_##name##_reg { \
        test_##name##_reg() { shocktest::register_test(#name, test_##name, false); } \
    }; \
    static test_##name##_reg reg_##name; \
    static void test_##name()

//        
// !\brief An alias for clarity—same as SHOCKTEST_CASE.
//
#define SHOCKTEST_CASE(name) SHOCKTEST_GOODWEATHER(name)

//
// !\brief SHOCKTEST_BADWEATHER registers a test expected to fail (bad weather).
//
#define SHOCKTEST_BADWEATHER(name) \
    static void test_##name(); \
    struct test_##name##_reg { \
        test_##name##_reg() { shocktest::register_test(#name, test_##name, true); } \
    }; \
    static test_##name##_reg reg_##name; \
    static void test_##name()

//
// !\brief expect expression is true
//
#define EXPECT_TRUE(x) \
    do { \
        if (!(x)) throw std::runtime_error("EXPECT_TRUE failed: " #x); \
    } while(0)        

//
// !\brief expect expression is false
//    
#define EXPECT_FALSE(x) \
    do { \
        if ((x)) { \
            std::ostringstream oss; \
            oss << "EXPECT_FALSE failed: " #x " evaluated to true"; \
            throw std::runtime_error(oss.str()); \
        } \
    } while(0)


//
// !\brief expect a != b
//    
#define EXPECT_NE(a, b) \
    do { \
        if ((a) == (b)) { \
            std::ostringstream oss; \
            oss << "EXPECT_EQ failed: " #a " == " #b " (" << (a) << " vs " << (b) << ")"; \
            throw std::runtime_error(oss.str()); \
        } \
    } while(0)    

//
// !\brief expect a == b
//    
#define EXPECT_EQ(a, b) \
    do { \
        if ((a) != (b)) { \
            std::ostringstream oss; \
            oss << "EXPECT_EQ failed: " #a " != " #b " (" << (a) << " vs " << (b) << ")"; \
            throw std::runtime_error(oss.str()); \
        } \
    } while(0)


//
// !\brief expect a >= b
//    
#define EXPECT_GE(a, b) \
    do { \
        if (!((a) >= (b))) { \
            std::ostringstream oss; \
            oss << "EXPECT_GE failed: " #a " < " #b " (" << (a) << " vs " << (b) << ")"; \
            throw std::runtime_error(oss.str()); \
        } \
    } while(0)

//
// !\brief expect a >= b
//    
#define EXPECT_GT(a, b) \
    do { \
        if (!((a) > (b))) { \
            std::ostringstream _oss; \
            _oss << "EXPECT_GT failed: " #a " is not greater than " #b " (" << (a) << " vs " << (b) << ")"; \
            throw std::runtime_error(_oss.str()); \
        } \
    } while(0)


//
// !\brief expect expression does not cause an exception
//    
#define EXPECT_NO_THROW(stmt)                                                    \
    do {                                                                         \
        try { stmt; }                                                            \
        catch (const std::exception& ex) {                                       \
            throw std::runtime_error("Unexpected exception thrown: " + std::string(ex.what()));       \
        }                                                                        \
        catch (...) {                                                            \
            throw std::runtime_error("Unexpected unknown exception thrown"); \
        }                                                                        \
    } while (0)    

#define EXPECT_THROW(stmt)                                    \
    do {                                                      \
        bool thrown = false;                                  \
        try {                                                 \
            stmt;                                             \
        } catch (...) {                                       \
            thrown = true;                                    \
        }                                                     \
        if (!thrown) {                                        \
            throw std::runtime_error("Expected exception but none was thrown.");   \
        }                                                     \
    } while (0)


#define EXPECT_THROW_MSG(stmt, expected_msg)                                     \
    do {                                                                         \
        bool thrown = false;                                                     \
        try { stmt; }                                                            \
        catch (const std::exception& ex) {                                       \
            thrown = true;                                                       \
            if (std::string(ex.what()).find(expected_msg) == std::string::npos) {\
                throw std::runtime_error("Exception message mismatch. Got: \"" + std::string(ex.what()) + "\", expected to contain: \"" + expected_msg + "\"");      \
            }                                                                    \
        }                                                                        \
        catch (...) { thrown = true; }                                           \
        if (!thrown)                                                             \
            throw std::runtime_error("Expected exception but none was thrown"); \
    } while (0)



//
//!\brief expects std::cout output produced by stmt to match expected
//
#define EXPECT_STDCOUT(stmt, expected)                                           \
    do {                                                                         \
        const std::string _shocktest_actual =                                    \
            shocktest::capture_stream(std::cout, [&]() { stmt; });               \
        shocktest::expect_stream_eq("std::cout", _shocktest_actual, (expected)); \
    } while (0)

//
//!\brief expects std::cerr output produced by stmt to match expected
//
#define EXPECT_STDCERR(stmt, expected)                                           \
    do {                                                                         \
        const std::string _shocktest_actual =                                    \
            shocktest::capture_stream(std::cerr, [&]() { stmt; });               \
        shocktest::expect_stream_eq("std::cerr", _shocktest_actual, (expected)); \
    } while (0)


// ASSERT_TRUE: Terminates the current test if the condition is false.
#define ASSERT_TRUE(x) \
    do { \
        if (!(x)) { \
            std::ostringstream oss; \
            oss << "ASSERT_TRUE failed: " #x; \
            throw std::runtime_error(oss.str()); \
        } \
    } while(0)

// ASSERT_EQ: Terminates the test if a != b.
#define ASSERT_EQ(a, b) \
    do { \
        if ((a) != (b)) { \
            std::ostringstream oss; \
            oss << "ASSERT_EQ failed: " #a " != " #b " (" << (a) << " vs " << (b) << ")"; \
            throw std::runtime_error(oss.str()); \
        } \
    } while(0)

// ASSERT_GT: Terminates the test if a is not greater than b.
#define ASSERT_GT(a, b) \
    do { \
        if (!((a) > (b))) { \
            std::ostringstream oss; \
            oss << "ASSERT_GT failed: " #a " <= " #b " (" << (a) << " vs " << (b) << ")"; \
            throw std::runtime_error(oss.str()); \
        } \
    } while(0)


} // namespace shocktest

#ifndef SHOCKTEST_CUSTOM_MAIN
int main() {
    return shocktest::run_all();
}
#endif

#endif // SHOCKTEST_HPP
