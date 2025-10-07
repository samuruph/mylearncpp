# Chapter 05 — Pointers & References

## Overview
Addresses, dereferencing, member access via `->`, and when a reference is preferable.

## Learning outcomes

- Explain `&` (address-of) and `*` (dereference) precisely.
- Choose references for must-exist aliases; use pointers for reseating/null.
- Access struct/class members via pointers with `->`.

## Sections

### s01 — Pointer vs reference
Print `&p` (address of pointer), `p` (address stored), `*p` (value at address), and `r` (reference alias). Add a small struct and access a field via `ps->x`.
**Build/Run**
```bash
cmake --build build --target ch05_ptrs
./build/ch05_ptrs
```
**Exercises**
- Write `swap(T&,T&)` using references.
- Write `find(T*, size_t, const T&) -> T*` returning `nullptr` when not found.

## Pitfalls & pro-tips
- Dereferencing null/invalid pointers (UB).
- Storing the address of a temporary that goes out of scope.

## LearnCpp references (anchor lessons)
- 12.7 — Introduction to pointers.
- 13.x — Member selection operators (., ->).
- 20.1 — Function pointers (later).
