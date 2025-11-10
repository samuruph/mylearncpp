# Chapter 10 - Type Conversion, Type Aliases, and Type Deductions

## 🧭 Overview
This chapter explores how **types interact, convert, and evolve** in C++.  
Every program manipulates values of different types — integers, floating points, booleans, and user-defined types — and understanding how conversions occur between them is essential for writing safe and efficient code.  

You will learn how implicit and explicit conversions work, what **numeric promotions** are, how to avoid **narrowing conversions**, and how to use **type deduction** (`auto`) and **type aliases** (`using`) to simplify your code.  
The goal is to help you understand how C++ handles type transformations automatically, when you need to step in, and how to express conversions clearly and safely.

> **Key idea:** Good C++ code makes conversions explicit and predictable — reducing bugs and improving clarity.


---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch10_first
./build/ch10_first
```

---

## 🎯 Learning Outcomes

By the end of this chapter, you’ll be able to:

- ⚙️ Understand and apply **implicit** and **explicit** type conversions in C++.  
- 📈 Explain **numeric promotions** and how they preserve value while improving efficiency.  
- ⚖️ Differentiate between **safe**, **unsafe**, and **narrowing** conversions.  
- 🔒 Use `static_cast` for explicit, safe conversions instead of unsafe C-style casts.  
- 🧩 Define **type aliases** and **typedefs** (avoid if possible) to improve code readability and maintainability. Preferred way is `using`.
- 🔍 Apply **type deduction** with `auto` and understand when to use it safely.  
- 🧮 Utilize **arithmetic conversions** to predict how mixed-type expressions are evaluated.  
- 💡 Leverage `constexpr` and list initialization to detect unsafe conversions at compile time.  


---

## Sections

### S01 — 10.1 Implicit type conversions
#### Why conversions are needed:
The value of an object is stored as a asequence of bits, and the **data type** tells the compiler how to interpret those bits. Different data types may represent values differently (e.g., signed vs. unsigned integers, floating-point vs. integer types). For example the integer value `3` is stored as `0000 0000 0000 0000 0000 0000 0000 0011`, while floating point `3.0` is stored as `0100 0000 0100 0000 0000 0000 0000 0000`.

If you do something like this:
```cpp
float f{ 3 }; // implicit conversion from int to float
```
the compiler cannot simply copy the bits from the integer `3` to the floating-point variable `f`, because the bit representations are different. Instead, it needs to perform a **type conversion** to convert the integer value `3` into its floating-point representation `3.0`.

#### When implicity type conversions happen:
**Implicit type conversions** (also called **automatic type conversions** or **type coercions**) is performed automatically by the compiler when an expression of some type is supplied where a different type is expected. This can happen in several scenarios, including:
- **Assignments**: When assigning a value of one type to a variable of another type.
    ```cpp
    double d{ 3 }; // int value 3 implicitly converted to type double
    d = 6; // int value 6 implicitly converted to type double
    ```
- **Function calls**: When passing arguments to functions where the parameter types differ from the argument types, or when the return type of a function differs from the expected type.
    ```cpp
    void printDouble(double value);
    printDouble(5); // int value 5 implicitly converted to type double
    ```
    or 
    ```cpp
    float doSomething()
    {
        return 3.0; // double value 3.0 implicitly converted to type float
    }
    ```
- **Expressions**: When performing operations between different types, such as arithmetic operations or comparisons.
    ```cpp
    int a{ 5 };
    double b{ 2.5 };
    double result = a + b; // int a implicitly converted to type double
    ```
- **Some binary operators**: Certain binary operators may trigger implicit conversions when their operands are of different types.
    ```cpp
    double division{ 4.0 / 3 }; // int value 3 implicitly converted to type double
    ```
- **Conditional expressions**: In conditional (ternary) expressions, the types of the second and third operands may be converted to a common type.
    ```cpp
    int x{ 10 };
    double y{ 5.5 };
    auto result = (x > y) ? x : y; // int x implicitly converted to type double
    ```

#### The standard conversions:
As part of the core language, C++ defines a set of **standard conversions** that the compiler can apply automatically. As of C++23, there are 14 standard conversions, including:

| Category | Description |
|-----------------|-------------|
| Numeric promotions | Conversions of small integral types to `int` or `unsigned int`, and `float` to `double`. |
| Numeric conversions | Other integral and floating point conversions that do not involve promotions. |
| Qualification conversions | Conversions that add or remove `const`, `volatile`, or `restrict` qualifiers. |
| Pointer conversions | Conversions between pointer types, including conversions to/from `void*`, and `std::nullptr`. |


The others are left as an advanced topic for later study.

#### Type conversion can fail:
When a type covnersion is invoked, the compiler will check whether the conversion is valid. If the conversion is not valid (for example, trying to convert a `std::string` to an `int`), the compiler will generate a compile-time error. For example:
```cpp
std::string str{ "Hello" };
int number = str; // Error: cannot convert 'std::string' to 'int'
```

So sometimes, the compiler cannot figure out which type of conversion rule to apply, and this results in a compilation error.

#### Summary:
- Implicit type conversions are automatic conversions performed by the compiler when an expression of one type is used where a different type is expected.
- They occur in various scenarios, including assignments, function calls, expressions, binary operations, and conditional expressions.
- C++ defines a set of standard conversions that the compiler can apply automatically.


---

### S02 — 10.2 Floating points and integral promotion
Usually, a 32-bit computer can process efficiently data that is 32 bits wide (4 bytes). Smaller data types, such as `char` (1 byte) and `short` (2 bytes), may be slower, or require additional processing to handle them efficiently.

#### Numeric promotion:
Because C++ is designed to be portable across different hardware architectures, it defines a set of rules for promoting smaller data types to larger ones when performing arithmetic operations. This is known as **numeric promotion**. 

**Numeric promotion** is the type conversion that the compiler applies to smaller integral types (`char`, `short`) to convert them to a larger type (`int` or `unsigned int`) before performing arithmetic operations. This ensures that the operations are performed efficiently and consistently across different platforms.

All numeric promotions are **value-preserving** (also called **safe conversions**), meaning that the value of the original type is preserved in the promoted type without any loss of information. Because of that, the compiler will use them automatically whenever needed.

#### Numeric promotion reduces redundancy:
Numeric promotion also solve another problem. Consider this example:
```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}
```

What happens if you also want to print a `char` or a `short`? If type covnersion did not exist, you would need to write separate overloads of the `printInt` function for each type:
```cpp
void printChar(char x)
{
    std::cout << static_cast<int>(x) << '\n';
}

void printShort(short x)
{
    std::cout << static_cast<int>(x) << '\n';
}
```

You can see that this is not very efficient, and it would lead to a lot of code duplication. Instead, with numeric promotion, you can simply call the `printInt` function with a `char` or a `short`, and the compiler will automatically promote them to `int`:
```cpp
int main()
{
    char c{ 'A' };
    short s{ 42 };

    printInt(c); // char c is promoted to int
    printInt(s); // short s is promoted to int

    return 0;
}
```
This way, you only need to write the `printInt` function once, and it can handle all the smaller integral types.

#### Numeric promotion categories:
The numeric promotion rules are divided into 2 categories:
- **Integral promotion**: This category includes the promotion of `bool`, `char`, `signed char`, `unsigned char`, `short`, and `unsigned short` to `int` or `unsigned int`. The specific target type depends on the range of values that can be represented by the original type.
- **Floating-point promotion**: This category includes the promotion of `float` to `double`. This is done to ensure that floating-point operations are performed with sufficient precision.

#### Floating point promotions:
We will start with the easier one: floating-point promotion. In C++, when a `float` is used in an expression where a `double` is expected, the compiler automatically promotes the `float` to a `double`. This is done to ensure that floating-point operations are performed with sufficient precision. For example:
```cpp
#include <iostream>

