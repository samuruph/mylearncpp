# LearnCpp.com — Modern C++ Guide (Chapters & Sections)

## Important Questions
- Why another C++ tutorial?
  - Why not, moreover I am jobless and I need to do some shit.
- Did you use Chat-GPT for this?
  - Ofc, let's be honest, but mostly to generate the overall structure and to refine READMEs, since I am italian as you might know my english is terrible.
- ETA ?
  - No fukin idea, depending on how lazy I am
- Why to learn C++?
  - Because I saw that in most of job postings, C++ is HIGHLY appreciated, and moreover I wanted to learn CUDA C++, and how could I learn CUDA C++ without knowing C++ first?

## About
This is my **from‑scratch to good-enough** (you will tell me if it is actually good enough, not sure it worked for me) C++ path, built while following the excellent free tutorial at **[LearnCpp.com](https://www.learncpp.com/)**.  
The repo mirrors LearnCpp’s, but adds a clean, runnable code path:

- **One chapter README per topic**: crisp theory summary, gotchas, and direct pointers to relevant LearnCpp lessons.
- **`sections/` folder per chapter** with small, runnable programs you can build and step through.
- **CMake (C++17)**, strict warnings, and a tiny test harness so it scales with your learning.
- LearnCpp is continuously updated and has detailed **summaries/quizzes** — use those to self-check as you go.

> Tip: Treat this repo as your playground. Read, run, tweak, refactor, test.

---

## Getting Started (macOS, Apple Silicon M‑series)
### Prerequisites
- **VS Code 1.104.3** (with Microsoft *C/C++* extension for IntelliSense & debugging).
- Developer tools & toolchain:
  ```bash
  xcode-select --install                      # Apple Command Line Tools (includes Apple Clang)
  /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
  brew install llvm cmake ninja               # Clang/LLVM, CMake, Ninja
  ```

> Homebrew’s `clang++` typically lives at `/opt/homebrew/opt/llvm/bin/clang++`. Prefer that compiler path for the latest LLVM runtime and `<format>` support.

(Optional) prefer Homebrew LLVM in your shell:
```bash
echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zshrc
echo 'export LDFLAGS="-L/opt/homebrew/opt/llvm/lib"' >> ~/.zshrc
echo 'export CPPFLAGS="-I/opt/homebrew/opt/llvm/include"' >> ~/.zshrc
source ~/.zshrc
```

### Installation
Simply clone the source from this repository.
```shell
git clone https://github.com/samuruph/mylearncpp.git
cd mylearncpp
```

### VS Code setup (quick)
1. Install the **C/C++** extension.
2. Open this folder in VS Code; it will detect the CMake project.
3. Set **Compiler Path** to `/opt/homebrew/opt/llvm/bin/clang++` and **C++ standard** to `c++20` (Command Palette → *C/C++: Edit Configurations (UI)*).

---

## Build & Test
```bash
mkdir -p build && cd build
cmake -G Ninja ..        # or: cmake ..
cmake --build .
ctest --output-on-failure
```

Run a specific chapter example (see table below for targets), e.g.:
```bash
cmake --build build --target ch05_ptrs
./build/ch05_ptrs
```

---

## Repository Structure
```
.
├─ CMakeLists.txt
├─ .clang-format / .clang-tidy / .gitignore
├─ C00-Getting-Started/
├─ C01-Program-Structure/
├─ C02-Functions/
├─ C03-IO-Format/
├─ C04-Types-Init/
├─ C05-Pointers-References/
├─ C06-Std-Containers-Algorithms/
├─ C07-Classes-RAII/
├─ C08-Smart-Pointers/
├─ C09-Moves-Ownership/
├─ C10-Templates-Concepts/
├─ C11-Lambdas-Ranges/
├─ C12-Error-Handling/
├─ C13-Filesystem-Time/
├─ C14-CMake-Project/
└─ C15-Testing/
```
Each chapter folder contains:
- `README.md` — short theory, gotchas, and links to LearnCpp lessons.
- `sections/` — small runnable examples (each with a `main.cpp`).
- Optional `CMakeLists.txt` if the chapter builds multiple small targets.

---

## Chapter Map → Targets (quick navigation + TL;DR)

> Read each chapter’s README first, then open `sections/` to run examples.

| Chapter | Target(s) | TL;DR |
|---|---|---|
| **C00 — Getting Started** | `ch00_hello` | Install toolchain, build a hello world, debugger set default C++ language on vscode. LearnCpp’s intro explains the approach and who it’s for. |
| **C01 — Program Structure** | `ch01_first` | Statements, expressions, blocks, and `main()`. Write your first interactive program; chapter summary has a self‑quiz. |
| **C02 — Functions** | `ch02_funcs` | Why functions; decl/defn split; headers; pass small by value, big by `const&`, sinks by value/forwarding; chapter quiz available. |
| **C03 — I/O & `<format>`** | `ch03_io` | `cin/cout/cerr` basics; prefer C++20 `<format>` for type‑safe formatting (fallback to iostream manipulators if not available). |
| **C04 — Types & Init** | `ch04_types` | Fundamental types, sizes, conversions; prefer `const/constexpr` and brace‑init to avoid narrowing. |
| **C05 — Pointers & References** | `ch05_ptrs` | References alias; pointers store addresses; nullability; `*` and `&`; `->` for member access; later, function pointers build on this. |
| **C06 — Std Containers & Algos** | `ch06_stl` | `vector`, maps, iterators; `sort`, `find_if`, projections. Chapter summaries on arrays/containers are good refreshers. |
| **C07 — Classes & RAII** | `ch07_raii` | Encapsulation; resource ownership via ctor/dtor; rule of five; move‑only wrappers; class invariants. |
| **C08 — Smart Pointers** | `ch08_smart` | Default to `unique_ptr`; use `shared_ptr` for true sharing; `weak_ptr` to break cycles. |
| **C09 — Moves & Ownership** | `ch09_moves` | Value semantics with cheap moves; NRVO; use `std::move` intentionally when transferring ownership. |
| **C10 — Templates & Concepts** | `ch10_tpl` | Function/class templates; constrain with C++20 concepts (`std::integral`, etc.). |
| **C11 — Lambdas & Ranges** | `ch11_ranges` | Captures (`[=]`, `[&]`, init‑capture); Ranges pipelines (filter/transform) for composable data transforms. |
| **C12 — Error Handling** | `ch12_errors` | `std::optional` for expected absence; throw/catch at module boundaries; avoid throwing from destructors. |
| **C13 — Filesystem & Time** | `ch13_fs` | Iterate directories with `<filesystem>`; measure with `<chrono>` using steady clocks. |
| **C14 — CMake Project** | `ch14_cmake` | Targets, per‑target warnings, and CTest; scale from single file to multi‑target projects. |
| **C15 — Testing** | `ch15_tests` | Minimal header‑only test runner + CTest; swap in Catch2/doctest later if desired. |

---

## LearnCpp Section‑by‑Section TL;DR
A quick set of “what you should retain” notes for anchor lessons and chapter summary pages. Use these alongside LearnCpp’s official pages:

- **0.1 — Introduction to these tutorials**: You don’t need prior C. The course emphasizes clarity, progressive examples, and frequent updates; follow chapter order and do the quizzes.  
- **0.2 — Programs & languages**: A program is an ordered set of instructions; languages are tools to express those instructions; C++ balances performance and control.  
- **0.3 — Intro to C/C++**: It’s fine to start with C++; you’ll learn pitfalls along the way.  
- **1.1 — Statements & program structure**: Programs are built from statements grouped in blocks; execution starts at `main()`.  
- **1.11 — Your first program**: Compile, run, and iterate quickly; use the debugger early.  
- **1.x — Chapter 1 summary & quiz**: Review statements, expressions, literals, identifiers, and basic formatting; then take the quiz.  
- **2.1 — Introduction to functions**: Functions modularize programs; prefer short, single‑purpose functions; `main()` is only the start.  
- **2.2 — Return values**: Distinguish value‑returning vs `void` functions; be explicit with return types; use parameters intentionally.  
- **2.x — Chapter 2 summary & quiz**: Solidify when to pass by value vs `const&` and how to organize declarations/definitions.  
- **12.7 — Introduction to pointers**: Pointers store addresses; `&` gets an address, `*` dereferences; compare with references; practice printing `&p`, `p`, `*p`.  
- **20.1 — Function pointers**: Like variable pointers, but to functions; enable callbacks and strategy patterns.  
- **14.2 — Introduction to classes**: Class invariants define valid states; maintain them via constructors and member functions; violations risk UB.  
- **16.x — Chapter 16 summary & quiz**: Arrays and container foundations; lots of detail — expect to revisit; use the summary to anchor memory model & array behavior.  
- **25.x — Chapter 25 summary & quiz**: Polymorphism wrap‑up; base refs/pointers to derived enable generic code; virtual dispatch trades cost for flexibility.  

> LearnCpp also has an evolving **Site Index** that’s handy when you forget which lesson covered a specific symbol or topic.

---

## Study Workflow
1. Read the chapter README here, then the matching LearnCpp lesson(s).
2. Run the example(s) under `sections/` and experiment.
3. Quiz yourself on the LearnCpp chapter summary page if available.
4. Refactor the example (tests, RAII, ranges, error‑handling) to cement the idea.

---

## Troubleshooting (macOS)
- **VS Code can’t find the compiler?** Re‑set the *Compiler Path* to Homebrew LLVM and ensure your shell PATH puts `/opt/homebrew/opt/llvm/bin` first.  
- **`<format>` not found?** Your `libstdc++/libc++` may be old. Use Homebrew LLVM (see above) or temporarily fall back to iostream formatting.  

---

## License

This project is distributed under the terms of the MIT License.
See [LICENSE](LICENSE) for more information.
