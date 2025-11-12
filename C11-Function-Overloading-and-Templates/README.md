# Chapter 11 - Function Overloading and Function Templates

## 🧭 Overview
This chapter explores how C++ allows you to create multiple versions of functions with the same name (via **function overloading**) and generic versions of functions that can operate on multiple types (via **function templates**).  
These features make your programs more flexible, reusable, and expressive, letting you write concise and type‑safe code without duplicating logic.

You’ll learn how overload resolution works, how ambiguity arises, and how to design clean overloads. You’ll also master **templates**, understanding how the compiler generates functions on demand and how **non‑type template parameters** and **abbreviated function templates** (C++20) make code both powerful and readable.

> **Key idea:** Overloading and templates are two of C++’s most powerful abstractions — the first works at *compile time by choosing between existing implementations*, while the second *generates* implementations from blueprints.

---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch11_first
./build/ch11_first
```

---

## 🎯 Learning Outcomes

By the end of this chapter, you’ll be able to:

- 🧩 Define and use **function overloads** safely and effectively.  
- ⚖️ Explain **overload resolution** and handle **ambiguous matches**.  
- 🔒 Use the `= delete` specifier to prevent unwanted overloads.  
- ⚙️ Provide **default arguments** and understand how they interact with overloading.  
- 🧠 Create **function templates** that generalize algorithms over multiple types.  
- 🧮 Understand **template instantiation**, **type deduction**, and **specialization**.  
- 🧰 Combine **type** and **non‑type template parameters** to express compile‑time logic.  
- 🚀 Write concise, modern code using **abbreviated function templates (C++20)**.  
- 🧾 Properly organize templates across **multiple translation units** without linker errors.


---

## Sections

### S01 — 2.1 Introduction to function overloading
Consider the following function:
```cpp
int add( int x, int y ) {
    return x + y;
}
```
This function adds two integers and returns the result. But what if we want to add two floating-point numbers instead? If we simply pass these two numbers to the `add` function, this will convert them to integers, resulting in a loss of precision, and not the expected behavior that we are looking for.

One way to work around this is to define multiple functions:
```cpp
int addInteger( int x, int y ) {
    return x + y;
}

double addDouble( double x, double y ) {
    return x + y;
}
```
However, this approach can quickly become cumbersome and error-prone, especially as the number of types we want to support increases.

#### Introduction to function overloading:
Fortunately, C++ has an elegant solution to this problem: **function overloading**. Function overloading allows us to define multiple functions with the same name but different parameter types. The compiler determines which function to call based on the types of the arguments passed to it.

Every function sharing the same name (in the same scope) is considered an overload of that function. The compiler uses a process called **overload resolution** to determine which function to invoke based on the arguments provided.

To overload our `add()` function, we can define multiple versions of it in the same scope:
```cpp
int add(int x, int y) // integer version
{
    return x + y;
}

double add(double x, double y) // floating point version
{
    return x + y;
}

int main()
{
    return 0;
}
```

#### Introdution to overload resolution:
When a function is called, the compiler performs **overload resolution** to determine which version of the function to invoke. In our example, when we call the `add()` function with different argument types, the compiler selects the appropriate overload:
```cpp
int main()
{
    int intResult = add(2, 3);           // Calls the integer version
    double doubleResult = add(2.5, 3.5); // Calls the floating-point version
    return 0;
}
```
In this case, the compiler selects the correct `add()` function based on the types of the arguments provided.

#### making it compile:
In order for a program using overloaded functions to compile successfully, the following conditions must be met:
1. **Unique Signatures**: Each overloaded function must have a unique signature, which includes the function name and the types and number of its parameters. The return type is not considered part of the signature. We can also say that each function has to be **differentiated** from the others.
2. **No Ambiguity in Calling**: When calling an overloaded function, the compiler must be able to unambiguously determine which version to invoke based on the provided arguments. If there is ambiguity, the compiler will generate an error.

> **Best Practice**: Use function overloading to make your code more readable and maintainable. However, avoid excessive overloading, as it can lead to confusion and make the code harder to understand.

#### Summary:
- Function overloading allows multiple functions with the same name but different parameter types.
- The compiler uses overload resolution to determine which function to call based on argument types.


---

### S02 — 2.2 Function overload differentiation
In this section we will take a closer look at how function overloads can be differentiated, avoiding compilation errors.

#### How overloaded functions are differentiated:
Overloaded functions are differentiated based on their **signatures**, which include the function name, the types and number of their parameters. The return type is not considered part of the signature.

| Function Property | Used for Differentiation? | Notes                          |
|-------------------|---------------------------|--------------------------------|
| Function Name     | Yes                       | |
| Number of Parameters | Yes                       | |
| Parameter Types   | Yes                       | Excludes typedefs, type aliases, and const qualifier on value parameters. Includes ellipses.  |
| Return Type       | No                        | |

#### Overloading based on number of parameters:
One way to differentiate overloaded functions is by varying the number of parameters they accept. For example:
```cpp
int add(int x, int y) {
    return x + y;
}

int add(int x, int y, int z) {
    return x + y + z;
}
```
In this case, we have two `add()` functions: one that takes two parameters and another that takes three parameters. The compiler can differentiate between them based on the number of arguments provided during the function call. For example:
```cpp
int result1 = add(2, 3);       // Calls the first overload
int result2 = add(2, 3, 4);    // Calls the second overload
```

#### Overloading based on parameter types:
Another way to differentiate overloaded functions is by varying the types of their parameters. For example:
```cpp
int add(int x, int y); // integer version
double add(double x, double y); // floating point version
double add(int x, double y); // mixed version
double add(double x, int y); // mixed version
```
In this case, we have four `add()` functions, each with different parameter types. The compiler can differentiate between them based on the types of arguments provided during the function call. For example:
```cpp
int intResult = add(2, 3);           // Calls the integer version
double doubleResult = add(2.5, 3.5); // Calls the floating-point version
double mixedResult1 = add(2, 3.5);   // Calls the mixed version
double mixedResult2 = add(2.5, 3);   // Calls the mixed version
```

Because type aliases (or typedefs) are not distinct types, the following will cause a compilation error:
```cpp
typedef int Height; // typedef
using Age = int; // type alias

void print(int value);
void print(Age value); // not differentiated from print(int)
void print(Height value); // not differentiated from print(int)
```

For parameters passed by value, the const qualifier is also not considered for differentiation:
```cpp
void print(int);
void print(const int); // not differentiated from print(int)
```

#### The return type of a function is not considered for differentiation:
The return type of a function is not considered part of its signature for the purpose of function overloading. This means that you cannot overload functions solely based on their return types. For example, the following code will result in a compilation error:
```cpp
int getValue();
double getValue(); // Error: not differentiated from getValue()
```

The best way to address this situation is to use different function names:
```cpp
int getIntValue();
double getDoubleValue();
```

#### Type signature:
A function's **type signature** (generally referred to as just **signature**) is defined as the parts of the function header that are used for *differentiation* of the function in C++. In C++, this includes the function name, number of parameters, parameter types, and function-level qualifiers (e.g., `const` for member functions). The return type is not part of the signature.

#### Summary:
- Overloaded functions are differentiated based on their signatures, which include the function name, number of parameters, parameter types, and function-level qualifiers.
- The return type is not considered part of the signature.
- Overloading can be achieved by varying the number of parameters or their types.


---

### S03 — 2.3 Function overload resolution and ambiguous matches
In the previous section we discussed how overloaded functions are differentiated based on their signatures. In this section, we will explore how the compiler resolves which overloaded function to call when a function is invoked, and how to handle ambiguous matches.

The process of determining which overloaded function to invoke is called **overload resolution**. When a function is called, the compiler examines the arguments provided and compares them to the signatures of all available overloaded functions with the same name. The goal is to find the best match for the provided arguments.

This example is straightforward:
```cpp
#include <iostream>

void print(int x)
{
     std::cout << x << '\n';
}

void print(double d)
{
     std::cout << d << '\n';
}

int main()
{
     print(5); // 5 is an int, so this matches print(int)
     print(6.7); // 6.7 is a double, so this matches print(double)

     return 0;
}
```
But not always the best match is so obvious. For example, what happens when the argument type does not exactly match any of the overloaded function signatures ? For example:
```cpp
#include <iostream>

void print(int x)
{
     std::cout << x << '\n';
}

void print(double d)
{
     std::cout << d << '\n';
}

