#include "shockmock.hpp"
#include "shocktest.hpp"

int real_impl(int x) {
    return x;
}

int fake_impl_1(int x) {
    return x + 1;
}

int fake_impl_2(int x) {
    return x + 2;
}

using UnaryFn = int(*)(int);
SHOCKMOCK_DECLARE_MOCK(calc, UnaryFn, real_impl);

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

SHOCKTEST_CASE(ExpectEqEvaluatesOnce) {
    int v = 0;
    EXPECT_EQ(++v, 1);
    EXPECT_EQ(v, 1);
}
