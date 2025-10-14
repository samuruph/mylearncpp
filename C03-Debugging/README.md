# Chapter 03 — Debugging C++ Programs

## Overview
In this chapter, you will learn how to identify and fix common errors in C++ programs. You will explore various types of errors, including syntax errors, semantic errors, and runtime errors. Additionally, you will be introduced to debugging tools and techniques that can help you diagnose and resolve issues in your code effectively.

---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch03_first
./build/ch03_first
```

---

## 🎯 Learning Outcomes

By the end of this chapter, you’ll be able to:

- TODO: write outcomes

---

## Sections

### S01 — 3.1 Syntax and semantic errors
Errors usually fall into two categories:
- **Syntax errors**: Mistakes in the code that violate the rules of the programming language. These errors are typically caught by the compiler during the compilation process.
- **Semantic errors**: Mistakes in the code that lead to incorrect behavior or results, even though the code is syntactically correct. These errors are often harder to detect and may only become apparent during runtime.

#### Syntax errors:
**Syntax errors** occur when you wirte a statement that is not valid according to the rules of the programming language. Examples of syntax errors include:
- Missing semicolons at the end of statements.
- Mismatched parentheses or brackets.
- Incorrect use of keywords or operators.
- Misspelled variable or function names.

#### Semantic errors:
A **semantic error** is an error in meaning. It occurs when a statement is syntactically correct but does not do what the programmer intended. Examples of semantic errors include:
- Using an undeclared variable (compile-time semantic error).
- Type mismatches (compile-time semantic error).
- Logic errors that lead to incorrect results (runtime semantic error).
- Infinite loops (runtime semantic error).

#### Summary:
- Syntax errors are caught at compile-time, while semantic errors may only be detected at runtime, or give wrong results.
- Syntax errors prevent the program from compiling, whereas semantic errors allow the program to compile but lead to incorrect behavior.


---

### S02 — 3.2 The debugging process
Debugging is the process of identifying, analyzing, and fixing errors or bugs in a program. It involves a systematic approach to isolate the source of the problem and implement a solution.

#### A general approach to debugging:
Once a bug is identified, the following steps can be taken to debug the program:
1. Find the root cause of the bug (generally the line of code that is causing the issue).
2. Understand why the bug is occurring (what is the logic error or incorrect assumption).
3. Determine how you will fix the bug (what changes need to be made to the code).
4. Repair the issue (make the necessary code changes).
5. Retest the program to ensure the bug is fixed.
6. Retest to ensure no new issues have been introduced.

#### Example:
Here a buggy piece of code:
```cpp
#include <iostream>

int add(int x, int y) // this function is supposed to perform addition
{
    return x - y; // but it doesn't due to the wrong operator being used
}