int main()
{
     print('a'); // char does not match int or double, so what happens?
     print(5L); // long does not match int or double, so what happens?

     return 0;
}
```
In this case, the compiler will attempt to find the best match for the provided arguments by considering possible type conversions. The compiler will follow a set of rules to determine the best match. In this example, `char` can generally be converted to `int` more easily than to `double`, so the compiler will choose the `print(int)` overload for the `char` argument. Similarly, `long` can be converted to `double` more easily than to `int`, so the compiler will choose the `print(double)` overload for the `long` argument.

#### Resolving overloaded function calls:
When resolving overloaded function calls, the compiler follows these general steps:
1. **Exact Match**: The compiler first looks for an exact match between the argument types and the parameter types of the overloaded functions.
2. **Promotion**: If no exact match is found, the compiler considers type promotions (e.g., `char` to `int`, `float` to `double`).
3. **Standard Numeric Conversions**: If no match is found through promotions, the compiler considers standard conversions (e.g., `int` to `double`, `float` to `int`).
4. **User-Defined Conversions**: If no match is found through standard conversions, the compiler considers user-defined conversions (e.g., conversion operators, constructors).
5. **Ellipses**: If no match is found through user-defined conversions, the compiler considers ellipses (`...`). Ellipses can match any type, but they are considered the least preferred option.

At the end of this process of type conversions, there will be one of these three possible outcomes:
1. **No matching function found**: If no overloaded function matches the provided arguments, the compiler generates an error indicating that no suitable function was found.
2. **Single best match found**: If one overloaded function is determined to be the best match for the provided arguments, the compiler invokes that function.
3. **Ambiguous match**: If multiple overloaded functions are equally good matches for the provided arguments, the compiler generates an error indicating that the call is ambiguous.

#### The argument matching sequence:
- **Step 1 - Exact Match**: The compiler first looks for an exact match between the argument types and the parameter types of the overloaded functions. For example:
    ```cpp
    void foo(int)
    {
    }

    void foo(double)
    {
    }

    int main()
    {
        foo(0);   // exact match with foo(int)
        foo(3.4); // exact match with foo(double)

        return 0;
    }
    ```
    In this case, the compiler finds exact matches for both function calls, since `0` is an `int` and `3.4` is a `double`.

    Then, the compiler will try to apply a number of **trivial conversions** to find a match. These include:
    - Lvalue to rvalue conversion
    - Qualification conversions (e.g., non-const to const)
    - non-reference to reference conversions
    
    For example:
    ```cpp
    void foo(const int)
    {
    }

    void foo(const double&) // double& is a reference to a double
    {
    }

    int main()
    {
        int x { 1 };
        foo(x); // x trivially converted from int to const int

        double d { 2.3 };
        foo(d); // d trivially converted from double to const double& (non-ref to ref conversion)

        return 0;
    }
    ```
    In this example, the compiler applies trivial conversions to find matches for both function calls. Matches with trivial conversions are considered exact matches, and so non ambiguous.

- **Step 2 - Promotion**: If no exact match is found, the compiler considers type promotions. Promotions are a subset of standard conversions that convert smaller types to larger types without loss of information. If, after promotion, a match is found, the function call is resolved. For example:
    ```cpp
    void foo(int)
    {
    }

    void foo(double)
    {
    }

    int main()
    {
        foo('a');  // promoted to match foo(int)
        foo(true); // promoted to match foo(int)
        foo(4.5f); // promoted to match foo(double)

        return 0;
    }
    ```
    In this case, the compiler promotes `char` and `bool` to `int`, and `float` to `double`, allowing it to find matches for all function calls.

- **Step 3 - Standard Conversions**: If no match is found through promotions, the compiler considers standard numeric conversions. These include a wider range of type conversions, such as converting between numeric types (e.g., `int` to `double`, `double` to `int`), pointer conversions, and user-defined conversions. If, after applying standard conversions, a match is found, the function call is resolved. For example:
    ```cpp
    #include <string> // for std::string

    void foo(double)
    {
    }

    void foo(std::string)
    {
    }

    int main()
    {
        foo('a'); // 'a' converted to match foo(double)

        return 0;
    }
    ```
    In this example, the compiler converts `char` to `double`, allowing it to find a match for the function call.

- **Step 4 - User-Defined Conversions**: If no match is found through standard conversions, the compiler considers user-defined conversions. These are conversions defined by the programmer, such as conversion operators and constructors. If you do not understand this concept yet, don't worry, we will cover it in detail in a later chapter. For now, just know that user-defined conversions are considered last in the overload resolution process. For example:
    ```cpp
    class MyClass
    {
    public:
        // Conversion operator to int
        operator int() { return 42; }
    };

    void foo(int)
    {
    }

    void foo(double)
    {
    }

    int main()
    {
        MyClass obj;
        foo(obj); // user-defined conversion to match foo(int)

        return 0;
    }
    ```
    In this case, the compiler uses the user-defined conversion operator to convert `MyClass` to `int`, allowing it to find a match for the function call. After the user-defined conversion, the compiler could additionally other conversion (e.g., promotion, standard conversion) to find a match.

- **Step 5 - Ellipses**: If no match is found through user-defined conversions, the compiler considers ellipses (`...`). Ellipses can match any type, but they are considered the least preferred option. If a match is found using ellipses, the function call is resolved. For example:
    ```cpp
    #include <iostream>

    void foo(int)
    {
        std::cout << "foo(int) called\n";
    }

    void foo(...) // ellipses
    {
        std::cout << "foo(...) called\n";
    }

    int main()
    {
        foo(3.14); // matches foo(...) since no other match is found

        return 0;
    }
    ```
    In this example, the compiler uses the ellipses overload to match the `double` argument, since no other match is found.

- **Step 6 - No Match Found**: If no matching function is found after considering all the above steps, the compiler generates an error indicating that no suitable function was found for the provided arguments.

#### Ambiguous matches:
An **ambiguous match** occurs when two or more functions are equally good matches for the provided arguments, and the compiler cannot determine which one to invoke. But how is it possible, since each overloaded function must be differentiated based on its signature? Here an example:
```cpp
void foo(int)
{
}

void foo(double)
{
}

int main()
{
    foo(5L); // 5L is type long

    return 0;
}
```
Since literal `5L` is of type `long`, the compiler will first look to see if it can find an exact match for `foo(long)`. Since no exact match is found, the compiler will then consider promotions. However, `long` cannot be promoted, so there is no match either. Next, the compiler will consider standard conversions. In this case, `long` can be converted to both `int` and `double`. Since both conversions are equally good matches, the compiler cannot determine which function to invoke, resulting in an ambiguous match error, and it will give something like this:
```
error C2668: 'foo': ambiguous call to overloaded function
message : could be 'void foo(double)'
message : or       'void foo(int)'
message : while trying to match the argument list '(long)'
```

Here is another example:
```cpp
void foo(unsigned int)
{
}

void foo(float)
{
}

int main()
{
    foo(0);       // int can be numerically converted to unsigned int or to float
    foo(3.14159); // double can be numerically converted to unsigned int or to float

    return 0;
}
```
In this case, the compiler will find two equally good matches for both function calls, resulting in ambiguous match errors, even though you might expect that `0` would match `unsigned int` and `3.14159` would match `float`.

#### Resolving ambiguous matches:
Because ambiguous matches are a compile-time error, an ambiguous match needs to be disambiguated before your program will compile. There are a few ways to resolve ambiguous matches:
1. **Exact Function Definition**: Define an overloaded function that exactly matches the argument types being passed. This removes ambiguity by providing a clear match, without any conversions needed and ambiguity.
2. **Type Casting**: Use explicit type casting to convert the argument to the desired type before passing it to the function. This guides the compiler to select the correct overload. For example:
    ```cpp
    int x { 0 };
    food(static_cast<unsigned int>(x)); // explicitly cast to unsigned int
    double d { 3.14159 };
    foo(static_cast<float>(d)); // explicitly cast to float
    ```
3. **Literal Suffixes**: If your arguemnt is a literal, you can use literal suffixes to specify the desired type. For example:
    ```cpp
    foo(0u);      // 'u' suffix makes it unsigned int
    foo(3.14159f); // 'f' suffix makes it float
    ```

#### Matching for functions with multiple arguemnts:
If there are multiple arguemnts, the compiler applies the matching rules to each argument in sequence. The overall match quality is determined by the combination of matches for all arguments. If one function provides a better match for all arguments compared to another function (at least one argument must be a better match), then that function is selected. If no single function is the best match for all arguments, an ambiguous match error occurs.

For example:
```cpp
#include <iostream>

