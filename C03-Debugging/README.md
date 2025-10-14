# Chapter 03 — Debugging C++ Programs

## Overview
In this chapter, you’ll learn how to **find, analyze, and fix errors** in your C++ programs using a structured and methodical approach.  
We’ll explore the main **types of errors** — syntax, semantic, and runtime — and how to address them effectively. You’ll also discover **core debugging techniques** such as code inspection, adding temporary print statements, using **conditional compilation**, and employing **logging libraries**.  

Finally, you’ll gain hands-on experience with **integrated debuggers** (like VS Code’s), learning how to **set breakpoints**, **step through code**, **inspect variables**, and **analyze the call stack** to pinpoint issues. The chapter concludes with best practices for **defensive programming**, **testing**, and **error prevention** — essential habits for writing robust, maintainable code.

---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch03_first
./build/ch03_first
```

---

## 🎯 Learning Outcomes

By the end of this chapter, you will be able to:
- 🧩 Identify and distinguish between syntax, semantic, and runtime errors.
- 🧠 Apply a systematic debugging process — from finding the cause to verifying the fix.
- 🧾 Use debugging tactics such as commenting out code, printing values, and validating code flow.
- ⚙️ Leverage preprocessor directives (#ifdef, #define) to enable or disable debugging output.
- 🪵 Implement logging using libraries like plog for cleaner, configurable debugging.
- 🧭 Operate an integrated debugger: run to cursor, set breakpoints, step into/over/out, and inspect variables.
- 🧱 Interpret the call stack to trace program execution and locate logical - errors.
- 🧰 Apply defensive programming techniques to prevent errors before they - occur.
- 🧪 Design and run simple tests (unit and integration) to verify correctness - and prevent regressions.
- 🚀 Adopt coding habits that minimize bugs — small, focused functions, readability, and consistent refactoring.

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

### S06 — 3.6 Using and integrated debugger: Stepping
In this section, we will explore how to use an integrated debugger to step through your code and identify issues.

#### The debugger:
A **debugger** is a computer program that allows the programmer to control how another program executes and examine the **program state** (variables, memory, etc.) while that program is running. The debugger allows the user to precisely control the exectution of the program, including pausing execution, stepping through code line by line, and inspecting (and modifying) variables and memory.

Later debuggers, are now integrated into IDEs, such as Visual Studio, CLion, and Eclipse. These **integrated debuggers** provide a graphical interface that makes it easier to use the debugger's features. To use the integrated debugger in VSCode, you need to run the program clicking on the triangle on the top right corner, and selecting "Debug C/C++ File". 

You can set **breakpoints** in your code by clicking in the gutter next to the line numbers. A breakpoint is a marker that tells the debugger to pause execution when it reaches that line of code. Once the program is paused at a breakpoint, you can inspect the program state, including variable values and memory contents.

#### Stepping:
Stepping is the process of executing a program one line at a time, allowing the programmer to closely observe the program's behavior and state at each step. This can be useful for identifying issues in the code, as well as for understanding how the code works. There are several types of stepping:
- **Step into**: This command executes the next statement in the normal execution path of the program, and then it pauses execution again. If the next statement is a function call, the debugger will enter that function and pause at the first line of code inside the function.
- **Step over**: This command executes the next statement in the normal execution path of the program, but if the next statement is a function call, the debugger will execute the entire function and pause at the next line of code after the function call.
- **Step out**: This command continues execution until the current function returns, and then it pauses execution at the line of code that called the function.
- **Step back**: Some debuggers support stepping backwards, allowing the programmer to reverse the execution of the program one step at a time. This can be useful for understanding how the program reached its current state. However, not all debuggers support this feature (e.g., current VSCode C++ debugger does not).

#### Summary:
- A debugger is a tool that allows you to control the execution of a program and inspect its state.
- Integrated debuggers provide a graphical interface for using debugger features.
- Stepping allows you to execute a program one line at a time, helping you identify issues and understand how the code works.


---

### S07 — 3.7 Using an integrated debugger: Running and breakpoints
In this section, we will explore how to use an integrated debugger to run your code and set breakpoints.

#### Run to cursor:
The **Run to cursor** feature allows you to quickly execute your program up to a specific line of code. This can be useful for quickly reaching a specific point in your code without having to set a breakpoint. To use this feature, simply right-click on the line of code where you want to pause execution and select "Run to cursor" from the context menu. The debugger will then execute the program up to that line and pause execution.

#### Continue:
The **Continue** command resumes the execution of the program until the next breakpoint is reached or the program finishes executing. This can be useful for quickly running through sections of code that you are not interested in debugging. To use this command, simply click the "Continue" button in the debugger toolbar.

#### Breakpoints:
Breakpoints are markers that tell the debugger to pause execution when it reaches a specific line of code. You can set breakpoints by clicking in the gutter next to the line numbers in your code editor. Once a breakpoint is set, the debugger will pause execution at that line, allowing you to inspect the program state and variables.

You can manage breakpoints using the Breakpoints panel in the debugger sidebar. This panel allows you to enable, disable, or remove breakpoints, as well as view all the breakpoints that are currently set in your code.

#### Summary:
- The "Run to cursor" feature allows you to quickly execute your program up to a specific line of code.
- The "Continue" command resumes program execution until the next breakpoint or the end of the program.
- Breakpoints allow you to pause execution at specific lines of code for inspection and debugging.


---

### S08 — 3.8 Using an integrated debugger: Watching variables
In this section, we will explore how to use an integrated debugger to watch variables and monitor their values during program execution.

#### Watching variables:
Watching variables allows you to monitor the values of specific variables as your program executes. This can be useful for identifying issues in your code, as well as for understanding how the code works. To quickly watch variables you can go over the specific variable in your code and hover the mouse over it. A tooltip will appear showing the current value of the variable. This of course works well for a quick inspection, but if you want to keep track of a variable over time, you can add it to the watch list.


#### The watch window (VSCode):
To watch variables in VSCode, you can use the **"Run and Debug"** (play icon with a bug) sidebar. In the "Variables" section, you can see the local variables in the current scope, as well as any global variables. You can also add specific variables to the "Watch" section by clicking the "+" button and entering the variable name. This will allow you to monitor the value of that variable as you step through your code. In the "Call Stack" section, you can see the current function call stack, which can help you understand how your program reached its current state. In the "Breakpoints" section, you can manage your breakpoints, including enabling, disabling, or removing them.

#### Debug console (VSCode):
The **Debug Console** in VSCode (close to the terminal tab) allows you to evaluate expressions and execute commands while your program is paused in the debugger. You can use the Debug Console to inspect variable values, call functions, and execute arbitrary code. This can be useful for quickly testing hypotheses about your code and understanding how it works.

#### Summary:
- Watching variables allows you to monitor their values during program execution.
- The "Run and Debug" sidebar in VSCode provides a convenient way to view and manage variables, call stacks, and breakpoints.
- The Debug Console in VSCode allows you to evaluate expressions and execute commands while your program is paused in the debugger.


---

### S09 — 3.9 Using an integrated debugger: The call stack
The **call stack** is a list of all the active functions that have been called to get at the current point of execution in a program. Each time a function is called, a new entry is added to the top of the call stack. When a function returns, its entry is removed from the top of the stack. The call stack provides a way to trace the sequence of function calls that led to the current point of execution.

#### The call stack window (VSCode):
In VSCode, the call stack can be viewed in the "Call Stack" section of the "Run and Debug" sidebar. This section displays the current function call stack, with the most recent function call at the top. You can click on any entry in the call stack to navigate to the corresponding line of code in the editor. This can be useful for understanding how your program reached its current state and for identifying issues in your code.

For example, consider the following code:
```cpp
#include <iostream>

