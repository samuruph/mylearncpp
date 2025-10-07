# Chapter 01 — Program Structure

## Overview
Statements, expressions, blocks, and the role of `main()`.  
You’ll write a simple interactive program and see how input / processing / output hang together.

---

## Learning Outcomes

- Understand the basic structure of a C++ program.
- Understand comments and how/when to use them.


---

## Sections

### S01 — 1.1 Statements and Structure of a Program

Fundamental building blocks of C++ programs:

- A **statement** is the smallest do-something instruction; most end with `;`.

- Statements live inside **functions**. Every C++ program must have **`main()`**, where execution starts and typically ends.

- **Characters** are basic symbols; sequences of characters form text/strings (control characters like `\n` exist too).  

- **Syntax errors** (e.g., missing `;`) stop compilation; compilers may point at the next line—check the prior one.

**Example:**
  ```cpp
  #include <iostream>

  int main()
  {
      std::cout << "Hello world!";
      return 0;
  }
  ```

- `#include <iostream>` enables console I/O.  For example, `std::cout << ...;` prints text.
- `main()` is where execution starts and typically ends with `return 0;` to signal success.


---

### S02 — 1.2 Comments

Comments are notes ignored by the compiler, used to document code.

#### Two types:

- **Single-line:** `// comment` — ignores text to the end of the line.  
- **Multi-line:** `/* comment */` — ignores everything in between.

For example:
```cpp
std::cout << "Hello world!"; // single-line comment

/* 
This is
a multi-line
comment 
*/
```

#### When to use comments:

Use comments to explain:
1) *What* a program, library, or function does.
    ```cpp
    // This function calculates the student's final grade based on their test and homework scores.
    double final_grade(int test_score, int homework_score) {
        // function body
    }
    ```
2) *How* a block of code achieves its goal.
    ```cpp
    // Using the quadratic formula to find the roots of the equation ax^2 + bx + c = 0
    double discriminant = b*b - 4*a*c;
    if (discriminant >= 0) {
        double root1 = (-b + sqrt(discriminant)) / (2*a);
        double root2 = (-b - sqrt(discriminant)) / (2*a);
        // ...
    }
    ```
3) *Why* a specific statement or decision is made.
    
    ```cpp
    // The player just drank a potion of blindness and can not see anything
    sight = 0;
    ```

#### Good and bad comments:

- ❌ Bad:
  ```cpp
  // Set x to 5
  ```

- ✅ Good:
  ```cpp
  // Initialize x to 5 to count starting items
  ```

Avoid nested `/* */` comments — they can break compilation.


#### Commenting out code:

You can comment out code temporarily for debugging:
```cpp
// std::cout << "test";
```
or
```cpp
/*
std::cout << "test";
*/
```cpp
/*
std::cout << "1";
std::cout << "2";
std::cout << "3";
*/
```
In **VS Code**: select lines → `Ctrl + /` (toggle comment).

#### Summary:
- Use comments to describe **what**, **how**, **why**.
- Write as if someone else (or future you) will read your code fresh.
- Commenting out code is useful to temporarily disable parts of it.


---

### S03 — 1.3 Introduction to Objects and Variables

Programs produce results by manipulating **data**.  
Data are stored as **values**, and values live inside **objects** (memory storage).

#### Some definitions:
- A **data** is any information (numbers, text, etc.) that can be moved, processed, or stored by a computer.
- A **value** is a specific piece of data (e.g., `5`, `'c'`, `"Hello"`).

#### Values and literals:
- Examples: `5`, `-6.7`, `'H'`, `"Hello"`.
- Single quotes = character, double quotes = text, no quotes = numeric.
- Values written directly in code = **literals** (read-only).

```cpp
#include <iostream> // for std::cout

