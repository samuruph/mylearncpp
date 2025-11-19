# Chapter 12 - Compound Types: References and Pointers

## 🧭 Overview
This chapter explored how C++ handles references, pointers, function parameters, return mechanisms, type deduction, and optional values.  
You learned how functions communicate through **in**, **out**, and **in-out parameters**, when to use **return by value, reference, or address**, how **auto** deduces types with pointers/references and constness, and how **`std::optional`** provides a modern and safe way to represent “maybe-value” semantics.  
These tools allow you to write more efficient, expressive, and safer code — avoiding unnecessary copies, preventing dangling references, and making APIs clearer.


---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch12_first
./build/ch12_first
```

---

## 🎯 Learning Outcomes

By the end of this chapter, you understand:

- 🔗 The difference between **return by value**, **reference**, and **address**, including lifetime constraints.  
- 🧭 What **dangling references/pointers** are and why they cause undefined behavior.  
- 📥 The role of **in**, **out**, and **in-out parameters**, and why out parameters are discouraged.  
- ✨ Why **const references** are often preferred for efficient, read-only access.  
- 🧩 How **`auto` type deduction** handles references, pointers, and top- vs low-level const.  
- 📌 The distinction between **top-level const** and **low-level const**.  
- 📦 How **`std::optional<T>`** represents values that may or may not be present.  
- 💡 When returning an optional is preferable to sentinels or exceptions.


---

## Sections

### S01 — 12.1 Introduction to compound data types
In a previous chapter we covered fundamental data types such as `int`, `char`, and `double`. These data types do not cover the full range of needs as we begin to do more complex programming. In this chapter we will explore compound data types, specifically references and pointers.

For example, imagine you want to write a math program that multiplies two fractions together. A fraction has two parts: a numerator and a denominator. To represent a fraction in C++, we could use two separate `int` variables:
```cpp
#include <iostream>

int main()
{
    // Our first fraction
    int num1 {};
    int den1 {};

    // Our second fraction
    int num2 {};
    int den2 {};

    // Used to eat (remove) the slash between the numerator and denominator
    char ignore {};

    std::cout << "Enter a fraction: ";
    std::cin >> num1 >> ignore >> den1;

    std::cout << "Enter a fraction: ";
    std::cin >> num2 >> ignore >> den2;

    std::cout << "The two fractions multiplied: "
        << num1 * num2 << '/' << den1 * den2 << '\n';

    return 0;
}
```
that will print:
```
Enter a fraction: 1/2
Enter a fraction: 3/4
The two fractions multiplied: 3/8
```
However, this approach has some downsides. For example, if we wanted to create a function that multiplies two fractions together, we would need to pass in four separate `int` parameters (two for each fraction). This can quickly become cumbersome and error-prone.

Now imagine you want to write a program that keeps a list of eployees IDs. Each employee has a unique ID number, and you could try something like this:
```cpp
int main()
{
    int id1 { 42 };
    int id2 { 57 };
    int id3 { 162 };
    // and so on
}
```
But imagine now that you have 1000 employees! You would need to create 1000 separate `int` variables, which is not practical.

To solve these problems, we will need to move aways from fundamental data types and towards compound data types.

#### Compund data types:
Fortunately, C++ supports a set of data types called **compound data types** (also called **composite data types**). Compound data types are data types that are composed of other existing data types. These compound data types allow us to group related data together, making it easier to manage and manipulate.

C++ supports the following compund data types:
- **Functions**: compound data type that allow us to group related code together. Functions can take parameters and return values, making them a powerful tool for code reuse and organization.
- **C-style arrays**: C-style arrays are a type of compound data type that allow us to group related data together in a contiguous block of memory. C-style arrays are fixed in size and can be accessed using an index.
- **Pointers types**: compound data type that allow us to store the memory address of another variable. Pointers are powerful because they allow us to manipulate data indirectly, which can be useful in certain situations.
    - *Pointer to objects*
    - *Pointer to functions*
- **POinter to member types**: compound data type that allow us to store the memory address of a member variable or member function of a class. Pointer to member types are useful when we want to manipulate class members indirectly.
    - *Pointer to member data*
    - *Pointer to member functions*
- **Reference types**: compound data type that allow us to create an alias for another variable. References are useful because they allow us to manipulate data indirectly, similar to pointers, but with a simpler syntax.
    - *L-value references*
    - *R-value references*
- **Enumerated types**: compound data type that allow us to define a set of named values. Enumerated types are useful when we want to represent a set of related values in a more meaningful way.
    - *Unscoped enumerations*
    - *Scoped enumerations*
- **Class types**: compound data type that allow us to define our own custom data types. Class types are powerful because they allow us to encapsulate data and behavior together, making it easier to manage and manipulate complex data.
    - *Structs*
    - *Classes*
    - *Unions*

In the previous chapters, we have already been useing some of these compound data types, such as functions and class types. For example, consider this function:
```cpp
void doSomething(int x, double y)
{
    // function body
}
```
The type of this function is 'void(int, double)'. You can easily note that this is composed of fundamental data types, making it a compound data type.

Since this is a very big topic, we will cover them in different chapters, starting from more easy compund data types (e.g., `l-value references` and `pointers`), then `unscoped enumerations`, `scoped enumerations`, and our first class type: `structs`. Then, in later chapters, we will cover more advanced compound data types such as `classes` and `unions`, and other `array` types such as `std::array` and `std::vector` (inclusing the already covered `std::string`).

#### Summary:
- **Compound data types** are data types that are composed of other existing data types.
- C++ supports several compound data types, including functions, C-style arrays, pointer types, pointer to member types, reference types, enumerated types, and class types.
- Compound data types allow us to group related data together, making it easier to manage and manipulate complex data.


---

### S02 - 12.2 Value categories (lvalues and rvalues)
Before talking about our first compund type, we will need to understand **value categories** in C++. Value categories are a way to classify expressions based on their behavior and properties. In C++, there are two main value categories: **lvalues** and **rvalues**.

In a previous chapter, we defined an **expressions** as a *"a combination of literals, variables, operators, and function calls that can be executed to produce a singular value"*. For example:
```cpp
#include <iostream>

int main()
{
    std::cout << 2 + 3 << '\n'; // The expression 2 + 3 produces the value 5

    return 0;
}
```
In this example, the expression `2 + 3` produces the value `5`.

In a later chapter, we have seen that expressions can have **side effects**. Side effects are changes to the program state that occur as a result of evaluating an expression. For example:
```cpp
#include <iostream>

int main()
{
    int x { 5 };
    ++x; // This expression statement has the side-effect of incrementing x
    std::cout << x << '\n'; // prints 6

    return 0;
}
```
In this example, the expression `++x` has the side effect of incrementing the value of `x`.

Besides producing values and having side effects, expressions can do one more thing: they can **evaluate** objects or functions.

#### The propery of an expression:
An expression can be classified based on two properties:
1. **Type**: the data type of the value produced by the expression (e.g., `int`, `double`, `char`, etc.).
2. **Value**: the actual value produced by the expression (e.g., `5`, `3.14`, `'a'`, etc.).

#### 1. The type of an expression:
The type of an expression is equivalent to the type of the value, object, or function that results from evaluating the expression. For example:
```cpp
int main()
{
    auto v1 { 12 / 4 }; // int / int => int
    auto v2 { 12.0 / 4 }; // double / int => double

    return 0;
}
```
For `v1`, the compiler will determine (at compile time) that the type of the expression `12 / 4` is `int`, since both operands are `int`. For `v2`, the compiler will determine that the type of the expression `12.0 / 4` is `double`, since one of the operands is `double`.

The compiler can use the type of an expression to determine whether an expression is valid in a given context. For example:
```cpp
#include <iostream>

void print(int x)
{
    std::cout << x << '\n';
}

int main()
{
    print("foo"); // error: print() was expecting an int argument, we tried to pass in a string literal

    return 0;
}
```
In this example, the compiler will produce an error because the type of the expression `"foo"` is `const char*`, which is not compatible with the expected type of `int` for the `print()` function.

Note that the type of an expression must be determined at compile time, otherwise type checking and type deduction would not be possible. However, the value of an expression can be evaluated at either compile time or runtime, depending on the context (`constexpr` vs non-`constexpr` contexts).

#### 2. The value category of an expression:
Now conside the program:
```cpp
int main()
{
    int x{};

    x = 5; // valid: we can assign 5 to x
    5 = x; // error: can not assign value of x to literal value 5

    return 0;
}
```
In this example, the expression `x` can appear on the left side of an assignment operator (`=`), while the expression `5` cannot. How the compiler can know which expressions can legally appear on either side of an assignment operator?

To determine whether an expression can appear on the left side of an assignment operator, the compiler uses the concept of **value category**. This indicates whether an expression resolves to a value, a function, or an object of some sort.

Prior to C++11, there were only two value categories: **lvalues** and **rvalues**. Since C++11, the value categories have been expanded to include more categories (`gvalue`, `prvalue`, and `xvalue`), to support new feature called `move semantics`. However, for the purpose of understanding references and pointers, we will only focus on the original two categories: **lvalues** and **rvalues**.

#### Lvalue and rvalue expressions:
An **lvalue expression**, short for **left value expression** or **location value expression**, is an expression that evaluates to an identifiable object or function (or bit-field) that has a persistent memory address. This means that the entity can be accessed via an identifier, reference, or pointer, and typically has a lifetime longer than a single expression evaluation or statement. For example:
```cpp
int main()
{
    int x { 5 };
    int y { x }; // x is an lvalue expression

    return 0;
}
```
In this example, the expression `x` is an lvalue expression because it evaluates to an identifiable object (the variable `x`) that has a persistent memory address.

Since the introduction of constants, we can have **modifiable** and **non-modifiable** lvalue expressions. A **modifiable lvalue expression** is an lvalue expression whose value can be changed. A **non-modifiable lvalue expression** is an lvalue expression whose value cannot be changed (because it is `const` or `constexpr`). For example:
```cpp
int main()
{
    int x{};
    const double d{};

    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression

    return 0;
}
```
In this example, the expression `x` is a modifiable lvalue expression because its value can be changed. The expression `d` is a non-modifiable lvalue expression because its value cannot be changed.

An **rvalue expression**, short for **right value expression**, is an expression that is not an lvalue expression. Rvalue expressions evaluates to a value that does not have a persistent memory address. Typical rvalues iclude literals (except C-style string literals) and the return value of functions that return by value.

Rvalues are not identifiable objects or functions (meaning that they have to be used immediately), and only exist within the scope of the expression in which they are used. For example:
```cpp
int return5()
{
    return 5;
}

int main()
{
    int x{ 5 }; // 5 is an rvalue expression
    const double d{ 1.2 }; // 1.2 is an rvalue expression

    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression
    int z { return5() }; // return5() is an rvalue expression (since the result is returned by value)

    int w { x + 1 }; // x + 1 is an rvalue expression
    int q { static_cast<int>(d) }; // the result of static casting d to an int is an rvalue expression

    return 0;
}
```
In this example, the expressions `5`, `1.2`, `return5()`, `x + 1`, and `static_cast<int>(d)` are all rvalue expressions because they evaluate to values that do not have a persistent memory address.

#### Value categories and operators:
Unless otherwise specified, operators expet their operands to be rvalues. For example, binary `operator+` expects both its left and right operands to be rvalues:
```cpp
#include <iostream>

int main()
{
    std::cout << 1 + 2; // 1 and 2 are rvalues, operator+ returns an rvalue

    return 0;
}
```

Going back to our example. now we can answer why `x = 5;` is valid while `5 = x;` is not. The assignment `operator=` expects its left operand to be a modifiable lvalue expression (since it needs to store the value of the right operand into the left operand). In the first case, `x` is a modifiable lvalue expression, so the assignment is valid. In the second case, `5` is an rvalue expression, so the assignment is not valid.
```cpp
int main()
{
    int x{};

    // Assignment requires the left operand to be a modifiable lvalue expression and the right operand to be an rvalue expression
    x = 5; // valid: x is a modifiable lvalue expression and 5 is an rvalue expression
    5 = x; // error: 5 is an rvalue expression and x is a modifiable lvalue expression

    return 0;
}
```

#### Lvalue-ro-rvalue conversion:
Since assignment operators expect their right operand to be an rvalue expression, you may wonder why the following works:
```cpp
int main()
{
    int x{ 1 };
    int y{ 2 };

    x = y; // y is not an rvalue, but this is legal

    return 0;
}
```
In this example, the expression `y` is an lvalue expression, but the assignment operator expects its right operand to be an rvalue expression. How is this possible?

The reason this works is because of a process called **lvalue-to-rvalue conversion**. When an lvalue expression is used in a context that expects an rvalue expression, the compiler automatically converts the lvalue expression to an rvalue expression by retrieving the value stored in the object or function that the lvalue expression evaluates to. In this case, the compiler retrieves the value stored in `y` and uses it as the right operand of the assignment operator.

Now, consider the following example:
```cpp
int main()
{
    int x { 2 };

    x = x + 1;

    return 0;
}
```
In this example, the variable `x` is being used in two different contexts. On the left side of the assignment operator, `x` is being used as a modifiable lvalue expression, while on the right side of the assignment operator, `x` is being used in an rvalue context (as part of the expression `x + 1`, with `operator+`). In this case, the compiler performs lvalue-to-rvalue conversion on `x` when it is used on the right side of the assignment operator.

#### How to differentiate lvalues and rvalues:
To differentiate between lvalue and rvalue expressions, you can use the following rules of thumb:
- If an expression refers to a named variable, function, or object, it is likely an lvalue expression.
- If an expression is a literal value (except C-style string literals), a temporary object, or the result of a function that returns by value, it is likely an rvalue expression.
- If an expression can appear on the left side of an assignment operator, it is likely an lvalue expression.
- If an expression cannot appear on the left side of an assignment operator, it is likely an rvalue expression.

Finally, we can write a program and have the compiler tells us what kind of expression something is:
```cpp
#include <iostream>
#include <string>

// T& is an lvalue reference, so this overload will be preferred for lvalues
template <typename T>
constexpr bool is_lvalue(T&)
{
    return true;
}

// T&& is an rvalue reference, so this overload will be preferred for rvalues
template <typename T>
constexpr bool is_lvalue(T&&)
{
    return false;
}

// A helper macro (#expr prints whatever is passed in for expr as text)
#define PRINTVCAT(expr) { std::cout << #expr << " is an " << (is_lvalue(expr) ? "lvalue\n" : "rvalue\n"); }

int getint() { return 5; }

int main()
{
    PRINTVCAT(5);        // rvalue
    PRINTVCAT(getint()); // rvalue
    int x { 5 };
    PRINTVCAT(x);        // lvalue
    PRINTVCAT(std::string {"Hello"}); // rvalue
    PRINTVCAT("Hello");  // lvalue
    PRINTVCAT(++x);      // lvalue, since ++x modifies x and returns x as an lvalue
    PRINTVCAT(x++);      // rvalue, since it first returns x as an rvalue, then modifies x
}
```
This program will print:
```
5 is an rvalue
getint() is an rvalue
x is an lvalue
std::string {"Hello"} is an rvalue
"Hello" is an lvalue
++x is an lvalue
x++ is an rvalue
```

#### Summary:
- **Value categories** are a way to classify expressions based on their behavior and properties.
- There are two main value categories: **lvalues** and **rvalues**.
- An **lvalue expression** evaluates to an identifiable object or function that has a persistent memory address.
- An **rvalue expression** evaluates to a value that does not have a persistent memory address.
- The compiler uses value categories to determine whether an expression can appear on the left or right side of an assignment operator.
- The compiler can perform **lvalue-to-rvalue conversion** when an lvalue expression is used in a context that expects an rvalue expression.


---

### S03 - 12.3 Lvalue references
In C++, a **reference** is an alias for another existing object. Once a reference is defined, it can be used interchangeably with the original object. References are often used to avoid copying large objects, to allow functions to modify their arguments, and to improve code readability. Optionally, you could also create references to functions, but this is less common.

Modern C++ supports two types of references: **lvalue references** and **rvalue references**. In this section, we will focus on **lvalue references**.

#### Lvalue references types:
An **lvalue reference** is an alias for an existing lvalue (such as a variable). The type of the reference tells us what type of object the reference can refer to.
To declare an lvalue reference type, we use the `&` symbol after the type name. For example:
```cpp
// regular types
int        // a normal int type (not an reference)
int&       // an lvalue reference to an int object
double&    // an lvalue reference to a double object
const int& // an lvalue reference to a const int object
```
For example, `int&` the type of an lvalue reference to an `int` object, while `const int&` is the type of an lvalue reference to a `const int` object.

In this context, the type that specifies a reference (e.g., `int&`, `const double&`, etc.) is called a **reference type**, while the type that can be referenced by the reference (e.g., `int`, `const double`, etc.) is called the **referenced type**.

There are two kinds of lvalue references:
- **Modifiable lvalue references**: lvalue references that can refer to modifiable lvalue expressions (i.e., lvalue expressions that are not `const` or `constexpr`). Modifiable lvalue references are declared using non-`const` reference types (e.g., `int&`, `double&`, etc.).
- **Non-modifiable lvalue references**: lvalue references that can refer to non-modifiable lvalue expressions (i.e., lvalue expressions that are `const` or `constexpr`). Non-modifiable lvalue references are declared using `const` reference types (e.g., `const int&`, `const double&`, etc.).

We will focus on modifiable lvalue references first, and then we will cover non-modifiable lvalue references later.

#### Lvalue reference variables:
An **lvalue reference variable** is a variable that acts as a reference to an lvalue expression (usually another variable). To declare an lvalue reference variable, we use the `&` symbol after the type name, followed by the reference variable name. For example:
```cpp
#include <iostream>