void a()
{
	std::cout << "a() called\n";
}

void b()
{
	std::cout << "b() called\n";
	a();
}

int main()
{
	a();
	b();

	return 0;
}
```
If you set a breakpoint in the `a` function at line 5 and run the debugger, the call stack will show the sequence of function calls that led to the current point of execution. When the breakpoint is hit, the call stack will look like this:
```
  a()  (line 5)
  main()  (line 18)
```
This indicates that the `a` function was called from the `main` function at line 18. If you continue execution and hit the breakpoint again when `a` is called from `b`, the call stack will look like this:
```
  a()  (line 5)
  b()  (line 12)
  main()  (line 19)
```
This indicates that the `a` function was called from the `b` function at line 12, which was in turn called from the `main` function at line 19.

#### Summary:
- The call stack is a list of active function calls that led to the current point of execution.
- The call stack can be viewed in the "Call Stack" section of the "Run and Debug" sidebar in VSCode.
- The call stack can help you understand how your program reached its current state and identify issues in your code.


---

### S10 — 3.10 Finding issues before they become problems
In this section, we will explore some techniques for finding issues in your code before they become problems.

#### Don't make errors:
The best way to avoid bugs is to not introduce them in the first place. here is a list of some techniques that can help you avoid introducing bugs in your code:
- Follow best practices and coding standards.
-  Do not porgram when tired or distracted.
- Understand where common pitfalls are for a programming language.
- Keep your functions small and focused.
- Use standard libraries and frameworks.
- Comment your code.
- Start with simple code and gradually add complexity.
- Avoid clever/non-obvious code.
- Optimize for readability and maintainability.
- Use version control to track changes and revert to previous versions if necessary.
- Review your code regularly and refactor when necessary.
- Take breaks and step away from the code to gain a fresh perspective.

#### Refactoring your code:
Refactoring is the process of restructuring existing code without changing its external behavior. The goal of refactoring is to improve the code's readability, maintainability, and performance. Refactoring can help you identify and fix issues in your code before they become problems. Some common refactoring techniques include:
- Renaming variables and functions to improve clarity.
- Extracting functions to reduce code duplication and improve modularity.
- Simplifying complex logic to improve readability.
- Removing unused code to reduce clutter.
- Improving code structure to enhance maintainability.
- Improving performance by optimizing algorithms and data structures.
- Adding comments and documentation to improve understanding.

#### An introduction to defensive programming:
Defensive programming is a programming approach that emphasizes writing code that is robust and resilient to errors and unexpected inputs. The goal of defensive programming is to anticipate and handle potential issues before they become problems. Some common defensive programming techniques include:
- Input validation: Check that input values are within expected ranges and formats.
- Error handling: Use try-catch blocks to handle exceptions and errors gracefully.
- Assertions: Use assertions to check for conditions that should always be true.
- Logging: Use logging to track program execution and identify issues.
- Code reviews: Have other developers review your code to identify potential issues.
- Testing: Write unit tests and integration tests to verify that your code works as expected.

#### An introduction to testing functions:
Testing is the process of verifying that your code works as expected. Testing can help you identify and fix issues in your code before they become problems. Some common testing techniques include:
- **Unit testing**: Test individual functions and components in isolation.
- **Integration testing**: Test how different components work together.
- **System testing**: Test the entire system to ensure it meets requirements.
- **Regression testing**: Test that changes to the code do not introduce new issues.
- **Automated testing**: Use tools to automate the testing process and run tests frequently.
- **Test-driven development (TDD)**: Write tests before writing code to ensure that the code meets requirements.

Here a simple example of Unit testing:
```cpp
#include <iostream>

