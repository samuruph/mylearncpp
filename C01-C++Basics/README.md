# Chapter 01 — C++ Basics

## Overview
Introduction to C++ program structure, comments, variables, basic I/O, and simple interactive programs.

---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch01_first
./build/ch01_first
```


## 🎯 Learning Outcomes

By the end of this chapter, you’ll be able to:

- 🧩 **Understand** the structure of a C++ program and the role of the `main()` function.  
- 🔍 **Differentiate** between **statements**, **expressions**, and **blocks**, and explain their execution flow.  
- 💬 **Write effective comments** that clarify intent — using `//` for single-line and `/* ... */` for multi-line notes.  
- 🧱 **Declare and initialize variables** of fundamental types, and explain why initialization matters.  
- 🔡 **Use the iostream library** (`std::cout`, `std::cin`, and `std::endl`) for clean, formatted console input/output.  
- 🧮 **Perform basic computations** using arithmetic and logical operators.  
- 🚀 **Write, build, and run simple interactive programs** safely — avoiding undefined behavior and uninitialized variables.  
- 🧠 **Follow coding best practices** for clarity, naming, and consistent formatting.  

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
- **Data**: information (numbers, text, etc.) that can be moved, processed, or stored by a computer.
- **Value**: a specific piece of data (e.g., `5`, `'c'`, `"Hello"`).

#### Values and literals:
- Examples: `5`, `-6.7`, `'H'`, `"Hello"`.
- Single quotes = character, double quotes = string (text), no quotes = numeric.
- Values written directly in code are **literals** (read-only).
```cpp
#include <iostream> // for std::cout

int main()
{
    std::cout << 5;       // print the literal number `5`
    std::cout << -6.7;    // print the literal number `-6.7`
    std::cout << 'H';     // print the literal character `H`
    std::cout << "Hello"; // print the literal text `Hello`
}
```

#### Random Access Memory (RAM):
Computers have volatile memory (RAM) to store data temporarily while programs run. When we run a program, the OS allocates some RAM to it, reserving some additional memory for the program to use as it runs.


#### Objects and variables:
In C++, we access memory (indirectly) via **objects** and **variables**.
- An **object** is a region of memory that can hold a value (e.g., RAM or CPU registers).
- A **variable** is the name we give to an object (identifier).

Example:
```cpp
int x; // defines a variable x of type int
```
The compiler reserves memory and tracks it by name `x`.

#### Variable creation:
At **runtime**, objects have addresses in memory. The variable name is a label for that address. This process is called **allocation**.



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
int a, b;        // ok, same type
int a; double b; // also fine (better on separate lines)
```
Avoid:
```cpp
int a, double b; // invalid syntax
```

Best practice:
```cpp
int score;  // player score
int lives;  // number of lives left
```

#### Summary:
- Objects store values.
- Variables are named objects.
- Each has a **type**, **name**, and **value**.
- Created when memory is allocated at runtime.


---

### S04 — 1.4 Variable Assignment and Initialization

Give variables values either later (**assignment**) or at creation (**initialization**).

#### Variable assignment (`=`):
After a variable is defined, use assignment to give it a value:
```cpp
int width;   // define
width = 5;   // assign (copy-assignment)
width = 7;   // overwrite previous value
```
⚠️ Common pitfall: confuse assignment `=` with equality `==`.

#### Initialization (give an initial value at definition):

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
  int e{}; // e is 0
  ```

#### List-initialization disallows narrowing:
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

#### Value-initialization / zero-initialization:
```cpp
int count{};   // initializes to 0 (for fundamental types)
```

#### Instantiate and initialize:
“Instantiation” means the object is created (storage reserved) and initialized.

#### Initializing multiple variables:
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

#### Unused-initialized variables:
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

#### Include the header:
```cpp
#include <iostream>  // std::cout, std::cin, std::endl
```

#### `std::cout` — printing:
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

#### Newlines: `std::endl` vs `'\n'`:
```cpp
std::cout << "Hi!" << std::endl; // newline + flush
std::cout << "Hi!\n";           // newline only (faster)
```
- `std::endl` flushes the output buffer (slower).
- Prefer `'\n'` for routine newlines (no flush).
- Use `std::endl` only when you **need to flush**.

