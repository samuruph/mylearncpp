# Chapter 08 - Control Flow

## 🧭 Overview
Control flow determines **how a program’s instructions are executed** — sequentially, conditionally, or repeatedly.  
In C++, control flow statements allow developers to make **decisions**, **repeat actions**, and **jump** to different parts of the code based on logical conditions.  
Without control flow, a program would only execute linearly, unable to react to user input or dynamic situations.

This chapter covers conditional structures (`if`, `else`, `switch`), looping mechanisms (`for`, `while`, `do while`), jump statements (`break`, `continue`, `goto`), and program termination.  
It also introduces random number generation, often used in control-driven logic such as simulations or probabilistic algorithms.

> **Key idea:** Mastering control flow means mastering the *logic* of a program — when, how, and why code executes.


---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch08_first
./build/ch08_first
```


---

## 🎯 Learning Outcomes

By the end of this chapter, you’ll be able to:

- Explain what **control flow** is and why it’s fundamental in programming.  
- Use **conditional statements** (`if`, `else if`, `else`, `switch`) to control program decisions.  
- Implement **loops** (`for`, `while`, `do while`) for iteration and repeated execution.  
- Use **jump statements** (`break`, `continue`, `goto`) to alter normal execution flow.  
- Use **halt statements** (`std::exit()`, `std::abort()`) to terminate programs intentionally.  
- Understand **compile-time branching** with `if constexpr`.  
- Use **switch statements** effectively and handle fall-through safely (`[[fallthrough]]`).  
- Generate **random numbers** with C++’s `<random>` library and Mersenne Twister engine.  
- Apply **best practices** for code clarity and control structure readability.  


---

## Sections

### S01 — 8.1 Control flow introduction
When a program is run, begins executing instructions from the top of the `main` function and continues executing sequentially, one instruction after another. This is called **execution path** (or **path**, for short).

There are different type of programs based on their execution paths:
- **Straight-line programs**: Programs that execute instructions sequentially from start to finish without any branching or looping. These programs have a single, linear execution path (too simple to be real).
- **Control flow programs (branching)**: Programs that can alter their execution path based on certain conditions or repeat certain sections of code multiple times. These programs use **control flow statements** (also called **flow control statements**) to make decisions and control the flow of execution.

#### Categories of flow control statements:
Here are the main categories of flow control statements, along with their meanings and implementations in C++:

| Category | Meaning | Implementation in C++ |
|----------|---------|-----------------------|
| Conditional statements | Sequence of code is executed only if some condition is met | `if`, `else if`, `else`, `switch` |
| Jumps | Tells the CPU to start executing the statements at some other location in the program | `goto`, `break`, `continue` |
| Function calls | Tells the CPU to jump to the beginning of a function and start executing statements there | Function call syntax, `return` |
| Loops | Sequence of code is executed multiple times until some condition is met | `for`, `while`, `do while` |
| Halts | Terminate the program execution | `std::exit()`, `std::abort()` |
| Exceptions | Error handling mechanism that alters the normal flow of execution when an error occurs | `try`, `catch`, `throw` |



---

### S02 — 8.2 If statements and blocks
A **conditional statement** is a type of control flow statement that allows a program to execute certain sections of code based on whether a specified condition is true or false. C++ supports two basic conditional statements: `if` and `switch`.

#### Quick if-statement recap:
Here a quick recap of the `if` statement syntax in C++:
```cpp
if (condition) {
    // code to be executed if condition is true
} else if (another_condition) {
    // code to be executed if another_condition is true
} else {
    // code to be executed if none of the above conditions are true
}
```
If the condition evaluates to true, the code block inside the `if` statement is executed. If the condition is false, the program checks the next `else if` condition (if present) and executes its code block if true. If none of the conditions are true, the code block inside the `else` statement is executed (if present).

Remember to use curly braces `{}` to define code blocks, especially when you have multiple statements to execute within the conditional branches (multiple lines of code).

#### Implicit blocks:
If the programmer does not declare a block using curly braces `{}`, the compiler will implicitly declare one for the first statement following the condition. For example:
```cpp
if (condition)
    statement1;
    statement2; // This statement is NOT part of the if block
```
will be interpreted as:
```cpp
if (condition) {
    statement1;
}
statement2; // This statement is NOT part of the if block
```

For example, the following code:
```cpp
#include <iostream>

int main()
{
    if (true)
    {
        int x{ 5 };
    } // x destroyed here
    else
    {
        int x{ 6 };
    } // x destroyed here

    std::cout << x << '\n'; // x isn't in scope here

    return 0;
}
```
will not compile because `x` is declared inside the blocks of the `if` and `else` statements, and thus is not in scope outside of those blocks.

#### To block or not to block single statements?
Even for single statements, it is a good practice to always use curly braces `{}` to define code blocks. This improves code readability and helps prevent errors in more complex scenarios (adding new statements later, nested conditions, etc.).
Not having explicit blocks can lead to confusion and bugs, for example:
- Missing braces can lead to unintended behavior when adding new statements:
    ```cpp
    if (age >= minDrinkingAge)
    purchaseBeer();
    gamble(); // added later, but always executed (not inside if block)
    ```
- Missing braces can make debugging and maintenance more difficult, especially in nested conditions:
    ```cpp
    if (condition1)
        if (condition2)
            doSomething();
        else
            doSomethingElse(); // which if does this else belong to?
    ```
    or, if we comment out one statement while debugging:
    ```cpp
    if (age >= minDrinkingAge)
    //    addBeerToCart();

    checkout(); // conditionally executes now
    ```
- `if constexpr` statements (introduced in C++23) require blocks for multiple statements (so, ensuress consistency).

#### If-else vs if-if:
An `if-else` statement creates a mutually exclusive branching structure, meaning that only one of the branches will be executed based on the evaluated conditions. In contrast, multiple `if` statements are independent of each other, and each condition is evaluated separately, allowing for multiple branches to be executed if their conditions are true. In general:
- Use `if-else` when you have mutually exclusive conditions and only the first `true` condition should execute its block.
- Use multiple `if` statements when the conditions are independent, and you want to allow for multiple blocks to be executed if their conditions are true.

For example:
```cpp
#include <iostream>

void ifelse(bool a, bool b, bool c)
{
    if (a)      // always evaluates
        std::cout << "a";
    else if (b) // only evaluates when prior if-statement condition is false
        std::cout << "b";
    else if (c) // only evaluates when prior if-statement condition is false
        std::cout << "c";
    std::cout << '\n';
}

void ifif(bool a, bool b, bool c)
{
    if (a) // always evaluates
        std::cout << "a";
    if (b) // always evaluates
        std::cout << "b";
    if (c) // always evaluates
        std::cout << "c";
    std::cout << '\n';
}

int main()
{
    ifelse(false, true, true);
    ifif(false, true, true);

    return 0;
}
```
Output:
```
b
bc
```
In this example, the `ifelse` function only prints "b" because it uses an `if-else` structure, which stops evaluating conditions after the first true condition is found. The `if-if` function, on the other hand, prints "bc" because it uses separate `if` statements, allowing both conditions to be evaluated independently.

Now, have a look at this example:
```cpp
char getFirstMatchingChar(bool a, bool b, bool c)
{
    if (a) // always evaluates
        return 'a';
    else if (b) // only evaluates when prior if-statement condition is false
        return 'b';
    else if (c) // only evaluates when prior if-statement condition is false
        return 'c';

    return 0;
}
```
and this one:
```cpp
char getFirstMatchingChar(bool a, bool b, bool c)
{
    if (a) // always evaluates
        return 'a'; // returns when if-statement is true
    if (b) // only evaluates when prior if-statement condition is false
        return 'b'; // returns when if-statement is true
    if (c) // only evaluates when prior if-statement condition is false
        return 'c'; // returns when if-statement is true

    return 0;
}
```
Both functions behave the same way, returning the first matching character based on the conditions. However, the first function uses an `if-else` structure, which is more efficient in this case since it stops evaluating conditions after the first true condition is found. The second function uses separate `if` statements, which means all conditions are evaluated independently, even after a match is found, but the `return` statements ensure that only the first matching character is returned.

#### Summary:
- Use `if-else` when you have mutually exclusive conditions and only the first `true` condition should execute its block.
- Use multiple `if` statements when the conditions are independent, and you want to allow for multiple blocks to be executed if their conditions are true.


---

### S03 — 8.3 Common if statement problems
This is the continuation of the previous section, where we discuss some common problems and pitfalls when using `if` statements in C++.

#### Nested if-statements and the dangling else problem:
It is possible to nest `if` statements within other `if` statements to create more complex conditional structures. For example:
```cpp
if (condition1)
{
    if (condition2)
    {
        // code to be executed if both condition1 and condition2 are true
    }
}
```
However, nesting `if` statements can lead to the **dangling else problem**, which occurs when an `else` clause is ambiguous about which `if` statement it belongs to. For example:
```cpp
if (condition1)
    if (condition2)
        // code to be executed if both condition1 and condition2 are true
    else
        // code to be executed if condition1 is false
```
In this example, it is unclear whether the `else` clause belongs to the inner `if` statement or the outer `if` statement. To avoid this ambiguity, it is recommended to use curly braces `{}` to clearly define the blocks of code associated with each `if` and `else` statement. For example:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;

    if (x >= 0) // outer if-statement
        // it is bad coding style to nest if statements this way
        if (x <= 20) // inner if-statement
            std::cout << x << " is between 0 and 20\n";

    // which if statement does this else belong to?
    else
        std::cout << x << " is negative\n";

    return 0;
}
```
is equivalent to:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;

    if (x >= 0) // outer if statement
    {
        if (x <= 20) // inner if statement
            std::cout << x << " is between 0 and 20\n";
        else // attached to inner if statement
            std::cout << x << " is negative\n";
    }

    return 0;
}
```
and gives:
```
Enter a number: 21
21 is negative
```
To fix the ambiguity, we can use curly braces to clearly define the blocks of code associated with each `if` and `else` statement:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;

    if (x >= 0) // outer if statement
    {
        if (x <= 20) // inner if statement
        {
            std::cout << x << " is between 0 and 20\n";
        }
    }
    else // attached to outer if statement
    {
        std::cout << x << " is negative\n";
    }

    return 0;
}
```

> **Note:** In C++, an `else` clause is always associated with the nearest preceding unmatched `if` statement. This means that in the example above, the `else` clause would be associated with the inner `if` statement.

#### Flattening nested if-statements:
Deeply nested `if` statements can make code harder to read and maintain. To improve readability, consider flattening nested `if` statements by using logical operators (`&&`, `||`) to combine conditions or restructuring the logic. For example, the prebious example can be flattened as follows:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;

    if (x < 0)
        std::cout << x << " is negative\n";
    else if (x <= 20) // only executes if x >= 0
        std::cout << x << " is between 0 and 20\n";
    else // only executes if x > 20
        std::cout << x << " is greater than 20\n";

    return 0;
}
```

Here another example of flattening nested `if` statements using logical operators:
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

    if (x > 0 && y > 0) // && is logical and -- checks if both conditions are true
        std::cout << "Both numbers are positive\n";
    else if (x > 0 || y > 0) // || is logical or -- checks if either condition is true
        std::cout << "One of the numbers is positive\n";
    else
        std::cout << "Neither number is positive\n";

    return 0;
}
```

#### Null statements:
A null statement is a statement that does nothing. In C++, a null statement is represented by a single semicolon (`;`). Null statements can be useful in certain situations, such as when you need to provide a statement but don't want to perform any action. For example:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;

    if (x < 0)
        ; // null statement - do nothing for negative numbers
    else
        std::cout << x << " is non-negative\n";

    return 0;
}
```
In this example, if the user enters a negative number, the program does nothing (due to the null statement) and simply continues execution. If the user enters a non-negative number, the program prints the number.

> **Best Practice:** While null statements can be useful in certain situations, they should be used sparingly and with caution, as they can make code harder to read and understand. Always consider whether there is a clearer way to express your intent without using a null statement.

Sometimes, null statements are dangerous, for example:
```cpp
if (nuclearCodesActivated()); // note the semicolon at the end of this line
    blowUpTheWorld();
```
is equivalent to:
```cpp
if (nuclearCodesActivated()) // note the lack of semicolon at the end of this line
{
    ; // do nothing
}
blowUpTheWorld(); // always executes
```
To avoid such pitfalls, always be cautious when placing semicolons after `if` statements.

> **Note:** In Python, a null statement is represented by the `pass` keyword. Since it is a keyword, it is less likely to be confused with an accidental semicolon.

#### `operator==` vs `operator=` inside the conditional:
A common mistake when writing `if` statements is to accidentally use the assignment operator (`=`) instead of the equality operator (`==`) in the condition. The assignment operator assigns a value to a variable, while the equality operator checks if two values are equal. Inside your `if` statement conditions, you should always use `==` to compare values. For example:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter 0 or 1: ";
    int x{};
    std::cin >> x;
    if (x = 0) // oops, we used an assignment here instead of a test for equality
        std::cout << "You entered 0\n";
    else
        std::cout << "You entered 1\n";

    return 0;
}
```
prints:
```
Enter 0 or 1: 0
You entered 1
```
because the condition `x = 0` assigns `0` to `x` **different from `x == 0`**, and the result of the assignment expression is `0`, which evaluates to `false`. Therefore, the `else` branch is executed.

