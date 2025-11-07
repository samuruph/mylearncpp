# Chapter 09 — Error Detection and Handling

## Overview
In this chapter, we explore how to make C++ programs **robust and reliable** by anticipating and managing errors.  
You’ll learn how to test your code systematically, detect semantic and runtime issues, and design programs that fail gracefully instead of crashing.  
We’ll also look into error handling mechanisms like **assertions**, **error codes**, and **exceptions**, and cover best practices for working with `std::cin` input validation.  

By the end, you’ll understand how to confidently detect, isolate, and handle common sources of failure in your programs.  

---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch09_first
./build/ch09_first
```

---

## 🎯 Learning Outcomes

By the end of this chapter, you’ll be able to:

- Write and structure **unit tests** and **integration tests** to verify code correctness.  
- Understand and apply **code coverage** metrics (statement, branch, and loop coverage).  
- Identify and correct **semantic errors** such as logic and precision issues.  
- Implement **defensive programming** practices for robust code.  
- Handle user input safely with `std::cin`, including validation and fail state recovery.  
- Use **assertions** and **static_assert** to enforce program correctness and detect logical assumptions early.  

---

## Sections

### S01 — 9.1 Introduction to testing your code
Finally you wrote your program, compiled it, and it runs. But how do you know it works correctly?
Since your program will run multiple times in different conditions and with different inputs, you need to make sure it behaves correctly in all those situations, especially if you want to distribute it to other users.

One way to do this is through testing. Testing involves running your program with various inputs and checking the outputs against expected results. This can help you identify bugs and ensure your program behaves as intended.

**Software testing** (also called **software validation**) is the process of executing a program with the intent of finding errors. There are different types of testing, including:
- **Unit testing**: Testing individual components or functions of a program in isolation.
- **Integration testing**: Testing how different components of a program work together.
- **System testing**: Testing the complete and integrated software system to ensure it meets the specified requirements.
- **Acceptance testing**: Testing the software in a real-world environment to ensure it meets the needs of the end-users.

#### The testing challenge:
Before we talked about some practical ways to test your code, but now let's talk about why testing your program comprehensively is difficult. Consider this simple example:
```cpp
#include <iostream>

void compare(int x, int y)
{
    if (x > y)
        std::cout << x << " is greater than " << y << '\n'; // case 1
    else if (x < y)
        std::cout << x << " is less than " << y << '\n'; // case 2
    else
        std::cout << x << " is equal to " << y << '\n'; // case 3
}

int main()
{
    std::cout << "Enter a number: ";
    int x{};
    std::cin >> x;

    std::cout << "Enter another number: ";
    int y{};
    std::cin >> y;

    compare(x, y);

    return 0;
}
```
Assuming 4-byte integers, how many different input combinations are there for the `compare` function? Since each integer can take on 2^32 different values, the total number of input combinations is (2^32) * (2^32) = 2^64 (18,446,744,073,709,551,616, ~18 quintillion) times. Testing all these combinations is impractical.

In reality, in this case, you only need to test three scenarios to cover all possible outcomes of the `compare` function:
1. `x > y`
2. `x < y`
3. `x == y`
However, as programs become more complex, the number of possible input combinations can grow exponentially, making comprehensive testing a significant challenge. This is known as the **combinatorial explosion** problem in software testing.

#### Test your program in small pieces:
Consider an auto manufacturer testing a new car model. Instead of testing the entire car at once, they might test individual components like the engine, brakes, and transmission separately. This allows them to identify and fix issues in specific areas before integrating everything into the final product.

To effectively test your program, it's often helpful to break it down into smaller, manageable pieces. This approach is known as **unit testing**. By isolating individual functions or components, you can focus on testing their specific behavior without the complexity of the entire program. Each **unit test** verifies that a particular function or module behaves as expected under various conditions.

So, how can we test our code in units?

#### Informal testing:
The simplest way to test your code is through **informal testing** as you write new pieces of code (e.g., functions, classes). This involves writing small test cases to verify that each piece of code works as intended, then commenting out or removing the test code once you're satisfied with its correctness. For example:
```cpp
#include <iostream>

// We want to test the following function
// For simplicity, we'll ignore that 'y' is sometimes counted as a vowel
bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

int main()
{
    // So here's our temporary tests to validate it works
    std::cout << isLowerVowel('a') << '\n'; // temporary test code, should produce 1
    std::cout << isLowerVowel('q') << '\n'; // temporary test code, should produce 0

    return 0;
}
```
In this example, we have a function `isLowerVowel` that checks if a character is a lowercase vowel. We include some temporary test code in the `main` function to verify that the function behaves as expected for specific inputs. Once we're confident that the function works correctly, we can remove or comment out the test code.

#### Preserving your tests:
Although informal testing is quick and easy, it has a significant drawback: once you remove the test code, you lose the ability to easily re-run those tests in the future. This can be problematic if you later make changes to the code that might introduce new bugs. for example, you could move your temporary code into a separate function that you can call whenever you want to run your tests:
```cpp
void testVowel()
{
    std::cout << isLowerVowel('a') << '\n'; // temporary test code, should produce 1
    std::cout << isLowerVowel('q') << '\n'; // temporary test code, should produce 0
}
```
Then, in your `main` function, you can call `testVowel()` whenever you want to run your tests. This way, you preserve your tests for future use without cluttering your main codebase.

#### Automating your test functions:
One problem with thre above test function is that it requires you to manually check the output to see if the tests passed or failed. A better approach is to automate the verification process by comparing the actual output of your function against the expected output. If they match, the test passes; if they don't, the test fails. Here's an example:
```cpp
#include <iostream>

bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

// returns the number of the test that failed, or 0 if all tests passed
int testVowel()
{
    if (!isLowerVowel('a')) return 1;
    if (isLowerVowel('q')) return 2;

    return 0;
}

int main()
{
    int result { testVowel() };
    if (result != 0)
        std::cout << "testVowel() test " << result << " failed.\n";
    else
        std::cout << "testVowel() tests passed.\n";

    return 0;
}
```
In this example, the `testVowel` function runs two tests on the `isLowerVowel` function. If a test fails, it returns the number of the failed test; otherwise, it returns 0 to indicate that all tests passed. The `main` function then checks the result and prints an appropriate message.

An even better way would be to use **assertions**, which can automatically check conditions and report failures. However, assertions are typically used for debugging purposes and may not be suitable for production code.
```cpp
#include <cassert> // for assert
#include <cstdlib> // for std::abort
#include <iostream>

bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

// Program will halt on any failed test case
int testVowel()
{
#ifdef NDEBUG
    // If NDEBUG is defined, asserts are compiled out.
    // Since this function requires asserts to not be compiled out, we'll terminate the program if this function is called when NDEBUG is defined.
    std::cerr << "Tests run with NDEBUG defined (asserts compiled out)";
    std::abort();
#endif

    assert(isLowerVowel('a'));
    assert(isLowerVowel('e'));
    assert(isLowerVowel('i'));
    assert(isLowerVowel('o'));
    assert(isLowerVowel('u'));
    assert(!isLowerVowel('b'));
    assert(!isLowerVowel('q'));
    assert(!isLowerVowel('y'));
    assert(!isLowerVowel('z'));

    return 0;
}