void printDouble(double d)
{
    std::cout << d << '\n';
}

int main()
{
    printDouble(5.0); // no conversion necessary
    printDouble(4.0f); // numeric promotion of float to double

    return 0;
}
```

#### Integral promotions:
Integral promotion is a bit more complex, because there are more types involved. The following types are subject to integral promotion:
- `bool`
- `char`
- `signed char`
- `unsigned char`
- `short`
- `unsigned short`

With this type of promotion, the compiler can apply the following conversions:
- `singed char` or `signed short` can be promoted to `int`.
- `unsigned char`, `char8_t`, and `unsigned short` can be promoted to `int` if it can hold the entire range of the type; otherwise, they are promoted to `unsigned int`.
- If `char` is signed on the target platform, it is promoted to `int`; if it is unsigned, it follows the same rules as `unsigned char`.
- `bool` is promoted to `int`, with `false` becoming `0` and `true` becoming `1`.

There are also other rules, but here are not covered for brevity.

In most cases, this lets us write a function taking `int` parameter, and then use it with any of the smaller integral types without needing to write overloads. For example:
```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}

int main()
{
    printInt(2);

    short s{ 3 }; // there is no short literal suffix, so we'll use a variable for this one
    printInt(s); // numeric promotion of short to int

    printInt('a'); // numeric promotion of char to int
    printInt(true); // numeric promotion of bool to int

    return 0;
}
```

#### Not all widening conversions are numeric promotions:
Some widening conversions are not considered numeric promotions. For example, converting an `int` to a `long` or a `char` to `short` are not considered numeric promotions, but rather **numeric conversions**. This is because such conversions do not assist in the goal of converting smaller types to larger types that can be processed more efficiently.

#### Summary:
- Numeric promotion is the automatic conversion of smaller integral types to `int` or `unsigned int`, and `float` to `double`, to ensure efficient arithmetic operations.
- Numeric promotions are value-preserving, meaning that the value of the original type is preserved in the promoted type without any loss of information.
- Numeric promotion helps reduce code redundancy by allowing functions to handle multiple smaller integral types without needing separate overloads.
- Integral promotion applies to `bool`, `char`, `signed char`, `unsigned char`, `short`, and `unsigned short`, while floating-point promotion applies to `float` to `double`.


---

### S03 — 10.3 Numeric conversions
In the previous section, we discussed numeric promotions, which are a subset of numeric conversions. Now, we will explore the broader category of **numeric conversions**, that includes additional type conversions that are not considered promotions.

There are 5 main types of numeric conversions:
1. **Integral conversions**: Conversions between different integral types (e.g., `int` to `long`, `short` to `unsigned int`, etc.).
    ```cpp
    short s = 3; // convert int to short
    long l = 3; // convert int to long
    char ch = s; // convert short to char
    unsigned int u = 3; // convert int to unsigned int
    ```
2. **Floating-point conversions**: Conversions between different floating-point types (e.g., `float` to `double`, `double` to `long double`, etc.)., excluding floating-point promotion.
    ```cpp
    float f = 3.0; // convert double to float
    long double ld = 3.0; // convert double to long double
    ```
3. **Floating-integral conversions**: Conversions from a floating point type to any integral type (e.g., `double` to `int`, `float` to `long`, etc.).
    ```cpp
    int i = 3.7; // convert double to int (fractional part is truncated)
    long l = 4.9f; // convert float to long (fractional part is truncated)
    ```
4. **Integral-floating conversions**: Conversions from any integral type to a floating point type (e.g., `int` to `float`, `long` to `double`, etc.).
    ```cpp
    float f = 5; // convert int to float
    double d = 10L; // convert long to double
    ```
5. **Boolean conversions**: Conversions from an integral or floating point type to `bool`.
    ```cpp
    bool b1 = 0; // convert int to bool (0 becomes false)
    bool b2 = 3.14; // convert double to bool (non-zero becomes true)
    ```

> **Note**: Because brace-initialization does not allow some type of numeric conversions, we use copy-initialization in the examples above.

#### Safe and unsafe conversions:
Unlike numeric promotions, numeric conversions can be either **safe** or **unsafe**:
- **Safe conversions**: These conversions preserve the value of the original type without any loss of information. For example, converting a smaller integral type to a larger integral type (e.g., `int` to `long`) is a safe conversion.
- **Unsafe conversions**: These conversions may result in loss of information, meaning that at least one value of the source type cannot be converted into an equal value of the destination type. For example, converting a floating-point type to an integral type (e.g., `double` to `int`) is an unsafe conversion, because the fractional part is truncated.

Numeric conversions falls into three categories based on safety:
1. **Value-preserving conversions**: These conversions are safe and preserve the value of the original type without any loss of information. Examples include:
    - Converting a smaller integral type to a larger integral type (e.g., `int` to `long`).
    - Converting a floating-point type to a larger floating-point type (e.g., `float` to `double`).
    - Converting an integral type to a floating-point type (e.g., `int` to `float`).
    ```cpp
    int main()
    {
        int n { 5 };
        long l = n; // okay, produces long value 5

        short s { 5 };
        double d = s; // okay, produces double value 5.0

        return 0;
    }
    ```
2. **Reinterpretative conversions**: These conversions are unsafe numeric conversions where the converted value may be different from the original value, but no data is lost (e.g., singed/unsigned conversions). Examples include:
    - Converting a signed integral type to an unsigned integral type (e.g., `int` to `unsigned int`).
    - Converting an unsigned integral type to a signed integral type (e.g., `unsigned int` to `int`).
    ```cpp
    int main()
    {
        int n1 { 5 };
        unsigned int u1 { n1 }; // okay: will be converted to unsigned int 5 (value preserved)

        int n2 { -5 };
        unsigned int u2 { n2 }; // bad: will result in large integer outside range of signed int

        return 0;
    }
    ```
    Values converted using reinterpretative conversions can be converted back to the source type without loss of data.
3. **Lossy conversions**: These conversions are unsafe numeric conversions where some data is lost during the conversion (e.g., floating-integral conversions). Examples include:
    - Converting a floating-point type to an integral type (e.g., `double` to `int`).
    - Converting a larger integral type to a smaller integral type (e.g., `long` to `short`).
    ```cpp
    int main()
    {
        double d1 { 3.14 };
        int n1 = d1; // bad: fractional part (.14) is truncated

        long l2 { 70000 };
        short s2 = l2; // bad: value 70000 exceeds range of short

        double d3 { 1.23456789 };
        float f3 = d3; // bad: precision may be lost (will be converted to 1.23457)

        return 0;
    }
    ```
    Values converted using lossy conversions cannot be converted back to the source type without loss of data.
    
Generally, unsafe conversion should be avoided, as they can lead to unexpected behavior and bugs in the code. However, in some cases, those are accepted:
- When we can constraint the values to be converted to a safe range (e.g., converting a positive `int` to `unsigned int`).
- We do not care if some data is lost (e.g., converting an `int` to `bool`).

#### More on numeric conversions:
There are many more rules and edge cases regarding numeric conversions, which are beyond the scope of this summary. Hore the most important ones:
- In **all cases**, converting a value into a type whose range does not support that value will lead to unexpected results:
    ```cpp
    int main()
    {
        int i{ 30000 };
        char c = i; // chars have range -128 to 127

        std::cout << static_cast<int>(c) << '\n';

        return 0;
    }
    ```
- **Overflow** is well-defined on unsigned values, while it is not on signed values.
- Converting from **larger** (integral or floating point) types **to smaller** (integral or floating point) types can lead to data loss or unexpected results if the value fits in the range of the smaller type.
- In the case of floating point values, some rounding may occur due to a loss of precision in the smaller type. For example:
    ```cpp
    float f = 0.123456789; // double value 0.123456789 has 9 significant digits, but float can only support about 7
    std::cout << std::setprecision(9) << f << '\n'; // std::setprecision defined in iomanip header
    ```
    In this case, we will see loss of precision when printing the float value, giving us `0.123456791` instead of `0.123456789`.
- Converting from an integer to a floating point value generally works as long as the value fits within the range of the floating point type. However, very large integers may lose precision when converted to floating point types.
- Converting from floating point to integer types truncates the fractional part, effectively rounding towards zero.

#### Summary:
- Numeric conversions are type conversions between different numeric types, including integral conversions, floating-point conversions, floating-integral conversions, integral-floating conversions, and boolean conversions.
- Numeric conversions can be either safe (value-preserving) or unsafe (reinterpretative or lossy).
- Safe conversions preserve the value of the original type without any loss of information, while unsafe conversions may result in loss of information or unexpected results.
- Unsafe conversions should be used with caution, as they can lead to bugs and unexpected behavior in the code.


---

### S04 — 10.4 Narrowing conversions, list initialization, and constexpr initializers
#### Narrowing conversions:
In C++, a **narrowing conversion** is a potentially unsafe conversion where the destination type may not be able to hold all the values of the source type without loss of information. Narrowing conversions can lead to data loss, overflow, or unexpected behavior.

The following conversions are defined as narrowing conversions:
- From a floating-point type to an integral type.
- From a floating point type to a narrower floating-point type, unless the vlaue being converted is constexpr and it is in range of the destination type (even if the destination type does not have enough precision to represent the value exactly).
- Frtom an integral to a floating point type, unsless the value being converted is constexpr and it is in range of the destination type.
- From integral type to another integral type that cannot represent all the values of the source type, unless the value being converted is constexpr and it is in range of the destination type. This covers both wider-to-narrower and signed-to-unsigned conversions.

In most cases, implicit narrowing conversions will result in a compiler warning. These narrowing conversions should be avoided since they can lead to unexpected behavior.

> **best practice**: Because they can be unsafe, avoid narrowing conversions whenever possible.

#### Make intentional narrowing conversions explicit:
In some cases, narrowing conversions are not avoidable (e.g., some function calls). In those cases, it is best to make the narrowing conversion explicit using `static_cast`. This way, it is clear to anyone reading the code that the narrowing conversion is intentional, and the potential risks are acknowledged. For example:
```cpp
void someFcn(int i)
{
}