> **Note:** The assignment expression `x = 0` first assigns the value `0` to `x`, and then evaluates to the value of `x`, which is now `0`. In C++, any non-zero value is considered `true`, while `0` is considered `false`.

#### Summary:
- Use curly braces `{}` to clearly define blocks of code associated with each `if` and `else` statement to avoid ambiguity.
- Flatten nested `if` statements using logical operators or restructuring the logic to improve readability.
- Avoid using null statements unless absolutely necessary, as they can make code harder to read and understand.
- Always use the equality operator (`==`) in `if` statement conditions to compare values, not the assignment operator (`=`).


---

### S04 — 8.4 Constexpr if statements
Normally, `if` statements are evaluated at runtime, meaning that the condition is checked while the program is running. But consider the following example:
```cpp
#include <iostream>

int main()
{
	constexpr double gravity{ 9.8 };

	// reminder: low-precision floating point literals of the same type can be tested for equality
	if (gravity == 9.8) // constant expression, always true
		std::cout << "Gravity is normal.\n";   // will always be executed
	else
		std::cout << "We are not on Earth.\n"; // will never be executed

	return 0;
}
```
Here, `gravity` is declared as a `constexpr`, meaning its value is known at compile time. The condition `gravity == 9.8` is also a constant expression, so the compiler can determine that it will always evaluate to `true`.

#### Constexpr if statements (C++17 and later):
To optimize such scenarios, C++17 introduced the **`if constexpr` statement**, which allows the compiler to evaluate the condition at compile time. If the condition is `true`, the compiler includes the corresponding code block in the compiled program; if `false`, it excludes that block entirely. This can lead to more efficient code by eliminating unnecessary branches.
Here's how you can use `if constexpr`:
```cpp
#include <iostream>

int main()
{
	constexpr double gravity{ 9.8 };

	if constexpr (gravity == 9.8) // now using constexpr if
		std::cout << "Gravity is normal.\n";
	else
		std::cout << "We are not on Earth.\n";

	return 0;
}
```
In this example, since the condition `gravity == 9.8` is a constant expression that evaluates to `true`, the compiler includes only the first code block in the compiled program, resulting in more efficient code. Overall, it will compile like this:
```cpp
#include <iostream>

int main()
{
    std::cout << "Gravity is normal.\n";
    return 0;
}
```

> **Best Practice:** Prefer using `if constexpr` over regular `if` statements when evaluated on `constexpr` conditions, as it can lead to more efficient code by eliminating unnecessary branches at compile time.

#### Modern compilers and if statements with constexpr conditionals (C++17 and later):
Modern C++ compilers are quite good at optimizing code, and they can often optimize regular `if` statements with `constexpr` conditions similarly to `if constexpr` when those have constexpr conditions. However, using `if constexpr` explicitly communicates the intent to the compiler and other developers that the condition is meant to be evaluated at compile time, which can improve code readability and maintainability.

#### Summary:
- Use `if constexpr` when the condition is a constant expression known at compile time to enable compile-time evaluation and optimization.
- Modern compilers can optimize regular `if` statements with `constexpr` conditions, but using `if constexpr` improves code readability and intent.


---

### S05 — 8.5 Switch statement basics
Although it is possible to chain many `if-else if` statements together to handle multiple discrete values of a variable, this approach can become cumbersome and less readable as the number of conditions increases. In such cases, the `switch` statement provides a more concise and organized way to handle multiple discrete values. For example:
```cpp
#include <iostream>

void printDigitName(int x)
{
    if (x == 1)
        std::cout << "One";
    else if (x == 2)
        std::cout << "Two";
    else if (x == 3)
        std::cout << "Three";
    else
        std::cout << "Unknown";
}

int main()
{
    printDigitName(2);
    std::cout << '\n';

    return 0;
}
```
can be rewritten using a `switch` statement as follows:
```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x)
    {
        case 1:
            std::cout << "One";
            break;
        case 2:
            std::cout << "Two";
            break;
        case 3:
            std::cout << "Three";
            break;
        default:
            std::cout << "Unknown";
            break;
    }
}

int main()
{
    printDigitName(2);
    std::cout << '\n';
    return 0;
}
```
In this example, the `switch` statement evaluates the value of `x` and executes the corresponding `case` block based on the value. If none of the specified cases match, the `default` block is executed.

The **`switch` statement** is a control flow statement that allows a variable to be tested for equality against a list of values, called **cases**. Each case corresponds to a specific value that the variable can take. The syntax of a `switch` statement is as follows:
```cpp
switch (variable)
{
    case value1:
        // code to be executed if variable == value1
        break;
    case value2:
        // code to be executed if variable == value2
        break;
    // more cases...
    default:
        // code to be executed if variable does not match any case
        break;
}
```
The `break` statement is used to exit the `switch` statement after executing a case block. If `break` is omitted, the program will continue executing the subsequent case blocks (this is called "fall-through").

#### Starting a switch:
We start a `switch` statement with the `switch` keyword, followed by parentheses containing the variable to be tested. The variable must be of an **integral** or **enumeration type** (e.g., `int`, `char`, `enum`). Expressions that evaluate to floating point types, strings, or other non-integral types are not allowed.

> **Note:** In C++, the variable used in a `switch` statement must be of **integral** or **enumeration type**. This means that types like `float`, `double`, or `std::string` cannot be used directly in a `switch` statement.

Following the variable, we open a block with curly braces `{}` to contain the `case` labels and their corresponding code blocks.

#### Case labels:
Each `case` label specifies a value that the variable can be compared against. If the variable matches the value of a `case` label, the code block associated with that case is executed, starting from the next line after the `case` label, and running sequentially until a `break` statement is encountered or the end of the `switch` block is reached. For example:
```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x) // x is evaluated to produce value 2
    {
    case 1:
        std::cout << "One";
        return;
    case 2: // which matches the case statement here
        std::cout << "Two"; // so execution starts here
        return; // and then we return to the caller
    case 3:
        std::cout << "Three";
        return;
    default:
        std::cout << "Unknown";
        return;
    }
}

int main()
{
    printDigitName(2);
    std::cout << '\n';

    return 0;
}
```
Output:
```
Two
```
In this example, when `printDigitName(2)` is called, the `switch` statement evaluates `x` (which is `2`) and matches it to the `case 2:` label. The code block following `case 2:` is executed, printing "Two".

There is no practical limit to the number of `case` labels you can have in a `switch` statement, but having too many can make the code harder to read and maintain. The only requirement is that each `case` label must have a unique constant value.
```cpp
switch (x)
{
case 54:
case 54:  // error: already used value 54!
case '6': // error: '6' converts to integer value 54, which is already used
}
```

#### Default label:
The `default` label is optional and serves as a catch-all case that is executed when none of the specified `case` labels match the value of the variable. It is similar to the `else` clause in an `if-else` statement. The `default` label is typically placed at the end of the `switch` block, but it can appear anywhere within the block. For example:
```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x) // x is evaluated to produce value 5
    {
    case 1:
        std::cout << "One";
        return;
    case 2:
        std::cout << "Two";
        return;
    case 3:
        std::cout << "Three";
        return;
    default: // which does not match to any case labels
        std::cout << "Unknown"; // so execution starts here
        return; // and then we return to the caller
    }
}

int main()
{
    printDigitName(5);
    std::cout << '\n';

    return 0;
}
```
Output:
```
Unknown
```
In this example, when `printDigitName(5)` is called, the `switch` statement evaluates `x` (which is `5`) and finds that it does not match any of the specified `case` labels. Therefore, the code block following the `default` label is executed, printing "Unknown".

> **Best Practice:** Always include a `default` case in your `switch` statements to handle unexpected values and improve code robustness, and place it at the end of the `switch` block for better readability.

#### No matching case label and no default case:
If a `switch` statement does not have a matching `case` label for the value of the variable and does not include a `default` case, the program simply continues execution after the `switch` block without executing any code within the `switch`. For example:
```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x) // x is evaluated to produce value 5
    {
    case 1:
        std::cout << "One";
        return;
    case 2:
        std::cout << "Two";
        return;
    case 3:
        std::cout << "Three";
        return;
    // no matching case exists and there is no default case
    }

    // so execution continues here
    std::cout << "Hello";
}

int main()
{
    printDigitName(5);
    std::cout << '\n';

    return 0;
}
```
Output:
```
Hello
```
In this example, when `printDigitName(5)` is called, the `switch` statement evaluates `x` (which is `5`) and finds that it does not match any of the specified `case` labels. Since there is no `default` case, the program continues execution after the `switch` block, printing "Hello".

#### Taking a break:
In the examples above, we used `return` statements to exit the `switch` block after executing a case, since we were inside a function. However, in many (most) cases, you will want to use the `break` statement to exit the `switch` block and continue executing code after the `switch`. The `break` statement is used to terminate a `switch` case and prevent "fall-through" to subsequent cases. For example:
```cpp
#include <iostream>

void printDigitName(int x)
{
    switch (x) // x evaluates to 3
    {
    case 1:
        std::cout << "One";
        break;
    case 2:
        std::cout << "Two";
        break;
    case 3:
        std::cout << "Three"; // execution starts here
        break; // jump to the end of the switch block
    default:
        std::cout << "Unknown";
        break;
    }

    // execution continues here
    std::cout << " Ah-Ah-Ah!";
}

int main()
{
    printDigitName(3);
    std::cout << '\n';

    return 0;
}
```
Output:
```
Three Ah-Ah-Ah!
```
In this example, when `printDigitName(3)` is called, the `switch` statement evaluates `x` (which is `3`) and matches it to the `case 3:` label. The code block following `case 3:` is executed, printing "Three". The `break` statement then exits the `switch` block, and execution continues with the code after the `switch`, printing " Ah-Ah-Ah!".

> **Best Practice:** Every case block should typically end with a `break` or `return` statement to prevent unintended fall-through behavior, unless fall-through is explicitly desired and documented.

#### Labels are conventionally not indented:
In C++, it is common practice to not indent `case` and `default` labels within a `switch` statement. This convention improves readability by clearly distinguishing the labels from the code blocks associated with them. For example:
```cpp
switch (variable)
{
case value1:
    // code to be executed if variable == value1
    break;
case value2:
    // code to be executed if variable == value2
    break;
// more cases...
default:
    // code to be executed if variable does not match any case
    break;
}
```
This style makes it easier to identify the different cases and their associated code blocks at a glance.

#### Switch vs if-else:
Both `switch` statements and `if-else` chains can be used to handle multiple discrete values of a variable. However, in general, `switch` statements are preferred when there is a single expression (with a non-boolean integral or enumeration type) we want to evaluate for equality against a small set of constant values. `if-else` chains are more flexible and can handle a wider range of conditions, including ranges and complex boolean expressions.

#### Summary:
- Use `switch` statements for handling multiple discrete values of a single integral or enumeration variable.
- Always include a `default` case to handle unexpected values.
- End each case block with a `break` or `return` statement to prevent unintended fall-through.
- Follow the convention of not indenting `case` and `default` labels for improved readability.


---

### S06 — 8.6 Switch fall-through and scoping
This section discusses the concept of "fall-through" in `switch` statements and how to manage variable scoping within `case` blocks.

#### Fall-through behavior:
When a switch expression matches a case label, the program executes the first statement following the matched case label and continues executing subsequent statements in the switch block until:
- The end of the switch block is reached, or
- Another control flow statement (like `break`, `return`, or `goto`) is encountered.

Thus, without a `break` or `return` statement at the end of a case block, execution will "fall through" to the next case block, executing its statements as well. For example:
```cpp
#include <iostream>

int main()
{
    switch (2)
    {
    case 1: // Does not match
        std::cout << 1 << '\n'; // Skipped
    case 2: // Match!
        std::cout << 2 << '\n'; // Execution begins here
    case 3:
        std::cout << 3 << '\n'; // This is also executed
    case 4:
        std::cout << 4 << '\n'; // This is also executed
    default:
        std::cout << 5 << '\n'; // This is also executed
    }

    return 0;
}
```
Output:
```
2
3
4
5
```
In this example, when the switch expression matches `case 2:`, execution starts there and continues through cases 3, 4, and the default case because there are no `break` statements to stop the flow.