int main()
{
    testVowel();

    // If we reached here, all tests must have passed
    std::cout << "All tests succeeded\n";

    return 0;
}
```
In this example, we use the `assert` macro to check various conditions in the `testVowel` function. If any assertion fails, the program will terminate and report the failure. This approach allows for automated testing without the need for manual output checking.

#### Unit testing frameworks:
While writing your own test functions is a good start, as your codebase grows, you might find it beneficial to use a dedicated unit testing framework. These frameworks provide a structured way to write, organize, and run your tests, along with features like test reporting, setup/teardown functions, and more. Some popular C++ unit testing frameworks include:
- Google Test (gtest)
- Catch2
- Boost.Test
Using a unit testing framework can help you manage your tests more effectively and ensure that your code remains reliable as it evolves.

#### Integration testing:
Once you have tested individual components of your program through unit testing, the next step is to ensure that these components work together correctly. This is where **integration testing** comes into play. Integration testing focuses on verifying the interactions between different modules or components of your program. For example, if you have a function that processes user input and another function that performs calculations based on that input, integration testing would involve checking that the data flows correctly between these functions and that they work together as expected.

#### Summary:
- Testing is a crucial part of software development that helps ensure your program behaves correctly under various conditions.
- Unit testing involves testing individual components or functions in isolation, while integration testing focuses on how these components work together.
- Informal testing can be a quick way to validate code, but preserving and automating tests is essential for long-term reliability.
- Using assertions and unit testing frameworks can help streamline the testing process and improve code quality.


---

### S02 — 9.2 Code coverage
In this section, we will talk about what kind of testing you should do to make sure your code is correct (and well tested).

#### Code coverage:
**Code coverage** is a measure used to describe the degree to which the source code of a program is executed while testing. It helps identify which parts of the code have been tested and which parts have not, allowing developers to focus their testing efforts on untested areas. There are several types of code coverage metrics, and we will discuss some of the most common ones below.

#### Statement coverage:
**Statement coverage** measures the percentage of executable statements in the code that have been executed during testing. A statement is considered executed if it has been run at least once during the test suite. For example, consider the following code snippet:
```cpp
int foo(int x, int y)
{
    int z{ y };
    if (x > y)
    {
        z = x;
    }
    return z;
}
```
To achieve 100% statement coverage for this code, we need to ensure that all statements are executed at least once. This can be done calling the function as `foo(1,0)`, which will execute all statements in the function, including the assignment `z = x;` inside the `if` block.

for the previous example:
```cpp
bool isLowerVowel(char c)
{
    switch (c) // statement 1
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true; // statement 2
    default:
        return false; // statement 3
    }
}
```
100% statement coverage can be achieved by calling `isLowerVowel('a')` (to execute statement 2) and `isLowerVowel('b')` (to execute statement 3), so we will need 2 test cases.

#### Branch coverage:
**Branch coverage** measures the percentage of branches (or decision points) in the code that have been executed during testing. A branch is created by control flow statements such as `if`, `switch`, and loops. To achieve 100% branch coverage, each possible branch must be executed at least once. For example, `if statements` create two branches: one for the true condition and one for the false condition.

In the previous `foo` function example, calling the function as `foo(1,0)` will achieve 100% statement coverage, but only 50% branch coverage, since the false branch of the `if` statement is never executed. To achieve 100% branch coverage, we need to call the function twice: once with `foo(1,0)` (to execute the true branch) and once with `foo(0,1)` (to execute the false branch).

In the `isLowerVowel` function example:
```cpp
bool isLowerVowel(char c)
{
    switch (c)
    {
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}
```
To achieve 100% branch coverage, we need to ensure that both the true branch (returning true for vowels) and the false branch (returning false for non-vowels) are executed at least once. This can be done by calling `isLowerVowel('a')` (to execute the true branch) and `isLowerVowel('b')` (to execute the false branch), so we will need 2 test cases.

Now, consider the following example:
```cpp
void compare(int x, int y)
{
	if (x > y)
		std::cout << x << " is greater than " << y << '\n'; // case 1
	else if (x < y)
		std::cout << x << " is less than " << y << '\n'; // case 2
	else
		std::cout << x << " is equal to " << y << '\n'; // case 3
}
```
To achieve 100% branch coverage for this code, we need to ensure that all branches of the `if-else` statements are executed at least once. This can be done by calling the function three times with different inputs:
1. `compare(1, 0)` (to execute case 1)
2. `compare(0, 1)` (to execute case 2)
3. `compare(1, 1)` (to execute case 3)

> **Best practice:** Aim for 100% branch coverage rather than 100% statement coverage, as branch coverage provides a more comprehensive assessment of your tests' effectiveness.

#### Loop coverage:
**Loop coverage** (informally called **0, 1, 2 testing**) says that if you have. aloop in your code, you should ensure it works properly when:
- The loop is not executed at all (0 iterations)
- The loop is executed exactly once (1 iteration)
- The loop is executed multiple times (2 or more iterations)

If all these cases are tested, you can be more confident that your loop behaves correctly in different scenarios. For example, consider the following code snippet:
```cpp
#include <iostream>

void spam(int timesToPrint)
{
    for (int count{ 0 }; count < timesToPrint; ++count)
         std::cout << "Spam! ";
}
```
To test the loop within this function, you should call it three times: `spam(0)`, `spam(1)`, and `spam(2)`. This way, you cover the cases where the loop is not executed, executed once, and executed multiple times. If all these cases work correctly, then `spam(n)` should work for any non-negative integer `n > 2`.

#### Testing different categories of inputs:
When testingn functions that accepts parameters, or when accepting user inputs, it's important to consider different categories of inputs to ensure your code handles various scenarios correctly. In this context, we will call "category" a group of inputs that share similar characteristics or behaviors. for example:
1. For **integer inputs**, you might consider categories such as:
   - Positive integers (e.g., 1, 42, 1000)
   - Negative integers (e.g., -1, -42, -1000)
   - Zero (0)
   - Boundary values (e.g., INT_MAX, INT_MIN) for overflow testing
2. For **floating point inputs**, you might consider categories such as:
   - Positive, negative, and zero values
   - Special values (e.g., NaN, infinity)
   - Precision boundary values, to test values that are slightly larger or smaller than expected (e.g., `0.1`, `-0.1`, `1.000001`, `0.999999`)
3. For **string inputs**, you might consider categories such as:
   - Empty strings (`""`)
   - Alphanumeric strings (e.g., `"hello123"`)
   - Strings with special characters (e.g., `"hello@world!"`)
   - Strings with whitespace (e.g., `"   "`, `"hello world"`)
4. For **pointer inputs**, you might consider categories such as:
   - Valid pointers (pointing to valid memory locations)
   - Null pointers (`nullptr`)
   - Dangling pointers (pointing to deallocated memory)

#### Summary:
- Code coverage is a measure of how much of your code is executed during testing, helping identify untested areas.
- Statement coverage measures the percentage of executed statements, while branch coverage measures the percentage of executed branches.
- Loop coverage ensures that loops are tested for 0, 1, and multiple iterations.
- Testing different categories of inputs helps ensure your code handles various scenarios correctly.


---

### S03 — 9.3 Common semantic errors in C++
In a previous chapter, we covered syntax errors, which occur when the code violates the rules of the programming language. However, even if your code is syntactically correct, it can still contain **semantic errors**. Semantic errors occur when the code does not behave as intended or produces incorrect results, despite being syntactically valid. These type of errors can be more challenging to identify and fix, as they often require a deeper understanding of the program's logic and intended behavior.

#### Conditional logic errors:
One common type of semantic error is a **conditional logic error**. This occurs when the conditions in control flow statements (like `if`, `else if`, `else`, `switch`) or a loop condition are incorrect or do not cover all possible scenarios. For example:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;

    if (x >= 5) // oops, we used operator>= instead of operator>
        std::cout << x << " is greater than 5\n";

    return 0;
}
```
can give:
```
Enter an integer: 5
5 is greater than 5
```
In this example, the condition `x >= 5` is incorrect if we want to check if `x` is strictly greater than 5. The correct condition should be `x > 5`. This type of error can lead to unexpected behavior in the program.

Here another example using a `for` loop:
```cpp
#include <iostream>

int main()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;

    // oops, we used operator> instead of operator<
    for (int count{ 1 }; count > x; ++count)
    {
        std::cout << count << ' ';
    }

    std::cout << '\n';

    return 0;
}
```
can give:
```
Enter an integer: 5
```
(no output)
In this example, the loop condition `count > x` is incorrect if we want to print numbers from 1 to `x`. The correct condition should be `count < = x`. This type of error can lead to loops that do not execute as intended.

#### Infinite loops:
Another common semantic error is an **infinite loop**. This occurs when the loop's exit condition is never met, causing the loop to run indefinitely. For example:
```cpp
#include <iostream>

int main()
{
    int count{ 1 };
    while (count <= 10) // this condition will never be false
    {
        std::cout << count << ' '; // so this line will repeatedly execute
    }

    std::cout << '\n'; // this line will never execute

    return 0; // this line will never execute
}
```
can give:
```
1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 ...
```
until you terminate the program manually.
In this example, the loop condition `count <= 10` is never updated within the loop, causing the loop to run indefinitely. To fix this, we need to increment `count` within the loop.

Here another example using a `for` loop:
```cpp
#include <iostream>

int main()
{
    for (unsigned int count{ 5 }; count >= 0; --count)
    {
        if (count == 0)
            std::cout << "blastoff! ";
        else
          std::cout << count << ' ';
    }

    std::cout << '\n';

    return 0;
}
```
it is supposed to print `5 4 3 2 1 blastoff!`, but instead it prints:
```
5 4 3 2 1 4294967295 4294967294 4294967293 ...
```
until you terminate the program manually.
In this example, the loop condition `count >= 0` is always true for an unsigned integer, causing the loop to run indefinitely. To fix this, we can change the loop condition to `count > 0` and handle the `0` case separately, or (better) removing the unsigned qualifier.

#### Off-by-one errors:
An **off-by-one error** occurs when a loop iterates one time too many or one time too few. This often happens when the loop's start or end conditions are incorrect. For example:
```cpp
#include <iostream>

int main()
{
    for (int count{ 1 }; count < 5; ++count)
    {
        std::cout << count << ' ';
    }

    std::cout << '\n';

    return 0;
}
```
is supposed to print `1 2 3 4 5`, but instead it prints:
```
1 2 3 4 
```
This happens because the loop condition `count < 5` causes the loop to stop before printing `5`. To fix this, we can change the condition to `count <= 5`.

#### Incorrect operator precedence:
Another common semantic error is **incorrect operator precedence**. This occurs when the order of operations in an expression is not what the programmer intended, leading to unexpected results. For example:
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int y{ 7 };

    if (!x > y) // oops: operator precedence issue
        std::cout << x << " is not greater than " << y << '\n';
    else
        std::cout << x << " is greater than " << y << '\n';

    return 0;
}
```
Because `logical NOT` (`!`) has higher precedence than `greater than` (`>`), the expression `!x > y` is evaluated as `(!x) > y`. Since `!x` evaluates to `false` (or `0`), the condition becomes `0 > 7`, which is false. Therefore, the program incorrectly outputs that `5 is greater than 7`. To fix this, we should use parentheses to clarify the intended logic: `!(x > y)`.

#### Precision issues with floating point types:
When working with floating point types (`float`, `double`), you may encounter **precision issues** due to the way these types represent decimal numbers in binary. This can lead to unexpected results when performing arithmetic operations or comparisons. For example, the following floating point variable does not have enough precision to store the entire number:
```cpp
#include <iostream>

