# Chapter F - Constexpr functions

## 🧭 Overview
In this chapter, we explore **`constexpr` functions**, which allow computations to be performed at **compile time** rather than at runtime.  
While `constexpr` variables let you store constants known during compilation, `constexpr` functions extend this idea — enabling entire functions to be evaluated at compile time when possible.  

This capability improves performance, increases safety, and allows the compiler to catch more errors early. We also discuss **`consteval`** functions (C++20), which *must* be evaluated at compile time, and tools such as `std::is_constant_evaluated()` and `if consteval` (C++23) for controlling evaluation contexts.  

By the end of this chapter, you will understand how and when to use `constexpr` and `consteval` to make your C++ code more **efficient, deterministic, and reliable**.


---

## 🧱 Build / Run

To build and run the examples from this chapter:

```bash
cmake --build build --target chf_first
./build/chf_first
```


---

## 🎯 Learning Outcomes

By the end of this chapter, you’ll be able to:

- 🧩 Understand the difference between **compile-time** and **runtime** evaluation.  
- 🧠 Declare and implement **`constexpr` functions** that can be evaluated at compile time.  
- ⚙️ Understand when a `constexpr` function is evaluated at compile time or runtime.  
- 🧮 Use **`consteval`** (C++20) to force compile-time evaluation.  
- 🧾 Recognize the difference between **required** and **non-required** constant expression contexts.  
- 🧰 Use `std::is_constant_evaluated()` and `if consteval` to control behavior based on evaluation context.  
- 🧱 Safely use **non-const local variables** inside `constexpr` and `consteval` functions (C++14+).  
- 🧩 Distinguish between `constexpr` and non-`constexpr` function calls, and understand their interactions.  
- 🚀 Identify when and why to mark functions as `constexpr` — even if they currently evaluate at runtime.


---

## Sections

### S01 — F.1 Constexpr functions
In a previous chapter, we have introduced the concept of `constexpr` variables, which are variables that can be evaluated at compile time. In this section, we will extend this concept to functions by exploring `constexpr` functions. These functions can be evaluated at compile time when provided with constant expressions as arguments. This allows for more complex computations to be performed during compilation, leading to potential performance improvements and enhanced code optimization.

One challange of constant expressions is that function call are not allowed in constant expressions. For example, here we cannot use a function to compute the circumference of a circle at compile time:
```cpp
#include <iostream>

int main()
{
    constexpr double radius { 3.0 };
    constexpr double pi { 3.14159265359 };
    constexpr double circumference { 2.0 * radius * pi };

    std::cout << "Our circle has circumference " << circumference << "\n";

    return 0;
}
```
But instead we have initialized the circumference variable directly in the expression. This is not very flexible, especially if we want to compute the circumference of multiple circles with different radii, or doign more complex calculations.

To solve this problem, we could try to use a normal function to compute the circumference:
```cpp
#include <iostream>

double calcCircumference(double radius)
{
    constexpr double pi { 3.14159265359 };
    return 2.0 * pi * radius;
}

int main()
{
    constexpr double circumference { calcCircumference(3.0) }; // compile error

    std::cout << "Our circle has circumference " << circumference << "\n";

    return 0;
}
```
However, this code will not compile, because normal functions cannot be evaluated at compile time. This is because constecpr variables require that their initializers are constant expressions, and normal function calls are not considered constant expressions.

#### Constexpr functions can be used in constant expressions:
A **constexpr function** is a function that is allowed to be called in a constant expression. To declare a function as `constexpr`, we simply add the `constexpr` keyword before the function's return type. Here is how we can define a `constexpr` function to calculate the circumference of a circle:
```cpp
#include <iostream>

constexpr double calcCircumference(double radius) // now a constexpr function
{
    constexpr double pi { 3.14159265359 };
    return 2.0 * pi * radius;
}

int main()
{
    constexpr double circumference { calcCircumference(3.0) }; // now compiles

    std::cout << "Our circle has circumference " << circumference << "\n";

    return 0;
}
```
Now, the `calcCircumference` function is declared as `constexpr`, which means it can be evaluated at compile time when called with constant expressions. In this case, we can use it to initialize the `circumference` variable, and the code compiles successfully.

