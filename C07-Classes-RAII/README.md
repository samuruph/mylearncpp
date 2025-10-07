# Chapter 07 — Classes & RAII

## Overview
Encapsulate state and behavior; tie resource lifetime to object lifetime.

## Learning outcomes

- Write a move-only RAII wrapper that closes in the destructor.
- Decide whether to delete copy operations or implement the rule of five.
- Explain why destructors shouldn’t throw.

## Sections

### s01 — Move-only FILE* wrapper
Implement `File` that opens in the ctor and closes in the dtor. Delete copy, implement move ctor/assign. Use it to copy a file using buffered reads/writes.
**Build/Run**
```bash
cmake --build build --target ch07_raii
./build/ch07_raii
```
**Exercises**
- Add an `open` helper that reopens safely (strong exception guarantee).
- Add a small unit-test main that exercises copy prohibition.

## Pitfalls & pro-tips
- Forgetting to release resources in all paths; RAII avoids leaks even on exceptions.
- Throwing from destructors (leads to terminate during stack unwinding).

## LearnCpp references (anchor lessons)
- 14.x — OOP overview and intro to classes.
