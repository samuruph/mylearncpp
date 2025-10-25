# Chapter 05 — Constants and Strings

## Overview
TODO: write overview


---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch05_first
./build/ch05_first
```


---

## 🎯 Learning Outcomes
TODO: write outcomes


---

## Sections
### S01 — 5.1 Constant variables (named constants)

#### Introduction to constants:
In programming, a **constant** is a value that may not be altered by the program during normal execution. C++ provides two different types of constants:
- **Named constants (symbolic constants)**: These are constants that are given a name using the `const` keyword. They improve code readability and maintainability by allowing you to use meaningful names instead of hard-coded values.
- **Literal constants**: These are fixed values that are directly written into the code and not associated with a name.

There are three ways of defining named constants in C++:
1. Constant variables (this lesson)
2. Object-like macros with substitution text (preprocessor directives) (previous chapter)
3. Enumerated constants (upcoming chapter)

#### Constant variables:
In C++, you can define a constant variable using the `const` keyword. Once a constant variable is initialized, its value cannot be changed. This is useful for defining values that should remain constant throughout the program.

Example:
```cpp
const int MAX_USERS = 100;  
const double PI = 3.14159;
const double gravity { 9.8 };  // preferred use of const before type
int const sidesInSquare { 4 }; // X "east const" style, okay but not preferred
```

Constant variables **must be initialized** at the time of declaration. Attempting to modify a constant variable after its initialization will result in a compilation error. They can al;so be initialized by other variables or expressions, as long as the value is known at compile time.

#### Naming your constant variables:
When naming constant variables, it is a common convention to use uppercase letters with underscores to separate words. This helps distinguish them from regular variables. However, we could also use the same naming conventions as for regular variables, as long as we are consistent.
Example:
```cpp
const int MAX_SPEED = 120; // uppercase with underscores
const double interestRate = 0.05; // camelCase
```

### Const function parameters:
You can also use the `const` keyword with function parameters to indicate that the function should not modify the argument passed to it. This is particularly useful when passing large objects or structures to functions, as it prevents accidental modifications and can improve performance by avoiding unnecessary copies. For example:
```cpp
#include <iostream>

void printInt(const int x)
{
    std::cout << x << '\n';
}

int main()
{
    printInt(5); // 5 will be used as the initializer for x
    printInt(6); // 6 will be used as the initializer for x

    return 0;
}
```
However, usually it is better to not use `const` for value parameters.

#### Const return values:
For fundamental types, the `const` qualifier on return values is simply ignored. So, try to avoid this.

#### Why variables should be made constant:
Making variables constant has several benefits:
- **Reduce bugs**: By preventing accidental modifications, constant variables help reduce the likelihood of bugs in your code.
- **Optimizations**: Compilers can make optimizations based on the knowledge that certain values will not change, potentially leading to more efficient code.
- **Self-documenting code**: Using constant variables makes your code more readable and understandable, as it clearly indicates which values are intended to remain unchanged.

#### Object-like macros with substitution text:
In a previous lesson, we introduced object-like macros using the `#define` preprocessor directive to create symbolic constants. These macros are also named constants, but they differ from constant variables in several ways:
- Macros do not follow normal C++ scoping rules, all macros are globally visible after they are defined and are substituted by the preprocessor before compilation.
- Macros do not have a specific type, they are simply text substitutions.
- Macros make harder to debug code, as they do not provide type safety or scope control.

> **Note**: In modern C++, it is generally recommended to use constant variables (`const`) instead of object-like macros for defining named constants, due to the advantages of type safety and scope control.

#### Nomenclature: type qualifiers:
A **type qualifier** is a keyword that you can use to modify a data type. The most common type qualifier in C++ is `const`, which indicates that a variable's value cannot be changed after it has been initialized. Other type qualifiers include `volatile` and `mutable`, but they are less commonly used. In technical documentation, the `const` and `volatile` keywords are often referred to as **cv-qualifiers** (constant and volatile qualifiers). In general:
- **cv-unqualified**: a type that is neither `const` nor `volatile`.
- **cv-qualified**: a type with one or more type qualifiers (e.g., `const int`, `volatile double`, etc.).
- **possibly cv-qualified**: a type that may or may not have type qualifiers.

#### Summary:
- Constant variables are defined using the `const` keyword and cannot be modified after initialization.
- Named constants improve code readability and maintainability.
- Use `const` with function parameters to prevent modifications to arguments.
- Avoid using `const` for return values of fundamental types.
- Prefer using `const` for pointers and references to indicate that the pointed-to value should not be modified.


---

### S02 — 5.2 Literals
**Literals** are values that are directly inserted into the code without being associated with a name. They represent fixed values of various data types, such as integers, floating-point numbers, characters, and strings. For example:
```cpp
return 5;                     // 5 is an integer literal
bool myNameIsAlex { true };   // true is a boolean literal
double d { 3.4 };             // 3.4 is a double literal
std::cout << "Hello, world!"; // "Hello, world!" is a C-style string literal
char letter { 'A' };          // 'A' is a character literal
```
In here, `5`, `true`, `3.4`, `"Hello, world!"`, and `'A'` are all examples of literals.

#### The type of a literal:
Just like objects have a type, literals also have a type. The type of a literal is determined by its format and the context in which it is used. For example:
- Integer literals (e.g., `42`, `0`, `-7`) are of type `int` by default.
- Floating-point literals (e.g., `3.14`, `0.0`, `-2.5`) are of type `double` by default.
- Character literals (e.g., `'A'`, `'b'`, `'\n'`) are of type `char`.
- String literals (e.g., `"Hello"`, `"C++"`) are of type `const char[]`.

#### Literal suffixes:
You can modify the type of a literal by using suffixes. Here are some common suffixes:
- `u` or `U`: Unsigned integer (e.g., `42u`)
- `l` or `L`: Long integer (e.g., `42l`)
- `ul` or `UL`: Unsigned long integer (e.g., `42ul`)
- `f` or `F`: Float (e.g., `3.14f`)
- `ll` or `LL`: Long long integer (e.g., `42ll`)
- `ull` or `ULL`: Unsigned long long integer (e.g., `42ull`)
- `s`: String literal of type `std::string` (C++14 and later) (e.g., `"Hello"s`)
- `sv`: String view literal of type `std::string_view` (C++17 and later) (e.g., `"Hello"sv`)
- and many others for different types.

In most cases, suffixes are not needed, except for float literals `f`, as by default floating-point literals are of type `double`.

#### Suffix casing:
Most of suffixes are case-insensitive, meaning you can use either uppercase or lowercase letters. The exceptions are:
- `s` and `sv` must be lower case.
- Two consecutive `l` or `L` must have the same case (e.g., `ll` or `LL`).

#### Integral literals:
Generally, you will not need to use suffixes for integral literals, as the default type `int` is usually sufficient. However, here some examples:
```cpp
#include <iostream>

int main()
{
    std::cout << 5 << '\n';  // 5 (no suffix) is type int (by default)
    std::cout << 5L << '\n'; // 5L is type long
    std::cout << 5u << '\n'; // 5u is type unsigned int

    return 0;
}
```
Usually, the compiler will automatically promote the type of an integral literal as needed, so you rarely need to use suffixes. For example:
```cpp
int main()
{
    int a { 5 };          // ok: types match
    unsigned int b { 6 }; // ok: compiler will convert int value 6 to unsigned int value 6
    long c { 7 };         // ok: compiler will convert int value 7 to long value 7

    return 0;
}
```

#### Floating-point literals:
By default, floating-point literals are of type `double`. If you need a `float` literal, you should use the `f` or `F` suffix. For example:
```cpp
#include <iostream>

int main()
{
    std::cout << 5.0 << '\n';  // 5.0 (no suffix) is type double (by default)
    std::cout << 5.0f << '\n'; // 5.0f is type float

    return 0;
}
```
When assigning a floating-point literal to a `float` variable, it is important to use the `f` suffix to ensure that the literal is treated as a `float`. For example:
```cpp
int main()
{
    float x { 3.14f }; // ok: 3.14f is type float
    // float y { 3.14 }; // error: 3.14 is type double, cannot convert to float without a cast

    return 0;
}
```
If you do not use the `f` suffix, the compiler will treat the literal as a `double`, which may lead in a loss of precision when assigning it to a `float` variable.

#### Scientific notation for floating-point literals:
There are two ways to write floating-point literals:
- Standard decimal notation (e.g., `3.14`, `0.001`, `123.456`)
- Scientific notation (e.g., `3.14e2`, `1.0e-3`, `1.23456E3`)

#### String literals:
String literals are sequences of characters enclosed in double quotes. They are of type `const char[]`. For example:
```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!" << '\n';
    return 0;
}
```
Because strings are commonly used in programs, most modern programming languages include a fundamental string data type, called **C strings** or **C-style strings** in C++.