int main()
{
    float f{ 0.123456789f };
    std::cout << f << '\n';

    return 0;
}
```
and the number is rounded to `0.123457`.

In a previous chapter we saw how `operator==` and `operator!=` can give unexpected results when comparing floating point numbers due to precision issues. For example:
```cpp
#include <iostream>

int main()
{
    double d{ 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 + 0.1 }; // should sum to 1.0

    if (d == 1.0)
        std::cout << "equal\n";
    else
        std::cout << "not equal\n";

    return 0;
}
```
will print:
```
not equal
```
due to precision issues in representing `0.1` in binary. The more arithmetic operations you perform, the more these small errors can accumulate, leading to unexpected results.

#### Integral division:
When performing division with integer types, you may encounter **integral division** issues. In C++, when you divide two integers, the result is also an integer, and any fractional part is truncated (not rounded). This can lead to unexpected results if you're not careful. For example:
```cpp
#include <iostream>

int main()
{
    int x{ 5 };
    int y{ 3 };

    std::cout << x << " divided by " << y << " is: " << x / y << '\n'; // integer division

    return 0;
}
```
will print:
```
5 divided by 3 is: 1
```
instead of the expected `1.66667`. To get a floating-point result, you can cast one or both of the integers to a floating-point type:
```cpp
std::cout << x << " divided by " << y << " is: " << static_cast<double>(x) / y << '\n';
```
This will print:
```
5 divided by 3 is: 1.66667
```

#### Accidental null statements:
An **accidental null statement** occurs when a semicolon (`;`) is mistakenly placed after a control flow statement, resulting in an empty statement being executed instead of the intended block of code. For example:
```cpp
#include <iostream>

void blowUpWorld()
{
    std::cout << "Kaboom!\n";
}

