# Chapter 03 — I/O and Formatting

## Overview
Console I/O with iostreams and the C++20 `<format>` facility for type-safe formatting.

## Learning outcomes

- Read text safely with `std::getline` and numeric types with `operator>>`.
- Use `<format>` when available; fall back to stream manipulators otherwise.
- Understand buffering and newline vs flush.

## Sections

### s01 — Prompt, read, and format
Ask for name and age, then print with `std::format("Hi {}, age {}", name, age)`; if `<format>` isn’t available, print with iostreams.
**Build/Run**
```bash
cmake --build build --target ch03_io
./build/ch03_io
```
**Exercises**
- Print aligned columns using `<format>`’s width specifiers.
- Experiment with locales and numeric formatting.

## Pitfalls & pro-tips
- Mixing `std::getline` and `operator>>` without consuming the trailing newline.
- Assuming `<format>` exists on old libstdc++/libc++: check toolchain.

## LearnCpp references (anchor lessons)
- Chapter 1 & 3 I/O lessons (cin/cout basics).
