# Chapter 06 — Operators

## 🧭 Overview
Operators are the **building blocks of computation** in C++. They define how data is combined, compared, and transformed.  
Every program relies on operators to perform actions such as arithmetic operations, logical decisions, and value assignments.  
Understanding how operators behave—especially in terms of **precedence**, **associativity**, **side effects**, and **evaluation order**—is essential for writing correct and efficient programs.

This chapter provides a complete guide to all C++ operators, from arithmetic and relational to logical and conditional ones.  
You will learn how expressions are evaluated, how to avoid common pitfalls with side effects, and how to use operators safely and idiomatically.

> **Key idea:** Even though operators look simple, many subtle issues—such as undefined behavior, precedence, and type conversions—can cause unexpected results if misunderstood.


---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch06_first
./build/ch06_first
```

---

## 🎯 Learning Outcomes

By the end of this chapter, you’ll be able to:

- Explain what **operators** are and how they form **expressions**.
- Understand **operator precedence** and **associativity** and how they determine the evaluation order.
- Use **parentheses** to explicitly control and clarify the order of evaluation.
- Apply **arithmetic**, **relational**, and **logical** operators effectively.
- Use **compound assignment**, **increment**, and **decrement** operators correctly.
- Identify **side effects** and understand why they may cause undefined or unspecified behavior.
- Use the **comma** and **conditional (`?:`)** operators appropriately.
- Compare **floating-point values** safely, accounting for precision errors.
- Recognize **short-circuit evaluation** and its role in boolean logic.
- Write clear and unambiguous expressions by avoiding misuse of precedence and side effects.

---

## Sections
This chapter builts on top of [1.9 Introduction to literals and operators](../C01-C++Basics/README.md#s09---19-introduction-to-literals-and-operators) from Chapter 01. An **operator** is a mathematical process involving zero or more input values (called **operands**) that produces a new value (output).
For example, the `+` operator takes two operands and produces a new value. In this chapter we will discuss topics related to operators, and how to use them in your code.

### S01 — 6.1 Operator precedence and associativity
#### Evaluation of compound expressions:
A **compound expression** is an expression that contains one or more operators. For example, the expression `1 + 2 * 3` is a compound expression because it contains the `+` and `*` operators.
But how the compiler evaluates a compound expression?

In order to evaluate an expression, the compiler must do two things:
- At compile time, the compiler parse the expression and determine the order of evaluation of the operators.
- At compile time or runtime, the compiler evaluate the expression.

#### Operator precedence:
To parse correctly a compund expression, all operators are assigned a **precedence** level. The precedence level of an operator is a number that indicates the order in which the operator is evaluated. Operators with a higher precedence level are grouped with operands first.

#### Operator associativity:
The **associativity** tells the compiler whether to evaluate the operators (not the operands!) from left to right or from right to left. The associativity can be from left to right or from right to left.

#### Table of operator precedence and associativity:
Please have a look at the original table from the course (Chapter 6.1).

#### Parenthesization:
To override the default precedence and associativity, you can use parentheses. For example, the expression `1 + 2 * 3` can be parenthesized as `(1 + 2) * 3` to change the order of evaluation.

> **Note**: Use parentheses liberally to make your code more readable, even when they are not strictly necessary.

#### Value computation of operators:
The value computation of an operator is the process of evaluating the operator and producing a new value. The value computation of an operator is performed after the operator has been parsed and the order of evaluation has been determined. For exmaple, in the expression `1 + 2 * 3`, the value computation of the `*` operator is performed first, producing the value `6`, and then the value computation of the `+` operator is performed, producing the final value `7`.

#### The order of evaluation of operands (including function arguments) is mostly unspecified:
The order of evaluation of operands is the order in which the operands are evaluated. The order of evaluation of operands is mostly unspecified, meaning that the compiler can choose to evaluate the operands in any order it wants. For example, in the expression `f() + g()`, the compiler can choose to evaluate `f()` first or `g()` first.

Normally, this is not a problem, but if the operands have side effects (e.g., modifying a global variable), then the order of evaluation can affect the final result. For example:
```cpp
#include <iostream>

int getValue()
{
    std::cout << "Enter an integer: ";

    int x{};
    std::cin >> x;
    return x;
}

void printCalculation(int x, int y, int z)
{
    std::cout << x + (y * z);
}