int main()
{
    int x { 5 };    // x is a normal integer variable
    int& ref { x }; // ref is an lvalue reference variable that can now be used as an alias for variable x

    std::cout << x << '\n';  // print the value of x (5)
    std::cout << ref << '\n'; // print the value of x via ref (5)

    return 0;
}
```
In this example, `ref` is an lvalue reference variable that refers to the variable `x`. We can use `ref` interchangeably with `x`, and any changes made to `ref` will affect `x`, and vice versa.

> **Note:** From the compiler's perspective, it does not matter whether `&` is attached to the type name (e.g., `int& ref`) or to the variable name (e.g., `int &ref`). Both forms are equivalent and valid.

> **Best Practice:** It is generally recommended to attach the `&` to the type name (e.g., `int& ref`) to improve code readability and maintain consistency with other type declarations.

#### Modifying values through a non-const lvalue reference:
In the previous example, we saw that we can use a reference to read the value of the object being referenced. We can also use non-`const` lvalue references to modify the value of the object being referenced. For example:
```cpp
#include <iostream>

int main()
{
    int x { 5 }; // normal integer variable
    int& ref { x }; // ref is now an alias for variable x

    std::cout << x << ref << '\n'; // print 55

    x = 6; // x now has value 6

    std::cout << x << ref << '\n'; // prints 66

    ref = 7; // the object being referenced (x) now has value 7

    std::cout << x << ref << '\n'; // prints 77

    return 0;
}
```
printing:
```
55
66
77
```
In this example, we first print the values of `x` and `ref`, which are both `5`. Then, we modify the value of `x` to `6`, and print the values again, which are now both `6`. Finally, we modify the value of `ref` to `7`, which also modifies the value of `x`, and print the values again, which are now both `7`.

#### Refernce initialization:
Much like constants, all references **must** be initialized. References are initialized using. aform of initialization called **reference initialization**:
```cpp
int main()
{
    int& invalidRef;   // error: references must be initialized

    int x { 5 };
    int& ref { x }; // okay: reference to int is bound to int variable

    return 0;
}
```
In this example, the declaration of `invalidRef` produces a compiler error because references must be initialized. The declaration of `ref` is valid because it is initialized to refer to the variable `x`.

When a reference is initialized with an object (or function), we say that the reference is **bound** to the object (or function). The process of initializing a reference to an object (or function) is called **binding**. The object (or function) that the reference is bound to is called the **referent**.

Non-const lvalue references can only be bound to a *modifiable* lvalue expression (i.e., an lvalue expression that is not `const` or `constexpr`). For example:
```cpp
int main()
{
    int x { 5 };
    int& ref { x };         // okay: non-const lvalue reference bound to a modifiable lvalue

    const int y { 5 };
    int& invalidRef { y };  // invalid: non-const lvalue reference can't bind to a non-modifiable lvalue
    int& invalidRef2 { 0 }; // invalid: non-const lvalue reference can't bind to an rvalue

    return 0;
}
```
In this example, the declaration of `ref` is valid because it is bound to the modifiable lvalue expression `x`. The declarations of `invalidRef` and `invalidRef2` produce compiler errors because non-`const` lvalue references cannot be bound to non-modifiable lvalue expressions (like `y`, which is `const`) or rvalue expressions (like the literal `0`).

Additionally, lvalue refeerences to `void` are disallowed, since `void` is an incomplete type and does not represent an object or function that can be referenced.

#### A reference will (usually) only bind to an object matching its referenced type:
In most cases, a reference will only bind to an object whose type matches the referenced type of the reference (except in some cases involving inheritance and polymorphism, which we will cover in later chapters). If you try to bind a reference to an object of a different type, the compiler will try to implicitly convert the object to the referenced type. If the conversion is not possible, the compiler will produce an error. For example:
```cpp
int main()
{
    int x { 5 };
    int& ref { x };            // okay: referenced type (int) matches type of initializer

    double d { 6.0 };
    int& invalidRef { d };     // invalid: conversion of double to int is narrowing conversion, disallowed by list initialization
    double& invalidRef2 { x }; // invalid: non-const lvalue reference can't bind to rvalue (result of converting x to double)

    return 0;
}
```
In this example, the declaration of `ref` is valid because the referenced type of the reference (`int`) matches the type of the initializer (`x`, which is also `int`). The declarations of `invalidRef` and `invalidRef2` produce compiler errors because the compiler cannot implicitly convert `d` (which is `double`) to `int` (since it is a narrowing conversion), and because the result of converting `x` (which is `int`) to `double` is an rvalue expression, which cannot be bound to a non-`const` lvalue reference.

#### References can’t be reseated (changed to refer to another object):
Once a reference is bound to an object (or function), it cannot be changed to refer to another object (or function). This is known as **reseating**. This will compile and run, but not do what you might expect:
```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int y { 6 };

    int& ref { x }; // ref is now an alias for x

    ref = y; // assigns 6 (the value of y) to x (the object being referenced by ref)
    // The above line does NOT change ref into a reference to variable y!

    std::cout << x << '\n'; // user is expecting this to print 5

    return 0;
}
```
printing:
```
6
```
In this example, we first bind the reference `ref` to the variable `x`. Then, we attempt to reseat `ref` to refer to `y` by writing `ref = y;`. However, this line does not change `ref` to refer to `y`; instead, it assigns the value of `y` (which is `6`) to the object being referenced by `ref` (which is `x`). Therefore, after this line, `x` now has the value `6`, and `ref` still refers to `x`.

#### refernce scope and duration:
The **scope** and **duration** of a reference variable are the same as those of the object (or function) it is bound to. This means that a reference variable cannot outlive the object (or function) it is bound to. For example:
```cpp
#include <iostream>

int main()
{
    int x { 5 }; // normal integer
    int& ref { x }; // reference to variable value

     return 0;
} // x and ref die here
```
In this example, both `x` and `ref` have automatic storage duration and block scope. They are both created when the program execution enters the `main()` function and destroyed when the program execution leaves the `main()` function.

#### Refernces and referents have independent lifetimes:
With one exception (that we’ll cover next lesson), the lifetime of a reference and the lifetime of its referent are independent. In other words, both of the following are true:
- A reference can be destroyed while its referent is still alive.
- A referent can be destroyed while its reference is still alive.

When a reference is destroyed, it simply ceases to exist as an alias for its referent, while the referent remains unchanged.
```cpp
#include <iostream>

int main()
{
    int x { 5 };

    {
        int& ref { x };   // ref is a reference to x
        std::cout << ref << '\n'; // prints value of ref (5)
    } // ref is destroyed here -- x is unaware of this

    std::cout << x << '\n'; // prints value of x (5)

    return 0;
} // x destroyed here
```
printing:
```
5
5
```
In this example, the reference variable `ref` is created inside a nested block scope. When the program execution leaves the nested block scope, `ref` is destroyed, but `x` remains alive. We can still access `x` after `ref` has been destroyed.

#### Dangling references:
A **dangling reference** occurs when a reference is bound to an object that has been destroyed. Accessing a dangling reference results in undefined behavior, which can lead to program crashes or other unexpected behavior. For example:
```cpp
#include <iostream>

int& createDanglingReference()
{
    int x { 5 };
    return x; // error: returning reference to local variable x, which will be destroyed when the function returns
}

int main()
{
    int& ref { createDanglingReference() }; // ref is now a dangling reference

    std::cout << ref << '\n'; // undefined behavior: accessing a dangling reference

    return 0;
}
```
In this example, the function `createDanglingReference()` creates a local variable `x` and returns a reference to it. However, when the function returns, `x` is destroyed, and the reference returned by the function becomes a dangling reference. Accessing this dangling reference in `main()` results in undefined behavior.

#### References are not objects:
Perhaps surprisingly, references are not objects in C++. This means that references do not have their own memory address, and they cannot be manipulated like objects. The compiler will optimize references away by replacing them with the object (or function) they refer to. For example:
```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int& ref { x };

    std::cout << &x << '\n';   // prints the memory address of x
    std::cout << &ref << '\n'; // prints the memory address of x (not ref)

    return 0;
}
```
printing:
```
0x7ffeedcba98c
0x7ffeedcba98c
```
In this example, both `&x` and `&ref` print the same memory address, which is the memory address of `x`. This demonstrates that `ref` does not have its own memory address; it is simply an alias for `x`.

We did not cover `&` operator in detail yet, but for now, just remember that when applied to a variable name, it returns the memory address of the variable (not the reference).

#### Summary:
- An **lvalue reference** is an alias for an existing lvalue expression (such as a variable).
- Lvalue references are declared using the `&` symbol after the type name (e.g., `int&`, `const double&`, etc.).
- There are two kinds of lvalue references: **modifiable lvalue references** and **non-modifiable lvalue references**.
- Lvalue reference variables must be initialized when they are declared, and they cannot be reseated to refer to another object.
- The scope and duration of a reference variable are the same as those of the object (or function) it is bound to.
- References and their referents have independent lifetimes, but accessing a dangling reference results in undefined behavior.
- References are not objects and do not have their own memory address.


---

### S04 - 12.4 Lvalue references to const
In the previous section we have seen that non-`const` lvalue references can only be bound to modifiable lvalue expressions (i.e., lvalue expressions that are not `const` or `constexpr`). This means that we cannot bind a non-`const` lvalue reference to a `const` variable or a literal value. To solve this problem, C++ provides **lvalue references to const**.

#### Lvalue references to const:
An **lvalue reference to const** is an alias for a non-modifiable lvalue expression (i.e., an lvalue expression that is `const` or `constexpr`). Lvalue references to const are declared using the `const` keyword before the type name, followed by the `&` symbol. For example:
```cpp
int main()
{
    const int x { 5 };    // x is a non-modifiable lvalue
    const int& ref { x }; // okay: ref is a an lvalue reference to a const value

    return 0;
}
```
In this example, `ref` is an lvalue reference to const that refers to the `const` variable `x`. We can use `ref` to read the value of `x`, but we cannot use `ref` to modify the value of `x`.
```cpp
#include <iostream>

int main()
{
    const int x { 5 };    // x is a non-modifiable lvalue
    const int& ref { x }; // okay: ref is a an lvalue reference to a const value

    std::cout << ref << '\n'; // okay: we can access the const object
    ref = 6;                  // error: we can not modify an object through a const reference

    return 0;
}
```

#### Initializing an lvalue reference to const with modifiable lvalue:
Interestingly, lvalue references to const can also be bound to modifiable lvalue expressions (i.e., lvalue expressions that are not `const` or `constexpr`). This allows us to create a read-only alias for a modifiable object. For example:
```cpp
#include <iostream>

int main()
{
    int x { 5 };          // x is a modifiable lvalue
    const int& ref { x }; // okay: we can bind a const reference to a modifiable lvalue

    std::cout << ref << '\n'; // okay: we can access the object through our const reference
    ref = 7;                  // error: we can not modify an object through a const reference

    x = 6;                // okay: x is a modifiable lvalue, we can still modify it through the original identifier

    return 0;
}
```
In this example, `ref` is an lvalue reference to const that refers to the modifiable variable `x`. We can use `ref` to read the value of `x`, but we cannot use `ref` to modify the value of `x`. However, we can still modify `x` through its original identifier.
Favour `lvalue references to const` over `lvalue references to non-const` unless you specifically need to modify the referent through the reference. This practice enhances code safety and clarity by preventing unintended modifications.

#### Initializing an lvalue reference to const with an rvalue:
Another interesting property of lvalue references to const is that they can be bound to rvalue expressions. This allows us to create a reference to a temporary object or literal value. For example:
```
#include <iostream>

int main()
{
    const int& ref { 5 }; // okay: 5 is an rvalue

    std::cout << ref << '\n'; // prints 5

    return 0;
}
```
printing:
```
5
```
In this example, `ref` is an lvalue reference to const that refers to the literal value `5`. We can use `ref` to read the value of `5`, but we cannot use `ref` to modify the value of `5`.

#### Initializing an lvalue reference to const with a value of a different type:
Lvalue references to const can also be bound to rvalue expressions of a different type, as long as the rvalue can be implicitly converted to the referenced type. This allows us to create a reference to a temporary object of a different type. For example:
```cpp
#include <iostream>

int main()
{
    // case 1
    const double& r1 { 5 };  // temporary double initialized with value 5, r1 binds to temporary

    std::cout << r1 << '\n'; // prints 5

    // case 2
    char c { 'a' };
    const int& r2 { c };     // temporary int initialized with value 'a', r2 binds to temporary

    std::cout << r2 << '\n'; // prints 97 (since r2 is a reference to int)

    return 0;
}
```
printing:
```
5
97
```
In this example, `r1` is an lvalue reference to const that refers to a temporary `double` object initialized with the value `5`. We can use `r1` to read the value of the temporary object. Similarly, `r2` is an lvalue reference to const that refers to a temporary `int` object initialized with the value of `c` (which is `'a'`). We can use `r2` to read the value of the temporary object.

#### Const references bound to temporary objects extend the lifetime of the temporary object:
When an lvalue reference to const is bound to a temporary object, the lifetime of the temporary object is extended to match the lifetime of the reference. This means that the temporary object will remain alive as long as the reference is alive. For example:
```cpp
#include <iostream>

int main()
{
    const int& ref { 5 }; // The temporary object holding value 5 has its lifetime extended to match ref

    std::cout << ref << '\n'; // Therefore, we can safely use it here

    return 0;
} // Both ref and the temporary object die here
```
In this example, the temporary object holding the value `5` has its lifetime extended to match the lifetime of the reference `ref`. Therefore, we can safely use `ref` to access the value of the temporary object.

#### Constexpr lvalue references (Optional):
When applied to a reference, `constexpr` allows the reference to be used in constant expressions. Constexpr references have a particular limitation: they can only be bound to objects with static duration (either globals or static locals). This is because the compiler knows where the static objects will be instatiated in memory, so it can treat that address as a compile-time constant.

A constexpr reference cannot bind to a (non-static) local variable. This is because the address of local variables is not known until the function they are defined within is actually called.
```cpp
int g_x { 5 };

int main()
{
    [[maybe_unused]] constexpr int& ref1 { g_x }; // ok, can bind to global

    static int s_x { 6 };
    [[maybe_unused]] constexpr int& ref2 { s_x }; // ok, can bind to static local

    int x { 6 };
    [[maybe_unused]] constexpr int& ref3 { x }; // compile error: can't bind to non-static object

    return 0;
}
```
In this example, `ref1` and `ref2` are valid `constexpr` lvalue references because they are bound to objects with static duration (`g_x` and `s_x`, respectively). However, `ref3` produces a compiler error because it is attempting to bind to a non-static local variable (`x`).

> **Note:** When defining. a constexpr reference to a const value, we need to apply both `constexpr` (to the reference) and `const` (to the referenced type). For example, `constexpr const int& ref { x };`.

Fiven these limitations, constexpr references typically see little use in practice.

#### Summary:
- An **lvalue reference to const** is an alias for a non-modifiable lvalue expression (i.e., an lvalue expression that is `const` or `constexpr`).
- Lvalue references to const are declared using the `const` keyword before the type name, followed by the `&` symbol (e.g., `const int&`, `const double&`, etc.).
- Lvalue references to const can be bound to modifiable lvalue expressions, rvalue expressions, and rvalue expressions of a different type (as long as the rvalue can be implicitly converted to the referenced type).
- When an lvalue reference to const is bound to a temporary object, the lifetime of the temporary object is extended to match the lifetime of the reference.
- `constexpr` lvalue references can only be bound to objects with static duration (either globals or static locals).


---

### S05 - 12.5 Pass by value reference
In this section, we will show why references are useful by demonstrating how to use lvalue references to implement **pass by reference** function parameters.

In a previous chapter, we learned about **pass by value** function parameters, where the function creates a copy of the argument passed to it.
```cpp
#include <iostream>

void printValue(int y)
{
    std::cout << y << '\n';
} // y is destroyed here

int main()
{
    int x { 2 };

    printValue(x); // x is passed by value (copied) into parameter y (inexpensive)

    return 0;
}
```
In this example, the function `printValue()` takes an `int` parameter `y`, which is passed by value. When we call `printValue(x)`, the value of `x` is copied into `y`. This is inexpensive for small types like `int`, but can be inefficient for larger types (like large structs or classes) because it involves copying the entire object.

#### Some objects are expensive to copy:
Most of the types provided by the standard library (like `std::string`, `std::vector`, etc.) are class types. Class types are usually expensive to copy because they often manage dynamic memory or other resources. For this reason, we usually try to avoid doing unnecessary copies of objects that are expensive to copy.

Consider the following example:
```cpp
#include <iostream>
#include <string>

void printValue(std::string y)
{
    std::cout << y << '\n';
} // y is destroyed here

int main()
{
    std::string x { "Hello, world!" }; // x is a std::string

    printValue(x); // x is passed by value (copied) into parameter y (expensive)

    return 0;
}
```
This program will print:
```
Hello, world!
```
In this example, the function `printValue()` takes a `std::string` parameter `y`, which is passed by value. When we call `printValue(x)`, the entire `std::string` object `x` is copied into `y`. This can be expensive because it involves allocating memory for the new string and copying the characters from `x` to `y`. We can do better!

#### Pass by reference:
To avoid the overhead of copying large objects, we can use **pass by reference** function parameters. In pass by reference, we pass a reference to the argument instead of a copy of the argument. This allows the function to access the original object without making a copy. For example:
```cpp
#include <iostream>
#include <string>

void printValue(std::string& y) // type changed to std::string&
{
    std::cout << y << '\n';
} // y is destroyed here

int main()
{
    std::string x { "Hello, world!" };

    printValue(x); // x is now passed by reference into reference parameter y (inexpensive)

    return 0;
}
```
This program is identical to the previous one, but now the function `printValue()` takes a `std::string&` parameter `y`, which is an lvalue reference to a `std::string`. When we call `printValue(x)`, the lvalue reference parameter `y` is bound to arguemnt `x`. This means that `y` is now an alias for `x`, and the function can access the original `std::string` object without making a copy. 

Binding a reference is always inexpensive, regardless of the size of the object being referenced. Therefore, pass by reference is a more efficient way to pass large objects to functions.

In the following, we demonstrate that a value parameter is a separate object from the argument passed to it, while a reference parameter is an alias for the argument passed to it:
```cpp
#include <iostream>

void printAddresses(int val, int& ref)
{
    std::cout << "The address of the value parameter is: " << &val << '\n';
    std::cout << "The address of the reference parameter is: " << &ref << '\n';
}