int main()
{
    double d{ 5.0 };

    someFcn(d); // bad: implicit narrowing conversion will generate compiler warning

    // good: we're explicitly telling the compiler this narrowing conversion is intentional
    someFcn(static_cast<int>(d)); // no warning generated

    return 0;
}
```
In this example, we use `static_cast<int>(d)` to explicitly convert the `double` value `d` to an `int` before passing it to the `someFcn` function. This makes it clear that we are aware of the narrowing conversion and have taken responsibility for it.

> **best practice**: Use `static_cast` to make intentional narrowing conversions explicit.

#### Brace initialization disallows narrowing conversions:
One of the benefits of using brace initialization is that it prevents narrowing conversions. When using brace initialization, the compiler will generate an error if a narrowing conversion is attempted. This helps catch potential issues at compile time and encourages safer coding practices. For example:
```cpp
int main()
{
    double d{ 5.7 };

    int n1 = d; // okay: implicit narrowing conversion (with warning)
    int n2(d); // okay: implicit narrowing conversion (with warning)
    int n3{ d }; // error: narrowing conversion not allowed with brace initialization

    return 0;
}
```
In this example, the attempt to initialize `n3` using brace initialization with the `double` value `d` results in a compile-time error, preventing the narrowing conversion.

If you want to do a narrowing conversion with brace initialization, you must use `static_cast` to make the conversion explicit:
```cpp
int main()
{
    double d{ 5.7 };

    int n{ static_cast<int>(d) }; // okay: explicit narrowing conversion

    return 0;
}
```

#### Some constexpr conversions are not considered narrowing:
When the source value of a narrowing conversion is not known until runtime, the result of the conversion cannot be determined until runtime as well. For example:
```cpp
#include <iostream>

void print(unsigned int u) // note: unsigned
{
    std::cout << u << '\n';
}

int main()
{
    std::cout << "Enter an integral value: ";
    int n{};
    std::cin >> n; // enter 5 or -5
    print(n);      // conversion to unsigned may or may not preserve value

    return 0;
}
```
In this example, the value of `n` is not known until runtime, so the conversion to `unsigned int` may or may not preserve the value, depending on the input.

However, if the source value is known at compile time (i.e., it is a `constexpr`), the compiler can determine whether the conversion will preserve the value or not. If the value is within the range of the destination type, the conversion is not considered narrowing, even if it would be narrowing for some other values of the source type. For example:
```cpp
#include <iostream>

