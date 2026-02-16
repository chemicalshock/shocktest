# <ProjectName>

Short one-paragraph description of what this project is and what problem it solves.

---

## Overview

This project follows a structured, modular C++ layout designed for:

- Clear separation of source and build artefacts
- Reusable components
- Clean dependency management
- Scalable test structure
- Long-term maintainability

The repository is suitable for both library-style and executable-style projects.

---

## Repository Structure

/bld Final build artefacts (executables, shared libraries)

/dep External dependencies
/docs Project documentation

/src
bin/ Entry points (e.g. main.cpp)
inc/ Header files
lib/ Implementation source files
bld/ Intermediate build artefacts (objects, static libs)

tst/
ut/ Unit tests
sy/ System tests
bld/ Test build artefacts


### Build Artefact Policy

- `src/bld/` and `src/tst/bld/` contain intermediate compilation output.
- `/bld` at the repository root contains final distributable artefacts.
- Build output is not committed to the repository.

---

## Requirements

- C++ compiler (C++17 or C++20 recommended)
- Make
- POSIX-compatible environment (Linux, macOS, WSL, etc.)

---

## Build

### Default build

make

### Release build

make MODE=release


### Run

./bld/<ProjectName>


---

## Testing

Unit tests:

make tests


System tests may require additional configuration depending on project scope.

---

## Dependencies

External components are located in `/dep`.

See:

dep/README.md


for dependency management strategy.

---

## Documentation

All architectural and design documentation lives in:

docs/


Start with:

docs/README.md


---

## Philosophy

This repository aims to:

- Keep implementation separate from interface
- Keep build artefacts separate from source
- Support both standalone and reusable component development
- Scale from small utilities to large modular systems

---

## Licence

See `LICENSE`.