int main()
{
    int x { 5 };
    std::cout << "The address of x is: " << &x << '\n';
    printAddresses(x, x);

    return 0;
}
```
This program will print something like:
```
The address of x is: 0x7ffd16574de0
The address of the value parameter is: 0x7ffd16574de4
The address of the reference parameter is: 0x7ffd16574de0
```
In this example, we define a function `printAddresses()` that takes an `int` value parameter `val` and an `int&` reference parameter `ref`. Inside the function, we print the memory addresses of both parameters. In `main()`, we call `printAddresses(x, x)`, passing the same variable `x` for both parameters. When we run the program, we can see that the address of the value parameter `val` is different from the address of `x` (it means it is a separate object), while the address of the reference parameter `ref` is the same as the address of `x` (it means it is an alias for `x`).

#### Pass by reference allows us to change the value of an argument:
When an object is passed by value, the function receives a copy of the object, and any changes made to the parameter do not affect the original argument. For example:
```cpp
#include <iostream>

void addOne(int y) // y is a copy of x
{
    ++y; // this modifies the copy of x, not the actual object x
}

int main()
{
    int x { 5 };

    std::cout << "value = " << x << '\n';

    addOne(x);

    std::cout << "value = " << x << '\n'; // x has not been modified

    return 0;
}
```
will print:
```
value = 5
value = 5
```
In this example, the function `addOne()` takes an `int` parameter `y`, which is passed by value. Inside the function, we increment `y` by `1`, but this does not affect the original variable `x` in `main()`, because `y` is a copy of `x`.

However, when an object is passed by reference, the function receives a reference to the original object (same memory address), and any changes made to the parameter will affect the original argument. For example:
```cpp
#include <iostream>

void addOne(int& y) // y is bound to the actual object x
{
    ++y; // this modifies the actual object x
}

int main()
{
    int x { 5 };

    std::cout << "value = " << x << '\n';

    addOne(x);

    std::cout << "value = " << x << '\n'; // x has been modified

    return 0;
}
```
will print:
```
value = 5
value = 6
```
In this example, the function `addOne()` takes an `int&` parameter `y`, which is passed by reference. Inside the function, we increment `y` by `1`, which also modifies the original variable `x` in `main()`, because `y` is an alias for `x`.

The ability to modify the original argument through a reference parameter can be useful in many situations. For example, imagine a function that determines whether a monster has successfully attacked the player. If the attack is successful, the function could modify the player's health by passing the player object by reference. If you had passed the player object by value instead, the function would only modify a copy of the player object, and the player's health in the calling code would remain unchanged.

#### Pass by reference can only accept modifiable lvalue arguemnts:
When a function parameter is declared as a non-`const` lvalue reference, it can only accept modifiable lvalue arguments (i.e., lvalue expressions that are not `const` or `constexpr`). This is because non-`const` lvalue references cannot be bound to non-modifiable lvalue expressions or rvalue expressions. This means that you cannot pass `const` variables, literals, or temporary objects to functions that take non-`const` lvalue reference parameters. For example:
```cpp
#include <iostream>

void printValue(int& y) // y only accepts modifiable lvalues
{
    std::cout << y << '\n';
}

int main()
{
    int x { 5 };
    printValue(x); // ok: x is a modifiable lvalue

    const int z { 5 };
    printValue(z); // error: z is a non-modifiable lvalue

    printValue(5); // error: 5 is an rvalue

    return 0;
}
```
In this example, the function `printValue()` takes an `int&` parameter `y`, which can only accept modifiable lvalue arguments. The call `printValue(x)` is valid because `x` is a modifiable lvalue. However, the calls `printValue(z)` and `printValue(5)` produce compiler errors because `z` is a non-modifiable lvalue (it is `const`), and `5` is an rvalue.

Fortunately, an easy solution exists, that will be covered in the next section.

#### Summary:
- **Pass by reference** allows functions to accept references to arguments instead of copies of arguments, which can improve performance when passing large objects.
- Pass by reference is implemented using **lvalue reference parameters**, which are declared using the `&` symbol after the type name (e.g., `std::string&`, `int&`, etc.).
- When an object is passed by reference, the function receives a reference to the original object, and any changes made to the parameter will affect the original argument.
- Non-`const` lvalue reference parameters can only accept modifiable lvalue arguments (i.e., lvalue expressions that are not `const` or `constexpr`).


---

### S06 - 12.6 Pass by const lvalue reference
Unlike non-`const` lvalue references, **lvalue references to const** can be bound to a wider range of expressions, including modifiable lvalue expressions, non-modifiable lvalue expressions, and rvalue expressions. Therefore, if we make a reference parameter `const`, we can accept a wider range of arguments. This is known as **pass by const reference**.
```cpp
#include <iostream>

void printRef(const int& y) // y is a const reference
{
    std::cout << y << '\n';
}

int main()
{
    int x { 5 };
    printRef(x);   // ok: x is a modifiable lvalue, y binds to x

    const int z { 5 };
    printRef(z);   // ok: z is a non-modifiable lvalue, y binds to z

    printRef(5);   // ok: 5 is rvalue literal, y binds to temporary int object

    return 0;
}
```
In this example, the function `printRef()` takes a `const int&` parameter `y`, which is an lvalue reference to const. The function can accept modifiable lvalue arguments (like `x`), non-modifiable lvalue arguments (like `z`), and rvalue arguments (like the literal `5`). This makes pass by const reference a versatile and efficient way to pass arguments to functions.

Using const reference parameters instead of non-const reference parameters has some advantages:
- **Wider range of accepted arguments**: As demonstrated above, const reference parameters can accept a wider range of arguments, including modifiable lvalues, non-modifiable lvalues, and rvalues.
- **Safety**: Since const reference parameters cannot be used to modify the original argument, they provide a level of safety by preventing unintended modifications to the argument.

> **Best Practice**: Favor passing by const reference over passing by non-const reference unless you have a specific reason to do otherwise (e.g. the function needs to change the value of an argument).

Now we can understand the motivation for allowing const value references to bind rvalues: without that capability, there would be no way to pass literals or temporary objects to functions that take const reference parameters.

#### Passing arguments of a different type to a const lvalue reference parameter:
In a previous sections, we ahve seen that const lvalue references can bind to value of a different type, as long as the value can be implicitly converted to the referenced type. This means that we can pass arguments of a different type to functions that take const lvalue reference parameters, as long as the argument can be implicitly converted to the referenced type.

The primary motivation for allowing this is so that we can pass a value as an argument to either a value parameter or a const reference parameter in exactly the same way:
```cpp
#include <iostream>

void printVal(double d)
{
    std::cout << d << '\n';
}

void printRef(const double& d)
{
    std::cout << d << '\n';
}

int main()
{
    printVal(5); // 5 converted to temporary double, copied to parameter d
    printRef(5); // 5 converted to temporary double, bound to parameter d

    return 0;
}
```
In this example, we define two functions: `printVal()` takes a `double` value parameter, and `printRef()` takes a `const double&` lvalue reference parameter. In `main()`, we call both functions with the integer literal `5`. In both cases, the integer `5` is implicitly converted to a temporary `double` object. In the case of `printVal()`, the temporary `double` object is copied to the parameter `d`. In the case of `printRef()`, the temporary `double` object is bound to the parameter `d`.

#### Mixing pass by value and pass by reference:
When designing functions, you may choose to use a mix of pass by value and pass by reference parameters based on the specific needs of your function. For example:
```cpp
#include <string>

void foo(int a, int& b, const std::string& c)
{
}

int main()
{
    int x { 5 };
    const std::string s { "Hello, world!" };

    foo(5, x, s);

    return 0;
}
```
In this example, the function `foo()` takes three parameters:
- `a`: an `int` value parameter, which is passed by value.
- `b`: an `int&` reference parameter, which is passed by reference and can be modified by the function.
- `c`: a `const std::string&` const reference parameter, which is passed by const reference and cannot be modified by the function.

#### when to use pass by value vs pass by reference:
For most C++ beginners, the choice of whether to use pass by value or pass by reference isn’t very obvious. Here are some general guidelines to help you decide:
- **Fundamental types** (like `int`, `char`, `float`, etc.) and **enumerated types** are usually inexpensive to copy, so passing them by value is often the best choice.
- **Class types** (like `std::string`, `std::vector`, etc.) are often expensive to copy, so passing them by const reference is usually the best choice.

> **Best Practice**: Pass by value for small, inexpensive-to-copy types (like fundamental and enumerated types), and pass by const reference for large, expensive-to-copy types (like class types). If you are not sure, prefer pass by const reference.

#### The cost of pass by value vs pass by reference (Advanced):
No all classes need to be passed by reference (such as `std::string_view`), and you may ask why we are not passing everything by reference. The reason is that passing by reference has its own costs.

First, we need to consider the cost of **initializing** the function parameter.
- For **pass by value**, the cost of initializing the parameter is the cost of copying the argument to the parameter, and it is generally proportional to two things:
    1. The size of the object being copied (larger objects take longer to copy).
    2. Any additional setup costs associated with the copy operation (like allocating memory for dynamic members, opening a file database connections, etc.).
- For **pass by reference**, the cost of initializing the parameter is the cost of creating the reference (binding the reference to the argument), which is generally very inexpensive and often constant time, regardless of the size of the object being referenced.

Second, we need to consider the cost of **accessing** the function parameter inside the function body.
- For **pass by value**, accessing the parameter is generally very fast because the parameter is a local object stored in the function's stack frame (1 RAM/CPU memory access).
- For **pass by reference**, accessing the parameter may involve an additional level of indirection (dereferencing the reference to access the original object), which can be slightly slower than accessing a local object (2 RAM/CPU memory accesses). However, this cost is usually negligible compared to the cost of copying large objects.

Third, we need to consider the **compiler optimizations**.
- Modern compilers are very good at optimizing code passed by value, especially for small objects. They can often eliminate unnecessary copies through techniques like copy elision and return value optimization (RVO).
- Compilers can also optimize code passed by reference, but the optimizations may be less effective due to the additional indirection involved in accessing the referenced object.

So overall, now we can answer the question of why we do not always pass everything by reference:
- For small, inexpensive-to-copy objects (like fundamental and enumerated types), the cost of copying the object is often negligible compared to the cost of accessing the object through a reference. Therefore, passing these objects by value is often more efficient.
- For large, expensive-to-copy objects (like class types), the cost of copying the object can be significant, and the cost of accessing the object through a reference is usually negligible in comparison. Therefore, passing these objects by const reference is often more efficient.

Last but not least, how can we defined **cheap to copy**?
There is no general rule, since this depends on compiler, use cases, and hardware architecture. However, a common guideline is that objects smaller than or equal to **two "words"** (typically 8 or 16 bytes, depending on the architecture) are usually considered cheap to copy, while larger objects are considered expensive to copy. Here the term "word" refers to the memory address size, which is typically 4 bytes on 32-bit systems and 8 bytes on 64-bit systems.

The following program defines a function-like macro that can be used to determine if a type (or object) is cheap to copy accordingly:
```cpp
#include <iostream>

// Function-like macro that evaluates to true if the type (or object) is equal to or smaller than
// the size of two memory addresses
#define isSmall(T) (sizeof(T) <= 2 * sizeof(void*))

struct S
{
    double a;
    double b;
    double c;
};

int main()
{
    std::cout << std::boolalpha; // print true or false rather than 1 or 0
    std::cout << isSmall(int) << '\n'; // true

    double d {};
    std::cout << isSmall(d) << '\n'; // true
    std::cout << isSmall(S) << '\n'; // false

    return 0;
}
```
printing (on a 64-bit system):
```
true
true
false
```

#### For function parameters, prefer `std::string_view` over `const std::string&` in most cases:
One common question that arises when designing function parameters is whether to use `const std::string&` or `std::string_view` for passing string data. In most cases, prefer using `std::string_view` over `const std::string&` as it can handle a wider range of string-like inputs (like C-style strings, string literals, and substrings) without requiring the creation of temporary `std::string` objects. This can lead to improved performance and reduced memory usage. Additionally, `std::string_view` provides a more flexible and efficient way to work with string data in functions, without the overhead of copying or managing the lifetime of `std::string` objects.
```cpp
void doSomething(const std::string&);
void doSomething(std::string_view);   // prefer this in most cases
```

There are few cases where `const std::string&` may be preferred:
- If you are using C++14 or older, where `std::string_view` is not available.
- If your function needs to call some other function that takes C-style string or `std::string` parameters, then `const std::string&` may be more convenient since `std::string_view` is not guaranteed to be null-terminated, and conversion to `std::string` is not free.

> **Best Practice**: In most cases, prefer using `std::string_view` for string parameters in functions. Only use `const std::string&` when you specifically need to work with `std::string` objects or when compatibility with older C++ standards is required.

#### Why `std::string_view` parameters are more efficient than `const std::string&` (Advanced):
In C++, a string arguemnt will typically be a `std::string`, a `std::string_view`, or a C-style string/string literal.

As reminders:
- If the type of an arguement does not match the type of the parameter, an implicit conversion will be performed by the compiler to convert the argument to the type of the parameter.
- Converting a value creates a temporary object of the converted type, which is then used as the argument for the parameter.
- Creating (or copying) a `std::string_view` is inexpensive, as `std::string_view` odoes not make a copy of the string it is viewing; it simply holds a pointer to the original string data and its length.
- Creating (or copying) a `std::string` can be expensive, as it may involve allocating memory and copying the string data.

Here is a table to show how different types of string arguments are passed to functions:
| Argument Type        | `std::string` Parameter               | `std::string_view` Parameter          |
|----------------------|--------------------------------------|--------------------------------------|
| `std::string`        | Inexpensive conversion     | Inexpensive reference binding (no copy)      |
| `std::string_view`   | Inexpensive copy | Inexpensive explicit conversion to `std::string` |
| C-style string / literal | Inexpensive conversion (creates temporary `std::string`) | Inexpensive conversion | Expensive conversion |

With a `std::string_view` value parameter:
- If we pass in a `std::string`, the compiler will convert `std::string` to `std::string_view`, which is inexpensive.
- If we pass in a `std::string_view`, the compiler will copy the argument into the parameter, which is inexpensive.
- If we pass in a C-style string or string literal, the compiler will convert it to `std::string_view`, which is inexpensive.

As you can see, `std::string_view` supports all three cases with inexpensive conversions.

With a `const std::string&` reference parameter:
- If we pass in a `std::string`, the compiler will bind the reference to the argument, which is inexpensive.
- If we pass in a `std::string_view`, the compiler will refuse to do an implicit conversion, and produce a compilation error. We can use `static_cast` to explicitly convert the `std::string_view` to a `std::string`, but this involves creating a temporary `std::string` object, which can be expensive.
- If we pass in a C-style string or string literal, the compiler will implicitly convert it to a temporary `std::string` object, which can be expensive.

Thus, using `std::string_view` parameters is generally more efficient than using `const std::string&` parameters, especially when dealing with C-style strings or string literals.

Here the same concepts in code form, as we love and breathe C++ code now:
```cpp
#include <iostream>
#include <string>
#include <string_view>

void printSV(std::string_view sv)
{
    std::cout << sv << '\n';
}

void printS(const std::string& s)
{
    std::cout << s << '\n';
}

int main()
{
    std::string s{ "Hello, world" };
    std::string_view sv { s };

    // Pass to `std::string_view` parameter
    printSV(s);              // ok: inexpensive conversion from std::string to std::string_view
    printSV(sv);             // ok: inexpensive copy of std::string_view
    printSV("Hello, world"); // ok: inexpensive conversion of C-style string literal to std::string_view

    // pass to `const std::string&` parameter
    printS(s);              // ok: inexpensive bind to std::string argument
    printS(sv);             // compile error: cannot implicit convert std::string_view to std::string
    printS(static_cast<std::string>(sv)); // bad: expensive creation of std::string temporary
    printS("Hello, world"); // bad: expensive creation of std::string temporary

    return 0;
}
```

#### Summary:
- **Pass by const reference** allows functions to accept a wider range of arguments (modifiable lvalues, non-modifiable lvalues, and rvalues) without making copies of the arguments.
- Pass by const reference is implemented using **lvalue reference to const parameters**, which are declared using the `const` keyword before the type name, followed by the `&` symbol (e.g., `const std::string&`, `const int&`, etc.).
- When designing functions, prefer using **pass by const reference** for large, expensive-to-copy objects (like class types) and **pass by value** for small, inexpensive-to-copy objects (like fundamental and enumerated types).
- For string parameters, prefer using `std::string_view` over `const std::string&` in most cases for improved performance and flexibility.


---

### S07 - 12.7 Introduction to pointers
And finally, here they are: **pointers**! In this section, we will introduce pointers, which are another type of compound type in C++. Do not be scared, at the end of the day, pointers are very similar to lvalue references. But first, here is some setup.

Consider a normal variable like this:
```cpp
char x {}; // chars use 1 byte of memory
```
The variable `x` is a named object that, the the code runs, will occupy 1 byte of RAM memory to store a `char` value. For example, let us say that `x` is stored at memory address `140` (generally represented in hexadecimal format, like `0x8C`). Whenever we use the variable `x` in an expression or statement, the program will go to the memory address `140` to read or write the value of `x`.

This is the nice thing of variables: we can use them without worrying about where they are stored in memory. The compiler and runtime system will take care of that for us.

This also holds true for lvalue references. For example:
```cpp
int main()
{
    char x {}; // assume this is assigned memory address 140
    char& ref { x }; // ref is an lvalue reference to x (when used with a type, & means lvalue reference)

    return 0;
}
```
In this example, `ref` is an lvalue reference to `x`. Whenever we use `ref` in an expression or statement, the program will go to the memory address `140` to read or write the value of `x`. Again, we do not need to worry about where `x` is stored in memory; the compiler and runtime system will take care of that for us.

#### The address-of operator (`&`):
In C++, we can use the **address-of operator** (`&`) to obtain the memory address of a variable (or object). The address-of operator is a unary operator that is placed before the variable name. For example:
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    std::cout << x << '\n';  // print the value of variable x
    std::cout << &x << '\n'; // print the memory address of variable x

    return 0;
}
```
This program will print something like:
```
5
0027FEA0
```
In this example, we use the address-of operator (`&`) to obtain the memory address of the variable `x`. The output shows the value of `x` (which is `5`) and the memory address of `x` (which is represented in hexadecimal format).