int main()
{
    constexpr int n1{ 5 };   // note: constexpr
    unsigned int u1 { n1 };  // okay: conversion is not narrowing due to exclusion clause

    constexpr int n2 { -5 }; // note: constexpr
    unsigned int u2 { n2 };  // compile error: conversion is narrowing due to value change

    return 0;
}
```
In this example, the conversion of `n1` to `unsigned int` is not considered narrowing because the value `5` is within the range of `unsigned int`. However, the conversion of `n2` to `unsigned int` results in a compile-time error because the value `-5` cannot be represented as an `unsigned int`.

Instead, conversions from floating point type to integral type are always considered narrowing, even if the `constexpr` value is within range:
```cpp
int n { 5.0 }; // compile error: narrowing conversion
```

Strangely, conversions from floating point type to narrower floating point type are not considered narrowing even when there is a loss of the precision! For example:
```cpp
constexpr double d { 0.1 };
float f { d }; // not narrowing, even though loss of precision results
```

#### List initialization with constexpr initializers:
These constexpr exception clauses are incredibly useful when **list initializing** non-`int` or non-`double` objects, as we can use an `int` or `double` literal (or a`constexpr` variable of those types) to initialize other numeric types without worrying about narrowing conversions. For example:
```cpp
int main()
{
    // We can avoid literals with suffixes
    unsigned int u { 5 }; // okay (we don't need to use `5u`)
    float f { 1.5 };      // okay (we don't need to use `1.5f`)

    // We can avoid static_casts
    constexpr int n{ 5 };
    double d { n };       // okay (we don't need a static_cast here)
    short s { 5 };        // okay (there is no suffix for short, we don't need a static_cast here)

    return 0;
}
```
In this example, we can use `int` and `double` literals (or `constexpr` variables) to initialize `unsigned int`, `float`, `double`, and `short` variables without worrying about narrowing conversions or needing to use suffixes or `static_cast`.

This allows us to avoid:
- Having to use literal suffixes in most cases.
- Having to clutter our initializations with `static_cast` calls.

#### Summary:
- Narrowing conversions are potentially unsafe conversions where the destination type may not be able to hold all the values of the source type without loss of information.
- Narrowing conversions should be avoided whenever possible.
- Intentional narrowing conversions should be made explicit using `static_cast`.
- Brace initialization prevents narrowing conversions by generating compile-time errors when such conversions are attempted.
- Some `constexpr` conversions are not considered narrowing if the value being converted is known at compile time and is within the range of the destination type.
- List initialization with `constexpr` initializers allows for safe initialization of various numeric types without worrying about narrowing conversions or needing to use literal suffixes or `static_cast`.


---

### S05 — 10.5 Arithmetic conversions
What happen when we perform arithmetic operations (e.g., addition, subtraction, multiplication, division) between two operands of different types? In such cases, C++ applies a set of rules known as **usual arithmetic conversions** to bring both operands to a common type before performing the operation. This ensures that the operation is performed correctly and consistently. The matching type prodiuced by these conversions is called the **common type**.

#### The operators that require operands of the same type:
The following arithmetic operators require both operands to be of the same type:
- Binary arithmetic operators: `+`, `-`, `*`, `/`, `%`
- Binary relational operators: `==`, `!=`, `<`, `>`, `<=`, `>=`
- Binary bitwise operators: `&`, `|`, `^`
- Conditional operator: `?:` (excluding the condition expression, which is expected to be `bool`)

#### The usual arithmetic conversion rules:
The usual arithmetic conversion rules are somewhat complex, so we’ll simplify a bit. The compiler has a ranked list of types that looks something like this:
- `long double` (highest rank)
- `double`
- `float`
- `long long`
- `long`
- `int` (lowest rank)

The following rules are applied to find a matching type:

1. Step 1:
    - If one operand is an **integral type** and the other a **floating-point type**, the integral type is converted to the floating-point type (no integral promotion takes place here).
    - Otherwise, any integral operands are numerically promoted (i.e., integral promotion takes place here).
2. Step 2:
    - After promotion, if one operand is singed and the other is unsigned, the following rules are applied:
        - If the unsigned operand has rank greater than or equal to the signed operand, the signed operand is converted to the type of the unsigned operand.
        - Otherwise, if the signed operand can represent all values of the unsigned operand, the unsigned operand is converted to the type of the signed operand.
        - Otherwise, both operands are converted to the unsigned version of the type of the signed operand.
    - Otherwise, the operand with the lower rank is converted to the type of the operand with the higher rank.

#### Some examples:
In the following examples, we will use the `typeid` operator (included in the `<typeinfo>` header) to print the type of the result of the arithmetic operation.

In the first example, we will add an `int` and a `double`:
```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    int i{ 2 };
    std::cout << typeid(i).name() << '\n'; // show us the name of the type for i

    double d{ 3.5 };
    std::cout << typeid(d).name() << '\n'; // show us the name of the type for d

    std::cout << typeid(i + d).name() << ' ' << i + d << '\n'; // show us the type of i + d

    return 0;
}
```
In this example, the `int` operand `i` is converted to `double`, since `double` has a higher rank than `int`. The result of the addition is of type `double`. This will output something like:
```
int
double
double 5.5
```

In the next example, we will add two values of type `short`:
```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    short a{ 4 };
    short b{ 5 };
    std::cout << typeid(a + b).name() << ' ' << a + b << '\n'; // show us the type of a + b

    return 0;
}
```
Because neither operand appears on the priority list, both operands undergo integral promotion to type `int`. The result of the addition is of type `int`. This will output something like:
```
int 9
```

#### Signed and unsigned issues:
This prioritization hierarchy and conversion rules can cause some issues when mixing signed and unsigned types. For example:
```cpp
#include <iostream>
#include <typeinfo> // for typeid()

int main()
{
    std::cout << typeid(5u-10).name() << ' ' << 5u - 10 << '\n'; // 5u means treat 5 as an unsigned integer

    return 0;
}
```
You would expect to see `-5` as the result of `5 - 10`, but because `5u` is an unsigned integer, the signed integer `10` is converted to an unsigned integer before the subtraction. This results in a very large unsigned integer value instead of `-5`. The output will be something like:
```
unsigned int 4294967291
```

Here is another ezample:
```cpp
#include <iostream>

int main()
{
    std::cout << std::boolalpha << (-3 < 5u) << '\n';

    return 0;
}
```
In this example, the signed integer `-3` is converted to an unsigned integer before the comparison. Since unsigned integers cannot represent negative values, `-3` becomes a very large unsigned integer, which is greater than `5u`. Therefore, the comparison evaluates to `false`, and the output will be:
```
false
```

This is one of the most common pitfalls in C++, so be very careful when mixing signed and unsigned types in arithmetic operations or comparisons. In general, try to avoid `unsigned int` unless you specifically need it for a particular use case (e.g., bit manipulation, representing sizes or counts that cannot be negative).

> **Best practice**: Avoid mixing signed and unsigned types in arithmetic operations and comparisons to prevent unexpected behavior.

#### `std::common_type` and `std::common_type_t`:
In future lessons, we will encounter cases where it is useful to determine the common type of two or more types at compile time. C++ provides a type trait called `std::common_type` (defined in the `<type_traits>` header) that can be used to determine the common type resulting from the usual arithmetic conversions for a set of types. For example:
```cpp
#include <iostream>
#include <type_traits> // for std::common_type
#include <typeinfo>    // for typeid()

int main()
{
    std::cout << typeid(std::common_type<int, double>::type).name() << '\n'; // common type of int and double
    std::cout << typeid(std::common_type_t<unsigned int, long>::type).name() << '\n'; // common type of unsigned int and long

    return 0;
}
```
In this example, `std::common_type<int, double>::type` will be `double`, and `std::common_type_t<unsigned int, long>` will be `long` (assuming `long` can represent all values of `unsigned int` on the target platform). The output will be something like:
```
double
long
```

#### Summary:
- Usual arithmetic conversions are a set of rules applied to bring operands of different types to a common type before performing arithmetic operations.
- The common type is determined based on a ranked list of types and a set of conversion rules.
- Mixing signed and unsigned types can lead to unexpected behavior, so it is best to avoid such combinations in arithmetic operations and comparisons.
- C++ provides the `std::common_type` type trait to determine the common type resulting from usual arithmetic conversions at compile time.


---

### S06 — 10.6 Explicit type conversion (casting) and static_cast
Let us consider this example:
```cpp
double d = 10 /4; // integer division, result is 2.0
```
In this example, since both operands are of type `int`, the division is performed using integer division, resulting in `2` as results. This integer result is then implicitly converted to `double`, resulting in `2.0`. However, if you expected the result to be `2.5`, this would not be the case. To achieve the desired result, we need to ensure that at least one of the operands is of type `double`:
```cpp
double d = 10.0 / 4; // floating-point division, result is 2.5
// or
double d = 10 / 4.0; // floating-point division, result is 2.5
// or
double d = 10.0 / 4.0; // floating-point division, result is 2.5
```
In this case, the division is performed using floating-point division, resulting in `2.5` as expected.

But what if you are using variables instead of literals? For example:
```cpp
int a = 10;
int b = 4;
double d = a / b; // integer division, result is 2.0
```
In this case, we will have the same issue, since both `a` and `b` are of type `int`, the division is performed using integer division.

To achieve the expected behavior, C++ comes with a number of different **type casting operators** that allow us to explicitly convert a value from one type to another. The most commonly used casting operator is `static_cast`. This form of casting is known as **explicit type conversion**, since the programmer explicitly specifies the type conversion.

#### Type casting:
C++ supports 5 different type casting operators:
| Cast | Description| Safe |
|------|------------|------|
| `static_cast<type>(expression)` | Performs a compile-time type conversion between compatible types. | Yes |
| `dynamic_cast<type>(expression)` | Performs run-time type conversion on pointers or references in a polymorphic (inheritance) hierarchy. | Yes (with checks) |
| `const_cast<type>(expression)` | Adds or removes `const` or `volatile` qualifiers from a type. | Only for adding qualifiers |
| `reinterpret_cast<type>(expression)` | Reinterprets the bit-level representation of one type as if it were another type. | No |
| C-style cast: `(type)expression` | Performs a type conversion using C-style syntax, combining the behavior of `static_cast`, `const_cast`, and `reinterpret_cast`. | No |

We will cover `static_cast` and C-style casts in this section, since they are the most commonly used.

#### C-style cast:
In standard C programming, casting is done via `operator()`, like this:
```c
int n = 5;
double d = (double)n; // C-style cast
```
This form of casting is known as a **C-style cast**. C-style casts are powerful, but they are also dangerous, because they can perform multiple types of conversions (including unsafe ones) without any checks. For example, a C-style cast can perform a `reinterpret_cast`, which can lead to undefined behavior if used incorrectly.

For example:
```cpp
#include <iostream>

