# Dependencies (`dep/`)

This directory contains external dependencies used by the project.

The `dep/` folder is intentionally flexible. It may contain:

- Git submodules
- Symlinks to locally cloned repositories
- Vendored third-party code
- Header-only libraries
- Internal shared components reused across projects

## Philosophy

The main repository should remain focused on its own source code.

External components should live here to:

- Keep ownership boundaries clear
- Avoid mixing third-party code with project code
- Allow version pinning per project
- Enable clean upgrades or swaps

## Recommended Approaches

### 1. Git Submodules (Reproducible)

Use submodules when you want the repository to fully define dependency versions.

Example:

git submodule add <repo-url> dep/<name>

Pros:
- Fully reproducible
- Version pinned
- Easy CI integration

Cons:
- Slightly more workflow overhead


### 2. Symlinks (Local Development)

Use symlinks when developing multiple repositories together.

Example:

ln -s ~/projects/common-lib dep/common-lib

Pros:
- Rapid local iteration
- No duplication
- Clean separation of repositories

Cons:
- Not portable unless the target exists


### 3. Vendoring

For small or stable libraries, you may copy source directly into `dep/`.

Pros:
- Simple
- No external fetch required

Cons:
- Manual update process


## Build Expectations

The build system should:

- Include headers from `dep/`
- Link against static or shared libraries located in `dep/`
- Not assume a specific dependency strategy

Each dependency should document its own build requirements.

## Important

This directory should not contain:

- Project source code
- Build artefacts
- Temporary files

Build output belongs in:

- `src/bld/` (intermediate)
- `/bld/` (final artefacts)