int main()
{
    printCalculation(getValue(), getValue(), getValue()); // this line is ambiguous

    return 0;
}
```
In the above example, the order in which `getValue()` is called is unspecified, so the user may be prompted to enter the integers in any order. To avoid this ambiguity, it is better to call the functions separately and store the results in variables:
```cpp
int a = getValue();
int b = getValue();
int c = getValue();
printCalculation(a, b, c);
```

#### Summary:
- Operator precedence and associativity determine the order of evaluation of operators in a compound expression.
- Parentheses can be used to override the default precedence and associativity.
- The order of evaluation of operands is mostly unspecified, so be careful when using operands with side effects.


---

### S02 — 6.2 Arithmetic operators
#### Unary arithmetic operators:
There are two unary arithmetic operators: the unary plus (`+`) and the unary minus (`-`). The unary plus operator returns the value of its operand, while the unary minus operator negates the value of its operand (multiplies it by -1).

| Operator | Symbol | Form | Operation |
|----------|--------|------|-----------|
| Unary plus | `+` | `+a` | Returns the value of `a` |
| Unary minus | `-` | `-a` | Negates the value of `a` |

#### Binary arithmetic operators:
There are five binary arithmetic operators: addition (`+`), subtraction (`-`), multiplication (`*`), division (`/`), and modulus (`%`). These operators take two operands and perform the corresponding arithmetic operation.

| Operator | Symbol | Form | Operation |
|----------|--------|------|-----------|
| Addition | `+` | `a + b` | Returns the sum of `a` and `b` |
| Subtraction | `-` | `a - b` | Returns the difference of `a` and `b` |
| Multiplication | `*` | `a * b` | Returns the product of `a` and `b` |
| Division | `/` | `a / b` | Returns the quotient of `a` and `b` |
| Modulus | `%` | `a % b` | Returns the remainder of `a` divided by `b` |

#### Integer and floating point division:
The division operator (`/`) can have two "modes" of operation: integer division and floating point division:
- **Integer division**: If both operands are integers, the division operator performs integer division, which discards any fractional part of the result and returns only the integer part. For example, `5 / 2` evaluates to `2`.
- **Floating point division**: If at least one operand is a floating point number, the division operator performs floating point division, which returns a floating point result. For example, `5.0 / 2` evaluates to `2.5`.

#### Using `static_cast` to do floating point division with integer operands:
To perform floating point division with integer operands, you can use `static_cast` to convert one or both operands to a floating point type.
For example:
```cpp
#include <iostream>

int main()
{
    constexpr int x{ 7 };
    constexpr int y{ 4 };

    std::cout << "int / int = " << x / y << '\n';
    std::cout << "double / int = " << static_cast<double>(x) / y << '\n';
    std::cout << "int / double = " << x / static_cast<double>(y) << '\n';
    std::cout << "double / double = " << static_cast<double>(x) / static_cast<double>(y) << '\n';

    return 0;
}
```
prints:
```
int / int = 1
double / int = 1.75
int / double = 1.75
double / double = 1.75
```

#### Dividing by 0 or 0.0:
Dividing by zero is undefined behavior in C++. If you attempt to divide an integer by zero, your program may crash or produce unexpected results. If you attempt to divide a floating point number by zero, the result will be implementation-defined (it may produce `inf`, `-inf`, or `nan`).

#### Arithmetic assignment operators:
In addition to the standard arithmetic operators, C++ provides arithmetic assignment operators that combine an arithmetic operation with assignment. These operators modify the value of the left operand by performing the specified arithmetic operation with the right operand.

| Operator | Symbol | Form | Operation |
|----------|--------|------|-----------|
| Addition assignment | `+=` | `a += b` | Equivalent to `a = a + b` |
| Subtraction assignment | `-=` | `a -= b` | | Equivalent to `a = a - b` |
| Multiplication assignment | `*=` | `a *= b` | Equivalent to `a = a * b` |
| Division assignment | `/=` | `a /= b` | Equivalent to `a = a / b` |
| Modulus assignment | `%=` | `a %= b` | Equivalent to `a = a % b` |

#### Modifying and non-modifying operators:
An operator that can modify the value of one of its operands is informally called a **modifying operator**. In C++, most operators are **non-modifying operators**, meaning they do not change the value of their operands. However, two categories of built-in operators are modifying operators:
- The assignment operators (e.g., `=`), the arithmetic assignment operators (e.g., `+=`), and the bitwise assignment operators (e.g., `<<=`, `>>=`, `&=`, `|=`, `^=`) are all modifying operators because they modify the value of their left operand.
- The increment (`++`) and decrement (`--`) operators are also modifying operators because they modify the value of their operand by adding or subtracting 1.

#### Summary:
- C++ provides a variety of arithmetic operators for performing mathematical operations.
- The division operator can perform integer or floating point division depending on the types of its operands.
- Arithmetic assignment operators combine arithmetic operations with assignment.

### S03 — 6.3 Remainder and exponentiation
#### The remainder operator (`operator%`):
The **remainder operator** (also called the **modulus operator**) is represented by the symbol `%`. It computes the remainder of the division of two integers. For example, `5 % 2` evaluates to `1`, because when `5` is divided by `2`, the quotient is `2` and the remainder is `1`. This is often used to check if a number is evently divisible by another number (i.e., if the remainder is `0`). For example:
```cpp
#include <iostream>

int main()
{
	std::cout << "Enter an integer: ";
	int x{};
	std::cin >> x;

	std::cout << "Enter another integer: ";
	int y{};
	std::cin >> y;

	std::cout << "The remainder is: " << x % y << '\n';

	if ((x % y) == 0)
		std::cout << x << " is evenly divisible by " << y << '\n';
	else
		std::cout << x << " is not evenly divisible by " << y << '\n';

	return 0;
}
```

#### Remainder with negative operands:
The remainder operator can also work with negative operands. The result of the remainder operation will have the same sign as the dividend (the left operand). For example, `-5 % 2` evaluates to `-1`, and `5 % -2` evaluates to `1`.

Be careful when using the remainder operator with negative operands, for example:
```cpp
bool isOdd(int x)
{
    return (x % 2) == 1; // fails when x is -5
}
```
A better implementation would be:
```cpp
bool isOdd(int x)
{
    return (x % 2) != 0; // works for both positive and negative x, could also write return (x % 2)
}
```

#### Exponentiation in C++:
C++ does not have a built-in exponentiation operator (like `^` in some other languages).

> **Note**: The `^` operator in C++ is the bitwise XOR operator, not an exponentiation operator, be careful not to confuse them!

Instead, you can use the `std::pow` function from the `<cmath>` header to perform exponentiation. For example:
```cpp
#include <cmath>