#### The [[fallthrough]] attribute (C++17 and later):
To explicitly tell the compiler that fall-through behavior is intentional, C++17 introduced the `[[fallthrough]]` attribute. This attribute can be placed at the end of a case block to indicate that falling through to the next case is deliberate. For example:
```cpp
#include <iostream>

int main()
{
    switch (2)
    {
    case 1:
        std::cout << 1 << '\n';
        break;
    case 2:
        std::cout << 2 << '\n'; // Execution begins here
        [[fallthrough]]; // intentional fallthrough -- note the semicolon to indicate the null statement
    case 3:
        std::cout << 3 << '\n'; // This is also executed
        break;
    }

    return 0;
}
```
Output:
```
2
3
```
In this example, the `[[fallthrough]]` attribute indicates that the fall-through from `case 2:` to `case 3:` is intentional, helping to improve code clarity and prevent compiler warnings about unintentional fall-through.

> **Best Practice:** Use the `[[fallthrough]]` attribute when you intend to allow fall-through behavior in a `switch` statement to improve code clarity and prevent compiler warnings.

#### Sequential case labels:
You can use logical OR to combine multiple tests into a single statement:
```cpp
bool isVowel(char c)
{
    return (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' ||
        c=='A' || c=='E' || c=='I' || c=='O' || c=='U');
}
```
However, this suffers of the same issue: `c` gets evaluated mutiple times. A better approach is to use sequential case labels in a `switch` statement:
```cpp
bool isVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
        return true;
    default:
        return false;
    }
}
```
In this example, if `c` matches any of the vowel characters, the program will execute the code block following the last case label, returning `true`. If `c` does not match any of the vowel characters, the program will execute the `default` case, returning `false`. In this case, fall-through behavior is intentional and allows for a more concise implementation.

#### Labels do not define new scope:
In `switch` statements, the statements after each label (`case` or `default`) do not create a new scope, but keeps the same scope as the `switch` block itself.

#### Variable declaration and initialization inside case statements:
You can declare or define (but not initialize) variables inside the `switch` block, both before and after case labels:
```cpp
switch (1)
{
    int a; // okay: definition is allowed before the case labels
    int b{ 5 }; // illegal: initialization is not allowed before the case labels

case 1:
    int y; // okay but bad practice: definition is allowed within a case
    y = 4; // okay: assignment is allowed
    break;

case 2:
    int z{ 4 }; // illegal: initialization is not allowed if subsequent cases exist
    y = 5; // okay: y was declared above, so we can use it here too
    break;

case 3:
    break;
}
```
This shows that a variable defined inside a case block is in scope for the entire `switch` block, including other case blocks. However, initializing a variable inside a case block is not allowed if there are subsequent case blocks, because the initialization would be skipped if the switch expression matches an earlier case.
To work around this limitation, you can use an explicit block (curly braces) to create a new scope for variable initialization:
```cpp
switch (1)
{
case 1:
{ // note addition of explicit block here
    int x{ 4 }; // okay, variables can be initialized inside a block inside a case
    std::cout << x;
    break;
}

default:
    std::cout << "default case\n";
    break;
}
```
In this way, the variable `x` is initialized within its own scope, and there are no conflicts with other case blocks.

#### Summary:
- Be aware of fall-through behavior in `switch` statements and use `break` or `return` statements to control the flow.
- Use the `[[fallthrough]]` attribute to indicate intentional fall-through behavior.
- Remember that case labels do not create new scopes; use explicit blocks to manage variable initialization within case blocks.


---

### S07 — 8.7 Goto statements
The next control flow statement we will discuss is the **unconditional jump statement**, commonly known as the `goto` statement. The `goto` statement allows you to jump to a specific labeled statement within the same function. However, its use is generally discouraged in modern programming due to potential negative impacts on code readability and maintainability. Here is an exampe:
```cpp
#include <iostream>
#include <cmath> // for sqrt() function

int main()
{
    double x{};
tryAgain: // this is a statement label
    std::cout << "Enter a non-negative number: ";
    std::cin >> x;

    if (x < 0.0)
        goto tryAgain; // this is the goto statement

    std::cout << "The square root of " << x << " is " << std::sqrt(x) << '\n';
    return 0;
}
```
Output:
```
Enter a non-negative number: -4
Enter a non-negative number: 9
The square root of 9 is 3
```
In this program, if the user enters a negative number, the `goto` statement transfers control back to the `tryAgain` label, prompting the user to enter a non-negative number again. In this way we can continually ask the user for input until a valid number is provided.

#### Statement labels have function scope:
A statement label is an identifier followed by a colon (`:`) that marks a specific location in the code. Statement labels have function scope, meaning they can be accessed from anywhere within the same function. However, they cannot be accessed from outside the function in which they are defined. For example:
```cpp
#include <iostream>

void exampleFunction()
{
    goto myLabel; // okay: myLabel is in the same function

myLabel:
    std::cout << "This is myLabel\n";
}

int main()
{
    // goto myLabel; // error: myLabel is not in scope here

    exampleFunction();

    return 0;
}
```
In this example, the `myLabel` label is defined within the `exampleFunction`, and the `goto` statement can access it within the same function. However, attempting to use `goto myLabel;` in the `main` function would result in a compilation error because `myLabel` is not in scope there.

#### Avoiding spaghetti code:
The use of `goto` statements can lead to "spaghetti code," which is code that is difficult to read and maintain due to its complex and tangled control flow. This can make it challenging to understand the program's logic and can lead to errors during maintenance or modification. For example:
```
#include <iostream>

int main()
{
    int x{};
    std::cout << "Enter a number between 1 and 10: ";
    std::cin >> x;

    if (x < 1)
        goto error;
    if (x > 10)
        goto error;

    std::cout << "You entered a valid number: " << x << '\n';
    return 0;

error:
    std::cout << "Invalid input. Please enter a number between 1 and 10.\n";
    return 1;
}
```
In this example, the use of `goto` statements can make the control flow harder to follow, especially as the program grows in complexity. A better approach would be to use structured control flow statements like `if-else` or loops to handle input validation.

#### Alternatives to goto:
In most cases, you can achieve the same functionality as `goto` statements using structured control flow statements such as loops and functions. For example, the previous example can be rewritten using a loop:
```cpp
#include <iostream>

int main()
{
    int x{};
    while (true)
    {
        std::cout << "Enter a number between 1 and 10: ";
        std::cin >> x;

        if (x >= 1 && x <= 10)
            break; // valid input, exit the loop

        std::cout << "Invalid input. Please enter a number between 1 and 10.\n";
    }

    std::cout << "You entered a valid number: " << x << '\n';
    return 0;
}
```
In this version, a `while` loop is used to repeatedly prompt the user for input until a valid number is entered, eliminating the need for `goto` statements and improving code readability.

> **Best Practice:** Avoid using `goto` statements in your code. Instead, use structured control flow statements like loops and functions to manage program flow in a clear and maintainable way.

#### Summary:
- The `goto` statement allows for unconditional jumps to labeled statements within the same function.
- Statement labels have function scope and cannot be accessed outside their defining function.
- Avoid using `goto` statements to prevent "spaghetti code" and improve code readability.
- Use structured control flow statements like loops and functions as alternatives to `goto` for better maintainability.


---

### S08 — 8.8 Introduction to loops and while statements
In this section, we will introduce loops, which are control flow statements that allow you to execute a block of code repeatedly based on a condition. The most basic type of loop in C++ is the `while` loop.

#### Introduction to loops:
A loop is a control flow statement that allows you to execute a block of code multiple times based on a condition. Loops are useful for tasks that require repetition, such as iterating over a collection of items, performing calculations until a certain condition is met, or repeatedly prompting the user for input until valid data is provided. For example, consider the task of printing the numbers from 1 to 10. With the instruments you have learned so far, it would be pretty redundant to write:
```cpp
#include <iostream>

int main()
{
    std::cout << 1 << '\n';
    std::cout << 2 << '\n';
    std::cout << 3 << '\n';
    std::cout << 4 << '\n';
    std::cout << 5 << '\n';
    std::cout << 6 << '\n';
    std::cout << 7 << '\n';
    std::cout << 8 << '\n';
    std::cout << 9 << '\n';
    std::cout << 10 << '\n';

    return 0;
}
```
or 
```cpp
#include <iostream>

int main()
{
    int number{1};

    std::cout << "1 2 3 4 5 6 7 8 9 10\n";
    return 0;
}
```
Doing this is not only tedious, but also error-prone and inflexible. If you wanted to print numbers from 1 to 100, you would have to write a lot more code. Instead, we can use a loop to achieve the same result in a more efficient and flexible way.

#### While statements:
The `while` loop is a control flow statement that repeatedly executes a block of code as long as a specified condition is true. The syntax of a `while` loop is as follows:
```cpp
while (condition)
{
    // code to be executed repeatedly as long as condition is true
}
```
The `condition` is a boolean expression that is evaluated before each iteration of the loop. If the condition evaluates to `true`, the code block inside the loop is executed. After executing the code block, the condition is evaluated again. This process continues until the condition evaluates to `false`, at which point the loop terminates, and the program continues with the code following the loop.

Here is an example of using a `while` loop to print the numbers from 1 to 10:
```cpp
#include <iostream>

int main()
{
    int number{1}; // initialize number to 1

    while (number <= 10) // condition: continue while number is less than or equal to 10
    {
        std::cout << number << ' '; // print the current value of number
        ++number; // increment number by 1
    }

    return 0;
}
```
Output:
```
1 2 3 4 5 6 7 8 9 10 
```
In this example, the `while` loop continues to execute as long as the variable `number` is less than or equal to 10. Inside the loop, the current value of `number` is printed, and then `number` is incremented by 1. This process repeats until `number` becomes 11, at which point the loop terminates.

#### While statements that evaluate to false initially:
If the condition of a `while` loop evaluates to `false` initially, the code block inside the loop will not be executed at all. For example:
```cpp
#include <iostream>

int main()
{
    int number{11}; // initialize number to 11

    while (number <= 10) // condition: continue while number is less than or equal to 10
    {
        std::cout << number << ' '; // this line will not be executed
        ++number; // this line will not be executed
    }

    std::cout << "Loop has ended.\n";

    return 0;
}
```
Output:
```
Loop has ended.
```
In this example, since the initial value of `number` is 11, the condition `number <= 10` evaluates to `false` right away. As a result, the code block inside the `while` loop is never executed, and the program immediately continues with the code following the loop.

#### Infinite loops:
An infinite loop is a loop that continues to execute indefinitely because the condition always evaluates to `true`. Infinite loops can occur unintentionally due to a logic error, or they can be used intentionally in certain scenarios, such as in event-driven programming or server applications that need to run continuously. Here is an example of an infinite loop:
```cpp
#include <iostream>

int main()
{
    while (true) // condition always true
    {
        std::cout << "This loop will run forever!\n";
    }

    return 0;
}
```
In this example, the condition `true` always evaluates to `true`, so the loop will continue to execute indefinitely, printing "This loop will run forever!" repeatedly.

In the previous example, we would have had an infinite loop if we had forgotten to increment the `number` variable inside the loop:
```cpp
#include <iostream>

int main()
{
    int number{1}; // initialize number to 1

    while (number <= 10) // condition: continue while number is less than or equal to 10
    {
        std::cout << number << ' '; // print the current value of number
        // missing increment of number here
    }

    return 0;
}
```
This would result in an infinite loop because `number` would always remain `1`, causing the condition `number <= 10` to always evaluate to `true`.

#### Intentional infinite loops:
In some cases, infinite loops are used intentionally, such as in programs that need to run continuously until explicitly terminated. For example, a server application might use an infinite loop to continuously listen for incoming requests. Here is an example of an intentional infinite loop:
```cpp
#include <iostream>

int main()
{
    while (true) // intentional infinite loop
    {
        // this loop will execute indefinitely until the program is terminated
        std::cout << "Server is running...\n";
        // simulate some server work here
    }

    return 0;
}
```

The only way to exit an infinite loop is to use a control flow statement like `break`, `return`, or to terminate the program externally (e.g., by pressing Ctrl+C in the terminal). For example:
```cpp
#include <iostream>

int main()
{

    while (true) // infinite loop
    {
        std::cout << "Loop again (y/n)? ";
        char c{};
        std::cin >> c;

        if (c == 'n')
            return 0;
    }

    return 0;
}
```
In this example, the infinite loop continues to prompt the user until they enter 'n', at which point the program exits using the `return` statement.

> **Best Practice:** Be cautious when creating infinite loops. Ensure that there is a clear exit condition or mechanism to terminate the loop when necessary. Prefer `while(true)` for intentional infinite loops to clearly indicate the intent.

