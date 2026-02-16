# Source Tree (`src/`)

`src/` contains the framework headers and tests for this repository.

## Current Layout

- `inc/`
  - `shocktest.hpp`: header-only test framework
  - `shockmock.hpp`: function-pointer mocking helpers
- `tst/ut/`
  - unit tests for framework behavior and mocking
  - dedicated UT build system (`makefile` + `makefile.shocktest.mk`)
  - binaries output to `src/tst/ut/bld/`
- `tst/sy/`
  - reserved for system/integration tests (currently placeholder only)
- `bin/`, `lib/`
  - present for project-template compatibility
  - currently empty in this repository
- `bld/`
  - intermediate objects/dependency files from top-level builds

## Build Notes

- Unit tests are self-contained under `src/tst/ut/` and run via:

```sh
make ut
```

- Top-level `make` expects sources in `src/bin/` and/or `src/lib/`. Since those directories are currently empty, executable linking is not yet meaningful.

## Include Guidance

Recommended include grouping in C++ files:

```cpp
// own header first
#include "myfile.hpp"

// standard library
#include <string>

// project headers
#include "shocktest.hpp"

// dependency headers
#include "dep_name/header.hpp"
```