double x { std::pow(2.0, 3.0) }; // 2.0 to the power of 3.0, x will be 8.0
```

Note that the parameters and return type of `std::pow` are of type `double`. If you need to perform exponentiation with integer types, you can create your own function:
```cpp
#include <cassert> // for assert
#include <cstdint> // for std::int64_t
#include <iostream>

// note: exp must be non-negative
// note: does not perform range/overflow checking, use with caution
constexpr std::int64_t powint(std::int64_t base, int exp)
{
	assert(exp >= 0 && "powint: exp parameter has negative value");

	// Handle 0 case
	if (base == 0)
		return (exp == 0) ? 1 : 0;

	std::int64_t result{ 1 };
	while (exp > 0)
	{
		if (exp & 1)  // if exp is odd
			result *= base;
		exp /= 2;
		base *= base;
	}

	return result;
}

int main()
{
	std::cout << powint(7, 12) << '\n'; // 7 to the 12th power

	return 0;
}
```

This is an even safer implementation that check for overflow:
```cpp
#include <cassert> // for assert
#include <cstdint> // for std::int64_t
#include <iostream>
#include <limits> // for std::numeric_limits

// A safer (but slower) version of powint() that checks for overflow
// note: exp must be non-negative
// Returns std::numeric_limits<std::int64_t>::max() if overflow occurs
constexpr std::int64_t powint_safe(std::int64_t base, int exp)
{
    assert(exp >= 0 && "powint_safe: exp parameter has negative value");

    // Handle 0 case
    if (base == 0)
        return (exp == 0) ? 1 : 0;

    std::int64_t result { 1 };

    // To make the range checks easier, we'll ensure base is positive
    // We'll flip the result at the end if needed
    bool negativeResult{ false };

    if (base < 0)
    {
        base = -base;
        negativeResult = (exp & 1);
    }

    while (exp > 0)
    {
        if (exp & 1) // if exp is odd
        {
            // Check if result will overflow when multiplied by base
            if (result > std::numeric_limits<std::int64_t>::max() / base)
            {
                std::cerr << "powint_safe(): result overflowed\n";
                return std::numeric_limits<std::int64_t>::max();
            }

            result *= base;
        }

        exp /= 2;

        // If we're done, get out here
        if (exp <= 0)
            break;

        // The following only needs to execute if we're going to iterate again

        // Check if base will overflow when multiplied by base
        if (base > std::numeric_limits<std::int64_t>::max() / base)
        {
            std::cerr << "powint_safe(): base overflowed\n";
            return std::numeric_limits<std::int64_t>::max();
        }

        base *= base;
    }

    if (negativeResult)
        return -result;

    return result;
}

int main()
{
	std::cout << powint_safe(7, 12) << '\n'; // 7 to the 12th power
	std::cout << powint_safe(70, 12) << '\n'; // 70 to the 12th power (will return the max 64-bit int value)

	return 0;
}
```

#### Summary:
- The remainder operator (`%`) computes the remainder of the division of two integers.
- C++ does not have a built-in exponentiation operator; use `std::pow` or implement your own function for integer exponentiation.


---

### S04 — 6.4 Increment/decrement operators, and side effects
#### Incrementing and decrementing variables:
Since incrementing or decrementing a variable by `1` is a common operation, C++ provides two special operators for this purpose: the **increment operator** (`++`) and the **decrement operator** (`--`). These operators can be used in both prefix and postfix forms.

| Operator | Symbol | Form | Operation |
|----------|--------|------|-----------|
| Prefix increment (pre-increment) | `++` | `++a` | Increments the value of `a` by `1`, then returns 'a' |
| Prefix decrement (pre-decrement) | `--` | `--a` | Decrements the value of `a` by `1`, then returns 'a' |
| Postfix increment (post-increment) | `++` | `a++` | Copy the value of `a`, increments `a` by `1`, then returns the copied value |
| Postfix decrement (post-decrement) | `--` | `a--` | Copy the value of `a`, decrements `a` by `1`, then returns the copied value |

#### Prefix increment and decrement:
In the **prefix** form of the increment and decrement operators, the operator is placed before the operand. The operation is performed first, and then the modified value is returned. For example:
```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int y { ++x }; // x is incremented to 6, x is evaluated to the value 6, and 6 is assigned to y

    std::cout << x << ' ' << y << '\n';
    return 0;
}
```
gives:
```
6 6
```

#### Postfix increment and decrement:
In the **postfix** form of the increment and decrement operators, the operator is placed after the operand. The current value of the operand is returned first, and then the operation is performed. For example:
```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int y { x++ }; // the current value of x (5) is assigned to y, then x is incremented to 6

    std::cout << x << ' ' << y << '\n';
    return 0;
}
```
gives:
```
6 5
```

Basically, first a temporary copy of variable `x` is made (value = 5), then the original variable `x` is incremented (value = 6), and finally the temporary copy (value = 5) is assigned to variable `y`. This is why `y` ends up being 5, even though `x` is now 6.

#### More examples:
```cpp
#include <iostream>