int main()
{
    int x { 10 };
    int y { 4 };

    std::cout << (double)x / y << '\n'; // C-style cast of x to double

    return 0;
}
```
In this example, we use a C-style cast to convert `x` to `double` before performing the division. This ensures that the division is performed using floating-point division, resulting in `2.5` as expected.

C++ also provides an alternative called `function-style cast**, which uses the same syntax as function calls:
```cpp
#include <iostream>

int main()
{
    int x { 10 };
    int y { 4 };

    std::cout << double(x) / y << '\n'; // function-style cast of x to double

    return 0;
}
```
and it works the exact same way as C-style cast.

In general, C-style casts and function-style casts should be avoided in C++ code, because they can lead to unsafe conversions and make the code harder to read and maintain. Instead, it is recommended to use the more explicit and safer C++ casting operators, such as `static_cast`. The main reasons to avoid C-style casts are:
- They can perform multiple types of conversions without any checks, which can lead to unsafe behavior.
- They make it harder to identify, since it is just a pair of parentheses, making it easy to overlook.

> **Best practice**: Avoid using C-style casts and function-style casts in C++ code. Use C++ casting operators instead.

#### `static_cast` should be used to cast most values:
The `static_cast` operator is the most commonly used casting operator in C++. It performs a *compile-time* type conversion between compatible types. `static_cast` return a temporary variable of the specified type, which can then be used in expressions or assigned to variables of that type.
It is safer than C-style casts because it only allows conversions that are checked at compile time, preventing some unsafe conversions, and are easier to identify in the code. For example:
```cpp
#include <iostream>

int main()
{
    char c { 'a' };
    std::cout << static_cast<int>(c) << '\n'; // prints 97 rather than a

    return 0;
}
```
In this example, we use `static_cast<int>(c)` to convert the `char` value `c` to an `int` before printing it. This ensures that the ASCII value of the character is printed instead of the character itself.

Here is how we could use `static_cast` to fix the earlier division example:
```cpp
#include <iostream>

int main()
{
    int x { 10 };
    int y { 4 };
    std::cout << static_cast<double>(x) / y << '\n'; // static_cast of x to double

    return 0;
}
```
In this example, we use `static_cast<double>(x)` to convert `x` to `double` before performing the division. This ensures that the division is performed using floating-point division, resulting in `2.5` as expected.

There are two important properties of `static_cast`:
- It provides compile-time type checking, preventing some unsafe conversions.
- It is intentionally less powerful than C-style casts, as it will prevent certain kinds of dangerous conversions.

#### Using `static_cast` to make narrowing conversions explicit:
As discussed in the previous section on narrowing conversions, narrowing conversions can lead to data loss or unexpected behavior. For example:
```cpp
int i { 48 };
char ch = i; // implicit narrowing conversion
```
will cause an implicit narrowing conversion from `int` to `char`, which may lead to data loss if the value of `i` exceeds the range of `char`.
To make this narrowing conversion explicit, we can use `static_cast`:
```cpp
int i { 48 };
char ch = static_cast<char>(i); // explicit narrowing conversion
```
In this way, it is clear to anyone reading the code that the narrowing conversion is intentional, and the potential risks are acknowledged.

Another example:
```cpp
int i { 1000 };
i = static_cast<int>(i / 2.5); // explicit narrowing conversion from double to int
```
In this example, we use `static_cast<int>(i / 2.5)` to explicitly convert the result of the division (which is of type `double`) to `int`. This makes it clear that we are aware of the narrowing conversion and have taken responsibility for it.

#### Casting vs initializing a temporary object:
We have generally two conventional ways to convert a value from one type to another:
1. `static_cast<type>(expression)`: this returns a temporary object of the specified type, **direct-initialized** with the value of the expression.
2. `type {expression}`: this creates a temporary object of the specified type, **direct-list-initialized** with the value of the expression.

In general, we should avoid using the second form for type conversions, because it can performar a dangerous conversion under the hood (e.g., narrowing conversion).

There are three notable differences between these two forms:
1. `type {expression}` uses list initialization, which disallows narrowing conversions, while `static_cast<type>(expression)` allows narrowing conversions (but makes them explicit). For example, it could be a problem depending on the OS you are using (32-bit vs 64-bit):
    ```cpp
    #include <iostream>

    int main()
    {
        int x { 10 };
        int y { 4 };

        // We want to do floating point division, so one of the operands needs to be a floating point type
        std::cout << double{x} / y << '\n'; // okay if int is 32-bit, narrowing if x is 64-bit
    }
    ```
    This will work fine for 32-bit systems, since `int` can be safely converted to `double` without narrowing. However, on 64-bit systems, this will result in a compile-time error due to narrowing conversion from `int` (64-bit) to `double` (which may not be able to represent all 64-bit integers exactly), and it will not compile.
2. `static_cast` makes it clearer that a type conversion is taking place, while `type {expression}` may not be as obvious to readers of the code.
3. Direct-list-initialization of a temporary object only allows single-word type names (e.g., `int`, `double`, while `unsigned int`, `long long`, etc. are not allowed). `static_cast` allows multi-word type names, and is therefore more flexible.

> **Best practice**: Use `static_cast<type>(expression)` for type conversions instead of `type {expression}` to avoid potential narrowing conversions and improve code clarity.

#### Summary:
- Explicit type conversion (casting) allows programmers to convert values from one type to another intentionally.
- C-style casts and function-style casts should be avoided in C++ code due to their potential for unsafe conversions and reduced code clarity.
- `static_cast` is the preferred casting operator for most type conversions, as it provides compile-time type checking and makes conversions explicit.
- `static_cast` should be used to make intentional narrowing conversions explicit.
- When converting types, prefer using `static_cast<type>(expression)` over `type {expression}` to avoid potential narrowing conversions and improve code clarity.


---

### S07 — 10.7 Typedefs and type aliases
#### Type aliases:
In C++, you can define a new name for an existing type using **type aliases**. Type aliases can make your code more readable and easier to maintain by providing meaningful names for complex types. There are two ways to create type aliases in C++:
1. Using the `typedef` keyword (available since C):
    ```cpp
    typedef existing_type new_type_name;
    ```
2. Using the `using` keyword (introduced in C++11):
    ```cpp
    using new_type_name = existing_type;
    ```

Both methods achieve the same result, but the `using` syntax is generally preferred in modern C++ due to its clarity and flexibility, especially when dealing with template types.

For example:
```cpp
using Distance = double; // Distance is now an alias for double
```
and then we can use `Distance` as a type in our code:
```cpp
#include <iostream>

int main()
{
    using Distance = double; // define Distance as an alias for type double

    Distance milesToDestination{ 3.4 }; // defines a variable of type double

    std::cout << milesToDestination << '\n'; // prints a double value

    return 0;
}
```
In this example, we define `Distance` as an alias for `double`, and then use it to declare a variable `milesToDestination`. This improves code readability by providing a meaningful name for the type.
The compiler will substitute `Distance` with `double` during compilation, so there is no runtime overhead associated with using type aliases.

#### Naming type aliases:
There are three main conventions for naming type aliases:
1. `*_t` suffix: This convention appends `_t` to the end of the type alias name to indicate that it is a type. This is used by the standard library for global types (e.g., `size_t`, `nullptr_t`), so it could cause name clashes if used in the global namespace. Therefore, it is best to avoid using this convention in the global namespace.
2. `_type` suffix: This convention appends `_type` to the end of the type alias name (e.g., `index_type`, `value_type`). This is used by some standard libraries (like `std::string`) to name nested type aliases (e.g., `std::string::size_type`).
3. No suffix: This convention uses a descriptive name without any suffix (e.g., `Distance`, `Index`). This is often the most readable option, especially for simple type aliases.