int main()
{
    std::cout << "5 + 3 = " << add(5, 3) << '\n'; // should produce 8, but produces 2

    return 0;
}
```
To debug this code, you would follow the steps outlined above:
1. Identify the bug: The output of the program is incorrect (it should be 8, but it produces 2), and the print statement is at line 10.
2. Understand the cause: The `add` function is using the subtraction operator (`-`) instead of the addition operator (`+`).
3. Determine the fix: Change the operator in the `add` function from `-` to `+`.
4. Repair the issue: Update the code with `+` in the `add` function.
5. Retest the program: Run the program again to verify that the output is now correct.
6. Retest for new issues: Ensure that the change did not introduce any new bugs.

#### Summary:
- Debugging is a systematic process that involves identifying, understanding, and fixing bugs in code.
- It is important to follow a structured approach to debugging to ensure that all aspects of the issue are addressed.

---

### S03 — 3.3 A startegy for debugging
In this section, we will start exploring how to find the errors in your code, usually the hardest part of debugging.

#### Finding problems via code inspection:
Code inspection is a manual process of reviewing the code to identify potential issues or bugs. It involves carefully examining the code for syntax errors, logical errors, and other potential problems. For example:
```cpp
int main()
{
    getNames(); // ask user to enter a bunch of names
    sortNames(); // sort them in alphabetical order
    printNames(); // print the sorted list of names

    return 0;
}
```
You expected this program to print the names in alphabetical order, but it printed them in opposite order. By inspecting the code, you might find that the `sortNames` function is incorrectly implemented to sort in descending order instead of ascending order. In this way you narrowd down the source of the problem.

However, code inspection can be time-consuming and may not always be effective in identifying all issues, especially in large or complex codebases.

#### Finding problems by running the program:
Running the program and observing its behavior can help identify issues that may not be apparent through code inspection alone. This approach involves executing the program and monitoring its output, performance, and any error messages that may be generated step by step.

This approach can be generalized as:
1. Figure out how to reproduce the problem consistently.
2. Run the program and observe its behavior to narrow down the source of the problem.
3. Repeat the prior step until you have found the source of the problem.

#### Reproducing the problem:
To effectively debug a program, it is crucial to be able to reproduce the problem consistently. This allows you to observe the issue and test potential fixes. To reproduce a problem, you may need to define some **reproduction steps** that are a list of clear and precise steps that can be followed to cause the problem to occur. Theoretically, this should lead to 100% reproducibility, but in practice, it may be lower due to various factors such as timing issues or environmental differences (e.g., different operating systems or hardware configurations).

#### Homing in on issues:
This step is about figure out where in the code the problem is occurring. This can be done by following the "hi-lo" game (binary search), by starting looking for the problem in between the start of the program and the point where the problem occurs, and then narrowing down the search space by half each time. This can be done by adding print statements or using a debugger to step through the code and observe its behavior.

#### Summary:
- Finding problems in code can be done through code inspection or by running the program and observing its behavior.
- Reproducing the problem consistently is crucial for effective debugging.
- Homing in on issues can be done using a systematic approach, such as the "hi-lo" game.

---

### S04 — 3.4 Basic debugging tactics
In this section, we will explore some basic debugging tactics that can help you identify and fix issues in your code.

#### Tactic 1: Commenting out your code:
One simple way to narrow down the source of a problem is to comment out sections of code and see if the problem persists. By systematically commenting out different parts of the code, you can isolate the section that is causing the issue. For example, in the example of before (it is suppose to print the names in alphabetical order, but it printed them in opposite order):
```cpp
int main()
{
    getNames(); // ask user to enter a bunch of names
    doMaintenance(); // do some random stuff
    sortNames(); // sort them in alphabetical order
    printNames(); // print the sorted list of names

    return 0;
}
```
We might supsect that the `doMaintenance` function has nothing to do with the sorting, so we can comment it out:
```cpp
int main()
{
    getNames(); // ask user to enter a bunch of names
    // doMaintenance(); // do some random stuff
    sortNames(); // sort them in alphabetical order
    printNames(); // print the sorted list of names

    return 0;
}
```
There are three possible outcomes:
1. **The problem goes away**: This indicates that the commented-out code was likely contributing to the issue. You can then focus your debugging efforts on that section of code.
2. **The problem does not change**: This suggests that the commented-out code is not related to the issue. You can then uncomment it and continue commenting out other sections of code to further isolate the problem.
3. **The problem changes**: This indicates that the commented-out code may be interacting with other parts of the program in a way that affects the issue. You may need to investigate further to understand the relationship between the commented-out code and the rest of the program.

#### Tactic 2: Validating your code flow:
Another common issue in a more complex system is that a program is calling a function too many times or too few times (inlcuding not at all). To validate your code flow, you can add print statements at the beginning and end of functions to track when they are called. For example:
```cpp
#include <iostream>

int getValue()
{
std::cerr << "getValue() called\n";
	return 4;
}