There are two non-obvious things to know about C-style strings:
1. All C-style strings have an implicit null terminator at the end, that indicates the end of the string. This null terminator is represented by the escape sequence `\0`.
2. Unlike most other literals (which are values, not objects), string literals are const objects that are created at the start of the program and destroyed at the end of the program. This will become important next, when we will talk about `std::string_view`.

Unlike C-style string literals, `std::string` and `std::string_view` literals create temporary objects that are destroyed at the end of the full expression in which they are used.

#### Magic numbers:
A **magic number** is a literal (usually a number) that either has an unclear meaning or may need to be changed later. For example:
```cpp
const int maxStudentsPerSchool{ numClassrooms * 30 };
setMax(30);
```
In this example, the number `30` is a magic number because it is not clear why this specific value was chosen, and if the maximum number of students per classroom changes in the future, you would need to find and update all occurrences of this magic number in your code.
Using magic numbers in code is generally discouraged, as they can make the code harder to read and maintain. Instead, it is better to use named constants (constant variables) to give meaningful names to these values. For example, instead of using the magic number `3.14159` directly in your code, you could define a named constant:
```cpp
const int maxStudentsPerClass { 30 };
const int totalStudents{ numClassrooms * maxStudentsPerClass }; // now obvious what this 30 means

const int maxNameLength{ 30 };
setMax(maxNameLength); // now obvious this 30 is used in a different context
```

#### Summary:
- Literals are fixed values directly written in the code.
- Literals have types determined by their format and context.
- Suffixes can modify the type of literals.
- Avoid using magic numbers; use named constants instead for better readability and maintainability.


---

### S03 — 5.3 Numeral systems (decimal, binary, hexadecimal, and octal)
In everyday life, we commonly use the **decimal** numeral system (base 10), which consists of ten digits: 0, 1, 2, 3, 4, 5, 6, 7, 8, and 9. However, in computer science and programming, other numeral systems are also frequently used, such as binary (base 2), hexadecimal (base 16), and octal (base 8). By default, C++ uses the decimal numeral system for integer literals, but you can also specify literals in binary, hexadecimal, and octal formats using specific prefixes.

In **binary** there are only 2 digits: 0 and 1, and we can count like this: 0, 1, 10, 11, 100, 101, 110, 111, 1000, etc.

Decimal and binary are two examples of **numerical systems**, that is the name for a collection of symbols (digits) used to represent numbers. Some numeral systems include:
- **Decimal (base 10)**: uses ten symbols: 0-9. For example, the decimal number `42` represents the value forty-two (4 * 10 + 2).
- **Binary (base 2)**: uses two symbols: 0 and 1. For example, the binary number `101010` represents the decimal value `42` (1 * 32 + 0 * 16 + 1 * 8 + 0 * 4 + 1 * 2 + 0 * 1).
- **Hexadecimal (base 16)**: uses sixteen symbols: 0-9 and A-F (or a-f) to represent values ten to fifteen. For example, the hexadecimal number `2A` represents the decimal value `42` (2 * 16 + 10).
- **Octal (base 8)**: uses eight symbols: 0-7. For example, the octal number `52` represents the decimal value `42` (5 * 8 + 2).

#### Octal and hexadecimal literals:
**Octal** is based on 8 digits (0-7) and is not commonly used in modern programming, but it can be useful in certain contexts, such as file permissions in Unix-like operating systems. In octal, one can count like this: 0, 1, 2, 3, 4, 5, 6, 7, 10, 11, 12, etc. Note that after 7 comes 10, because 8 is represented as 10 in base 8.

In C++, you can represent octal literals by prefixing the number with a leading `0` (zero). For example:
```cpp
int octalNumber = 012; // This is an octal literal
std::cout << octalNumber << '\n'; // will print 10 in decimal (by default)
```
that will print `10` in decimal.

**Hexadecimal** is based on 16 digits (0-9 and A-F) and is widely used in programming, especially for representing memory addresses and color codes. In hexadecimal, one can count like this: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F, 10, 11, etc. Note that after 9 comes A (10 in decimal), B (11 in decimal), and so on up to F (15 in decimal), after which comes 10 (16 in decimal). For example:
```cpp
#include <iostream>

int main()
{
    int x{ 0xF }; // 0x before the number means this is hexadecimal
    std::cout << x << '\n';
    return 0;
}
```
that will print `15` in decimal.

#### Numeral system tables:
Here are tables showing the representation of numbers from 0 to 15 in different numeral systems:

| Decimal | Binary  | Octal | Hexadecimal |
|---------|---------|-------|-------------|
| 0       | 0000    | 00    | 0           |
| 1       | 0001    | 01    | 1           |
| 2       | 0010    | 02    | 2           |
| 3       | 0011    | 03    | 3           |
| 4       | 0100    | 04    | 4           |
| 5       | 0101    | 05    | 5           |
| 6       | 0110    | 06    | 6           |
| 7       | 0111    | 07    | 7           |
| 8       | 1000    | 10    | 8           |
| 9       | 1001    | 11    | 9           |
| 10      | 1010    | 12    | A           |
| 11      | 1011    | 13    | B           |
| 12      | 1100    | 14    | C           |
| 13      | 1101    | 15    | D           |
| 14      | 1110    | 16    | E           |
| 15      | 1111    | 17    | F           |

#### Using hexadecimal to represent binary values:
Hexadecimal is often used as a more human-friendly representation of binary values, since one hexadecimal digit corresponds to four binary digits (bits). This makes it easier to read and write large binary numbers, since 1 byte (8 bits) can be represented by just two hexadecimal digits. For example, the binary value `0011 1010 0111 1111 1001 1000 0010 0110` can be represented in hexadecimal as `3A7F 9826`.

#### Binary literals:
Prior to C++14, there was no direct way to represent binary literals in C++. However, hexadecimal literals were often used as a more human-friendly representation of binary values.
```cpp
#include <iostream>

int main()
{
    int bin{};    // assume 16-bit ints
    bin = 0x0001; // assign binary 0000 0000 0000 0001 to the variable
    bin = 0x0002; // assign binary 0000 0000 0000 0010 to the variable
    bin = 0x0004; // assign binary 0000 0000 0000 0100 to the variable
    bin = 0x0008; // assign binary 0000 0000 0000 1000 to the variable
    bin = 0x0010; // assign binary 0000 0000 0001 0000 to the variable
    bin = 0x0020; // assign binary 0000 0000 0010 0000 to the variable
    bin = 0x0040; // assign binary 0000 0000 0100 0000 to the variable
    bin = 0x0080; // assign binary 0000 0000 1000 0000 to the variable
    bin = 0x00FF; // assign binary 0000 0000 1111 1111 to the variable
    bin = 0x00B3; // assign binary 0000 0000 1011 0011 to the variable
    bin = 0xF770; // assign binary 1111 0111 0111 0000 to the variable

    return 0;
}
```
With the introduction of C++14, you can now represent binary literals directly using the `0b` or `0B` prefix. For example:
```cpp
#include <iostream>

int main()
{
    int bin{};        // assume 16-bit ints
    bin = 0b1;        // assign binary 0000 0000 0000 0001 to the variable
    bin = 0b11;       // assign binary 0000 0000 0000 0011 to the variable
    bin = 0b1010;     // assign binary 0000 0000 0000 1010 to the variable
    bin = 0b11110000; // assign binary 0000 0000 1111 0000 to the variable

    return 0;
}
```

#### Digit separators:
To improve the readability of large numeric literals, C++14 introduced the **digit separator** feature, which allows you to use the single quote character (`'`) as a separator within numeric literals (purely visual). This can be particularly useful for representing large numbers, binary values, or hexadecimal values. For example:
```cpp
#include <iostream>
int main()
{
    int largeNumber = 1'000'000;        // one million
    int binaryValue = 0b1101'0010;      // binary literal with separator
    int hexValue = 0xDEAD'BEEF;         // hexadecimal literal with separator

    std::cout << largeNumber << '\n';
    std::cout << binaryValue << '\n';
    std::cout << hexValue << '\n';

    return 0;
}
```

#### Outputting values in deciaml, octal, or hexadecimal:
By default, C++ outputs integer values in decimal format. However, you can change the output format to octal or hexadecimal using `std::dec`, `std::oct`, and `std::hex` I/O manipulators. For example:
```cpp
#include <iostream>

int main()
{
    int x { 12 };
    std::cout << x << '\n'; // decimal (by default)
    std::cout << std::hex << x << '\n'; // hexadecimal
    std::cout << x << '\n'; // now hexadecimal
    std::cout << std::oct << x << '\n'; // octal
    std::cout << std::dec << x << '\n'; // return to decimal
    std::cout << x << '\n'; // decimal

    return 0;
}
```
that will print:
```
12
c
c
14
12
12
```