For objects that use more than one byte of memory (like `int`, `double`, `std::string`, etc.), the address returned by the address-of operator is the address of the first byte of the object in memory.

#### The dereference operator (`*`):
In C++, we can use the **dereference operator** (`*`) to access the value stored at a specific memory address. The dereference operator is a unary operator that is placed before a pointer variable (which we will learn about shortly). For example:
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    std::cout << x << '\n';  // print the value of variable x
    std::cout << &x << '\n'; // print the memory address of variable x

    std::cout << *(&x) << '\n'; // print the value at the memory address of variable x (parentheses not required, but make it easier to read)

    return 0;
}
```
This program will print something like:
```
5
0027FEA0
5
```
As shown in this example, we use the dereference operator (`*`) to access the value stored at the memory address of the variable `x`. The output shows the value of `x` (which is `5`), the memory address of `x`, and the value obtained by dereferencing the memory address of `x` (which is also `5`).

> **Note:** The address-of operator (`&`) and the dereference operator (`*`) are complementary operators. The address-of operator obtains the memory address of an object, while the dereference operator accesses the value stored at a specific memory address.

Now, I would add finally, we can start to add some sauce to the mix: **pointers**.

#### Pointers ("dumb" or "raw" pointers):
A **pointer** is an object that holds a *memory address* as its value. Pointers are used to store the memory addresses of other objects (variables). In C++, a type that specifies a pointer (e.g., `int*`) is called a **pointer type**. The `*` symbol in a pointer type indicates that the type is a pointer to the specified type. For example, `int*` is a pointer type that points to an `int` object, and `char*` is a pointer type that points to a `char` object. For example:
```cpp
int;  // a normal int
int&; // an lvalue reference to an int value

int*; // a pointer to an int value (holds the address of an integer value)
char*; // a pointer to a char value (holds the address of a char value)
```

To declare a pointer variable, we simply define a variable with a pointer type:
```cpp
int main()
{
    int x { 5 };    // normal variable
    int& ref { x }; // a reference to an integer (bound to x)

    int* ptr;       // a pointer to an integer

    return 0;
}
```
In this example, `ptr` is a pointer variable that can hold the memory address of an `int` object.

> **Best Practice:** When declaring pointer variables, place the `*` symbol next to the type name (e.g., `int* ptr;`) to make it clear that the variable is a pointer type.

#### Pointer initialization:
Like normal variables, pointers are **not initialized** by default. Therefore, it is important to initialize pointer variables before using them. A pointer that has not been initialized is sometimes called a **wild pointer**. Dereferencing a wild pointer (i.e., accessing the value at the memory address stored in the pointer) results in **undefined behavior**, as it caontains a gargabge memory address.

> **Best practice:** Always initialize your pointers before using them to avoid undefined behavior.

So, how do we initialize pointers? There are several ways to initialize a pointer:
```cpp
int main()
{
    int x{ 5 };

    int* ptr;        // an uninitialized pointer (holds a garbage address)
    int* ptr2{};     // a null pointer (we'll discuss these in the next lesson)
    int* ptr3{ &x }; // a pointer initialized with the address of variable x

    return 0;
}
```
In this example, we declare three pointer variables:
- `ptr`: an uninitialized pointer that holds a garbage memory address (wild pointer).
- `ptr2`: a null pointer that is initialized to `nullptr` (we will discuss null pointers in the next lesson).
- `ptr3`: a pointer that is initialized with the memory address of the variable `x` using the address-of operator (`&`), usually the most safe and common way to initialize a pointer.

Since pointers hold memory addresses, we can use the address-of operator (`&`) to initialize a pointer with the address of a variable.

Once we have a pointer holding the address of another object, we can use the dereference operator (`*`) to access the value stored at that memory address. For example:
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    std::cout << x << '\n'; // print the value of variable x

    int* ptr{ &x }; // ptr holds the address of x
    std::cout << *ptr << '\n'; // use dereference operator to print the value at the address that ptr is holding (which is x's address)

    return 0;
}
```
This program will print:
```
5
5
```
In this example, we initialize the pointer `ptr` with the address of the variable `x`. We then use the dereference operator (`*`) to access the value stored at the memory address held by `ptr`, which is the value of `x`.

Conceptually, here a diagram to illustrate how pointers work (the left box is the pointer object, and the right box is the object being pointed to):

```
                            Memory Address: 0x0012FFB0
+------------------+        +-----------+
|   ptr (int*)     | -----> |  x (int)  |
| (value=0012FFB0) |        | (value=5) |
+------------------+        +-----------+
```
Here, `ptr` is holding the memory address of `x` (e.g., `0x0012FFB0`), and dereferencing `ptr` (`*ptr`) allows us to access the value of `x` (which is `5`), that is stored at that memory address.

The pointer's type must match the type of the object it points to. For example, an `int*` pointer can only point to an `int` object, and a `char*` pointer can only point to a `char` object. Attempting to assign the address of an object of a different type to a pointer will result in a compilation error.
```cpp
int main()
{
    int i{ 5 };
    double d{ 7.0 };

    int* iPtr{ &i };     // ok: a pointer to an int can point to an int object
    int* iPtr2 { &d };   // not okay: a pointer to an int can't point to a double object
    double* dPtr{ &d };  // ok: a pointer to a double can point to a double object
    double* dPtr2{ &i }; // not okay: a pointer to a double can't point to an int object

    return 0;
}
```
With one exception that we will see later, initializing a pointer with a literal value is disallowed, as literals do not have a memory address that can be referenced:
```cpp
int* ptr{ 5 }; // not okay
int* ptr{ 0x0012FF7C }; // not okay, 0x0012FF7C is treated as an integer literal
```

#### Pointers and assignment:
We can use assignment with pointers in two different ways:
1. To change what the pointer is pointing to (i.e., change the memory address stored in the pointer). For example:
    ```cpp
    #include <iostream>

    int main()
    {
        int x{ 5 };
        int* ptr{ &x }; // ptr initialized to point at x

        std::cout << *ptr << '\n'; // print the value at the address being pointed to (x's address)

        int y{ 6 };
        ptr = &y; // // change ptr to point at y

        std::cout << *ptr << '\n'; // print the value at the address being pointed to (y's address)

        return 0;
    }
    ```
    that prints:
    ```
    5
    6
    ```
    In this example, we first initialize the pointer `ptr` to point to the variable `x`. We then use the dereference operator (`*`) to access and print the value of `x`. Next, we change the pointer `ptr` to point to the variable `y` by assigning the address of `y` to `ptr` (`ptr = &y;`). Finally, we use the dereference operator again to access and print the value of `y`.
2. To change the value of the object being pointed to (i.e., change the value at the memory address stored in the pointer). For example:
    ```cpp
    #include <iostream>

    int main()
    {
        int x{ 5 };
        int* ptr{ &x }; // initialize ptr with address of variable x

        std::cout << x << '\n';    // print x's value
        std::cout << *ptr << '\n'; // print the value at the address that ptr is holding (x's address)

        *ptr = 6; // The object at the address held by ptr (x) assigned value 6 (note that ptr is dereferenced here)

        std::cout << x << '\n';
        std::cout << *ptr << '\n'; // print the value at the address that ptr is holding (x's address)

        return 0;
    }
    ```
    printing:
    ```
    5
    5
    6
    6
    ```
    In this example, we initialize the pointer `ptr` with the address of the variable `x`. We then print the value of `x` and the value obtained by dereferencing `ptr` (which is also `x`). Next, we use the dereference operator (`*`) to change the value of the object being pointed to by `ptr` (which is `x`) to `6`. Finally, we print the value of `x` and the value obtained by dereferencing `ptr` again, which are both now `6`. 
    In this second case, compared to the first case, we are not changing what the pointer is pointing to; instead, we are changing the value of the object being pointed to.

#### Pointers behave much like lvalue references:
Pointers and lvalue references are similar in many ways. Consider the following example:
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int& ref { x };  // get a reference to x
    int* ptr { &x }; // get a pointer to x

    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (5)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (5)

    ref = 6; // use the reference to change the value of x
    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (6)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (6)

    *ptr = 7; // use the pointer to change the value of x
    std::cout << x;
    std::cout << ref;  // use the reference to print x's value (7)
    std::cout << *ptr << '\n'; // use the pointer to print x's value (7)

    return 0;
}
```
This program will print:
```
5 5 5
6 6 6
7 7 7
```
In this example, we have a variable `x`, an lvalue reference `ref` to `x`, and a pointer `ptr` to `x`. We use both the reference and the pointer to access and modify the value of `x`. The output shows that both the reference and the pointer can be used to read and write the value of `x` in a similar manner.

Thus, pointers and references both provide a way to indirectly access another object. The primary differences between pointers and references are:
- With pointers we need to explicitly use the address-of operator (`&`) to obtain the address of an object, and the dereference operator (`*`) to access the value at that address. With references, the compiler automatically handles these operations for us.
- References must be initialized when they are declared, while pointers can be declared without initialization (but they should be).
- References are not objects, while pointers are objects that occupy memory and have their own address.
- References cannot be reseated to refer to a different object, while pointers can be reassigned to point to different objects.
- References must always be bound to an object, while pointers can be null (i.e., they can hold a special value `nullptr` that indicates they do not point to any object).
- Refernces are "safe" (outside dangling references), while pointers can be "unsafe" (dangling pointers, wild pointers, etc.).

#### The address-of operator (`&`) returns a pointer:
The address-of operator does not return the address of its operand as a literal (C++ does not support address literals). Instead, it returns a pointer to the operand, whose value is the memory address of the operand. In other words, given variable `int x` returns an `int*` holding the address of `x`. For example:
```cpp
#include <iostream>
#include <typeinfo>

int main()
{
	int x{ 4 };
	std::cout << typeid(x).name() << '\n';  // print the type of x
	std::cout << typeid(&x).name() << '\n'; // print the type of &x

	return 0;
}
```
This program will print something like:
```
int (or i, depending on the compiler)
int * (or Pi - Pointer to int -, depending on the compiler)
```
In this example, we use the `typeid` operator to obtain the type information of the variable `x` and the expression `&x`. The output shows that the type of `x` is `int`, and the type of `&x` is `int*`, which is a pointer to an `int`.

#### The size of pointers:
The size of a pointer depends on the architecture of the system (e.g., 32-bit vs 64-bit). On a 32-bit system, since the memory addresses are 32 bits (4 bytes) long, pointers are typically 4 bytes in size. On a 64-bit system, since the memory addresses are 64 bits (8 bytes) long, pointers are typically 8 bytes in size. The size of a pointer is the same regardless of the type of object it points to (e.g., `int*`, `char*`, `double*`, etc. all have the same size on a given architecture).
```cpp
#include <iostream>

int main() // assume a 32-bit application
{
    char* chPtr{};        // chars are 1 byte
    int* iPtr{};          // ints are usually 4 bytes
    long double* ldPtr{}; // long doubles are usually 8 or 12 bytes

    std::cout << sizeof(chPtr) << '\n'; // prints 4
    std::cout << sizeof(iPtr) << '\n';  // prints 4
    std::cout << sizeof(ldPtr) << '\n'; // prints 4

    return 0;
}
```
This program will print (on a 32-bit system):
```
4
4
4
```
Here we can clearly see that all pointers have the same size (4 bytes, if on a 32-bit system), regardless of the type of object they point to.

#### Dangling pointers:
A **dangling pointer** is a pointer that is holding the address of an object that is no longer valid (e.g., the object has been destroyed or deallocated). Dereferencing a dangling pointer results in **undefined behavior**, as the memory address stored in the pointer may no longer contain a valid object.

Here is how a dangling pointer could be created:
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int* ptr{ &x };

    std::cout << *ptr << '\n'; // valid

    {
        int y{ 6 };
        ptr = &y;

        std::cout << *ptr << '\n'; // valid
    } // y goes out of scope, and ptr is now dangling

    std::cout << *ptr << '\n'; // undefined behavior from dereferencing a dangling pointer

    return 0;
}
```
In this example, we create a pointer `ptr` that initially points to the variable `x`. Inside a nested scope, we create a variable `y` and change `ptr` to point to `y`. When the nested scope ends, `y` goes out of scope and is destroyed, leaving `ptr` as a dangling pointer. Dereferencing `ptr` after this point results in undefined behavior.

#### Conclusion:
Pointers are avriables that hold a memory address as their value. They can be dereferenced to access the value stored at that memory address. Pointers and lvalue references are similar in many ways, but they have some important differences. It is crucial to initialize pointers before using them and to avoid dereferencing dangling or wild pointers to prevent undefined behavior.

In general, pointers are more flexible and dangerous than lvalue references. 

#### Summary:
- A **pointer** is an object that holds a memory address as its value.
- A **pointer type** is a type that specifies a pointer to a specific type (e.g., `int*`, `char*`, etc.).
- The **address-of operator** (`&`) is used to obtain the memory address of a variable, and it returns a pointer to that variable.
- The **dereference operator** (`*`) is used to access the value stored at a specific memory address held by a pointer.
- Pointers must be initialized before use to avoid undefined behavior.
- Pointers and lvalue references are similar in many ways, but they have important differences.
- Dereferencing a **dangling pointer** results in undefined behavior.


---

### S08 - 12.8 Null pointers
In the previous section we covered the basics of pointers. In this section, we will discuss **null pointers**, which are a special type of pointer that does not point to any object.

#### Null pointers:
Besides a memory address, there is one special value that a pointer can hold: the **null value**. A **null value** (often shortened to **null**) is a special value that means something has no value. When a pointer is holding a null value, we say that the pointer is a **null pointer**. A null pointer does not point to any object.

The easisest way to create a null pointer is to use value initialization:
```cpp
int* ptr{}; // ptr is a null pointer
```
In this way, the pointer `ptr` is value-initialized to `nullptr`, which is the null pointer value in C++.

> **Best Practice:** Value initialize your pointers (to be null pointers) if you are not initializing them with the address of a valid object.

Since we can change what a pointer is pointing to, we can also change a pointer to be a null pointer by assigning it the null pointer value:
```cpp
#include <iostream>

int main()
{
    int* ptr {}; // ptr is a null pointer, and is not holding an address

    int x { 5 };
    ptr = &x; // ptr now pointing at object x (no longer a null pointer)

    std::cout << *ptr << '\n'; // print value of x through dereferenced ptr

    return 0;
}
```

#### The `nullptr` keyword:
In C++, the null pointer value is represented by the keyword `nullptr`. The `nullptr` keyword is a special literal that represents the null pointer value. It was introduced in C++11 to provide a type-safe way to represent null pointers. For example:
```cpp
int main()
{
    int* ptr { nullptr }; // can use nullptr to initialize a pointer to be a null pointer

    int value { 5 };
    int* ptr2 { &value }; // ptr2 is a valid pointer
    ptr2 = nullptr; // Can assign nullptr to make the pointer a null pointer

    someFunction(nullptr); // we can also pass nullptr to a function that has a pointer parameter

    return 0;
}
```
In this way, we can explicitly use `nullptr` to initialize or assign a pointer to be a null pointer.

> **Best Practice:** Use `nullptr` when you need a null pointer initialization, assignment, or argument.

#### Dereferencing a null pointer results in undefined behavior:
Dereferencing a null pointer (i.e., accessing the value at the memory address stored in a null pointer) results in **undefined behavior**. This is because a null pointer does not point to any valid object, and attempting to access the value at a null address is invalid, and it may crash your application.
```cpp
#include <iostream>

int main()
{
    int* ptr {}; // Create a null pointer
    std::cout << *ptr << '\n'; // Dereference the null pointer

    return 0;
}
```
This program results in undefined behavior when dereferencing the null pointer `ptr`. The program may crash, produce garbage output, or exhibit other unexpected behavior.

#### Checking for null pointers:
Like we can use conditional to test boolean values to `true` or `false`, we can also use conditionals to test whether a pointer is a null pointer or not:
```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int* ptr { &x };

    if (ptr == nullptr) // explicit test for equivalence
        std::cout << "ptr is null\n";
    else
        std::cout << "ptr is non-null\n";

    int* nullPtr {};
    std::cout << "nullPtr is " << (nullPtr==nullptr ? "null\n" : "non-null\n"); // explicit test for equivalence

    return 0;
}
```
This program will print:
```
ptr is non-null
nullPtr is null
```
In this example, we use conditionals to check whether the pointers `ptr` and `nullPtr` are null pointers or not. We use the equality operator (`==`) to compare the pointers with `nullptr`. Easy enough!

In a previous lesson, we have seen that integral values will implicitly convert to boolean values in conditionals, where `0` converts to `false`, and non-zero values convert to `true`. The same applies to pointers: null pointers convert to `false`, and non-null pointers convert to `true`. Therefore, we can simplify the previous example as follows:
```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int* ptr { &x };

    if (ptr) // implicit test for non-null
        std::cout << "ptr is non-null\n";
    else
        std::cout << "ptr is null\n";

    int* nullPtr {};
    std::cout << "nullPtr is " << (nullPtr ? "non-null\n" : "null\n"); // implicit test for non-null

    return 0;
}
```
This program will print the same output as before, but with cleaner code.

#### Use `nullptr` to avoid dangling pointers:
To avoid dereferencing a null pointer, it is a good practice to check if a pointer is null before dereferencing it. For example:
```cpp
// Assume ptr is some pointer that may or may not be a null pointer
if (ptr) // if ptr is not a null pointer
    std::cout << *ptr << '\n'; // okay to dereference
else
    // do something else that doesn't involve dereferencing ptr (print an error message, do nothing at all, etc...)
```
In this way, we avoid unexpected behaviors or crashes that may occur from dereferencing null or dangling pointers.

But what about dangling pointers? Because there is no effective way to check if a pointer is dangling (i.e., pointing to an invalid object), a common practice is to set all pointers to `nullptr` after the object they point to has been destroyed or deallocated. This way, if we accidentally dereference a dangling pointer, it will result in dereferencing a null pointer instead, which is easier to detect and handle. But of course, this is not that easy, since one a pointed object is destryed, all pointers pointing to that object become dangling, and we need to set all of them to `nullptr`, which is not always feasible.