int main()
{
    int x { 5 };
    int y { 5 };
    std::cout << x << ' ' << y << '\n';
    std::cout << ++x << ' ' << --y << '\n'; // prefix
    std::cout << x << ' ' << y << '\n';
    std::cout << x++ << ' ' << y-- << '\n'; // postfix
    std::cout << x << ' ' << y << '\n';

    return 0;
}
```
gives:
```
5 5
6 4
6 4
6 4
7 3
```

#### When to use prefix vs postfix:
In many cases, both prefix and postfix produce the same result. For example:
```cpp
int main()
{
    int x { 0 };
    ++x; // increments x to 1
    x++; // increments x to 2

    return 0;
}
```
However, when the result of the increment or decrement operation is used in a larger expression, the choice between prefix and postfix can affect the outcome. As a general rule of thumb, prefer using the prefix form unless you specifically need the behavior of the postfix form, since it is more coincise and more performant (especially for user-defined types).

> **Best practice**: Favor the prefix verion, as it is often more performant and less likely to cause confusion.

#### Side effects:
A function or expression is said to have **side effects** if it has some observable effect other than returning a value. Modifying a variable, performing I/O operations, or throwing an exception are all examples of side effects. Mostr of the time side effects are useful:
```cpp
x = 5; // the assignment operator has side effect of changing value of x
++x; // operator++ has side effect of incrementing x
std::cout << x; // operator<< has side effect of modifying the state of the console
```
#### Side effects can cause order of evaluation issues:
When an expression has multiple side effects, the order in which those side effects are applied can affect the final result. For example:
```cpp
#include <iostream>

int add(int x, int y)
{
    return x + y;
}

int main()
{
    int x { 5 };
    int value{ add(x, ++x) }; // undefined behavior: is this 5 + 6, or 6 + 6?
    // It depends on what order your compiler evaluates the function arguments in

    std::cout << value << '\n'; // value could be 11 or 12, depending on how the above line evaluates!

    return 0;
}
```
Here, the order in which the arguments to the `add` function are evaluated is unspecified, so the result of the expression is undefined behavior.

#### The sequencing of side effects:
To avoid issues with the order of evaluation of side effects, it is best to separate expressions that have side effects into multiple statements. For example:
```cpp
int main()
{
    int x { 5 };
    int temp{ ++x }; // increment x first, store the result in a temporary variable
    int value{ add(x, temp) }; // now call add with the updated value of x and the temporary variable
    std::cout << value << '\n'; // now value is well-defined
    return 0;
}
```

Avoid doing things like `x + ++x`, `f(++x, x)`, `arr[i++] = i`, etc., since they lead to undefined behavior.

#### Summary:
- The increment (`++`) and decrement (`--`) operators can be used in both prefix and postfix forms.
- Side effects can lead to order of evaluation issues; separate expressions with side effects into multiple statements to avoid undefined behavior.


---

### S05 — 6.5 The comma operator
The **comma operator** (`,`) is a rarely used operator that allows you to evaluate two expressions in sequence. Basically, this operator evaluates the left operand, then the right operand, and then returns the value of the right operand.

| Operator | Symbol | Form | Operation |
|----------|--------|------|-----------|
| Comma operator | `,` | `a , b` | Evaluates `a`, then evaluates `b`, then returns the value of `b` |

For example:
```cpp
#include <iostream>

int main()
{
    int x{ 1 };
    int y{ 2 };

    std::cout << (++x, ++y) << '\n'; // increment x and y, evaluates to the right operand

    return 0;
}
```
prints:
```
3
```
since `++x` increments `x` to `2`, then `++y` increments `y` to `3`, and the value of the entire expression is the value of the right operand, which is `3`.

Note that the comma operator has the lowest precedence of all operators, so it is evaluated last in a compound expression. Because of this, the following two lines are different:
```cpp
z = (a, b); // evaluate (a, b) first to get result of b, then assign that value to variable z.
z = a, b; // evaluates as "(z = a), b", so z gets assigned the value of a, and b is evaluated and discarded.
```
In the first case, `z` gets the value of `b`, while in the second case, `z` gets the value of `a`.
So the comma operator will always be evaluated last due to its low precedence.

> **Note**: The comma operator is somehow dangerous to use. In almost every case, a statement written using the comma operator would be better written as separate statements.

For example, it would be better to write:
```cpp
#include <iostream>

int main()
{
    int x{ 1 };
    int y{ 2 };

    ++x;
    std::cout << ++y << '\n';

    return 0;
}
```
instead of using the comma operator.

#### Comma as a separator:
The comma is also used as a **separator** in several contexts in C++, such as:
- In function argument lists: `void func(int a, double b);`
- In variable declarations: `int x, y, z;`

In these contexts, the comma does not act as an operator, but rather as a syntactic separator between different elements. for example:
```cpp
void foo(int x, int y) // Separator comma used to separate parameters in function definition
{
    add(x, y); // Separator comma used to separate arguments in function call
    constexpr int z{ 3 }, w{ 5 }; // Separator comma used to separate multiple variables being defined on the same line (don't do this)
}
```

#### Summary:
- The comma operator evaluates two expressions in sequence and returns the value of the right operand.
- The comma is also used as a separator in various contexts, such as function argument lists and variable declarations.


---

### S06 — 6.6 The conditional operator
The **conditional operator** (`?:`), also called the **ternary operator** in C++ (since it has historically been the C++'s only ternary operator), is a shorthand way of expressing conditional statements. It takes three operands and evaluates to one of two values based on a condition.

| Operator | Symbol | Form | Operation |
|----------|--------|------|-----------|
| Conditional operator | `?:` | `condition ? expr1 : expr2` | If `condition` is true, evaluates to `expr1`; otherwise, evaluates to `expr2`. |

To recap, an if-else statement takes the following form:
```cpp
if (condition)
    expression1;
