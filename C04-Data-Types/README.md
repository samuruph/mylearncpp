# Chapter 04 — Fundamental Data Types

## Overview
In this chapter, you’ll dive deep into the **fundamental data types** that form the backbone of every C++ program.  
Before we can build complex data structures or algorithms, we must understand how data is represented and manipulated at the most basic level — as **bits, bytes, and memory**.

You’ll learn:
- how C++ represents different **kinds of data** (numbers, characters, booleans, etc.),
- how **memory and data size** influence performance and precision,
- the difference between **signed and unsigned integers**, and why the latter can be dangerous,
- what **floating-point numbers** are and why they can’t always represent decimals exactly,
- and how to safely **convert between types** using `static_cast`.

By the end of this chapter, you’ll have a solid understanding of how computers store, interpret, and operate on data — the essential foundation for mastering control flow, arithmetic, and object-oriented programming later on.


---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch04_first
./build/ch04_first
```


---

## 🎯 Learning Outcomes

By completing this chapter, you’ll be able to:

- 🧠 **Understand how data is stored** in memory as bits and bytes, and what “data type” really means.  
- 🔢 **Identify and use fundamental C++ types**, such as `int`, `float`, `double`, `char`, `bool`, and `void`.  
- 📏 **Use `sizeof`** to inspect object and type sizes, and explain how architecture affects data representation.  
- ⚖️ **Differentiate between signed and unsigned integers**, and understand why signed arithmetic is safer.  
- 🧱 **Apply fixed-width integer types** (`std::int32_t`, `std::uint64_t`, etc.) for precise and portable code.  
- 🧮 **Represent and read numbers in scientific notation** for large or small magnitudes.  
- 🌊 **Work confidently with floating-point types**, understanding rounding errors, precision, and `NaN`/`Inf`.  
- 🚦 **Use booleans and if-statements** to control program flow with clear logical expressions.  
- 🔤 **Manipulate character data** using `char`, ASCII codes, and escape sequences.  
- 🧩 **Perform safe type conversions** using `static_cast` to prevent implicit data loss or confusion.


---

## Sections

### S01 — 4.1 Introduction to fundamental data types
In this section, we will explore the concept of data types in C++. We will cover the following topics:
- Bits, bytes, and memory addressing
- Data types
- Fundamental data types
- Integer vs integral types
- Other sets of types
- The _t suffix

#### Bits, bytes, and memory addressing:
When a variable is defined, a piece of memory is reserved to hold the value of that variable. To start understanding a bit how the memory works, here some definitions:
- **Binary digit (bit)**: the smallest unit of data in a computer, represented as either 0 or 1.
- **Byte**: a group of 8 bits. A byte can represent 256 different values (from 0 to 255).
- **Memory address**: a unique identifier for a byte in memory, that are organized into sequential addresses. Each byte has its own address, which is typically represented as a hexadecimal number.

#### Data types:
A **data type** tells the compiler how to interpret the contents of memory. It defines the type of data that can be stored in a variable, the operations that can be performed on that data, and how much memory is allocated for that variable.

#### Fundamental data types:
Here some basic data types:
| Data Type | Size (bytes) | Description                          | Example Values          |
|-----------|--------------|--------------------------------------|-------------------------|
| `int`     | 4            | Integer numbers                      | -3, 0, 42              |
| `float`   | 4            | Single-precision floating-point numbers | 3.14, -0.001, 2.0      |
| `double`  | 8            | Double-precision floating-point numbers | 3.141592653589793, -0.0000001 |
| `char`    | 1            | Single character                    | 'a', 'Z', '0', '$'     |
| `bool`    | 1            | Boolean values (true or false)      | true, false           |
| `void`    | 0            | Represents no value or type         | N/A                     |

#### Integer vs integral types:
An integer is a whole number (no fractional part), while integral types are data type "similar to integers" that can represent whole numbers. In C++, integral types include `int`, `char`, `short`, `long`, and their unsigned variants.

- **Standard integer types**: `int`, `short`, `long`, `long long`, including their signed and unsigned variants.
- **Integral types**: `char`, `bool`, and the standard integer types. 

All integral types are stored in memory as integer types, but only the integer types will be represented as integer numbers when printed.

#### Other sets of types:
C++ containes three sets of types:
- **Fundamental types**: the basic data types provided by the language (e.g., `int`, `float`, `char`, etc.).
- **Compound types**: types that are composed of multiple fundamental types (e.g., arrays, structures, classes, etc.).
- **Standard library types**: types provided by the C++ Standard Library (e.g., `std::string`, `std::vector`, etc.). These need the library to be included.

#### The _t suffix:
The `_t` suffix stands for "type" and is often used in type definitions to indicate that the name represents a type. For example, `uint32_t` is an unsigned 32-bit integer type, or `std::nullptr_t` is a type that can hold a null pointer value.

#### Summary:
- Values are stored in memory as bits and bytes, each byte having a unique memory address.
- A data type tells the compiler how to interpret the contents of memory.
- Fundamental data types include `int`, `float`, `double`, `char`, `bool`, and `void`.
- Integral types are data types that can represent whole numbers, including `int`, `char`, `short`, `long`, and their unsigned variants.
- C++ contains three sets of types: fundamental types, compound types, and standard library types.
- The `_t` suffix stands for "type" and is often used in type definitions to indicate that the name represents a type.


---

### S02 — 4.2 Void
**Void** is the easiest data type to understand, as it represents the absence of a value or type (i.e., "no type")and it is part of the **incomplete types**. 

An **incomplete type** is a type that has been declared but not yet defined. Incomplete types cannot be used to create objects or variables (can not be instantiated), for example this will not work:
```cpp