void print(char, int)
{
	std::cout << 'a' << '\n';
}

void print(char, double)
{
	std::cout << 'b' << '\n';
}

void print(char, float)
{
	std::cout << 'c' << '\n';
}

int main()
{
	print('x', 'a');

	return 0;
}
```
In this case, the compiler will evaluate the matches for both arguments:
1. For the first argument (`char`), all three overloads provide an exact match.
2. For the second argument (`char`), the first overload requires a promotion to `int`, the second overload requires a standard conversion to `double`, and the third overload requires a standard conversion to `float`.
Since promotion is preferred over standard conversions, the compiler selects the first overload (`print(char, int)`), resulting in the output `a`.

#### Summary:
- Overload resolution is the process of determining which overloaded function to invoke based on the provided arguments.
- The compiler follows a sequence of steps: exact match, promotion, standard conversions, user-defined conversions, and ellipses.
- An ambiguous match occurs when multiple functions are equally good matches for the provided arguments.
- Ambiguous matches can be resolved by defining an exact function, using type casting, or using literal suffixes.
- When multiple arguments are involved, the compiler evaluates matches for each argument in sequence to determine the overall best match.


---

### S04 — 2.4 Deleting functions
In some cases, it is possible to write functions that do not behave as desired when called with certain argument types, for example:
```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}

int main()
{
    printInt(5);    // okay: prints 5
    printInt('a');  // prints 97 -- does this make sense?
    printInt(true); // print 1 -- does this make sense?

    return 0;
}
```
prints:
```
5
97
1
```
In this case, calling `printInt()` with a `char` or `bool` argument results in implicit conversions to `int`, which may not be the intended behavior.

To prevent such unintended calls, C++ allows you to **delete** specific function overloads. By marking a function as deleted, you inform the compiler that this function should not be used, and any attempt to call it will result in a compilation error.

#### Deleting a function using the `= delete` specifier:
In cases where we have. afunction that we explicitely do not want to be called with certain argument types, we can declare that function and mark it as deleted using the `= delete` specifier. If the compiler matches a function call to a deleted function, it will generate a compilation error. For example:
```cpp
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}

void printInt(char) = delete; // deleted overload for char
void printInt(bool) = delete; // deleted overload for bool

int main()
{
    printInt(5);    // okay: prints 5
    printInt('a');  // error: call to deleted function
    printInt(true); // error: call to deleted function

    return 0;
}
```
In this example, we have defined two deleted overloads of the `printInt()` function: one for `char` and one for `bool`. Any attempt to call `printInt()` with these argument types will result in a compilation error, effectively preventing unintended calls.

#### Delete all non-matching overloads (Advanced):
In some cases, you may want to delete all overloads of a function that do not match a specific set of argument types. Using the previous method, you would need to explicitly delete each unwanted overload, which can be tedious and error-prone. Instead, you can use a function template (we will see this later) as follows:
```cpp
#include <iostream>

// This function will take precedence for arguments of type int
void printInt(int x)
{
    std::cout << x << '\n';
}

// This function template will take precedence for arguments of other types
// Since this function template is deleted, calls to it will halt compilation
template <typename T>
void printInt(T x) = delete;

int main()
{
    printInt(97);   // okay
    printInt('a');  // compile error
    printInt(true); // compile error

    return 0;
}
```
In this example, we define a function template `printInt(T x)` that is deleted. This template will match any argument type that is not explicitly handled by the non-template overload `printInt(int x)`. As a result, any attempt to call `printInt()` with argument types other than `int` will result in a compilation error.

#### Summary:
- Functions can be deleted using the `= delete` specifier to prevent unintended calls.
- Deleted functions generate compilation errors when called.
- Function templates can be used to delete all non-matching overloads efficiently.


---

### S05 — 2.5 Default arguments
A **default argument** is a default value provided for a function parameter. For example:
```cpp
void print(int x, int y=10) // 10 is the default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
```
In this case, the parameter `y` has a default argument of `10`. This means that if the caller does not provide a value for `y`, the function will use the default value of `10`.

Consider this example:
```cpp
#include <iostream>

void print(int x, int y=4) // 4 is the default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}

int main()
{
    print(1, 2); // y will use user-supplied argument 2
    print(3); // y will use default argument 4, as if we had called print(3, 4)

    return 0;
}
```
prints:
```
x: 1
y: 2
x: 3
y: 4
```
In the first call to `print()`, both arguments are provided by the caller, so the function uses the user-supplied value of `2` for `y`. In the second call, only one argument is provided, so the function uses the default value of `4` for `y`.

Note that you must provide `=` signs to specify default arguments, using parenthesis or brace initialization will not work. 
```cpp
void foo(int x = 5);   // ok
void goo(int x ( 5 )); // compile error
void boo(int x { 5 }); // compile error
```

#### When to use default arguments:
Default arguments are useful when a default reasonable value exists for a function parameter (used when the caller does not provide a value), but you also want to allow the caller to specify a different value if needed. They can help simplify function calls and improve code readability by reducing the number of arguments that need to be explicitly provided. For example:
```cpp
int rollDie(int sides=6);
void openLogFile(std::string filename="default.log");
```

Default arguemnts are also useful for maintaining backward compatibility when modifying existing functions. By adding default arguments to new parameters, you can extend the functionality of a function without breaking existing code that relies on the original function signature.

#### Multiple default arguments:
A function can have multiple default arguments. When calling such a function, the caller can provide values for any number of arguments, starting from the leftmost parameter. If the caller omits values for some parameters, the function will use the default values for those parameters. For example:
```cpp
#include <iostream>

void print(int x=10, int y=20, int z=30)
{
    std::cout << "Values: " << x << " " << y << " " << z << '\n';
}

int main()
{
    print(1, 2, 3); // all explicit arguments
    print(1, 2); // rightmost argument defaulted
    print(1); // two rightmost arguments defaulted
    print(); // all arguments defaulted

    return 0;
}
```
prints:
```
Values: 1 2 3
Values: 1 2 30
Values: 1 20 30
Values: 10 20 30
```
If you provide only part of the arguments, the compiler will use the default values for the omitted arguments, starting from the rightmost parameter.

C++ does not (as of C++23) support function call syntax such as `print(,,3);` to skip specific arguments and use default values for others. You must provide arguments in order, starting from the leftmost parameter. this has three main consequences:
- A function call, any explicitly provided arugments must be leftmost arguments. For example:
    ```cpp
    void print(std::string_view sv="Hello", double d=10.0);

    int main()
    {
        print();           // okay: both arguments defaulted
        print("Macaroni"); // okay: d defaults to 10.0
        print(20.0);       // error: does not match above function (cannot skip argument for sv)

        return 0;
    }
    ```
- If a poarameter is given a default arguemnt, all subsequent parameters must also have default arguments. For example:
    ```cpp
    void foo(int x=10, double d); // compile error: d must have a default argument

    void goo(int x, double d=3.14); // okay

    int main()
    {
        return 0;
    }
    ```
- If more than one parameter has a default argument, the leftmost parameter should be the one most likely to be explicitly provided by the caller. This improves code readability and usability.

#### Default arguments can not be redeclared, and must be declared before use:
Once declared, a default argument cannot be redeclared in the same translation unit. This means that for a function with a forward declaration and a function definition, the default default argument can be declared in either the forward declaration or the function definition, but not both. For example:
```cpp
#include <iostream>

void print(int x, int y=4); // forward declaration

void print(int x, int y=4) // compile error: redefinition of default argument
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
```

Additionally, the default argument must be declared before the function is called. If a function is called before its default argument is declared, the compiler will generate an error. For example:
```cpp
#include <iostream>

void print(int x, int y); // forward declaration, no default argument

int main()
{
    print(3); // compile error: default argument for y hasn't been defined yet

    return 0;
}

void print(int x, int y=4)
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}
```

> **Best Practice**: If a function has a forward declaration, it is recommended to declare default arguments in the forward declaration, and not in the function definition, as the forward declaration is more likely to be seen by other files and included before use.

For example:

foo.h:
```cpp
#ifndef FOO_H
#define FOO_H
void print(int x, int y=4);
#endif
```
main.cpp:
```cpp
#include "foo.h"
#include <iostream>

void print(int x, int y)
{
    std::cout << "x: " << x << '\n';
    std::cout << "y: " << y << '\n';
}

