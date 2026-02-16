# Documentation (`docs/`)

This directory contains all project documentation.

The goal of this folder is to centralise design decisions, architecture notes, and long-term planning separate from the source code.

Documentation should evolve alongside the project.

---

## Structure

Typical files in this directory:

- `design.md`  
  Architecture overview, component relationships, design philosophy, constraints.

- `roadmap.md`  
  Planned features, milestones, and future direction.

- `architecture.md`  
  Detailed breakdown of modules and internal structure (optional).

- `decisions.md`  
  Record of important design decisions and the reasoning behind them.

- `api.md`  
  Public interface documentation (if applicable).

Additional documents may include:

- performance notes
- benchmarking results
- build pipeline documentation
- deployment instructions
- diagrams (SVG, PNG, etc.)

---

## Philosophy

Documentation should:

- Explain *why*, not just *what*
- Capture architectural intent
- Prevent repeated design debates
- Help future maintainers understand context

Avoid duplicating comments already present in source code.

---

## Guidelines

- Keep documents concise but precise.
- Prefer markdown for portability.
- Diagrams should be version controlled.
- If a design decision changes, update the documentation.

---

## When to Document

You should update `docs/` when:

- A new subsystem is introduced
- The build system changes significantly
- Public APIs change
- Architectural direction shifts
- A non-obvious decision is made

---

## Not Included Here

This directory should not contain:

- Generated documentation
- Build artefacts
- Temporary notes or scratch files

Generated documentation (if any) should live in a separate output directory.