int main()
{
    std::cout << 5;       // print the literal number `5`
    std::cout << -6.7;    // print the literal number `-6.7`
    std::cout << 'H';     // print the literal character `H`
    std::cout << "Hello"; // print the literal text `Hello`

    return 0;
}
```

#### Random Access Memory (RAM):
Computers have volatile memory (RAM) to store data temporarily while programs run. When we run a program, the OS allocates some RAM to it, reserving some additional memory for the program to use as it runs.


#### Objects and variables:
In C++, we access memory indirectly via **objects** and **variables**.
- An **object** is a region of memory that can hold a value (e.g., RAM or CPU registers).
- A **variable** is the name we give to an object (identifier).

Example:
```cpp
int x; // defines a variable x of type int
```
The compiler reserves memory and tracks it by name `x`.

#### Variable creation:
At **runtime**, when the program is loaded into memory and runs, each object is given a specific memory address. The variable name is just a label for that address. This process is acalled **allocation**.


#### Data types:
Define what kind of value is stored (`int`, `double`, `char`, ...), that must be known at compile time.

Here some common types:
| Type    | Description                     | Memory (typical) | Example    |
|---------|---------------------------------|------------------|------------|
| `char`  | Character (single symbol)          | 1 byte           | `'A'`      |
| `bool`  | Boolean (true/false)         | 1 byte           | `true`     |
| `int`   | Integer (whole number)          | 4 bytes          | `42`       |
| `float` | Floating-point number (decimal) | 4 bytes          | `3.14f`    |
| `double`| Floating-point number (decimal) | 8 bytes          | `3.14`     |
| `std::string` | Text (sequence of characters) | Varies           | `"Hello"`  |
| `void`  | No value (used for functions) | 0 bytes          | N/A        |

Examples:
```cpp
int a;       // integer
double b;    // floating-point number
char c;      // character
bool flag;   // boolean
```

#### Multiple definitions:
Good examples:
```cpp
int a, b;   // ok, same type
int a; double b; // also fine (better on separate lines)
```
Avoid:
```cpp
int a, double b; // invalid syntax
```

Best practice:
Define one variable per line and comment it:
```cpp
int score;  // player score
int lives;  // number of lives left
```

#### Summary
- Objects store values.
- Variables are named objects.
- Each has a **type**, **name**, and **value**.
- Created when memory is allocated at runtime.


---

### S04 — 1.4 Variable Assignment and Initialization

How to give variables values—either later (**assignment**) or at creation (**initialization**).

#### Variable assignment (`=`)
After a variable is defined, use assignment to give it a value:
```cpp
int width;   // define
width = 5;   // assign (copy-assignment)
width = 7;   // overwrite previous value
```
⚠️ Common pitfall: confuse assignment `=` with equality `==`.

#### Initialization (give an initial value at definition)

Prefer initializing when defining the variable:
```cpp
int width{5};   // initialize to 5 (list-init) — preferred
```

#### Five common forms:
```cpp
int a;        // 1) default-initialization (often indeterminate)
int b = 5;    // 2) copy-initialization
int c(6);     // 3) direct-initialization
int d{7};     // 4) direct-list-initialization  ← preferred
int e{};      // 5) value-initialization (zero-initialization in most cases)
```
- **Default-initialization**: no initializer; value is indeterminate (garbage).
  ```cpp
  int a; // a has an indeterminate value
  ```
- **Copy-initialization**: `=`; allows implicit conversions (e.g., `double` to `int` by truncation).
  ```cpp
  int b = 5;    // b is 5
  int b2 = 4.5; // b2 is 4 (truncated) --> not good!
  ```
- **Direct-initialization**: `()`; allows implicit conversions.
  ```cpp
  int c(6);     // c is 6
  int c2(4.5);  // c2 is 4 (truncated) --> not good!
  ```
- **Direct-list-initialization**: `{}`; disallows narrowing conversions (PREFERRED ✅).
  ```cpp
  int d1 { 5 };    // direct-list-initialization of initial value 5 into variable width (preferred)
  int d2 = { 6 };  // copy-list-initialization of initial value 6 into variable height (rarely used)
  int d3{4.5};     // error: narrowing conversion --> good!
  ```
- **Value-initialization**: `{}` with no value; initializes to zero for fundamental types.
  ```cpp
  int e{};      // e is 0
  ```

#### List-initialization disallows narrowing
With curly braces (direct-list-initialization), unsafe/narrowing conversions are rejected:
```cpp
int w1{4.5};   // error: narrowing
int w2 = 4.5;  // ok: becomes 4
int w3(4.5);   // ok: becomes 4
```
Later assignments may still narrow:
```cpp
int x{0};
x = 4.5;  // ok, becomes 4
```

#### Value-initialization / zero-initialization
```cpp
int count{};   // initializes to 0 (for fundamental types)
```

#### Instantiate and initialize
“Instantiation” means the object is created (storage reserved) and initialized.

#### Initializing multiple variables
```cpp
int a = 5,  b = 6;   // copy-init both
int c(7),   d(8);    // direct-init both
int e{9},   f{10};   // list-init both
int i{},    j{};     // value-init both
```

⚠️ Pitfall:
```cpp
int a, b = 5;   // a is uninitialized; only b gets 5
```

#### Unused-initialized variables
Compilers may warn on unused variables. Options:
- Remove if not needed.
- Use it (e.g., print).
- If intentionally unused and justified:
```cpp
[[maybe_unused]] double gravity{9.8};
```

#### Best practices:
- Initialize upon creation (prefer `{}` or `{value}`).
- Prefer **list-init (`{}`)** to avoid narrowing and for consistency.
- One variable per line, with a short comment if helpful.

#### Summary:
- Assignment (`=`) gives a value after definition.
- Initialization gives a value at definition (preferred).
- Prefer list-initialization (`{}`) to avoid narrowing.


---

### S05 — 1.5 Introduction to iostream: cout, cin, and endl

Using the Input/Output (I/O) library to print to the console and read user input.

#### Include the header
```cpp
#include <iostream>  // std::cout, std::cin, std::endl
```

#### `std::cout` — printing
Print text, numbers, and variables using the **insertion operator** `<<`:
```cpp
std::cout << "Hello world!";
std::cout << 4;
int x{5};
std::cout << "x is " << x;
```
- `<<` means "convey to" or "insert into", from left to right.
- Chain multiple `<<` to build one line of output.
- `std::cout` is **buffered** (the output is stored temporarily in a buffer and periodically "flushed" to the console).

#### Newlines: `std::endl` vs `'\n'`
```cpp
std::cout << "Hi!" << std::endl; // newline + flush
std::cout << "Hi!\n";           // newline only (faster)
```
- `std::endl` flushes the output buffer (slower).
- Prefer `'\n'` for routine newlines (no flush).
- Use `std::endl` only when you **need to flush**.

#### `std::cin` — reading input
Read values using the **extraction operator** `>>`:
```cpp
#include <iostream>  // for std::cout and std::cin

