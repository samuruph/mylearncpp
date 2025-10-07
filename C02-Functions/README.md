# Chapter 02 — Functions

## Overview
Function decomposition, declarations vs definitions, and practical parameter-passing heuristics.

## Learning outcomes

- Split declarations (headers) and definitions (sources).
- Choose value vs `const&` vs sink (by value / forwarding).
- Return values vs `void`.

## Sections

### s01 — Functions & headers
Implement `add`, `greet`, and `concat_take`. Observe how headers expose interfaces. Explain why `concat_take(std::string a)` is efficient when you’re going to make a copy anyway.
**Build/Run**
```bash
cmake --build build --target ch02_funcs
./build/ch02_funcs
```
**Exercises**
- Add `repeat(std::string s, int n)` and consider pass-by-value vs `const&`.
- Convert one function to a header-only inline and inspect ODR concerns.

## Pitfalls & pro-tips
- Declaring defaults in both header and source (defaults belong in declarations).
- Overusing `inline` across multiple TUs; understand ODR.

## LearnCpp references (anchor lessons)
- 2.1 — Introduction to functions.
- 2.2 — Function return values (value-returning).
- 2.3 — Void functions (non-value returning).
