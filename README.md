# ShockTest

ShockTest is a lightweight C++ unit testing framework designed for fast development, minimal boilerplate, and intuitive output. It is ideal for embedding directly into small or medium-sized projects without complex dependencies.

## Features

- Single-header, dependency-free framework.
- Automatic `main()` inclusion (can be disabled).
- Simple macro-based test definitions.
- Optional `EXPECT_*` macros for expressive assertions.
- Coloured output with pass/fail status.
- Support for exception-based tests using `EXPECT_THROW`.

## Quick Start

### Include the header

Place `shocktest.hpp` in your project (typically under `dep/shocktest/src/inc`) and include it in your test files:

```cpp
#include "shocktest.hpp"
```

If you're already defining `main()` yourself, define the following before inclusion:

```cpp
#define SHOCKTEST_CUSTOM_MAIN
```

### Define a test

```cpp
SHOCKTEST("Maths basics") {
    int a = 2 + 2;
    EXPECT_EQ(a, 4);
    EXPECT_NE(a, 5);
}
```

### Compile

Assuming you’re using `g++`:

```sh
g++ -std=c++17 -Ipath/to/shocktest test_file.cpp -o test_runner
```

Then run your tests:

```sh
./test_runner
```

## Exception Testing

```cpp
SHOCKTEST("Expect throw") {
    EXPECT_THROW(throw std::runtime_error("error"), std::runtime_error);
    EXPECT_THROW_MSG(throw std::logic_error("bad logic"), std::logic_error, "bad logic");
}
```

## Output Example

```
[✓] Maths basics
[✓] Expect throw

All tests passed (2/2).
```

## Custom Main

If you need to initialise something or wrap test execution, define your own main:

```cpp
#define SHOCKTEST_CUSTOM_MAIN
#include "shocktest.hpp"

int main() {
    std::cout << "Running custom test suite...\n";
    return shocktest::run_all_tests();
}
```

## Directory Layout Suggestion

```
project/
├── dep/
│   └── shocktest/
│       └── src/
│           └── inc/
│               └── shocktest.hpp
└── src/
    └── tst/
        └── test_nameofunit.cpp
```
