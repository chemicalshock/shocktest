#define SHOCKTEST_CUSTOM_MAIN
#include "shocktest.hpp"

#include <iostream>
#include <stdexcept>

namespace {

int verify_goodweather_passes() {
    shocktest::registry().clear();
    shocktest::register_test("goodweather_pass", [] { EXPECT_TRUE(true); }, false);
    return shocktest::run_all();
}

int verify_badweather_throw_passes() {
    shocktest::registry().clear();
    shocktest::register_test(
        "badweather_throw_pass",
        [] { throw std::runtime_error("expected failure"); },
        true
    );
    return shocktest::run_all();
}

int verify_badweather_no_throw_fails() {
    shocktest::registry().clear();
    shocktest::register_test("badweather_no_throw_fail", [] {}, true);
    return shocktest::run_all();
}

int verify_goodweather_throw_fails() {
    shocktest::registry().clear();
    shocktest::register_test(
        "goodweather_throw_fail",
        [] { throw std::runtime_error("unexpected failure"); },
        false
    );
    return shocktest::run_all();
}

} // namespace

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