void value; // won't work, variables can't be defined with incomplete type void
```


#### Functions that do not return a value:
The most common use of `void` is in functions that do not return a value. When a function is declared with a return type of `void`, it indicates that the function does not return any value to the caller. For example:
```cpp
void printMessage() {
    std::cout << "Hello, World!" << std::endl;
}
```
In this example, the `printMessage` function does not return any value, and its return type is specified as `void`.


#### Other uses of void:
Another use of `void` is in pointer types. A `void*` pointer is a special type of pointer that can point to any data type, but it cannot be dereferenced directly. For example:
```cpp
void* ptr;
int x = 42;
ptr = &x; // ptr now points to an int
```
If you do not understand pointers yet, don't worry, they will be covered in a later chapter.

#### Summary:
- `void` represents the absence of a value or type.
- It is part of the incomplete types, which cannot be instantiated.
- It is commonly used in functions that do not return a value.
- It can also be used in pointer types, such as `void*`, which can point to any data type but cannot be dereferenced directly.


---

### S03 — 4.3 Object sizes and sizeof operator

#### Object sizes:
The size of an object in C++ is determined by its data type and the architecture of the system. Different data types have different sizes, which can vary depending on the system architecture (e.g., 32-bit vs 64-bit systems) and can use 1, 2, 4, 8 or even more memory bytes.

A single bit value can hold 2 possible values (0 or 1). With 2 bits, you can represent 4 possible values (00, 01, 10, 11). With 3 bits, you can represent 8 possible values (000 to 111). An 8-bit byte can represent 256 possible values (00000000 to 11111111). In general, with **n bits**, you can represent **2^n possible values**.

#### Fundamental data type sizes:
C++ standards does not define the exact size (in bits) of any fundamental data type, but it does define some rules:
- An object must ofccupy **at least 1 byte** of memory.
- A byte must be at least **8 bits**.
- The integral types `char`, `short`, `int`, `long`, and `long long` have a minimum size of 8, 16, 16, 32, and 64 bits respectively.
- `char` and `char8_t` are exactly 1 byte (8 bits).

In the following we will make these assumptions:
- A byte is 8 bits.
- Memory is addressed by bytes.
- Floating point support is IEEE-754 compliant.
- We are on a 32-bit or 64-bit architecture.

Given these assumptions, here the typical sizes of the fundamental data types:
| Category        | Data Type       | Minimum Size (bytes) | Typical Size (bytes) | Description                          | Example Values          |
|-----------------|-----------------|----------------------|----------------------|--------------------------------------|-------------------------|
| Boolean        | `bool`          | 1                    | 1                    | Boolean values (true or false)      | true, false              |
| Character      | `char`          | 1                    | 1                    | Single character                    | 'a', 'Z', '0', '$'     |
|                | `wchar_t`       | 1                    | 2 or 4               | Wide character                      | L'a', L'Z', L'0', L'$' |
|                | `char8_t`       | 1                    | 1                    | UTF-8 character                     | u8'a', u8'Z', u8'0', u8'$' |
|                | `char16_t`      | 2                    | 2                    | UTF-16 character                    | u'a', u'Z', u'0', u'$' |
|                | `char32_t`      | 4                    | 4                    | UTF-32 character                    | U'a', U'Z', U'0', U'$' |
| Integral       | `short`         | 2                    | 2                    | Short integer numbers               | -32768 to 32767         |
|                | `int`           | 2                    | 4                    | Integer numbers                     | -2147483648 to 2147483647 |
|                | `long`          | 4                    | 4 or 8               | Long integer numbers                | -2147483648 to 2147483647 (32-bit) or -9223372036854775808 to 9223372036854775807 (64-bit) |
|                | `long long`     | 8                    | 8                    | Long long integer numbers           | -9223372036854775808 to 9223372036854775807 |
| Floating Point | `float`         | 4                    | 4                    | Single-precision floating-point numbers | 3.14, -0.001, 2.0      |
|                | `double`        | 8                    | 8                    | Double-precision floating-point numbers | 3.141592653589793, -0.0000001 |
|                | `long double`   | 8                    | 8, 12, or 16      | Extended-precision floating-point numbers | 3.14159265358979323846 |
| Pointer        | `std::nullptr_t` | 4              | 4 or 8               | Type of the null pointer literal `nullptr` | N/A                     |

#### The sizeof operator:
The `sizeof` operator is a compile-time unary operator that returns the size (in bytes) of a data type or object. It can be used to determine the size of fundamental data types, user-defined types, and arrays. The syntax for using the `sizeof` operator is as follows:
```cpp
sizeof(type)
```

If you run this code:
```cpp
#include <iomanip> // for std::setw (which sets the width of the subsequent output)
#include <iostream>
#include <climits> // for CHAR_BIT

int main()
{
    std::cout << "A byte is " << CHAR_BIT << " bits\n\n";

    std::cout << std::left; // left justify output

    std::cout << std::setw(16) << "bool:" << sizeof(bool) << " bytes\n";
    std::cout << std::setw(16) << "char:" << sizeof(char) << " bytes\n";
    std::cout << std::setw(16) << "short:" << sizeof(short) << " bytes\n";
    std::cout << std::setw(16) << "int:" << sizeof(int) << " bytes\n";
    std::cout << std::setw(16) << "long:" << sizeof(long) << " bytes\n";
    std::cout << std::setw(16) << "long long:" << sizeof(long long) << " bytes\n";
    std::cout << std::setw(16) << "float:" << sizeof(float) << " bytes\n";
    std::cout << std::setw(16) << "double:" << sizeof(double) << " bytes\n";
    std::cout << std::setw(16) << "long double:" << sizeof(long double) << " bytes\n";

    return 0;
}
```
You should get an output similar to this (may vary depending on the architecture):
```
bool:           1 bytes
char:           1 bytes
short:          2 bytes
int:            4 bytes
long:           4 bytes
long long:      8 bytes
float:          4 bytes
double:         8 bytes
long double:    8 bytes
```

`sizeof` does not include dynamic allocated memory used by an object (we will discuss dynamic memory allocation in a later chapter).

#### Summary:
- The size of an object in C++ is determined by its data type and the architecture of the system.
- Different data types have different sizes, which can vary depending on the system architecture (e.g., 32-bit vs 64-bit systems).
- The C++ standard defines minimum sizes for fundamental data types, but typical sizes can vary.
- The `sizeof` operator is a compile-time unary operator that returns the size (in bytes) of a data type or object.


---

### S04 — 4.4 Signed integers
An **integer** is an integral type that can represent positive and negative whole numbers. In C++, integers can be either signed or unsigned. A **signed integer** can represent both positive and negative values, while an **unsigned integer** can only represent non-negative values (zero and positive values).

#### Common signed integer types in C++:
- `short int`: Represents a signed short integer (16 bits).
- `int`: Typically represents a signed integer (16 bits, but typically 32 bits on modern systems).
- `long int`: Represents a signed long integer (32 bits).
- `long long int`: Represents a signed long long integer (64 bits).

The main difference is that they have varying sizes, and larger integers can represent a wider range of values.

#### Signed integers:
By default, integer types in C++ are signed. This means that they can represent both positive and negative values. The range of values that a signed integer can represent depends on its size (in bytes) and the system architecture. For example, a signed 32-bit integer can represent values from -2,147,483,648 to 2,147,483,647.

#### Defining signed integers:
You can define signed integers using the following syntax:
```cpp
short s;      // prefer "short" instead of "short int"
int i;
long l;       // prefer "long" instead of "long int"
long long ll; // prefer "long long" instead of "long long int"
```
You can also use the `signed` keyword explicitly, but it is not necessary since integers are signed by default:
```cpp
signed short s;
signed int i;
signed long l;
signed long long ll;
```

#### Signed integrer ranges:
As your learned in the previous section, a variable with **n bits** can represent **2^n possible values**. These values will fall into a **range**, that is determined by two factors:
- its size (in bits)
- whether it is signed or unsigned

For example, a signed 8-bit integer can represent values from -128 to 127, while an unsigned 8-bit integer can represent values from 0 to 255.

This is beacuse one bit is used to represent the sign of the number (0 for positive, 1 for negative), leaving **n-1 bits** to represent the magnitude of the number. Therefore, a signed integer with **n bits** can represent values from **-2^(n-1)** to **2^(n-1) - 1**. The last -1 is because 0 is included in the positive range.

Here the ranges for common signed integer types:
| Data Type       | Size (bits) | Range                          |
|-----------------|--------------|--------------------------------|
| `short`         | 16           | -32,768 to 32,767               |
| `int`           | 32           | -2,147,483,648 to 2,147,483,647     |
| `long`          | 32 or 64      | -2,147,483,648 to 2,147,483,647 (32-bit) or -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 (64-bit) |

#### Overflow:
When a signed integer exceeds its maximum or minimum value, it results in an **overflow**. This can lead to unexpected behavior, as the value wraps around to the opposite end of the range. 

For example, if you have a signed 32-bit integer with a maximum value of 2,147,483,647 and you add 1 to it, the result will be -2,147,483,648 (the minimum value for a signed 32-bit integer). This is because the value wraps around to the opposite end of the range.
```cpp
#include <iostream>

