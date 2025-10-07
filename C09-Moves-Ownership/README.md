# Chapter 09 — Moves & Ownership

## Overview
Prefer value semantics with cheap moves; apply `std::move` deliberately when transferring.

## Learning outcomes

- Explain NRVO and when copies are elided.
- Use `std::move` to transfer resources into containers or return values.
- Know when to accept by value vs `const&` for efficiency.

## Sections

### s01 — Moving big strings
Return a large string by value and push it into a vector. Inspect whether it’s moved vs copied (tooling/diagnostics).
**Build/Run**
```bash
cmake --build build --target ch09_moves
./build/ch09_moves
```
**Exercises**
- Compare `emplace_back` vs `push_back` for construction in-place.
- Add a trivial trace type to log move/copy operations.

## Pitfalls & pro-tips
- Overusing `std::move` on variables you still need (turns them into unspecified but valid states).

## LearnCpp references (anchor lessons)
- Move semantics lessons and value category overviews.
