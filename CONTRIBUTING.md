# Contributing to AndyCAD

AndyCAD is an ambitious project: a modern re-engineering of a legacy C++ CAD system, originally built on MFC, now evolving toward a clean, testable, long-lived architecture.

We welcome contributions—but only those that respect the project’s technical direction, standards, and discipline.

This document explains **how to contribute effectively**.

---

## Project Philosophy

AndyCAD is not a demo, a tutorial project, or a playground for experiments.

It is:

* A **real CAD system**
* Built for **longevity**
* Designed to evolve from **C++98/MFC roots toward modern C++**
* Opinionated about **architecture, correctness, and performance**

Contributions that add features at the cost of architectural clarity will be rejected.

Clarity wins. Always.

---

## Code of Conduct (Short Version)

* Be respectful and technical.
* Disagree with arguments, not people.
* No ego-driven refactors.
* No drive-by changes without context.

If you want to rewrite half the system, start with a design discussion.

---

## Getting Started

### 1. Fork and Clone

```bash
git clone https://github.com/segedeh/andycad.git
cd andycad
```

### 2. Build the Project

AndyCAD currently targets:

* Windows (primary)
* MFC-based UI
* MSVC toolchain

You are expected to:

* Build successfully before submitting anything
* Understand the existing architecture before modifying it

If you cannot build the project locally, do not submit a PR.

---

## Architecture Overview (Read Before Coding)

AndyCAD follows a **Document–View–Controller–Facade hybrid**:

* **App**
  Owns lifecycle and global services

* **Document**
  Holds the model state
  Owns a `Draw` object (the core façade)

* **View**
  Renders and forwards user interaction
  Should be thin

* **Draw (Facade)**
  Central access point for:

  * Geometry
  * Shapes
  * Transformations
  * Editing
  * Camera
  * Snapping

If your code bypasses `Draw` and reaches deep into internals, it is probably wrong.

---

## Contribution Types

We accept contributions in the following categories:

### Bug Fixes

* Must include a **clear reproduction**
* Must explain **why the bug happened**
* Minimal fix preferred over clever fix

### Refactoring

* Must preserve behavior
* Must improve:

  * Readability
  * Testability
  * Separation of concerns
* No “modern C++ just because” changes

### New Features

* Require prior discussion
* Must fit the architectural direction
* Must not introduce unnecessary dependencies

### Tooling / Build Improvements

* Highly welcome
* Especially around modernization and portability

---

## Coding Standards

### Language Level

* Current baseline: **C++17**
* C++20 allowed **only when justified**
* Do not use features just because they exist

Modern C++ is a tool, not a religion.

---

### Style Rules (Non-Negotiable)

* Prefer **explicit code** over clever abstractions
* Avoid deep inheritance trees
* Composition beats inheritance
* No macros unless absolutely necessary
* No hidden control flow

If the debugger becomes useless, the design is wrong.

---

### Memory Management

* Prefer RAII
* Raw pointers are allowed **when ownership is clear**
* `unique_ptr` over `shared_ptr`
* No silent ownership transfer

AndyCAD must remain debuggable.

---

### Error Handling

* No swallowing errors
* Assertions for programmer errors
* Graceful handling for runtime/user errors

---

## Tests

Testing is evolving but expected where reasonable.

* New logic should be testable
* Geometry/math code should be deterministic
* Avoid UI-driven logic where possible

If something cannot be tested, explain why.

---

## Commit Guidelines

Write commits that explain **why**, not just **what**.

**Good commit message:**

```
Fix incorrect snapping when grid is rotated

The snap calculation ignored the view transform,
causing offset errors when the grid was rotated.
```

**Bad commit message:**

```
Fix bug
```

---

## Pull Requests

Before submitting a PR:

* Code builds
* No unrelated formatting changes
* Commit history is clean
* PR description explains:

  * Problem
  * Solution
  * Trade-offs

Large PRs without discussion will be closed.

---

## Design Discussions

For non-trivial changes:

* Open an issue first
* Describe intent, not implementation
* Expect pushback—this is healthy

AndyCAD values **architectural coherence** over speed.

---

## What Will Be Rejected

Be clear about this:

* Blind framework rewrites
* “Let’s switch everything to X” proposals
* Feature dumps without design
* Changes that increase coupling
* Code that optimizes prematurely

AndyCAD is not chasing trends.

---

## Final Word

Contributing to AndyCAD means thinking like a **systems engineer**, not a feature factory.

If you care about:

* Software longevity
* Clean architecture
* Real engineering trade-offs

You are welcome here.

If not, that’s fine—this project is intentionally demanding.

Build things that last.