else
    expression2;
```

The equivalent expression using the conditional operator would be:
```cpp
condition ? expression1 : expression2;
```

for example, this if-else statement:
```cpp
if (x > y)
    max = x;
else
    max = y;
```
can be made more concise using the conditional operator:
```cpp
max = (x > y) ? x : y;
```

for example, the following code:
```cpp
#include <iostream>

int getValue()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;
    return x;
}

int main()
{
    int x { getValue() };
    int y { getValue() };
    int max { (x > y) ? x : y };
    std::cout << "The max of " << x <<" and " << y << " is " << max << ".\n";

    return 0;
}
```
prints:
```
Enter a number: 5
Enter a number: 10
The max of 5 and 10 is 10.
```

#### The conditional operator evaluates as part of an expression:
The conditional operator can be used as part of a larger expression, and can be used anywhere an expression is accepted. In cases where the operands of the conditional operator are constant expressions, the conditional operator can be used in a constant expression. This allows the conditional operator to be used where statements cannot be used, such as in the initialization of `constexpr` variables.

For example:
```cpp
#include <iostream>

int main()
{
    constexpr bool inBigClassroom { false };
    constexpr int classSize { inBigClassroom ? 30 : 20 };
    std::cout << "The class size is: " << classSize << '\n';

    return 0;
}
```

You might think to write something like:
```cpp
#include <iostream>

int main()
{
    constexpr bool inBigClassroom { false };

    if (inBigClassroom)
        constexpr int classSize { 30 };
    else
        constexpr int classSize { 20 };

    std::cout << "The class size is: " << classSize << '\n'; // Compile error: classSize not defined

    return 0;
}
```
but this will not compile, since `if` statements cannot be used in constant expressions, and the variable `classSize` is not defined outside the scope of the `if` and `else` blocks.

> **Note**: Variables defined inside the branches of an `if` statement are not accessible outside of those branches, and they are destroyed at the end of their respective blocks.

If you want to do something similar using `if` statements, you would need to do something like:
```cpp
#include <iostream>

int getClassSize(bool inBigClassroom)
{
    if (inBigClassroom)
        return 30;
    else
        return 20;
}

int main()
{
    const int classSize { getClassSize(false) };
    std::cout << "The class size is: " << classSize << '\n';

    return 0;
}
```
This will work since `getClassSize(false)` is an expression, and the if-else logic is inside a function (where we can use statements). However, this is a lot of extra code just to get a constant value, so using the conditional operator is often more concise.

#### Parenthesizing the conditional operator:
Because the conditional operator has relatively low precedence, it is often a good idea to use parentheses to make your code more readable. For example:
```cpp
10 - x > y ? x : y
```
you would expect to be interpreted as:
```cpp
10 - (x > y ? x : y)
```
but due to operator precedence rules, it is actually interpreted as:
```cpp
(10 - x) > y ? x : y
```

Another example:
```cpp
#include <iostream>

int main()
{
    int x { 2 };
    std::cout << (x < 0) ? "negative" : "non-negative";

    return 0;
}
```
prints:
```
0
```
because the expression is interpreted as:
```cpp
(std::cout << (x < 0)) ? "negative" : "non-negative";
```
which first evaluates `std::cout << (x < 0)`, which prints `0` (since `x` is not less than `0`), and then evaluates the conditional operator, which evaluates to `"non-negative"`, but this value is not printed.

To avoid this confision, it is better to use parentheses as follows:
- Parenthesize the entire conditional operator expression when used as an operand in a compund expression.
- For readability, consider parenthesizing the condition if it contains multiple operators.

For example:
```cpp
return isStunned ? 0 : movesLeft;           // not used in compound expression, condition contains no operators
int z { (x > y) ? x : y };                  // not used in compound expression, condition contains operators
std::cout << (isAfternoon() ? "PM" : "AM"); // used in compound expression, condition contains no operators (function call operator excluded)
std::cout << ((x > y) ? x : y);             // used in compound expression, condition contains operators
```

#### The type of the expressions must match or be convertible:
To comply with C++ type checking rules, one of the following must be true:
- The type of `expr1` and `expr2` must be the same.
- The compiler must be able to find a way to convert one or both of the second and third operands (`expr1` and `expr2`) to matching types. The conversion rules are quite complex and may yield to surprising results in some cases.

For example:
```cpp
#include <iostream>

int main()
{
    std::cout << (true ? 1 : 2) << '\n';    // okay: both operands have matching type int

    std::cout << (false ? 1 : 2.2) << '\n'; // okay: int value 1 converted to double

    std::cout << (true ? -1 : 2u) << '\n';  // surprising result: -1 converted to unsigned int, result out of range

    return 0;
}
```
prints:
```
1
2.2
4294967295
```
In the last line, `-1` is converted to an unsigned integer, which results in a very large value (assuming a 32-bit unsigned int).
In general, to avoid confusion, it is best to ensure that both operands of the conditional operator have the same type.

If the compiler cannot find a way to convert the types of `expr1` and `expr2` to matching types, a compilation error will occur. For example:
```cpp
#include <iostream>

int main()
{
    constexpr int x{ 5 };
    std::cout << ((x != 5) ? x : "x is 5"); // compile error: compiler can't find common type for constexpr int and C-style string literal

    return 0;
}
```
causes a compilation error because the compiler cannot find a common type between `int` and a C-style string literal. In this case you can or do an explicit conversion, or use an `if` statement instead.
```cpp
#include <iostream>
#include <string>

