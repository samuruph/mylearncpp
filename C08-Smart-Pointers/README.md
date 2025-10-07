# Chapter 08 — Smart Pointers

## Overview
Express ownership explicitly: `unique_ptr` for sole ownership, `shared_ptr` when truly shared, `weak_ptr` to break cycles.

## Learning outcomes

- Refactor raw owning pointers to `std::unique_ptr`.
- Recognize when sharing is necessary and the costs of `shared_ptr`.
- Use `weak_ptr` to observe without extending lifetime.

## Sections

### s01 — Tree with unique_ptr children
Represent a simple tree; each node `owns` its children via `unique_ptr`. Build a small tree and traverse it iteratively.
**Build/Run**
```bash
cmake --build build --target ch08_smart
./build/ch08_smart
```
**Exercises**
- Add `emplace_child(int id)` convenience API.
- Try converting to `shared_ptr` and discuss cycle risks.

## Pitfalls & pro-tips
- Using `shared_ptr` by default (hidden ref-counting costs).
- Creating reference cycles (fix with `weak_ptr`).

## LearnCpp references (anchor lessons)
- Smart pointer introductions and ownership guidelines.
