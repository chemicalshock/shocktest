# Shocktest

`shocktest` is a lightweight, header-only C++ test framework with a weather-themed test model:

- `GOODWEATHER` tests are expected to pass.
- `BADWEATHER` tests are expected to fail (throw).

The repository also includes `shockmock`, a small RAII-based function-pointer mocking helper intended for unit tests.

## Current Scope

This repo currently provides:

- `src/inc/shocktest.hpp` (framework + assertions + optional auto-main)
- `src/inc/shockmock.hpp` (mockable function-pointer helpers)
- Unit tests under `src/tst/ut/`

`SHOCKTEST_VERSION` in `src/inc/shocktest.hpp` is currently `0.2.0`.

## Repository Layout

- `src/inc/` public headers (`shocktest.hpp`, `shockmock.hpp`)
- `src/tst/ut/` unit tests and UT makefiles
- `src/tst/sy/` placeholder for system tests
- `docs/` project docs (currently this README only)
- `dep/` external dependency area
- `bld/` final top-level build outputs
- `src/bld/` intermediate main build outputs

## Requirements

- `g++` (or another C++20-capable compiler)
- `make`
- POSIX shell environment

## Build And Test

### Unit tests (recommended)

```sh
make ut
```

This builds and runs:

- `TEST_SHOCKTEST_BEHAVIOR_UT`
- `TEST_SHOCKMOCK_UT`
- `TEST_CUSTOM_MAIN_UT`

### Top-level project build

```sh
make
```

The root makefile is template-capable (exe/static/shared), but this repository currently has no sources in `src/bin/` or `src/lib/`. As a result, `make` may fail for executable linking until app/library sources are added.

## Quick Usage

Minimal example:

```cpp
#include "shocktest.hpp"

SHOCKTEST_CASE(MyFirstTest) {
    EXPECT_EQ(2 + 2, 4);
}
```

Compile a test file directly:

```sh
g++ -std=c++20 -I./src/inc my_test.cpp -o my_test
./my_test
```

If you want your own `main()`, define `SHOCKTEST_CUSTOM_MAIN` before including `shocktest.hpp`, then call `shocktest::run_all()`.

## Assertion And Utility Highlights

`shocktest.hpp` includes:

- Assertions: `EXPECT_*`, `ASSERT_*`
- Exception checks: `EXPECT_THROW`, `EXPECT_NO_THROW`, `EXPECT_THROW_MSG`
- Stream capture checks: `EXPECT_STDCOUT`, `EXPECT_STDCERR`

## Related Docs

- `src/README.md`
- `docs/README.md`
- `dep/README.md`