#### Unintentional infinite loops:
Unintentional infinite loops often occur due to logic errors, such as forgetting to update the loop control variable or using an incorrect condition. An additional example, would be unintentionally placing a semicolumn `;` immediately after the `while` condition, which creates a null statement as the loop body:
```cpp
#include <iostream>

int main()
{
    int number{1}; // initialize number to 1

    while (number <= 10); // oops, semicolon creates a null statement here
    {
        std::cout << number << ' '; // this block is not part of the loop
        ++number; // this line is not part of the loop
    }

    return 0;
}
```
In this example, the semicolon after the `while` condition creates a null statement as the loop body, causing the loop to execute indefinitely without executing the code block that follows. The code block after the loop is not part of the loop and will only execute once after the loop terminates (which it never does in this case). This program will run as if we had written:
```cpp
#include <iostream>

int main()
{
    int number{1}; // initialize number to 1

    while (number <= 10) // infinite loop with no body
        ; // null statement

    {
        std::cout << number << ' '; // this block is not part of the loop
        ++number; // this line is not part of the loop
    }

    return 0;
}
```
To avoid such mistakes, always ensure that the loop body is properly defined and that the loop control variable is updated correctly within the loop.

Unlike if-statements, for which a semicolon after the condition is always a mistake, a semicolon after a while-loop condition is not necessarily an error. It can be used intentionally like:
```cpp
while (keepRunning());
```
In this case, the semicolon indicates that the loop body is a null statement, and the loop will continue to evaluate the `keepRunning()` function until it returns `false`.

> **Note:** Be careful with semicolons after `while` conditions, as they can lead to unintended infinite loops if not used intentionally or properly.

#### Loop variables and naming:
A **loop variable** is a variable that is used to control the execution of a loop. It is typically initialized before the loop starts and is updated within the loop body to eventually terminate the loop. In the previous examples, the variable `number` served as the loop variable.

When naming loop variables, it is important to choose descriptive names that convey their purpose. Common conventions include using names like `i`, `j`, or `k` for simple loops, especially in nested loops, or more descriptive names like `index`, `count`, or `item` for loops that iterate over collections or perform specific tasks. One issue with these names, is when using the search function in your IDE, as they are single letters, they may match many other occurrences in your code. To avoid this, consider using slightly longer names that are still concise, such as `idx`, `cnt`, or `itemNum`.

Generally, loop variables are of type `int` or `size_t`, but they can be of any type that supports the necessary operations for the loop's logic (e.g., `char`).

#### Integral loop variables should be signed:
When using integral types as loop variables, it is generally recommended to use signed types (like `int`) rather than unsigned types (like `unsigned int` or `size_t`). This is because signed types can represent both positive and negative values, which can help prevent unexpected behavior when performing arithmetic operations or comparisons. For example, if you use an unsigned type as a loop variable and perform a decrement operation that results in a negative value, it will wrap around to a large positive value, potentially causing an infinite loop or other logic errors. Using signed types helps avoid such issues and makes the code more predictable. For example:
```cpp
#include <iostream>

int main()
{
    unsigned int count{ 10 }; // note: unsigned

    // count from 10 down to 0
    while (count >= 0)
    {
        if (count == 0)
        {
            std::cout << "blastoff!";
        }
        else
        {
            std::cout << count << ' ';
        }
        --count;
    }

    std::cout << '\n';

    return 0;
}
```
Output:
```
10 9 8 7 6 5 4 3 2 1 blastoff! 4294967295 ... infinite loop continues
```
In this example, using an unsigned type for `count` leads to an infinite loop because when `count` is decremented from `0`, it wraps around to a large positive value (typically `4294967295` on a 32-bit system), causing the condition `count >= 0` to always evaluate to `true`.To avoid this issue, it is better to use a signed type for the loop variable:
```cpp
#include <iostream>

int main()
{
    int count{ 10 }; // note: signed

    // count from 10 down to 0
    while (count >= 0)
    {
        if (count == 0)
        {
            std::cout << "blastoff!";
        }
        else
        {
            std::cout << count << ' ';
        }
        --count;
    }

    std::cout << '\n';

    return 0;
}
```
Output:
```
10 9 8 7 6 5 4 3 2 1 blastoff!
```
In this corrected example, using a signed type for `count` allows the loop to terminate correctly when `count` reaches `-1`, preventing the infinite loop issue.

> **Best Practice:** Use signed integral types (like `int`) for loop variables to avoid unexpected behavior with arithmetic operations and comparisons.

#### Doing something every N iterations:
Each time a loop executes, it is called an **iteration**. Sometimes, you may want to perform a specific action every N iterations of a loop. This can be achieved by using the modulus operator (`%`) to check if the current iteration count is divisible by N. For example, to print a message every 5 iterations:
```cpp
#include <iostream>

// Iterate through every number between 1 and 50
int main()
{
    int count{ 1 };
    while (count <= 50)
    {
        // print the number (pad numbers under 10 with a leading 0 for formatting purposes)
        if (count < 10)
        {
            std::cout << '0';
        }

        std::cout << count << ' ';

        // if the loop variable is divisible by 10, print a newline
        if (count % 10 == 0)
        {
            std::cout << '\n';
        }

        // increment the loop counter
        ++count;
    }

    return 0;
}
```
Output:
```
01 02 03 04 05 06 07 08 09 10
11 12 13 14 15 16 17 18 19 20
21 22 23 24 25 26 27 28 29 30
31 32 33 34 35 36 37 38 39 40
41 42 43 44 45 46 47 48 49 50
```
In this example, the loop iterates through numbers from 1 to 50. The condition `if (count % 10 == 0)` checks if the current value of `count` is divisible by 10, and if so, it prints a newline character to format the output into rows of 10 numbers each.

#### Nested while loops:
A nested loop is a loop that exists inside another loop. The inner loop is executed completely for each iteration of the outer loop. Nested loops are useful for tasks that require multiple levels of iteration, such as iterating over multi-dimensional data structures (like matrices) or generating combinations of values. Here is an example of nested `while` loops:
```cpp
#include <iostream>

void printUpto(int outer)
{
    // loop between 1 and outer
    // note: inner will be created and destroyed at the end of the block
    int inner{ 1 };
    while (inner <= outer)
    {
        std::cout << inner << ' ';
        ++inner;
    }
} // inner destroyed here

int main()
{
    // outer loops between 1 and 5
    int outer{ 1 };
    while (outer <= 5)
    {
        // For each iteration of the outer loop, the code in the body of the loop executes once

        // This function prints numbers between 1 and outer
        printUpto(outer);

        // print a newline at the end of each row
        std::cout << '\n';
        ++outer;
    }

    return 0;
}
```
Output:
```
1
1 2
1 2 3
1 2 3 4
1 2 3 4 5
```
In this example, the outer loop iterates from 1 to 5. For each iteration of the outer loop, the `printUpto` function is called, which contains an inner loop that prints numbers from 1 up to the current value of `outer`. This results in a triangular pattern of numbers being printed.

Now, a more confusing example with nested `while` loops:
```cpp
#include <iostream>

int main()
{
    // outer loops between 1 and 5
    int outer{ 1 };
    while (outer <= 5)
    {
        // For each iteration of the outer loop, the code in the body of the loop executes once

        // inner loops between 1 and outer
        // note: inner will be created and destroyed at the end of the block
        int inner{ 1 };
        while (inner <= outer)
        {
            std::cout << inner << ' ';
            ++inner;
        }

        // print a newline at the end of each row
        std::cout << '\n';
        ++outer;
    } // inner destroyed here

    return 0;
}
```
Output:
```
1
1 2
1 2 3
1 2 3 4
1 2 3 4 5
```
In this example, the outer loop iterates from 1 to 5. For each iteration of the outer loop, an inner loop is created that prints numbers from 1 up to the current value of `outer`. This results in the same triangular pattern of numbers being printed as in the previous example. The `inner` variable is created and destroyed within the scope of the outer loop, ensuring that it starts fresh for each iteration of the outer loop.

#### Summary:
- Loops allow you to execute a block of code repeatedly based on a condition.
- The `while` loop continues executing as long as its condition evaluates to `true`.
- Be cautious of infinite loops and ensure there is a clear exit condition.
- Use signed integral types for loop variables to avoid unexpected behavior.
- You can perform actions every N iterations using the modulus operator `%`.
- Nested loops allow for multiple levels of iteration, useful for multi-dimensional data structures.


---

### S09 — 8.9 Do while statements
Consider the case where you want to execute a block of code at least once, and then continue executing it as long as a certain condition is true. In such cases, the `do while` loop is useful, that works better than a regular `while` loop for this purpose.

#### Do while statements:
The `do while` loop is a control flow statement that executes a block of code at least once, and then continues to execute the block as long as a specified condition evaluates to `true`. The syntax of a `do while` loop is as follows:
```cpp
do
{
    // code to be executed at least once and repeatedly as long as condition is true
} while (condition);
```
The key difference between a `do while` loop and a regular `while` loop is that the condition is evaluated after the code block is executed, ensuring that the code block is executed at least once, regardless of the initial condition.

For example, consider the following `do while` loop that prompts the user to enter a positive number:
```cpp
#include <iostream>

int main()
{
    int number{};

    do
    {
        std::cout << "Enter a positive number: ";
        std::cin >> number;
    } while (number <= 0); // continue prompting until a positive number is entered

    std::cout << "You entered: " << number << '\n';

    return 0;
}
```
In this example, the `do while` loop prompts the user to enter a positive number. The loop continues to execute as long as the entered number is less than or equal to zero. Since the condition is checked after the code block, the user is guaranteed to be prompted at least once.

Another example:
```cpp
#include <iostream>

int main()
{
    // selection must be declared outside of the do-while-loop, so we can use it later
    int selection {};

    do
    {
        std::cout << "Please make a selection: \n";
        std::cout << "1) Addition\n";
        std::cout << "2) Subtraction\n";
        std::cout << "3) Multiplication\n";
        std::cout << "4) Division\n";
        std::cin >> selection;
    }
    while (selection < 1 || selection > 4);

    // do something with selection here
    // such as a switch statement

    std::cout << "You selected option #" << selection << '\n';

    return 0;
}
```
In this example, the `do while` loop prompts the user to make a selection from a menu of options. The loop continues to execute as long as the entered selection is less than 1 or greater than 4, ensuring that the user is prompted at least once and only valid selections are accepted.

Notice that the variable `selection` is declared outside of the `do while` loop so that it can be used after the loop has completed.

> **Note:** Declare variables that need to be accessed after the loop outside of the `do while` loop to ensure they are in scope.

#### Summary:
- The `do while` loop executes a block of code at least once and continues executing it as long as the condition evaluates to `true`.
- The condition is evaluated after the code block, ensuring at least one execution.
- Declare variables that need to be accessed after the loop outside of the `do while` loop.


---

### S10 — 8.10 For statements
By far the most commonly used loop in C++ is the `for` loop. It is especially useful when the number of iterations is known beforehand. As for C++11, there are two different types of `for` loops: the traditional `for` loop and the range-based `for` loop. We will cover here the traditional `for` loop, while range-based `for` loops will be covered in a next more advanced module.

#### For statements:
The `for` loop is a control flow statement that allows you to execute a block of code a specific number of times. It is particularly useful when the number of iterations is known beforehand. The syntax of a traditional `for` loop is as follows:
```cpp
for (initialization; condition; update)
{
    statement; // code to be executed repeatedly as long as condition is true
}
```

The `for` loop can be seen as a more compact way of writing a `while` loop, as it combines initialization, condition checking, and updating in a single line:
```cpp
{ // note the block here
    initialization;  // executed once before the loop starts
    while (condition) // condition checked before each iteration
    {
        statement;    // code to be executed
        update;       // executed after each iteration
    }
} // end of block, variables declared in initialization go out of scope here
```

#### Evaluation of for-statements:
A for-statement is evaluated in three parts:
1. **Initialization:** This part is executed once at the beginning of the loop. It is typically used to initialize a loop control variable, that has loop scope (i.e., it is only accessible within the loop).
2. **Condition:** This part is evaluated before each iteration of the loop. If the condition evaluates to `true`, the code block inside the loop is executed. If it evaluates to `false, the loop terminates.
3. **Update:** This part is executed after each iteration of the loop. It is typically used to update the loop control variable.

Here is an example of a simple `for` loop:
```cpp
#include <iostream>

int main()
{
    for (int i{ 1 }; i <= 10; ++i)
        std::cout << i << ' ';

    std::cout << '\n';

    return 0;
}
```
Output:
```
1 2 3 4 5 6 7 8 9 10 
```
In this example:
1. The initialization `int i{ 1 };` initializes the loop control variable `i` to `1`.
2. The condition `i <= 10;` checks if `i` is less than or equal to `10` before each iteration.
3. The update `++i` increments ``i` by `1` after each iteration.

#### More for-loop examples:
Here is an example of a function that uses `for` loop to calculate integer exponentiation:
```cpp
#include <cstdint> // for fixed-width integers

// returns the value base ^ exponent -- watch out for overflow!
std::int64_t pow(int base, int exponent)
{
    std::int64_t total{ 1 };

    for (int i{ 0 }; i < exponent; ++i)
        total *= base;

    return total;
}
```
In this example, the `for` loop iterates `exponent` times, multiplying the `total` by `base` in each iteration to calculate the power.