#### `std::cin` — reading input:
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

#### Best practices:
- Prefer `'\n'` over `std::endl` for routine newlines.
- Initialize variables before reading into them.
- Keep I/O statements clear and self-contained.

#### Summary:
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
In C/C++, uninitialized variables have indeterminate values, leading to undefined behavior if used before being assigned a value.

```cpp
#include <iostream>

int main()
{
    int x; // uninitialized variable (indeterminate value)
    std::cout << "Uninitialized x: " << x << '\n'; // undefined behavior

    x = {42}; // now we initialize x
    std::cout << "Initialized x: " << x << '\n'; // now safe to use

    return 0;
}
```

#### Uninitialized variables warning:
Using a variable that has not been initialized can lead to unpredictable results, crashes, or security vulnerabilities. This could cause a compilation error similar to: 
```c:\VCprojects\test\test.cpp(11) : warning C4700: uninitialized local variable 'x' used```

#### Undefined behavior (UB):
Using an uninitialized variable can lead to undefined behavior, where the program may produce unexpected results or crash. **Always initialize variables before use.**

#### Best practices:
- Always initialize variables upon declaration.
- Use list-initialization (`{}`) to avoid narrowing and ensure initialization.
- Pay attention to compiler warnings about uninitialized variables.

#### Summary:
- Uninitialized variables have indeterminate values.
- Using them leads to undefined behavior.
- Always initialize variables before use.


---

### S07 - 1.7 Keywords and naming identifiers
C++ has reserved **keywords** (92 reserved words in C++23) that cannot be used as identifiers (variable names, function names, etc.).

#### List of keywords:
```cpp
alignas, alignof, and, and_eq, asm, auto, bitand, bitor, bool, break, case, catch, char, char8_t (since C++20), char16_t, char32_t, class, compl, concept (since C++20), const, consteval (since C++20), constexpr, constinit (since C++20), const_cast, continue, co_await (since C++20), co_return (since C++20), co_yield (since C++20), decltype, default, delete, do, double, dynamic_cast, else, enum, explicit, export, extern, false, float, for, friend, goto, if, inline, int, long, mutable, namespace, new, noexcept, not, not_eq, nullptr, operator, or, or_eq, private, protected, public, register, reinterpret_cast, requires (since C++20), return, short, signed, sizeof, static, static_assert, static_cast, struct, switch, template, this, thread_local, throw, true, try, typedef, typeid, typename, union, unsigned, using, virtual, void, volatile, wchar_t, while, xor, xor_eq
```

#### Identifier (name of a variable) naming rules:
- Cannot be a keyword.
- Can be composed of letters (A-Z, a-z), digits (0-9), and underscores (_).
- Must begin with a letter or underscore (not a digit).
- C++ is case-sensitive (`var`, `Var`, and `VAR` are different).

#### Identifier naming best practices:
1) Should begin with a lowercase letter (e.g., `myVariable`).
    ```cpp
    int value; // conventional

    int Value; // unconventional (should start with lower case letter)
    int VALUE; // unconventional (should start with lower case letter and be in all lower case)
    int VaLuE; // unconventional (see your psychiatrist) ;)
    ```
    If multi-word, use **camelCase** or **snake_case**:
    ```cpp
    int my_variable_name;   // conventional (separated by underscores/snake_case)
    int my_function_name(); // conventional (separated by underscores/snake_case)

    int myVariableName;     // conventional (intercapped/camelCase)
    int myFunctionName();   // conventional (intercapped/camelCase)

    int my variable name;   // invalid (whitespace not allowed)
    int my function name(); // invalid (whitespace not allowed)

    int MyVariableName;     // unconventional (should start with lower case letter)
    int MyFunctionName();   // unconventional (should start with lower case letter)
    ```
2) Avoid starting with an underscore `_` (reserved for compiler/library use).
    ```cpp
    int _value; // unconventional (should not start with underscore)
    int __value; // unconventional (should not start with underscore)
    ```
3) Use meaningful and descriptive names.
    ```cpp
    int score;      // good (descriptive)
    int s;          // bad (not descriptive)
    int x1;         // bad (not descriptive)
    ```
