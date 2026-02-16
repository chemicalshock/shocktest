// -------------------------------------------------------------
//
//!\file test_shocktest_behavior.cpp
//!\brief Unit tests for shocktest GOODWEATHER/BADWEATHER execution semantics.
//!\author Colin J.D. Stewart
//
// -------------------------------------------------------------
//
//            Copyright (c) 2026. Colin J.D. Stewart
//                   All rights reserved
//
// -------------------------------------------------------------

// let shocktest know we are providing our own main function
#define SHOCKTEST_CUSTOM_MAIN

// shocktest
#include "shocktest.hpp"

// system
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace {

//
//!\brief Runs all registered tests while suppressing console output.
//
int run_all_quiet() {
    std::ostringstream sink;
    std::streambuf* old_buf = std::cout.rdbuf(sink.rdbuf());
    const int rc = shocktest::run_all();
    std::cout.rdbuf(old_buf);
    return rc;
}

//
//!\brief Verifies that a GOODWEATHER test that passes returns success.
//
int verify_goodweather_passes() {
    shocktest::registry().clear();
    shocktest::register_test("goodweather_pass", [] { EXPECT_TRUE(true); }, false);
    return shocktest::run_all();
}

//
//!\brief Verifies that a BADWEATHER test that throws is treated as success.
//
int verify_badweather_throw_passes() {
    shocktest::registry().clear();
    shocktest::register_test(
        "badweather_throw_pass",
        [] { throw std::runtime_error("expected failure"); },
        true
    );
    return shocktest::run_all();
}

//
//!\brief Verifies that a BADWEATHER test that does not throw is treated as failure.
//
int verify_badweather_no_throw_fails() {
    shocktest::registry().clear();
    shocktest::register_test("badweather_no_throw_fail", [] {}, true);
    return run_all_quiet();
}

//
//!\brief Verifies that a GOODWEATHER test that throws is treated as failure.
//
int verify_goodweather_throw_fails() {
    shocktest::registry().clear();
    shocktest::register_test(
        "goodweather_throw_fail",
        [] { throw std::runtime_error("unexpected failure"); },
        false
    );
    return run_all_quiet();
}

} // namespace

//
//!\brief Custom main used to validate multiple execution-semantics scenarios.
//
int main() {
    if (verify_goodweather_passes() != 0) {
        std::cerr << "Expected GOODWEATHER pass to return 0\n";
        return 1;
    }
    if (verify_badweather_throw_passes() != 0) {
        std::cerr << "Expected BADWEATHER throw to return 0\n";
        return 1;
    }
    if (verify_badweather_no_throw_fails() == 0) {
        std::cerr << "Expected BADWEATHER no-throw to return non-zero\n";
        return 1;
    }
    if (verify_goodweather_throw_fails() == 0) {
        std::cerr << "Expected GOODWEATHER throw to return non-zero\n";
        return 1;
    }
    return 0;
}