> **Note**: Once you set the output format using `std::hex` or `std::oct`, it remains in that format until you change it back to decimal using `std::dec`.

#### Outputting values in binary:
Outputting values in binary is a little harder, as `std::cout` doesn’t come with this capability built-in. Fortunately, the C++ standard library includes a type called `std::bitset` that will do this for us (in the `<bitset>` header). Here is an example:
```cpp
#include <bitset> // for std::bitset
#include <iostream>

int main()
{
	// std::bitset<8> means we want to store 8 bits
	std::bitset<8> bin1{ 0b1100'0101 }; // binary literal for binary 1100 0101
	std::bitset<8> bin2{ 0xC5 }; // hexadecimal literal for binary 1100 0101

	std::cout << bin1 << '\n' << bin2 << '\n';
	std::cout << std::bitset<4>{ 0b1010 } << '\n'; // create a temporary std::bitset and print it

	return 0;
}
```
that will print:
```
11000101
11000101
1010
```

#### Outputting values in binary using the format / print library (C++20 and later):
Starting from C++20, you can use the `<format>` library to output values in binary format more easily. Here is an example:
```cpp
#include <format> // C++20
#include <iostream>
#include <print> // C++23

int main()
{
    std::cout << std::format("{:b}\n", 0b1010);  // C++20, {:b} formats the argument as binary digits
    std::cout << std::format("{:#b}\n", 0b1010); // C++20, {:#b} formats the argument as 0b-prefixed binary digits

    std::println("{:b} {:#b}", 0b1010, 0b1010);  // C++23, format/print two arguments (same as above) and a newline

    return 0;
}
```
that will print:
```
1010
0b1010
1010 0b1010
```

#### Summary:
- C++ supports multiple numeral systems: decimal, binary, hexadecimal, and octal.
- You can represent literals in different numeral systems using specific prefixes.
- Use digit separators to improve the readability of large numeric literals.
- You can output values in different numeral systems using I/O manipulators or the `<format>` library (C++20 and later).


---

### S04 — 5.4 The as-if rule and compile-time optimization
#### Introduction to optimization:
Optimization is the process of modifying software to make it more efficient, such as running faster or using fewer resources. Some optimizations are done manually by developers, using a program called **optimizer** to measure the performance of their code and identify areas for improvement (typically hand optimization are algorithms or data structures).

Other kinds of optimization can be performed automatically. A program that performs automatic optimization is called an **optimizer**, that typically work at low level (assembly or machine code) to improve performance without changing the program's behavior. Usualy focus on rewriting, reordering, eliminating, or combining instructions to make them more efficient. For example, an optimizer might change this ``x = x + 1;`` to this ``++x;`` to improve performance, dependign on the architecture.

Modern C++ compilers are **optimizing compilers**: they can automatically improve the performance of your code during compilation, without modifying your source files. This allows developers to write readable and maintainable code while still benefiting from performance improvements.

Compilers offer different optimization levels (e.g., `-O0`, `-O1`, `-O2`, `-O3`, `-Os`), which can prioritize speed, size, or debugging simplicity.

#### The as-if rule:
The **as-if rule** says that the compiler can modify a program however it likes in order to produce more optimized code, so long as those modifications do not affect a program’s “observable behavior”. Observable behavior includes:
- The program’s output (e.g., what is printed to the console or written to a file).
- The program’s interactions with the outside world (e.g., reading from or writing to files, network communication, etc.).
- The program’s use of volatile objects (e.g., hardware registers).

#### An optimization opportunity:
Consider the following code snippet:
```cpp
#include <iostream>

int main()
{
	int x { 3 + 4 };
	std::cout << x << '\n';

	return 0;
}
```
In this example, the expression `3 + 4` is a constant expression, meaning its value can be determined at compile time. An optimizing compiler can recognize this and replace the expression with its computed value, resulting in the following optimized code:
```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << x << '\n';
    return 0;
}
```
This optimization does not change the observable behavior of the program, as it still produces the same output. However, it can improve performance by reducing the number of calculations performed at runtime.

#### Compile-time evaluation:
Compile-time evaluation is the process of evaluating expressions and performing computations during the compilation phase, rather than at runtime. This can lead to more efficient code, as certain calculations can be performed once during compilation, rather than repeatedly during program execution. Compile-time evaluation is often used in conjunction with constant expressions, which are expressions that can be evaluated at compile time.

#### Constant folding:
**Constant folding** is a specific optimization technique where the compiler evaluates constant expressions at compile time and replaces them with their computed values. This reduces the number of calculations that need to be performed at runtime, leading to more efficient code. For example, in the previous example, the expression `3 + 4` is a constant expression that can be evaluated at compile time, allowing the compiler to replace it with the value `7`, and not computing it at runtime spending CPU cycles. For example:
```cpp
#include <iostream>
int main()
{
    int x { 3 + 4 }; // constant expression
    std::cout << x << '\n';

    return 0;
}
```
In this example, the compiler can use constant folding to evaluate the expression `3 + 4` at compile time and replace it with the value `7`, resulting in the following optimized code:
```cpp
#include <iostream>
int main()
{
    int x { 7 }; // constant expression replaced with its computed value
    std::cout << x << '\n';
    return 0;
}
```

#### Constant propagation:
**Constant propagation** is an optimization technique where the compiler replaces variables known to have constant values with their values. This can lead to further optimizations, such as enabling constant folding on expressions that involve these constant variables. For example here, without constant propagation:
```cpp
#include <iostream>

int main()
{
	int x { 7 };
	std::cout << x << '\n';

	return 0;
}
```
the value `7` will be store in the memory location allocated for `x`, then retrieved at runtime to be printed, leading to 2 memory accesses.
With constant propagation, the compiler can recognize that `x` is a constant variable with a known value of `7`, and replace its occurrences in the code with the constant value directly:
```cpp
#include <iostream>

int main()
{
	std::cout << 7 << '\n';

	return 0;
}
```
This optimization eliminates the need for memory accesses to store and retrieve the value of `x`, resulting in more efficient code.

In this example:
```cpp
#include <iostream>

int main()
{
	int x { 7 };
	int y { 3 };
	std::cout << x + y << '\n';

	return 0;
}
```
the compiler can use constant propagation to replace `x` and `y` with their constant values, and then apply constant folding to compute the sum at compile time.

#### Dead code elimination:
**Dead code elimination** is an optimization technique where the compiler removes code that may be executed but has no effect on the program’s behavior. This can include variables that are assigned values but never used, or code blocks that are never reached due to control flow. For example:
```cpp
#include <iostream>
int main()
{
    int x { 5 };
    int y { 10 };
    int z { x + y }; // z is assigned a value but never used

    std::cout << x << '\n';

    return 0;
}
```
In this example, the variable `z` is assigned a value but never used in the program. An optimizing compiler can recognize this and eliminate the assignment to `z`, resulting in the following optimized code:
```cpp
#include <iostream>
int main()
{
    int x { 5 };
    int y { 10 };
    std::cout << x << '\n';
    std::cout << y << '\n';

    return 0;
}
```
When a variable is removed from the code, we say it has been **optimized out**.

#### How to help the optimizer:
To help the optimizer perform better optimizations, you can follow these guidelines:
- Use `const` for variables that should not change, allowing the compiler to treat them as constant expressions.
- Write clear and straightforward code, as complex or convoluted code can make it harder for the optimizer to analyze and optimize.
- Avoid unnecessary computations or redundant code, as these can hinder optimization efforts.

For example, one could have written:
```cpp
#include <iostream>

int main()
{
	const int x { 7 }; // x is now const
	std::cout << x << '\n';

	return 0;
}
```
This gives the compiler more information to work with, potentially enabling better optimizations.

#### Optimization can make programs harder to debug:
While optimizations can improve performance, they can also make programs harder to debug. This is because optimizations can change the structure of the code, making it difficult to trace the original source code during debugging. For example, if a variable is optimized out, it may not be available for inspection in the debugger. To mitigate this, debug builds typically leave optimizations disabled to preserve the original code structure for easier debugging.

#### Nomenclature: compile-time constants vs runtime constants:
Constants in C++ can be classified into two categories based on when their values are determined:
- **Compile-time constants**: Constants whose values are known and fixed at compile time. For example:
    - Literals (e.g., `42`, `3.14`, `'A'`, `"Hello"`).
    - `const` variables initialized with constant expressions (e.g., `const int x { 5 + 3 };`).
- **Runtime constants**: Constants whose values are determined at runtime, meaning they can vary each time the program is executed. For example:
    - `const` function parameters (e.g., `void func(const int x)`).
    - `const` variables initialized with non-constant expressions (e.g., `const int y { getValueFromUser() };`).

