# Chapter 14 — CMake Project

## Overview
Introduce targets, per-target warnings, and CTest so projects can scale cleanly.

## Learning outcomes

- Declare C++ standard once and enforce per-target warnings.
- Use `target_link_libraries`, `target_include_directories`, and CTest.
- Understand out-of-source builds and generator choices (Ninja/Make/IDE).

## Sections

### s01 — Tiny app target
A single target with strict warnings is already production-grade for small tools. Extend by adding a library target and linking it into the app.
**Build/Run**
```bash
cmake --build build --target ch14_cmake
./build/ch14_cmake
```
**Exercises**
- Add `mylib` and link it.
- Add `ctest` invocation to CI later.

## Pitfalls & pro-tips
- Global compiler options instead of target-scoped options (harder to maintain).

## LearnCpp references (anchor lessons)
- CMake tutorial (official).
