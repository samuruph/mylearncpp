# Chapter 11 — Lambdas & Ranges

## Overview
Use lambdas as inline function objects; compose transformations with ranges pipelines.

## Learning outcomes

- Choose capture modes safely (`[=]`, `[&]`, init-capture).
- Readability-first: prefer algorithm + lambda to ad-hoc loops.
- Use ranges `views::filter/transform` and projections.

## Sections

### s01 — Odds then squares (pipeline)
Compose a pipeline that filters odd numbers and squares them. Iterate the view without allocating a new container.
**Build/Run**
```bash
cmake --build build --target ch11_ranges
./build/ch11_ranges
```
**Exercises**
- Add a `take(5)` view and print only the first 5 results.
- Replace the lambda with a stateless function object and compare.

## Pitfalls & pro-tips
- Dangling references captured by `[&]` when lambdas outlive scope.
- Accidentally materializing heavy intermediate containers.

## LearnCpp references (anchor lessons)
- Lambda basics; capture lists; ranges introduction and view adaptors.