#### Constexpr functions can be evaluated at compile time:
When a `constexpr` function is called with constant expressions as arguments, the compiler evaluates the function at compile time. This allows us to perform computations during compilation, leading to potential performance improvements and enhanced code optimization.

In our example, since `circumference` is a constexpr variable, it will require a constant expression initializer. Since `calcCircumference(3.0)` is a call to a `constexpr` function with a constant expression argument, the compiler evaluates the function at compile time and uses the result to initialize `circumference`.

When a function call is evaluated at compile-time, the compiler will calculate the return value of the function call at compile-time, and then replace the function call with the return value. So in our example, the compiler will replace `calcCircumference(3.0)` with `18.84955592154` during compilation, leading to the following code to be compiled:
```cpp
#include <iostream>

constexpr double calcCircumference(double radius)
{
    constexpr double pi { 3.14159265359 };
    return 2.0 * pi * radius;
}

int main()
{
    constexpr double circumference { 18.8496 };

    std::cout << "Our circle has circumference " << circumference << "\n";

    return 0;
}
```
This means that the function call has been effectively "inlined" at compile time, resulting in potentially more efficient code.

To evaluate at compile-time, to other things must hold true:
- The call to the constexpr function must have arguments that are known at compile time (i.e., constant expressions).
- All statements and expressions within the constexpr function must be evaluable at compile time.

So, when a constexpr function is being evaluated at compile-time, any other functions it calls are required to be evaluated at compile-time as well. This means that if a constexpr function calls another function, that other function must also be declared as constexpr.

#### Constexpr functions can also be evaluated at runtime:
It's important to note that `constexpr` functions can also be called at runtime with non-constant arguments. In such cases, the function will be evaluated at runtime, just like a normal function, and it will return a non-constant result. For example:
```cpp
#include <iostream>

constexpr int greater(int x, int y)
{
    return (x > y ? x : y);
}

int main()
{
    int x{ 5 }; // not constexpr
    int y{ 6 }; // not constexpr

    std::cout << greater(x, y) << " is greater!\n"; // will be evaluated at runtime

    return 0;
}
```
In this example, the `greater` function is declared as `constexpr`, but it is called with non-constant arguments `x` and `y`. As a result, the function will be evaluated at runtime, and it will return the greater of the two values.

#### Summary:
- A `constexpr` function is a function that can be evaluated at compile time when called with constant expressions as arguments.
- To declare a function as `constexpr`, we add the `constexpr` keyword before the function's return type.
- When a `constexpr` function is called with constant expressions, the compiler evaluates the function at compile time, allowing for computations to be performed during compilation.
- `constexpr` functions can also be called at runtime with non-constant arguments, in which case they behave like normal functions.


---

### S02 — F.2 Constexpr functions (part 2)
#### Constexpr function calls in non-required constant expressions:
In the previous section, we learned that `constexpr` functions can be evaluated at compile time when called with constant expressions as arguments. However, `constexpr` functions can also be called in non-required constant expression contexts. In such cases, the compiler has the flexibility to choose whether to evaluate the function at compile time or at runtime, depending on various factors such as optimization settings and the specific context of the code. For example:
```cpp
#include <iostream>

constexpr int getValue(int x)
{
    return x;
}

int main()
{
    int x { getValue(5) }; // may evaluate at runtime or compile-time

    return 0;
}
```
In this example, the `getValue` function is declared as `constexpr`, but it is called in a non-required constant expression context, since the variable `x` is not declared as `constexpr`. In this case, the compiler has the flexibility to choose whether to evaluate the function at compile time or at runtime, depending on various factors such as optimization settings and the specific context of the code.