int main()
{
std::cerr << "main() called\n";
    std::cout << getValue << '\n';

    return 0;
}
```
By adding these print statements with `std::cerr`, you can observe the program's execution flow and verify that functions are being called as expected. If a function is not being called when it should be, or is being called too many times, you can investigate the surrounding code to identify the issue.

**Tip:** When you add debugging statements, try to not indent them to make them stand out more. If you are using `clang-format`, you can use `// clang-format off` and `// clang-format on` to disable formatting for a section of code, as follows:
```cpp
// clang-format off
std::cerr << "main() called\n";
// clang-format on
```

#### Tactic 3: Printing values:
Printing the values of variables at different points in your program can help you understand how data is being manipulated and identify where things may be going wrong. For example:
```cpp
#include <iostream>

int add(int x, int y)
{
	return x + y;
}

void printResult(int z)
{
	std::cout << "The answer is: " << z << '\n';
}

int getUserInput()
{
	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
	int x{ getUserInput() };
	int y{ getUserInput() };

	int z{ add(x, 5) };
	printResult(z);

	return 0;
}
```
Outputs the following:
```
Enter a number: 4
Enter a number: 3
The answer is: 9
```
Let's add some print statements to see the values of `x`, `y`, and `z`:
```cpp
#include <iostream>

int add(int x, int y)
{
	return x + y;
}

void printResult(int z)
{
	std::cout << "The answer is: " << z << '\n';
}

int getUserInput()
{
	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
	int x{ getUserInput() };
std::cerr << "main::x = " << x << '\n';
	int y{ getUserInput() };
std::cerr << "main::y = " << y << '\n';

	int z{ add(x, 5) };
std::cerr << "main::z = " << z << '\n';
	printResult(z);

	return 0;
}
```
This will output:
```
Enter a number: 4
main::x = 4
Enter a number: 3
main::y = 3
main::z = 9
The answer is: 9
```
From this we can understand that variables `x` and `y` are being read correctly, but `z` is not what we expect (it should be `x + y`, but it is not). So we can modify `add` function the following way:
```cpp
#include <iostream>

int add(int x, int y)
{
std::cerr << "add() called (x=" << x <<", y=" << y << ")\n";
	return x + y;
}

void printResult(int z)
{
	std::cout << "The answer is: " << z << '\n';
}

int getUserInput()
{
	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
	int x{ getUserInput() };
std::cerr << "main::x = " << x << '\n';
	int y{ getUserInput() };
std::cerr << "main::y = " << y << '\n';

	int z{ add(x, 5) };
std::cerr << "main::z = " << z << '\n';
	printResult(z);

	return 0;
}
```
That will output:
```
Enter a number: 4
main::x = 4
Enter a number: 3
main::y = 3
add() called (x=4, y=5)
main::z = 9
The answer is: 9
```
From this we can see that the `add` function is being called with `y` equal to `5` instead of `3`, which is the value we expected. So we can fix the call to `add` in `main`:
```cpp
    int z{ add(x, y) };
```

#### Why using printing statements to debug is not great:
While using print statements can be a quick and easy way to debug code, it has several drawbacks:
- **Cluttered code**: Adding print statements throughout your code can make it harder to read and maintain. It can also lead to a lot of unnecessary output that can be overwhelming.
- **Cluttered output**: The output from print statements can be difficult to parse, especially if there are many statements or if the output is interleaved with other program output.
- **Code modification**: Adding print statements requires modifying the code, which can introduce new bugs or change the behavior of the program.
- **Removing statements**: After debugging, you need to remember to remove all the print statements, which can be tedious, error-prone, and not reusable.

#### Summary:
- Commenting out code, validating code flow, and printing variable values are basic debugging tactics that can help identify and fix issues in code.
- You can use `std::cerr` to print debugging information without interfering with the program's standard output.
- While print statements can be useful for debugging, they can also clutter code and output, and require code modification.


---

### S05 — 3.5 More debugging tactics
In this section we will explore how to mitigate the issues of using print statements to debug code.