#### Legacy null pointer literals: `NULL` and `0`:
Before C++11, the null pointer value was often represented by the macro `NULL` or the integer literal `0`. For example:
```cpp
int* ptr1 { NULL }; // using NULL macro to initialize a null pointer
int* ptr2 { 0 };    // using integer literal 0 to initialize a null pointer
```
However, using `NULL` or `0` to represent null pointers can lead to ambiguity and type-safety issues, especially in function overloads. Therefore, it is recommended to use `nullptr` instead of `NULL` or `0` for null pointer representation in modern C++. We will discuss why in a later section.

#### Foavor references over pointers when possible:
Pointers and references both give us the ability to access some other object indirectly. Pointers have the additional capability of being able to change what they point to (i.e., they can be reassigned to point to different objects) and can also be null pointers. However, this additional flexibility comes with added complexity and potential for errors (e.g., dangling pointers, wild pointers, null pointer dereferencing, etc.).
```cpp
int main()
{
    int* ptr { };

    {
        int x{ 5 };
        ptr = &x; // assign the pointer to an object that will be destroyed (not possible with a reference)
    } // ptr is now dangling and pointing to invalid object

    if (ptr) // condition evaluates to true because ptr is not nullptr
        std::cout << *ptr; // undefined behavior

    return 0;
}
```

Instead, since references cannot be bound to null or changed to refer to different objects, they are generally safer and easier to use. Therefore, when designing functions or data structures, prefer using references over pointers whenever possible. Use pointers only when you need the additional flexibility that pointers provide (e.g., when you need to represent optional objects with null pointers, or when you need to change what an object points to).

> **Best Practice:** Favor using references over pointers when possible to reduce complexity and potential errors. Use pointers only when necessary.

#### Summary:
- A **null pointer** is a pointer that does not point to any object.
- The null pointer value is represented by the keyword `nullptr` in C++.
- Dereferencing a null pointer results in undefined behavior.
- Use conditionals to check for null pointers before dereferencing them.
- To avoid dangling pointers, set pointers to `nullptr` after the object they point to has been destroyed or deallocated.
- Prefer using references over pointers when possible to reduce complexity and potential errors.


---

### S09 - 12.9 Pointers ad const
Consider the following code snippet:
```cpp
int main()
{
    int x { 5 };
    int* ptr { &x }; // ptr is a normal (non-const) pointer

    int y { 6 };
    ptr = &y; // we can point at another value

    *ptr = 7; // we can change the value at the address being held

    return 0;
}
```
With normal (non-const) pointers, we can change both what the pointer is pointing to (i.e., change the memory address stored in the pointer) and the value of the object being pointed to (i.e., change the value at the memory address stored in the pointer).

But what happens if the value we want to point at is const? For example:
```cpp
int main()
{
    const int x { 5 }; // x is now const
    int* ptr { &x };   // compile error: cannot convert from const int* to int*

    return 0;
}
```
This code results in a compilation error because we are trying to initialize a normal (non-const) pointer (`int*`) with the address of a `const int` object. This is not allowed because a normal pointer allows modifying the value at the address being pointed to, which would violate the constness of the object.

#### Pointer to const value:
A **pointer to const value** is a pointer that points to a const object. This means that we cannot change the value of the object being pointed to through the pointer. To declare a pointer to const value, we use the `const` keyword before the type name in the pointer declaration. For example:
```cpp
int main()
{
    const int x{ 5 };
    const int* ptr { &x }; // okay: ptr is pointing to a "const int"

    *ptr = 6; // not allowed: we can't change a const value

    return 0;
}
```
In this example, we declare a pointer `ptr` that points to a `const int` object. We cannot change the value of `x` through the pointer `ptr`, as it is a pointer to a const value. We can instead change what the pointer is pointing to:
```cpp
int main()
{
    const int x{ 5 };
    const int* ptr { &x }; // ptr points to const int x

    const int y{ 6 };
    ptr = &y; // okay: ptr now points at const int y

    return 0;
}
```
Here, we change the pointer `ptr` to point to another `const int` object `y`. This is allowed because we are not changing the value of the object being pointed to; we are only changing what the pointer is pointing to.

Like a reference to const, a pointer to const can point to both const and non-const objects:
```cpp
int main()
{
    int x{ 5 }; // non-const
    const int* ptr { &x }; // ptr points to a "const int"

    *ptr = 6;  // not allowed: ptr points to a "const int" so we can't change the value through ptr
    x = 6; // allowed: the value is still non-const when accessed through non-const identifier x

    return 0;
}
```
In this way, a pointer to const provides a way to safely point to objects without allowing modification of their values through the pointer.

#### Const pointers:
We can also make a pointer itself constant. A **const pointer** is a pointer that cannot change what it is pointing to (i.e., the memory address stored in the pointer cannot be changed). To declare a const pointer, we use the `const` keyword after the `*` symbol in the pointer declaration. For example:
```cpp
int main()
{
    int x{ 5 };
    int* const ptr { &x }; // const after the asterisk means this is a const pointer

    return 0;
}
```
Doing so, we declare a const pointer `ptr` that points to the variable `x`. We cannot change what `ptr` is pointing to. Like normal const variables, a const pointer must be initialized upon definition, and this value cannot be changed later via assignment:
```cpp
int main()
{
    int x{ 5 };
    int y{ 6 };

    int* const ptr { &x }; // okay: the const pointer is initialized to the address of x
    ptr = &y; // error: once initialized, a const pointer can not be changed.

    return 0;
}
```
In this example, we attempt to change the const pointer `ptr` to point to the variable `y`, which results in a compilation error because const pointers cannot be reassigned after initialization. However, because the value being pointed to is non-const, we can change the value of `x` through the const pointer:
```cpp
int main()
{
    int x{ 5 };
    int* const ptr { &x }; // ptr will always point to x

    *ptr = 6; // okay: the value being pointed to is non-const

    return 0;
}
```

#### Const pointer to a const value:
Finally, we can combine both concepts to create a **const pointer to a const value**. This is a pointer that cannot change what it is pointing to, and also cannot change the value of the object being pointed to. To declare a const pointer to a const value, we use the `const` keyword both before the type name and after the `*` symbol in the pointer declaration. For example:
```cpp
int main()
{
    int value { 5 };
    const int* const ptr { &value }; // a const pointer to a const value

    return 0;
}
```

#### Pointer and const recap:
To summarize, you will need to remember these 4 pretty logical rules:
- A non-const. pointer (e.g., `int * ptr`) can change what it is pointing to (i.e., the memory address stored in the pointer)
- A const pointer (e.g., `int* const ptr`) always points to the same address (i.e., the memory address stored in the pointer cannot be changed)
- A pointer to a non-const value (e.g., `int* ptr`) can change the value of the object being pointed to (i.e., the value at the memory address stored in the pointer), and cannot point to a const value
- A pointer to a const value (e.g., `const int* ptr`) cannot change the value of the object being pointed to (i.e., the value at the memory address stored in the pointer), but can point to both const and non-const values

Regarding the const keyword placement, remember:
- If `const` is before the `*`, it applies to the value being pointed to (i.e., pointer to const value), meaning that the value at the memory address stored in the pointer cannot be changed
- If `const` is after the `*`, it applies to the pointer itself (i.e., const pointer), meaning that the pointer cannot change what it is pointing to

```cpp
int main()
{
    int v{ 5 };

    int* ptr0 { &v };             // points to an "int" but is not const itself.  We can modify the value or the address.
    const int* ptr1 { &v };       // points to a "const int" but is not const itself.  We can only modify the address.
    int* const ptr2 { &v };       // points to an "int" and is const itself.   We can only modify the value.
    const int* const ptr3 { &v }; // points to a "const int" and is const itself.  We can't modify the value nor the address.

    // if the const is on the left side of the *, the const belongs to the value
    // if the const is on the right side of the *, the const belongs to the pointer

    return 0;
}
```

#### Summary:
- A **pointer to const value** is a pointer that points to a const object, and cannot change the value of the object being pointed to through the pointer.
- A **const pointer** is a pointer that cannot change what it is pointing to (i.e., the memory address stored in the pointer cannot be changed).
- A **const pointer to a const value** is a pointer that cannot change what it is pointing to, and also cannot change the value of the object being pointed to.
- The placement of the `const` keyword in a pointer declaration determines whether it applies to the value being pointed to or the pointer itself.


---

### S10 - 12.10 Pass by address
In previous sections, we covered two main ways to pass arguments to functions: **pass by value** and **pass by lvalue reference**:
```cpp
#include <iostream>
#include <string>

void printByValue(std::string val) // The function parameter is a copy of str
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const std::string& ref) // The function parameter is a reference that binds to str
{
    std::cout << ref << '\n'; // print the value via the reference
}

int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str

    return 0;
}
```
When we pass arguemnt `str` by value, a copy of `str` is made, and the function works with that copy. When we pass argument `str` by lvalue reference, no copy is made, and the function works directly with the original object. In this case, since our reference parameter is const, the function cannot modify the original object.

In both cases, the caller is providing the actual object (`str`) to be passed as an argument to the function call.
But what if we want to pass the address of the object instead of the object itself? This is where **pass by address** comes in.

#### Pass by address:
C++ provides a third way to pass values to a function, called **pass by address**. In pass by address, instead of providing an object as an argument, the caller provides the address of the object (i.e., a pointer to the object). This pointer is copied into a pointer parameter of the called function, which now has access to the original object via the pointer. For example:
```cpp
#include <iostream>
#include <string>

void printByValue(std::string val) // The function parameter is a copy of str
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const std::string& ref) // The function parameter is a reference that binds to str
{
    std::cout << ref << '\n'; // print the value via the reference
}

void printByAddress(const std::string* ptr) // The function parameter is a pointer that holds the address of str
{
    std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}

int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str
    printByAddress(&str); // pass str by address, does not make a copy of str

    return 0;
}
```
All the three functions are very similar, but let us see the latter in more details.

First, because we want our `printByAddress` function to use pass by address, we have made our function parameter a pointer to `const std::string` (`const std::string* ptr`). This means that the function parameter `ptr` will hold the address of a `const std::string` object, and we cannot modify the value of the object being pointed to through the pointer.
```cpp
void printByAddress(const std::string* ptr) // The function parameter is a pointer that holds the address of str
{
    std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}
```
Inside the function, we use the dereference operator (`*`) to access the value of the object being pointed to by the pointer `ptr`. We then print that value.

Second, when the function is called, we cannot just pass the object `str` directly, because the function parameter is a pointer, not an object. Instead, we need to pass the address of the object `str` using the address-of operator (`&`):
```cpp
printByAddress(&str); // pass str by address, does not make a copy of str
```
When this call is executed, `&str` will create a pointer holding the address of `str`. This address is then copied into function arameter `ptr`, which now points to the original object `str`.

In this example we used the address-of operator, but in case we already have a pointer to the object, we can pass that pointer directly:
```cpp
int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str
    printByAddress(&str); // pass str by address, does not make a copy of str

    std::string* ptr { &str }; // define a pointer variable holding the address of str
    printByAddress(ptr); // pass str by address, does not make a copy of str

    return 0;
}
```
In this case, we first create a pointer `ptr` that holds the address of `str`. We then pass that pointer directly to the `printByAddress` function.

#### Pass by address does not make a copy of the object being pointed to:
Consider this example:
```cpp
std::string str{ "Hello, world!" };
printByAddress(&str); // use address-of operator (&) to get pointer holding address of str
```
As we have seen previously, doing a copy of `std::string` can be expensive, especially for large strings, and we want to avoid it. By using pass by address, we avoid making a copy of the object `str`. Instead, we only copy the pointer (holding the address of the object) into the function parameter. This is much more efficient, as copying a pointer is typically a very cheap operation (usually just copying a memory address, of 4 or 8 bytes depending on the architecture).

#### Pass by address allows the function to modify the arguement's value:
Since we are passing the address of the object to the function, the function can use that address to modify the value of the original object by dereferencing the pointer. For example:
```cpp
#include <iostream>

void changeValue(int* ptr) // note: ptr is a pointer to non-const in this example
{
    *ptr = 6; // change the value to 6
}

int main()
{
    int x{ 5 };

    std::cout << "x = " << x << '\n';

    changeValue(&x); // we're passing the address of x to the function

    std::cout << "x = " << x << '\n';

    return 0;
}
```
will print:
```
x = 5
x = 6
```
As you can easily see, the `changeValue` function takes a pointer to `int` as its parameter. Inside the function, we dereference the pointer and change the value of the object being pointed to. When we call the function with the address of `x`, the function modifies the original object `x` through the pointer.

In case a function should not modify the value of the object being pointed to, we can use a pointer to const value as the function parameter:
```cpp
void changeValue(const int* ptr) // note: ptr is now a pointer to a const
{
    *ptr = 6; // error: can not change const value
}
```
in this way, the function cannot modify the value of the object being pointed to through the pointer.

For many of the same reasons, we typically do not `const` refgular (non-pointer, non-reference) function parameters, as it does not provide any additional safety or benefits. Additionally we also do not `const` pointer function parameters.

Let's make two assertions:
- A `const` keyword used to make a pointer function parameter a const pointer provides little value (since it has no impact on the caller, and mostly serves as documentation for the callee)
- A `const` keyword used to differentiate a pointer-to-const from a pointer-to-non-const provides significant value (since it provides safety for the callee, and documents the intent of the function)

So overall, when using pass by address, we typically only use `const` to make the pointer a pointer to const value, and not to make the pointer itself a const pointer.

> **Best Practice:** Prefer pointer-to-const function parameters over pointer-to-non-const function parameters, unless the function needs to modify the object passed in.
Do not make function parameters const pointers unless there is some specific reason to do so.

f we only use non-const pointer function parameters, then all uses of `const` are significant. As soon as we start using `const` for const pointer function parameters, then it becomes more difficult to determine whether a given use of `const` is significant or not. More importantly, it also makes it harder to notice pointer-to-non-const parameters. For example:
```cpp
void foo(const char* source, char* dest, int count);             // Using non-const pointers, all consts are significant.
void foo(const char* const source, char* const dest, int count); // Using const pointers, `dest` being a pointer-to-non-const may go unnoticed amongst the sea of spurious consts.
```
In the former case, it is easy to see that `source` is a pointer to const value, and `dest` is a pointer to non-const value. In the latter case, the presence of const pointers makes it harder to notice that `dest` is a pointer to non-const value.

#### Null checking:
Now consider this innocent program:
```cpp
#include <iostream>

void print(int* ptr)
{
	std::cout << *ptr << '\n';
}

int main()
{
	int x{ 5 };
	print(&x);

	int* myPtr {};
	print(myPtr);

	return 0;
}
```
This program has a serious problem: it dereferences a null pointer! In the `main` function, we create a null pointer `myPtr` and pass it to the `print` function. Inside the `print` function, we dereference the pointer without checking if it is null, which results in undefined behavior.

To avoid this, when passing a parameter by address, it is a good practice to check if the pointer is null before dereferencing it. For example:
```cpp
void print(int* ptr)
{
    if (ptr) // check if ptr is not null
        std::cout << *ptr << '\n'; // safe to dereference
    else
        std::cout << "Error: null pointer\n"; // handle null pointer case
}
```
In this way, we avoid dereferencing null pointers and prevent undefined behavior.

While this can work for easy functions, it might be cumbersome for more complex functions. In general, it is better to test for the negative case (i.e., null pointer) early in the function and handle it appropriately (e.g., return an error code, throw an exception, etc.) rather than checking for null pointers throughout the function. For example:
```cpp
void print(int* ptr)
{
    if (!ptr) // check for null pointer early
    {
        std::cout << "Error: null pointer\n"; // handle null pointer case
        return; // exit the function early
    }

    // if we reached this point, ptr is guaranteed to be non-null
    std::cout << *ptr << '\n'; // safe to dereference
}
```
In this way, we handle the null pointer case early in the function, and the rest of the function can safely assume that the pointer is non-null.

If a null pointer should nebver be passed to a function, and there is no way to recover from it, an **assertion** can be used to document this assumption and catch violations during development:
```cpp
#include <cassert>

void print(int* ptr)
{
    assert(ptr && "ptr should never be null"); // assert that ptr is not null, failing the program if it is

    // (optionally) handle this as an error case in production mode so we don't crash if it does happen
    if (!ptr)
        return;
    
    std::cout << *ptr << '\n'; // safe to dereference
}
```
In this way, we use an assertion to document the assumption that `ptr` should never be null. If this assumption is violated during development, the program will terminate with an assertion failure, helping us catch the error early.

#### Prefer pass by (const) reference:
The previous function `print()` does not handle null values very well, it simply aborts the program if a null pointer is passed in. 

So we allowing the user to pass a null pointer at all? **Pass by reference** has the same benefits as pass by address (i.e., no copy of the object is made), without the risk of inadvertently passing a null pointer.

Moreover, pass by const reference has few other advantages over pass by address:
- Since an object passed by address must have an address, only lvalues (i.e., named objects) can be passed by address. In contrast, both lvalues and rvalues (e.g., temporary objects) can be passed by const reference.
    ```cpp
    #include <iostream>

    void printByValue(int val) // The function parameter is a copy of the argument
    {
        std::cout << val << '\n'; // print the value via the copy
    }

    void printByReference(const int& ref) // The function parameter is a reference that binds to the argument
    {
        std::cout << ref << '\n'; // print the value via the reference
    }

    void printByAddress(const int* ptr) // The function parameter is a pointer that holds the address of the argument
    {
        std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
    }

    int main()
    {
        printByValue(5);     // valid (but makes a copy)
        printByReference(5); // valid (because the parameter is a const reference)
        printByAddress(&5);  // error: can't take address of r-value

        return 0;
    }
    ```
- The syntax for pass by reference is natural, as we can just pass in literals or objects directly without needing to use the address-of operator (`&`).
- There is no need to check for null pointers when using pass by reference, as references cannot be null.

> **Best Practice:** Prefer pass by (const) reference over pass by address when possible, to avoid the risk of null pointers and to allow passing both lvalues and rvalues.