int main()
{
    std::cout << "Enter a number: "; // ask user for a number

    int x{};       // define variable x to hold user input (and value-initialize it)
    std::cin >> x; // get number from keyboard and store it in variable x

    std::cout << "You entered " << x << '\n';
    return 0;
}
```
- `>>` means "extract from", from right to left.
- Read multiple values:
  ```cpp
  int a{}, b{};
  std::cin >> a >> b;
  ```
- Input is **buffered** (user types input, presses Enter, then program reads it).
- Whitespace (spaces, tabs, newlines) is skipped automatically.

#### Operator `<<` vs `>>`:
- `std::cout << value` → value flows **to** the console (right to left).
- `std::cin >> var` → value flows **into** your variable (left to right).

#### Best practices
- Prefer `'\n'` over `std::endl` for routine newlines.
- Initialize variables before reading into them.
- Keep I/O statements clear and self-contained.

#### Summary
- Use `std::cout` with `<<` to print.
- Use `std::cin` with `>>` to read input.
- Prefer `'\n'` for newlines; use `std::endl` only when flushing is needed.

---

### S06 — 1.6 First Interactive Program

Prompt for an integer, compute a result, print it.

```cpp
#include <iostream>

int main()
{
    int num{};
    std::cout << "Enter a number: ";
    std::cin >> num;
    std::cout << "You entered: " << num << '\n';
    return 0;
}
```


---

### S06 - 1.6 Uninitialized variables and undefined behavior
Intro 

#### Sec 1


#### Best practices
- 
-

#### Summary
- 
-


---

### S07 - 1.7
Intro 

#### Sec 1


#### Best practices
- 
-

#### Summary
- 
-


---

### S08 - 1.8
Intro

#### Sec 1

#### Best practices
-
-

#### Summary
-
-


---










**Build / Run**
```bash
cmake --build build --target ch01_first
./build/ch01_first
```

**Exercises**
- Add validation for non-integer input.
- Log invalid input using `std::cerr`.

---

### Pitfalls & Pro Tips
- Don’t forget `#include <iostream>`.  
- Don’t use `using namespace std;` in headers.  
- Define variables before using them; initialize upon creation.  
- Avoid narrowing with list-initialization; use `[[maybe_unused]]` only when justified.

---

### LearnCpp References
- 1.1 — Statements and the structure of a program  
  https://www.learncpp.com/cpp-tutorial/statements-and-the-structure-of-a-program/
- 1.2 — Comments  
  https://www.learncpp.com/cpp-tutorial/comments/
- 1.3 — Introduction to objects and variables  
  https://www.learncpp.com/cpp-tutorial/introduction-to-objects-and-variables/
- 1.4 — Variable assignment and initialization  
  https://www.learncpp.com/cpp-tutorial/variable-assignment-and-initialization/
- 1.5 — Introduction to iostream: cout, cin, and endl  
  https://www.learncpp.com/cpp-tutorial/introduction-to-iostream-cout-cin-and-endl/
- 1.x — Chapter summary & quiz  
  https://www.learncpp.com/cpp-tutorial/chapter-summary-and-quiz/
