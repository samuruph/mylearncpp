# Chapter 10 — Templates & Concepts

## Overview
Generic programming basics and constraints for clearer intent and diagnostics.

## Learning outcomes

- Write function templates and understand type deduction.
- Add constraints with standard concepts like `std::integral`.
- Prefer constraints to legacy SFINAE for readability.

## Sections

### s01 — add(T,T) and inc(I)
Implement a simple adder function template and a constrained increment using `std::integral`. Discuss error messages with and without constraints.
**Build/Run**
```bash
cmake --build build --target ch10_tpl
./build/ch10_tpl
```
**Exercises**
- Implement `clamp(T lo, T x, T hi)` and constrain to totally-ordered types.
- Try a constrained lambda (C++20) for fun.

## Pitfalls & pro-tips
- Template definitions in .cpp without explicit instantiations (link errors).
- Over-constraining templates (unnecessarily restricting valid uses).

## LearnCpp references (anchor lessons)
- Template intros; class templates; concept overviews.