int main()
{
    int x{ 5 }; // intentionally non-constexpr for this example

    // We can explicitly convert the types to match
    std::cout << ((x != 5) ? std::to_string(x) : std::string{"x is 5"}) << '\n';

    // Or use an if-else statement
    if (x != 5)
        std::cout << x << '\n';
    else
        std::cout << "x is 5" << '\n';

    return 0;
}
```

#### When you shoul use the conditional operator:
The conditional operator is best used in the following situations:
- Initializing an object with one of two values based on a condition.
- Assigning one of two values to an object based on a condition.
- Passing one of two values as an argument to a function based on a condition.
- Returning one of two values from a function based on a condition.
- Printing one of two values based on a condition.

Complicated expressions involving the conditional operator should be avoided, as they can make your code difficult to read and understand. In such cases, it is better to use `if` statements for clarity.

#### Summary:
- The conditional operator (`?:`) is a concise way to express conditional statements.
- It can be used in constant expressions and as part of larger expressions.
- Ensure that the types of the second and third operands match or are convertible to avoid unexpected results.
- Use parentheses to improve readability and avoid confusion with operator precedence.


---

### S07 — 6.7 Relational operators and floating point comparisons
**Relational operators** are used to compare two values and determine their relationship. They return a boolean value (`true` or `false`) based on the comparison.

| Operator | Symbol | Form | Operation |
|----------|--------|------|-----------|
| Equal to | `==` | `a == b` | Returns `true` if `a` is equal to `b`; otherwise, returns `false` |
| Not equal to | `!=` | `a != b` | Returns `true` if `a` is not equal to `b`; otherwise, returns `false` |
| Greater than | `>` | `a > b` | Returns `true` if `a` is greater than `b`; otherwise, returns `false` |
| Less than | `<` | `a < b` | Returns `true` if `a` is less than `b`; otherwise, returns `false` |
| Greater than or equal to | `>=` | `a >= b` | Returns `true` if `a` is greater than or equal to `b`; otherwise, returns `false` |
| Less than or equal to | `<=` | `a <= b` | Returns `true` if `a` is less than or equal to `b`; otherwise, returns `false` |

Here are some examples of using relational operators:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;

    std::cout << "Enter another integer: ";
    int y{};
    std::cin >> y;

    if (x == y)
        std::cout << x << " equals " << y << '\n';
    if (x != y)
        std::cout << x << " does not equal " << y << '\n';
    if (x > y)
        std::cout << x << " is greater than " << y << '\n';
    if (x < y)
        std::cout << x << " is less than " << y << '\n';
    if (x >= y)
        std::cout << x << " is greater than or equal to " << y << '\n';
    if (x <= y)
        std::cout << x << " is less than or equal to " << y << '\n';

    return 0;
}
```
The result will be:
```
Enter an integer: 4
Enter another integer: 5
4 does not equal 5
4 is less than 5
4 is less than or equal to 5
```

#### Boolean conditional values:
By default, conditions in an if statement or conditional operator (and a few other places) are evaluated as boolean values. In C++, the boolean type is represented by the `bool` keyword, and it can take on two values: `true` and `false`. When a relational operator is used in a condition, it evaluates to either `true` or `false`.

It is good practice to write:
```cpp
if (b1) ...
if (!b2) ...
```
instead of:
```cpp
if (b1 == true) ...
if (b2 == false) ...
```

#### Comparison of calculated floating point values can be problematic:
When comparing floating point values (e.g., `float`, `double`, or `long double`), be aware that due to the way floating point numbers are represented in memory, two values that are mathematically equal may not be exactly equal when represented as floating point numbers. This can lead to unexpected results when using relational operators to compare floating point values. For example:
```cpp
#include <iostream>

int main()
{
    constexpr double d1{ 100.0 - 99.99 }; // should equal 0.01 mathematically
    constexpr double d2{ 10.0 - 9.99 }; // should equal 0.01 mathematically

    if (d1 == d2)
        std::cout << "d1 == d2" << '\n';
    else if (d1 > d2)
        std::cout << "d1 > d2" << '\n';
    else if (d1 < d2)
        std::cout << "d1 < d2" << '\n';

    return 0;
}
```
prints:
```
d1 < d2
```
even though mathematically `d1` and `d2` should be equal. This is because the floating point representation of `d1` and `d2` are not exactly the same due to rounding errors.
By inspecting `d1` and `d2`, we find that `d1` is approximately `0.010000000000005116` and `d2` is approximately `0.0099999999999997868`. Thus, `d1` is slightly greater than `d2`, leading to the result `d1 < d2`.

> **Note:** If the operands are almost identical (due to rounding errors), using the less-than (`<`) or greater-than (`>`) operators can lead to unexpected results, and they are considered unreliable.

The equality and inequality operators (`==` and `!=`) are much more troublesome when used with floating point values. Because of rounding errors, two floating point values that are mathematically equal may not be exactly equal when represented as floating point numbers. Therefore, it is generally not recommended to use the equality (`==`) or inequality (`!=`) operators to compare floating point values directly.