Here an example where we decrement the loop variable:
```cpp
#include <iostream>

int main()
{
    for (int i{ 9 }; i >= 0; --i)
        std::cout << i << ' ';

    std::cout << '\n';

    return 0;
}
```
Output:
```
9 8 7 6 5 4 3 2 1 0 
```
In this example, the `for` loop initializes `i` to `9`, checks if `i` is greater than or equal to `0`, and decrements `i` by `1` in each iteration, printing the numbers from `9` down to `0`.

Additionally, we can increment/decrement by more than 1:
```cpp
#include <iostream>

int main()
{
    for (int i{ 0 }; i <= 20; i += 2)
        std::cout << i << ' ';

    std::cout << '\n';

    return 0;
}
```
Output:
```
0 2 4 6 8 10 12 14 16 18 20 
```
In this example, the `for` loop increments `i` by `2` in each iteration, printing even numbers from `0` to `20`.


#### The perils of `operator!=` in for-loop conditions:
When writing a loop condition involving a value, we can use either `operator<` or `operator!=`. For example, the following are the same:
```cpp
#include <iostream>

int main()
{
    for (int i { 0 }; i < 10; ++i) // uses <
         std::cout << i;

    for (int i { 0 }; i != 10; ++i) // uses !=
         std::cout << i;

     return 0;
}
```
However, using `operator!=` can lead to unexpected behavior in certain scenarios, especially when dealing with floating-point numbers or when the loop variable is modified in a way that could skip the exact value being compared against (`i` skip the exact value of `10`). For example:
```cpp
#include <iostream>

int main()
{
    for (int i { 0 }; i < 10; ++i) // uses <, still terminates
    {
         std::cout << i;
         if (i == 9) ++i; // jump over value 10
    }

    for (int i { 0 }; i != 10; ++i) // uses !=, infinite loop
    {
         std::cout << i;
         if (i == 9) ++i; // jump over value 10
    }

     return 0;
}
```
In this example, the first loop using `operator<` terminates correctly, while the second loop using `operator!=` results in an infinite loop because when `i` is incremented from `9` to `11`, it skips the value `10`, causing the condition `i != 10` to always evaluate to `true`.

> **Best Practice:** Prefer using `operator<` or `operator>` over `operator!=` in loop conditions to avoid potential infinite loops or unexpected behavior.

#### Off-by-one errors:
An off-by-one error is a common programming mistake that occurs when a loop iterates one time too many or one time too few. This can happen due to incorrect initialization, condition, or update (pre-increment vs post-increment) of the loop control variable. For example:
```cpp
#include <iostream>

int main()
{
    // off-by-one error: should be i <= 10
    for (int i{ 1 }; i < 10; ++i)
        std::cout << i << ' ';

    std::cout << '\n';

    return 0;
}
```
Output:
```
1 2 3 4 5 6 7 8 9 
```
In this example, the loop is intended to print numbers from `1` to `10`, but due to the condition `i < 10`, it only prints up to `9`, resulting in an off-by-one error. The correct condition should be `i <= 10` to include `10` in the output.

#### Omitted expressions in for-loops:
In C++, the `for` loop can have omitted expressions for initialization, condition, and update. This can lead to different behaviors:
```cpp
#include <iostream>

int main()
{
    int i{ 0 };
    for ( ; i < 10; ) // no init-statement or end-expression
    {
        std::cout << i << ' ';
        ++i;
    }

    std::cout << '\n';

    return 0;
}
```
Output:
```
0 1 2 3 4 5 6 7 8 9 
```
In this example, the initialization and update expressions are omitted. The loop still functions correctly because the variable `i` is initialized before the loop, and the update (`++i`) is performed inside the loop body.

Or, ofr example, defining an infinite loop:
```cpp
for ( ; ; ) // infinite loop
{
    // code to be executed indefinitely
}
```
This loop will run indefinitely because there is no condition to terminate it, and it is equivalent to `while (true)`.

#### For-loops with multiple counters:
C++ allows you to use multiple loop control variables in a `for` loop by separating them with commas. This can be useful when you need to track multiple values simultaneously. Here is an example:
```cpp
#include <iostream>

int main()
{
    for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
        std::cout << x << ' ' << y << '\n';

    return 0;
}
```
Output:
```
0 9
1 8
2 7
3 6
4 5
5 4
6 3
7 2
8 1
9 0
```
In this example, the `for` loop initializes two variables, `x` and `y`. The loop continues as long as `x` is less than `10`, incrementing `x` and decrementing `y` in each iteration, printing their values.

#### Nested for-loops:
A nested `for` loop is a `for` loop that exists inside another `for` loop. The inner loop is executed completely for each iteration of the outer loop. Nested loops are useful for tasks that require multiple levels of iteration, such as iterating over multi-dimensional data structures (like matrices) or generating combinations of values. Here is an example of nested `for` loops:
```cpp
#include <iostream>

int main()
{
	for (char c{ 'a' }; c <= 'e'; ++c) // outer loop on letters
	{
		std::cout << c; // print our letter first

		for (int i{ 0 }; i < 3; ++i) // inner loop on all numbers
			std::cout << i;

		std::cout << '\n';
	}

	return 0;
}
```
Output:
```
a012
b012
c012
d012
e012
```
In this example, the outer loop iterates over the letters from 'a' to 'e. For each letter, the inner loop iterates from `0` to `2`, printing the numbers alongside the letter.

#### Variables used only inside a loop should be deifned inside the loop:
When a variable is only needed within the scope of a loop, it is best practice to define it inside the loop. This limits the variable's scope to the loop itself, reducing potential naming conflicts and improving code readability.

New programmers, often think that creating variables is expensive, so that they try to define all variables once, and avoid defining variables multiple times. leading to code like this:
```cpp
#include <iostream>

int main()
{
    int i {}; // i defined outside loop
    for (i = 0; i < 10; ++i) // i assigned value
    {
        std::cout << i << ' ';
    }

    // i can still be accessed here

    std::cout << '\n';

    return 0;
}
```

However, **creating variables has negligible cost** in modern C++ compilers, while it is the **initialization** of variables that can have a cost. This will cause three main issues:
- It makes the program more complex than necessary, as the variable exists outside the loop where it is not needed.
- It increases the chance of naming conflicts, especially in larger programs where many variables are defined.
- It can lead to slower execution, since the compiler may not be able to optimize the code as effectively when variables have a broader scope than necessary.

> **Note:** Creating variables has negligible cost; prefer defining variables inside loops when they are only needed there.

#### Summary:
- The `for` loop is a control flow statement that allows you to execute a block of code a specific number of times.
- It consists of three parts: initialization, condition, and update.
- Prefer using `operator<` or `operator>` over `operator!=` in loop conditions.
- Be cautious of off-by-one errors when defining loop conditions.
- You can omit expressions in `for` loops, but ensure the loop still functions correctly.
- You can use multiple loop control variables in a `for` loop.


---

### S11 — 8.11 Break and continue statements

#### Break statements:
The `break` statement is a control flow statement that allows you to exit a loop or switch statement prematurely. When a `break` statement is encountered inside a loop, the loop is immediately terminated, and the program continues executing the code that follows the loop.

#### Breaking a switch statement:
In a `switch` statement, the `break` statement is used to exit the switch block after a case has been executed. Without a `break` statement, the program will continue executing the subsequent cases (this is known as "fall-through"). Here is an example:
```cpp
#include <iostream>

void printMath(int x, int y, char ch)
{
    switch (ch)
    {
    case '+':
        std::cout << x << " + " << y << " = " << x + y << '\n';
        break; // don't fall-through to next case
    case '-':
        std::cout << x << " - " << y << " = " << x - y << '\n';
        break; // don't fall-through to next case
    case '*':
        std::cout << x << " * " << y << " = " << x * y << '\n';
        break; // don't fall-through to next case
    case '/':
        std::cout << x << " / " << y << " = " << x / y << '\n';
        break;
    }
}

int main()
{
    printMath(2, 3, '+');

    return 0;
}
```
Output:
```
2 + 3 = 5
```
In this example, the `break` statements prevent fall-through between cases in the `switch` statement. When the case for `'+'` is executed, the program exits the switch block after printing the result.

#### Breaking a loop:
The `break` statement can also be used inside loops to exit the loop prematurely based on a specific condition. Here is an example:
```cpp
#include <iostream>

int main()
{
    int sum{ 0 };

    // Allow the user to enter up to 10 numbers
    for (int count{ 0 }; count < 10; ++count)
    {
        std::cout << "Enter a number to add, or 0 to exit: ";
        int num{};
        std::cin >> num;

        // exit loop if user enters 0
        if (num == 0)
            break; // exit the loop now

        // otherwise add number to our sum
        sum += num;
    }

    // execution will continue here after the break
    std::cout << "The sum of all the numbers you entered is: " << sum << '\n';

    return 0;
}
```
In this example, the `break` statement is used to exit the loop when the user enters `0`. The program then continues executing the code that follows the loop, printing the sum of the numbers entered. Here is a sample execution:
```
Enter a number to add, or 0 to exit: 5
Enter a number to add, or 0 to exit: 10
Enter a number to add, or 0 to exit: 3
Enter a number to add, or 0 to exit: 0
The sum of all the numbers you entered is: 18
```

`break` can be used to get out of an intentional infinite loop:
```cpp
#include <iostream>

int main()
{
    while (true) // intentional infinite loop
    {
        std::cout << "Enter a number to add, or 0 to exit: ";
        int num{};
        std::cin >> num;

        // exit loop if user enters 0
        if (num == 0)
            break; // exit the loop now

        std::cout << "You entered: " << num << '\n';
    }

    std::cout << "Exited the loop.\n";

    return 0;
}
```
In this example, the `break` statement is used to exit the infinite loop when the user enters `0`. The program then continues executing the code that follows the loop, printing a message indicating that the loop has been exited.

#### Break vs return:
Both `break` and `return` can be used to exit from a block of code, but they serve different purposes:
- `break` is used to exit loops or switch statements, allowing the program to continue executing the code that follows the loop or switch.
- `return` is used to exit a function and return control to the calling function, optionally returning a value. 

Here is an example that illustrates the difference:
```cpp
#include <iostream>

void demonstrateBreak()
{
    for (int i{ 0 }; i < 5; ++i)
    {
        if (i == 3)
            break; // exit the loop when i is 3
        std::cout << "Inside loop: " << i << '\n';
    }
    std::cout << "Exited loop using break.\n";
}

void demonstrateReturn()
{
    for (int i{ 0 }; i < 5; ++i)
    {
        if (i == 3)
            return; // exit the function when i is 3
        std::cout << "Inside loop: " << i << '\n';
    }
    std::cout << "This line will never be reached due to return.\n";
}

int main()
{
    demonstrateBreak();
    demonstrateReturn();

    return 0;
}
```
Output:
```
Inside loop: 0
Inside loop: 1
Inside loop: 2
Exited loop using break.
Inside loop: 0
Inside loop: 1
Inside loop: 2
```
In this example, the `demonstrateBreak` function uses `break` to exit the loop when `i` is `3`, allowing the function to continue executing and print a message after the loop. The `demonstrateReturn` function uses `return` to exit the function entirely when `i` is `3`, preventing any further code in the function from being executed.

#### Continue statements:
The `continue` statement is a control flow statement that allows you to skip the current iteration of a loop and move on to the next iteration. When a `continue` statement is encountered inside a loop, the remaining code in the loop body for that iteration is skipped, and the loop proceeds to the next iteration. Here is an example:
```cpp
#include <iostream>

int main()
{
    for (int i{ 1 }; i <= 10; ++i)
    {
        // skip even numbers
        if (i % 4 == 0)
            continue; // skip to next iteration

        // If the number is not divisible by 4, print it
        std::cout << i << ' ';
    }

    std::cout << '\n';
    return 0;
}
```
Output:
```
1 2 3 5 6 7 9 10
```
In this example, the `continue` statement is used to skip numbers that are divisible by `4`. When such a number is encountered, the loop skips the `std::cout` statement and moves on to the next iteration.

The `continue` keyword jumps to the bottom of the loop, where the update expression is executed (in the case of a `for` loop), before re-evaluating the loop condition.

#### Conitinue in while loops:
The `continue` statement can also be used in `while` loops to skip the current iteration, but be careful that the loop condition is still properly updated to avoid infinite loops. Here is an example:
```cpp
#include <iostream>

int main()
{
    int i{ 0 };
    while (i < 10)
    {
        ++i; // increment i at the start of the loop

        // skip even numbers
        if (i % 4 == 0)
            continue; // skip to next iteration

        // If the number is not divisible by 4, print it
        std::cout << i << ' ';
    }

    std::cout << '\n';
    return 0;
}
```
Output:
```
1 2 3 5 6 7 9 10
```
In this example, the `continue` statement is used to skip numbers that are divisible by `4` in a `while` loop. The loop increments `i` at the start of each iteration to ensure that the loop condition is properly updated, preventing an infinite loop.

