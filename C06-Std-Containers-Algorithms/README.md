# Chapter 06 — Standard Containers & Algorithms

## Overview
Daily-driver containers and algorithms (and why they beat hand-rolled loops).

## Learning outcomes

- Pick `std::vector` by default; know when `std::array` or maps fit better.
- Use algorithms like `sort`, `find_if`, `transform` with iterators or ranges.
- Understand iterator invalidation rules for containers.

## Sections

### s01 — Sorting and indexing records
Maintain `std::vector<Rec>`; `std::sort` by score (desc); build `unordered_map<int,std::string>` for id→name lookup; query with `find_if`.
**Build/Run**
```bash
cmake --build build --target ch06_stl
./build/ch06_stl
```
**Exercises**
- Add stable sorting by name for ties.
- Replace `unordered_map` with `map` and compare behavior.

## Pitfalls & pro-tips
- Assuming iterators remain valid after `vector` `push_back`/`insert` (they may not).
- O(n) linear searches where a map lookup is appropriate.

## LearnCpp references (anchor lessons)
- Arrays/containers lessons; algorithm overviews and complexity notes.
