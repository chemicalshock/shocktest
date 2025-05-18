# ShockTest

**ShockTest** is a minimal, header-only C++ unit testing framework built for developers who want fast, elegant, dependency-free test organisation.

Created by **Colin J.D. Stewart**  
Version: `0.1.0`

---

## 🚀 Features

- Header-only
- Simple macros: `TEST()`, `EXPECT_EQ()`, `EXPECT_TRUE()`
- Multiple test cases per file
- Coloured output (Windows/Linux)
- Fully cross-platform

---

## ✍️ Example

```cpp
#include "shocktest.hpp"

TEST(my_basic_case) {
    EXPECT_TRUE(1);
    EXPECT_EQ(2 + 2, 4);
}

int main() {
    return shocktest::run_all();
}
```

---

## 🔧 Integration

Place `shocktest/src/inc/shocktest.hpp` somewhere accessible and add to your include path.

In your project:

```cpp
#include "../../shocktest/src/inc/shocktest.hpp"
```

---

## 📄 License

Copyright (c) 2025  
**Colin J.D. Stewart** – All rights reserved.