#### Diagnosis of constexpr functions in required constant expressions:
The compiler is not required to determine whether a constexpr function is evaluatable at compile-time until it is actually evaluated at compile-time. This means that the compiler may not diagnose certain issues with constexpr functions until they are used in a required constant expression context. For example:
```cpp
#include <iostream>

int getValue(int x)
{
    return x;
}

// This function can be evaluated at runtime
// When evaluated at compile-time, the function will produce a compilation error
// because the call to getValue(x) cannot be resolved at compile-time
constexpr int foo(int x)
{
    if (x < 0) return 0; // needed prior to adoption of P2448R1 in C++23 (see note below)
    return getValue(x);  // call to non-constexpr function here
}

int main()
{
    int x { foo(5) };           // okay: will evaluate at runtime
    constexpr int y { foo(5) }; // compile error: foo(5) can't evaluate at compile-time

    return 0;
}
```
In this example, the `foo` function is declared as `constexpr`, but it calls the non-`constexpr` function `getValue`. When `foo` is called in a non-required constant expression context (i.e., when initializing `x`), it can be evaluated at runtime without any issues. However, when `foo` is called in a required constant expression context (i.e., when initializing `y`, it **must** be a compile-time constant), the compiler produces a compilation error because `getValue` cannot be resolved at compile time.

> **Best Practice:** To ensure that your `constexpr` functions can be evaluated at compile time, make sure to test them in required constant expression contexts. This will help you identify any issues with the function's implementation that may prevent it from being evaluated at compile time.

#### Constexpr/consteval function parameters are not constexpr:
It's important to note that parameters of `constexpr` or `consteval` functions are not implicitly `constexpr`. This means that even though a function is declared as `constexpr`, its parameters are treated as regular variables within the function body. Therefore, you cannot assume that the parameters will always be constant expressions. For example:
```cpp
consteval int goo(int c)    // c is not constexpr, and cannot be used in constant expressions
{
    return c;
}

constexpr int foo(int b)    // b is not constexpr, and cannot be used in constant expressions
{
    constexpr int b2 { b }; // compile error: constexpr variable requires constant expression initializer

    return goo(b);          // compile error: consteval function call requires constant expression argument
}

int main()
{
    constexpr int a { 5 };

    std::cout << foo(a); // okay: constant expression a can be used as argument to constexpr function foo()

    return 0;
}
```
In this example, the parameters `b` and `c` of the `foo` and `goo` functions, respectively, are not implicitly `constexpr`. As a result, attempting to use them in constant expressions within the function body leads to compilation errors.

#### COnstexpr functions are implicitly inline:
When a constexpr function is evaluated at compile-time. the compiler must be able to see the full definition of the function in order to evaluate it, and a forward declaration is not sufficient. So, in order to use these functions in multipe translation units, you should incluse its definition in multiple files, and it will results in a clear violation of the one-definition rule (ODR).

To solve this, C++ makes all `constexpr` functions implicitly `inline`. This means that you can define a `constexpr` function in a header file, and include that header file in multiple translation units without violating the ODR. The compiler will ensure that there is only one definition of the function across all translation units.

As a result, the constexpr are often defined in header files, so that they can be used in multiple translation units.

> **Best Practice:** When defining `constexpr` functions, consider placing their definitions in header files to facilitate their use across multiple translation units without violating the one-definition rule.

For constexpr function calls that are only evaluated at runtime, a forward declaration is sufficient to satisfy the compiler. This means that you can use a forward declaration of a `constexpr` function in a translation unit, and the compiler will be able to resolve the function call at runtime without needing to see the full definition of the function.

#### Racap:
- Marking a function as `constexpr` doesn't imply it will always be evaluated at compile-time; it can also be evaluated at runtime.
- A constant expression context requires that the expression be evaluated at compile-time.
- The compiler may decide whether to evaluate a `constexpr` function at compile-time or runtime based on the context.

