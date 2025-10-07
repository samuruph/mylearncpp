# Chapter 15 — Testing (CTest + tiny runner)

## Overview
Add fast feedback with a header-only assertion runner and CTest integration. Swap in Catch2/Doctest when desired.

## Learning outcomes

- Write test executables that return non-zero on failure.
- Register tests with `add_test()` and run via `ctest`.
- Evolve to a full framework later without changing habits.

## Sections

### s01 — One check to rule them all
A minimal test file using a tiny runner. The pattern scales: add more TEST_CASEs or move to Catch2 with minimal changes.
**Build/Run**
```bash
cmake --build build --target ch15_tests
./build/ch15_tests
```
**Exercises**
- Add edge-case tests (overflow, empty inputs).
- Have one chapter exercise guarded by tests.

## Pitfalls & pro-tips
- Printing without assertions: tests should fail when behavior is wrong.

## LearnCpp references (anchor lessons)
- CTest docs; introductory testing patterns.