In modern C++, it is good practice to name type aliases with a **starting capital letter** (e.g., `Distance`, `Index`, `ValueType`) and avoid using suffixes, unless there is a specific reason to do so (e.g., to avoid name clashes). For example:
```cpp
using Distance = double; // good: descriptive name with starting capital letter
using IndexType = std::size_t; // good: descriptive name with starting capital letter and Type suffix
using value_t = int; // bad: uses _t suffix in global namespace
```

> **Best practice**: Name type aliases with a starting capital letter and avoid using suffixes unless necessary to prevent name clashes.

#### Type aliases are not distinct types:
It is important to note that type aliases do not create new distinct types. They are simply alternative names for existing types. This means that variables of the aliased type can be used interchangeably with variables of the original type. For example:
```cpp
#include <iostream>

int main()
{
    using Distance = double; // define Distance as an alias for type double
    using Length = double; // define Length as an alias for type double

    Distance d1 { 5.0 }; // variable of type double
    double d2 { 10.0 };  // variable of type double
    Length d3 { 7.5 };   // variable of type double

    double sum = d1 + d2 + d3; // valid: Distance, Length, and double are interchangeable

    std::cout << "Sum: " << sum << '\n'; // prints 22.5
    return 0;
}
```
In this example, we define two type aliases, `Distance` and `Length`, both of which are aliases for `double`. We can use variables of these aliased types interchangeably with variables of type `double`, as they are not distinct types.

#### The scope of type aliases:
Because the scope is a property of the identifier, type aliases follow the same scoping rules as other identifiers in C++. This means that type aliases can be defined in different scopes, such as global scope, block scope, or within classes and namespaces. For example:
```cpp
#ifndef MYTYPES_H
#define MYTYPES_H

    using Miles = long;
    using Speed = long;

#endif // MYTYPES_H
```
will define `Miles` and `Speed` as type aliases for `long` in the global scope, making them accessible throughout the program.

#### Typedefs:
A **typedef** (short for "type definition") is an older way to create type aliases in C++. It uses the `typedef` keyword followed by the existing type and the new type name. For example:
```cpp
// The following aliases are identical
typedef long Miles;
using Miles = long;
```
Both `typedef` and `using` achieve the same result of creating a type alias. However, the `using` syntax is generally preferred in modern C++ due to its clarity and flexibility, especially when dealing with template types.

Typedef have few syntactical issues:
- It’s easy to forget whether the name of the typedef or the name of the type to alias comes first.
   ```cpp
    typedef Distance double; // incorrect (typedef name first)
    typedef double Distance; // correct (aliased type name first)
    ```
- The syntax for typedefs can get ugly with more complex types:
    ```cpp
    typedef int (*FcnType)(double, char); // FcnType hard to find
    using FcnType = int(*)(double, char); // FcnType easier to find
    ```

#### When to use type aliases:
Type aliases are useful in several scenarios:
- Platform independence: When writing code that needs to run on multiple platforms, type aliases can help abstract away platform-specific types (e.g., using `std::int32_t` for a 32-bit integer).
- Code readability: Type aliases can provide meaningful names for complex types, making the code easier to read and understand.
- Give meaning to values: Type aliases can help convey the intended use of a type (e.g., using `Distance` for a variable representing distance).
- Easier code maintenance: If the underlying type needs to change, you only need to update the type alias definition instead of changing all occurrences of the type throughout the code.

#### Using type aliases for platform independent coding:
When writing code that needs to run on multiple platforms, it is important to use types that have consistent sizes across different systems. The C++ standard library provides fixed-width integer types in the `<cstdint>` header, such as `std::int8_t`, `std::int16_t`, `std::int32_t`, and `std::int64_t`, which guarantee specific sizes regardless of the platform. For example, you could define type aliases for platform-independent integer types like this:
```cpp
#ifdef INT_2_BYTES
using int8_t = char;
using int16_t = int;
using int32_t = long;
#else
using int8_t = char;
using int16_t = short;
using int32_t = int;
#endif
```
In this way, you can use `int8_t`, `int16_t`, and `int32_t` in your code, and they will have consistent sizes across different platforms.

For example:
```cpp
#include <cstdint> // for fixed-width integers
#include <iostream>

int main()
{
    std::int8_t x{ 97 }; // int8_t is usually a typedef for signed char
    std::cout << x << '\n';

    return 0;
}
```
will most likely print `a`, because `std::int8_t` is typically defined as a typedef for `signed char`, which has an ASCII value of `97` for the character `'a'`.

#### Using type aliases to make complex types easier to read:
Type aliases can be particularly useful when dealing with complex types, such as function pointers or template types. For example:
```cpp
#include <string> // for std::string
#include <vector> // for std::vector
#include <utility> // for std::pair

bool hasDuplicates(std::vector<std::pair<std::string, int>> pairlist)
{
    // some code here
    return false;
}

int main()
{
     std::vector<std::pair<std::string, int>> pairlist;

     return 0;
}
```
In this example, the type `std::vector<std::pair<std::string, int>>` is quite complex and can make the code harder to read. To improve readability, we can create a type alias for this complex type:
```cpp
#include <string> // for std::string
#include <vector> // for std::vector
#include <utility> // for std::pair

using VectPairSI = std::vector<std::pair<std::string, int>>; // make VectPairSI an alias for this crazy type

bool hasDuplicates(VectPairSI pairlist) // use VectPairSI in a function parameter
{
    // some code here
    return false;
}

int main()
{
     VectPairSI pairlist; // instantiate a VectPairSI variable

     return 0;
}
```
In this modified example, we define `VectPairSI` as an alias for `std::vector<std::pair<std::string, int>>`. This makes the code more readable and easier to maintain.

#### Using type aliases to document the meaning of a value:
Type aliases can also be used to provide meaningful names for types that convey the intended use of a value. For example, given the following function:
```cpp
int gradeTest();
```
it is not immediately clear what the return value represents. To improve clarity, we can use a type alias:
```cpp
using TestScore = int;
TestScore gradeTest();
```
In this example, we define `TestScore` as an alias for `int`, which makes it clear that the return value of `gradeTest` represents a test score. This improves code readability and helps convey the intended meaning of the value.

#### Using type aliases for easier code meaintenance:
Type aliases can simplify code maintenance by allowing you to change the underlying type in one place, rather than updating all occurrences throughout the code. For example:
```cpp
#include <iostream>

using Distance = double; // define Distance as an alias for type double

void printDistance(Distance d)
{
    std::cout << "Distance: " << d << " miles\n";
}

int main()
{
    Distance d1 { 5.0 };
    printDistance(d1);

    return 0;
}
```
In this example, if we later decide to change the underlying type of `Distance` from `double` to `float`, we only need to update the type alias definition:
```cpp
using Distance = float; // change Distance to alias for type float
```

#### Downsides and conclusions:
While type aliases offer many benefits, there are some downsides to consider:
- Type aliases do not create distinct types, which means that they cannot provide type safety. For example, you cannot prevent mixing different type aliases that are based on the same underlying type.
- Overuse of type aliases can lead to confusion if the aliases are not well-named or if there are too many aliases in use.

#### Summary:
- Type aliases provide alternative names for existing types, improving code readability and maintainability.
- Type aliases can be created using the `using` keyword or the `typedef` keyword, with `using` being the preferred modern approach.
- Type aliases do not create distinct types; they are simply alternative names for existing types.
- Type aliases can be defined in various scopes, following the same scoping rules as other identifiers.
- Type aliases are useful for platform independence, code readability, conveying meaning, and easier code maintenance.