#### Comparing floating point numbers (advanced / optional reading):
A better approach to comparing floating point numbers is to check if the absolute difference between the two numbers is within a small tolerance (also called **epsilon**, generally defined as a small positive value, e.g., `1e-8`):
```cpp
#include <cmath> // for std::abs()

// absEpsilon is an absolute value
bool approximatelyEqualAbs(double a, double b, double absEpsilon)
{
    // if the distance between a and b is less than or equal to absEpsilon, then a and b are "close enough"
    return std::abs(a - b) <= absEpsilon;
}
```
This function checks if the absolute difference between `a` and `b` is less than or equal to `absEpsilon`, and returns `true` if they are close enough, and `false` otherwise.

An even better approach is to use a relative tolerance, which takes into account the magnitude of the numbers being compared:
```cpp
#include <algorithm> // for std::max
#include <cmath>     // for std::abs

// Return true if the difference between a and b is within epsilon percent of the larger of a and b
bool approximatelyEqualRel(double a, double b, double relEpsilon)
{
	return (std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
}
```
This function checks if the absolute difference between `a` and `b` is less than or equal to `relEpsilon` percent of the larger of `a` and `b`, and returns `true` if they are close enough, and `false` otherwise.

#### Summary:
- Relational operators are used to compare two values and return a boolean result.
- Be cautious when comparing floating point values due to potential rounding errors; consider using approximate comparison methods instead.
- When comparing floating point numbers, prefer using a small tolerance (epsilon) to determine if they are "close enough" rather than checking for exact equality.


---

### S08 — 6.8 Logical operators
While relational (comparison) operators can be used to test whether a particular condition is true or false, they can only test one condition at a time. To combine multiple conditions, C++ provides **logical operators** that allow you to create more complex boolean expressions.

C++ has three logical operators:
| Operator | Symbol | Form | Operation |
|----------|--------|------|-----------|
| Logical NOT | `!` | `!a` | Returns `true` if `a` is `false`; otherwise, returns `false` |
| Logical AND | `&&` | `a && b` | Returns `true` if both `a` and `b` are `true`; otherwise, returns `false` |
| Logical OR | `||` | `a || b` | Returns `true` if either `a` or `b` is `true`; if both are `false`, returns `false` |

#### Logical NOT operator (`!`):
The **logical NOT operator** (`!`) is a unary operator that negates the boolean value of its operand. If the operand is `true`, the result is `false`, and if the operand is `false`, the result is `true`.
| Operand | Result |
|---------|--------|
| `true`  | `false`|
| `false` | `true` |

This is often used to check if a condition is false. For example:
```cpp
bool tooLarge { x > 100 }; // tooLarge is true if x > 100
if (!tooLarge)
    // do something with x
else
    // print an error
```

> **Note:** The logical NOT operator has high precedence, so it is evaluated before most other operators. Use parentheses to make your code more readable when necessary.

For example:
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int y{ 7 };

    if (!x > y)
        std::cout << x << " is not greater than " << y << '\n';
    else
        std::cout << x << " is greater than " << y << '\n';

    return 0;
}
```
will print:
```
5 is greater than 7
```
because the expression is evaluated as `(!x) > y`, which negates `x` (which is `5`, a non-zero value, so it evaluates to `0`), and then compares `0 > 7`, which is `false`. To avoid confusion, it is better to use parentheses:
```cpp
if (!(x > y))
    std::cout << x << " is not greater than " << y << '\n';
else
    std::cout << x << " is greater than " << y << '\n';
```

#### Logical OR operator (`||`):
The **logical OR operator** (`||`) is a binary operator that returns `true` if at least one of its operands is `true`. If both operands are `false`, it returns `false`.
| Operand A | Operand B | Result |
|-----------|-----------|--------|
| `true`    | `true`    | `true` |
| `true`    | `false`   | `true` |
| `false`   | `true`    | `true` |
| `false`   | `false`   | `false`|

This operator is often used to check if at least one of multiple conditions is true. For example:
```cpp
if (isWeekend || isHoliday)
    // do something fun
else
    // go to work
```

Be careful, `if (value == 0 || 1)` does not check if `value` is `0` or `1`. It is interpreted as `if ((value == 0) || 1)`, which always evaluates to `true` since `1` is a non-zero value. To check if `value` is `0` or `1`, you should write `if (value == 0 || value == 1)`.

> **Note:** Do not confuse the logical OR operator (`||`) with the bitwise OR operator (`|`), which performs a bitwise operation on integer values.

#### Logical AND operator (`&&`):
The **logical AND operator** (`&&`) is a binary operator that returns `true` only if both of its operands are `true`. If either operand is `false`, it returns `false`.
| Operand A | Operand B | Result |
|-----------|-----------|--------|
| `true`    | `true`    | `true` |
| `true`    | `false`   | `false`|
| `false`   | `true`    | `false`|
| `false`   | `false`   | `false`|

For example, we might want to know if the value of variable x is between 10 and 20:
```cpp
if (x >= 10 && x <= 20)
    // x is between 10 and 20
else
    // x is outside the range
```

> **Note:** Do not confuse the logical AND operator (`&&`) with the bitwise AND operator (`&`), which performs a bitwise operation on integer values.

#### Short-circuit evaluation:
Both the logical AND (`&&`) and logical OR (`||`) operators use **short-circuit evaluation**. This means that the second operand is only evaluated if necessary. For example, in the case of the logical AND operator (`&&`), if the first operand is `false`, the overall expression will be `false` regardless of the value of the second operand, so the second operand is not evaluated. Similarly, for the logical OR operator (`||`), if the first operand is `true`, the overall expression will be `true` regardless of the value of the second operand, so the second operand is not evaluated.

Short circuit evaluation provides another example of why operators that cause side effects shoul dnot be used in compund expressions. For example:
```cpp
if (x == 1 && ++y == 2)
    // do something