#### Summary:
- **Pass by address** is a way to pass arguments to functions by providing the address of the object (i.e., a pointer to the object) instead of the object itself.
- Pass by address does not make a copy of the object being pointed to, making it more efficient for large objects.
- Functions can modify the value of the original object through the pointer parameter.
- It is a good practice to check for null pointers before dereferencing them in functions that use pass by address.
- Prefer pass by (const) reference over pass by address when possible, to avoid the risk of null pointers and to allow passing both lvalues and rvalues.


---

### S11 - 12.11 Pass by address (part 2)
#### Pass by address for "optional" arguments:
One of the most common use cases for pass by address is to allow functions to have "optional" arguments. An optional argument is an argument that may or may not be provided by the caller. If the caller does not provide the argument, the function uses a default value or behavior. For example:
```cpp
#include <iostream>

void printIDNumber(const int *id=nullptr)
{
    if (id)
        std::cout << "Your ID number is " << *id << ".\n";
    else
        std::cout << "Your ID number is not known.\n";
}

int main()
{
    printIDNumber(); // we don't know the user's ID yet

    int userid { 34 };
    printIDNumber(&userid); // we know the user's ID now

    return 0;
}
```
This program will print:
```
Your ID number is not known.
Your ID number is 34.
```
In this example, the `printIDNumber` function has a pointer parameter `id` that defaults to `nullptr`. This means that if the caller does not provide an argument for `id`, it will be a null pointer inside the function. The function checks if `id` is null, and if it is not, it prints the ID number. Otherwise, it prints a message indicating that the ID number is not known.

However, in may cases, **function overloading** is a better alternative to achieve the same result:
```cpp
#include <iostream>

void printIDNumber()
{
    std::cout << "Your ID is not known\n";
}

void printIDNumber(int id)
{
    std::cout << "Your ID is " << id << "\n";
}

int main()
{
    printIDNumber(); // we don't know the user's ID yet

    int userid { 34 };
    printIDNumber(userid); // we know the user is 34

    printIDNumber(62); // now also works with rvalue arguments

    return 0;
}
```
This has a number of advantages: we no longer have to worry about null dereferences, and we can pass in literals or other rvalues directly without needing to use the address-of operator (`&`).

#### Changing what a pointer parameter points at:
When passing an argument by address, that address is copied from the argument into the pointer parameter (which is fast, since copying a pointer is cheap). Now consider the following code:
```cpp
#include <iostream>

// [[maybe_unused]] gets rid of compiler warnings about ptr2 being set but not used
void nullify([[maybe_unused]] int* ptr2)
{
    ptr2 = nullptr; // Make the function parameter a null pointer
}

int main()
{
    int x{ 5 };
    int* ptr{ &x }; // ptr points to x

    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");

    nullify(ptr);

    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");
    return 0;
}
```
This program will print:
```
ptr is non-null
ptr is non-null
```
This is because in the `nullify` function, we are changing what the function parameter `ptr2` points at (i.e., we are making `ptr2` a null pointer). However, this does not affect the original pointer `ptr` in the `main` function, as `ptr2` is a copy of `ptr`. Therefore, changing `ptr2` does not change `ptr`.

> **Note:** Since the function parameter is a copy of the argument, changing what the pointer parameter points at does not affect the original pointer in the caller.

So what if we want to allow a function to change what a pointer argument points at? We can achieve this by passing the pointer by reference! It might sound confusing, but it is actually quite simple.

#### Pass by address... by reference:
Just like we can pass normal variables by reference, we can also pass pointers by reference. This allows the function to modify the original pointer argument in the caller. To do so, you just need to add an additional `&` symbol to the pointer parameter declaration.
For example:
```cpp
#include <iostream>

void nullify(int*& refptr) // refptr is now a reference to a pointer
{
    refptr = nullptr; // Make the function parameter a null pointer
}

int main()
{
    int x{ 5 };
    int* ptr{ &x }; // ptr points to x

    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");

    nullify(ptr);

    std::cout << "ptr is " << (ptr ? "non-null\n" : "null\n");
    return 0;
}
```
This program will print:
```
ptr is non-null
ptr is null
```
In this example, we declare the function parameter `refptr` as a reference to a pointer (`int*& refptr`). This means that `refptr` is an alias for the original pointer argument `ptr` in the `main` function. Therefore, when we change what `refptr` points at (i.e., make it a null pointer), it also changes what `ptr` points at in the `main` function.

#### Why using `0` or `NULL` is no longer preferred (Optional):
The literal `0` can be interpreted as either an integral literal or a null pointer literal, depending on the context. This can lead to ambiguity and confusion, especially in function overloads, the compiler may assume we mean one when we actually mean the other. 

In a previous chapter, we have seen that function can be overloaded (multiple functions can have the same name, as long as they can be differentiated by the number or types of their parameters). When using `0` or `NULL` as a null pointer literal, it can lead to ambiguity in function overloads. For example:
```cpp
#include <iostream>
#include <cstddef> // for NULL

void print(int x) // this function accepts an integer
{
	std::cout << "print(int): " << x << '\n';
}

void print(int* ptr) // this function accepts an integer pointer
{
	std::cout << "print(int*): " << (ptr ? "non-null\n" : "null\n");
}

int main()
{
	int x{ 5 };
	int* ptr{ &x };

	print(ptr);  // always calls print(int*) because ptr has type int* (good)
	print(0);    // always calls print(int) because 0 is an integer literal (hopefully this is what we expected)

	print(NULL); // this statement could do any of the following:
	// call print(int) (Visual Studio does this)
	// call print(int*)
	// result in an ambiguous function call compilation error (gcc and Clang do this)

	print(nullptr); // always calls print(int*)

	return 0;
}
```
In this example, we have two overloaded functions named `print`: one that accepts an `int` parameter, and another that accepts an `int*` parameter. When we call `print(NULL)`, the compiler cannot determine which function to call, as `NULL` can be interpreted as either an integer literal or a null pointer literal. Also, when we call `print(0)`, it always calls the `print(int)` function, which may not be what we intended if we wanted to pass a null pointer.
This results in an ambiguous function call compilation error in some compilers (e.g., gcc and Clang), while other compilers (e.g., Visual Studio) may choose to call one of the functions, which may not be what we intended.
On Visual Sudio, it will print something like:
```
print(int*): non-null
print(int): 0
print(int): 0
print(int*): null
```

Using `nullptr` instead of `0` or `NULL` resolves this ambiguity, as `nullptr` is specifically designed to represent a null pointer value. Therefore, when we call `print(nullptr)`, it always calls the `print(int*)` function, which is the intended behavior.

#### `std::nullptr_t` type (Optional):
Since `nullptr` is a keyword representing the null pointer value, it has its own type called `std::nullptr_t`. This type is defined in the `<cstddef>` header file. The `std::nullptr_t` can only hold one value: `nullptr`. This type is primarily used for type safety and to differentiate null pointer values from other types. Also, in cases where we want to pass to a function `nullptr` literal arguments only:
```cpp
#include <iostream>
#include <cstddef> // for std::nullptr_t

void print(std::nullptr_t)
{
    std::cout << "in print(std::nullptr_t)\n";
}

void print(int*)
{
    std::cout << "in print(int*)\n";
}

int main()
{
    print(nullptr); // calls print(std::nullptr_t)

    int x { 5 };
    int* ptr { &x };

    print(ptr); // calls print(int*)

    ptr = nullptr;
    print(ptr); // calls print(int*) (since ptr has type int*)

    return 0;
}
```
This program will print:
```
in print(std::nullptr_t)
in print(int*)
in print(int*)
```
In this example, we have two overloaded functions named `print`: one that accepts a `std::nullptr_t` parameter, and another that accepts an `int*` parameter. When we call `print(nullptr)`, it calls the `print(std::nullptr_t)` function, as `nullptr` has the type `std::nullptr_t`. When we call `print(ptr)`, it calls the `print(int*)` function, as `ptr` has the type `int*`.

#### There is only pass by value:
Now that you understand the basic differences between passing by reference, address, and value, let's get reductionist for a moment: in C++, **there is only pass by value**. 

When we say we are passing by reference or by address, what we really mean is that we are passing a value that is either a reference or a pointer. In both cases, the value being passed is copied into the function parameter. 

When passing by reference, the value being passed is a reference (i.e., an alias for the original object). When passing by address, the value being passed is a pointer (i.e., the memory address of the original object). In both cases, the function parameter receives a copy of the value being passed.

#### Summary:
- Pass by address is commonly used to allow functions to have "optional" arguments by using null pointers.
- Function overloading is often a better alternative to achieve optional arguments without the risk of null dereferences.
- To allow a function to change what a pointer argument points at, pass the pointer by reference (using `int*&` syntax).
- Using `nullptr` instead of `0` or `NULL` avoids ambiguity in function overloads and improves type safety.
- `std::nullptr_t` is the type of the `nullptr` literal, used for type safety and differentiation from other types.
- In C++, there is only pass by value; passing by reference or address involves passing a value that is either a reference or a pointer.


---

### S12 - 12.12 Return by reference and return by address
In the previous sections, we have discussed that when passing an argument by value, a copy of the argument is made and passed to the function. For fundamental types (e.g., `int`, `char`, `float`, etc.), this is usually not a problem, as copying these types is cheap. However, for user-defined types (e.g., classes, structs, etc.), copying can be expensive, especially for large objects.
To avoid the overhead of copying large objects, we can use **return by reference** or **return by address**.

We encountered a simular situation when returning by value, since a copy of the return value is made when returning by value, for example:
```cpp
std::string returnByValue(); // returns a copy of a std::string object (expensive for large strings)
```

To avoid this overhead, we can use return by reference or return by address. Let's see how.

#### Return by reference:
When we are passing class type back to the caller, we may (or may not) want to return by reference instead of by value. **Reeturn by reference** returns a reference bound to the original object, instead of a copy of the object. This avoids the overhead of copying the object, as no copy is made. For example:
```cpp
std::string&       returnByReference(); // returns a reference to an existing std::string (cheap)
const std::string& returnByReferenceToConst(); // returns a const reference to an existing std::string (cheap)
```
In this example, the `returnByReference` function returns a reference to an existing `std::string` object, while the `returnByReferenceToConst` function returns a const reference to an existing `std::string` object. In both cases, no copy of the object is made, making it more efficient for large objects.

Here is an academic program to demonsatrate return by reference:
```cpp
#include <iostream>
#include <string>

const std::string& getProgramName() // returns a const reference
{
    static const std::string s_programName { "Calculator" }; // has static duration, destroyed at end of program

    return s_programName;
}

int main()
{
    std::cout << "This program is named " << getProgramName();

    return 0;
}
```
This program will print:
```
This program is named Calculator
```
In this example, the `getProgramName` function returns a const reference to a static `std::string` object. Since the object has static duration, it will not be destroyed when the function returns, and the reference remains valid in the caller.

#### The object being returned by reference must exist after the function returns:
One major caveat is that when returning by reference, it is crucial to ensure that the object being referenced still exists after the function returns. If the object goes out of scope or is destroyed, the reference will become **dangling**, leading to undefined behavior when accessed in the caller. For example, if we modify our code:
```cpp
#include <iostream>
#include <string>

const std::string& getProgramName()
{
    const std::string programName { "Calculator" }; // now a non-static local variable, destroyed when function ends

    return programName;
}

int main()
{
    std::cout << "This program is named " << getProgramName(); // undefined behavior

    return 0;
}
```
This program has undefined behavior because the `programName` variable is a local variable that goes out of scope when the `getProgramName` function returns. Therefore, the reference returned by the function becomes dangling, and accessing it in the `main` function leads to undefined behavior.

Modern compilers often issue warnings when they detect that a function is returning a reference to a local variable, as this is a common source of bugs.

> **Warning:** Never return a reference to a local variable from a function, as it will lead to dangling references and undefined behavior.

#### Lifetime extention does not work across function boudnaries:
Let us take a look at an example where we return a temporary object by reference:
```cpp
#include <iostream>

const int& returnByConstReference()
{
    return 5; // returns const reference to temporary object
}

int main()
{
    const int& ref { returnByConstReference() };

    std::cout << ref; // undefined behavior

    return 0;
}
```
This program has undefined behavior because the temporary object created by the literal `5` in the `returnByConstReference` function goes out of scope when the function returns. Therefore, the reference returned by the function becomes dangling, and accessing it in the `main` function leads to undefined behavior.

Here’s a less obvious example that similarly doesn’t work:
```cpp
#include <iostream>

const int& returnByConstReference(const int& ref)
{
    return ref;
}

int main()
{
    // case 1: direct binding
    const int& ref1 { 5 }; // extends lifetime
    std::cout << ref1 << '\n'; // okay

    // case 2: indirect binding
    const int& ref2 { returnByConstReference(5) }; // binds to dangling reference
    std::cout << ref2 << '\n'; // undefined behavior

    return 0;
}
```
In this example, the `returnByConstReference` function takes a const reference as a parameter and returns it. In the `main` function, we first create a const reference `ref1` that directly binds to the temporary object created by the literal `5`, which extends its lifetime. However, when we call `returnByConstReference(5)`, the temporary object created by the literal `5` goes out of scope when the function returns, leading to a dangling reference in `ref2`.

> **Warning:** Reference lifetime extention does not work across function boundaries. Never return a reference to a temporary object from a function, as it will lead to dangling references and undefined behavior.

#### Do not return non-const static local variables by reference:
While it is safe to return static local variables by reference, as we did in the first example, it is generally not a good practice to return non-const static local variables by reference. This is because returning a non-const reference allows the caller to modify the static variable, which can lead to unexpected behavior and make the code harder to reason about. For example:
```cpp
#include <iostream>
#include <string>

const int& getNextId()
{
    static int s_x{ 0 }; // note: variable is non-const
    ++s_x; // generate the next id
    return s_x; // and return a reference to it
}

int main()
{
    const int& id1 { getNextId() }; // id1 is a reference
    const int& id2 { getNextId() }; // id2 is a reference

    std::cout << id1 << id2 << '\n';

    return 0;
}
```
This program will print:
```
12
```
This happens because the `getNextId` function returns a reference to the static variable `s_x`, which is incremented each time the function is called. Therefore, both `id1` and `id2` refer to the same static variable, which has the value `2` after two calls to the function.

> **Best Practice:** Avoid returning non-const static local variables by reference, as it allows the caller to modify the static variable, leading to unexpected behavior.

Returning a const reference to a const local static variable is sometimes done if the local variable being returned by reference is expensive to create and/or initialize (so we don’t have to recreate the variable every function call). But this is rare.

Sometimes it is also done to encapsulate access to a global variable, we discussed this in a previous chapter.

#### Assigning/initializing a normal variable with a returned reference makes a copy:
If a function returns a reference, and we use that return value to initialize or assign to a normal variable, a copy of the object being referenced is made. For example:
```cpp
#include <iostream>
#include <string>

const int& getNextId()
{
    static int s_x{ 0 };
    ++s_x;
    return s_x;
}

int main()
{
    const int id1 { getNextId() }; // id1 is a normal variable now and receives a copy of the value returned by reference from getNextId()
    const int id2 { getNextId() }; // id2 is a normal variable now and receives a copy of the value returned by reference from getNextId()

    std::cout << id1 << id2 << '\n';

    return 0;
}
```
This program will print:
```
12
```
This happens because `id1` and `id2` are normal variables, not references. Therefore, when we initialize them with the return value of `getNextId`, a copy of the value being referenced is made. As a result, `id1` receives the value `1`, and `id2` receives the value `2`, and they are not bound to the same object.

Also note that if the function returns a dangling reference, the reference is left dangling before the copy is made, leading to undefined behavior.
```cpp
#include <iostream>
#include <string>

const std::string& getProgramName() // will return a const reference
{
    const std::string programName{ "Calculator" };

    return programName;
}

int main()
{
    std::string name { getProgramName() }; // makes a copy of a dangling reference
    std::cout << "This program is named " << name << '\n'; // undefined behavior

    return 0;
}
```
This program has undefined behavior because the `getProgramName` function returns a dangling reference to a local variable `programName`. When we initialize the `name` variable with the return value of `getProgramName`, we are making a copy of a dangling reference, leading to undefined behavior when we access `name`.

#### It is okay to return reference parameters by reference:
There are few cases in which returning objects by reference makes sense. One such case is when returning reference parameters by reference. If a parameter is passed by reference to a function, it is safe to return that parameter by reference, as the object being referenced will still exist after the function returns. For example:
```cpp
#include <iostream>
#include <string>

// Takes two std::string objects, returns the one that comes first alphabetically
const std::string& firstAlphabetical(const std::string& a, const std::string& b)
{
	return (a < b) ? a : b; // We can use operator< on std::string to determine which comes first alphabetically
}

int main()
{
	std::string hello { "Hello" };
	std::string world { "World" };

	std::cout << firstAlphabetical(hello, world) << '\n';

	return 0;
}
```
This program will print:
```
Hello
```
In this example, the `firstAlphabetical` function takes two `std::string` objects by const reference and returns the one that comes first alphabetically by returning a const reference to the appropriate parameter. Since the parameters are passed by reference, they will still exist after the function returns, making it safe to return them by reference.

#### It is okay for an rvalue passed by const reference to be returned by const reference:
When an argument for a const reference parameter is an rvalue, it is safe to return that parameter by const reference, as the rvalue will not be destryed before the full expression containing the function call is complete. For example:
```cpp
#include <iostream>
#include <string>

std::string getHello()
{
    return "Hello"; // implicit conversion to std::string
}

int main()
{
    const std::string s{ getHello() };

    std::cout << s;

    return 0;
}
```
In this example, the `getHello` returns a temporary `std::string` object created from the string literal `"Hello"`, that is an rvalue. This rvalue is the used to initialize the const reference `s` in the `main` function. The lifetime of the temporary object is extended to match the lifetime of the const reference `s`, making it safe to use.

Now let us have a look at the following example:
```cpp
#include <iostream>
#include <string>

const std::string& foo(const std::string& s)
{
    return s;
}

std::string getHello()
{
    return "Hello"; // implicit conversion to std::string
}

int main()
{
    const std::string s{ foo(getHello()) };

    std::cout << s;

    return 0;
}
```
The only difference here is that we are passing the rvalue returned by `getHello()` to the `foo` function, which takes a const reference parameter and returns it by const reference. This is still safe, as the lifetime of the temporary object created by `getHello()` is extended to match the lifetime of the const reference `s` in the `main` function.