int main()
{
    std::cout << "Should we blow up the world again? (y/n): ";
    char c{};
    std::cin >> c;

    if (c == 'y');     // accidental null statement here
        blowUpWorld(); // so this will always execute since it's not part of the if-statement

    return 0;
}
```
will always print `Kaboom!`, regardless of the user's input, because of the semicolon after the `if` condition. To fix this, simply remove the semicolon.

#### Not using a compund statement when one is required:
A **compound statement** (or block) is a group of statements enclosed in curly braces (`{}`) that are treated as a single statement. When using control flow statements like `if`, `else`, `for`, `while`, etc., if you want to execute multiple statements based on a condition, you must use a compound statement. Failing to do so can lead to unexpected behavior. For example:
```cpp
#include <iostream>

void blowUpWorld()
{
    std::cout << "Kaboom!\n";
}

int main()
{
    std::cout << "Should we blow up the world again? (y/n): ";
    char c{};
    std::cin >> c;

    if (c == 'y')
        std::cout << "Okay, here we go...\n";
        blowUpWorld(); // Will always execute.  Should be inside compound statement.

    return 0;
}
```
will always print `Kaboom!`, regardless of the user's input, because the `blowUpWorld` function is not part of the `if` statement. To fix this, you should use a compound statement!

A dangling else, where an `else` clause is associated with the wrong `if` statement, is another common mistake that can be avoided by using compound statements.

#### Using assignment instead of equality inside a conditional:
A common mistake is to use the assignment operator (`=`) instead of the equality operator (`==`) inside a conditional statement. This can lead to unintended behavior, as the assignment operator assigns a value rather than comparing values. For example:
```cpp
#include <iostream>

void blowUpWorld()
{
    std::cout << "Kaboom!\n";
}

int main()
{
    std::cout << "Should we blow up the world again? (y/n): ";
    char c{};
    std::cin >> c;

    if (c = 'y') // uses assignment operator instead of equality operator
        blowUpWorld();

    return 0;
}
```
will always print `Kaboom!`, regardless of the user's input, because the condition `c = 'y'` assigns the value `'y'` to `c`, and return `c`. Then `if(c)` is evaluated. Since `c` is non-zero, it is converted implicitly to `bool` value `true`, causing the `blowUpWorld` function to always execute.

#### Fomratting to use the function call operator when calling a function:
A common mistake is to forget to use the function call operator (`()`) when calling a function. This can lead to unexpected behavior, as the function will not be executed, and instead, the function pointer will be evaluated. For example:
```cpp
#include <iostream>

int getValue()
{
    return 5;
}

int main()
{
    std::cout << getValue << '\n';

    return 0;
}
```
will print something like:
```
0x55f8c3e4d6a9
```
or 

```
true/false
```
instead of `5`, because we forgot to use the function call operator `()`, and it will print the hex address of the function instead of calling it (or converted to a boolean value). To fix this, we should use `getValue()` to call the function.

#### Summary:
- Semantic errors occur when the code does not behave as intended, despite being syntactically correct.
- Common semantic errors include conditional logic errors, infinite loops, off-by-one errors, incorrect operator precedence, precision issues with floating point types, integral division, accidental null statements, not using compound statements when required, using assignment instead of equality in conditionals, and forgetting to use the function call operator when calling a function.
- Identifying and fixing semantic errors often requires a deeper understanding of the program's logic and intended behavior.


---

### S04 — 9.4 Detecting and handling errors in C++
In the previous section, we discussed common semantic errors that can occur in C++ programs. In this section, we will explore techniques for detecting and handling errors in C++ to improve the robustness and reliability of your code.

The most common cause of errors are **assumptions errors**. An assumption error occurs when a programmer makes an incorrect assumption about how a piece of code will behave or what inputs it will receive (e.g., assuming unique IDs when they might not be unique). These errors can lead to unexpected behavior, crashes, or security vulnerabilities in the program. There are three main places where assumption errors can occur:
1. **User input**: Users may provide invalid or unexpected input that the program is not prepared to handle. For example, a program that expects a positive integer may receive a negative integer or a non-numeric value.
2. **Function returns**: Functions may return unexpected values or error codes that the calling code does not handle properly. For example, a function that reads data from a file may return an error code if the file does not exist or is inaccessible.
3. **Function arguments**: Functions may receive invalid or unexpected arguments that can lead to errors during execution. For example, a function that expects a non-null pointer may receive a null pointer, leading to a segmentation fault.

To handle assumption errors effectively, it's important to folllow the **defensive programming** approach. Defensive programming involves writing code that anticipates and handles potential errors or unexpected situations gracefully, rather than assuming that everything will always work as expected.

#### Handling errors in functions:
When writing functions, it's important to consider how to handle errors that may occur during their execution. Here are some common srategies that can be followed:
1. **Handle errors internally**: If a function can recover from an error, it should handle the error internally and return a valid result. For example, if a function reads data from a file and encounters an error, it could return a default value or an empty result instead of propagating the error to the caller.
2. **Return error codes**: If a function cannot recover from an error, it can return an error code to indicate that an error occurred. The calling code can then check the error code and take appropriate action.
3. **Halt the program**: In some cases, it may be appropriate to halt the program if a critical error occurs that cannot be handled gracefully. This can be done using functions like `std::abort()` or by throwing an exception.
4. **Throw exceptions**: C++ provides a built-in mechanism for error handling through exceptions. When an error occurs, a function can throw an exception, which can be caught and handled by the calling code. This allows for more flexible error handling and separation of error handling logic from regular code.

#### 1. Handling errors internally:
If possible, the best way to handle errors is to manage them within the function itself, and recover from them. There are two options here: retry until success (e.g., internet connection is lost, and the function keeps trying to reconnect), or cancel the operation being executed and return a default value (e.g., reading a configuration file fails, so return default configuration values).

An example of second case is:
```cpp
// Silent failure if y=0
void printIntDivision(int x, int y)
{
    if (y != 0)
        std::cout << x / y;
}
```
This can be imporved by notifying the user that the operation could not be completed:
```cpp
void printIntDivision(int x, int y)
{
    if (y != 0)
        std::cout << x / y;
    else
        std::cout << "Error: Could not divide by zero\n";
}
```
In this way, the function handles the error internally and provides feedback to the user without crashing the program.

#### 2. Returning error codes:
Another common approach to handling errors in functions is to return error codes. This allows the calling code to check for errors and take appropriate action. For example:
```cpp
bool printIntDivision(int x, int y)
{
    if (y == 0)
    {
        std::cout << "Error: could not divide by zero\n";
        return false;
    }

    std::cout << x / y;

    return true;
}
```
returns `false` if an error occurred (division by zero), and `true` if the operation was successful. The calling code can then check the return value and handle the error accordingly:
```cpp
int main()
{
    int a{ 10 };
    int b{ 0 };

    if (!printIntDivision(a, b))
    {
        std::cout << "Division failed.\n";
    }

    return 0;
}
```
In this example, the `printIntDivision` function returns a boolean value indicating whether the division was successful or not. The `main` function checks the return value and prints an additional message if the division failed.

In some cases, you can also use some **sentinel values** to indicate errors. A sentinel value is a special value that is used to indicate an error or a special condition, outside the range of possible valid return values. For example:
```cpp
// The reciprocal of x is 1/x, returns 0.0 if x=0
constexpr double error_no_reciprocal { 0.0 }; // could also be placed in namespace