For example:
```cpp
#include <iostream>

int five()
{
    return 5;
}

int pass(const int x) // x is a runtime constant
{
    return x;
}

int main()
{
    // The following are non-constants:
    [[maybe_unused]] int a { 5 };

    // The following are compile-time constants:
    [[maybe_unused]] const int b { 5 };
    [[maybe_unused]] const double c { 1.2 };
    [[maybe_unused]] const int d { b };       // b is a compile-time constant

    // The following are runtime constants:
    [[maybe_unused]] const int e { a };       // a is non-const
    [[maybe_unused]] const int f { e };       // e is a runtime constant
    [[maybe_unused]] const int g { five() };  // return value isn't known until runtime
    [[maybe_unused]] const int h { pass(5) }; // return value isn't known until runtime

    return 0;
}
```

#### Summary:
- The as-if rule allows compilers to optimize code as long as observable behavior remains unchanged.
- Compile-time evaluation, constant folding, constant propagation, and dead code elimination are common optimization techniques.
- Writing clear and straightforward code can help the optimizer perform better optimizations.

---

### S05 - 5.5 Constant expressions
In a previous lesson, we introduced **expressions** as combinations of operators and operands that produce a value. By default, expressions are evaluated at runtime, and in some cases they must do so:
```cpp
#include <iostream>
int getValueFromUser()
{
    int value{};
    std::cout << "Enter an integer: ";
    std::cin >> value;
    return value;
}
Because input and output operations can only be performed at runtime, any expression that involves them must also be evaluated at runtime.

In some cases, C++ language requires an expression that can be evaluated at compile time. For example, `constexpr` variables must be initialized with constant expressions, which are expressions that can be evaluated at compile time. For example:
```cpp
int main()
{
    constexpr int x { expr }; // Because variable x is constexpr, expr must be evaluatable at compile-time
}
```
If `expr` cannot be evaluated at compile time, the compiler will generate an error. We will discuss `constexpr` variables in more detail in the next lesson.

#### The benefits of compile-time programming:
The as-if rule is great, but it is invisible to us and difficult to control. To overcome this, C++ language provides us with ways to explicitly request compile-time evaluation of expressions, allowing us to write code that is guaranteed to be evaluated at compile time. This is known as **compile-time programming**. Compile-time programming has several benefits:
- **Performance**: By performing computations at compile time, we make our program smaller and faster, as there are fewer calculations to perform at runtime.
- **Versatility**: Compile-time programming allows us to create more flexible and reusable code, as we can define functions and data structures that can be evaluated at compile time.
- **Predictability**: We can have the compiler halt compilation if it determines that code cannot be executed at compile-time, allowing us to catch errors early in the development process.
- **Quality**: We can have the compiler reliably detect certain kinds of programming errors at compile-time, and halt the build if it encounters them. This is much more effective than trying to detect and gracefully handle those same errors at runtime.
- **Quality**: Undefined behavior is not allowed at compile-time, so we can use compile-time programming to eliminate certain kinds of undefined behavior from our code.

The following C++ features are the most foundational for compile-time programming:
- `constexpr` variables
- `constexpr` functions
- Templates
- `static_assert`

All of these have 1 thing in common: they all make use of **constant expressions**.

#### Constant expressions:
A **constant expression** is a non-empty sequence of literals, constant variables, operators, and function calls that **must** be evaluatable at compile time. An expression thta is not a constant expression is called a **non-constant expression** or **runtime expression**.

#### What can be in a constant expression ?
Constant expressions can include:
- **Literals**: such as `42`, `3.14`, `'A', and `"Hello"`.
- Most **operators**: such as arithmetic operators (`+`, `-`, `*`, `/`), comparison operators (`==`, `!=`, `<`, `>`, etc.), and logical operators (`&&`, `||`, `!`).
- **Constant variables**: variables declared with the `const` or `constexpr` keywords that are initialized with constant expressions.
- **`constexpr` functions**: functions declared with the `constexpr` keyword that can be evaluated at compile time when called with constant expressions as arguments.

#### Examples of constant expressions:
In this example, we have several constant expressions:
```cpp
#include <iostream>

int getNumber()
{
    std::cout << "Enter a number: ";
    int y{};
    std::cin >> y; // can only execute at runtime

    return y;      // this return expression is a runtime expression
}

// The return value of a non-constexpr function is a runtime expression
// even when the return expression is a constant expression
int five()
{
    return 5;      // this return expression is a constant expression
}

int main()
{
    // Literals can be used in constant expressions
    5;                           // constant expression
    1.2;                         // constant expression
    "Hello world!";              // constant expression

    // Most operators that have constant expression operands can be used in constant expressions
    5 + 6;                       // constant expression
    1.2 * 3.4;                   // constant expression
    8 - 5.6;                     // constant expression (even though operands have different types)
    sizeof(int) + 1;             // constant expression (sizeof can be determined at compile-time)

    // The return values of non-constexpr functions can only be used in runtime expressions
    getNumber();                 // runtime expression
    five();                      // runtime expression (even though the return expression is a constant expression)

    // Operators without constant expression operands can only be used in runtime expressions
    std::cout << 5;              // runtime expression (std::cout isn't a constant expression operand)

    return 0;
}
```
In here, the expressions `5`, `1.2`, `"Hello world!"`, `5 + 6`, `1.2 * 3.4`, `8 - 5.6`, and `sizeof(int) + 1` are all constant expressions because they consist of literals and operators that can be evaluated at compile time. The expressions `getNumber()` and `five()` are runtime expressions because they involve function calls that cannot be evaluated at compile time. The expression `std::cout << 5` is also a runtime expression because it involves an I/O operation that can only be performed at runtime.

In the following, we define some variables, and indicate whether their initializers are constant expressions or runtime expressions:
```cpp
// Const integral variables with a constant expression initializer can be used in constant expressions:
const int a { 5 };           // a is usable in constant expressions
const int b { a };           // b is usable in constant expressions (a is a constant expression per the prior statement)
const long c { a + 2 };      // c is usable in constant expressions (operator+ has constant expression operands)

// Other variables cannot be used in constant expressions (even when they have a constant expression initializer):
int d { 5 };                 // d is not usable in constant expressions (d is non-const)
const int e { d };           // e is not usable in constant expressions (initializer is not a constant expression)
const double f { 1.2 };      // f is not usable in constant expressions (not a const integral variable)
```

#### When constant expressions are evaluated at compile-time:
Constant expressions are evaluated at compile-time when they are used in contexts that require compile-time evaluation, **not always**. For example:
```cpp
const int x { 3 + 4 }; // constant expression 3 + 4 must be evaluated at compile-time
int y { 3 + 4 };       // constant expression 3 + 4 may be evaluated at compile-time or runtime
```
In this example, the expression `3 + 4` must be evaluated at compile time when initializing the `const int x`, because `x` is a constant variable. However, when initializing the non-constant variable `int y`, the expression `3 + 4` may be evaluated at either compile time or runtime, depending on the compiler's optimization decisions.

#### Summary:
- Constant expressions are expressions that can be evaluated at compile time.
- Constant expressions can include literals, most operators, constant variables, and `constexpr` functions.
- Constant expressions are evaluated at compile time when used in contexts that require compile-time evaluation.
- Constant variables initialized with non-constant expressions cannot be used in constant expressions.
- Const non-integral variables, even when they have a constant expression initializer (e.g. `const double d { 1.2 };`). To use such variables in a constant expression, define them as constexpr variables instead.
- The return values of non-`constexpr` functions are always runtime expressions, even when the return expression is a constant expression.


---

### S06 - 5.6 Constexpr variables
In the previous lesson, we introduced **constant expressions** as expressions that can be evaluated at compile time. In this lesson, we will explore **`constexpr` variables**, which are variables that are guaranteed to be constant expressions.

#### The compile-time `const` challenge:
In C++, the `const` keyword is used to declare variables that cannot be modified after their initialization. However, not all `const` variables are guaranteed to be constant expressions. Namely, a `const` variable with an i**integral type** (e.g., `int`, `char`, `bool`, etc.) and a constant expression initializer can be used in constant expressions, otherwise it cannot. `const` are sometime challenging because:
- It is difficult to understand when a `const` variable can be used in constant expressions and when it cannot.
- `const` does not provide a way to inform the compiler that a variable is intended to be a constant expression.
- The use of `const` to create compile-time constants is limited to integral types only.

To overcome these challenges, C++ provides the `constexpr` keyword, which allows us to declare variables that are guaranteed to be constant expressions, regardless of their type.

