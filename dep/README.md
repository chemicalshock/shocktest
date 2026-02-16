# Dependencies (`dep/`)

This directory is where external dependencies should be placed.

## Current State

`dep/` is currently empty (no active third-party dependencies).

The project builds and runs unit tests using only:

- C++ standard library
- local headers in `src/inc/`

## How `dep/` Is Used By Build Scripts

- Root makefile scans `dep/*/src/inc` and adds include paths automatically.
- A dependency include map is generated under `src/bld/depinc/`.
- Unit-test makefile adds `-I$(ROOT_DIR)/dep` by default.

## Recommended Patterns

Use one of:

- git submodules (pinned/reproducible)
- vendored source
- local symlink during development

For any added dependency, include a short README in that dependency folder explaining:

- version/source
- required build flags
- update process

## Keep Out

Do not place build artefacts or temporary files in `dep/`.