int main()
{
    // assume 4 byte integers
    int x { 2'147'483'647 }; // the maximum value of a 4-byte signed integer
    std::cout << x << '\n';

    x = x + 1; // integer overflow, undefined behavior
    std::cout << x << '\n';

    return 0;
}
```

#### Integer division:
When performing division with signed integers, the result is also a signed integer. If the division results in a fractional value, the fractional part is truncated (not rounded). For example:
```cpp
#include <iostream>

int main()
{
    int a { 7 };
    int b { 3 };
    int c { a / b }; // integer division, result is 2 (fractional part truncated)
    std::cout << c << '\n';

    return 0;
}
```

#### Summary:
- An integer is an integral type that can represent positive and negative whole numbers.
- Signed integers can represent both positive and negative values, while unsigned integers can only represent non-negative values.
- Common signed integer types in C++ include `short int`, `int`, `long int`, and `long long int`.
- The range of values that a signed integer can represent depends on its size (in bytes) and the system architecture.
- When a signed integer exceeds its maximum or minimum value, it results in an overflow, which can lead to unexpected behavior.
- When performing division with signed integers, the result is also a signed integer, and any fractional part is truncated.

---

### S05 — 4.5 Unsigned integers, and why to avoid them
In C++, **unsigned integers** are integral types that can only represent non-negative whole numbers (zero and positive values). 

#### Unsigned integer range:
A 1-byte (8 bits) unsigned integer can represent values from 0 to 255. In general, an unsigned integer with **n bits** can represent values from **0** to **2^n - 1**.

#### Unsigned integer overflow:
When an unsigned integer exceeds its maximum value, it results in an **overflow**. This can lead to unexpected behavior, as the value wraps around to zero and continues counting up from there (basically only the reminder is kept). 

For example, if you want to represent the number `280` using an 8-bit unsigned integer, we divide `280` by `256` (the maximum value + 1), getting a quotient of `1` and a remainder of `24`. The value stored in the unsigned integer will be `24`, as the overflow caused the value to wrap around. Another example is `256`, which will wrap around to `0`.

```cpp
#include <iostream>

int main()
{
    unsigned short x{ 65535 }; // largest 16-bit unsigned value possible
    std::cout << "x was: " << x << '\n';

    x = 65536; // 65536 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';

    x = 65537; // 65537 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';

    x = -1; // -1 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';

    x = -2; // -2 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';

    return 0;
}
```
The output will be:
```
x was: 65535
x is now: 0
x is now: 1
x is now: 65535
x is now: 65534
```

This to say that assigning negative values to unsigned integers will also result in wrap-around behavior, which can lead to unexpected results.

#### The controversy over unsigned integers:
Developers generally suggest to avoid unsigned integers unless there is a specific need for them. Here some reasons why:
- With unsigned integers it is easier to overflow the bottom of the range (i.e., go below zero) without realizing it, compared to signed integers where you would get negative values.
- Mixing signed and unsigned integers in expressions can lead to unexpected results due to implicit type conversions performed by the compiler.
    ```cpp
    #include <iostream>

    // assume int is 4 bytes
    int main()
    {
        unsigned int u{ 2 };
        signed int s{ 3 };

        std::cout << u - s << '\n'; // 2 - 3 = 4294967295

        return 0;
    }
    ```
    In this example, the signed integer `s` is implicitly converted to an unsigned integer before the subtraction takes place, resulting in a large positive value instead of the expected negative value. The output will be `4294967295` instead of `-1`.
#### Summary:
- Unsigned integers are integral types that can only represent non-negative whole numbers.
- An unsigned integer with **n bits** can represent values from **0** to **2^n - 1**.
- When an unsigned integer exceeds its maximum value, it results in an overflow, causing the value to wrap around to zero.
- Assigning negative values to unsigned integers will also result in wrap-around behavior.
- Developers generally suggest avoiding unsigned integers unless there is a specific need for them, due to potential issues with overflow and implicit type conversions.


---

### S06 — 4.6 Fixed-width integers and size_t
Generally, it is good to know in advance on which system your code will run (16-bit, 32-bit, 64-bit, etc.), so you can understand better the bahavior of your program. For example:
```cpp
#include <iostream>

int main()
{
    int x { 32767 };        // x may be 16-bits or 32-bits
    x = x + 1;              // 32768 overflows if int is 16-bits, okay if int is 32-bits
    std::cout << x << '\n'; // what will this print?

    return 0;
}
```

#### Why variable-width integers on C and C++:
C and C++ were designed to be portable languages, meaning that code written in these languages can run on different hardware architectures without modification. To achieve this, the languages allow the size of fundamental data types to vary depending on the architecture. This flexibility allows C and C++ to be used on a wide range of systems, from small embedded devices to large supercomputers, and one could simply use `int`, for example, without worrying about the exact size.

#### Fixed-width integers:
To address the above issue, C++11 introduced **fixed-width integer** types, that are defined in the `<cstdint>` header. These types have a specific size (in bits) regardless of the architecture, making them useful for situations where you need to ensure a specific size for your integers. Some common fixed-width integer types include (table):
| Data Type       | Fixed size (byte) | Fixed range | Note                          |
|-----------------|-------------------|-------------|-------------------------------|
| `std::int8_t`    | 1 (signed)          | -128 to 127 | Treated like a signed char on many systems |
| `std::uint8_t`   | 1 (unsigned)        | 0 to 255    | Treated like an unsigned char on many systems |
| `std::int16_t`   | 2 (signed)         | -32,768 to 32,767 | |
| `std::uint16_t`  | 2 (unsigned)       | 0 to 65,535 | |
| `std::int32_t`   | 4 (signed)         | -2,147,483,648 to 2,147,483,647 | |
| `std::uint32_t`  | 4 (unsigned)       | 0 to 4,294,967,295 | |
| `std::int64_t`   | 8 (signed)         | -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807 | |
| `std::uint64_t`  | 8 (unsigned)       | 0 to 18,446,744,073,709,551,615 | | 

These types are particularly useful in scenarios where you need to ensure that your integers have a specific size, such as when working with binary data formats or network protocols.

#### Warning: `std::int8_t` and `std::uint8_t` typically behaves like `char` types:
On many modern systems, `std::int8_t` and `std::uint8_t` are treated like `signed char` and `unsigned char` respectively. This means that when you use these types in arithmetic operations or when printing them, they may behave differently than you expect. For example, when printing a `std::int8_t` variable, it may be interpreted as a character rather than an integer value.
```cpp
#include <cstdint>
#include <iostream>
int main()
{
    std::int8_t smallInt { 65 }; // ASCII value for 'A'
    std::cout << "smallInt as char: " << smallInt << '\n'; // may print 'A'

    return 0;
}
```
In this example, the output may be `smallInt as char: A` instead of `smallInt as char: 65`. To avoid this behavior, you can cast the variable to an `int` when printing:
```cpp
#include <cstdint>
#include <iostream>
int main()
{
    std::int8_t smallInt { 65 }; // ASCII value for 'A'
    std::cout << "smallInt as int: " << static_cast<int>(smallInt) << '\n'; // will print 65
    return 0;
}
```
We will see more about type casting in a later chapter.

#### Other fixed-width downsides:
The fixed-width integers have some potential downsides:
- The fixed-width integers are not guaranteed to be defined on all architectures. For example, a system may not support an 8-bit integer type.
- Using fixed-width integers may lead to performance issues on some architectures, as the CPU may be optimized for handling native integer sizes (e.g., 32-bit or 64-bit) rather than smaller sizes or specific sizes.

#### Fast and least integral types:
In addition to fixed-width integers, the `<cstdint>` header also defines **fast** and **least** integral types, to fix the potential downsides of fixed-width integers:
- **Fast integral types**: These types are designed to be the fastest integer types available for a given size. They are defined as `std::int_fastN_t` and `std::uint_fastN_t`, where `N` is the number of bits (8, 16, 32, or 64). For example, `std::int_fast16_t` is the fastest signed integer type that is at least 16 bits wide on the target architecture.
- **Least integral types**: These types are designed to be the smallest integer types available for a given size. They are defined as `std::int_leastN_t` and `std::uint_leastN_t`, where `N` is the number of bits (8, 16, 32, or 64). For example, `std::int_least16_t` is the smallest signed integer type that is at least 16 bits wide on the target architecture.

Here an example:
```cpp
#include <cstdint> // for fast and least types
#include <iostream>

int main()
{
	std::cout << "least 8:  " << sizeof(std::int_least8_t)  * 8 << " bits\n";
	std::cout << "least 16: " << sizeof(std::int_least16_t) * 8 << " bits\n";
	std::cout << "least 32: " << sizeof(std::int_least32_t) * 8 << " bits\n";
	std::cout << '\n';
	std::cout << "fast 8:  "  << sizeof(std::int_fast8_t)   * 8 << " bits\n";
	std::cout << "fast 16: "  << sizeof(std::int_fast16_t)  * 8 << " bits\n";
	std::cout << "fast 32: "  << sizeof(std::int_fast32_t)  * 8 << " bits\n";

	return 0;
}
```
The output will vary depending on the architecture, but it will show the sizes (in bits) of the least and fast integral types:
```
least 8:  8 bits
least 16: 16 bits
least 32: 32 bits

fast 8:  8 bits
fast 16: 32 bits
fast 32: 32 bits
```

#### Best practices:
- Prefer **`int`** when the size of the integer is not critical to your application, as it is typically optimized for the target architecture. 
- Prefer **`std::intN_t`** when storing a quantity needs a guaranteed range (e.g., file formats, network protocols, etc.).
- Prefer **`std::uintN_t`** when doing bit manipulation or well-defined wrap-around behavior is desired.

Avoid the following when possible:
- `short` and `long` types, unless you have a specific reason to use them.
- The fast and least types, unless you have a specific reason to use them.
- Unsigned types for holding quantities.
- The 8-bit fixed-width types (`std::int8_t` and `std::uint8_t`), unless you have a specific reason to use them. Prefer using `std::int16_t` or larger types to avoid unexpected behavior.
- Any compiler-specific integer types (e.g., `__int64`, etc.) to maintain portability.

#### What is `std::size_t`?
`std::size_t` is an unsigned integer type that is used to represent the size of objects in bytes. It is defined in the `<cstddef>` header and is typically used in functions that deal with memory allocation, array indexing, and other operations that involve sizes or counts of objects.

```cpp
#include <iostream>

int main()
{
    std::cout << sizeof(int) << '\n';

    return 0;
}
```
In this example, the `sizeof` operator returns a value of type `std::size_t`, which represents the size of the `int` type in bytes. 

#### Summary:
- C and C++ allow the size of fundamental data types to vary depending on the architecture to achieve portability.
- Fixed-width integer types, defined in the `<cstdint>` header, have a specific size (in bits) regardless of the architecture.
- `std::int8_t` and `std::uint8_t` typically behave like `char` types on many systems, which can lead to unexpected behavior.
- Fast and least integral types are also defined in the `<cstdint>` header to address potential downsides of fixed-width integers.
- Best practices include preferring `int` for general use and fixed-width types for specific size requirements, while avoiding unsigned types for holding quantities.


---

### S07 — 4.7 Introduction to scientific notation
Scientific notation is a way of representing very large or very small numbers in a compact form. In C++, scientific notation is represented using the letter `e` or `E`, which stands for "exponent". The number before the `e` represents the significand (or mantissa), and the number after the `e` represents the exponent, which indicates the power of 10 by which the significand should be multiplied.

For example, the number `3.14e2` represents `3.14 * 10^2`, which is equal to `314`. Similarly, the number `2.5E-3` represents `2.5 * 10^-3`, which is equal to `0.0025`.

#### Significant digits:
In scientific notation, the number of significant digits is important, as it indicates the precision of the number. Significant digits include all non-zero digits, as well as any zeros that are between non-zero digits or at the end of the number after the decimal point. The more significant digits a number has, the more precise it is.

#### How to convert decimal numbers to scientific notation:
To convert a decimal number to scientific notation, follow these steps:
1. Your exponents start at 0.
2. If the number has no explicit decimal point, assume it is at the end of the number.
3. Move the decimal point to the left until there is only one non-zero digit to the left of the decimal point.
    - For each position you move the decimal point to the left, increase the exponent by 1.
    - For each position you move the decimal point to the right, decrease the exponent by 1.
4. Trim off any leading zeros in the significand (on the left side of the decimal point) and any trailing zeros (on the right side of the decimal point).

Here some examples:
```
Start with: 600.410
Slide decimal point left 2 spaces: 6.00410e2
No leading zeros to trim: 6.00410e2
Don't trim trailing zeros: 6.00410e2 (6 significant digits)

Start with: 0.0078900
Slide decimal point right 3 spaces: 0007.8900e-3
Trim leading zeros: 7.8900e-3
Don't trim trailing zeros: 7.8900e-3 (5 significant digits)

Start with: 1230000
Slide decimal point left 6 spaces: 1.230000e6
No leading zeros to trim: 1.230000e6
Don't trim trailing zeros: 1.230000e6 (7 significant digits)    
```

#### Handling trailing zeros:
When converting to scientific notation, trailing zeros in the significand are important as they indicate the precision of the number. Do not trim trailing zeros unless you want to reduce the precision of the number.
For example, `6.00410e2` has 6 significant digits, while `6.0041e2` has only 5 significant digits.

#### Summary:
- Scientific notation is a way of representing very large or very small numbers in a compact form using the letter `e` or `E`.
- The significand (or mantissa) is the number before the `e`, and the exponent is the number after the `e`.
- The number of significant digits indicates the precision of the number.
- To convert a decimal number to scientific notation, move the decimal point to create a significand with one non-zero digit to the left of the decimal point, adjusting the exponent accordingly.
- Trailing zeros in the significand should be preserved to maintain precision.


---

### S08 — 4.8 Floating point numbers
**Floating point numbers** are used to represent real numbers (numbers with fractional parts). They are called "floating point" because the decimal point can "float" to different positions within the number, allowing for a wide range of values to be represented.

#### C++ floating point types:
C++ provides three main floating point types:
- `float`: typically a 4 bytes (32 bits) single-precision floating point type.
- `double`: typically a 8 bytes (64 bits) double-precision floating point type.
- `long double`: typically a 8, 12, or 16 bytes (64, 96, or 128 bits) extended-precision floating point type.

#### Printing floating point numbers:
An example:
```cpp
#include <iostream>

int main()
{
	std::cout << 5.0 << '\n';
	std::cout << 6.7f << '\n';
	std::cout << 9876543.21 << '\n';

	return 0;
}
```
The output will be:
```
5
6.7
9.87654e+06
```

#### Floating point precision:
The **precision** of a floating point type defines how many significant digits it can represent without information loss. Here are the typical precisions for the three floating point types:
| Data Type   | Typical Size (bytes) | Typical Precision (significant digits) |
|-------------|----------------------|----------------------------------------|
| `float`       | 4                    | 6-9 (typically 7)                      |
| `double`      | 8                    | 15-18 (typically 16)                   |
| `long double` | 8, 12, or 16       | 18-36 (varies by implementation)       |
This means that a `float` can typically represent numbers with up to 7 significant digits accurately, while a `double` can represent numbers with up to 16 significant digits accurately.

#### Outputting floating point values:
By default, C++ `std::cout` has 6 digits of precision when outputting floating point values, and it will truncate any additional digits. For example:
```cpp
#include <iostream>

int main()
{
    std::cout << 9.87654321f << '\n';
    std::cout << 987.654321f << '\n';
    std::cout << 987654.321f << '\n';
    std::cout << 9876543.21f << '\n';
    std::cout << 0.0000987654321f << '\n';

    return 0;
}
```
The output will be:
```
9.87654
987.654
987654
9.87654e+006
9.87654e-005
```

We can change the precision of floating point output using the `std::setprecision` manipulator from the `<iomanip>` header. For example:
```cpp
#include <iomanip> // for output manipulator std::setprecision()
#include <iostream>

int main()
{
    std::cout << std::setprecision(17); // show 17 digits of precision
    std::cout << 3.33333333333333333333333333333333333333f <<'\n'; // f suffix means float
    std::cout << 3.33333333333333333333333333333333333333 << '\n'; // no suffix means double

    return 0;
}
```

The output will be:
```
3.3333332538604736
3.3333333333333335
```

#### Rounding errors make floating point comparisons tricky:
Floating point numbers are tricky to work with due to non-obvious differences between binary (how data is stored) and decimal (how we think) numbers. For example, the decimal number `0.1` will be represented in banary as `0.00011001100110011…` (an infinitely repeating binary fraction). This means that when you try to store `0.1` in a floating point variable, it will be rounded to the nearest representable value, which may not be exactly `0.1`.

```cpp
#include <iomanip> // for std::setprecision()
#include <iostream>

int main()
{
    double d{0.1};
    std::cout << d << '\n'; // use default cout precision of 6
    std::cout << std::setprecision(17);
    std::cout << d << '\n';

    return 0;
}
```
The output will be:
```
0.1
0.10000000000000001
```

This small difference can lead to unexpected results:
```cpp
#include <iomanip> // for std::setprecision()
#include <iostream>

int main()
{
    std::cout << std::setprecision(17);

    double d1{ 1.0 };
    std::cout << d1 << '\n';

    double d2{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 }; // should equal 1.0
    std::cout << d2 << '\n';

    return 0;
}
```
The output will be:
```
1
0.99999999999999989
```
As you can see, adding `0.1` ten times does not exactly equal `1.0` due to rounding errors.

#### NaN and Inf:
IEEE 754 compatible formats additionally support some special values:
- **NaN (Not a Number)**: Represents an undefined or unrepresentable value, such as the result of `0.0 / 0.0` or the square root of a negative number.
- **Inf (Infinity)**: Represents infinite values, positive (`+Inf`) or negative (`-Inf`), such as the result of dividing a positive number by zero.
- **Signed zero**: Both `+0.0` and `-0.0` are distinct values in floating point representation.

For example:
```cpp
#include <iostream>

int main()
{
    double zero { 0.0 };

    double posinf { 5.0 / zero }; // positive infinity
    std::cout << posinf << '\n';

    double neginf { -5.0 / zero }; // negative infinity
    std::cout << neginf << '\n';

    double z1 { 0.0 / posinf }; // positive zero
    std::cout << z1 << '\n';

    double z2 { -0.0 / posinf }; // negative zero
    std::cout << z2 << '\n';

    double nan { zero / zero }; // not a number (mathematically invalid)
    std::cout << nan << '\n';

    return 0;
}
```
The output will be:
```
inf
-inf
0
-0
nan
```

#### Summary:
- Floating point numbers are used to represent real numbers with fractional parts.
- C++ provides three main floating point types: `float`, `double`, and `long double`.
- The precision of floating point types defines how many significant digits they can represent without information loss.
- By default, C++ `std::cout` has 6 digits of precision when outputting floating point values, but this can be changed using the `std::setprecision` manipulator.
- Floating point numbers can have rounding errors due to the way they are represented in binary, which can lead to unexpected results in comparisons and calculations.
- IEEE 754 compatible formats support special values such as NaN (Not a Number) and Inf (Infinity).


---

### S09 — 4.9 Boolean values
In C++, a **boolean** is a data type that can hold one of two possible values: `true` or `false`. The boolean type is represented by the keyword `bool`. 

#### Boolean variables:
You can declare boolean variables using the `bool` keyword. For example:
```cpp
bool b; // declare a boolean variable
```

To initialize or assign a `true` or `false` value to a boolean variable, you can use the following syntax:
```cpp
bool b1 { true };
bool b2 { false };
b1 = false;
bool b3 {}; // default initialize to false
```
Boolean values are actually stored in memeory as integers, where `true` is represented by the integer value `1`, and `false` is represented by the integer value `0`.

#### Logical not:
The logical NOT operator (`!`) is used to invert the value of a boolean expression. If the expression is `true`, applying the NOT operator will make it `false`, and vice versa. For example:
```cpp
#include <iostream>
int main()
{
    bool b1 { true };
    bool b2 { false };

    std::cout << std::boolalpha; // print bools as true/false instead of 1/0
    std::cout << "!b1: " << !b1 << '\n'; // prints false
    std::cout << "!b2: " << !b2 << '\n'; // prints true

    return 0;
}
```
will print:
```
!b1: false
!b2: true
```

#### Printing boolean values:
By default, when you print a boolean value using `std::cout`, it will display `1` for `true` and `0` for `false`. However, you can use the `std::boolalpha` manipulator from the `<iostream>` header to print boolean values as `true` or `false`. For example:
```cpp
#include <iostream>

int main()
{
    std::cout << true << '\n';
    std::cout << false << '\n';

    std::cout << std::boolalpha; // print bools as true or false

    std::cout << true << '\n';
    std::cout << false << '\n';
    return 0;
}
```
will show:
```
1
0
true
false
```

#### Integer to boolean conversion:
In C++, integers can be implicitly converted to boolean values. Any non-zero integer value is converted to `true`, while the integer value `0` is converted to `false`. For example:
```cpp
#include <iostream>
int main()
{
    int x { 42 };
    int y { 0 };

    bool b1 { x }; // non-zero integer converts to true
    bool b2 { y }; // zero integer converts to false

    std::cout << std::boolalpha; // print bools as true/false
    std::cout << "b1: " << b1 << '\n'; // prints true
    std::cout << "b2: " << b2 << '\n'; // prints false

    return 0;
}
```
will print:
```
b1: true
b2: false
```

However, when initializing a boolean variable from an integer, it is recommended to use explicit `true` or `false` values for clarity.

#### Inputting boolean values:
When reading boolean values from input using `std::cin`, any non-zero integer input will be interpreted as `true`, while an input of `0` will be interpreted as `false`. For example:
```cpp
#include <iostream>

int main()
{
	bool b{}; // default initialize to false
	std::cout << "Enter a boolean value: ";
	std::cin >> b;
	std::cout << "You entered: " << b << '\n';

	return 0;
}
```
If the user enters the string `true`/`false`, the output will be:
```
Enter a boolean value: true
You entered: 0
```
This is because `std::cin` does not recognize the strings `true` or `false` as boolean values, and interprets any non-numeric input as `0` (false). To read boolean values as `true` or `false`, you can use `std::boolalpha` with `std::cin`:
```cpp
#include <iostream>

int main()
{
	bool b{};
	std::cout << "Enter a boolean value: ";

	// Allow the user to input 'true' or 'false' for boolean values
	// This is case-sensitive, so True or TRUE will not work
	std::cin >> std::boolalpha;
	std::cin >> b;

	// Let's also output bool values as `true` or `false`
	std::cout << std::boolalpha;
	std::cout << "You entered: " << b << '\n';

	return 0;
}
```
If the user enters the string `true`/`false`, the output will be:
```
Enter a boolean value: true
You entered: true
```

However, when `std::boolalpha` is enabled, numeric values will no longer be accepted as valid boolean input.

#### Boolean return values:
Functions can return boolean values to indicate success or failure, or to represent a true/false condition. These functions typically start with the prefix `is`, `has`, `can`, or similar. For example:
```cpp
#include <iostream>

// returns true if x and y are equal, false otherwise
bool isEqual(int x, int y)
{
    return x == y; // operator== returns true if x equals y, and false otherwise
}

int main()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;

    std::cout << "Enter another integer: ";
    int y{};
    std::cin >> y;

    std::cout << std::boolalpha; // print bools as true or false

    std::cout << x << " and " << y << " are equal? ";
    std::cout << isEqual(x, y) << '\n'; // will return true or false

    return 0;
}
```
will output:
```
Enter an integer: 5
Enter another integer: 5
5 and 5 are equal? true
```
or
```
Enter an integer: 6
Enter another integer: 4
6 and 4 are equal? false
```

#### Summary:
- A boolean is a data type that can hold one of two possible values: `true` or `false`.
- Boolean variables are declared using the `bool` keyword.
- The logical NOT operator (`!`) is used to invert the value of a boolean expression.
- By default, `std::cout` prints boolean values as `1` for `true and `0` for `false`, but the `std::boolalpha` manipulator can be used to print them as `true` or `false`.
- Integers can be implicitly converted to boolean values, with non-zero integers converting to `true` and `0` converting to `false.
- When reading boolean values from input, `std::boolalpha` can be used to allow input of the strings `true` and `false`.
- Functions can return boolean values to indicate success or failure, or to represent true/false conditions.


---

### S10 — 4.10 Introduction to if statements
An **if statement** is a control flow statement that allows you to execute a block of code conditionally, based on whether a specified condition is true or false. For example, you want to print a message only if a certain condition is met.

The simplest form of an if statement is:
```cpp
if (condition) true_statement;
```
or 
```cpp
if (condition)
    true_statement(s);
