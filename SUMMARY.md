# Modern C++ Master Guide (LearnCpp‑based)

> A comprehensive, practical reference that mirrors the flow of LearnCpp while pointing to modern best practices. Use it as a study path **and** a quick‑look handbook.

---

## 0) Setup & Mental Model

### Tooling checklist
- **Compiler**: GCC, Clang, or MSVC (any reasonably recent C++20 toolchain).
- **Editor/IDE**: VS Code / CLion / Visual Studio.
- **Build system**: **CMake** (learn the basics early).
- **Linters/analysis**: `clang-tidy`, compiler warnings `-Wall -Wextra -Wpedantic`.
- **Formatter**: `clang-format`.

### C++ mental model (short)
- **Strong static typing** with value semantics first.
- Objects have **storage duration**: automatic (stack), dynamic (heap), static.
- **References** alias an object; **pointers** hold an address.
- **RAII**: acquire in constructor, release in destructor.

---

## 1) Hello, C++

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, C++!\n";
}
```

Build & run (POSIX):
```bash
clang++ -std=c++20 -O2 -Wall -Wextra -pedantic hello.cpp && ./a.out
```

Tips
- Treat warnings as errors (`-Werror`) while learning.
- Step through `main()` with a debugger at least once.

---

## 2) The Absolute Basics

### Variables & initialization
- Prefer **`const`** and **`constexpr`**.
- Use **brace initialization** to guard against narrowing:
  ```cpp
  int n{42};         // ok
  double d{3.14};    // ok
  // int bad{3.14};  // error: narrowing
  ```

### Scope & lifetime
- Locals die at end of scope.
- Never return references/pointers to dead locals.
- Returning by value is cheap for standard types (copy elision, moves).

### Expressions & control flow
- `if/else`, `switch`, `for`, `while` work as expected.
- Prefer pre‑increment (`++i`) with iterators; same cost for ints.

---

## 3) Functions & Parameters

```cpp
int add(int a, int b) { return a + b; }

// For large types
std::string greet(const std::string& name) {
    return "Hello, " + name;
}
```

Parameter passing heuristics
- **Small trivially copyable** (int, double, small structs): pass **by value**.
- **Big objects** (std::string, std::vector): pass **`const&`** to read, **by value** if you need a copy anyway, **`T&&`** to sink (see §9).

Default arguments live in the declaration; avoid them in virtual interfaces.

---

## 4) I/O & Formatting

- **Streams**: `std::cout`, `std::cin`, `std::cerr`.
- **Formatting (C++20)**: `<format>` is typesafe and fast.

```cpp
#include <format>
#include <iostream>

int main() {
    std::cout << std::format("Pi ≈ {:.3f}\n", 3.1415926);
}
```

---

## 5) Pointers & References — a crisp cheat sheet

```cpp
int x = 42;
int& r = x;    // reference: must bind, cannot be reseated, non-null
int* p = &x;   // pointer: holds address, can be reseated or null

*r = 7;        // modifies x via r
p = nullptr;   // ok for pointers; references can’t be null
```

Printing addresses & values:
```cpp
int v = 10;
int* p = &v;
std::cout << "&p (address of pointer var) = " << &p << '\n';
std::cout << "p  (address stored)       = " << p  << '\n';
std::cout << "*p (value pointed to)     = " << *p << '\n';
```

Guidelines
- Avoid owning raw pointers in application code. Prefer `std::unique_ptr`.
- Use references to express *must‑exist* relationships.

---

## 6) Data Structures & `std::` Essentials

### Core containers (memorize these first)
- `std::vector<T>` – dynamic array (default choice).
- `std::array<T,N>` – fixed size on stack.
- `std::string` – UTF‑8 by convention in most projects.
- `std::unordered_map<K,V>` – hash map; `std::map<K,V>` – tree map (ordered).
- `std::optional<T>` – maybe‑a‑value (better than sentinel values).

### Algorithms (classic + ranges)
```cpp
#include <algorithm>
#include <vector>

std::vector<int> v{5,2,4,1,3};
std::sort(v.begin(), v.end());
```

Ranges (C++20):
```cpp
#include <ranges>
#include <vector>

auto odds_squared = v
  | std::views::filter([](int x){ return x % 2; })
  | std::views::transform([](int x){ return x*x; });
```

---

## 7) Classes, Structs & RAII

```cpp
#include <cstdio>

class File {
    std::FILE* f{};
public:
    explicit File(const char* path, const char* mode)
      : f(std::fopen(path, mode)) {}
    ~File() { if (f) std::fclose(f); }

    File(const File&) = delete;              // non-copyable
    File& operator=(const File&) = delete;