int main()
{
    print(5);

    return 0;
}
```

#### Default arguments and function overloading:
Functions with default arguemnts may be overloaded. For example:
```cpp
#include <iostream>
#include <string_view>

void print(std::string_view s)
{
    std::cout << s << '\n';
}

void print(char c = ' ')
{
    std::cout << c << '\n';
}

int main()
{
    print("Hello, world"); // resolves to print(std::string_view)
    print('a');            // resolves to print(char)
    print();               // resolves to print(char)

    return 0;
}
```
prints:
```
Hello, world
a
    
```
In this example, the function call to `print()` actually calls `print(char)` with the default argument of a space character.

Now consider this example:
```cpp
void print(int x);                  // signature print(int)
void print(int x, int y = 10);      // signature print(int, int)
void print(int x, double y = 20.5); // signature print(int, double)
```
Since default values are not part of a function's signature, the second and third `print()` functions have different signatures (`print(int, int)` and `print(int, double)` respectively). Therefore, they can coexist as overloads. However, calling `print(5)` would result in an ambiguous match error, since both `print(int, int)` and `print(int, double)` could be called with a single `int` argument, using their respective default values for the second parameter.

#### Default arguments can lead to ambiguous matches:
Default arguments can easily lead to ambiguous function calls:
```cpp
void foo(int x = 0)
{
}

void foo(double d = 0.0)
{
}

int main()
{
    foo(); // ambiguous function call

    return 0;
}
```
In this case, the call to `foo()` is ambiguous because both overloads can be called without any arguments, using their respective default values. The compiler cannot determine which overload to invoke, resulting in a compilation error.

Here is a slightly more complex example:
```cpp
void print(int x);                  // signature print(int)
void print(int x, int y = 10);      // signature print(int, int)
void print(int x, double y = 20.5); // signature print(int, double)

int main()
{
    print(1, 2);   // will resolve to print(int, int)
    print(1, 2.5); // will resolve to print(int, double)
    print(1);      // ambiguous function call

    return 0;
}
```
In this case, the call to `print(1)` is ambiguous because the compiler cannot determine whether to invoke `print(int)`, `print(int, int)` with the default value for `y`, or `print(int, double)` with the default value for `y`. This results in a compilation error.

#### Default arguments don’t work for functions called through function pointers (Advanced):
When calling functions through function pointers, default arguments are not considered. This is because the function pointer type does not carry information about default arguments. For example:
```cpp
#include <iostream>

void print(int x, int y = 10)
{
    std::cout << "x: " << x << ", y: " << y << '\n';
}

int main()
{
    void (*funcPtr)(int, int) = print; // function pointer without default argument info

    funcPtr(5); // compile error: no matching function for call to 'print(int)'

    return 0;
}
```
In this example, the function pointer `funcPtr` is of type `void (*)(int, int)`, which does not include information about the default argument for `y`. Therefore, when calling `funcPtr(5)`, the compiler generates an error because it cannot find a matching function that takes a single `int` argument. If you cannot understand this concept yet, don't worry, we will cover function pointers in detail in a later chapter. For now, just know that default arguments are not considered when calling functions through function pointers.

#### Summary:
- Default arguments allow function parameters to have default values if the caller does not provide them.
- Default arguments must be declared before use and cannot be redeclared.
- Functions with default arguments can be overloaded, but care must be taken to avoid ambiguous matches.


---

### S06 — 2.6 Function templates
Function templates are a powerful feature in C++ that allow you to create functions that can operate on different data types without having to write separate functions for each type. A function template is a blueprint for creating functions based on the types provided when the function is called.

For example, let's say you want to calculate the maximum of two numbers:
```cpp
int max(int x, int y)
{
    return (x < y) ? y : x;
    // Note: we use < instead of > because std::max uses <
}
```
This function works well for `int` types (or types that can be promoted to `int`), but what if you want to work with ohter types, such as `double` or `float`? You would need to write an overloaded version of the `max()` function for each type:
```cpp
double max(double x, double y)
{
    return (x < y) ? y : x;
}
float max(float x, float y)
{
    return (x < y) ? y : x;
}
```
This can quickly become tedious and error-prone, especially if you need to support many different types. This is a clear violation of the "Don't Repeat Yourself" (DRY) principle.

Ideally, we would like to write a single version of `max()` that can work with any type that supports comparison. This is where function templates come in.

#### Introduction to C++ templates:
In C++, the template system was designed to simplify the process of creating functions (or classes) that are able to work with different data types.

A **template** is a blueprint or formula for creating a generic class or function. The idea is to write the code once, and then use it with different data types without having to rewrite the code for each type. In this way, you can deifne the logic once, and then use this template with different types as needed.

#### Function templates:
A **fucntion template** is a function-like defintiion that is used to generate one or more overloaded functions, each with a different set of types. The function template itself is not a function, but rather a blueprint for creating functions based on the types provided when the function is called.

The initial function template is called **primary template**, and the functions generated from it are called **instantiated functions**.

When we create a primary function, we use **placeholder types** (also called **type template parameters**) to represent the types that will be used when the function is instantiated. These placeholder types are specified using the `template` keyword, followed by a list of template parameters enclosed in angle brackets (`<>`).

#### Creating a `max()` function template:
Here is the original `int` version of the `max()` function:
```cpp
int max(int x, int y)
{
    return (x < y) ? y : x;
}
```
We used type `int` three times in this function.

To create a function template for `max()` function, we will do the following:
1. Replace the specific type `int` with a placeholder type (e.g., `T`). In this case, sicne we only have one type (`int`), we will use a single placeholder type `T`.
    ```cpp
    T max(T x, T y)
    {
        return (x < y) ? y : x;
    }
    ```
2. Template parameter declaration: We need to declare the template parameters using the `template` keyword. Since we are using a single placeholder type `T`, we will declare it as follows:
    ```cpp
    template <typename T>
    ```
    We start with the keyword `template` (telling the compiler that we are defining a template), followed by angle brackets (`<>`) containing the template parameter declaration. The `typename` (preferred over `class` in general) keyword indicates that `T` is a type placeholder.

Here is the `max()` function template:
```cpp
template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}
```

#### Naming template parameters:
When naming template parameters, it is important to choose meaningful names that convey the purpose of the type. Common conventions include:
- Start with a capital letter (e.g., `T`, `U`, `V`).
- Use descriptive names that indicate the role of the type (e.g., `TValue`, `TKey`, `TElement`).
- Prefixed with `T`, then capital letter (e.g., `TValue`, `TKey`).

#### Summary:
- Function templates allow you to create generic functions that can operate on different data types.
- A function template is defined using the `template` keyword followed by template parameters.
- Placeholder types are used in the function template to represent the types that will be used when the function is instantiated.


---

### S07 — 2.7 Function template instantiation
In this section, we will focus on how function templates are used, when they are instantiated, and how the compiler generates the appropriate function overloads based on the provided argument types.

#### Using a function template:
Function templates are not actually functions themselves, their code is not compiled or executed directly. Instead, they have one job: to generate functions, that are compiled and executed.

To use our `function_template_name<T>()`, we can call it like:
```cpp
function_template_name<type_argument>(arguments); // explicit template argument
```
Where:
- `function_template_name` is the name of the function template.
- `<type_argument>` is the type that will replace the placeholder type `T` in the function template, that is called **template argument**.
- `arguments` are the actual arguments passed to the function.

Let's have a look at an example:
```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // instantiates and calls function max<int>(int, int)

    return 0;
}
```
When the compiler encounters the function call `max<int>(1, 2)`, it performs the following steps:
1. **Template Argument Substitution**: The compiler replaces the placeholder type `T` in the function template with the provided template argument `int`. This results in `max<int>(int x, int y)`. So the original function template:
    ```cpp
    template <typename T>
    T max(T x, T y)
    {
        return (x < y) ? y : x;
    }
    ```
    becomes:
    ```cpp
    template<> // ignore this for now
    int max<int>(int x, int y) // the generated function max<int>(int, int)
    {
        return (x < y) ? y : x;
    }
    ```
2. **Function Instantiation**: If the function `max<int>(int x, int y)` has not been instantiated before, the compiler generates the function definition based on the actual template `max<T>`.
3. **Function Call**: The compiler then compiles and executes the instantiated function `max<int>(int x, int y)` with the provided arguments `1` and `2`.

The process of generating a function from a function template based on the provided template arguments is called **function template instantiation**. When a function is instantiated due to a function call, it is called **implicit instantiation**. A function that is instantiated from a template is called **specialization** of that template, but normally is just called a **function instance**, while the template itself is called the **primary template**.

Basically, afetr all the instantiations are done, the compiler will compile this code:
```cpp
#include <iostream>