```

A **condition** (or **conditional expression**) is an expression that evaluates to a boolean value (`true` or `false`). If the condition evaluates to `true`, the code block (the **true statement(s)**) inside the if statement is executed. If the condition evaluates to `false`, the code block is skipped.

#### A sample program using an if statement:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x {};
    std::cin >> x;

    if (x == 0)
        std::cout << "The value is zero\n";

    return 0;
}
```
Here is output when the user enters `0`:
```
Enter an integer: 0
The value is zero
```
And here is output when the user enters `5`:
```
Enter an integer: 5
``` 

#### If-else:
An **if-else statement** allows you to execute one block of code if a condition is true, and another block of code if the condition is false. The syntax is:
```cpp
if (condition)
    true_statement(s);
else
    false_statement(s);
```

For example:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x {};
    std::cin >> x;

    if (x == 0)
        std::cout << "The value is zero\n";
    else
        std::cout << "The value is non-zero\n";

    return 0;
}
```
Now our output will be:
```
Enter an integer: 0
The value is zero
```
or
```
Enter an integer: 5
The value is non-zero
```

#### Chaining if statements with else if:
You can chain multiple conditions together using `else if` statements. This allows you to check multiple conditions in sequence. The syntax is:
```cpp
if (condition1)
    statement(s)1;