    File(File&& other) noexcept : f(other.f) { other.f = nullptr; }
    File& operator=(File&& other) noexcept {
        if (this != &other) {
            if (f) std::fclose(f);
            f = other.f; other.f = nullptr;
        }
        return *this;
    }
};
```

RAII tips
- If your type **owns** a resource, either:
  - Delete copy ops and implement moves, **or**
  - Define correct copy/move semantics (the *Rule of Five*).
- Don’t leak exceptions from destructors.

---

## 8) Smart Pointers & Ownership

```cpp
#include <memory>

auto p = std::make_unique<int>(42);   // sole ownership
auto q = std::move(p);                // transfer ownership

auto sp = std::make_shared<int>(7);   // shared ownership (use sparingly)
std::weak_ptr<int> wp = sp;           // observe without owning
```

Heuristics
- Default to `unique_ptr`.
- Reach for `shared_ptr` only when shared lifetime is truly required.
- Use `weak_ptr` to break reference cycles.

---

## 9) Value Semantics, Copy vs Move

```cpp
#include <string>
#include <vector>

std::string make_big() { return std::string(1'000'000, 'x'); }

int main() {
    std::vector<std::string> v;
    v.push_back(make_big()); // moved into the vector (NRVO + move)
}
```

Parameter rules of thumb
- **Read‑only**: `const T&`.
- **Taking ownership** (sink): `T` by value (copy elision) or `T&&` with perfect forwarding.
- Use `std::move` to express transfer-of-resources; don’t overuse it.

---

## 10) Templates, Type Deduction & Concepts (C++20)

```cpp
template <typename T>
T add(T a, T b) { return a + b; }

#include <concepts>

template <std::integral I>
I inc(I x) { return x + 1; }
```

Notes
- Start from function templates → class templates → constraints.
- Concepts make diagnostics clearer and intent explicit.

---

## 11) Lambdas & Functional Utilities

```cpp
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> xs{1,2,3,4,5};
    auto n_odds = std::count_if(xs.begin(), xs.end(), [](int x){ return x % 2; });
}
```

Captures
- `[=]` copy, `[&]` reference, `[this]` capture object, `[x = expr]` init‑capture.

---

## 12) Error Handling

- **Return types** for expected absence: `std::optional`, or `std::expected<T,E>` (if available).
- **Exceptions** for exceptional, non‑local conditions.
- Don’t throw from destructors; use `noexcept` where appropriate.

Example with `optional`:
```cpp
#include <optional>
#include <charconv>

std::optional<int> to_int(std::string_view s) {
    int x{};
    auto [p, ec] = std::from_chars(s.data(), s.data()+s.size(), x);
    if (ec == std::errc{}) return x;
    return std::nullopt;
}
```

---

## 13) Modules, Ranges Deep‑Dive, Coroutines (preview)

- **Modules** reduce header bloat; require compiler & build support.
- **Ranges** offer composable pipelines & projections.
- **Coroutines** enable async/generator patterns (advanced topic).

---

## 14) Concurrency (quick primer)

- Use `std::jthread` (C++20) for scoped threads.
- Prefer high‑level concurrency: thread pools, tasks, async libraries.
- Synchronization: `std::mutex`, `std::lock_guard`, `std::atomic<T>`.

---

## 15) Filesystem & Time

```cpp
#include <filesystem>
namespace fs = std::filesystem;

for (auto& p : fs::directory_iterator(".")) {
    // p.path()
}
```

```cpp
#include <chrono>
using namespace std::chrono_literals;