// a declaration for our function template (we don't need the definition any more)
template <typename T>
T max(T x, T y);

// the instantiated function
template<>
int max<int>(int x, int y) // the generated function max<int>(int, int)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // instantiates and calls function max<int>(int, int)

    return 0;
}
```

A function template is only instantiated the first time a function call is made in each translation unit. If the same function template is called again with the same template arguments, the compiler will reuse the previously instantiated function, rather than generating a new one.

Here another example:
```cpp
#include <iostream>

template <typename T>
T max(T x, T y) // function template for max(T, T)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n';    // instantiates and calls function max<int>(int, int)
    std::cout << max<int>(4, 3) << '\n';    // calls already instantiated function max<int>(int, int)
    std::cout << max<double>(1, 2) << '\n'; // instantiates and calls function max<double>(double, double)

    return 0;
}
```
Afetr all the instantiations are done, the compiler will compile this code:
```cpp
#include <iostream>

// a declaration for our function template (we don't need the definition any more)
template <typename T>
T max(T x, T y);

// the instantiated functions
template<>
int max<int>(int x, int y) // the generated function max<int>(int, int)
{
    return (x < y) ? y : x;
}

template<>
double max<double>(double x, double y) // the generated function max<double>(double, double)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n';    // calls function max<int>(int, int)
    std::cout << max<int>(4, 3) << '\n';    // calls already instantiated function max<int>(int, int)
    std::cout << max<double>(1, 2) << '\n'; // calls function max<double>(double, double)

    return 0;
}
```
Note that in the `double` instantiation, the compiler automatically converts the integer arguments `1` and `2` to `double` when calling `max<double>(double, double)`.

#### Template arguemnt deduction:
In most cases, the actual types we want to use for instantiation will match the types of the arguments we pass to the function. In such cases, we can let the compiler deduce the template arguments automatically, without explicitly specifying them. This is called **template argument deduction**.

For example, instead of specifying the template argument explicitly like this:
```cpp
std::cout << max<int>(1, 2) << '\n'; // specifying we want to call max<int>
```
We can simply call the function template without specifying the template argument:
```cpp
std::cout << max<>(1, 2) << '\n'; // let the compiler deduce the template argument
// or even simpler:
std::cout << max(1, 2) << '\n'; // compiler deduces we want to call max<int>
```
In both cases, the compiler deduces that the template argument `T` should be `int`, based on the types of the arguments `1` and `2`, and it will instantate and call `max<int>(int, int)`.

The difference between `max<>(1, 2)` and `max(1, 2)` is that in the first case, we are telling the compiler that should only consider `max<int>` for template function overload resolution, while in the second case, the compiler can consider all possible instantiations of `max<T>` for different types `T` during overload resolution (including `max` for other types, if any exist). For example:
```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    std::cout << "called max<int>(int, int)\n";
    return (x < y) ? y : x;
}

int max(int x, int y)
{
    std::cout << "called max(int, int)\n";
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // calls max<int>(int, int)
    std::cout << max<>(1, 2) << '\n';    // deduces max<int>(int, int) (non-template functions not considered)
    std::cout << max(1, 2) << '\n';      // calls max(int, int)

    return 0;
}
```
In here, the bottom call looks identical to a normal function call `max()`. This is what we will prefer to use in most cases, because:
- The synatx is simpler and cleaner.
- It is rare to have both matching non-template function and a function template that could be instantiated to match the same argument types.
- If we do have a matching non-template function and a matching function template, we will usually prefer the non-template function anyway (the specific-type non-template function is considered a better, because it is supposed to be more specialized).

For example:
```cpp
#include <iostream>

// This function template can handle many types, so its implementation is generic
template <typename T>
void print(T x)
{
    std::cout << x; // print T however it normally prints
}

// This function only needs to consider how to print a bool, so it can specialize how it handles
// printing of a bool
void print(bool x)
{
    std::cout << std::boolalpha << x; // print bool as true or false, not 1 or 0
}

int main()
{
    print<bool>(true); // calls print<bool>(bool) -- prints 1
    std::cout << '\n';

    print<>(true);     // deduces print<bool>(bool) (non-template functions not considered) -- prints 1
    std::cout << '\n';

    print(true);       // calls print(bool) -- prints true
    std::cout << '\n';

    return 0;
}
```
prints:
```
1
1
true
```
In this example, the function template `print<T>(T)` is a generic implementation that can handle many types, while the non-template function `print(bool)` is a specialized implementation for printing boolean values. When calling `print(true)`, the compiler prefers the non-template function `print(bool)` over the function template instantiation `print<bool>(bool)`, resulting in the output `true`.

> **Best Practice**: In most cases, prefer to let the compiler deduce the template arguments automatically by calling the function template without specifying the template arguments. This leads to cleaner and more maintainable code.

#### Function templates with non-template parameters:
It’s possible to create function templates that have both template parameters and non-template parameters. The template parameters can be matched by any type, while the non-template parameters must match exactly. For example:
```cpp
#include <iostream>

template <typename T>
void printMultiple(T value, int count)
{
    for (int i = 0; i < count; ++i)
    {
        std::cout << value << ' ';
    }
    std::cout << '\n';
}

int main()
{
    printMultiple<std::string>("Hello", 3); // prints "Hello Hello Hello"
    printMultiple(42, 5);                    // prints "42 42 42 42 42"

    return 0;
}
```
prints:
```
Hello Hello Hello
42 42 42 42 42
```
In this example, the function template `printMultiple<T>(T value, int count)` has a template parameter `T` and a non-template parameter `int count`. The template parameter `T` can be matched by any type, while the non-template parameter `count` must match exactly as an `int`.

#### Instantiated functions may not always compile:
When a function template is instantiated with specific template arguments, the resulting instantiated function must be valid C++ code. If the instantiated function contains code that is not valid for the provided types, the compiler will generate an error during instantiation. For example:
```cpp
#include <iostream>

template <typename T>
T addOne(T x)
{
    return x + 1;
}

int main()
{
    std::cout << addOne(1) << '\n';
    std::cout << addOne(2.3) << '\n';

    return 0;
}
```
The compiler will compile this:
```cpp
#include <iostream>

template <typename T>
T addOne(T x);

template<>
int addOne<int>(int x)
{
    return x + 1;
}

template<>
double addOne<double>(double x)
{
    return x + 1;
}

int main()
{
    std::cout << addOne(1) << '\n';   // calls addOne<int>(int)
    std::cout << addOne(2.3) << '\n'; // calls addOne<double>(double)

    return 0;
}
```
producing:
```
2
3.3
```
However, if we try to instantiate `addOne()` with a type that does not support the `+` operator, such as `std::string`, we will get a compilation error:
```cpp
#include <iostream>
#include <string>

template <typename T>
T addOne(T x)
{
    return x + 1;
}

int main()
{
    std::string hello { "Hello, world!" };
    std::cout << addOne(hello) << '\n';

    return 0;
}
```
generating this:
```cpp
#include <iostream>
#include <string>

template <typename T>
T addOne(T x);

template<>
std::string addOne<std::string>(std::string x)
{
    return x + 1;
}

int main()
{
    std::string hello{ "Hello, world!" };
    std::cout << addOne(hello) << '\n';

    return 0;
}
```
This will produce a compilation error, because the expression `x + 1` is not valid for `std::string` types.

#### Instantiated functions may not always make sense semantically:
Even if the instantiated function compiles successfully, it may not always make sense semantically for certain types. For example:
```cpp
#include <iostream>

template <typename T>
T addOne(T x)
{
    return x + 1;
}

int main()
{
    std::cout << addOne("Hello, world!") << '\n';

    return 0;
}
```
In this example, we are calling `addOne()` with a C-style string literal (`const char*`). The compiler will instantiate the function `addOne<const char*>(const char* x)`, which will compile successfully, but the result of adding `1` to a string literal does not make sense semantically. The output will be:
```
ello, world!
```
This happens because adding `1` to a pointer type (`const char*`) results in pointer arithmetic, which advances the pointer by one character. While this is valid C++ code, it does not produce a meaningful result in the context of adding one to a string.

To avoid this, we could use the `delete` specifier to prevent instantiation for certain types, or we could add static assertions or type traits to restrict the types that can be used with the function template. For example:
```cpp
const char* addOne(const char*) = delete; // prevent instantiation for const char*
```

#### Function templates and default arguments for non-template parameters:
Just like normal functions, function templates can also have default arguments for their non-template parameters. For example:
```cpp
#include <iostream>