#### Another example:
Here is another example:
```cpp
#include <iostream>

constexpr int greater(int x, int y)
{
    return (x > y ? x : y);
}

int main()
{
    constexpr int g { greater(5, 6) };              // case 1: always evaluated at compile-time
    std::cout << g << " is greater!\n";

    std::cout << greater(5, 6) << " is greater!\n"; // case 2: may be evaluated at either runtime or compile-time

    int x{ 5 }; // not constexpr but value is known at compile-time
    std::cout << greater(x, 6) << " is greater!\n"; // case 3: likely evaluated at runtime

    std::cin >> x;
    std::cout << greater(x, 6) << " is greater!\n"; // case 4: always evaluated at runtime

    return 0;
}
```
In this example, we have a `constexpr` function `greater` that returns the greater of two integers. The function is called in four different contexts:
1. In case 1, the function is called in a context that requires a constant expression (initializing `g`, that is `constexpr`), so it is always evaluated at compile-time.
2. In case 2, the function is called in a non-required constant expression context (printing the result directly), so the compiler may choose to evaluate it at either compile-time or runtime.
3. In case 3, the function is called with a variable `x` that is not `constexpr`, but its value is known at compile-time. The compiler will likely choose to evaluate it at runtime.
4. In case 4, the function is called with a variable `x` whose value is not known at compile-time (it is read from user input), so it is always evaluated at runtime.

**Note:** Your compiler's optimization settings may influence whether certain `constexpr` function calls are evaluated at compile-time or runtime in non-required constant expression contexts. For example, both **gcc** and **Clang** will not compile-time evaluate a constexpr function called where a constant expression isn’t required unless the compiler told to optimize the code (e.g. using the `-O2` compiler option).

#### Summary:
- `constexpr` functions can be called in both required and non-required constant expression contexts.
- In required constant expression contexts, `constexpr` functions must be evaluated at compile-time.
- In non-required constant expression contexts, the compiler has the flexibility to choose whether to evaluate ``constexpr` functions at compile-time or runtime.
- Parameters of `constexpr` functions are not implicitly `constexpr`.
- `constexpr` functions are implicitly `inline`, allowing their definitions to be included in multiple translation units without violating the one-definition rule.


---

### S03 — F.3 Constexpr function (part 3) and consteval
#### Forcing a constexpr function to be evaluated at compile-time:
There is no way to tell the compiler to always evaluate a `constexpr` function at compile-time. However, C++ provides a way to enforce that a constexpr function that is eligible to be evaluated at compile-time to actually be evaluated at compile-time. This needs to be done on a per-class basis.

The most common way is to use the return value of the constexpr function in a required constant expression context. For example, to initialize a `constexpr` variable. Unfortunately, this requires to introduce a new variable just to force the compile-time evaluation, that is generally not good.

In C++20, there is a better way to enforce compile-time evaluation of a function, by using the `consteval` keyword.

#### Consteval (C++20):
The `consteval` keyword is used to declare a function that must be evaluated at compile-time. When a function is declared as `consteval`, the compiler will produce a compilation error if the function is called in a context where it cannot be evaluated at compile-time. Such functions are called **immediate functions**. Here is an example:
```cpp
#include <iostream>

consteval int greater(int x, int y) // function is now consteval
{
    return (x > y ? x : y);
}

int main()
{
    constexpr int g { greater(5, 6) };              // ok: will evaluate at compile-time
    std::cout << g << '\n';

    std::cout << greater(5, 6) << " is greater!\n"; // ok: will evaluate at compile-time

    int x{ 5 }; // not constexpr
    std::cout << greater(x, 6) << " is greater!\n"; // error: consteval functions must evaluate at compile-time

    return 0;
}
```
In this example, the `greater` function is declared as `consteval`, which means it must be evaluated at compile-time. The first two calls to `greater` are valid because they can be evaluated at compile-time. However, the third call to `greater` with a non-constant expression argument `x` results in a compilation error, because `consteval` functions **cannot** be evaluated at runtime.

> **Best Practice:** Use `consteval` for functions that must always be evaluated at compile-time, ensuring that any misuse is caught at compile-time.

> **Note:** C++ currently does not provide any reliable way to determie whether a constexpr function call is being evaluated at compile-time or runtime. Therefore, if you need to ensure that a function is always evaluated at compile-time, it is recommended to use `consteval` instead of `constexpr`.

#### What bout `std::is_constant_evaluated` or `if consteval`?
Neither of these capabilities tell you whether a function call is evaluating at compile-time or runtime.

`std::is_constant_evaluated` is a standard library function (defined in `<type_traits>`) that returns a `bool` indicating whether the current function is executing in a constant-evaluated context. A **constant-evaluated context** (also called **constant context**) is defined as one in which a constant expression is required (e.g., initializing a `constexpr` variable). So in cases where the compiler is required to evaluate a constant expression at compile-time `std::is_constant_evaluated` will return `true`, otherwise it will return `false`. This allows to do something like this:
```cpp
#include <type_traits> // for std::is_constant_evaluated()