#### The `constexpr` keyword:
The `constexpr` keyword (short for "constant expression") is used to declare variables that are guaranteed to be constant expressions. A `constexpr` variable must be initialized with a constant expression, and its value cannot be modified after initialization. For example:
```cpp
#include <iostream>

// The return value of a non-constexpr function is not constexpr
int five()
{
    return 5;
}

int main()
{
    constexpr double gravity { 9.8 }; // ok: 9.8 is a constant expression
    constexpr int sum { 4 + 5 };      // ok: 4 + 5 is a constant expression
    constexpr int something { sum };  // ok: sum is a constant expression

    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    constexpr int myAge { age };      // compile error: age is not a constant expression
    constexpr int f { five() };       // compile error: return value of five() is not constexpr

    return 0;
}
```
In this example, the variables `gravity`, `sum`, and `something` are declared as `constexpr` variables because they are initialized with constant expressions. However, the variable `myAge` cannot be declared as `constexpr` because it is initialized with a non-constant expression (the value of `age` is not known at compile time). Similarly, the variable `f` cannot be declared as `constexpr` because the return value of the non-`constexpr` function `five()` is not a constant expression.

> **Note**: Because functions normally execute at runtime, the return values of non-`constexpr` functions are always runtime expressions, even when the return expression is a constant expression.

Additionally, `constexpr` variables can be of any type, not just integral types. For example:
```cpp
constexpr double d { 1.2 }; // d can be used in constant expressions!
```
This is different from `const` variables, which can only be used in constant expressions if they are of integral type.

#### The meaning of `const` vs `constexpr` for variables:
For variables, the `const` and `constexpr` keywords have different meanings:
- `const` indicates that a variable's value cannot be modified after initialization. However, it does not guarantee that the variable is a constant expression.
- `constexpr` indicates that a variable is guaranteed to be a constant expression, meaning it can be evaluated at compile time. `constexpr` variables are implicitly `const`, so their values cannot be modified after initialization.

> **Note**: Unlike `const`, `constexpr` is not part of an object type; it is a property of the variable itself. So a variable defined as `constexpr int` actually has type `const int`, due to the implicit `const` that `constexpr` provides.

#### `const` and `constexpr` function parameters:
Normal function calls are executed at runtime,  with the supplied arguments being runtime expressions. Because the initialization of function parameters happens at runtime, this leads to two consequences:
- `const` function parameters are treated as runtime constants, meaning their values cannot be modified within the function, but they cannot be used in constant expressions.
- `constexpr` function parameters are not allowed, because function parameters cannot be constant expressions.

#### Nomenclature recap:
- **Compile-time constants**: Constants whose values are known and fixed at compile time. Examples include literals and `const` or `constexpr` variables initialized with constant expressions.
- **Constexpr**: Keyword that declares variables guaranteed to be constant expressions, allowing them to be evaluated at compile time.
- **Constant expressions**: An expression that contains only compile-time constants and operators/functions that support compile-time evaluation.
- **Runtime expressions**: Expressions that cannot be evaluated at compile time, often involving non-constant variables or function calls.
- **Runtime constants**: Constants whose values are determined at runtime, such as `const` function parameters and `const` variables initialized with non-constant expressions.

#### A brief introduction to `constexpr` functions:
A **`constexpr` function** is a function that is declared with the `constexpr` keyword, indicating that it can be evaluated at compile time when called with constant expressions as arguments. `constexpr` functions must have a body that consists of a single return statement or a series of statements that can be evaluated at compile time. We will explore `constexpr` functions in more detail in the next lesson.

For example:
```cpp
#include <iostream>

int max(int x, int y) // this is a non-constexpr function
{
    if (x > y)
        return x;
    else
        return y;
}

constexpr int cmax(int x, int y) // this is a constexpr function
{
    if (x > y)
        return x;
    else
        return y;
}

int main()
{
    int m1 { max(5, 6) };            // ok
    const int m2 { max(5, 6) };      // ok
    constexpr int m3 { max(5, 6) };  // compile error: max(5, 6) not a constant expression

    int m4 { cmax(5, 6) };           // ok: may evaluate at compile-time or runtime
    const int m5 { cmax(5, 6) };     // ok: may evaluate at compile-time or runtime
    constexpr int m6 { cmax(5, 6) }; // okay: must evaluate at compile-time

    return 0;
}
```
In this example, the function `max` is a non-`constexpr` function, so its return value cannot be used to initialize a `constexpr` variable. On the other hand, the function `cmax` is a `constexpr` function, so its return value can be used to initialize a `constexpr` variable when called with constant expressions as arguments, or simply used in constant expressions.

#### Summary:
- `constexpr` variables are guaranteed to be constant expressions and can be evaluated at compile time.
- `constexpr` variables can be of any type, not just integral types.
- `const` function parameters are treated as runtime constants and cannot be used in constant expressions.
- `constexpr` function parameters are not allowed, as function parameters cannot be constant expressions.


---

### S07 - 5.7 Introduction to `std::string`
In a previous lesson, we introduced **C-style string literals**:
```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!"; // "Hello world!" is a C-style string literal.
    return 0;
}
```
While C-style string literals are fine to use, they behave oddly, are hard to work with, and are dangerous. So it is generally better to avoid them.

C++ provides a more powerful and safer way to work with strings through the `std::string` and `std::string_view` (C++17 and later) types, which are part of the C++ Standard Library. `std::string` and `std::string_view`, unlike the previous types we encountered (e.g., `int`, `double`, etc.), are not fundamental types; they are **class types** that encapsulate string data and provide various member functions for string manipulation.

#### Introducing `std::string`:
The easiest way to work with strings objects in C++ is to use the `std::string` class, which is defined in the `<string>` header. `std::string` provides a convenient way to create, manipulate, and manage strings of characters. We can create objects of type `std::string` as follows:
```cpp
#include <string> // allows use of std::string

int main()
{
    std::string name {}; // empty string

    return 0;
}
```
In this example, we include the `<string>` header to gain access to the `std::string` class, and then we create an empty string object named `name`.

Just like normal variables, you can initialize or assign values to `std::string` objects using string literals:
```cpp
#include <string>

int main()
{
    std::string name { "Alex" }; // initialize name with string literal "Alex"
    name = "John";               // change name to "John"

    return 0;
}
```

#### String output with `std::cout`:
You can output `std::string` objects using `std::cout`, just like you would with C-style string literals:
```cpp
#include <iostream>
#include <string>
int main()
{
    std::string greeting { "Hello, world!" };
    std::cout << greeting << '\n'; // output the string

    return 0;
}
```
that will print:
```
Hello, world!
```

Empty strings will just print nothing instead.

#### `std::string` can handle strings of different lengths:
One of the main advantages of `std::string` over C-style string literals is that `std::string` can handle strings of different lengths without the need for manual memory management. You can create `std::string` objects of varying lengths, and the class will automatically manage the memory for you. For example:
```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name { "Alex" }; // initialize name with string literal "Alex"
    std::cout << name << '\n';

    name = "Jason";              // change name to a longer string
    std::cout << name << '\n';

    name = "Jay";                // change name to a shorter string
    std::cout << name << '\n';

    return 0;
}
```
that will print:
```
Alex
Jason
Jay
```

> **Note**: If `std::string` objects grow beyond their current capacity, they will automatically allocate more memory to accommodate the new size. This dynamic resizing is handled internally by the `std::string` class, so you don't have to worry about it.

#### String input with `std::cin`:
You can read input into `std::string` objects using `std::cin`. By default, `std::cin` reads input until it encounters whitespace (spaces, tabs, or newlines). For example:
```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::cin >> name; // this won't work as expected since std::cin breaks on whitespace

    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::cin >> color;

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';

    return 0;
}
```
it will print:
```
Enter your full name: John Doe
Enter your favorite color: Blue
Your name is John and your favorite color is Doe
```
This is because when you use `operator>>` with `std::cin`, it stops reading input as soon as it encounters whitespace. Any characters after the first whitespace are left in the input buffer for subsequent reads (inside `std::cin`). So in this case, `name` only captures "John", and "Doe" remains in the input buffer, which is then read into `color`.

#### Use `std::getline` to read full lines of input:
To read an entire line of input, including spaces, you can use the `std::getline` function from the `<string>` header. `std::getline` requires two inputs:
1. The input stream to read from (e.g., `std::cin`).
2. The `std::string` object to store the input.

For example:
```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::getline(std::cin, name); // read the full line into name
    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::getline(std::cin, color); // read the full line into color

    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';
    return 0;
}
```
that will print:
```
Enter your full name: John Doe
Enter your favorite color: Light Blue
Your name is John Doe and your favorite color is Light Blue
```