else if (condition2)
    statement(s)2;
else if (condition3)
    statement(s)3;
else
    statement(s)_n;
```

In the previous example, we can extend it to check for positive and negative values:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x {};
    std::cin >> x;

    if (x > 0)
        std::cout << "The value is positive\n";
    else if (x < 0)
        std::cout << "The value is negative\n";
    else
        std::cout << "The value is zero\n";

    return 0;
}
```

#### Boolean return values and if statements:
Functions that return boolean values can be used directly in if statements to control the flow of execution based on the result of the function. For the example of the previous section, we could rewrite it like this:
```cpp
#include <iostream>

// returns true if x and y are equal, false otherwise
bool isEqual(int x, int y)
{
    return x == y; // operator== returns true if x equals y, and false otherwise
}

int main()
{
    std::cout << "Enter an integer: ";
    int x {};
    std::cin >> x;

    std::cout << "Enter another integer: ";
    int y {};
    std::cin >> y;

    if (isEqual(x, y))
        std::cout << x << " and " << y << " are equal\n";
    else
        std::cout << x << " and " << y << " are not equal\n";

    return 0;
}
```
This program will output whether the two entered integers are equal or not.

#### Non-boolean conditinals:
In C++, any expression that evaluates to a non-boolean value will be converted to a boolean value when used in a conditional context (like an if statement). The rules for this conversion are:
- Non-zero values are converted to `true`.
- Zero values are converted to `false`.