auto start = std::chrono::steady_clock::now();
// work
auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::steady_clock::now() - start);
```

---

## 16) Testing & Project Structure

```
project/
├─ CMakeLists.txt
├─ include/            # public headers
├─ src/                # library/app sources
├─ apps/               # small executables
├─ tests/              # unit tests (Catch2 / doctest)
└─ cmake/              # CMake helpers
```

Example `CMakeLists.txt`
```cmake
cmake_minimum_required(VERSION 3.22)
project(hello LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
add_executable(hello src/main.cpp)
```

Testing sketch (doctest)
```cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>
int add(int a,int b){return a+b;}
TEST_CASE("add") { CHECK(add(2,3)==5); }
```

---

## 17) Practical Katas

- **Pointers/refs**: implement `swap(T&,T&)` and a `find` returning `T*` or `nullptr`.
- **RAII**: timer class that prints elapsed time in destructor.
- **Algorithms**: sort records by field with `std::ranges::sort` + projection.
- **Errors**: CSV parser returning `std::optional<Record>`.
- **Templates**: tiny `min` constrained by a strict ordering concept.
- **CMake**: split into library + tests, then add `install(TARGETS ...)` and `cpack`.

---

## 18) Common Pitfalls → Better Choices

| Pitfall | Better |
|---|---|
| Owning raw pointers | `std::unique_ptr`, containers manage memory |
| `new`/`delete` in app code | avoid; use RAII wrappers |
| `using namespace std;` in headers | never; prefer qualified names |
| Missing `virtual` destructors in polymorphic base | make base destructor `virtual` |
| Copy when you meant move | use `std::move` intentionally |
| Header include bloat | forward‑declare; consider modules |
| Exceptions for routine absence | use `std::optional` / `expected` |

---

## 19) Cheats — One‑Screen Reminders

### Function passing
- Small PODs → by value
- Large read‑only → `const&`
- Sink/own → by value or `T&&` + `std::forward`

### Rule of Five triggers
If you manage a resource (file, socket, heap pointer): dtor, copy/move ctors, copy/move assigns.

### Build flags (GCC/Clang typical)
```
-std=c++20 -O2 -Wall -Wextra -Wpedantic -Wconversion
```

### Useful headers to memorize
- `<array> <vector> <string> <string_view> <optional> <variant> <span>`
- `<algorithm> <ranges> <numeric> <iterator>`
- `<memory> <utility> <type_traits>`
- `<filesystem> <chrono> <format>`

---

## 20) Study Plan (8–12 weeks)

**A. Foundations (2 weeks)**  
- Build toolchain, variables & I/O, functions, control flow.

**B. Types & Collections (2 weeks)**  
- Arrays, `std::vector`, `std::string`, enums, references/pointers.

**C. Abstraction (2 weeks)**  
- Classes/structs, RAII, constructors, overloading, namespaces.

**D. Generic programming (2–3 weeks)**  
- Templates, algorithms, ranges, lambdas, ownership models, error handling.

**E. Modern features + build (2–3 weeks)**  
- Concepts, modules (if available), coroutines (read‑through), testing, CMake basics.

Daily rhythm: 45–90 min + 3–5 katas. Weekly: one integration task (refactor, add tests, package).

---

## 21) Mini‑Cookbook

### `std::visit` with `std::variant`
```cpp
#include <variant>
#include <string>
#include <iostream>

using V = std::variant<int, std::string>;

int main(){
    V v = std::string{"hi"};
    std::visit([](auto&& x){ std::cout << x << '\n'; }, v);
}
```

### Non‑owning views with `std::string_view`
```cpp
void log(std::string_view s);
log("literal");
std::string name = "Ada";
log(name);               // no allocation
```

### Ranges + projections
```cpp
#include <ranges>
#include <vector>
#include <algorithm>

struct Item{int id; int score;};
std::vector<Item> items{{1,50},{2,70},{3,60}};
std::ranges::sort(items, std::less{}, &Item::score);
```

### Measuring time safely
```cpp
#include <chrono>

auto t0 = std::chrono::steady_clock::now();
// ... work ...
auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - t0).count();
```

### Simple file read
```cpp
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> read_lines(const std::string& path){
    std::ifstream ifs(path);
    std::vector<std::string> out;
    for(std::string line; std::getline(ifs, line); ) out.push_back(line);
    return out;
}
```

---

## 22) Glossary (bite‑size)

- **RAII**: tie resource lifetime to object lifetime.
- **Copy elision**: compiler skips creating temporary copies.
- **Move**: transfer resources from one object to another.
- **SFINAE**: substitution failure is not an error; basis for constraints.
- **UB**: undefined behavior; avoid by following the rules.

---

## 23) Where to go next

- Concurrency and parallel algorithms (`<execution>`).
- Networking (Asio / Networking TS).
- Metaprogramming with concepts & `constexpr` algorithms.
- Performance profiling, allocators, cache‑friendly data layouts.

---

### Appendix A — Debugging quickstart
- Set a breakpoint in `main`.
- Step into/over; inspect variables and call stack.
- Learn watch expressions and conditional breakpoints.

### Appendix B — `clang-tidy` quickstart
- Run with a baseline config:
  ```yaml
  Checks: '-*,bugprone-*,performance-*,readability-*,cppcoreguidelines-*'
  WarningsAsErrors: '*'
  ```
- Iterate by enabling more checks gradually.

### Appendix C — Minimal module (if supported)
```cpp
// math.ixx
export module math;
export int add(int a, int b) { return a+b; }
```
```cpp
// main.cpp
import math;
#include <iostream>
int main(){ std::cout << add(2,3) << '\n'; }
```

> Build system support for modules is evolving; check your compiler & CMake version.

---

**End of Guide**