An erroneous example that leads to an infinite loop would be:
```cpp
#include <iostream>

int main()
{
    int i{ 0 };
    while (i < 10)
    {
        // skip even numbers
        if (i == 4)
            continue; // skip to next iteration without incrementing i

        // If the number is not 4, print it
        std::cout << i << ' ';
        ++i; // increment i
    }
    std::cout << '\n';
    return 0;
}
```
In this erroneous example, when `i` is `4`, the `continue` statement causes the loop to skip the increment step, leading to an infinite loop where `i` remains `4` forever. To fix this, the increment step should be placed before the `continue` statement.

#### The debate over use of break and continue:
The use of `break` and `continue` statements in loops is a topic of debate among programmers. Some argue that these statements can make code harder to read and understand, as they introduce additional control flow paths that may not be immediately obvious. Others believe that `break` and `continue` can enhance code clarity by allowing early exits from loops or skipping unnecessary iterations, making the intent of the code clearer.

As often in programming, the truth lies somewhere in between. The key is to use `break` and `continue` judiciously and with consideration for code readability. Here are some guidelines to consider:
- Use `break` when you need to exit a loop early based on a specific condition, especially in cases where continuing the loop would be unnecessary or inefficient.
- Use `continue` when you want to skip specific iterations of a loop, particularly when the skipped iterations are not relevant to the task at hand.
- Avoid overusing `break` and `continue`, as excessive use can lead to complex and hard-to-follow code. Strive for clarity and simplicity in your loop logic.

For example, this hard-to-read code:
```cpp
#include <iostream>

int main()
{
    int count{ 0 }; // count how many times the loop iterates
    bool keepLooping { true }; // controls whether the loop ends or not
    while (keepLooping)
    {
        std::cout << "Enter 'e' to exit this loop or any other character to continue: ";
        char ch{};
        std::cin >> ch;

        if (ch == 'e')
            keepLooping = false;
        else
        {
            ++count;
            std::cout << "We've iterated " << count << " times\n";
        }
    }

    return 0;
}
```
Can be rewritten more clearly using `break`:
```cpp
#include <iostream>

int main()
{
    int count{ 0 }; // count how many times the loop iterates

    while (true) // intentional infinite loop
    {
        std::cout << "Enter 'e' to exit this loop or any other character to continue: ";
        char ch{};
        std::cin >> ch;

        if (ch == 'e')
            break; // exit the loop immediately

        ++count;
        std::cout << "We've iterated " << count << " times\n";
    }

    return 0;
}
```
In this revised example, the use of `break` simplifies the loop logic, making it clearer that the loop will continue until the user enters 'e' to exit.

The `continue` statement is most effectively used at the top of a for-loop to skip unnecessary processing, as shown in this example:
```cpp
#include <iostream>

int main()
{
    for (int count{ 0 }; count < 10; ++count)
    {
        // if the number is not divisible by 4...
        if ((count % 4) != 0) // nested block
        {
                // Print the number
                std::cout << count << '\n';
        }
    }

    return 0;
}
```
Can be more clearly written using `continue`:
```cpp
#include <iostream>

int main()
{
    for (int count{ 0 }; count < 10; ++count)
    {
        // skip numbers that are divisible by 4
        if ((count % 4) == 0)
            continue; // skip to next iteration

        // Print the number
        std::cout << count << '\n';
    }

    return 0;
}
```
In this revised example, the use of `continue` eliminates the need for a nested block, making the code easier to read and understand.

> **Best Practice:** Use `break` and `continue` when they enhance code clarity, but avoid overusing them to maintain readability.

#### The debate over use of early returns:
Similar to the debate over `break` and `continue`, the use of early `return` statements in functions is also a topic of discussion among programmers. Early returns can improve code readability by allowing functions to exit as soon as a certain condition is met, reducing the need for nested conditional statements. However, excessive use of early returns can lead to multiple exit points in a function, which may make it harder to follow the flow of the function.

As with `break` and `continue`, the key is to use early `return` statements judiciously and with consideration for code readability.

#### Summary:
- The `break` statement allows you to exit loops or switch statements prematurely.
- The `continue` statement allows you to skip the current iteration of a loop and move on to the next iteration.
- Use `break` to exit loops based on specific conditions and `continue to skip unnecessary iterations.
- Be mindful of code readability when using `break`, `continue`, and early `return` statements.


---

### S12 — 8.12 Halts (exiting your program early)
The last category of control flow statements we will cover are those that allow you to exit your program early. These statements are useful when you need to terminate your program based on certain conditions or errors.

By default, if your `main` function reaches the closing brace (`}`), or a `return` statement is executed, the program will call implicitly `std::exit(0)`, indicating successful completion of the program.

#### The exit function:
The `exit` function is a standard library function that allows you to terminate your program immediately. It is defined in the `<cstdlib>` header and has the following syntax:
```cpp
#include <cstdlib>

void exit(int status);
```
The `status` parameter is an integer value that indicates the exit status of the program. A value of `0` typically indicates successful completion (**normal termination**), while a non-zero value indicates an error (typically non-zero `status` codes are used to indicate specific error conditions).

`std::exit()` performs several cleanup operations before terminating the program, such as:
- Destroying static objects
- Flushing and closing open output streams
- Other miscellaneous cleanup tasks
- Calling functions registered with `std::atexit()`: the control returns to the operating system after `std::exit()` is called.

#### Calling `std::exit()` explicitly:
Although `std::exit()` is called implicitly when `main` returns, you can also call it explicitly in your code to terminate the program early. Here is an example:
```cpp
#include <cstdlib> // for std::exit()
#include <iostream>

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main()
{
    std::cout << 1 << '\n';
    cleanup();

    std::exit(0); // terminate and return status code 0 to operating system

    // The following statements never execute
    std::cout << 2 << '\n';

    return 0;
}
```
Output:
```
1
cleanup!
```
In this example, the `std::exit(0)` function is called to terminate the program early. The `cleanup` function is called before exiting to perform any necessary cleanup operations. The statements after the `std::exit(0)` call are never executed.

#### `std::exit()` does not clean up local variables:
It is important to note that `std::exit()` does not perform cleanup for local variables in the current function scope. Local variables are not destroyed, and their destructors are not called when `std::exit()` is invoked. This can lead to resource leaks if local variables manage resources that require cleanup. Here is an example:
```cpp
#include <cstdlib> // for std::exit()
#include <iostream>

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource released\n"; }
};

void example()
{
    Resource res;
    std::exit(0);
}

int main()
{
    example();

    return 0;
}
```
Output:
```
Resource acquired
```
In this example, the `Resource` object is created in the `example` function. When `std::exit(0)` is called, the destructor for the `Resource` object is not invoked, and the message "Resource released" is never printed, indicating that the resource was not properly cleaned up.

> **Note:** `std::exit()` does not clean up local variables; be cautious when using it in functions that manage resources.

#### `std::atexit()` function:
Because `std::exit()` terminates the program immediately, you may want to manually do some cleanup before terminating. In this context, cleanup means things like closing database or network connections, deallocating any memory you have allocated, writing information to a log file, etc. To facilitate this, C++ provides the `std::atexit()` function, which allows you to register functions to be called automatically when `std::exit()` is invoked.
The syntax of the `std::atexit()` function is as follows:
```cpp
#include <cstdlib> // for std::exit()
#include <iostream>

void cleanup()
{
    // code here to do any kind of cleanup required
    std::cout << "cleanup!\n";
}

int main()
{
    // register cleanup() to be called automatically when std::exit() is called
    std::atexit(cleanup); // note: we use cleanup rather than cleanup() since we're not making a function call to cleanup() right now

    std::cout << 1 << '\n';

    std::exit(0); // terminate and return status code 0 to operating system

    // The following statements never execute
    std::cout << 2 << '\n';

    return 0;
}
```
Output:
```
1
cleanup!
```
In this example, the `cleanup` function is registered with `std::atexit()`, so it is called automatically when `std::exit(0)` is invoked. This allows you to perform necessary cleanup operations before the program terminates.

If you register multiple functions with `std::atexit()`, they will be called in the reverse order of their registration (i.e., last registered, first called).

#### `std::abort()` and `std::terminate()` functions:
In addition to `std::exit()`, C++ provides two other functions for terminating a program:
- `std::abort()`: This function terminates the program immediately without performing any cleanup operations, leading to an **abnormal termination**. It does not call functions registered with `std::atexit()`, nor does it flush output streams or destroy static objects. It is typically used in situations where the program encounters a critical error and cannot continue.
    ```cpp
    #include <cstdlib> // for std::abort()
    #include <iostream>

    int main()
    {
        std::cout << 1 << '\n';
        std::abort();

        // The following statements never execute
        std::cout << 2 << '\n';

        return 0;
    }
    ```
- `std::terminate()`: This function is often used in combination with exception handling (covered in a later chapter). It is called when an exception is thrown but not caught, leading to program termination. By default, `std::terminate()` calls `std::abort()`, resulting in abnormal termination.

#### When you should use halting functions:
Halting functions like `std::exit()`, `std::abort()`, and `std::terminate()` should be used **almost never** in regular program flow. They are primarily intended for exceptional situations.

#### Summary:
- The `std::exit()` function allows you to terminate your program immediately, performing some cleanup operations.
- The `std::atexit()` function allows you to register functions to be called automatically when `std::exit()` is invoked.
- The `std::abort()` function terminates the program immediately without performing any cleanup operations.
- The `std::terminate()` function is called when an exception is thrown but not caught, leading to program termination.


---

### S13 — 8.13 Introduction to random number generation
The ability to generate random numbers can be useful in certain kinds of programs, particularly in games, statistical modelling programs, and cryptographic applications that need to encrypt and decrypt things. In this section, we will provide a brief introduction to random number generation in C++. 

Computers are deterministic machines, meaning that they follow a set of predefined instructions to perform tasks. As a result, generating truly random numbers is challenging. Instead, computers use algorithms to simulate randomness, producing what are known as **pseudorandom numbers**. These numbers appear random but are generated using a deterministic process.

#### Algorithms and state:
An **algorithm** is a finite sequence of instructions that, when followed, produce a specific output. For example, you can use an algorithm to order a list of names alphabetically or to calculate the sum of a series of numbers. In this way, a repeated set of instructions can produce a correct (if the algorithm is well designed) and predictable output, that works with different inputs.

For example, consider the following simple algorithm:
```cpp
#include <iostream>

int plusOne()
{
    static int s_state { 3 }; // only initialized the first time this function is called

    // Generate the next number

    ++s_state;      // first we modify the state
    return s_state; // then we use the new state to generate the next number in the sequence
}

int main()
{
    std::cout << plusOne() << '\n';
    std::cout << plusOne() << '\n';
    std::cout << plusOne() << '\n';

    return 0;
}
```
Output:
```
4
5
6
```
In this example, the `plusOne` function uses a static variable `s_state` to maintain state between function calls. Each time the function is called, it increments `s_state` by `1` and returns the new value. The output is predictable and follows a specific pattern.

An algorithm is considered to be **stateful** if it retains some information across calls, allowing it to produce different outputs based on its internal state. In the example above, the `plusOne` function is stateful because it uses the static variable `s_state` to keep track of the current number in the sequence. The term **state** refers to the internal data that an algorithm uses to maintain its progress or context.

The algorithm can be:
- **Deterministic:** Given the same initial state, it will always produce the same sequence of outputs. In the `plusOne` example, starting with `s_state` initialized to `3`, the sequence will always be `4, 5, 6, ...`.
- **Non-deterministic:** The algorithm may produce different outputs even when starting from the same initial state, often due to external factors or randomness.

#### Pseudo-random number generators (PRNGs):
A **pseudo-random number generator (PRNG)** is an algorithm that uses mathematical formulas or pre-calculated tables to generate a sequence of numbers whose properties approximate those of random numbers. PRNGs are deterministic and rely on an initial value known as a **seed** to start the generation process. By using the same seed, a PRNG will produce the same sequence of numbers, which is useful for testing and debugging.

Here is a short PRNG example that generates 100 16-bit pseudo-random numbers:
```cpp
#include <iostream>

// For illustrative purposes only, don't use this
unsigned int LCG16() // our PRNG
{
    static unsigned int s_state{ 0 }; // only initialized the first time this function is called

    // Generate the next number

    // We modify the state using large constants and intentional overflow to make it hard
    // for someone to casually determine what the next number in the sequence will be.

    s_state = 8253729 * s_state + 2396403; // first we modify the state
    return s_state % 32768; // then we use the new state to generate the next number in the sequence
}