4) Avoid abbreviations unless widely understood.
    ```cpp
    int totalScore; // good (clear)
    int totScr;     // bad (unclear)
    ```
5) Avoid single-letter names, except for loop indices (e.g., `i`, `j`, `k`).
    ```cpp
    for (int i = 0; i < 10; ++i) { // ok for loop index
        // ...
    }
    int x; // bad (not descriptive)
    ```
6) Comment when helpful.
    ```cpp
    int maxPlayers; // maximum number of players allowed
    ```

#### Best practices / Summary:
- Always use meaningful and descriptive names.
- Use consistent naming conventions throughout your codebase.
- Avoid using single-letter variable names, except for loop indices (e.g., `i`, `j`, `k`).
- Avoid starting identifiers with underscores.
- Avoid using keywords as identifiers.
- Comment your variables when it adds clarity.
- Use camelCase or snake_case for multi-word identifiers.
- Prefer lowercase starting letters for identifiers.

---

### S08 - 1.8 Whitespace and basic formatting
**Whitespace** refers to characters that are used for formatting and separating code elements, but do not affect the program's execution. This includes spaces, tabs, and newlines.

#### Some language elements must be separated by whitespace:
```cpp
#include <iostream> // correct
#include<iostream>  // incorrect, may cause compilation error

intx; // invalid: 'int' and 'x' must be separated
int x; // valid

int main() { return 0; } // valid
```

#### Quoted text:
When in quotes (single `'` or double `"`), whitespace is preserved:
```cpp
std::cout << "Hello, world!"; // valid
std::cout << "Hello,world!";  // valid (no space after comma)
```

#### Formatting and readability:
Use whitespace to improve readability and format the code:

- ❌ Bad:
    ```cpp
    int main(){int x=5;std::cout<<"x is "<<x<<'\n';return 0;}
    ```

- ✅ Good:
    ```cpp
  // Initialize x to 5 to count starting items
  int main() {
      int x = 5;
      std::cout << "x is " << x << '\n';
      return 0;
  }
  ```

#### Basic formatting guidelines:
1) Use indentation (e.g., 4 spaces or a tab) to indicate code blocks.
2) Two conventional styles for function braces:
    - **K&R style** (brace on same line):
        ```cpp
        int main() {
            // code
        }
        ```
   - **Allman style** (brace on new line):
        ```cpp
        int main()
        {
            // code
        }
        ```
   Choose one style and be consistent.
3) Each statement inside curly braces `{}` should start one tab or 4 spaces in.
4) Line should not exceed 80-100 characters for readability.
5) If a line is split with an operator (e.g., `<<`, `>>`, `+`), the operator should be placed at the start of the new line:
    ```cpp
    std::cout << 3 + 4
    + 5 + 6
    * 7 * 8;
    ```
6) Use whitespaces to make your code more readable:
    ```cpp
    cost          = 57;
    pricePerItem  = 24;
    value         = 5;
    numberOfItems = 17;

    std::cout << "Hello world!\n";                  // cout lives in the iostream library
    std::cout << "It is very nice to meet you!\n";  // these comments are easier to read
    std::cout << "Yeah!\n";                         // especially when all lined up
    ```

#### Automatic formatting tools:
Use tools like **clang-format** or IDE features to automatically format your code according to a style guide.