#### Conditionalizing your debugging code:
Consider the followong example:
```cpp
#include <iostream>

int getUserInput()
{
std::cerr << "getUserInput() called\n";
	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
std::cerr << "main() called\n";
    int x{ getUserInput() };
    std::cout << "You entered: " << x << '\n';

    return 0;
}
```
This code will always print the debugging statements, which can clutter the output, or you will have to remove them or comment them (not ideal). A better approach is to use preprocessor directives to conditionally include or exclude debugging code. For example:
```cpp
#include <iostream>

#define ENABLE_DEBUG // comment out to disable debugging

int getUserInput()
{
#ifdef ENABLE_DEBUG
std::cerr << "getUserInput() called\n";
#endif
	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
#ifdef ENABLE_DEBUG
std::cerr << "main() called\n";
#endif
    int x{ getUserInput() };
    std::cout << "You entered: " << x << '\n';

    return 0;
}
```
By defining or undefining the `ENABLE_DEBUG` macro, you can easily enable or disable the debugging statements without modifying the code itself.

#### Using a logger:
An alternative approach to using preprocessor directives is to send the debugging to a logging system, and the process of generating log messages is called **logging**. Logs are typically write on a file, called a **log file**, but they can also be sent to other destinations, such as the console or a remote server.

C++ contains an output stream called `std::clog` that is intended for logging messages, however by default it writes to standard error stream (same as `std::cerr`). While you could redirect `std::clog` to a file, it is often more convenient to use a dedicated third-party logging library that provides more features and flexibility. A popular choice is `plog`, which is a simple and lightweight logging library for C++. For example:
```cpp
#include <plog/Log.h> // Step 1: include the logger headers
#include <plog/Initializers/RollingFileInitializer.h>
#include <iostream>

int getUserInput()
{
	PLOGD << "getUserInput() called"; // PLOGD is defined by the plog library

	std::cout << "Enter a number: ";
	int x{};
	std::cin >> x;
	return x;
}

int main()
{
	plog::init(plog::debug, "Logfile.txt"); // Step 2: initialize the logger

	PLOGD << "main() called"; // Step 3: Output to the log as if you were writing to the console

	int x{ getUserInput() };
	std::cout << "You entered: " << x << '\n';

	return 0;
}
```
This code will create a log file called `Logfile.txt` in the current directory, and write the debugging messages to it:
```
2018-12-26 20:03:33.295 DEBUG [4752] [main@19] main() called
2018-12-26 20:03:33.296 DEBUG [4752] [getUserInput@7] getUserInput() called
```
With `plog`, you can temporary disable logging by changing the log level to `none`:
```cpp
plog::init(plog::none , "Logfile.txt"); // plog::none eliminates writing of most messages, essentially turning logging off
```

#### Summary:
- You can use preprocessor directives to conditionally include or exclude debugging code.
- Using a logging library like `plog` can provide more features and flexibility for logging messages.
- Logging can help keep your code clean and organized while still providing valuable debugging information.


---

### S06 — 3.6 Using and integrated debugger. Stepping
In this section, we will explore how to use an integrated debugger to step through your code and identify issues.

#### The debugger:
A **debugger** is a computer program that allows the programmer to control how another program executes and examine the **program state** (variables, memory, etc.) while that program is running. The debugger allows the user to precisely control the exectution of the program, including pausing execution, stepping through code line by line, and inspecting (and modifying) variables and memory.

Later debuggers, are now integrated into IDEs, such as Visual Studio, CLion, and Eclipse. These **integrated debuggers** provide a graphical interface that makes it easier to use the debugger's features.

#### Stepping:
Stepping is the process of executing a program one line at a time, allowing the programmer to closely observe the program's behavior and state at each step. This can be useful for identifying issues in the code, as well as for understanding how the code works. There are several types of stepping:
- **Step into**: This command allows you to step into a function call, allowing you to see the code inside the function and how it is executed.
-












## 🧭 Summary

TODO: write summary

### 🧱 Core Concepts You Mastered:
- TODO: list concepts