template <typename T>
void print(T val, int times=1)
{
    while (times--)
    {
        std::cout << val;
    }
}

int main()
{
    print(5);      // print 5 1 time
    print('a', 3); // print 'a' 3 times

    return 0;
}
```
prints:
```
5aaa
```
In this example, the function template `print<T>(T val, int times=1)` has a default argument of `1` for the non-template parameter `times`. When calling `print(5)`, the default value is used, resulting in `5` being printed once. When calling `print('a', 3)`, the provided value of `3` is used, resulting in `'a'` being printed three times.

#### Beware function templates with modifiable static local variables:
In a previous chapter, we discussed **static local variables**, which are local variables with static duration (they persist for the lifetime of the program). When using function templates, each instantiation of the template creates a separate version of the function, and consequently, each version has its own copy of any static local variables defined within it. This can lead to unexpected behavior if you are not careful. For example:
```cpp
#include <iostream>

// Here's a function template with a static local variable that is modified
template <typename T>
void printIDAndValue(T value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

int main()
{
    printIDAndValue(12);
    printIDAndValue(13);

    printIDAndValue(14.5);

    return 0;
}
```
prints:
```
1) 12
2) 13
1) 14.5
```
In this example, we have a function template `printIDAndValue<T>(T value)` that contains a static local variable `id`. When we call `printIDAndValue(12)` and `printIDAndValue(13)`, the template is instantiated with `T` as ``int`, and both calls share the same static variable `id`, resulting in the output `1)` and `2)`.
However, when we call `printIDAndValue(14.5)`, the template is instantiated with `T` as `double`, creating a separate version of the function with its own static variable `id`. This results in the output `1)` again, since this is the first call to the `double` instantiation.

This is what the compiler will actually compile:
```cpp
#include <iostream>

template <typename T>
void printIDAndValue(T value);

template <>
void printIDAndValue<int>(int value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

template <>
void printIDAndValue<double>(double value)
{
    static int id{ 0 };
    std::cout << ++id << ") " << value << '\n';
}

int main()
{
    printIDAndValue(12);   // calls printIDAndValue<int>()
    printIDAndValue(13);   // calls printIDAndValue<int>()

    printIDAndValue(14.5); // calls printIDAndValue<double>()

    return 0;
}
```
and each instantiated function has its own static local variable `id`.

#### Generic programming:
Generic programming is a programming paradigm that focuses on designing algorithms and data structures in a way that allows them to work with any data type. Function templates are a key feature of generic programming in C++, as they allow you to create functions that can operate on different types without having to write separate functions for each type.

#### Conlusion:
Function templates are a powerful feature in C++ that enable generic programming. They allow you to create functions that can work with different data types without code duplication. By using function templates, you can write more flexible and reusable code, leading to improved maintainability and reduced development time.

Function templates do have few drawsbacks, such as increased compilation times and larger binary sizes due to multiple instantiations. However, the benefits of code reuse and flexibility often outweigh these drawbacks. Also, they tend to produce crazy-looking error messages when something goes wrong, which can be intimidating for beginners. But with practice, you will become more comfortable with reading and understanding these error messages.

> **Best Practice**: Use function templates to create generic functions that can operate on different data types, reducing code duplication and improving maintainability.

#### Summary:
- Function templates allow you to create generic functions that can operate on different data types.
- Function templates are defined using the `template` keyword followed by template parameters (`template <typename T>`).
- Function templates are instantiated when they are called with specific template arguments.
- The compiler generates instantiated functions based on the provided template arguments.


---

### S08 — Function templates with multiple types
Function templates can have multiple template parameters, allowing you to create functions that can work with multiple types simultaneously. This is useful when you want to create functions that operate on different types of data.

Consider the following example:
```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(2, 3.5) << '\n';  // compile error

    return 0;
}
```
In this example, we have a function template `max<T>(T x, T y)` that takes two parameters of the same type `T`. When we try to call `max(2, 3.5)`, the compiler generates a compilation error because it cannot deduce a single type `T` that can accommodate both `int` and `double`, giving a similar error to:
```
Project3.cpp(11,18): error C2672: 'max': no matching overloaded function found
Project3.cpp(11,28): error C2782: 'T max(T,T)': template parameter 'T' is ambiguous
Project3.cpp(4): message : see declaration of 'max'
Project3.cpp(11,28): message : could be 'double'
Project3.cpp(11,28): message : or       'int'
Project3.cpp(11,28): error C2784: 'T max(T,T)': could not deduce template argument for 'T' from 'double'
Project3.cpp(4): message : see declaration of 'max'
```
This will mainly fail because `T` can only represent a single type in this function template, and because both parameters must be of the same type `T`, the compiler cannot deduce a single type that satisfies both arguments.

#### Solution 1 - use static_cast to convert the arguments to matching types:
The first solution is to explicitly convert the arguments to matching types using `static_cast`:
```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(static_cast<double>(2), 3.5) << '\n'; // convert our int to a double so we can call max(double, double)

    return 0;
}
```
In this way, we convert the `int` argument `2` to a `double`, allowing the compiler to deduce `T` as `double` for both parameters. This will compile successfully and print `3.5`.

#### Solution 2 - provide an explicit type template arguemnt:
If we had written a non-template `max(double, double)` function, then we would be able to call `max(int, double)` and let the implicit type conversion rules convert our int argument into a `double` so the function call could be resolved:
```cpp
#include <iostream>

double max(double x, double y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(2, 3.5) << '\n'; // the int argument will be converted to a double

    return 0;
}
```
However, when the compiler is doing template argument deduction for function templates, it does not do any type conversions (as done for normal function overload resolution). Therefore, to use our function template `max<T>(T, T>`, we need to provide an explicit type template argument that can accommodate both argument types:
```cpp
#include <iostream>

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    // we've explicitly specified type double, so the compiler won't use template argument deduction
    std::cout << max<double>(2, 3.5) << '\n';

    return 0;
}
```
In this case, we explicitly specify `double` as the template argument for `T` (it will instantiate `max<double>(double, double)`), allowing both parameters to be treated as `double`. The `int` argument `2` will be implicitly converted to `double` during the function call.

While this is more readable than using `static_cast`, it would be even better if we could have a function template that can handle multiple types without requiring explicit type conversions or template arguments.

#### Solution 3 - function templates with multiple template type parameters:
To create a function template that can handle multiple types, we can define multiple template parameters. For example:
```cpp
#include <iostream>

template <typename T, typename U> // We're using two template type parameters named T and U
T max(T x, U y) // x can resolve to type T, and y can resolve to type U
{
    return (x < y) ? y : x; // uh oh, we have a narrowing conversion problem here
}

int main()
{
    std::cout << max(2, 3.5) << '\n'; // resolves to max<int, double>

    return 0;
}
```
In this example, we define a function template `max<T, U>(T x, U y)` with two template parameters `T` and `U`. This allows the first parameter `x` to be of type `T` and the second parameter `y` to be of type `U`. When we call `max(2, 3.5)`, the compiler deduces `T` as `int` and `U` as `double`, instantiating the function `max<int, double>(int x, double y)`.

However, the output of this will be:
```
3
```
This is because there is a problem in the implementation of the `max()` function. The return type is `T`, which means that if `y` (of type `U`) is greater than `x` (of type `T`), it will be returned and implicitly converted to type `T`. This can lead to a narrowing conversion problem, where the value of `y` may not fit into type `T`.

To fix this, return type decution (via `auto`) can be used to let the compiler deduce the appropriate return type based on the types of the parameters:
```cpp
#include <iostream>

template <typename T, typename U>
auto max(T x, U y) // ask compiler can figure out what the relevant return type is
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(2, 3.5) << '\n';

    return 0;
}
```
Now, the output will be:
```
3.5
```
This is because the compiler deduces the return type of `max<int, double>(int x, double y)` as `double`, which can accommodate the value of `y`.

#### Abbreviated function templates (C++20):
In C++20, a new feature called **abbreviated function templates** was introduced, allowing you to define function templates more concisely using `auto` in the parameter list. This feature simplifies the syntax for function templates, making them easier to read and write. For example, the previous `max()` function template can be rewritten using abbreviated function templates as follows:
```cpp
auto max(auto x, auto y) // abbreviated function template
{
    return (x < y) ? y : x;
}
```
In this example, the `max()` function template is defined using `auto` for both parameters `x` and `y`. The compiler automatically deduces the types of `x` and `y` based on the arguments passed to the function. This approach is more concise and eliminates the need to explicitly declare template parameters.