---

### S08 — 10.8 Type deduction for objects using the `auto` keyword
In C++, we are required to provide explicit type information when declaring variables. However, sometimes could be a bit redundant. For example:
```cpp
double d { 3.14 };
```
In this example, we explicitly specify the type of the variable `d` as `double`. However, since we are initializing `d` with a `double` literal (`3.14`), the compiler could easily deduce the type of `d` without us having to specify it explicitly.

#### Type deduction for initialized variables using `auto`:
**Type deduction** (also called **type inference**) is a feature in C++ that allows the compiler to automatically deduce the type of a variable based on its initializer. This can help reduce redundancy and improve code readability. For example, we can use the `auto` keyword to declare a variable without explicitly specifying its type:
```cpp
int main()
{
    auto d { 5.0 }; // 5.0 is a double literal, so d will be deduced as a double
    auto i { 1 + 2 }; // 1 + 2 evaluates to an int, so i will be deduced as an int
    auto x { i }; // i is an int, so x will be deduced as an int

    return 0;
}
```
In this example, the compiler deduces the types of `d`, `i`, and `x` based on their initializers. `d` is deduced as `double`, while both `i` and `x` are deduced as `int`.

Because function calls are valid expressions, we can also use `auto` to deduce the return type of a function:
```cpp
int add(int x, int y)
{
    return x + y;
}

int main()
{
    auto sum { add(5, 6) }; // add() returns an int, so sum's type will be deduced as an int

    return 0;
}
```
Here the compiler will deduce the type of `sum` as `int`, since the `add` function returns an `int`.

LIteral suffixes can be used in combination with type deduction to specify a particular type:
```cpp
int main()
{
    auto a { 1.23f }; // f suffix causes a to be deduced to float
    auto b { 5u };    // u suffix causes b to be deduced to unsigned int

    return 0;
}
```


Variables using type deduction can also use other specifiers/qualifiers, such as `const` and `constexpr`:
```cpp
int main()
{
    const auto pi { 3.14159 }; // pi is deduced as const double
    constexpr auto e { 2.71828 }; // e is deduced as constexpr double

    return 0;
}
```
In this example, `pi` is deduced as `const double`, and `e` is deduced as `constexpr double`.

#### Type deduction must have something to deduce from:
When using type deduction with `auto`, the variable must be initialized with an expression that provides enough information for the compiler to deduce the type. For example, the following code will not compile:
```cpp
#include <iostream>

void foo()
{
}

int main()
{
    auto a;           // The compiler is unable to deduce the type of a
    auto b { };       // The compiler is unable to deduce the type of b
    auto c { foo() }; // Invalid: c can't have type incomplete type void

    return 0;
}
```
In these cases, the compiler cannot deduce the type of the variables `a`, `b`, and `c` because there is no initializer that provides type information. The compiler will generate an error indicating that it cannot deduce the type.

#### Type deduction drops `const` from the deducted type:
When using type deduction with `auto`, any `const` qualifier on the initializer is dropped from the deduced type. For example:
```cpp
int main()
{
    const int a { 5 }; // a has type const int
    auto b { a };      // b has type int (const dropped)

    return 0;
}
```
In this example, `a` is declared as `const int`, but when we use type deduction to declare `b`, the `const` qualifier is dropped, and `b` is deduced as `int`. So, be careful when using `auto` with `const` variables, as the resulting variable may not be `const`!

If you want to preserve the `const` qualifier in the deduced type, you can explicitly specify it in the declaration:
```cpp
const auto b { a }; // b has type const int (const dropped but reapplied)
```
In this case, `b` is explicitly declared as `const auto`, so it retains the `const` qualifier and is deduced as `const int`.

> **Note**: `auto` keyword drops `const` from the deduced type, so if you want the resulting variable to be `const`, you need to explicitly specify it.

#### Type deduction for string literals:
For historical reasons, string literals in C++ have a strange type. Therefore, when using type deduction with `auto`, you could notice some unexpected behavior. For example:
```cpp
auto s { "Hello, world" }; // s will be type const char*, not std::string
```
In this example, the string literal `"Hello, world"` has the type `const char[14]`, which decays to `const char*` when used in an expression. Therefore, `s` is deduced as `const char*`, not `std::string`.

If you want to deduce a `std::string` type, you need to explicitly construct a `std::string` object:
```cpp
#include <string>
#include <string_view>

int main()
{
    using namespace std::literals; // easiest way to access the s and sv suffixes

    auto s1 { "goo"s };  // "goo"s is a std::string literal, so s1 will be deduced as a std::string
    auto s2 { "moo"sv }; // "moo"sv is a std::string_view literal, so s2 will be deduced as a std::string_view

    return 0;
}
```
you will have to use `s` suffix to create a `std::string` literal, or `sv` suffix to create a `std::string_view` literal.

#### type deduction and constexpr:
Because `constexpr` is not part of the type system, it cannot be deducted by the `auto` keyword. However, `constexpr` variable is implicitely `const`, so you can add `constexpr` to the declaration to make the variable `constexpr`. For example:
```cpp
int main()
{
    constexpr double a { 3.4 };  // a has type const double (constexpr not part of type, const is implicit)

    auto b { a };                // b has type double (const dropped)
    const auto c { a };          // c has type const double (const dropped but reapplied)
    constexpr auto d { a };      // d has type const double (const dropped but implicitly reapplied by constexpr)

    return 0;
}
```
In this example, `a` is declared as `constexpr double`, which is implicitly `const double`. When we use type deduction to declare `b`, the `const` qualifier is dropped, and `b` is deduced as `double`. For `c`, we explicitly specify `const`, so it is deduced as `const double`. For `d`, we declare it as `constexpr`, so it is also deduced as `const double`.

#### Type deduction benefits and downsides:
Using type deduction with `auto` can provide several benefits:
- If two or more variables are defined on sequential lines, using `auto` will align the types visually, improving code readability.
    ```cpp
    // harder to read
    int a { 5 };
    double b { 6.7 };

    // easier to read
    auto c { 5 };
    auto d { 6.7 };
    ```
- The deduction works only with variables that have initializers, so if you are in the habit of using type deduction, it can help avoid uninitialized variables.
    ```cpp
    int x; // oops, we forgot to initialize x, but the compiler may not complain
    auto y; // the compiler will error out because it can't deduce a type for y
    ```
- They guarantee that there will be no unintended performance-impacting conversions:
    ```cpp
    std::string_view getString();   // some function that returns a std::string_view

    std::string s1 { getString() }; // bad: expensive conversion from std::string_view to std::string (assuming you didn't want this)
    auto s2 { getString() };        // good: no conversion required
    ```

Type deduction also has some downsides:
- The deduction obscures the actual type of the variable, which can make the code harder to understand for readers who are not familiar with the codebase. For example:
    ```cpp
    auto x { someFunction() }; // what is the type of x?
    auto y { 5 }; // oops, we wanted a double here but we accidentally provided an int literal
    ```
- If the type of the initializer changes, the type of the variable will also change, which can lead to unexpected behavior if the code relies on a specific type. For example:
    ```cpp
    auto sum { add(5, 6) + gravity }; // what if return type of add() changes from int to double?
    ```

> **Best practice**: Use type deduction (`auto`) when the type of the object does not matter, or when it improves code readability. Avoid using `auto` when the specific type is important for understanding and running the code correctly.