int main()
{
    // Print 100 random numbers
    for (int count{ 1 }; count <= 100; ++count)
    {
        std::cout << LCG16() << '\t';

        // If we've printed 10 numbers, start a new row
        if (count % 10 == 0)
            std::cout << '\n';
    }

    return 0;
}
```
Output (example):
```
4339	838	25337	15372	6783	2642	6021	19992	14859	26462	
25105	13860	28567	6762	17053	29744	15139	9078	14633	2108	
7343	642	17845	29256	5179	14222	26689	12884	8647	17050	
8397	18528	17747	9126	28505	13420	32479	23218	21477	30328	
20075	26558	20081	3716	13303	19146	24317	31888	12163	982	
1417	16540	16655	4834	16917	23208	26779	30702	5281	19124	
9767	13050	32045	4288	31155	17414	31673	11468	25407	11026	
4165	7896	25291	26654	15057	26340	30807	31530	31581	1264	
9187	25654	20969	30972	25967	9026	15989	17160	15611	14414	
16641	25364	10887	9050	22925	22816	11795	25702	2073	9516
```
In this example, the `LCG16` function implements a simple linear congruential generator (LCG) algorithm to produce pseudo-random numbers. The state is updated using a linear equation, and the output is constrained to 16-bit values using the modulus operator. The state is initially set to `0`, then it is updated with each call to generate a new number.

This is not considered a good PRNG for serious applications, but it serves to illustrate the concept of stateful algorithms and pseudo-random number generation (numbers alternate between even and odd, and have visible patterns).

#### Seeding a PRNG:
To improve the randomness of a PRNG, it is common to initialize its state using a **seed** value that is derived from a variable source, such as the current time or user input. Here is an example where we seed our PRNG using a user-provided seed:
```cpp
#include <iostream>

unsigned int g_state{ 0 };

void seedPRNG(unsigned int seed)
{
    g_state = seed;
}

// For illustrative purposes only, don't use this
unsigned int LCG16() // our PRNG
{
    // We modify the state using large constants and intentional overflow to make it hard
    // for someone to casually determine what the next number in the sequence will be.

    g_state = 8253729 * g_state + 2396403; // first we modify the state
    return g_state % 32768; // then we use the new state to generate the next number in the sequence
}

void print10()
{
    // Print 10 random numbers
    for (int count{ 1 }; count <= 10; ++count)
    {
        std::cout << LCG16() << '\t';
    }

    std::cout << '\n';
}

int main()
{
    unsigned int x {};
    std::cout << "Enter a seed value: ";
    std::cin >> x;

    seedPRNG(x); // seed our PRNG
    print10();   // generate 10 random values

    return 0;
}
```
Output (example `7`):
```
Enter a seed value: 7
10458	3853	16032	17299	10726	32153	19116	7455	242	549
```
Output (example `7`):
```
Enter a seed value: 7
10458	3853	16032	17299	10726	32153	19116	7455	242	549
```
Output (example `9876`):
```
Enter a seed value: 9876
24071	18138	27917	23712	8595	18406	23449	26796	31519	7922
```

Notice that when we provide the same seed value (`7`), we get the same sequence of pseudo-random numbers. Changing the seed value (`9876`) results in a different sequence.

#### Seed quality and underseeding:
The quality of the seed used to initialize a PRNG can significantly impact the randomness of the generated numbers. A poor-quality seed may lead to predictable or non-random sequences, which can be problematic in applications requiring high-quality randomness, such as cryptography. 

The theoretical maximum number of unique states a PRNG can have is determined by the size of its internal state. For example, a PRNG with a 32-bit state can have up to 2^32 (approximately 4.29 billion) unique states. If the seed value does not utilize the full range of possible states, it can lead to **underseeding**, where the PRNG produces a limited set of outputs, reducing randomness. For example, an underseeding may exhibit the following issues:
- The random sequences could have high correlation, meaning that certain patterns or relationships exist between the numbers generated.
- On the generation of the N-th number, the PRNG may cycle back to a previous state, leading to repeated sequences of numbers and never-generated values.
- Someone may be able to guess the seed given the output numbers, compromising security in cryptographic applications.

#### What makes a good PRNG? (Optional reading)
A good PRNG should have the following characteristics:
- **Uniform distribution:** The generated numbers should be uniformly distributed across the desired range, meaning that each number has an equal probability of being selected.
- **Unpredictability:** The sequence of numbers should be difficult to predict, even if some of the previous numbers in the sequence are known.
- **Good distribution properties:** The PRNG should exhibit good statistical properties, and generate well-distributed numbers across the entire range.
- **Long period:** The PRNG should have a long period before the sequence of numbers starts to repeat. A longer period reduces the likelihood of patterns emerging in the generated numbers.
- **Efficiency:** The PRNG should be computationally efficient, allowing for fast generation of random numbers without significant overhead.

#### Different kinds of PRNG algorithms:
There are many different algorithms for generating pseudo-random numbers, each with its own strengths and weaknesses. Some common types of PRNG algorithms include:
- **Linear Congruential Generators (LCG):** Simple and fast, but may have poor statistical properties.
- **Mersenne Twister:** Known for its long period and good statistical properties, widely used in various applications.
- **Xorshift:** Fast and efficient, using bitwise operations to generate random numbers.
- **Cryptographically Secure PRNGs (CSPRNGs):** Designed for security-sensitive applications, providing high unpredictability and resistance to attacks.

#### Randomization in C++:
C++ provides a standard library for random number generation in the `<random>` header. This library includes various PRNG algorithms, distributions, and utilities for generating random numbers. As for C++20 and later, it is recommended to use the Marsenne Twister (MT) algorithm provided by the standard library for general-purpose random number generation, since it has both decent performance and quality. Here is an example of using the C++ standard library to generate random numbers (we will cover this library in more detail in a later section):
```cpp
#include <iostream>
#include <random>

int main()
{
    // Create a random device to seed the PRNG
    std::random_device rd;

    // Create a Mersenne Twister PRNG and seed it with the random device
    std::mt19937 mt(rd());

    // Define a uniform distribution between 0 and 99
    std::uniform_int_distribution<int> dist(0, 99);

    // Generate and print 10 random numbers
    for (int i = 0; i < 10; ++i)
    {
        int random_number = dist(mt);
        std::cout << random_number << '\t';
    }

    std::cout << '\n';
    return 0;
}
```
Output (example):
```
42	7	89	23	56	12	78	34	90	5	
```
In this example, we use the C++ standard library to generate random numbers. We create a `std::random_device` to seed the Mersenne Twister PRNG (`std::mt19937`). We then define a uniform distribution between `0` and `99` using `std::uniform_int_distribution`. Finally, we generate and print `10` random numbers from the defined distribution.

One drawback of using MT, is that the result can be predicted after seeing 624 generated numbers, so it is not suitable for cryptographic applications. For cryptographic applications, consider using third-party libraries that implement cryptographically secure PRNGs (CSPRNGs).

#### Summary:
- Computers use algorithms to simulate randomness, producing pseudorandom numbers.
- A pseudo-random number generator (PRNG) is an algorithm that generates a sequence of numbers that approximate the properties of random numbers.
- PRNGs are deterministic and rely on an initial seed to start the generation process.
- The quality of the seed can significantly impact the randomness of the generated numbers.
- Good PRNGs exhibit uniform distribution, unpredictability, good statistical properties, long periods, and efficiency.
- C++ provides a standard library for random number generation in the `<random>` header, which includes various PRNG algorithms and distributions.


---

### S14 — 8.14 Generating random numbers using Marsenne Twister
In this section, we will take a look at how to generate random numbers in your programs using the `<random>` header from the C++ standard library, specifically using the Mersenne Twister (MT) algorithm.

#### Generating random numbers in C++ using Mersenne Twister:
Mersenne Twister is a widely used pseudo-random number generator (PRNG) known for its long period and good statistical properties. Even though it is a bit old by today's standards, it is still a solid choice for general-purpose random number generation in C++. The random library `<random>` provides an implementation of the Mersenne Twister algorithm through two classes:
- `std::mt19937`: MT that generates 32-bit unsigned integers.
- `std::mt19937_64`: MT that generates 64-bit unsigned integers.

Using MT is straightforward. Here is an example of generating random numbers using `std::mt19937`:
```cpp
#include <iostream>
#include <random> // for std::mt19937

int main()
{
	std::mt19937 mt{}; // Instantiate a 32-bit Mersenne Twister

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << mt() << '\t'; // generate a random number

		// If we've printed 5 numbers, start a new row
		if (count % 5 == 0)
			std::cout << '\n';
	}

	return 0;
}
```
Output (example):
```
3499211612      581869302       3890346734      3586334585      545404204
4161255391      3922919429      949333985       2715962298      1323567403
418932835       2350294565      1196140740      809094426       2348838239
4264392720      4112460519      4279768804      4144164697      4156218106
676943009       3117454609      4168664243      4213834039      4111000746
471852626       2084672536      3427838553      3437178460      1275731771
609397212       20544909        1811450929      483031418       3933054126
2747762695      3402504553      3772830893      4120988587      2163214728
```
In this example, we first include the `<random>` header to access the random number generation facilities. We then instantiate a `std::mt19937` object named `mt`, which represents our Mersenne Twister PRNG. We use a loop to generate and print `40` random numbers by calling `mt()`. Calling `mt()` produces a new random number each time, and it calls the function `mt.operator()` under the hood.

#### Rolling a dice using Mersenne Twister:
A 32-bit PRNG will generate numbers in the range of `0` to `4,294,967,295`. However, in many cases, we want to generate random numbers within a specific range. For example, if we want to simulate rolling a six-sided dice, we need to generate random numbers between `1` and `6`. Unfortunately, PRNGs like Mersenne Twister do not provide built-in functionality to generate numbers within a specific range. Instead, we need some way to convert a number from the full range of the PRNG to our desired range. The `<random>` header provides a way to do this using **distributions**.

A **random number distribution** is a way to map the output of a PRNG to a specific range or pattern. The `<random>` header provides several types of distributions, including uniform, normal, and others. For our dice-rolling example, we will use the **uniform integer distribution** (`std::uniform_int_distribution`), which generates integers uniformly distributed within a specified range. Here is an example of rolling a six-sided dice using Mersenne Twister and a uniform integer distribution:
```cpp
#include <iostream>
#include <random> // for std::mt19937 and std::uniform_int_distribution