#### `std::ws` manipulator:
When using `std::getline` after reading input with `std::cin`, you may encounter issues with leftover newline characters in the input buffer. To address this, you can use the `std::ws` manipulator, which discards any leading whitespace characters (including newlines) from the input stream before reading the next line. For example:
```cpp
#include <iostream>
#include <string>
#include <iomanip>

int main()
{
    std::cout << "Enter your full name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // note: std::ws here
    std::cout << "Enter your favorite color: ";
    std::string color{};
    std::getline(std::cin >> std::ws, color); // note: std::ws here
    std::cout << "Your name is " << name << " and your favorite color is " << color << '\n';
    return 0;
}
```
that will print:
```
Enter your full name: John Doe
Enter your favorite color: Light Blue
Your name is John Doe and your favorite color is Light Blue
```

#### `std::ws` manipulator:
When using `std::getline` after reading input with `std::cin`, you may encounter issues with leftover newline characters in the input buffer. To address this, you can use the `std::ws` manipulator, which tells `std::cin` to discard any leading whitespace characters (including newlines) from the input stream before reading the next line.

Why this is useful?

Consider this example:
```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Pick 1 or 2: ";
    int choice{};
    std::cin >> choice;

    std::cout << "Now enter your name: ";
    std::string name{};
    std::getline(std::cin, name); // note: no std::ws here

    std::cout << "Hello, " << name << ", you picked " << choice << '\n';

    return 0;
}
```
it will give you:
```
Pick 1 or 2: 1
Now enter your name: Hello, , you picked 1
```
This happens because when you enter `1` and press Enter, the newline character (`\n`) remains in the input buffer after reading `choice`. When `std::getline` is called the second time, it immediately encounters this newline character and considers it the end of the input, resulting in an empty string for `name`. By using `std::ws`, you can ensure that any leading whitespace (including the leftover newline) is discarded before reading the next line.

So we can fix the above example like this:
```cpp
#include <iostream>
#include <string>

int main()
{
    std::cout << "Pick 1 or 2: ";
    int choice{};
    std::cin >> choice;

    std::cout << "Now enter your name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // note: added std::ws here

    std::cout << "Hello, " << name << ", you picked " << choice << '\n';

    return 0;
}
```
that will print:
```
Pick 1 or 2: 1
Now enter your name: John Doe
Hello, John Doe, you picked 1
```

#### The length of a `std::string`:
You can determine the length of a `std::string` object using the `length()` member function. This function returns the number of characters in the string. For example:
```cpp
#include <iostream>
#include <string>

int main()
{
    std::string text{"Hello, World!"};
    std::cout << "The length of the string is: " << text.length() << '\n';
    return 0;
}
```
that will print:
```
The length of the string is: 13
```

> **Note**: The returned length of a `std::string` does not include the null terminator character.

A **member function** is a function that is associated with a class and operates on objects of that class. Member functions are defined within the class definition and can access the class's data members (variables) and other member functions. In the case of `std::string`, `length()` is a member function that operates on `std::string` objects to return their length. Since `length()` member function is declared in the `std::string` class, it is sometimes written as `std::string::length()` to indicate that it belongs to the `std::string` class.

> **Note**: `std::string::length()` returns an unsigned integral value (most likely of type `std::size_t`), so if you want to assign the length to an `int` variable, you should `static_cast` it to `int` first to avoid potential issues with signed/unsigned comparisons.

For example:
```cpp
int length { static_cast<int>(name.length()) };
```

#### Initializing a `std::string` is expensive:
Whenever a std::string is initialized, a copy of the string used to initialize it is made. Making copies of strings is expensive, so care should be taken to minimize the number of copies made.

#### Do not pass `std::string` by value:
When passing `std::string` objects to functions. Passing by value creates a copy of the string, which can be expensive in terms of performance, especially for large strings. We will discuss what to do instead (using `std::string_view`) in the next lesson.

#### Returning a `std::string`:
When a function return by value to the caller, the return value is normally copied from the function back to the caller. So you would think to avoid returning `std::string` objects by value. 
However, it is okay to return `std::string` by value when the expresion of the return resolves to any of the following:
- A local `std::string` variable.
- A `std::string` that has been returned by value from another function call.
- A temporary `std::string` object created during the evaluation of the return expression.
This is because modern compilers can apply optimizations (such as Return Value Optimization, or RVO) to eliminate the copy in these cases.

#### Literals for `std::string`:
You can initialize `std::string` objects using C-style string literals (enclosed in double quotes). For example:
```cpp
#include <string>
int main()
{
    std::string greeting { "Hello, world!" }; // initialize with C-style string literal
    return 0;
}
```

However, sometimes it is better to create literals with type `std::string` directly. You can do this by using the `s` suffix (available in C++14 and later) from the `<string>` header. For example:
```cpp
#include <string>
using namespace std::string_literals; // enables the use of the s suffix

int main()
{
    std::string greeting { "Hello, world!" }; // initialize with C-style string literal
    std::string greeting2 { "Hello, world!"s }; // initialize with std::string literal
    return 0;
}
```

#### Constexpr strings:
If you try to declare a `std::string` variable as `constexpr`, you will probably get a compile-time error. This is because `std::string` is not a literal type, and therefore cannot be used in constant expressions. If you need constexpr strings, use `std::string_view` instead (we will cover `std::string_view` in the next lesson).

#### Summary:
- `std::string` is a class type that provides a convenient way to work with strings in C++.
- You can create, manipulate, and manage strings using `std::string` objects.
- Use `std::getline` to read full lines of input into `std::string` objects.
- Use `std::ws` manipulator to discard leading whitespace when reading input with `std::getline`.
- Use the `length()` member function to determine the length of a `std::string`.
- Avoid passing `std::string` by value to functions to prevent unnecessary copies.


---

### S08 - 5.8 Introduction to `std::string_view`
Consider the following program:
```cpp
#include <iostream>

int main()
{
    int x { 5 }; // x makes a copy of its initializer
    std::cout << x << '\n';

    return 0;
}
```
When the definition of `x` is executed, the initialized value `5` is copied into the memory allocated for variable `int x`. For fundamental types like `int`, this copy operation is inexpensive. However, for complex types like `std::string`, copying can be expensive in terms of performance, especially for large strings.

Now consider this program:
```cpp
#include <iostream>
#include <string>

int main()
{
    std::string s{ "Hello, world!" }; // s makes a copy of its initializer
    std::cout << s << '\n';

    return 0;
}
```
When the definition of `s` is executed, the C-style string literal `"Hello, world!"` is copied into the memory allocated for the `std::string` object `s`. Unlike fundamental types, initializing a `std::string` is **slow**. We have basically made a copy of the literal to just print it out. This is inefficient!

#### The solution: `std::string_view` (C++17 and later)
To address the performance issues associated with copying `std::string` objects, C++17 introduced the `std::string_view` class, which is defined in the `<string_view>` header. `std::strin_view` provides **read-only** access to an **existing string** (a C-style string, a `std::string`, or another `std::string_view`) without making a copy of the string data. This makes `std::string_view` much more efficient for scenarios where you only need to read or inspect a string without modifying it. For example:
```cpp
#include <iostream>
#include <string_view> // C++17

// str provides read-only access to whatever argument is passed in
void printSV(std::string_view str) // now a std::string_view
{
    std::cout << str << '\n';
}

int main()
{
    std::string_view s{ "Hello, world!" }; // now a std::string_view
    printSV(s);

    return 0;
}
```
In this example, **no copies** of the string data are made when creating the `std::string_view` object `s` or when passing it to the `printSV` function. Instead, `std::string_view` simply provides a view into the existing string data, allowing us to read and print it efficiently.

> **Best practice**: Prefer using `std::string_view` over `std::string` when you need read-only string, especially for function parameters. This can help improve performance by avoiding unnecessary copies of string data.

#### `std::string_view` can be initialized with many different types of strings:
`std::string_view` can be initialized with various types of strings, including:
- C-style string literals.
- `std::string` objects.
- Other `std::string_view` objects.

For example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string_view s1 { "Hello, world!" }; // initialize with C-style string literal
    std::cout << s1 << '\n';

    std::string s{ "Hello, world!" };
    std::string_view s2 { s };  // initialize with std::string
    std::cout << s2 << '\n';

    std::string_view s3 { s2 }; // initialize with std::string_view
    std::cout << s3 << '\n';

    return 0;
}
```

#### `std::string_view` parameters will accept many different types of string arguments:
When you define a function that takes a `std::string_view` parameter, you can pass in various types of string arguments, including C-style string literals, `std::string` objects, and other `std::string_view` objects. Both C-style string literals and `std::string` objects will be implicitly converted to `std::string_view` when passed to the function. For example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

void printSV(std::string_view str)
{
    std::cout << str << '\n';
}

int main()
{
    printSV("Hello, world!"); // call with C-style string literal

    std::string s2{ "Hello, world!" };
    printSV(s2); // call with std::string

    std::string_view s3 { s2 };
    printSV(s3); // call with std::string_view

    return 0;
}
```
In this example, the `printSV` function can accept different types of string arguments without making copies of the string data, thanks to `std::string_view`.