> **Best Practice**: Use abbreviated function templates if you are using C++20 or later, as they provide a cleaner and more concise syntax for defining function templates.

#### Function templates may be overloaded:
Just like functions may be overloaded, function templates may also be overloaded. This allows you to create multiple versions of a function template that can handle different types or combinations of types. For example:
```cpp
#include <iostream>

// Add two values with matching types
template <typename T>
auto add(T x, T y)
{
    return x + y;
}

// Add two values with non-matching types
// As of C++20 we could also use auto add(auto x, auto y)
template <typename T, typename U>
auto add(T x, U y)
{
    return x + y;
}

// Add three values with any type
// As of C++20 we could also use auto add(auto x, auto y, auto z)
template <typename T, typename U, typename V>
auto add(T x, U y, V z)
{
    return x + y + z;
}

int main()
{
    std::cout << add(1.2, 3.4) << '\n'; // instantiates and calls add<double>()
    std::cout << add(5.6, 7) << '\n';   // instantiates and calls add<double, int>()
    std::cout << add(8, 9, 10) << '\n'; // instantiates and calls add<int, int, int>()

    return 0;
}
```
prints:
```
4.6
12.6
27
```
In this example, we have three overloaded versions of the `add()` function template:
1. `add<T>(T x, T y)`: Adds two values of the same type.
2. `add<T, U>(T x, U y)`: Adds two values of different types.
3. `add<T, U, V>(T x, U y, V z)`: Adds three values of any types.