double reciprocal(double x)
{
    if (x == 0.0)
       return error_no_reciprocal;

    return 1.0 / x;
}
```
In this example, the `reciprocal` function returns `0.0` as a sentinel value to indicate that the reciprocal of `0` is undefined, since the reciprocal of any non-zero number is always non-zero, and so `0.0` is outside the range of valid return values.

#### 1. Halting the program - Fatal errors:
In some cases, it may be appropriate to halt the program if a critical error occurs that cannot be handled gracefully. This can be done using functions like `std::abort()` or `std::exit()`. For example:
```cpp
double doIntDivision(int x, int y)
{
    if (y == 0)
    {
        std::cout << "Error: Could not divide by zero\n";
        std::exit(1);
    }
    return x / y;
}
```
In this example, if a division by zero is attempted, the program will print an error message and then terminate with a non-zero exit code, indicating that an error occurred.

#### 4. Throwing exceptions:
C++ provides a built-in mechanism for error handling through exceptions. When an error occurs, a function can throw an exception, which can be caught and handled by the calling code. This allows for more flexible error handling and separation of error handling logic from regular code. In this way, the error can be propagated up the call stack until it is caught and handled appropriately (not only the caller of the function, but any function up the call stack).

#### When to use `std::cout` vs `std::cerr` vs logging:
When handling errors, it's important to consider how to communicate error messages to the user or developer, whether to use `std::cout` (console), `std::cerr` (error console), or logging to a file. 

First we can differentiate two types of applications:
1. **Interactive applications**: These are applications that interact directly with users through a console or graphical user interface (GUI), like games and music apps.
2. **Non-interactive applications**: These are applications that run in the background or as part of a larger system, without direct user interaction, like web servers and data processing scripts.

Within non-interactive applications, we can further differentiate two types:
1. **Tools:** are non-interactive applications that are tipically launched to produce some immediate result, and then terminate after that, like command-line utilities and scripts (e.g., Unix's `grep` command).
2. **Services:** are non-interactive applications that run continuously in the background, often as part of a larger system, like virus scanners and web servers.

Here some rules of thumb:
- Use `std::cout` for all conventional, user-facing text output in interactive applications.
- For an interactive program, use `std::cout` for normal user-facing error messages (e.g., "Your input was invalid, please try again"), and use `std::cerr` or logging for status and diagnostic information that may be helpful for diagnosis issues but not interesting for the user (e.g., "Failed to open configuration file, using default settings").
- For a non-interactive program, use `std::cerr` for error output only (e.g., could not open input file), this allows errors to be handled and parsed differently to normal output.
- For any application type that is transactional in nature (e.g., one that process specific events, such as web requests or database transactions), consider using logging for all error and status messages, as this allows for better tracking and analysis of issues over time.

#### Summary:
- Errors can occur due to incorrect assumptions about user input, function returns, or function arguments.
- Defensive programming involves writing code that anticipates and handles potential errors gracefully.
- Common strategies for handling errors in functions include handling errors internally, returning error codes, halting the program, and throwing exceptions.
- Choosing the appropriate method for communicating error messages (e.g., `std::cout`, `std::cerr`, logging) depends on the type of application and the intended audience for the messages.


---

### S05 — 9.5 `std::cin` and handling invalid input
When reading input from the user using `std::cin`, the user's input is **free-form**; they can enter anything they want, including invalid data that your program may not be prepared to handle. If the user enters invalid data, `std::cin` will enter a **fail state**, which means that subsequent input operations will fail until the fail state is cleared. This can lead to unexpected behavior in your program if you don't handle invalid input properly.

First, let use review how `std::cin` and `operator>>` work:
1. First, leading whitespace (spaces, and newlines in fron of the buffer) is skipped.
2. If the input buffer is now empty, `operator>>` will wait until the user enters some input. Leading whitespaces are again discarded.
3. `operator>>` then extarct as many consecutive characters as possible, until it encounters either a newline character (the end of the input) or a character that is not valid for the type being read (e.g., a letter when reading an integer).

The result of the extraction is as follows:
- If any characters were extracted in step 3 above, extraction is considered successful, and the extracted characters are converted to the target type (if possible) and stored in the provided variable.
- If no characters were extracted in step 3 (e.g., the first character encountered was not valid for the target type), extraction is considered to have failed. The object being extracted to is assigned the value `0` (as of C++11) and any future extractions will immediately fail (until `std::cin` is cleared).

To handle invalid input with `std::cin`, you can follow these steps:
1. **Input validation**: Before processing the input, check if it meets the expected format or criteria. If not, prompt the user to enter valid input.
2. **Clearing the fail state**: If `std::cin` enters a fail state, you can clear it using `std::cin.clear()`, and then discard the invalid input using `std::cin.ignore()`.
3. **Looping until valid input is received**: You can use a loop to repeatedly prompt the user for input until valid data is entered.

#### Validating input:
The processs of checking whether the input meets the expected format or criteria is called **input validation**. For example, if you expect the user to enter a positive integer, you can check if the input is indeed a positive integer before processing it. There are three main ways to do input validation.

**Inline (as the user types)**:
1. Prevent the user from typing invalid inputs in the first place.

**Post-entry (after the user types)**:

2. Let the user enter whatever they want into a string, then validate the string to ensure it meets the expected format before processing it, and convert it to the desired type.
3. Let the user enter whatever they want, let `std::cin` and `operator>>` attempt to extract the input, then handle the error cases.

#### A sample program:
Cosinder the following calculator program that has no error handling:
```cpp
#include <iostream>

double getDouble()
{
    std::cout << "Enter a decimal number: ";
    double x{};
    std::cin >> x;
    return x;
}

char getOperator()
{
    std::cout << "Enter one of the following: +, -, *, or /: ";
    char op{};
    std::cin >> op;
    return op;
}

void printResult(double x, char operation, double y)
{
    std::cout << x << ' ' << operation << ' ' << y << " is ";

    switch (operation)
    {
    case '+':
        std::cout << x + y << '\n';
        return;
    case '-':
        std::cout << x - y << '\n';
        return;
    case '*':
        std::cout << x * y << '\n';
        return;
    case '/':
        std::cout << x / y << '\n';
        return;
    }
}