#### `tsd::string_view` will not implicitly convert to `tsd::string`:
While `std::string` objects can be implicitly converted to `std::string_view`, the reverse is not true. `std::string_view` objects cannot be implicitly converted to `std::string` objects. This is to prevent accidental copies of string data, which would negate the performance benefits of using `std::string_view`, if done unintentionally.

However, if this is deired, we ahve two options:
1. Explicitly create a `std::string` object from a `std::string_view`, since this will rarely be done intentionally.
2. Convert an existing `std::string_view` to a `std::string` by using `static_cast`:

For example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

void printString(std::string str)
{
	std::cout << str << '\n';
}

int main()
{
	std::string_view sv{ "Hello, world!" };

	// printString(sv);   // compile error: won't implicitly convert std::string_view to a std::string

	std::string s{ sv }; // okay: we can create std::string using std::string_view initializer
	printString(s);      // and call the function with the std::string

	printString(static_cast<std::string>(sv)); // okay: we can explicitly cast a std::string_view to a std::string

	return 0;
}
```

#### Assignment changes what the `std::string_view` is viewing:
When you assign a new value to a `std::string_view` object, you are changing what string data it is viewing. The original string data **remains unchanged**; only the view is updated to point to the new string data. For example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string name { "Alex" };
    std::string_view sv { name }; // sv is now viewing name
    std::cout << sv << '\n'; // prints Alex

    sv = "John"; // sv is now viewing "John" (does not change name)
    std::cout << sv << '\n'; // prints John

    std::cout << name << '\n'; // prints Alex

    return 0;
}
```
This will print:
```
Alex
John
Alex
```
this because when we assigned `"John"` to `sv`, we changed what `sv` was viewing, but the original string `name` remained unchanged.

#### Literals for `std::string_view`:
Double-quoted string literals are C-style string literals by default. However, you can create string literals with type `std::string_view` directly by using the `sv` suffix (available in C++17 and later) from the `<string_view>` header. For example:
```cpp
#include <iostream>
#include <string>      // for std::string
#include <string_view> // for std::string_view

int main()
{
    using namespace std::string_literals;      // access the s suffix
    using namespace std::string_view_literals; // access the sv suffix

    std::cout << "foo\n";   // no suffix is a C-style string literal
    std::cout << "goo\n"s;  // s suffix is a std::string literal
    std::cout << "moo\n"sv; // sv suffix is a std::string_view literal

    return 0;
}
```

> **Note**: It is fine to initialize a `std::string_view` with a C-style string literal (without the `sv` suffix), it will work anyways.

#### Constexpr `std::string_view`:
Unlike `std::string`, `std::string_view` has full support for constexpr. This means you can declare `std::string_view` variables as `constexpr`, allowing them to be used in constant expressions. For example:
```cpp
#include <iostream>
#include <string_view>
int main()
{
    constexpr std::string_view sv { "Hello, constexpr string_view!" };  // ok: std::string_view supports constexpr
    std::cout << sv << '\n';  // sv will be replaced with the string literal at compile-time

    return 0;
}
```
In this way, `std::string_view` can be used in compile-time contexts, and here the `sv` variable will be replaced with the string literal at compile-time.

#### Summary:
- `std::string_view` provides read-only access to existing string data without making copies.
- Prefer using `std::string_view` over `std::string` for read-only strings, especially for function parameters.
- `std::string_view` can be initialized with C-style string literals, `std::string` objects, and other `std::string_view` objects.
- `std::string_view` parameters can accept various types of string arguments without making copies.
- `std::string_view` objects cannot be implicitly converted to `std::string` objects.
- Assigning a new value to a `std::string_view` changes what it is viewing, not the original string data.
- `std::string_view` supports `constexpr`, allowing it to be used in constant expressions.


---

### S09 - 5.9 `std::string_view` (part 2)
In the previous lesson, we introduced the `std::string_view` class, which provides read-only access to existing string data without making copies. Since `std::string_view` is the first view type we have encountered, in this lesson we will explore how to use it safely, provide some examples of how can be used incorrectly, and some generic guidelines for using it effectively, and when to use `std::string` or `std::string_view`.

#### `std::string` is a (sole) owner:
You might be wondering why `std::string` makes an expensive copy of its initializer.When an object is instatiated, memory is **allocated** for that specific object to store its data. This memory is **reserved** for that object alone, as long as the object exists. It is a safe space. `std::string`, and most of other objects, copy the initialization value into their own reserved memory space to ensure that they have full control over their data. This way, the `std::string` object is the **sole owner** of its data, and it can manage it independently without relying on external sources.

This is good because the initializer can go out of scope, be modified, or be deleted without affecting the `std::string` object. The `std::string` object can safely manage its own data without worrying about external changes. The downside is that copying data can be expensive, especially for large strings.

> **Note**: Independence of object comes at the cost of performance due to copying.

#### We don't always need a copy:
In many scenarios, we don't need to modify the string data, and we only need to read or inspect it. In such cases, making a copy of the string data is unnecessary and inefficient. From a previous example:
```cpp
#include <iostream>
#include <string>

void printString(std::string str) // str makes a copy of its initializer
{
    std::cout << str << '\n';
}

int main()
{
    std::string s{ "Hello, world!" };
    printString(s);

    return 0;
}
```
In this example, the `printString` function takes a `std::string` parameter, which makes a copy of the string, prints it, and then the copy is destroyed when the function exits. This copying is unnecessary because we only need to read the string data without modifying it.

Could we just use the string that `s` is holding directly inside the function? Possibly, given the following criteria:
- Could `s` be destroyed while `str` is still in use? No, because `s` is in the caller's scope and will remain valid for the duration of the function call.
- Could `s` be modified while `str` is still in use? No, because `s` is not modified in this example, and we only need read access.
- Does `str` modify the string in some way? No, `str` only reads and prints the string.

Since all the criteria are false, we can safely avoid making a copy of the string data.

#### `std::string_view` is a viewer, not an owner:
`std::string_view` takes a different approach to initialization. Instead of making an expensive copy of the string data, it creates an **inexpensive view** of the initialization string. This view provides read-only access to the existing string data **without taking ownership** of the data. This means that `std::string_view` does not manage the memory of the string data; it simply points to the existing data.

> **Note**: if the original string data goes out of scope, is modified, or deleted, the `std::string_view` will be left with a dangling pointer, leading to undefined behavior if accessed.

#### `std::string_view` is best used as a read-only function parameter:
The most common and recommended use case for `std::string_view` is as a **read-only function parameter**. By using `std::string_view` as a function parameter, we can avoid unnecessary copies of string data while still providing read access to the string. For example:
```cpp
#include <iostream>
#include <string_view>

void printString(std::string_view str)
{
    std::cout << str << '\n';
}

int main()
{
    std::string s{ "Hello, world!" };
    printString(s);          // pass std::string
    printString("Goodbye!"); // pass C-style string literal

    return 0;
}
```
In this example, the `printString` function takes a `std::string_view` parameter, allowing it to accept both `std::string` objects and C-style string literals without making copies of the string data.

Then, what should I prefer?
> Prefer `std::string_view` in most cases, we will cover this in a later chapter.

#### Improperly using `std::string_view`:
Let's have a look at some examples of improper use of `std::string_view` that can lead to undefined behavior.

First, consider this example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string_view sv{};

    { // create a nested block
        std::string s{ "Hello, world!" }; // create a std::string local to this nested block
        sv = s; // sv is now viewing s
    } // s is destroyed here, so sv is now viewing an invalid string

    std::cout << sv << '\n'; // undefined behavior

    return 0;
}
```
In this example, the `std::string` object `s` is created within a nested block and goes out of scope when the block ends. The `std::string_view` object `sv` is assigned to view `s`, but after the block ends, `s` is destroyed, leaving `sv` with a dangling pointer. Accessing `sv` after this point results in undefined behavior.

Here is another version of the same mistake:
```cpp
#include <iostream>
#include <string>
#include <string_view>

std::string getName()
{
    std::string s { "Alex" };
    return s;
}