#### The cller can modify values through the reference:
When an argument is passed to a function by a non-const reference, the function can use the reference to modify the original object in the caller. In a similar way, if a function returns a non-const reference, the caller can use that reference to modify the original object being referenced. For example:
```cpp
#include <iostream>

// takes two integers by non-const reference, and returns the greater by reference
int& max(int& x, int& y)
{
    return (x > y) ? x : y;
}

int main()
{
    int a{ 5 };
    int b{ 6 };

    max(a, b) = 7; // sets the greater of a or b to 7

    std::cout << a << b << '\n';

    return 0;
}
```
This program will print:
```
57
```
In this example, the `max` function takes two integers by non-const reference and returns the greater of the two by reference. In the `main` function, we call `max(a, b)` and assign the value `7` to the returned reference. Since `b` is greater than `a`, `b` is modified to `7`, while `a` remains `5`.

#### Return by address:
Similar to return by reference, we can also return by address. **Return by address** works almost identically to return by reference, except that instead of returning a reference to the object, we return a pointer to the object. This approach has the same primary caveat as return by reference: the returned pointed object must still exist after the function returns (outside the function's scope), otherwise we will end up with a dangling pointer.

The major **advantage** of return by address over return by reference is that it allows us to return a null pointer (`nullptr`) to indicate that there is no valid object to return. For example, let's say we want to search a specific pizza in a menu list (sorry I am italian), we can use return by address to return a pointer to the pizza if found, or `nullptr` if not found. (Or maybe fake it is not present if you are looking for a pizza with pineapple... just kidding! Or not...)

The major **disadvantage** of return by address is that it requires the caller to check for null pointers before dereferencing the returned pointer, which can lead to more verbose and error-prone code. Because of this danger, return by reference is often preferred over return by address when possible.

> **Best Practice:** Prefer return by reference over return by address, unless the function must be able to indicate the absence of a valid object (e.g., by returning a null pointer).

#### Summary:
- Return by reference returns a reference bound to the original object, avoiding the overhead of copying large objects.
- The object being returned by reference must exist after the function returns; never return a reference to a local variable or temporary object.
- Reference lifetime extension does not work across function boundaries; never return a reference to a temporary object from a function.
- Avoid returning non-const static local variables by reference, as it allows the caller to modify the static variable.
- Assigning or initializing a normal variable with a returned reference makes a copy of the object being referenced.
- It is safe to return reference parameters by reference, as they will still exist after the function returns.
- It is safe to return an rvalue passed by const reference by const reference, as the lifetime of the temporary object is extended to match the lifetime of the const reference in the caller.
- The caller can modify values through a returned non-const reference.
- Return by address works similarly to return by reference but allows returning a null pointer to indicate the absence of a valid object.
- Prefer return by reference over return by address, unless the function must indicate the absence of a valid object.


---

### S13 - 12.13 In and out parameters
A function and its caller communicate via two mechanism: parameters and return values. Parameters are used to pass information from the caller to the function (by value, by reference, or by address), while return values are used to pass information from the function back to the caller.

Typically we will pass arguments by value or by const reference, but there are cases where we will do otherwise.

#### In parameters:
An **in parameter** is a parameter that is used only for receiving input data from the caller. In parameters are typically passed by value or by const reference, as the function does not need to modify the original object in the caller. For example:
```cpp
#include <iostream>

void print(int x) // x is an in parameter
{
    std::cout << x << '\n';
}

void print(const std::string& s) // s is an in parameter
{
    std::cout << s << '\n';
}

int main()
{
    print(5);
    std::string s { "Hello, world!" };
    print(s);

    return 0;
}
```

#### Out parameters:
An **out parameter** is a parameter that is used only for sending output data back to the caller. Out parameters are typically passed by non-const reference or by address, as the function needs to modify the original object in the caller. For example:
```cpp
#include <cmath>    // for std::sin() and std::cos()
#include <iostream>

// sinOut and cosOut are out parameters
void getSinCos(double degrees, double& sinOut, double& cosOut)
{
    // sin() and cos() take radians, not degrees, so we need to convert
    constexpr double pi { 3.14159265358979323846 }; // the value of pi
    double radians = degrees * pi / 180.0;
    sinOut = std::sin(radians);
    cosOut = std::cos(radians);
}

int main()
{
    double sin { 0.0 };
    double cos { 0.0 };

    double degrees{};
    std::cout << "Enter the number of degrees: ";
    std::cin >> degrees;

    // getSinCos will return the sin and cos in variables sin and cos
    getSinCos(degrees, sin, cos);

    std::cout << "The sin is " << sin << '\n';
    std::cout << "The cos is " << cos << '\n';

    return 0;
}
```
This function `getSinCos` takes a degree value as an in parameter and two out parameters (`sinOut` and `cosOut`) , that are passed by non-const reference, and so the function can modify the original variables in the caller. The function assigns new values to `sinOut` and `cosOut`, which are then reflected in the `sin` and `cos` variables in the `main` function.

#### Out parameters have an annatural usage syntax:
Out parameters, while functional, have a few donwsides:
- The caller must instantiate (and initialize) the variables that will be used as out parameters before calling the function, which can lead to more verbose code, and cannot be made const.
- Because the caller must pass in objects, these values cannot be used as temporaries or literals, or easily used in a single expression.

For example, consider the following code:
```cpp
#include <iostream>

int getByValue()
{
    return 5;
}

void getByReference(int& x)
{
    x = 5;
}

int main()
{
    // return by value
    [[maybe_unused]] int x{ getByValue() }; // can use to initialize object
    std::cout << getByValue() << '\n';      // can use temporary return value in expression

    // return by out parameter
    int y{};                // must first allocate an assignable object
    getByReference(y);      // then pass to function to assign the desired value
    std::cout << y << '\n'; // and only then can we use that value

    return 0;
}
```
In here, we have a function `getByValue` that returns an integer by value, and a function `getByReference` that uses an out parameter to return an integer by reference. In the `main` function, we can use the return value of `getByValue` directly in expressions or to initialize objects. However, for `getByReference`, we must first create a variable `y`, pass it to the function, and then use it, which is more verbose. Overall, using out parameters can lead to less natural and more cumbersome syntax compared to return by value.

#### Out-parameters by reference do not make it obvious the arguments will be modified:
When we assigned a function's return value to an object (return by value), it is clear that the object will receive a new value. For example:
```cpp
x = getByValue(); // clearly indicates x will receive a new value
```

However, when using out parameters passed by reference, it is not immediately obvious that the arguments will be modified by the function (and especially which ones will be modified). For example:
```cpp
getSinCos(degrees, sin, cos); // does not clearly indicate that sin and cos will be modified
```

Using **pass by address** instead of pass by reference can in some cases help make out-parameters more obvious, as the caller must use the address-of operator (`&`) to pass the arguments. For example:
```cpp
getSinCos(degrees, &sin, &cos); // more clearly indicates that sin and cos will be modified
```

And here is a complete example comparing pass by value, pass by reference, and pass by address:
```cpp
void foo1(int x);  // pass by value
void foo2(int& x); // pass by reference
void foo3(int* x); // pass by address

int main()
{
    int i{};

    foo1(i);  // can't modify i
    foo2(i);  // can modify i (not obvious)
    foo3(&i); // can modify i

    int *ptr { &i };
    foo3(ptr); // can modify i (not obvious)

    return 0;
}
```
In this example, `foo1` takes an integer by value, `foo2` takes an integer by reference, and `foo3` takes an integer by address. When calling `foo2`, it is not immediately obvious that `i` may be modified, while when calling `foo3`, the use of the address-of operator (`&`) makes it clearer that `i` may be modified.

Anyways, for all these reasons, out parameters are generally discouraged in modern C++ programming, and alternatives are preferred (we will discuss these alternatives later on).

> **Best Practice:** Avoid using out parameters when possible, as they can lead to less natural syntax and make it less obvious which arguments will be modified.

#### In-out parameters:
In rare cases, a parameter may be used both for receiving input data from the caller and for sending output data back to the caller. Such parameters are called **in-out parameters**. In-out parameters work identiacally to out-parameters, and have the same downsides.

#### When to pass by non-const reference:
In general, if you want to pass by reference to avoid making copy of a large object, and the function does not need to modify the original object in the caller, you should almost always **pass by const reference**.

However, there are two primary cases where you should pass by non-const reference:
1. When a parameter is an **in-out parameter**. Since we are already need that object as input, it might be more efficient to pass it by non-const reference, so we can also modify it and send the modified value back to the caller. For example:
    ```cpp
        void someFcn(Foo& inout)
    {
        // modify inout
    }

    int main()
    {
        Foo foo{};
        someFcn(foo); // foo modified after this call, may not be obvious

        return 0;
    }
    ```
    You could also make the function name more descriptive to indicate that the parameter will be modified (e.g., `modifyFoo` instead of `someFcn`), or use comments to indicate that the parameter is an in-out parameter.

    The alternative would be to pass the object by value, and return the modified value by return value, but this would involve making a copy of the object, which may be expensive for large objects (two extra copies: one for the parameter, and one for the return value).

2. When a function would otherwise need to return an object by value to the caller, but this would be extrimely expensive (e.g., returning a large object). In this case, you can pass the object by non-const reference as an out parameter, so the function can modify the original object in the caller instead of returning a copy. For example:
    ```cpp
    void generateExpensiveFoo(Foo& out)
    {
        // modify out
    }

    int main()
    {
        Foo foo{};
        generateExpensiveFoo(foo); // foo modified after this call

        return 0;
    }
    ```

#### Summary:
- In parameters are used for receiving input data from the caller and are typically passed by value or by const reference.
- Out parameters are used for sending output data back to the caller and are typically passed by non-const reference or by address (non-const reference is more common).
- Out parameters can lead to more verbose and less natural syntax, as the caller must instantiate and initialize the variables before calling the function.
- Out parameters passed by reference do not make it obvious which arguments will be modified; using pass by address can help make this clearer.
- In-out parameters are used for both receiving input and sending output data, and work identically to out parameters.
- Pass by non-const reference should be used for in-out parameters or when returning large objects by value would be extremely expensive.


---

### S14 - 12.14 Type deduction with pointers, references, and const
In a previous chapter, we have seen how type deduction works with `auto`, giving the compiler the ability to deduce the type of a variable from its initializer. 
```cpp
int main()
{
    int a { 5 };
    auto b { a }; // b deduced as an int

    return 0;
}
```
We have also noted that by default, type deduction drops `const` (or `constexpr`) qualifiers from the deduced type:
```cpp
int main()
{
    const double a { 7.8 }; // a has type const double
    auto b { a };           // b has type double (const dropped)

    constexpr double c { 7.8 }; // c has type const double (constexpr implicitly applies const)
    auto d { c };               // d has type double (const dropped)

    return 0;
}
```

These qualifiers can be reapplied by adding the `const` qualifier to the `auto` declaration:
```cpp
int main()
{
    double a { 7.8 };    // a has type double
    const auto b { a };  // b has type const double (const applied)

    constexpr double c { 7.8 }; // c has type const double (constexpr implicitly applies const)
    const auto d { c };         // d is const double (const dropped, const reapplied)
    constexpr auto e { c };     // e is constexpr double (const dropped, constexpr reapplied)

    return 0;
}
```

In this section, we will explore how type deduction works with pointers and references, and how `const` qualifiers are handled in these cases.

#### Type deduction drops references:
When using `auto` with references, type deduction also drops the reference qualifier from the deduced type. For example:
```cpp
#include <string>

std::string& getRef(); // some function that returns a reference

int main()
{
    auto ref { getRef() }; // type deduced as std::string (not std::string&)

    return 0;
}
```
In this example, the `getRef` function returns a reference to a `std::string` object. However, when we use `auto` to deduce the type of `ref`, the reference qualifier is dropped, and `ref` is deduced as a `std::string`, not a `std::string&`.

Just like with dropped `const` qualifiers, we can reapply the reference qualifier by adding the `&` to the `auto` declaration:
```cpp
#include <string>

std::string& getRef(); // some function that returns a reference

int main()
{
    auto ref1 { getRef() };  // std::string (reference dropped)
    auto& ref2 { getRef() }; // std::string& (reference dropped, reference reapplied)

    return 0;
}
```
In this way, by using `auto&`, we can ensure that `ref2` is deduced as a reference to a `std::string`.

#### Top-level const and low-level const:
When dealing with pointers and references, it is important to understand the concepts of **top-level const** and **low-level const**.
- **Top-level const** refers to a `const` qualifier that applies to the object itself (the actual variable, or the pointer/reference), rather than the object being pointed to or referenced.
    ```cpp
    const int x;    // this const applies to x, so it is top-level
    int* const ptr; // this const applies to ptr, so it is top-level
    // references don't have a top-level const syntax, as they are implicitly top-level const
    ```
- **Low-level const** refers to a `const` qualifier that applies to the object being pointed to or referenced
    ```cpp
    const int& ref; // this const applies to the object being referenced, so it is low-level
    const int* ptr; // this const applies to the object being pointed to, so it is low-level
    ```

A reference to a const level is always a low-level const, as references are implicitly top-level const. A pointer can have top-level const (the pointer itself is const) or low-level const (the object being pointed to is const), or both:
```cpp
const int* const ptr; // the left const is low-level, the right const is top-level
```


When we say that type deduction drops `const` qualifiers, it only drops **top-level const** qualifiers. **Low-level const** qualifiers are preserved during type deduction. 

> **Note:** type deduction drops only top-level const qualifiers; low-level const qualifiers are preserved.

#### Type deduction and const references:
If the initializer is a reference to a const, the reference is dropped first (and then reapplied if applicable), and then any top-level const is dropped from the deduced type. For example:
```cpp
#include <string>

const std::string& getConstRef(); // some function that returns a reference to const

int main()
{
    auto ref1{ getConstRef() }; // std::string (reference dropped, then top-level const dropped from result)

    return 0;
}
```
In this example, the `getConstRef` function returns a reference to a const `std::string` object. When we use `auto` to deduce the type of `ref1`, the reference qualifier is dropped first, resulting in `const std::string`. Then, the top-level const is dropped, resulting in `std::string`.

This can change a low-level const (`const std::string&`) into a top-level const (`const std::string`), which is then dropped.

We can reappl,y a reference and/or const qualifier as needed:
```cpp
#include <string>

const std::string& getConstRef(); // some function that returns a const reference

int main()
{
    auto ref1{ getConstRef() };        // std::string (reference and top-level const dropped)
    const auto ref2{ getConstRef() };  // const std::string (reference dropped, const dropped, const reapplied)

    auto& ref3{ getConstRef() };       // const std::string& (reference dropped and reapplied, low-level const not dropped)
    const auto& ref4{ getConstRef() }; // const std::string& (reference dropped and reapplied, low-level const not dropped)

    return 0;
}
```
In this example, we demonstrate how to reapply reference and const qualifiers when using `auto`. 
- `ref1` is deduced as `std::string`, as both the reference and top-level const are dropped.
- `ref2` is deduced as `const std::string`, as the reference is dropped, the top-level const is dropped, and then const is reapplied.
- `ref3` is deduced as `const std::string&`, as the reference is not dropped (since we used `auto&`), and the low-level const is preserved (since it is not top-level).
- `ref4` is also deduced as `const std::string&`, as the reference is not dropped (since we used `const auto&`), and the low-level const is preserved (since it is not top-level). We explicitly added const, because it is generally good to explicitly indicate that we want a const reference.

> **Best Practice:** If you want a const reference, reapply `const` qualifier even though low-level const is preserved, to make it explicit.

#### What about `constexpr` references?
`constexpr` is not part of an expression type, so it is not deduced by `auto`.

As a reminder, when we want a const reference (e.g., `const T&`), the `const` qualifier is applied to the object being referenced, making it a low-level const. When defining a `constexpr` reference to a const variable (e.g. `constexpr const T&`), the `constexpr` qualifier applies to the reference itself, while the `const` qualifier applies to the object being referenced.

Here is an example demonstrating type deduction with `constexpr` references:
```cpp
#include <string_view>
#include <iostream>

constexpr std::string_view hello { "Hello" };   // implicitly const

constexpr const std::string_view& getConstRef() // function is constexpr, returns a const std::string_view&
{
    return hello;
}

int main()
{
    auto ref1{ getConstRef() };                  // std::string_view (reference dropped and top-level const dropped)
    constexpr auto ref2{ getConstRef() };        // constexpr const std::string_view (reference dropped and top-level const dropped, constexpr applied, implicitly const)

    auto& ref3{ getConstRef() };                 // const std::string_view& (reference reapplied, low-level const not dropped)
    constexpr const auto& ref4{ getConstRef() }; // constexpr const std::string_view& (reference reapplied, low-level const not dropped, constexpr applied)

    return 0;
}
```
In this example:
- `ref1` is deduced as `std::string_view`, as both the reference and top-level const are dropped.
- `ref2` is deduced as `constexpr const std::string_view`, as the reference is dropped, the top-level const is dropped, and then `constexpr` is applied (with `const` being implicit).
- `ref3` is deduced as `const std::string_view&`, as the reference is not dropped (since we used ``auto&`), and the low-level const is preserved (since it is not top-level).
- `ref4` is deduced as `constexpr const std::string_view&`, as the reference is not dropped (since we used `constexpr const auto&`), the low-level const is preserved (since it is not top-level), and `constexpr` is applied.

#### Type deduction and pointers:
Unlike references, type deduction **does not drop pointers**. When using `auto` with pointers, the pointer qualifier is preserved in the deduced type. For example:
```cpp
#include <string>

std::string* getPtr(); // some function that returns a pointer

int main()
{
    auto ptr1{ getPtr() }; // std::string*

    return 0;
}
```
Here, the `getPtr` function returns a pointer to a `std::string` object. When we use `auto` to deduce the type of `ptr1`, the pointer qualifier is preserved, and `ptr1` is deduced as a `std::string*`.

We can also use an additional `*` in the `auto` declaration to indicate that we want a pointer to a pointer (`auto*`):
```cpp
#include <string>

std::string* getPtr(); // some function that returns a pointer

int main()
{
    auto ptr1{ getPtr() };  // std::string*
    auto* ptr2{ getPtr() }; // std::string*

    return 0;
}
```
to make it more explicit that we are working with pointers.

#### The difference between `auto` and `auto*` (Optional):
When we use `auto` with a pointer type initializer, the deducted type includes the pointer. So for the above example, `ptr1` is deduced as `std::string*`.

When we use `auto*` with a pointer type initializer, the deducted type **does not** include the pointer. Instead, it is reapplied afterward after the type is deducted. So for the above example, `ptr2` is deducted as `std::string`, and then the `*` is reapplied, resulting in `std::string*`.

In most cases, there is no practical difference between using `auto` and `auto*` with pointer type initializers, as both will result in the same deduced type. However, there are few differences:
- `auto*` must resolve to a point initializer, otherwise it will result in a compilation error. For example:
    ```cpp
    #include <string>

    std::string* getPtr(); // some function that returns a pointer

    int main()
    {
        auto ptr3{ *getPtr() };      // std::string (because we dereferenced getPtr())
        auto* ptr4{ *getPtr() };     // does not compile (initializer not a pointer, but the dereferenced value)

        return 0;
    }
    ```
    In `ptr4` case, `auto` deduces to `std::string`, and then the `*` is reapplied, resulting in `std::string*`, which does not match the initializer type (`std::string`), leading to a compilation error.
- There are differences in how `auto` and `auto*` interact with `const` qualifiers, that we will cover below.

#### Type deduction and const pointers (Optional):
Since pointers are not dropped we do not ahve to worry about them. But regarding this, we have two different cases with `const` pointers:
1. When the pointer itself is `const` (top-level const)
2. When the object being pointed to is `const` (low-level const)

Just like with references, type deduction drops only top-level const qualifiers; low-level const qualifiers are preserved. For example:
```cpp
#include <string>

std::string* getPtr(); // some function that returns a pointer

int main()
{
    const auto ptr1{ getPtr() };  // std::string* const
    auto const ptr2 { getPtr() }; // std::string* const

    const auto* ptr3{ getPtr() }; // const std::string*
    auto* const ptr4{ getPtr() }; // std::string* const

    return 0;
}
```
In this example:
- `ptr1` and `ptr2` are deduced as `std::string* const`, as the top-level const is applied to the pointer itself.
- `ptr3` is deduced as `const std::string*`, as the low-level const is preserved, applying to the object being pointed to (pointer to a const `std::string`).
- `ptr4` is deduced as `std::string* const`, as the top-level const is applied to the pointer itself (pointer is const).

This is getting complicated, I will leave this Optional section as optional for now, sorry :)

#### Summary:
Top-level vs low-level const recap:
- A top-level `const` applies to the object itself (the variable, pointer, or reference). For example, `const int x;` and `int* const ptr;` have top-level const.
- A low-level `const` applies to the object being pointed to or referenced. For example, `const int& ref;` and `const int* ptr;` have low-level const. You could see these with parenthesis for clarity `(const int)& ref;` and `(const int)* ptr;`. Easier like that right?

What type deduction deduces:
- Type deduction drops top-level `const` qualifiers; low-level `const` qualifiers are preserved.
- Type deduction first drops any references (unless the deduced type is defined as reference). For const references, droppping reference will cause the low-level const to become top-level const, which is then dropped.
- Type deduction then drops any top-level const (unless the deduced type is defined as `const` or `constexpr`).
- `constexpr` is not part of an expression type, so it is not deduced by `auto`.
- Type deduction does not drop pointers; pointer qualifiers are preserved in the deduced type.
- Always explicitly define the deduced type as a reference, `const`, or `constexpr` as needed to make it clear what you want.

Type deduction and pointers:
- When using `auto`, the deducted type will be a pointer only if the initializer is a pointer. When using `auto*`, the deducted type will be a pointer regardless of the initializer type (the `*` is reapplied after deduction).
- `auto const` and `const auto` both make the deducted pointer a top-level const pointer. There is no way to specify a low-level const pointer using `auto` alone.
- `auto* const` makes the pointer itself a top-level const pointer. Rememebr `int* const` is a const pointer to int.
- `const auto*` makes the object being pointed to a low-level const. Remember `const int*` is a pointer to const int.
- Prefer using `auto*` over `auto` since it allows to apply low-level or top-level const qualifiers as needed, while `auto` only allows to apply top-level const qualifiers.


---

### S15 - 12.15 `std::optional`
In a previous chapter we discussed about cases where a function encounters an error that cannot reasonably handle itself, and so it needs to indicate to the caller that an error occurred. For example:
```cpp
int doIntDivision(int x, int y)
{
    return x / y;
}
```
If the caller passes `0` as the second argument, the function will attempt to divide by zero, leading to undefined behavior.
In thi case, the best option is to detect the error, and then pass the error back to the caller.

Previously, we covered two different ways to have a function return an error back to the caller:
- Have a void returning function return a bool instead, indicating success or failure, and use out parameters to return the actual result.
- Have a value-returning function return a sentinel value (a special value that does not occur in the set of possible valid return values) to indicate an error.

An example of the latter, the `reciprocal` function that returns `0.0` to indicate an error when the input is `0.0`:
```cpp
#include <iostream>

// The reciprocal of x is 1/x, returns 0.0 if x=0
double reciprocal(double x)
{
    if (x == 0.0) // if x is semantically invalid
       return 0.0; // return 0.0 as a sentinel to indicate an error occurred

    return 1.0 / x;
}

void testReciprocal(double d)
{
     double result { reciprocal(d) };
     std::cout << "The reciprocal of " << d << " is ";
     if (result != 0.0)
         std::cout << result << '\n';
     else
         std::cout << "undefined\n";
}

int main()
{
    testReciprocal(5.0);
    testReciprocal(-4.0);
    testReciprocal(0.0);

    return 0;
}
```

While this is a valid approach, it has some downsides:
- The programmer must know which sentinel value the function is using to indicate an error, and must check for that value after every function call.
- Different version of the function may use different sentinel values, leading to confusion and bugs.
- This is not valid when valid return values can include all possible values of the return type.

Consider our `doIntDivision` function. If we wanted to use a sentinel value to indicate an error, what value could we use? Any integer value could be a valid result of the division, so there is no suitable sentinel value.

So what we could do?

First, we could pick a very uncommon value as sentinel, such as `std::numeric_limits<int>::lowest()`:
```cpp
#include <limits> // for std::numeric_limits

// returns std::numeric_limits<int>::lowest() on failure
int doIntDivision(int x, int y)
{
    if (y == 0)
        return std::numeric_limits<int>::lowest();
    return x / y;
}
```
While this could work, it is not ideal because of two main reasons:
- Every time we call this function, we need to check if the return value is equal to `std::numeric_limits<int>::lowest()`, which is verbose and error-prone.
- If the user legitimately wants to divide two integers and get `std::numeric_limits<int>::lowest()` as result (e.g., calling `doIntDivision(std::numeric_limits<int>::lowest(), 1)`), they will get a false positive error.

Second, we could abandon using return values to return errors, and use some other mechanism (e.g., exceptions) to indicate errors. While this is a valid approach, it can be overkill for simple functions, and exceptions have their own downsides (e.g., performance overhead, complexity).

Third, we could abandon returning a single value and return two values instead: one for the result, and one for the error status (of type `bool`). This could be probably the best approach in many cases, but it can lead to more verbose code, and the caller must always check the error status before using the result.

Prior to C==17, this last option required you to implement it by yourself, leading to inconsistencies and errors.

#### returning a `std::optional`:
C++17 introduced the `std::optional` type, which is a wrapper that can either contain a value of a specified type, or no value at all (indicating an error or absence of value). `std::optional<T>` can either have a value of type `T`, or not have a value (be empty).

We can use this to implement the third option above, returning a `std::optional` from our function to indicate success or failure. For example:
```cpp
#include <iostream>
#include <optional> // for std::optional (C++17)

// Our function now optionally returns an int value
std::optional<int> doIntDivision(int x, int y)
{
    if (y == 0)
        return {}; // or return std::nullopt
    return x / y;
}

int main()
{
    std::optional<int> result1 { doIntDivision(20, 5) };
    if (result1) // if the function returned a value
        std::cout << "Result 1: " << *result1 << '\n'; // get the value
    else
        std::cout << "Result 1: failed\n";

    std::optional<int> result2 { doIntDivision(5, 0) };

    if (result2)
        std::cout << "Result 2: " << *result2 << '\n';
    else
        std::cout << "Result 2: failed\n";

    return 0;
}
```
This will output:
```
Result 1: 4
Result 2: failed
```
In this example, the `doIntDivision` function returns a `std::optional<int>`. If the division is successful, it returns the result wrapped in a `std::optional`. If there is an error (division by zero), it returns an empty `std::optional` (indicating failure). The caller can then check if the `std::optional` contains a value using the `if (result)` syntax, and access the value using the dereference operator (`*result`).

Using `std::optional` is quite easy, and we can construct a `std::optional<T>` with or without a value:
```cpp
std::optional<int> o1 { 5 };            // initialize with a value
std::optional<int> o2 {};               // initialize with no value
std::optional<int> o3 { std::nullopt }; // initialize with no value
```

To check if a `std::optional` contains a value, we can use:
- The `has_value()` member function, which returns `true` if the `std::optional` contains a value, and `false` otherwise.
- The boolean conversion operator, which allows us to use the `std::optional` in a boolean context (e.g., in an `if` statement).

For example:
```cpp
if (o1.has_value()) // call has_value() to check if o1 has a value
if (o2)             // use implicit conversion to bool to check if o2 has a value
```

To get the value from a `std::optional`, we can use:
- The dereference operator (`*`), which returns a reference to the contained value.
- The `value()` member function, which returns a reference to the contained value, or throws an exception if the `std::optional` is empty.
- The `value_or(default_value)` member function, which returns the contained value if it exists, or `default_value` if the `std::optional` is empty.

For example:
```cpp
std::cout << *o1;             // dereference to get value stored in o1 (undefined behavior if o1 does not have a value)
std::cout << o2.value();      // call value() to get value stored in o2 (throws std::bad_optional_access exception if o2 does not have a value)
std::cout << o3.value_or(42); // call value_or() to get value stored in o3 (or value `42` if o3 doesn't have a value)
```

Note that `std::optional` has a usage syntax essentially identical to pointers, as we use the dereference operator (`*`) to access the contained value.

| Behavior               | Pointer Syntax   | std::optional Syntax      |
|------------------------|------------------|---------------------------|
| Hold no value          | initialize/assign `{}` or `std::nullptr` | initialize/assign `{}` or `std::nullopt` |
| Hold a value         | initialize/assign an address | initialize/assign a value |
| Check if has value | implicit conversion to bool | | implicit conversion to bool or `has_value()` |
| Get value              | dereference operator (`*ptr`) | dereference operator (`*optional`) or `value()` |
| Get value with default  | N/A              | `value_or(default_value)` |

However, semantically, a popinter and a `std::optional` are quite different:
- A pointer has a reference semantics, meaning it points to an object in memory, and assignment copies the pointer, not the object it points to. If we return a pointer by address, the pointer is copied back to the caller, not the object it points to. This means we cannot return local objects by pointer, as they will go out of scope when the function returns.
- A `std::optional` has a value semantics, meaning it actually contains its value (if it has one), and assignment copies the value. If we return a `std::optional` by value, the contained object is copied back to the caller (if it exists). This means we can return local objects by `std::optional`, as the object will be copied back to the caller.

With this in mind, let us look at how our example works under the hood. Our `doIntDivision` function returns a `std::optional<int>` by value, instead of an `int`. Inside its function body, if there is no error, it returns an `int` value (which is used to construct a `std::optional<int>` containing that value). If there is an error, it returns an empty `std::optional<int>`.

In the caller `main()`, we use an implicit conversion to bool to check if our returned `std::optional<int>` contains a value. If it does, we use the dereference operator (`*`) to get the contained value and print it. If it does not contain a value, we print an error message.

#### Pros and cons of returning a `std::optional`:
Using `std::optional` to return values that may fail has several advantages:
- using `std::optional` documents that a function may return a value or may fail (no value).
- We do not have to remember which sentinel value to check for, as we can simply check if the `std::optional` contains a value.
- The syntax is convenient and easy to use, similar to pointers.
- We can return local objects by `std::optional`, as the object will be copied back to the caller.

However, there are also some downsides:
- We have to check if the returned `std::optional` contains a value before using it, which can lead to more verbose code. If we dereference an empyy `std::optional`, it leads to undefined behavior (or an exception if using `value()`).
- This approach doesn't give a way to pass back information about the specific error that occurred. If we need to provide more detailed error information, we may need to use other mechanisms (e.g., exceptions, error codes, or custom error types).

> **Best Practice:** Return a `std::optional` (instead of a sentinel value) for functions that may fail, unless your function needs to return additional information about why it failed.

#### Using `std::optional` as an optional function parameter:
In [S11 - 12.11 Pass by address (part 2)](#s11---1211-pass-by-address-part-2), we discussed how pass by address can be used to allow a function to accept an "optional" argument, by allowing the caller to pass a `nullptr` to indicate that they do not want to provide that argument, or a valid address to provide the argument. However, one downside of this approach is that a non-`nullptr` must be an lvalue, so that its address can be taken.

An alternative approach is to use `std::optional` as the function parameter type (in-parameter only). This allows the caller to either provide a value (by passing a `std::optional` containing a value), or indicate that they do not want to provide a value (by passing an empty `std::optional`). For example, instead of this:
```cpp
#include <iostream>

void printIDNumber(const int *id=nullptr)
{
    if (id)
        std::cout << "Your ID number is " << *id << ".\n";
    else
        std::cout << "Your ID number is not known.\n";
}

int main()
{
    printIDNumber(); // we don't know the user's ID yet

    int userid { 34 };
    printIDNumber(&userid); // we know the user's ID now

    return 0;
}
```
We could do this:
```cpp
#include <iostream>
#include <optional>

void printIDNumber(std::optional<const int> id = std::nullopt)
{
    if (id)
        std::cout << "Your ID number is " << *id << ".\n";
    else
        std::cout << "Your ID number is not known.\n";
}

int main()
{
    printIDNumber(); // we don't know the user's ID yet

    int userid { 34 };
    printIDNumber(userid); // we know the user's ID now

    printIDNumber(62); // we can also pass an rvalue

    return 0;
}
```

There are two main advantages of using `std::optional` as function parameters:
1. It explicitely document that the parameter is optional, making the code more readable.
2. We can pass in an rvalue directly, without needing to create a named variable first, since `std::optional` will make a copy of the rvalue internally.

However, since it makes a copy of its argument, this becomes problematic when `T` is an expensive-to-copy type (like `std::string` or a large struct/class). In such cases, passing by `std::optional<T>` may lead to unnecessary copies, which can impact performance.

So we suggest using `std::optional<T>` an an optional parameter when `T` is a small and cheap-to-copy type (like built-in types, small structs, or small classes). For expensive-to-copy types, consider using pass by address instead (e.g., `const T*`).

> **Best Practice 1:** Use `std::optional<T>` as an optional function parameter when `T` is a small and cheap-to-copy type. For expensive-to-copy types, consider using pass by address instead.

#### Summary:
- `std::optional<T>` is a wrapper that can either contain a value of type `T`, or no value at all (indicating an error or absence of value).
- We can use `std::optional` to return values from functions that may fail, allowing the caller to check if the function succeeded or failed.
- Using `std::optional` documents that a function may return a value or may fail, and provides a convenient syntax for checking and accessing the returned value.
- However, we must remember to check if the `std::optional` contains a value before using it, which can lead to more verbose code.
- `std::optional` has value semantics, meaning it actually contains its value (if it has one), and assignment copies the value.
- We can also use `std::optional` as an optional function parameter, allowing the caller to either provide a value or indicate that they do not want to provide a value.


---

### SX - 12.x Summary and quiz
### S11 — Summary and quiz
Try to answer the questions and the quizzes, and then check the solutions in the `exercises` folder.

Enjoy and have fun! :)


---

## 🧾 Summary
Functions communicate with their callers through parameters and return values.  
**References** act as aliases to existing objects; **pointers** store addresses and must be checked for validity. Returning by reference avoids copies but requires that the referenced object outlive the function. Returning by address is similar but allows signaling “no object” via `nullptr`.

Parameters can be **in**, **out**, or **in-out**, but out parameters often lead to unclear and verbose code. Modern C++ favors **returning values** (possibly wrapped in `std::optional`) or using **const references** for read-only inputs.

`auto` simplifies variable declarations, but drops references and top-level const, requiring the programmer to reapply them via `auto&`, `const auto`, or `const auto&`. Pointers are preserved, and constness must be managed carefully.

`std::optional` provides a safe, expressive way to return a value that may not exist — avoiding sentinel values and making intent explicit. It has value semantics, unlike pointers, and can also be used to represent optional parameters.

## 🧱 Core Concepts You Mastered

- **Lvalues, rvalues, and references**  
  - What references bind to and how binding affects lifetime  
  - The danger of dangling references and dangling pointers  
- **Return strategies**  
  - Return by value (safe, may copy)  
  - Return by reference (zero-copy but must outlive function)  
  - Return by address (nullable, must check for `nullptr`)  
- **Parameter semantics**  
  - In, out, and in-out parameters  
  - Why out parameters lead to unclear APIs  
  - Why const references are preferred for read-only large objects  
- **Type deduction with `auto`**  
  - Reference dropping  
  - Top-level vs low-level const  
  - `auto`, `auto&`, `const auto&`, `auto*`  
- **Pointers**  
  - Wild, null, and dangling pointers  
  - Pointers to const vs const pointers  
- **Optional values**  
  - Using `std::optional<T>` to represent “maybe a value”  
  - Checking presence (`has_value()`, `if(optional)`)  
  - Extracting values (`*opt`, `opt.value()`, `opt.value_or(default)`)  
  - Using optional as a function parameter  