#### Style guides:
- [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines)
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [LLVM Coding Standards](https://llvm.org/docs/CodingStandards.html)
- [GCC/GNU Coding Standards](https://gcc.gnu.org/codingconventions.html)



#### Best practices / Summary:
- Use whitespace to separate code elements and improve readability.
- Be consistent with indentation and brace styles.
- Follow a style guide and consider using automatic formatting tools.
- Keep lines within a reasonable length (80-100 characters).


---

### S09 - 1.9 Introduction to literals and operators
C++ provides various **literals** to represent fixed values in code, and **operators** to perform operations on these values.

#### Literals:
- A **literal** is a fixed value written directly in the code (e.g., `5`, `3.14`, `'A'`, `"Hello"`).
    ```cpp
    std::cout << "Hello world!";
    int x { 5 };
    ```
    Here, `"Hello world!"` is a string literal, and `5` is an integer literal.

- **Literals vs variables**:
    - *Literals* are constant values that cannot be changed.
    - *Variables* are named storage locations that can hold different values during program execution.
        ```cpp
        #include <iostream>

        int main()
        {
            std::cout << 5 << '\n'; // print the value of a literal

            int x { 5 };
            std::cout << x << '\n'; // print the value of a variable
            return 0;
        }
        ```

- **Types of literals**:
  - **Integer literals**: `42`, `-7`, `0`
  - **Floating-point literals**: `3.14`, `-0.001`, `2.0e3`
  - **Character literals**: `'A'`, `'z'`, `'\n'`
  - **String literals**: `"Hello"`, `"C++"`
  - **Boolean literals**: `true`, `false`   

#### Operators:
In mathematics, **operator** is a process involving zero or more input values (called **operands**) that produces a new value (output).
In C++, operators are special symbols that perform operations on one or more operands.


Common operators include:
- **Arithmetic operators**: `+`, `-`, `*`, `/`, `%` (addition, subtraction, multiplication, division, modulus)
    ```cpp
    int sum = 5 + 3; // sum is 8
    int diff = 10 - 4; // diff is 6
    int prod = 2 * 3; // prod is 6
    int quot = 8 / 2; // quot is 4
    int mod = 7 % 3; // mod is 1
    ```
- **Relational operators**: `==`, `!=`, `<`, `>`, `<=`, `>=` (equality, inequality, less than, greater than, less than or equal to, greater than or equal to)
    ```cpp
    bool isEqual = (5 == 5); // true
    bool isNotEqual = (5 != 3); // true
    bool isLess = (3 < 5); // true
    bool isGreater = (5 > 3); // true
    bool isLessEqual = (3 <= 3); // true
    bool isGreaterEqual = (5 >= 3); // true
    ```
- **Logical operators**: `&&`, `||`, `!` (logical AND, logical OR, logical NOT)
    ```cpp
    bool andResult = (true && false); // false
    bool orResult = (true || false); // true
    bool notResult = !true; // false
    ``` 
- **Assignment operator**: `=` (assigns a value to a variable)
    ```cpp
    int x = 5; // assigns 5 to x
    ```
- **Others**: There are many more operators in C++ (bitwise, increment/decrement, conditional, etc.), like increment `++`, decrement `--`, insertion `<<`, extraction `>>`, and some textual operators like `new`, `delete`, `throw`, etc.

The number of operands an operator works with defines its **arity**:
- **Unary operators**: operate on a single operand (e.g., `-x`, `!flag`, `++i`)
- **Binary operators**: operate on two operands (e.g., `a + b`, `x == y`)
- **Ternary operator**: `? :` operates on three operands (e.g., `condition ? value1 : value2`)
- **N-ary operators**: operators that can take a variable number of operands (e.g., `std::cout << a << b << c;`)
- **Nullary operators**: operators that take no operands (e.g., `sizeof`, `typeid`)

#### Chanining operators:
Some operators can be chained together, such as summing multiple numbers:
```cpp
int total = 1 + 2 + 3 + 4; // total is 10
```

#### Return values and side effects:
- Most operators produce a **return value** (e.g., `5 + 3` returns `8`).
- Some operators have **side effects** (e.g., `++i` increments `i` by 1, or `x = 5` assigns `5` to `x`).

#### Best practices / Summary:
- Use operators to perform operations on literals and variables.
- Understand the different types of operators and their arity.
- Be aware of operator precedence and associativity to avoid unexpected results.


---

### S10 - 1.10 Introduction to expressions

#### Expressions:
An **expression** is a non-empty sequence of literals, variables, operators, and function calls that the compiler evaluates to produce a value.
All of these lines are expressions that evaluate to a value:
```cpp
// five() is a function that returns the value 5
int five()
{
    return 5;
}

int main()
{
    int a{ 2 };             // initialize variable a with literal value 2
    int b{ 2 + 3 };         // initialize variable b with computed value 5
    int c{ (2 * 3) + 4 };   // initialize variable c with computed value 10
    int d{ b };             // initialize variable d with variable value 5
    int e{ five() };        // initialize variable e with function return value 5

    return 0;
}
```

- The process of executing an expression is called **evaluation**, and the resulting value is the **result** of the expression (this can be a value, an object or a function, or nothing).

- Expressions do not end in a semicolon `;` (statements do), and cannot be compiled on their own. Usually they are part of a statement.
  ```cpp
  int x{ 2 + 3 }; // 2 + 3 is an expression that has no semicolon -- the semicolon is at the end of the statement containing the expression
  ```

#### Expresssion statements:
An **expression statement** is an expression followed by a semicolon `;`. It is a valid statement that can be compiled and executed.
```cpp
int x{ 2 + 3 }; // expression statement
x = x + 1;      // expression statement
std::cout << x; // expression statement
```

#### Useless expressions:
Some expressions do not have any effect (no side effects) and their result is not used.
```cpp
5 + 3; // useless expression: computes 8 but does nothing with it
```

#### Sub-expressions, full expressions, and compund expressions:
- A **sub-expression** is an expression used as an operand of another expression.
  ```cpp
  (2 * 3) + 4; // (2 * 3) and 4 are a sub-expressions of the full expression (2 * 3) + 4
  ```
- A **full expression** is an expression that is not a sub-expression of another expression.
  ```cpp
  2               // 2 is a literal that evaluates to value 2
  2 + 3           // 2 + 3 uses operator+ to evaluate to value 5
  x = 4 + 5       // 4 + 5 evaluates to value 9, which is then assigned to variable x
  ```
- A **compound expression** is an expression that contains two or more uses of operators.
  ```cpp
  2 + 3 * 4       // compound expression with two operators: + and *
  (2 + 3) * 4     // compound expression with two operators: + and *
  ```

#### Best practices / Summary:
- Understand what expressions are and how they are evaluated.
- Use expressions within statements to perform computations and operations.
- Avoid useless expressions that do not have any effect.


---

### S11 - 1.11 Developing your first program
The exercise is to create a simple interactive program that asks a user for an integer, doubles it, and prints the result.
Here is a complete example:
```cpp
// clang++ -std=gnu++14 -fcolor-diagnostics -fansi-escape-codes -g C01-C++Basics/sections/s11-first-program/main.cpp -o C01-C++Basics/sections/s11-first-program/main
#include <iostream>

int main()
{      
    // Ask to enter an integer
    std::cout << "Enter an integer: ";

    // Define the integer variable x
    int x {};

    // Input the integer number from user
    std::cin >> x;

    // Print the doubled number using an expression
    std::cout << "Double that number is: " << (x * 2) << "\n";
    return 0;
}
```

Compile it and run it! Enjoy!


---

### SX - 1.x Chapter 1 Summary & Quiz
Here the solution of the proposed exercise (get two inputs, and print their sum and difference):
```cpp
// /usr/bin/clang++ -std=gnu++14 -fcolor-diagnostics -fansi-escape-codes -g C01-C++Basics/sections/sx-summary-quiz/main.cpp -o C01-C++Basics/sections/sx-summary-quiz/main
#include <iostream>

int main() 
{
    int a {};
    int b {};

    std::cout << "Enter an integer: ";
    std::cin >> a;

    std::cout << "Enter another integer: ";
    std::cin >> b;

    std::cout << a << " + " << b << " is " << (a + b) << ".\n";
    std::cout << a << " - " << b << " is " << (a - b) << ".\n";
}
```

---

## 🧭 Summary

In this chapter, you’ve taken your **first real steps into C++** — understanding not just *what* the language looks like, but *how* it thinks. 🦾  

### 🧱 Core Concepts You Mastered:
- 🧩 The **structure** of a C++ program and the role of `main()`.  
- 💬 Writing clear and meaningful **comments** (what, how, and why).  
- 📦 Understanding **variables**, **data types**, and **initialization**.  
- 🖥️ Using **input/output streams** (`iostream`) for communication with the console.  
- ➕ Performing **basic arithmetic** and logical operations.  
- ⚙️ Writing **interactive programs** that process user input and produce clean output.  
- ✨ Following **best practices** — meaningful naming, consistent indentation, avoiding uninitialized variables, and preferring `{}` initialization.