constexpr int someFunction()
{
    if (std::is_constant_evaluated()) // if evaluating in constant context
        doSomething();
    else
        doSomethingElse();
}
```
However, this does not tell you whether a specific function call is being evaluated at compile-time or runtime, since the compiler may decide to evaluate a `constexpr` function at either compile-time or runtime based on the context. So `std::is_constant_evaluated` litterally means "the compiler is being forced to evaluate this expression at compile-time", not "this function call is being evaluated at compile-time".

In C++23, `if consteval` is a replacement for `if (std::is_constant_evaluated())` that nicer syntax, but the same functionality.

#### Using consteval to make constexpr execute at compile-time (C++20):
The downside of consteval functions is that such functions can’t evaluate at runtime at all. This can be too restrictive in some cases, where you want a function to be able to evaluate at compile-time when possible, but also be able to evaluate at runtime when necessary. To solve this problem, you can use `std::is_constant_evaluated()` inside a `constexpr` function to conditionally execute different code paths based on whether the function is being evaluated at compile-time or runtime. Here is an example:
```cpp
#include <iostream>

#define CONSTEVAL(...) [] consteval { return __VA_ARGS__; }()               // C++20 version per Jan Scultke (https://stackoverflow.com/a/77107431/460250)
#define CONSTEVAL11(...) [] { constexpr auto _ = __VA_ARGS__; return _; }() // C++11 version per Justin (https://stackoverflow.com/a/63637573/460250)

// This function returns the greater of the two numbers if executing in a constant context
// and the lesser of the two numbers otherwise
constexpr int compare(int x, int y) // function is constexpr
{
    if (std::is_constant_evaluated())
        return (x > y ? x : y);
    else
        return (x < y ? x : y);
}

int main()
{
    int x { 5 };
    std::cout << compare(x, 6) << '\n';                  // will execute at runtime and return 5

    std::cout << compare(5, 6) << '\n';                  // may or may not execute at compile-time, but will always return 5
    std::cout << CONSTEVAL(compare(5, 6)) << '\n';       // will always execute at compile-time and return 6


    return 0;
}
```
Here, the `compare` function is declared as `constexpr`, allowing it to be evaluated at both compile-time and runtime. Inside the function, we use `std::is_constant_evaluated()` to check whether the function is being evaluated in a constant context. If it is, we return the greater of the two numbers; otherwise, we return the lesser of the two numbers.

Here is an ever better version without preprocessor macros:
```cpp
#include <iostream>

// Uses abbreviated function template (C++20) and `auto` return type to make this function work with any type of value
// See 'related content' box below for more info (you don't need to know how these work to use this function)
// We've opted to use an uppercase name here for consistency with the prior example, but it also makes it easier to see the call
consteval auto CONSTEVAL(auto value)
{
    return value;
}

// This function returns the greater of the two numbers if executing in a constant context
// and the lesser of the two numbers otherwise
constexpr int compare(int x, int y) // function is constexpr
{
    if (std::is_constant_evaluated())
        return (x > y ? x : y);
    else
        return (x < y ? x : y);
}

int main()
{
    std::cout << CONSTEVAL(compare(5, 6)) << '\n';       // will execute at compile-time

    return 0;
}
```
In this version, we define a `consteval` function `CONSTEVAL` that takes a value and returns it. This function can be used to force the evaluation of any expression at compile-time. We then use this function to call `compare(5, 6)`, ensuring that it is evaluated at compile-time.

#### Summary:
- The `consteval` keyword is used to declare functions that must be evaluated at compile-time.
- When a `consteval` function is called in a context where it cannot be evaluated at compile-time, the compiler produces a compilation error.
- `consteval` functions cannot be evaluated at runtime.
- You can use `std::is_constant_evaluated()` inside a `constexpr` function to conditionally execute different code paths based on whether the function is being evaluated at compile-time or runtime.


---

### S04 — F.4 Constexpr functions (part 4)
#### Constexpr/consteval functions can use non-const local variables:
In C++14 and later, `constexpr` and `consteval` functions are allowed to use non-`const` local variables. This means that you can declare local variables within a `constexpr` or `consteval` function that are not marked as `const`. For example:
```cpp
#include <iostream>