int main()
{
    double x{ getDouble() };
    char operation{ getOperator() };
    double y{ getDouble() };

    printResult(x, operation, y);

    return 0;
}
```
This program prompts the user to enter two decimal numbers and an arithmetic operator, then performs the specified operation and prints the result. However, it does not handle invalid input, which can lead to unexpected behavior or crashes.
```
Enter a decimal number: 5
Enter one of the following: +, -, *, or /: *
Enter a decimal number: 7
5 * 7 is 35
```

In this example, the possible sources of invalid input are:
- The user may enter a non-numeric value when prompted for a decimal number (e.g., "five" instead of "5").
- The user may enter an invalid operator when prompted for an arithmetic operator (e.g., "%" instead of "+", "-", "*", or "/").
- The user may enter something like `"*q hello"` when prompted for an operator. The `*` will be extracted as the operator, but the remaining characters (`"q hello"`) will remain in the input buffer, potentially causing issues for subsequent input operations.

#### Types of invalid text input:
We can generally separate input text errors into four types:
1. Input extraction succeeds but the input is meaningless to the program (e.g. entering `k` as your mathematical operator).
2. Input extraction succeeds but the user enters additional input (e.g. entering `*q hello` as your mathematical operator).
3. Input extraction fails (e.g. trying to enter `q` into a numeric input).
4. Input extraction succeeds but the user overflows a numeric value.

#### 1. Extraction succeeds but the input is meaningless to the program:
This type of error occurs when the input is successfully extracted, but it does not make sense in the context of the program. For example, if the user is prompted to enter a mathematical operator and they enter `k`, the input is successfully extracted as a character, but `k` is not a valid operator for the calculator program. This will give something like:
```
Enter a decimal number: 5
Enter one of the following: +, -, *, or /: k
Enter a decimal number: 7
5 k 7 is 
```
To handle this type of error, you can validate the input after extraction to ensure it is meaningful to the program. This can be done in three steps:
1. Check if the extracted input is what you were expecting.
2. If so, return the value to the caller.
3. If not, notify the user of the invalid input and prompt them to enter a valid value again. For example, you can modify the `getOperator` function as follows:
```cpp
char getOperator()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char operation{};
        std::cin >> operation;

        // Check whether the user entered meaningful input
        switch (operation)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            return operation; // return it to the caller
        default: // otherwise tell the user what went wrong
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
    } // and try again
}
```
In this way, the function will keep prompting the user until they enter a valid operator.

#### 2. Extraction succeeds but the user enters additional input:
This type of error occurs when the input is successfully extracted, but there are additional characters remaining in the input buffer that may cause issues for subsequent input operations. Comnsider the following exectution:
```
Enter a decimal number: 5*7
Enter one of the following: +, -, *, or /: Enter a decimal number: 5 * 7 is 35
```
The program prints the right answer, but the formatting is messed up. When the user enters `5*7` as the first number, `5` is extracted as the first decimal number, but the remaining characters (`*7`) remain in the input buffer. When the program then prompts for the operator, it immediately reads the `*` from the buffer, and when it prompts for the second number, it reads `7` from the buffer. This is correct, but it is not the intended behavior.

It would be better to ignore any additional input after the first valid input. To handle this type of error, you can use `std::cin.ignore()` to discard any remaining characters in the input buffer after a successful extraction:
```cpp
std::cin.ignore(100, '\n');  // clear up to 100 characters out of the buffer, or until a '\n' character is removed
```
This will discard up to 100 characters from the input buffer, or until a newline character is encountered, whichever comes first, but if there are more than 100 characters remaining, the rest will remain in the buffer.

To ingore all characters until the next newline character, you can use:
```cpp
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // requires #include <limits>
```
`std::numeric_limits<std::streamsize>::max()` returns the maximum value that can be represented by the `std::streamsize` type, effectively allowing you to ignore all characters until a newline is encountered.

Since this line is quite long, we can create a helper function to encapsulate this behavior:
```cpp
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
```
You can then call this function after each successful extraction to clear any remaining input:
```cpp
double getDouble()
{
    std::cout << "Enter a decimal number: ";
    double x{};
    std::cin >> x;

    ignoreLine();
    return x;
}
```

#### 3. Extraction fails:
This type of error occurs when the input extraction fails, meaning that no valid characters were extracted for the expected type. For example, if the user is prompted to enter a decimal number and they enter `a`, the extraction will fail because `a` is not a valid decimal number. This will give:
```
Enter a decimal number: a
Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
Enter one of the following: +, -, *, or /: Oops, that input is invalid.  Please try again.
....
```
When the user enters `a`, that character is placed in the buffer, then `operator>>` tried to extract `a` to variable `x` of type `double`, but it fails because `a` is not a valid `double`. Since no characters were extracted, the extraction fails, and `x` is assigned the value `0.0`. Two things happen now: `a` is left in the buffer, and `std::cin` goes into a fail state. Any subsequent extraction attempts will immediately fail until the fail state is cleared.

In order to get `std::cin` out of the fail state, you need to do three thigns:
1. Detect that prior extraction ha failed by checking `std::cin.fail()`.
2. Put `std::cin` back to normal operation by calling `std::cin.clear()`. `clear()` resets the error flags on `std::cin`, allowing future input operations to proceed.
3. Remove the input that caused the failure from the input buffer using `std::cin.ignore()`.

Here is what this looks like:
```cpp
if (std::cin.fail()) // 1. If the previous extraction failed
{
    // Let's handle the failure
    std::cin.clear(); // 2. Put us back in 'normal' operation mode
    ignoreLine();     // 3. And remove the bad input
}
```
or (better):
```cpp
if (!std::cin) // 1. If the previous extraction failed
{
    // Let's handle the failure
    std::cin.clear(); // 2. Put us back in 'normal' operation mode
    ignoreLine();     // 3. And remove the bad input
}
```

Now, we can incorporate this into our `getDouble` function to handle extraction failures:
```cpp
double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        if (!std::cin) // If the previous extraction failed
        {
            // Let's handle the failure
            std::cin.clear(); // Put us back in 'normal' operation mode
            ignoreLine();     // And remove the bad input
            continue;
        }

        // Our extraction succeeded
        ignoreLine(); // Ignore any additional input on this line
        return x;     // Return the value we extracted
    }
}
```
Since it is fine to call `clear()` and `ignoreLine()` even if the extraction succeeded, we can simplify the code to:
```cpp
double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        bool success { std::cin }; // Remember whether we had a successful extraction
        std::cin.clear();          // Put us back in 'normal' operation mode (in case we failed)
        ignoreLine();              // Ignore any additional input on this line (regardless)

        if (success)               // If we actually extracted a value
            return x;              // Return it (otherwise, we go back to top of loop)
    }
}
```

#### Checking for EOF:
There is another case to address. An end-of-file (EOF) isa. aspecial error state that mean "No more data available". This is normally generated afetr an input operation fails due to no data being avaialble (e.g., no mora data to read from a file). Normally, `std::cin` will not enter EOF, but in some specific cases it will. For example, if the user presses `Ctrl+D` (on Linux/Mac) or `Ctrl+Z` (on Windows) to signal EOF, `std::cin` will enter the EOF state.

When `std::cin` is in the EOF state, the behavior will be OS-dependent. Here what it could happens:
- If the EOF is not the first character of input: All input prior to the EOF will be flushed, and the EOF character is ignored. On windows, any subsequent input will be ignored, except for the `\n` character.
- If the EOF is the first character of input: The EOF error will be set, and the input stream may or may not be disconnected.

Although `std::cin.clear()` will clear an EOF error, if the input stream is disconnected, the next input request will generate another EOF error. Therefore, it is important to check for EOF using `std::cin.eof()` after an input operation fails. If EOF is detected, you should handle it appropriately, such as by terminating the program or prompting the user to provide more input. Here an useful reusable function to check for EOF:
```cpp
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the user entered an EOF
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}
```
This will check for a failed extraction, handle it appropriately, and return `true` if an error was handled, or `false` if the extraction was successful.

#### 4. Extraction succeeds but the user overflows a numeric value:
This type of error occurs when the input is successfully extracted, but the value entered by the user exceeds the range of the target numeric type. For example:
```cpp
#include <cstdint>
#include <iostream>

