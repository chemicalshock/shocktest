# Source Tree (`src/`)

This directory contains all source code and test code for the project.

## Layout

- `bin/`  
  Entry points into the application or library.  
  Typically contains `main.cpp` or thin integration layers.

- `inc/`  
  Header files (`.h`, `.hpp`).  
  Public interfaces and internal headers live here.

- `lib/`  
  Implementation source files (`.cpp`, `.c`).  
  Core logic should live here rather than in `bin/`.

- `bld/`  
  Intermediate build artefacts for main targets.  
  Contains object files and static libraries only.  
  **Does not contain final executables.**

## Tests

Tests are structured by scope:

- `tst/ut/`  
  Unit tests (small, isolated, fast).

- `tst/sy/`  
  System tests (integration-level, broader coverage).

- `tst/bld/`  
  Intermediate build artefacts for test targets  
  (objects, test binaries, temporary outputs).

## Final Output

Final build artefacts (executables, shared libraries, packages) are placed in:

## Include Order

In C++ code files, include headers in this order:

```cpp
// own header
#include "myfile.hpp"

// system
#include <string>

// internal
#include "another_file.hpp"

// external
#include "dep1/somefile.hpp"
```