int main()
{
  std::string_view name { getName() }; // name initialized with return value of function
  std::cout << name << '\n'; // undefined behavior

  return 0;
}
```
In this example, the `getName` function returns a `std::string` object by value. When `getName` is called, a temporary `std::string` object is created and returned. The `std::string_view` object `name` is initialized to view this temporary string. However, the temporary string is destroyed at the end of the full expression, leaving `name` with a dangling pointer. Accessing `name` results in undefined behavior.

The following is a less-obvious variant of the same mistake:
```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    using namespace std::string_literals;
    std::string_view name { "Alex"s }; // "Alex"s creates a temporary std::string
    std::cout << name << '\n'; // undefined behavior

    return 0;
}
```
In this example, the string literal `"Alex"s` creates a temporary `std::string` object. The `std::string_view` object `name` is initialized to view this temporary string. However, the temporary string is destroyed at the end of the full expression, leaving `name` with a dangling pointer. Accessing `name` results in undefined behavior.

We can aslo get undefined behavior by modifying the underlying string data that a `std::string_view` is viewing. For example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string s { "Hello, world!" };
    std::string_view sv { s }; // sv is viewing s

    s[0] = 'h'; // modify the underlying string data

    std::cout << sv << '\n'; // undefined behavior

    return 0;
}
```
In this example, the `std::string` object `s` is modified after the `std::string_view` object `sv` is created to view it. Modifying the underlying string data can lead to undefined behavior when accessing the `std::string_view`, as it may no longer accurately represent the string data.

#### Revalidating an invalid `std::string_view`:
If you find yourself in a situation where a `std::string_view` has become invalid (e.g., due to the original string going out of scope), you can revalidate it by assigning it to a valid string. For example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string s { "Hello, world!" };
    std::string_view sv { s }; // sv is now viewing s

    s = "Hello, universe!";    // modifies s, which invalidates sv (s is still valid)
    std::cout << sv << '\n';   // undefined behavior

    sv = s;                    // revalidate sv: sv is now viewing s again
    std::cout << sv << '\n';   // prints "Hello, universe!"

    return 0;
}
```
In this example, after modifying the original string `s`, the `std::string_view` `sv` becomes invalid. To revalidate `sv`, we assign it to `s` again, which updates `sv` to view the current contents of `s`.

#### Be careful returning a `std::string_view` from a function:
`std::string_view` can be returned from functions, but it is generally dangerous. Because local variables are destroyed at the end of the function scope, returning a `std::string_view` that views a local variable will lead to undefined behavior. For example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

std::string_view getBoolName(bool b)
{
    std::string t { "true" };  // local variable
    std::string f { "false" }; // local variable

    if (b)
        return t;  // return a std::string_view viewing t

    return f; // return a std::string_view viewing f
} // t and f are destroyed at the end of the function

int main()
{
    std::cout << getBoolName(true) << ' ' << getBoolName(false) << '\n'; // undefined behavior

    return 0;
}
```
In this example, the `getBoolName` function returns a `std::string_view` that views local `std::string` variables `t` and `f`. Since these variables are destroyed at the end of the function, the returned `std::string_view` objects become invalid, leading to undefined behavior when accessed in `main`.

There are two main cases where returning a `std::string_view` from a function is safe:
1. Returning a C-style string literal as a `std::string_view`, since C-style literals have static storage duration and remain valid for the lifetime of the program. For example:
    ```cpp
    #include <iostream>
    #include <string_view>

    std::string_view getBoolName(bool b)
    {
        if (b)
            return "true";  // return a std::string_view viewing "true"

        return "false"; // return a std::string_view viewing "false"
    } // "true" and "false" are not destroyed at the end of the function

    int main()
    {
        std::cout << getBoolName(true) << ' ' << getBoolName(false) << '\n'; // ok

        return 0;
    }
    ```
    prints:
    ```
    true false
    ```
2. Return a function parameter that is a `std::string_view`, since the caller is responsible for ensuring that the original string data remains valid for the duration of the `std::string_view` usage. For example:
    ```cpp
    #include <iostream>
    #include <string_view>

    std::string_view echoString(std::string_view str)
    {
        return str; // return the same std::string_view passed in
    }

    int main()
    {
        std::string s { "Hello, world!" };
        std::cout << echoString(s) << '\n'; // ok

        return 0;
    }
    ```
    prints:
    ```
    Hello, world!
    ```

#### View modification functions:
`std::string_view` provides several member functions that allow you to create new views based on modifications of the original view. These functions do not modify the underlying string data; instead, they return new `std::string_view` objects that represent different portions of the original string. Some of these functions include:
- `remove_prefix(size_t n)`: Removes the first `n` characters from the view.
- `remove_suffix(size_t n)`: Removes the last `n` characters from the view.
- `substr(size_t pos = 0, size_t count = npos)`: Returns a new `std::string_view` that represents a substring starting at position `pos` and of length `count`.
For example:
```cpp
#include <iostream>
#include <string_view>

int main()
{
	std::string_view str{ "Peach" };
	std::cout << str << '\n';

	// Remove 1 character from the left side of the view
	str.remove_prefix(1);
	std::cout << str << '\n';

	// Remove 2 characters from the right side of the view
	str.remove_suffix(2);
	std::cout << str << '\n';

    // Create a new view that is a substring of the original view
	std::string_view subview = str.substr(1, 2);
	std::cout << subview << '\n';

    str = "Peach"; // reset the view
	std::cout << str << '\n';

	return 0;
}
```
that will print:
```
Peach
each
ea
Peach
```

> **Note**: `std::string_view::npos` can view substring, without copying a variable.

#### `std::string_view` may or may not be null-terminated:
Unlike C-style strings and `std::string` objects, `std::string_view` does not guarantee null-termination. A `std::string_view` is simply a view into a sequence of characters, and it does not require a null terminator to indicate the end of the string. This means that when working with `std::string_view`, you should not assume that it is null-terminated. If you need a null-terminated string, you may need to create a `std::string` object from the `std::string_view`. 

For example, considering the string `snowball`, if a `std::string_view` is created to view the whole string, then it is viewing a null-terminated string. However, if a `std::string_view` is created to view only a portion of the string (e.g., the first four characters), then it is not null-terminated. 

> **Note**: C-style string literal and `std::string` are always null-terminated, while `std::string_view` may or may not be null-terminated.

#### A quick guide on when to use `std::string` vs `std::string_view`:
**Varibles:**
Use a `std::string` variable when:
- You need a string that you can modify (e.g., append, erase, replace).
- You need to store user input or dynamically generated strings.
- You need to store the return value of a function that returns a `std::string`.

Use a `std::string_view` variable when:
- You need a read-only access to part or all of a string that alredy exists elsewhere and will not be modified or destroyed while the `std::string_view` is in use.
- You need a symbolic constant for a C-style string literal.
- You need to continue viewing the return value of a function that returns a C-style string literal or a non-dangling `std::string_view`.

**Function parameters:**
Use a `std::string` parameter when:
- The function needs to modify the string data passed as an arguemnt without affecting the caller's string. This is quite rare.
- You are using langauge standard C++14 or earlier (before C++17) and you are not confortable in using references yet.

Use a `std::string_view` parameter when:
- The function only needs read-only access to the string data passed as an argument.
- The function needs to work with non-null-terminated strings.

**Return types:**
Use a `std::string` return type when:
- The return value is a `std::string` local variable or function parameter.
- The return value is a function call or operator that return a `std::string` by value.

Use a `std::string_view` return type when:
- The function return a C-style string literal or local `std::string_view` parameter that has been initialized with a C-style string literal or a non-dangling `std::string_view`.
- The function return a `std::string_view` parameter.

#### What to remember:
Things to remember about `std::string`:
- Initializing and copying `std::string` is expensive, so avoid this as much as possible.
- Avoid passing `std::string` by value, as this makes a copy.
- If possible, avoid creating short-lived `std::string` objects.
- Modifying a `std::string` will invalidate any views to that string.
- It is okay to return a local `std::string` by value.
- `std::string` is a mutable sequence of characters.
- It is always null-terminated.
- It manages its own memory and can grow or shrink as needed.
- It is safe to use with C-style strings and can be easily converted to and from them.

Things to remember about `std::string_view`:
- `std::string_view` is typically used for passing string function parameters and returning string literals.
- Because C-style string literals exist for the entire program, it is always okay to set a `std::string_view` to a C-style string literal.
- When a string is destroyed, all views to that string are invalidated.
- Using an invalidated view (other than using assignment to revalidate the view) will cause undefined behavior.
- A `std::string_view` may or may not be null-terminated.
- `std::string_view` is a lightweight, non-owning view into a sequence of characters.
- It does not manage memory and does not own the underlying string data.
- It is useful for read-only access to strings and can be used with non-null-terminated strings.

#### Summary:
- `std::string_view` provides read-only access to existing string data without making copies.
- Prefer using `std::string_view` over `std::string` for read-only strings, especially for function parameters.
- Be cautious when using `std::string_view` to avoid dangling pointers and undefined behavior.
- Follow guidelines for when to use `std::string` vs `std::string_view` for variables, function parameters, and return types.


---

### SX - 5.x Summary and quiz
Have a look at the exercises for this chapter in the course. Then, you will find solution of question 4 inside the `exercises/sx-question4` folder.

Have fun! :)


---

## 🧭 Summary
TODO: write summary


### 🧱 Core Concepts You Mastered:
TODO: write core concepts