int main()
{
    std::int16_t x{}; // x is 16 bits, holds from -32768 to 32767
    std::cout << "Enter a number between -32768 and 32767: ";
    std::cin >> x;

    std::int16_t y{}; // y is 16 bits, holds from -32768 to 32767
    std::cout << "Enter another number between -32768 and 32767: ";
    std::cin >> y;

    std::cout << "The sum is: " << x + y << '\n';
    return 0;
}
```
If the user enters `40000` the output will be:
```
Enter a number between -32768 and 32767: 40000
Enter another number between -32768 and 32767: The sum is: 32767
```
In here, `std::cin` goes immmediately into failure mode, but also assigns the closest in-range value to the variable (`32767` in this case). Then, additional inputs are skipped (`y` is never assigned a value, and it is `0` by default). Finally, the sum is calculated as `32767 + 0`, which is `32767`.

These type of errors can be handled the same way as extraction failures, by checking `std::cin.fail()` after each extraction, clearing the fail state, and discarding the invalid input.

#### Putting it all together:
Here is the complete calculator program with error handling for all the types of invalid input discussed above:
```cpp
#include <cstdlib> // for std::exit
#include <iostream>
#include <limits> // for std::numeric_limits

void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the stream was closed
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}

double getDouble()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter a decimal number: ";
        double x{};
        std::cin >> x;

        if (clearFailedExtraction())
        {
            std::cout << "Oops, that input is invalid.  Please try again.\n";
            continue;
        }

        ignoreLine(); // Remove any extraneous input
        return x;     // Return the value we extracted
    }
}

char getOperator()
{
    while (true) // Loop until user enters a valid input
    {
        std::cout << "Enter one of the following: +, -, *, or /: ";
        char operation{};
        std::cin >> operation;

        if (!clearFailedExtraction()) // we'll handle error messaging if extraction failed below
             ignoreLine(); // remove any extraneous input (only if extraction succeded)

        // Check whether the user entered meaningful input
        switch (operation)
        {
        case '+':
        case '-':
        case '*':
        case '/':
            return operation; // Return the entered char to the caller
        default: // Otherwise tell the user what went wrong
            std::cout << "Oops, that input is invalid.  Please try again.\n";
        }
    }
}

void printResult(double x, char operation, double y)
{
    std::cout << x << ' ' << operation << ' ' << y << " is ";

    switch (operation)
    {
    case '+':
        std::cout << x + y << '\n';
        return;
    case '-':
        std::cout << x - y << '\n';
        return;
    case '*':
        std::cout << x * y << '\n';
        return;
    case '/':
        if (y == 0.0)
            break;

        std::cout << x / y << '\n';
        return;
    }

    std::cout << "???";  // Being robust means handling unexpected parameters as well, even though getOperator() guarantees operation is valid in this particular program
}

int main()
{
    double x{ getDouble() };
    char operation{ getOperator() };
    double y{ getDouble() };

    // Handle division by 0
    while (operation == '/' && y == 0.0)
    {
        std::cout << "The denominator cannot be zero.  Try again.\n";
        y = getDouble();
    }

    printResult(x, operation, y);

    return 0;
}
```

#### Summary:
- When reading input with `std::cin`, invalid input can cause the input stream to enter a fail state.
- To handle invalid input, you can use input validation, clear the fail state, and loop until valid input is received.
- Common types of invalid input include meaningless input, additional input, extraction failures, and numeric overflows.
- By implementing proper error handling, you can make your programs more robust and user-friendly.


---

### S06 — 9.6 Assert and static_assert
In a function that takes parameters, the caller may be able to pass arguemnts that are syntactically correct, but semantically invalid. For example:
```cpp
void printDivision(int x, int y)
{
    if (y != 0)
        std::cout << static_cast<double>(x) / y;
    else
        std::cerr << "Error: Could not divide by zero\n";
}
```
In this example, the `printDivision` function checks if the denominator `y` is zero before performing the division. If `y` is zero, it prints an error message instead of attempting to divide by zero.

However, in some cases, you may want to enforce certain conditions on the function parameters at runtime, and terminate the program if those conditions are not met. This is where the `assert` macro comes in. The `assert` macro is used to check a condition at runtime, and if the condition is false, it will print an error message and terminate the program. For example:
```cpp
#include <cassert> // for assert
#include <iostream>

void printDivision(int x, int y)
{
    assert(y != 0 && "Denominator must not be zero"); // Check that y is not zero

    std::cout << static_cast<double>(x) / y;
}
```
In this example, the `assert` macro checks if `y` is not zero before performing the division. If `y` is zero, the program will terminate and print an error message indicating that the denominator must not be zero. Now, let use understand better.

#### Preconditions, invariants, and postconditions:
- A **precondition** is a condition that must be true before a function is executed in order for the function to work correctly. In the example above, the precondition is that `y` must not be zero. Precodintions for a function are best placed at the top of the function body, before any other code is executed.
    ```cpp
    void printDivision(int x, int y)
    {
        if (y == 0) // handle
        {
            std::cerr << "Error: Could not divide by zero\n";
            return; // bounce the user back to the caller
        }

        // We now know that y != 0
        std::cout << static_cast<double>(x) / y;
    }
    ```
- An **invariant** is a condition that must always be true during the execution of a program or within a specific scope. Invariants are often used to ensure the consistency and correctness of data structures or algorithms. This is often used with loops, where loop body will only execute so long as the invariant is true.
    ```cpp
    int sumPositiveNumbers(const std::vector<int>& numbers)
    {
        int sum{ 0 };
        for (int number : numbers)
        {
            assert(number >= 0 && "All numbers must be positive"); // invariant: all numbers must be positive
            sum += number;
        }
        return sum;
    }
    ```
- A **postcondition** is a condition that must be true after a function has executed in order for the function to have worked correctly. Postconditions are best placed at the end of the function body, after all other code has executed.
    ```cpp
    int divide(int x, int y)
    {
        assert(y != 0 && "Denominator must not be zero"); // precondition

        int result{ x / y };

        assert((x == result * y + x % y) && "Result must satisfy the division algorithm"); // postcondition

        return result;
    }
    ```

#### Assertions:
An **assertion** is an expression that will be true unless there is a bug in the program. If the assertion is `true`, the program continues executing normally. If the assertion is `false`, the program will print an error message and terminate (using `std::abort`). Assertions are typically used to check preconditions, invariants, and postconditions in code.

In C++, assertions are implemented using the `assert` macro, which is defined in the `<cassert>` header. The syntax for using `assert` is as follows:
```cpp
#include <cassert> // for assert
assert(condition && "optional error message");
```
where `condition` is the expression to be evaluated. If `condition` is `false`, the program will print the optional error message (if provided) and terminate.

In our example:
```cpp
#include <cassert> // for assert()
#include <cmath> // for std::sqrt
#include <iostream>