For example:
```cpp
#include <iostream>

int main()
{
    int x { 4 };
    if (x) // nonsensical, but for the sake of example...
        std::cout << "hi\n";
    else
        std::cout << "bye\n";

    return 0;
}
```
will print `hi` because `x` is non-zero and thus evaluates to `true`.

#### If-statements and early returns:
If statements can be used to exit a function early using the `return` statement. This is useful for handling error conditions or special cases at the beginning of a function. For example:
```cpp
#include <iostream>

// returns the absolute value of x
int abs(int x)
{
    if (x < 0)
        return -x; // early return (only when x < 0)

    return x;
}

int main()
{
    std::cout << abs(4) << '\n'; // prints 4
    std::cout << abs(-3) << '\n'; // prints 3

    return 0;
}
```
computes the absolute value of an integer using an early return if the input is negative.

#### Summary:
- An if statement allows you to execute a block of code conditionally based on whether a specified condition is true or false.
- An if-else statement allows you to execute one block of code if a condition is true, and another block of code if the condition is false.
- You can chain multiple conditions together using else if statements.
- Functions that return boolean values can be used directly in if statements to control the flow of execution.
- Non-boolean expressions used in conditionals are converted to boolean values, with non-zero values converting to true and zero values converting to false.
- If statements can be used to exit a function early using the return statement.


---

### S11 — 4.11 Chars
The **char** data type in C++ is used to represent single characters, such as letters, digits, punctuation marks, and special symbols. The `char` type is typically 1 byte (8 bits) and it is an integral type, meaning that the underlying values is stored as an integer. The integer stored by a `char` variable corresponds to a specific character in the character encoding scheme used by the system (typically ASCII or UTF-8).

**ASCII** (American Standard Code for Information Interchange) is a character encoding standard that represents characters using integer values ranging from 0 to 127. Each character is assigned a unique integer value, known as its ASCII code. For example, the ASCII code for the uppercase letter 'A' is 65, while the ASCII code for the lowercase letter 'a' is 97.

