# Chapter 12 — Error Handling

## Overview
Use `std::optional` for expected absence; use exceptions for exceptional, non-local failures; avoid throwing in destructors.

## Learning outcomes

- Return `std::optional<T>` when a result may legitimately be missing.
- Translate errors at module boundaries; catch once at the top level.
- Mark destructors `noexcept` (default) and keep them simple.

## Sections

### s01 — Parse-or-nullopt + throwing I/O
Implement `to_int(std::string_view)` using `std::from_chars` that returns `optional<int>`. Add a `read_lines_throw()` that throws on open failure and catch in `main`.
**Build/Run**
```bash
cmake --build build --target ch12_errors
./build/ch12_errors
```
**Exercises**
- Replace exceptions with an `expected<T,E>`-like struct and compare call sites.
- Add error codes and map them to messages.

## Pitfalls & pro-tips
- Using exceptions for routine control flow (use optional/expected).
- Throwing in destructors (especially during stack unwinding).

## LearnCpp references (anchor lessons)
- Error handling lessons and chapter summaries.