int main()
{
	std::mt19937 mt{};

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```
Output (example):
```
3       1       3       6       5       2       6       6       1       2
2       6       1       1       6       1       4       5       2       5
6       2       6       2       1       3       5       4       5       6
1       4       2       3       1       2       2       6       2       1
```
In this example, we create a `std::uniform_int_distribution` object named `die6`, which is configured to generate integers between `1` and `6`. We then use the `die6(mt)` syntax to generate a random number in the specified range by passing our Mersenne Twister object `mt` to the distribution. Each call to `die6(mt)` produces a new random number between `1` and `6`, simulating a roll of a six-sided dice.

#### The above program is not as random as you might think:
While the above program generates random numbers using Mersenne Twister and a uniform distribution, it's important to note that the randomness of the generated numbers can be influenced by the initial state of the PRNG. In the example, we instantiated `std::mt19937 mt{}` without providing a seed, which means it uses a default seed value. This can lead to the same sequence of random numbers being generated each time the program is run.

To prevent this and improve the randomness of the generated numbers, we have different options for seeding the PRNG:
- Use the system clock.
- Use the system random device.
- Use a fixed seed value for reproducibility (useful for testing and debugging).

#### Seeding with the system clock:
One common approach to seeding a PRNG is to use the current time from the system clock. This ensures that the seed value changes each time the program is run, leading to different sequences of random numbers. In the following we will use the `<chrono>` header to get the current time in nanoseconds since epoch and use that value as the seed for our Mersenne Twister PRNG:
```cpp
#include <iostream>
#include <random> // for std::mt19937
#include <chrono> // for std::chrono

int main()
{
	// Seed our Mersenne Twister using steady_clock
	std::mt19937 mt{ static_cast<std::mt19937::result_type>(
		std::chrono::steady_clock::now().time_since_epoch().count()
		) };

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```
In this example, we use `std::chrono::steady_clock::now().time_since_epoch().count()` to get the current time in nanoseconds since epoch and cast it to the appropriate type for seeding the Mersenne Twister PRNG. This ensures that each time the program is run, a different seed value is used, leading to different sequences of random numbers. In this way, we will have different results each time we run the program.

The downside of this approach is that if the program is run multiple times in quick succession (within the same nanosecond), it may produce the same seed value (or very similar seed values), leading to similar sequences of random numbers. For most applications, this is not a significant concern, but for high-security applications, a more robust seeding method may be required.

#### Seeding with the system random device:
Another approach to seeding a PRNG is to use the system's random device, which provides a source of non-deterministic random numbers. The `<random>` header provides the `std::random_device` class (implementation-defined behavior by OS), which can be used to obtain random seed values from the operating system. Here is an example of seeding the Mersenne Twister PRNG using `std::random_device`:
```cpp
#include <iostream>
#include <random> // for std::mt19937 and std::random_device

int main()
{
	std::mt19937 mt{ std::random_device{}() };

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```
In this example, we create a `std::random_device` object and use it to generate a seed value for the Mersenne Twister PRNG. This approach provides a higher quality of randomness compared to using the system clock, as `std::random_device` is designed to provide non-deterministic random numbers based on hardware sources, if available.

One problem with `std::random_device` is that on some systems, it may not be truly non-deterministic and could fall back to a pseudo-random number generator. Additionally, it may be slower than other seeding methods due to the overhead of accessing hardware sources.

> **Note:** `std::random_device{}()` creates a temporary `std::random_device` (by `{}`) and immediately calls its `operator()` to get a random number for seeding.

#### Only seed a PRNG once:
It is important to note that a PRNG should only be seeded once, typically at the start of the program or before its first use. Re-seeding a PRNG multiple times can lead to reduced randomness and predictability in the generated numbers. Once a PRNG is seeded, it maintains its internal state and generates a sequence of random numbers based on that state. Re-seeding it resets the state, which can disrupt the randomness of the sequence. Here is an example of incorrect usage where a PRNG is re-seeded multiple times:
```cpp
#include <iostream>
#include <random>

int getCard()
{
    std::mt19937 mt{ std::random_device{}() }; // this gets created and seeded every time the function is called
    std::uniform_int_distribution card{ 1, 52 };
    return card(mt);
}

int main()
{
    std::cout << getCard() << '\n';

    return 0;
}
```
In this example, the `getCard` function creates and seeds a new `std::mt19937` object every time it is called. This can lead to poor randomness, especially if the function is called multiple times in quick succession, as the seed values may be similar or identical. Instead, the PRNG should be created and seeded once, and then reused for generating random numbers.

> **Best Practice:** Seed your PRNG once at the start of your program and reuse it for generating random numbers throughout your program.

#### Mersenne Twister and underseeding issues:
As discussed in the previous section, underseeding occurs when a PRNG is initialized with a seed value that does not utilize the full range of possible states, leading to reduced randomness and predictability in the generated numbers. Mersenne Twister internal state has 19937 bits (2493 bytes), which is 624 32-bit values or 312 64-bit values. As a result, `std::mt19937` allocates 624 integers whereas `std::mt19937_64` allocates 312 integers for its internal state.

When seeding Mersenne Twister from the clock or `std::random_device`, our seed is only a **single integer value** (32-bit or 64-bit), which means that we are only initializing a small portion of the internal state. The random library does the best it can to fill the remaining 623 (or 311) integers of state with "random" data, but it is not ideal. So, how can we fix it?

The random library provides a way to seed Mersenne Twister more thoroughly using a **seed sequence**. A seed sequence is a collection of integer values that can be used to initialize the entire internal state of a PRNG. The `<random>` header provides the `std::seed_seq` class for this purpose, that basically takes as many randomized values as we have, and generates as many additional unbiased seed values as needed to initialize the PRNG's internal state. For example, if we initialize the `std::seed_seq` with `n` values, it will generate the remaining `624 - n` (or `312 - n`) values needed to fully seed the Mersenne Twister PRNG. Here is an example of seeding Mersenne Twister using a seed sequence:
```cpp
#include <iostream>
#include <random>

int main()
{
	std::random_device rd{};
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() }; // get 8 integers of random numbers from std::random_device for our seed
	std::mt19937 mt{ ss }; // initialize our Mersenne Twister with the std::seed_seq

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```
In this example, we create a `std::seed_seq` object named `ss`, which is initialized with `8` random integers obtained from `std::random_device`. We then use this seed sequence to initialize the Mersenne Twister PRNG (`std::mt19937 mt{ ss };`). This approach ensures that the entire internal state of the PRNG is properly seeded, leading to improved randomness in the generated numbers.

#### Warming up a PRNG:
Some PRNGs may exhibit less randomness in the initial numbers they generate after being seeded, especially when underseeded. To mitigate this issue, it is common practice to "warm up" the PRNG by discarding a certain number of initial random numbers before using it for actual random number generation. This helps to ensure that the PRNG's intperforms warm up, so we do not need explicit warm-up in this case.

#### Debugging programs that use random numbers:
When debugging programs that use random numbers, it can be helpful to use a **fixed seed value** for the PRNG. This allows you to reproduce the same sequence of random numbers each time you run the program, making it easier to identify and fix issues. Here is an example of using a fixed seed value for debugging:
```cpp
#include <iostream>
#include <random>

int main()
{
    std::mt19937 mt{ 42 }; // fixed seed value for reproducibility

    // Create a reusable random number generator that generates uniform numbers between 1 and 6
    std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

    // Print a bunch of random numbers
    for (int count{ 1 }; count <= 40; ++count)
    {
        std::cout << die6(mt) << '\t'; // generate a roll of the die here

        // If we've printed 10 numbers, start a new row
        if (count % 10 == 0)
            std::cout << '\n';
    }

    return 0;
}
```
In this way, every time you run the program, it will produce the same sequence of random numbers, making it easier to debug and test your code.

#### Summary:
- The `<random>` header in C++ provides facilities for generating random numbers using various PRNG algorithms, including Mersenne Twister.
- Mersenne Twister is a widely used PRNG known for its long period and good statistical properties.
- Random number distributions, such as `std::uniform_int_distribution`, allow you to map the output of a PRNG to a specific range or pattern.
- Seeding a PRNG is crucial for ensuring randomness, and it should only be done once.
- Using a seed sequence (`std::seed_seq`) can help fully initialize the internal state of a PRNG, improving randomness.
- For debugging, using a fixed seed value allows for reproducible sequences of random numbers.


---

### S15 — 8.15 Global random numbers (Random.h)
What happens if we want to use a random number generator in multiple functions or files? One approach is to create (and seed) our PRNG in our `main()` function, and then pass it to any function that needs it. However, this can lead to a lot of extra parameters being passed around, which can make the code harder to read and maintain.

Another approach is to create a static local `std::mt19937` variable in each function that needs it (static so it only gets seeded once). However, this can lead to multiple PRNGs being created, which can result in less randomness overall and a bit overkill.

A better approach is to create a single global random number generator that can be accessed from anywhere in the program. This way, we only need to seed the PRNG once, and we can use it throughout our code without passing it around. Here is a simple, header-only implementation of a global random number generator using Mersenne Twister:
Random.h:
```cpp
#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <chrono>
#include <random>

// This header-only Random namespace implements a self-seeding Mersenne Twister.
// Requires C++17 or newer.
// It can be #included into as many code files as needed (The inline keyword avoids ODR violations)
// Freely redistributable, courtesy of learncpp.com (https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/)
namespace Random
{
	// Returns a seeded Mersenne Twister
	// Note: we'd prefer to return a std::seed_seq (to initialize a std::mt19937), but std::seed can't be copied, so it can't be returned by value.
	// Instead, we'll create a std::mt19937, seed it, and then return the std::mt19937 (which can be copied).
	inline std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	// Here's our global std::mt19937 object.
	// The inline keyword means we only have one global instance for our whole program.
	inline std::mt19937 mt{ generate() }; // generates a seeded std::mt19937 and copies it into our global object

	// Generate a random int between [min, max] (inclusive)
        // * also handles cases where the two arguments have different types but can be converted to int
	inline int get(int min, int max)
	{
		return std::uniform_int_distribution{min, max}(mt);
	}

	// The following function templates can be used to generate random numbers in other cases

	// See https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
	// You can ignore these if you don't understand them

	// Generate a random value between [min, max] (inclusive)
	// * min and max must have the same type
	// * return value has same type as min and max
	// * Supported types:
	// *    short, int, long, long long
	// *    unsigned short, unsigned int, unsigned long, or unsigned long long
	// Sample call: Random::get(1L, 6L);             // returns long
	// Sample call: Random::get(1u, 6u);             // returns unsigned int
	template <typename T>
	T get(T min, T max)
	{
		return std::uniform_int_distribution<T>{min, max}(mt);
	}

	// Generate a random value between [min, max] (inclusive)
	// * min and max can have different types
        // * return type must be explicitly specified as a template argument
	// * min and max will be converted to the return type
	// Sample call: Random::get<std::size_t>(0, 6);  // returns std::size_t
	// Sample call: Random::get<std::size_t>(0, 6u); // returns std::size_t
	// Sample call: Random::get<std::int>(0, 6u);    // returns int
	template <typename R, typename S, typename T>
	R get(S min, T max)
	{
		return get<R>(static_cast<R>(min), static_cast<R>(max));
	}
}

#endif
```
With this `Random.h` header, we define a `Random` namespace that contains a global `std::mt19937` object named `mt`. The `generate` function seeds the PRNG using a combination of the current time and random values from `std::random_device`. The `get` functions provide a convenient way to generate random integers within a specified range.

To use this approach in your prgram, you can follow these steps:
1. Copy&paste the `Random.h` code into a new header file named `Random.h`.
2. `#include "Random.h"` in any code file that needs to generate random numbers.
3. Use the `Random::get(min, max)` function to generate random integers within the desired range (e.g., `Random::get(1, 6)` to simulate a dice roll). No initialization or seeding is required, as the global PRNG is automatically seeded when the program starts.

For example, here is how you can use the `Random.h` header in a program to roll a six-sided dice:
```cpp
#include "Random.h" // defines Random::mt, Random::get(), and Random::generate()
#include <cstddef> // for std::size_t
#include <iostream>

int main()
{
	// We can call Random::get() to generate random integral values
	// If the two arguments have the same type, the returned value will have that same type.
	std::cout << Random::get(1, 6) << '\n';   // returns int between 1 and 6
	std::cout << Random::get(1u, 6u) << '\n'; // returns unsigned int between 1 and 6

        // In cases where we have two arguments with different types
        // and/or if we want the return type to be different than the argument types
        // We must specify the return type using a template type argument (between the angled brackets)
	// See https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
	std::cout << Random::get<std::size_t>(1, 6u) << ' '; // returns std::size_t between 1 and 6

	// If we have our own distribution, we can access Random::mt directly

	// Let's create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };
	for (int count{ 1 }; count <= 10; ++count)
	{
		std::cout << die6(Random::mt) << '\t'; // generate a roll of the die here
	}

	std::cout << '\n';

	return 0;
}
```

#### Few notes on the implementation:
- The `inline` keyword is used for the global `std::mt19937 mt` variable and the functions in the `Random` namespace to avoid multiple definition errors when the header is included in multiple translation units.
- The `generate` function creates and returns a seeded `std::mt19937` object, which is then used to initialize the global `mt` variable.
- The `get` functions provide a convenient interface for generating random integers within a specified range, handling both same-type and different-type arguments.

#### Summary:
- Creating a global random number generator allows for easy access to random numbers throughout a program without the need to pass around PRNG objects.
- The `Random.h` header provides a simple implementation of a global Mersenne Twister PRNG that is automatically seeded and can be used to generate random integers within a specified range.
- The `Random::get(min, max)` function simplifies the process of generating random numbers, making it easy to use in any part of the program.


---

### SX - 8.x Summary and quiz
Have a look at the quizzes in the orogianl web page, and then check the solution out!

Have fun!! :)


---

## 🧭 Summary

Control flow is what gives a program *intelligence* — the ability to react, repeat, and make decisions.  
Through this chapter, you learned how to guide program execution using conditional logic, loops, and jump mechanisms. You also explored advanced tools like `if constexpr` and random number generators for dynamic or probabilistic behavior.

By combining these techniques, you can write flexible and responsive programs capable of modeling complex real-world logic and automation.

---

### 🧱 Core Concepts You Mastered

- **Sequential execution** — programs execute line-by-line by default.  
- **Conditional branching** — controlling execution with `if`, `else`, and `switch`.  
- **Compile-time branching** — using `if constexpr` to eliminate runtime checks.  
- **Loops** — repeating execution with `for`, `while`, and `do while` statements.  
- **Jump control** — using `break`, `continue`, and `goto` carefully.  
- **Halts** — intentionally ending a program with `std::exit()` or `std::abort()`.  
- **Switch statements** — cleanly handling multiple discrete conditions.  
- **Fall-through control** — explicitly indicating intentional case continuation with `[[fallthrough]]`.  
- **Random number generation** — using `<random>` for deterministic or stochastic behavior.  
- **Code readability** — organizing control structures with consistent indentation and minimal nesting.  

> **Takeaway:** Understanding control flow is essential to write logic-driven, dynamic, and efficient C++ programs that make decisions, iterate, and respond intelligently to input.