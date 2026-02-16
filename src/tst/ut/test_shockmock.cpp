// -------------------------------------------------------------
//
//!\file test_shockmock.cpp
//!\brief Unit tests for shockmock integration with shocktest assertions.
//!\author Colin J.D. Stewart
//
// -------------------------------------------------------------
//
//            Copyright (c) 2026. Colin J.D. Stewart
//                   All rights reserved
//
// -------------------------------------------------------------

// shocktest
#include "shocktest.hpp"

// shockmock
#include "shockmock.hpp"

//
//!\brief Real implementation used as default for the mockable function pointer.
//
int real_impl(int x) {
    return x;
}

//
//!\brief First mock implementation used for override tests.
//
int fake_impl_1(int x) {
    return x + 1;
}

//
//!\brief Second mock implementation used for nested override tests.
//
int fake_impl_2(int x) {
    return x + 2;
}

using UnaryFn = int(*)(int);
SHOCKMOCK_DECLARE_MOCK(calc, UnaryFn, real_impl);

//
//!\brief Verifies mock override and automatic restoration through nested scopes.
//
SHOCKTEST_CASE(OverrideAndRestore) {
    EXPECT_EQ(SHOCKMOCK_CALL(calc, 10), 10);

    {
        SHOCKMOCK_MOCK_OVERRIDE(calc, fake_impl_1);
        EXPECT_EQ(SHOCKMOCK_CALL(calc, 10), 11);

        {
            SHOCKMOCK_MOCK_OVERRIDE(calc, fake_impl_2);
            EXPECT_EQ(SHOCKMOCK_CALL(calc, 10), 12);
        }

        EXPECT_EQ(SHOCKMOCK_CALL(calc, 10), 11);
    }

    EXPECT_EQ(SHOCKMOCK_CALL(calc, 10), 10);
}

//
//!\brief Verifies EXPECT_EQ evaluates side-effect expressions only once.
//
SHOCKTEST_CASE(ExpectEqEvaluatesOnce) {
    int v = 0;
    EXPECT_EQ(++v, 1);
    EXPECT_EQ(v, 1);
}