double calculateTimeUntilObjectHitsGround(double initialHeight, double gravity)
{
  assert(gravity > 0.0); // The object won't reach the ground unless there is positive gravity.

  if (initialHeight <= 0.0)
  {
    // The object is already on the ground. Or buried.
    return 0.0;
  }

  return std::sqrt((2.0 * initialHeight) / gravity);
}

int main()
{
  std::cout << "Took " << calculateTimeUntilObjectHitsGround(100.0, -9.8) << " second(s)\n";

  return 0;
}
```
When you run this program, it will terminate with an assertion failure because the gravity value is negative:
```
dropsimulator: src/main.cpp:6: double calculateTimeUntilObjectHitsGround(double, double): Assertion 'gravity > 0.0' failed.
```

#### Why the logical AND (`&&`) operator?
A string literal alwways evaluates to `true` in a boolean context, so the expression:
```cpp
condition && "optional error message"
```
will evaluate to `true` if `condition` is `true`, and to `false` if `condition` is `false`. This allows you to provide an optional error message that will be printed when the assertion fails. So logical AND-ing the condition with the string literal will not impact the evaluation of the assertion, but it will provide a useful error message when the assertion fails.

#### Using assertions for unimplemented features:
You can also use assertions to indicate that a feature is not yet implemented. For example:
```cpp
assert(moved && "Need to handle case where student was just moved to another classroom");
```
This assertion will always fail, indicating that the code for handling the case where a student is moved to another classroom has not yet been implemented.

#### NDEBUG macro:
The `assert` macro comes with a small performance cost because each time an assertion is evaluated, the condition must be checked at runtime. In performance-critical code, you may want to disable assertions in release builds to avoid this overhead. This can be done by defining the `NDEBUG` macro before including the `<cassert>` header:
```cpp
#define NDEBUG
#include <cassert> // assert is disabled
```
When `NDEBUG` is defined, all assertions are disabled, and the `assert` macro does nothing. This allows you to include assertions in your code for debugging purposes, while avoiding the performance cost in release builds.

In IDEs and build systems, there is often a built-in way to define `NDEBUG` for release builds, so you don't have to manually add the `#define NDEBUG` line to your code.

#### static_assert:
C++ has also another type of assert called `static_assert`. A **static_assert** is an assertion that is evaluated at compile time, rather than at runtime. This allows you to check conditions that can be determined at compile time, such as type traits or template parameters. `static_assert` is a keyword, so no header file is required to use it. The syntax for using `static_assert` is as follows:
```cpp
static_assert(condition, "error message");
```
where `condition` is the expression to be evaluated at compile time. If `condition` is `false`, the compiler will generate a compilation error with the provided error message. For example:
```cpp
static_assert(sizeof(long) == 8, "long must be 8 bytes");
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");

int main()
{
	return 0;
}
```
If the size of `long` is not `8` bytes or the size of `int` is less than `4` bytes on the target platform, the compiler will generate an error with the corresponding message.

Some useful notes about `static_assert`:
- Because `static_assert` is evaluated at compile time, the condition must be a constant expression that can be evaluated by the compiler.
- `static_assert` can be placed anywhere in the code file (even in the global namespace).
- `static_assert` is not deactivated in release builds (like normal `static_assert`), since it is evaluated at compile time.
- Because the compiler does the evaluation, there is no runtime cost associated with `static_assert`.

> **Best practice:** Favor `static_assert` over `assert()` whenever possible, as it allows you to catch errors at compile time rather than at runtime.

#### Assert vs error handling:
- **Assertions** are used to detect *programming errors* (bugs) during development. They are not meant to handle runtime errors that can occur due to user input or external factors. Assertions should be used to check conditions that should always be true if the program is functioning correctly.
- **Error handling** is used to handle *runtime errors* that can occur during the normal execution of a program, such as invalid user input, file not found errors, or network connection failures. Error handling should be used to gracefully handle these errors and provide appropriate feedback to the user or take corrective actions.

Sometimes, it is not clear whether a condition should be handled with an assertion or with error handling. For example:
```cpp
double getInverse(double x)
{
    return 1.0 / x;
}
```
Here the best option is to use **both**:
```cpp
double getInverse(double x)
{
    assert(x != 0.0);
    if (x == 0.0)
       // handle error somehow (e.g. throw an exception)

    return 1.0 / x;
}
```
In this way, during development, if `getInverse` is called with `0.0`, the assertion will catch the error and terminate the program, allowing you to fix the bug. In production, for a specific release build, the assertion will be disabled, and the function will handle the error gracefully by throwing an exception or taking other appropriate actions.

#### Some assert limitations and warnings:
- Assertions should not have side effects. The expression inside an `assert` should not modify any state or have any side effects, as assertions may be disabled in release builds.
- Assertions should not be used for input validation or error handling. They are meant to catch programming errors, not to handle runtime errors.
- The assertion itself can be improperly written, leading to false positives or negatives. Always ensure that the conditions being asserted are accurate and meaningful.

#### Summary:
- Assertions are used to check conditions that should always be true if the program is functioning correctly.
- The `assert` macro is used for runtime assertions, while `static_assert` is used for compile-time assertions.
- Assertions should be used to check preconditions, invariants, and postconditions in code.
- Assertions are not meant to handle runtime errors that can occur due to user input or external factors; error handling should be used for that purpose.


---

### SX - 9.x Summary and quiz
Try to answer the questions and the quizzes, and then check the solutions in the `exercises` folder.

Enjoy and have fun! :)


---

## 🧭 Summary

This chapter introduced essential techniques for **detecting, testing, and handling errors** in C++. You learned how to identify different kinds of mistakes — from logical bugs to invalid user input — and how to respond to them with clarity and control.

We started with testing methodologies and code coverage metrics, then explored common semantic pitfalls, defensive programming, and safe input handling with `std::cin`. Finally, we discussed how to use `assert` and `static_assert` for runtime and compile-time safety checks.

By integrating these practices into your workflow, you’ll be able to produce C++ code that is not only correct but also **resilient, predictable, and maintainable**.  

### 🧱 Core Concepts You Mastered:
- Software testing fundamentals (unit, integration, system, acceptance)  
- Code coverage metrics and their importance  
- Common semantic errors and debugging techniques  
- Defensive programming and assumption handling  
- Safe and reliable user input validation with `std::cin`  
- Assertions (`assert`, `static_assert`) for logical correctness  
- Proper use of `std::cout`, `std::cerr`, and error reporting practices, using `<cassert>` and `<cstdlib>`