int add(int x, int y)
{
	return x + y;
}

void testadd()
{
	std::cout << "This function should print: 2 0 0 -2\n";
	std::cout << add(1, 1) << ' ';
	std::cout << add(-1, 1) << ' ';
	std::cout << add(1, -1) << ' ';
	std::cout << add(-1, -1) << ' ';
}

int main()
{
	testadd();

	return 0;
}
```
This code defines a simple `add` function and a `testadd` function that tests the `add` function with a few different inputs. When you run the program, it will print the expected output, allowing you to verify that the `add` function works as intended.

#### An introduction to constraints:
Constraints are rules or conditions that must be met in order for a program to function correctly. Constraints can help you identify and fix issues in your code before they become problems. Some common types of constraints include:
- **Type constraints**: Ensure that variables and functions are used with the correct types.
- **Value constraints**: Ensure that variables and functions are used with valid values.
- **State constraints**: Ensure that the program is in a valid state before performing certain operations.
- **Performance constraints**: Ensure that the program meets performance requirements.
- **Security constraints**: Ensure that the program is secure and does not expose vulnerabilities.

#### Shotgunning for general issues:
Programmers tend to make certain kinds of common mistakes, and some of those mistakes can be discovered by programs trained to look for them. These programs, generally known as **static analysis tools**, can analyze your code without executing it and identify potential issues.

#### Summary:
- Avoid introducing bugs by following best practices and coding standards.
- Refactor your code to improve readability, maintainability, and performance.
- Use defensive programming techniques to anticipate and handle potential issues.
- Test your code to verify that it works as expected.
- Use constraints to ensure that your program meets requirements.


---

### SX - 3.x Chapter 3 summary and quiz
Unfortunately, no `sx-questions` folder for this chapter, you can try to debug a previous program you wrote. 

Have fun :)


--- 

## 🧭 Summary

Debugging is not just about fixing mistakes — it’s about **understanding program behavior**.  
Throughout this chapter, you learned how to **analyze errors**, **trace logic**, and **use debugging tools** to systematically locate problems. You practiced several debugging tactics (like commenting out code, using print statements, or logging), and learned how to make them more manageable through **conditional compilation** and **logging frameworks**.

You also explored how to use an **integrated debugger** in VS Code to step through execution, inspect variables, and study the **call stack**, giving you deeper insight into how your code actually runs.  
The chapter concluded with **preventive strategies**: defensive programming, testing, and refactoring — the tools of a disciplined, confident C++ developer.

### 🧱 Core Concepts You Mastered
- ⚙️ Error Types — Syntax, semantic, and runtime errors, and how to detect them.
- 🔍 Debugging Process — Step-by-step approach to isolate, understand, and fix bugs.
- 🧩 Debugging Techniques — Code inspection, print debugging, conditional compilation, and logging.
- 🐞 Integrated Debugger — Using breakpoints, stepping, and watching variables effectively.
- 🧠 Call Stack Analysis — Understanding how execution flows through nested function calls.
- 🧰 Defensive Programming — Writing robust code that anticipates and handles unexpected behavior.
- 🧪 Testing & Validation — Using unit tests and assertions to ensure correctness.
- 🚧 Prevention Mindset — Avoiding bugs through best practices, code reviews, and refactoring discipline.

✨ **Key takeaway:** Debugging is both a skill and a mindset.  
The best programmers don’t write bug-free code — they write code that’s **easy to debug**, **test**, and **trust**.