consteval int doSomething(int x, int y) // function is consteval
{
    x = x + 2;       // we can modify the value of non-const function parameters

    int z { x + y }; // we can instantiate non-const local variables
    if (x > y)
        z = z - 1;   // and then modify their values

    return z;
}

int main()
{
    constexpr int g { doSomething(5, 6) };
    std::cout << g << '\n';

    return 0;
}
```
In this example, the `doSomething` function is declared as `consteval`, and it uses non-`const` local variables `x` and `z`. We can modify the values of these variables within the function body, and the code compiles successfully.

When such functions are evalauted at compile-time, the compiler will essentially "execute" the function during compilation, and return the calculated result. The use of non-`const` local variables allows for more complex computations to be performed within `constexpr` and `consteval` functions.

#### COnstexpr/consteval functions can use function parameters and local variables as arguments in constexpr function calls:
Above we said that, "When a constexpr (or consteval) function is being evaluated at comoile-time, any other functions it calls are required to be evaluated at compile-time as well." This means that if a `constexpr` or `consteval` function calls another function, that other function must also be declared as `constexpr` or `consteval`. However, the parameters and local variables of the calling function can be used as arguments in the called function, even though they are not `constexpr` themselves. For example:

```cpp
#include <iostream>

constexpr int goo(int c) // goo() is now constexpr
{
    return c;
}

constexpr int foo(int b) // b is not a constant expression within foo()
{
    return goo(b);       // if foo() is resolved at compile-time, then `goo(b)` can also be resolved at compile-time
}

int main()
{
    std::cout << foo(5);

    return 0;
}
```
In this example, the `foo` function is declared as `constexpr`, and it calls the `goo` function, which is also declared as `constexpr`. The parameter `b` of the `foo` function is not a constant expression within the function body, but it can still be used as an argument in the call to `goo`. If `foo` is resolved at compile-time (e.g., when called with a constant expression), then the call to `goo(b)` can also be resolved at compile-time.

#### Can a constexpr function call a non-constexpr function?
The answer is **yes**, but only when the constexpr function is being evaluated in a non-constant context (i.e., at runtime). When a `constexpr` function is called in a non-required constant expression context, it can call non-`constexpr` functions as long as the call is made during runtime evaluation. For example:
```cpp
#include <type_traits> // for std::is_constant_evaluated

