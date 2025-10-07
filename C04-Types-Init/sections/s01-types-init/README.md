# Chapter 04 — Types & Initialization

## Overview
Fundamental types, sizes, and safe initialization patterns.

## Learning outcomes

- Prefer `const` / `constexpr` for invariants and compile-time values.
- Use brace-initialization to avoid narrowing.
- Know when implicit conversions occur; use `static_cast` explicitly.

## Sections

### s01 — Types, const, and brace-init
Declare a handful of fundamental types; show a safe static reference (`static int n`) to avoid dangling. Discuss when to use `constexpr`.
**Build/Run**
```bash
cmake --build build --target ch04_types
./build/ch04_types
```
**Exercises**
- Add examples that would narrow with `=` and see brace-init catch them.
- Contrast `constexpr` and `const` with a computed value.

## Pitfalls & pro-tips
- Relying on implementation-defined sizes; check `sizeof`.
- Returning references to locals (dangling).

## LearnCpp references (anchor lessons)
- 4.1 — Fundamental data types.
- 4.3 — `sizeof` and object sizes.
- 4.12 — Conversions and casts.
