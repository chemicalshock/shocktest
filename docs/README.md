# Documentation (`docs/`)

This directory contains longer-form project documentation that does not belong in code comments.

## Current State

Right now, the repository is focused on the core headers and unit tests:

- `src/inc/shocktest.hpp`
- `src/inc/shockmock.hpp`
- `src/tst/ut/*`

There are no additional design notes in `docs/` yet.

## What Belongs Here

Add docs here when project complexity grows, for example:

- architecture notes
- API usage guides
- release/versioning notes
- testing strategy and conventions
- design decisions and rationale

## Suggested Next Docs

If you want to expand documentation, start with:

- `api.md` for macro/reference usage (`SHOCKTEST_CASE`, `EXPECT_*`, `SHOCKMOCK_*`)
- `design.md` for framework philosophy and expected-failure model (`GOODWEATHER` vs `BADWEATHER`)
- `roadmap.md` for planned features and known limitations

## Guidelines

- Keep docs version-controlled and close to implementation changes.
- Prefer concise Markdown with copy-pasteable commands.
- Document behavior and tradeoffs, not just file locations.