constexpr int someFunction()
{
    if (std::is_constant_evaluated()) // if evaluating in constant context
        return someConstexprFcn();
    else
        return someNonConstexprFcn();
}
```
In this example, the `someFunction` is declared as `constexpr`, and it conditionally calls either a `constexpr` function (`someConstexprFcn`) or a non-`constexpr` function (`someNonConstexprFcn`) based on whether it is being evaluated in a constant context or not.

Now consider this variant:
```cpp
constexpr int someFunction(bool b)
{
    if (b)
        return someConstexprFcn();
    else
        return someNonConstexprFcn();
}
```
This will be legal as long as `someFunction(false)` is never called in a constant expression context, because in that case the call to `someNonConstexprFcn()` would need to be resolved at compile-time, which is not possible.

For best results, we suggest the following guidelines:
1. Avoid calling n on-constant functions within `constexpr` functiions if possible.
2. If your constexpr function requires different behavior for constant and non-constant contexts, consider using `std::is_constant_evaluated()` (C++20) or `if consteval` (C++23) to conditionally call the appropriate functions based on the evaluation context.
3. Always test your constexpr functions in a constant context, as they may work when called at runtime but fail when called at compile-time.

#### When should I constexpr a function?
Generally, if a function can be evaluated as part of am required constant expression, it should be declared as `constexpr`. This allows the function to be used in constant expression contexts, enabling compile-time computations and optimizations.

A **pure function** is a function that meets the following criteria:
- It always produces the same output for the same input (deterministic behavior).
- It has no side effects (it does not modify any global state, static variables, or external resources).

Pure functions are ideal candidates for `constexpr` functions because they can be safely evaluated at compile-time without any unintended consequences.

> **Best Practice (1):** When designing functions, strive to make them pure whenever possible. This not only facilitates their use as `constexpr` functions but also enhances code maintainability and testability.

> **Best Practice (2):** Unless you have a specific reason not to, a function that can be evaluated as part of a constant expression should be made `constexpr` (even if it isn’t currently used that way). A function that cannot be evaluated as part of a required constant expression should not be marked as `constexpr`.

#### Why not constexpr every function?
While marking functions as `constexpr` can provide benefits such as enabling compile-time evaluation and optimizations, there are some reasons why you might choose not to declare every function as `constexpr`:
1. It signals that a function can be used in a constant expression context, if your function cannot be evaluated as part of a constant expression, it should not be marked as `constexpr`.
2. It is part of the interface of a function, and changing it later may break existing code that relies on the function's signature.
3. It can be harder to debug since you cannot breakpoint or step into a function that is evaluated at compile-time.

#### Why constexpr a function when it is not actually evaluated at compile-time?
New programmers sometimes ask, “why should I constexpr a function when it is only evaluated at runtime in my program (e.g. because the arguments in the function call are non-const)”?

There are a few reasons:
1. There is little downside to marking a function as `constexpr`, even if it is only evaluated at runtime in your current code, and it may help to optimize your code in the future if you later decide to use it in a constant expression context.
2. Just because you are not currently using a function in a constant expression context does not mean that you will never use it that way in the future. By marking the function as `constexpr`, you are keeping your options open for future use cases.
3. Repetition helps ingrrain good habits. By consistently marking functions that can be `constexpr` as such, you develop a habit that will serve you well in more complex scenarios.

On a non-trivial project, it is a good idea to implement your functions as `constexpr` whenever possible, even if they are not currently used in constant expression contexts. This practice can lead to better code quality, improved performance, and greater flexibility for future development.

#### Summary:
- In C++14 and later, `constexpr` and `consteval` functions can use non-`const` local variables.
- Parameters and local variables of `constexpr` and `consteval` functions can be used as arguments in calls to other `constexpr` functions.
- A `constexpr` function can call a non-`constexpr` function when it is being evaluated at runtime.


---

### SX - F.X Summary and quiz
Again, try to answer the questions and the quizzes, and then check the solutions in the `exercises` folder.

Enjoy and have fun! :)


---

## 🧭 Summary

In this chapter, you learned how to **extend constant expressions to functions** using `constexpr` and `consteval`.  
While `constexpr` functions may be evaluated at either compile time or runtime (depending on context), `consteval` functions must always be evaluated during compilation.

You explored how the compiler decides evaluation contexts, the rules for what can appear inside `constexpr` functions, and why function parameters are *not implicitly constant expressions*.  
You also learned how C++14 and later relax these rules by allowing non-const locals, and how C++20 introduces **`std::is_constant_evaluated()`** and **`consteval`** to offer finer control and explicit enforcement of compile-time behavior.

> **Takeaway:** Prefer marking pure functions as `constexpr` when possible — it enables compile-time computation, improves performance, and provides greater flexibility without any runtime cost.

### 🧱 Core Concepts You Mastered:

- 🧠 Compile-time vs runtime evaluation  
- 🧩 `constexpr` functions and compile-time evaluation rules  
- ⚙️ Required vs non-required constant expression contexts  
- 🧰 Using `std::is_constant_evaluated()` and `if consteval` for context-dependent behavior  
- 💡 `consteval` functions and immediate evaluation enforcement  
- 🧱 Non-const locals and parameters in `constexpr`/`consteval` functions  
- 🧮 Interactions between `constexpr` and non-`constexpr` functions  
- 🧾 When and why to use `constexpr` for optimization and maintainability  
- 🧩 Best practices for pure functions and compile-time computation  