Here is a full table of the ASCII character set:
| Code | Symbol | Code | Symbol | Code | Symbol | Code | Symbol |
|------|--------|------|--------|------|--------|------|--------|
|  0   | NUL (null)              |  32  | (space)|  64  | @      |  96  | `      |
|  1   | SOH (start of header)   |  33  | !      |  65  | A      |  97  | a      |
|  2   | STX (start of text)     |  34  | "      |  66  | B      |  98  | b      |
|  3   | ETX (end of text)       |  35  | #      |  67  | C      |  99  | c      |
|  4   | EOT (end of transmission)|  36  | $      |  68  | D      | 100  | d      |
|  5   | ENQ (enquiry)           |  37  | %      |  69  | E      | 101  | e      |
|  6   | ACK (acknowledge)       |  38  | &      |  70  | F      | 102  | f      |
|  7   | BEL (bell)              |  39  | '      | |  71  | G      | 103  | g      |
|  8   | BS  (backspace)         |  40  | (      |  72  | H      | 104  | h      |
|  9   | TAB (horizontal tab)    |  41  | )      |  73  | I      | 105  | i      |
| 10   | LF  (line feed)          |  42  | *      |  74  | J      | 106  | j      |
| 11   | VT  (vertical tab)        |  43  | +      |  75  | K      | 107  | k      |
| 12   | FF  (form feed)          |  44  | ,      |  76  | L      | 108  | | l      |
| 13   | CR  (carriage return)    |  45  | -      |  77  | M      | 109  | m      |
| 14   | SO  (shift out)          |  46  | .      |  78  | N      | 110  | n      |
| 15   | SI  (shift in)           |  47  | /      |  79  | O      | 111  | o      |
| 16   | DLE (data link escape)   |  48  | 0      |  80  | P      | 112  | p      |
| 17   | DC1 (device control 1)   |  49  | 1      |  81  | Q      | 113  | q      |
| 18   | DC2 (device control 2)   |  50  | 2      |  82  | R      | 114  | r      |
| 19   | DC3 (device control 3)   |  51  | 3      |  83  | S      | 115  | s      |
| 20   | DC4 (device control 4)   |  52  | 4      |  84  | T      | 116  | t      |
| 21   | NAK (negative acknowledge)|  53  | 5      |  85  | U      | 117  | u      |
| 22   | SYN (synchronous idle)     |  54  | 6      |  86  | V      | 118  | v      |
| 23   | ETB (end of transmission block)|  55  | 7      |  87  | W      | 119  | w      |
| 24   | CAN (cancel)              |  56  | 8      |  88  | X      | 120  | x      |
| 25   | EM  (end of medium)       |  57  | 9      |  89  | Y      | 121  | y      |
| 26   | SUB (substitute)          |  58  | :      |  90  | Z      | 122  | z      |
| 27   | ESC (escape)              |  59  | ;      |  91  | [      | 123  | {      |
| 28   | FS  (file separator)      |  60  | <      |  92  | \      | 124  | vertical bar |
| 29   | GS  (group separator)     |  61  | =      |  93  | ]      | 125  | }      |
| 30   | RS  (record separator)    |  62  | >      |  94  | ^      | 126  | ~      |
| 31   | US  (unit separator)       |  63  | ?      |  95  | _      | 127  | DEL    |

Codes 0-31 are called the **unprintable control characters** because they do not represent printable characters. Instead, they are used to control various aspects of text formatting and communication protocols.

Codes 32-126 are called the **printable characters** because they represent characters that can be printed or displayed on a screen.

#### Initializing chars:
You can initialize a `char` variable using single quotes (`'`) to enclose the character. For example:
```cpp
char letterA { 'A' }; // initializes letterA with the character 'A' (stored as integer value 65
char digit5 { '5' };  // initializes digit5 with the character '5' (stored as integer value 53
char space { ' ' };    // initializes space with the space character (stored as integer value 32)
```

You can initialize `char` variables with integers as well:
```cpp
char letterA { 65 }; // initializes letterA with the character 'A' (ASCII code 65)
char digit5 { 53 };  // initializes digit5 with the character '5' (ASCII code 53)
char space { 32 };    // initializes space with the space character (ASCII code 32)
```

#### Printing chars:
When you print a `char` variable using `std::cout`, it will display the character corresponding to the stored integer value. For example:
```cpp
#include <iostream>

int main()
{
    char ch1{ 'a' }; // (preferred)
    std::cout << ch1; // cout prints character 'a'

    char ch2{ 98 }; // code point for 'b' (not preferred)
    std::cout << ch2; // cout prints a character ('b')


    return 0;
}
```
will output:
```
ab
```

#### Inputting chars:
You can read a single character from input using `std::cin`. For example:
```cpp
#include <iostream>

int main()
{
    std::cout << "Input a keyboard character: ";

    char ch{};
    std::cin >> ch;
    std::cout << "You entered: " << ch << '\n';

    return 0;
}
```
If the user inputs the character `Z`, the output will be:
```
Input a keyboard character: Z
You entered: Z
```

#### Extracting whitespace characters:
When reading input using `std::cin`, whitespace characters (spaces, tabs, newlines) are ignored by default. This means that if the user inputs a space or presses the Enter key, `std::cin` will skip over those characters and wait for a non-whitespace character to be entered. For example:
```cpp
#include <iostream>

int main()
{
    std::cout << "Input a keyboard character: "; // assume the user enters "a b" (without quotes)

    char ch{};
    std::cin >> ch; // extracts a, leaves " b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    std::cin >> ch; // skips leading whitespace (the space), extracts b, leaves "\n" in stream
    std::cout << "You entered: " << ch << '\n';

    return 0;
}
```
If the user inputs `a b` (without quotes), the output will be:
```
Input a keyboard character: a b
You entered: a
You entered: b
```

One simple way to address this is to use `std::cin.get()` which reads the next character from the input stream, including whitespace characters. For example:
```cpp
#include <iostream>
int main()
{
    std::cout << "Input a keyboard character: "; // assume the user enters "a b" (without quotes)

    char ch{};
    ch = std::cin.get(); // extracts 'a', leaves " b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    ch = std::cin.get(); // extracts ' ' (space), leaves "b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    ch = std::cin.get(); // extracts 'b', leaves "\n" in stream
    std::cout << "You entered: " << ch << '\n';

    return 0;
}
```
If the user inputs `a b` (without quotes), the output will be:
```
Input a keyboard character: a b
You entered: a
You entered: 
You entered: b
```

#### Char size, and default sign:
The `char` data type is typically 1 byte (8 bits) in size. The C++ standard does not specify whether `char` is signed or unsigned by default; it is implementation-defined, tho it is usually signed.