#### Summary:
- Type deduction using the `auto` keyword allows the compiler to automatically deduce the type of a variable based on its initializer.
- Type deduction improves code readability and reduces redundancy, but it can also obscure the actual type of the variable.
- When using `auto`, the `const` qualifier is dropped from the deduced type, so be cautious when working with `const` variables.
- Type deduction requires an initializer to provide enough information for the compiler to deduce the type.
- Type deduction can be beneficial for improving code readability and avoiding uninitialized variables, but it can also lead to unexpected behavior if the type of the initializer changes.


---

### S09 — 10.9 Type deduction for functions
Consider the following function:
```cpp
int add(int x, int y)
{
    return x + y;
}
```
When this function is compiled, the compiler will determine that `x + ` evaluates to `int`, so the return type of the function is `int`. However, what if we wanted to create a more generic `add` function that can work with different types, such as `double`, `float`, or even user-defined types? One way to achieve this is by using **function templates**, which allow us to define a function that can operate on different types without having to write separate functions for each type.

#### return type deduction with `auto`:
In C++14 and later, we can use the `auto` keyword to enable return type deduction for functions. This allows the compiler to automatically deduce the return type of a function based on the type of the expression in the `return` statement. For example:
```cpp
auto add(int x, int y)
{
    return x + y; // return type will be deduced based on the types of x and y
}
```
In this example, the `add` function takes two parameters of type `auto`, which means that the compiler will deduce their types based on the arguments passed to the function. The return type of the function is also deduced based on the expression `x + y`.

Here is how we can use the `add` function with different types:
```cpp
#include <iostream>

auto add(int x, int y)
{
    return x + y; // return type will be deduced based on the types of x and y
}

int main()
{
    std::cout << add(5, 6) << '\n';         // adds two ints, returns int
    std::cout << add(3.5, 2.5) << '\n';     // adds two doubles, returns double
    std::cout << add(1.2f, 3.4f) << '\n';   // adds two floats, returns float

    return 0;
}
```
In this example, we call the `add` function with different types of arguments (ints, doubles, and floats), and the compiler deduces the return type accordingly.

Be careful, when using `auto` for return deduction, all the `return` statements in the function must return values of the same type, otherwise the compiler will generate an error. For example:
```cpp
auto faultyFunction(int x)
{
    if (x > 0)
        return x;        // returns type of x
    else
        return 0.0;     // returns double, causes error if x is not double
}
```
will cause a compilation error if `x` is not of type `double`, because the two `return` statements return different types.

#### Benefits of return type deduction:
The main benefits of this, it is that it prevenets us from having mismatched return types in functions, which can lead to unexpected behavior. It also allows us to write more generic functions that can work with different types without having to specify the return type explicitly. Without `auto`, the compiler could throw an error, or even worse, silently perform an unintended conversion.

In some other cases, the return type of a function can be quite complex, especially when dealing with templates or nested types. Using `auto` for return type deduction can simplify the function declaration and improve code readability. For example:
```cpp
// let compiler determine the return type of unsigned short + char
auto add(unsigned short x, char y)
{
    return x + y;
}
```

#### Downsides of return type deduction:
There are two main downsides to using return type deduction with `auto`:
- Function with deducted return must be fully defined before they can be used (a forward declaration is not sufficient). For example:
    ```cpp
    #include <iostream>

    auto foo();

    int main()
    {
        std::cout << foo() << '\n'; // the compiler has only seen a forward declaration at this point

        return 0;
    }

    auto foo()
    {
        return 5;
    }
    ```
    will cause a compilation error, because the compiler cannot deduce the return type of `foo` from the forward declaration alone.

    When using type deduction with objects, the initializer is always present as part of the same statement. However, with functions, the return type is not part of the function signature, which can make it harder to understand the function's behavior at a glance. For example:
    ```cpp
    auto add(auto x, auto y); // what is the return type of add()?
    ```
    In this case, it is not immediately clear what the return type of `add` is, since it is not specified in the function signature.

> **Best practice**: In general, avoid using return type deduction with `auto` for functions.

#### Trailing return type syntax:
Before C++14, return type deduction was not available. However, C++11 introduced a feature called **trailing return type syntax**, which allows us to specify the return type of a function after the parameter list using the `->` syntax. This can be useful when the return type depends on the types of the parameters. For example:
```cpp
auto add(int x, int y) -> int
{
  return (x + y);
}
```
In this example, we specify the return type of the `add` function as `int` using the trailing return type syntax. This is particularly useful when the return type is complex or depends on the types of the parameters.

Why would you want to use this? Here some reasones:
- For functions with complex return types, a trailing return type can make the function easier to read:
    ```cpp
    #include <type_traits> // for std::common_type

    std::common_type_t<int, double> compare(int, double);         // harder to read (where is the name of the function in this mess?)
    auto compare(int, double) -> std::common_type_t<int, double>; // easier to read (we don't have to read the return type unless we care)
    ```
- The trailing return type syntax can aligned the names of your functions vertically, improving code readability:
    ```cpp
    // harder to read
    std::vector<int> getVector();
    std::map<std::string, int> getMap();

    // easier to read
    auto getVector() -> std::vector<int>;
    auto getMap() -> std::map<std::string, int>;
    ```

#### Type deduction cannot be used for function parameter types:
Many new programmers try something like this:
```cpp
#include <iostream>

void addAndPrint(auto x, auto y)
{
    std::cout << x + y << '\n';
}

int main()
{
    addAndPrint(2, 3); // case 1: call addAndPrint with int parameters
    addAndPrint(4.5, 6.7); // case 2: call addAndPrint with double parameters

    return 0;
}
```
However, type deduction does not work for function parameter types (prior to C++20). The above code will not compile, because the compiler cannot deduce the types of `x` and `y` in the function signature.

In C++20 and later, the `auto` keyword was extended so that the above program will compile and function correctly -- however, `auto` is not invoking type deduction in this case. Rather, it is triggering a different feature called `function templates` that was designed to actually handle such cases.

#### Summary:
- Return type deduction using the `auto` keyword allows the compiler to automatically deduce the return type of a function based on the type of the expression in the `return` statement.
- Return type deduction improves code readability and reduces redundancy, but it can also obscure the actual return type of the function.
- All `return` statements in a function with deduced return type must return values of the same type.
- Trailing return type syntax can be used to specify the return type of a function after the parameter list, improving readability for complex return types.
- Type deduction cannot be used for function parameter types (prior to C++20).


---

### SX - 10.x Summary and quiz
Try to answer the questions and the quizzes, and then check the solutions in the `exercises` folder.

Enjoy and have fun! :)


---

## 🧭 Summary

Type conversion, aliasing, and deduction are the foundation of **type safety and clarity** in C++.  
You learned that conversions happen all the time — sometimes automatically (implicit conversions), and sometimes explicitly (via `static_cast`). Understanding when and how they occur is crucial to avoid subtle bugs, rounding errors, or undefined behavior.  

You also saw how **numeric promotions** and **arithmetic conversions** unify operands to a common type, ensuring consistent behavior across different operations.  
With **type aliases**, you can simplify complex declarations and document intent. Finally, **type deduction** using `auto` allows cleaner, less redundant code — as long as it remains clear what the deduced types are.

> **Takeaway:** C++ gives you full control over type conversions — use that power to write expressive, efficient, and predictable code.

---

### 🧱 Core Concepts You Mastered

- 🔄 Implicit and explicit type conversions  
- 🧮 Numeric promotions (integral & floating-point)  
- ⚠️ Safe vs. unsafe conversions and narrowing conversions  
- 🧰 Using `static_cast` for safe explicit conversions  
- 🧱 Type aliases (`using`, `typedef`) for code clarity  
- 🧠 Type deduction with `auto` and `constexpr`  
- ⚖️ Usual arithmetic conversions and mixed-type expressions  
- 🧩 Trailing return type and `std::common_type` for deducing result types  
- 📘 Best practices for clarity and safety in type management  