When we call `add(1.2, 3.4)`, the compiler instantiates and calls `add<double>(double, double)` (from ``add<T>(T x, T y)`). When we call `add(5.6, 7)`, the compiler instantiates and calls `add<double, int>(double, int)` (from `add<T, U>(T x, U y)`). Finally, when we call `add(8, 9, 10)`, the compiler instantiates and calls `add<int, int, int>(int, int, int)` (from `add<T, U, V>(T x, U y, V z)`).

#### Summary:
- Function templates can have multiple template parameters, allowing them to handle different types simultaneously.
- The return type of a function template can be deduced using `auto` to avoid narrowing conversion problems.
- Abbreviated function templates (C++20) provide a concise syntax for defining function templates using `auto` in the parameter list.
- Function templates can be overloaded, allowing multiple versions of a function template to handle different types or combinations of types.


---

### S09 — 11.9 Non-type template parameters
While type template parameters are by far the most common type of template parameter used, there is another kind of template parameter called a **non-type template parameter**.

#### Non-type template parameters:
A **non-type template parameter** is a template parameter with a fixed type that serves as a placeholder for a `constexpr` value passed in as a template argument. This means that instead of representing a type, the non-type template parameter represents a constant value of a specific type.

A non-type template parameter can be of any of the following types:
- Integral types (e.g., `int`, `char`, `bool`, `enum`)
- Enumeration types
- `std::nullptr_t`
- Floating-point types (since C++20)
- Pointer or reference to an object
- Pointer or reference to a function
- Pointer or reference to a member function
- Literal class types with certain restrictions (since C++20)

We saw a first example of non-type template parameter when we discussed `std::bitset`:
```cpp
#include <bitset>

int main()
{
    std::bitset<8> bits{ 0b0000'0101 }; // The <8> is a non-type template parameter

    return 0;
}
```
In this example, `8` is a non-type template argument that specifies the size of the `std::bitset`.

#### Defining our own non-type template parameters:
We can define our own function templates with non-type template parameters. For example:
```cpp
#include <iostream>

template <int N> // declare a non-type template parameter of type int named N
void print()
{
    std::cout << N << '\n'; // use value of N here
}

int main()
{
    print<5>(); // 5 is our non-type template argument

    return 0;
}
```
prints:
```
5
```
In here, we define a function template `print<N>()` with a non-type template parameter `N` of type `int`. When we call `print<5>()`, the compiler instantiates the function with `N` set to `5`, and the function prints the value of `N`.

The compiled code will look like this:
```cpp
template <>
void print<5>()
{
    std::cout << 5 << '\n';
}
```

> **Best Practice**: Use `N` as the name for non-type template parameters of integral types, as it is a common convention that improves code readability.

#### What are non-type template parameters useful for?
As of C++20, function parameters cannot be `constexpr`, so non-type template parameters are useful when you want to pass constant values to functions at compile time. They are often used in scenarios where you need to define functions that operate on fixed-size data structures or perform operations based on constant values.

Let's say we have something like this:
```cpp
#include <cassert>
#include <cmath> // for std::sqrt
#include <iostream>

double getSqrt(double d)
{
    assert(d >= 0.0 && "getSqrt(): d must be non-negative");

    // The assert above will probably be compiled out in non-debug builds
    if (d >= 0)
        return std::sqrt(d);

    return 0.0;
}

int main()
{
    std::cout << getSqrt(5.0) << '\n';
    std::cout << getSqrt(-5.0) << '\n';

    return 0;
}
```
When run, the call `getSqrt(-5.0)` will runtime-assert and terminate the program. However, if we could make `d` a `constexpr` parameter, the compiler could evaluate the assertion at compile time when we call `getSqrt(-5.0)`, resulting in a compilation error instead of a runtime error, saving time and improving code safety. however, the `static_assert` requires constant expressions, and function parameters cannot be `constexpr`.

We can solve this problem by using a non-type template parameter:
```cpp
#include <cmath> // for std::sqrt
#include <iostream>

template <double D> // requires C++20 for floating point non-type parameters
double getSqrt()
{
    static_assert(D >= 0.0, "getSqrt(): D must be non-negative");

    if constexpr (D >= 0) // ignore the constexpr here for this example
        return std::sqrt(D); // strangely, std::sqrt isn't a constexpr function (until C++26)

    return 0.0;
}

int main()
{
    std::cout << getSqrt<5.0>() << '\n';
    std::cout << getSqrt<-5.0>() << '\n';

    return 0;
}
```
In this example, we define a function template `getSqrt<D>()` with a non-type template parameter `D` of type `double`. The `static_assert` checks at compile time whether `D` is non-negative. When we call `getSqrt<5.0>()`, the function compiles and runs successfully, printing the square root of `5.0`. However, when we call `getSqrt<-5.0>()`, the compiler generates a compilation error due to the failed static assertion, preventing a runtime error. Basically, when calling `getSqrt<-5.0>()`, the compiler will attempt to instantiate:
```cpp
template <>
double getSqrt<-5.0>()
{
    static_assert(-5.0 >= 0.0, "getSqrt(): D must be non-negative"); // compilation error here

    if constexpr (-5.0 >= 0)
        return std::sqrt(-5.0);

    return 0.0;
}
```
resulting in a compilation error, since the `static_assert` condition is false.

#### Implicit conversions for non-type template arguments (Optional):

Certain non-type template arguments can be implicitly converted in order to match a non-type template parameter of a different type. For example:
```cpp
#include <iostream>

template <int N> // int non-type template parameter
void print()
{
    std::cout << N << '\n';
}

int main()
{
    print<5>();   // no conversion necessary
    print<'c'>(); // 'c' converted to type int, prints 99

    return 0;
}
```
prints:
```
5
99
```
In the above example, the non-type template parameter `N` is of type `int`. When we call `print<'c'>()`, the character literal `'c'` (of type `char`) is implicitly converted to its corresponding integer value (`99` in ASCII) to match the `int` type of the non-type template parameter.

In this context, only some types of implicit conversions are allowed for non-type template arguments:
- Integral promotions (e.g., `char` to `int`, `short` to `int`)
- Integral conversions (e.g., `char` to `long`, `int` to `char`)
- User-defined conversions (e.g., some program-defined class to `int`)
- Lvalue to rvalue conversions for pointer and reference types (e.g., some variable `x` to the value of `x`)

Unlike normal functions, the algorithm for matching function template calls to function demplate definitions is not sophisticated that it can consider all possible implicit conversions. Therefore, it can very easily result in an ambiguity error if multiple conversions are possible with different overloads. For example:
```cpp
#include <iostream>

template <int N> // int non-type template parameter
void print()
{
    std::cout << N << '\n';
}

template <char N> // char non-type template parameter
void print()
{
    std::cout << N << '\n';
}

int main()
{
    print<5>();   // ambiguous match with int N = 5 and char N = 5
    print<'c'>(); // ambiguous match with int N = 99 and char N = 'c'

    return 0;
}
```
Both calls to `print()` will result in ambiguity errors, because both template definitions could match the provided non-type template arguments after implicit conversions.

#### Type deduction for non-type template parameters using `auto` (C++17):
As of C++17, you can use `auto` as the type for non-type template parameters, allowing the compiler to deduce the type of the non-type template parameter based on the provided template argument. For example:
```cpp
#include <iostream>

template <auto N> // deduce non-type template parameter from template argument
void print()
{
    std::cout << N << '\n';
}

int main()
{
    print<5>();   // N deduced as int `5`
    print<'c'>(); // N deduced as char `c`

    return 0;
}
```
prints:
```
5
c
```
In this example, we define a function template `print<N>()` with a non-type template parameter `N` using `auto`. The compiler deduces the type of `N` based on the provided template arguments. When we call `print<5>()`, `N` is deduced as `int`, and when we call `print<'c'>()`, `N` is deduced as `char`.

In this example, there is no ambiguous matching because we only have one function template definition, and the compiler first check for ambiguous matching among function template definitions and then instantiates the matching one. After instantiation, the program will look like this:
```cpp
#include <iostream>

template <auto N>
void print()
{
    std::cout << N << '\n';
}

template <>
void print<5>() // note that this is print<5> and not print<int>
{
    std::cout << 5 << '\n';
}

template <>
void print<'c'>() // note that this is print<`c`> and not print<char>
{
    std::cout << 'c' << '\n';
}

int main()
{
    print<5>();   // calls print<5>
    print<'c'>(); // calls print<'c'>

    return 0;
}
```

#### Summary:
- Non-type template parameters are template parameters that represent constant values of specific types, rather than types.
- Non-type template parameters can be of various types, including integral types, enumeration types, pointers, references, and more.
- Non-type template parameters are useful for passing constant values to functions at compile time.
- Implicit conversions for non-type template arguments are limited, and care must be taken to avoid ambiguity errors.
- As of C++17, `auto` can be used for non-type template parameters, allowing the compiler to deduce the type based on the provided template argument.


---

### S10 — Using function templates in multiple files
When using function templates in multiple files, it's important to understand how to properly declare and define them to avoid linker errors and ensure correct instantiation.

Consideer the following program (that will not compile for now):

main.cpp:
```cpp
#include <iostream>

template <typename T>
T addOne(T x); // function template forward declaration

int main()
{
    std::cout << addOne(1) << '\n';
    std::cout << addOne(2.3) << '\n';

    return 0;
}
```
add.cpp:
```cpp
template <typename T>
T addOne(T x) // function template definition
{
    return x + 1;
}
```
If `addOne` were a non-template function, this code would compile and link successfully, since the compiler would be satisifed from the forward declaration in `main.cpp`, and the linker would connect the call to `addOne()` in `main.cpp` to the definition in `add.cpp`.

However, because `addOne` is a function template, we will get the following linker error:
```
1>Project6.obj : error LNK2019: unresolved external symbol "int __cdecl addOne<int>(int)" (??$addOne@H@@YAHH@Z) referenced in function _main
1>Project6.obj : error LNK2019: unresolved external symbol "double __cdecl addOne<double>(double)" (??$addOne@N@@YANN@Z) referenced in function _main
```

In the `main.cpp` we call `addOne<int>(int)` and `addOne<double>(double)`, but the compiler cannot find the definitions for the function template `addOne`, and so it cannot instantiate those functions inside `main.cpp`. The compiler will see the forward declaration, and it will think that those functions exist elsewhere, and that they will be linked later.

In the `add.cpp`, the compiler will see the definition of the function template `addOne<T>(T)`, but since there are no calls to `addOne()` in `add.cpp`, the compiler will not instantiate any versions of the function template, and so no code for `addOne<int>(int)` or `addOne<double>(double)` will be generated in `add.obj`.

When the linker tries to link the object files together, it cannot find the definitions for `addOne<int>(int)` and `addOne<double>(double)`, since those functions were never instantiated, resulting in the linker errors.

> **Note**: For template function, forward declaration is not sufficient. The full definition of the function template must be visible to the compiler at the point of instantiation.

The solution is as follows:

add.h:
```cpp
#ifndef ADD_H
#define ADD_H

template <typename T>
T addOne(T x) // function template definition
{
    return x + 1;
}

#endif
```
main.cpp:
```cpp
#include "add.h" // import the function template definition
#include <iostream>

int main()
{
    std::cout << addOne(1) << '\n';
    std::cout << addOne(2.3) << '\n';

    return 0;
}
```
In this solution, we define the function template `addOne<T>(T)` in a header file `add.h`. This header file is then included in `main.cpp`, making the full definition of the function template visible to the compiler at the point of instantiation, because the preprocessor will copy the contents of `add.h` into `main.cpp` before compilation.

When we compile `main.cpp`, the compiler can see the full definition of the function template `addOne<T>(T)`, and it can instantiate the required versions of the function template (`addOne<int>(int)` and `addOne<double>(double)`) based on the calls in `main()`. This results in successful compilation and linking.

You may be wondering why this doesn’t cause a violation of the one-definition rule (ODR). The ODR says that types, templates, inline functions, and inline variables are allowed to have identical definitions in different files. So there is no problem if the template definition is copied into multiple files (as long as each definition is identical).

But what about the instantiated functions themselves? If a function is instantiated in multiple files, how does that not cause a violation of the ODR? The answer is that functions implicitly instantiated from templates are implicitly inline. And as you know, `inline` functions can be defined in multiple files, so long as the definition is identical in each.

Jere is another example of using function templates in multiple files:

max.h:
```cpp
#ifndef MAX_H
#define MAX_H

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

#endif
```
foo.cpp:
```cpp
#include "max.h" // import template definition for max<T>(T, T)
#include <iostream>

void foo()
{
	std::cout << max(3, 2) << '\n';
}
```
main.cpp:
```cpp
#include "max.h" // import template definition for max<T>(T, T)
#include <iostream>

void foo(); // forward declaration for function foo

int main()
{
    std::cout << max(3, 5) << '\n';
    foo();

    return 0;
}
```
When we compile and link `foo.cpp` and `main.cpp`, the compiler can see the full definition of the function template `max<T>(T, T)` in both files, allowing it to instantiate the required versions of the function template based on the calls in each file. This results in successful compilation and linking.

#### Summary:
- When using function templates in multiple files, the full definition of the function template must be visible to the compiler at the point of instantiation.
- To achieve this, define function templates in header files and include those header files in the source files where the function templates are used.
- Functions implicitly instantiated from templates are implicitly inline, allowing them to be defined in multiple files without violating the one-definition rule (ODR).


---

### S11 — Summary and quiz
Try to answer the questions and the quizzes, and then check the solutions in the `exercises` folder.

Enjoy and have fun! :)


---

## 🧭 Summary

In this chapter, you explored how C++ lets you generalize functions in two complementary ways:

- **Overloading** lets multiple functions share the same name with different parameters, increasing readability and usability.
- **Templates** let you write one function that can adapt to many types, avoiding code duplication and enabling **generic programming**.

You also saw that **overload resolution** is the compiler’s decision‑making process for selecting the best candidate among several overloads, and that ambiguity must be handled carefully.  
Function templates, on the other hand, are *instantiated* when used — producing type‑specific functions from a single blueprint.

You learned how **non‑type template parameters** encode compile‑time constants, and how **default arguments** make functions more flexible without losing clarity.  
Finally, you saw how to organize template definitions in header files to ensure correct instantiation across multiple source files.

> **Takeaway:** Function overloading and templates together enable powerful code reuse — but they demand discipline. Always favor clear, unambiguous overloads and explicitly constrained templates for safer, cleaner designs.

### 🧱 Core Concepts You Mastered:
- 🧩 Function overloading and differentiation via signatures  
- ⚖️ Overload resolution and ambiguity handling  
- 🚫 Deleted functions (`= delete`) to restrict overloads  
- ⚙️ Default arguments and their interaction with overloads  
- 🧠 Function templates and instantiation mechanics  
- 🔍 Template argument deduction and specialization  
- 🧮 Non‑type template parameters (`template<int N>`) and their compile‑time use  
- ✨ Abbreviated function templates (`auto`) and C++20 simplifications  
- 🧱 Organizing function templates across multiple files safely 