```
If `x` is not equal to `1`, then `++y` will not be evaluated, and `y` will not be incremented. This can lead to unexpected behavior if you are not careful.

#### Mixing ANDs and ORs:
When mixing logical AND (`&&`) and logical OR (`||`) operators in the same expression, it is important to be aware of operator precedence. The logical AND operator has higher precedence than the logical OR operator, so expressions with both operators will evaluate the AND operations first. It is generally a good idea to use parentheses to make the order of evaluation explicit and improve readability. For example:
```cpp
if (isWeekend || (isHoliday && isSunny))
    // do something fun
else
    // go to work
```

#### De Morgan's Laws:
De Morgan's Laws provide a way to simplify logical expressions involving negations. They state that:
- The negation of a conjunction is the disjunction of the negations:
  `!(A && B) == (!A || !B)`
- The negation of a disjunction is the conjunction of the negations:
  `!(A || B) == (!A && !B)`

These laws can be useful for simplifying complex logical expressions and for understanding how to negate conditions.

#### Logical exclusive OR (XOR) operator:
C++ does not have a built-in logical exclusive OR (XOR) operator, but you can simulate it using a combination of logical operators. The logical XOR operation returns `true` if exactly one of its operands is `true`, and `false` otherwise.

| Operand A | Operand B | Result |
|-----------|-----------|--------|
| `true`    | `true`    | `false`|
| `true`    | `false`   | `true` |
| `false`   | `true`    | `true` ||
| `false`   | `false`   | `false`|

Unlike logical OR and AND, there is no short-circuit evaluation for logical XOR, since both operands need to be evaluated to determine the result.

However, `operator!=` can be used to achieve the same effect when given `bool` operands:

| Operand A | Operand B | Logical XOR | `operator!=` |
|-----------|-----------|-------------|---------------|
| `true`    | `true`    | `false`     | `false`      |
| `true`    | `false`   | `true`      | `true`       |
| `false`   | `true`    | `true`      | `true`       |
| `false`   | `false`   | `false`     | `false`      |

Therefore, a logical XOR operation can be implemented as:
```cpp
bool logicalXOR(bool a, bool b)
{
    return a != b;
}
```
assuming both `a` and `b` are boolean values.

#### Alternative operator representations:
C++ also provides alternative representations for the logical operators using keywords:
```cpp
| Operator | Symbol | Alternative Representation |
|----------|--------|----------------------------|
| Logical NOT | `!` | `not` |
| Logical AND | `&&` | `and` |
| Logical OR | `||` | `or` |

These alternative representations can be used in place of the symbols, but they are less commonly used in practice. For example:
```cpp
std::cout << !a && (b || c);
std::cout << not a and (b or c);
```
Both lines are equivalent.

#### Summary:
- Logical operators (`!`, `&&`, `||`) are used to combine boolean expressions.
- Logical NOT (`!`) negates a boolean value.
- Logical AND (`&&`) returns `true` if both operands are `true`.
- Logical OR (`||`) returns `true` if at least one operand is `true`.
- Be cautious of operator precedence and use parentheses to improve readability.


---

### SX - 6.x Summary and quiz
Try it by yourself looking at the exercise section in the website. If you want to have a possible solution, it is [here](exercises/sx-questions/main.cpp).

Have fun! :)


## 🧭 Summary
Operators are fundamental to expressing logic and computation in C++.  
They define how operands are combined, evaluated, and transformed into new results.  
Each operator follows a well-defined **precedence** and **associativity**, which together determine how compound expressions are parsed and executed.  
Parentheses can always be used to override these rules and improve readability.

C++ provides a large set of built-in operators—arithmetic, logical, relational, assignment, and more—that work with both fundamental and user-defined types.  
Some operators (like increment/decrement) have **side effects**, meaning they modify data as part of their operation.  
Understanding when and how these side effects occur is crucial to avoiding **undefined behavior** and ensuring deterministic results.

This chapter also introduced advanced operators like the **comma operator** and the **conditional (`?:`)** operator, along with best practices for floating-point comparisons and boolean logic.  
By mastering these tools, you can express complex logic compactly and safely while keeping your code both efficient and readable.

### 🧱 Core Concepts You Mastered:
- **Operators and operands** — expressions built from operators and their input values.
- **Operator precedence** — determines which operations are grouped first.
- **Operator associativity** — defines whether evaluation proceeds left-to-right or right-to-left for operators of the same precedence.
- **Parentheses for clarity** — used to explicitly control and clarify evaluation order.
- **Arithmetic operators** — perform addition, subtraction, multiplication, division, and modulus.
- **Assignment and compound operators** — combine computation and assignment (`+=`, `-=`, etc.).
- **Increment/decrement operators** — modify values with prefix and postfix behavior.
- **Side effects and sequencing** — how modifying operations can affect evaluation order.
- **The comma operator** — evaluates two expressions in sequence and returns the second result.
- **The conditional operator (`?:`)** — a concise alternative to `if-else` expressions.
- **Relational operators** — compare values and return boolean results.
- **Floating-point comparisons** — best practices for approximate equality using epsilon tolerance.
- **Logical operators** — combine multiple boolean expressions (`&&`, `||`, `!`) with short-circuit evaluation.
- **Alternative keywords** — use of `and`, `or`, `not` as textual forms of logical operators.
- **Undefined and unspecified behavior** — understanding when operator ordering can lead to ambiguity.