#### Escape sequences:
Escape sequences are special character combinations that represent certain non-printable or special characters. They begin with a backslash (`\`) followed by one or more characters. Here are some common escape sequences in C++:
| Escape Sequence | Description                     |
|-----------------|---------------------------------|
| `\n`            | Newline (line feed)             |
| `\t`            | Horizontal tab                  |
| `\a`            | Alert (bell)                    |
| `\b`            | Moves cursor back one space     |
| `\f`            | Moves curosor to the next logical page |
| `\r`            | Carriage return (moves cursor to the beginning of the line) |
| `\\`            | Backslash character (`\`)       |
| `\'`            | Single quote character (`'`)    |
| `\"`            | Double quote character (`"`)    |
| `\0`            | Null character (ASCII code 0)   |
| `\x(number)` | Hexadecimal representation of a character (e.g., `\x41` represents 'A') |

For example:
```cpp
#include <iostream>

int main()
{
    std::cout << "\"This is quoted text\"\n";
    std::cout << "This string contains a single backslash \\\n";
    std::cout << "6F in hex is char '\x6F'\n";
    return 0;
}
```
will output:
```
"This is quoted text"
This string contains a single backslash \
6F in hex is char 'o'
```

#### Difference between single quotes and double quotes:
In C++, single quotes (`'`) are used to denote a single character literal, while double quotes (`"`) are used to denote a string literal (a sequence of characters), and it is treated as a C-style string literal (an array of characters terminated by a null character `\0`).

#### Avoid multicharacter literals:
In C++, a multicharacter literal is a character literal that contains more than one character enclosed in single quotes. For example, `'56'` is a multicharacter literal. Such literals are implementation-defined and can lead to unexpected behavior, as they may not represent what you intend. For example:
```cpp
#include <iostream>

int add(int x, int y)
{
	return x + y;
}

int main()
{
	std::cout << add(1, 2) << '/n'; // we used a forward slash instead of a backslash here

	return 0;
}
```
The output may not be what you expect because `'/n'` is a multicharacter literal, and could give the following output:
```
312142
```
To avoid this issue, always use single quotes for single characters and double quotes for strings.

#### Other character types:
C++ also provides other character types for representing characters in different encodings:
- `wchar_t`: used for wide characters, typically 2 or 4 bytes, depending on the platform. It is used to represent characters from larger character sets, such as Unicode.
- `char8_t`: used for UTF-8 encoded characters, typically 1 byte.
- `char16_t`: used for UTF-16 encoded characters, typically 2 bytes.
- `char32_t`: used for UTF-32 encoded characters, typically 4 bytes.

You will not use these character types much in this course, but they are available if you need to work with international character sets.

#### Summary:
- The `char` data type in C++ is used to represent single characters and is typically 1 byte (8 bits) in size.
- Characters are represented using integer values corresponding to their ASCII codes.
- You can initialize `char` variables using single quotes for characters or integer values for ASCII codes.
- When printing `char` variables, `std::cout` displays the corresponding character.
- You can read single characters from input using `std::cin`, but whitespace characters are ignored by default.
- Escape sequences are special character combinations that represent non-printable or special characters.


---

### S12 — 4.12 Introduction to type conversion and static_cast
Type conversion is the process of converting a value from one data type to another. In C++, type conversion can occur implicitly (automatically) or explicitly (manually).

#### Implicit type conversion (type coercion):
Implicit type conversion, also known as type coercion, occurs automatically when a value of one data type is assigned to a variable of another data type, or when an expression involves mixed data types. For example:
```cpp
#include <iostream>

void print(double x) // print takes a double parameter
{
	std::cout << x << '\n';
}

int main()
{
	print(5); // what happens when we pass an int value?

	return 0;
}
```
In this example, when we pass the integer value `5` to the `print` function, which expects a `double` parameter, the integer `5` is implicitly converted to the double value `5.0` before being passed to the function.

The type conversion processs does not modify the original value; it creates a temporary value of the target type. In the example above, the original integer `5` remains unchanged, and a temporary double value `5.0` is created for the function call.

**Implicit type conversion wanrnings:**
Implicit type conversions can sometimes lead to unexpected results or loss of information, especially when converting float to integer types, sicne it can cause a loss of the fractional part. For example:
```cpp
#include <iostream>

void print(int x) // print now takes an int parameter
{
	std::cout << x << '\n';
}

int main()
{
	print(5.5); // warning: we're passing in a double value

	return 0;
}
```
In this example, when we pass the double value `5.5` to the `print` function, which expects an `int` parameter, the double `5.5` is implicitly converted to the integer value `5`, resulting in a loss of the fractional part. The compiler may issue a warning about this implicit conversion.

#### Introduction to explicit type conversion (type casting) via static_cast operator:
Explicit type conversion, also known as type casting, is the process of manually converting a value from one data type to another using a cast operator. In C++, the preferred way to perform explicit type conversion is by using the `static_cast` operator. The syntax for `static_cast` is:
```cpp
static_cast<target_type>(expression)
```
where `target_type` is the data type you want to convert to, and `expression` is the value you want to convert.

In the previous example, we can use `static_cast` to explicitly convert the double value `5.5` to an integer before passing it to the `print` function:
```cpp
#include <iostream>

void print(int x)
{
	std::cout << x << '\n';
}

int main()
{
	print( static_cast<int>(5.5) ); // explicitly convert double value 5.5 to an int

	return 0;
}
```
In this example, we use `static_cast<int>(5.5)` to explicitly convert the double value `5.5` to the integer value `5` before passing it to the `print` function. This makes it clear that we are aware of the conversion and any potential loss of information.

#### Using static_cast to convert char to int:
You can also use `static_cast` to convert a `char` to its corresponding integer ASCII value. For example:
```cpp
#include <iostream>
int main()
{
    char ch { 'A' }; // character 'A'
    int ascii_value { static_cast<int>(ch) }; // convert char to int

    std::cout << "The ASCII value of '" << ch << "' is " << ascii_value << '\n';

    return 0;
}
```
will output:
```
The ASCII value of 'A' is 65
```

Note that, when you convert `ch` to an `int` using `static_cast`, `ch` is not modified; instead, a temporary integer value representing the ASCII code of 'A' (which is 65) is created and assigned to `ascii_value`.

#### Sign conversion using static_cast:
You can use `static_cast` to convert between signed and unsigned integer types. For example:
```cpp
#include <iostream>

int main()
{
    unsigned int u1 { 5 };
    // Convert value of u1 to a signed int
    int s1 { static_cast<int>(u1) };
    std::cout << s1 << '\n'; // prints 5

    int s2 { 5 };
    // Convert value of s2 to an unsigned int
    unsigned int u2 { static_cast<unsigned int>(s2) };
    std::cout << u2 << '\n'; // prints 5

    return 0;
}
```
will output:
```
5
5
```

But be aware, if the value being converted is out of range for the target type:
- If the destination type is unsigned, the value will be modulo wrapped to fit within the range of the unsigned type.
- If the destination type is signed, the result is implementation-defined (it may wrap around or produce a negative value).

For example:
```cpp
#include <iostream>

int main()
{
    int s { -1 };
    std::cout << static_cast<unsigned int>(s) << '\n'; // prints 4294967295

    unsigned int u { 4294967295 }; // largest 32-bit unsigned int
    std::cout << static_cast<int>(u) << '\n'; // implementation-defined prior to C++20, -1 as of C++20

    return 0;
}
```
will output:
```
4294967295
-1
```

#### Summary:
- Type conversion is the process of converting a value from one data type to another, which can occur implicitly or explicitly.
- Implicit type conversion occurs automatically when a value of one data type is assigned to a variable of another data type or when an expression involves mixed data types.
- Implicit type conversions can lead to unexpected results or loss of information, especially when converting from floating-point types to integer types.
- Explicit type conversion, or type casting, is performed manually using the `static_cast` operator.
- The `static_cast` operator allows you to convert values between different data types, including converting `char` to `int` and between signed and unsigned integer types.


---

### SX — 4.x summary and quiz:
Have a look at the exercises for this chapter in the course. Then, you will find solutions inside the `exercises/sx-questions` folder.

Enjoy! :)


---

## 🧭 Summary

In this chapter, you explored how C++ represents **data at the fundamental level** and how different types define both the **interpretation and precision** of values stored in memory. You learned that everything is ultimately represented as bits and bytes, and that **data types** tell the compiler how to interpret these values. The chapter covered how **fundamental types** like `int`, `float`, `double`, `char`, `bool`, and `void` form the foundation of every program, and how **object sizes** may vary depending on architecture.  

You discovered the key differences between **signed and unsigned integers**, the importance of **fixed-width types** for cross-platform consistency, and how `std::size_t` is used for sizes and indexing. You also explored how **floating-point numbers** can introduce rounding errors due to binary representation, and how **booleans** and **if-statements** enable logical control flow.  

Finally, you learned how **characters** are tied to numeric representations through ASCII codes, and how **explicit type conversions** using `static_cast` allow for safe and predictable data transformations.

---

### 🧱 Core Concepts You Mastered

- 🧠 Understanding of **memory representation** (bits, bytes, addresses)  
- 🔢 Mastery of **fundamental and integral data types**  
- 📏 Knowledge of **object size and `sizeof`**  
- ⚖️ Difference between **signed vs unsigned** and their pitfalls  
- 🧱 Usage of **fixed-width and portable integer types**  
- 🌊 Handling **floating-point precision and rounding errors**  
- 🧮 Familiarity with **scientific notation**  
- 🚦 Control flow with **booleans and `if` statements**  
- 🔤 Manipulation of **characters, ASCII, and escape sequences**  
- 🧩 Safe **explicit type casting** using `static_cast`