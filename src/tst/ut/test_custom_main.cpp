// -------------------------------------------------------------
//
//!\file test_custom_main.cpp
//!\brief Test that custom main function works correctly with the shocktest framework.
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

//
//!\brief A simple test case to verify that the custom main function is used and that tests run correctly.
//
SHOCKTEST_CASE(CustomMainModeWorks) {
    EXPECT_TRUE(true);
}

//
//!\brief The custom main function
//
int main() {
    return shocktest::run_all();
}
