#define SHOCKTEST_CUSTOM_MAIN
#include "shocktest.hpp"

SHOCKTEST_CASE(CustomMainModeWorks) {
    EXPECT_TRUE(true);
}

int main() {
    return shocktest::run_all();
}
