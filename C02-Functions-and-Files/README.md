# Chapter 02 — C++ Basics: Functions and Files

## Overview
This chapter takes you from “I can write `main()`” to “I can **design and structure programs** with clear, reusable functions.”  
You’ll learn how to declare, define, and call functions; return values vs `void`; pass data via parameters; manage **local scope & lifetime**; and organize multi-file projects with **headers**, **forward declarations**, and **include guards**.  
By the end, you’ll be comfortable splitting logic into small units, compiling multiple translation units, and avoiding naming collisions with **namespaces** and proper header hygiene.


---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch02_first
./build/ch02_first
```


---

## 🎯 Learning Outcomes
By the end of this chapter, you will be able to:

- ⚙️ **Explain** the difference between function **declaration**, **definition**, and **call**.  
- ✨ **Write** both value-returning and `void` functions, using `return` correctly and safely.  
- 🎯 **Use** parameters and arguments effectively — including nested calls and evaluation order.  
- 📦 **Apply** local **scope** and **lifetime** rules; understand when temporaries are created and destroyed.  
- 🧩 **Organize** code across multiple files and understand how separate **translation units** are compiled and linked.  
- 📄 **Create** and use **header files** with proper guards (`#ifndef` / `#define` / `#endif` or `#pragma once`).  
- 🚫 **Avoid** One Definition Rule (ODR) violations by keeping one definition and multiple consistent declarations.  
- 🧭 **Prevent** naming collisions using **namespaces** and disciplined include practices.  
- ⚡ **Leverage** the **preprocessor** (`#include`, `#define`, and conditionals) responsibly to manage builds.  
- 🧠 **Adopt** clean design habits — small, focused functions with clear purpose and reusable interfaces.



---

## Sections

### S01 — 2.1 Introduction to functions
A **function** is a reusable sequence of statements that performs a specific task.
It is good to break your code into functions to improve readability and reusability, introducing **user-defined functions**.

#### Definitions:
- **Function declaration**: tells the compiler about a function's name, return type, and parameters.
- **Function definition**: specifies the function's body.
- **Function call**: invokes the function to execute its code.

#### Examples:
Here's a simple example of a function in C++:
```cpp
returnType functionName() // This is the function header (tells the compiler about the existence of the function)
{
    // This is the function body (tells the compiler what the function does)
}
functionName(); // This is a function call (invokes the function)
```
Here's a complete example:
```cpp
#include <iostream> // for std::cout

// Definition of user-defined function doPrint()
// doPrint() is the called function in this example
void doPrint()
{
    std::cout << "In doPrint()\n";
}

// Definition of user-defined function main()
int main()
{
    std::cout << "Starting main()\n";
    doPrint();                        // Interrupt main() by making a function call to doPrint().  main() is the caller.
    std::cout << "Ending main()\n";   // This statement is executed after doPrint() ends

    return 0;
}
```
that produces the output:
```
Starting main()
In doPrint()
Ending main()
```

#### Notes:
- Function can be called more than once.
- Function can call other functions.
- Declare functions before calling them (or use function prototypes).
- `main()` is a special function that serves as the entry point of a C++ program
- **Nested function**  (a function defined inside another function) is not allowed in C++. For example, the following code will produce a compilation error:
    ```cpp
    void outerFunction() {
        void innerFunction() { // Error: nested function definition
            // ...
        }
    }
    ```

#### Summary:
- A function is a reusable sequence of statements that performs a specific task.
- A function has a declaration, a definition, and can be called.
- Functions help in organizing code and improving readability.

---

### S02 — 2.2 Function return values (value-returning functions)
A function can return a value to the caller using the `return` statement.

#### Return by value
When a function returns a value, it sends a **copy** of that value back to the caller. To return a value from a function, you need to:
- Specify the return type in the function declaration and definition.
    ```cpp
    returnType functionName() {
        // function body
    }
    ```
- Use the `return` statement inside the function to return a value of the specified type.
    ```cpp
    return value; // value must be of type returnType
    ```

#### Example:
Here's an example of a function that returns an integer value:
```cpp
#include <iostream>

int getValueFromUser() // this function now returns an integer value
{
 	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;

	return input; // return the value the user entered back to the caller
}

int main()
{
	int num { getValueFromUser() }; // initialize num with the return value of getValueFromUser()

	std::cout << num << " doubled is: " << num * 2 << '\n';

	return 0;
}
```

#### `main()` return type
In C++, there are 2 special rules for the `main()` function:
- `main()` must have a return type of `int`.
- Explicit function calls to `main()` are not allowed.
```cpp
void foo()
{
    main(); // Compile error: main not allowed to be called explicitly
}

void main() // Compile error: main not allowed to have non-int return type
{
    foo();
}
```
Note that if `main()` reaches the end of its body without encountering a `return` statement, it will automatically return `0` to the operating system, indicating successful completion.

#### Status codes:
The return value of `main()` is used as the program's **exit status code**. By convention, a return value of `0` indicates successful completion, while a non-zero value indicates an error or abnormal termination.
```cpp
int main()
{
    // program logic
    return 0; // indicate successful completion
}
```

#### Undefined behavior:
If a function with a non-`void` return (value-returning function) reaches the end of its body without encountering a `return` statement, the behavior is undefined. This means that the program may exhibit unpredictable behavior, including crashes or incorrect results. For example:
```cpp
int faultyFunction() {
    // No return statement here
} // Undefined behavior if this function is called
```

#### Notes:
- A function can only return one value. If you need to return multiple values, consider using structures, classes, or `std::tuple` (we will see this later).
- The `return` statement immediately exits the function, so any code after it will not be executed.
- You can have multiple `return` statements in a function, but only one will be executed per function call.
- The return type of a function must match the type of the value being returned.

#### Example:
Here an example of a code that can benefit from functions:
```cpp
#include <iostream>

int main()
{
	int x{};
	std::cout << "Enter an integer: ";
	std::cin >> x;

	int y{};
	std::cout << "Enter an integer: ";
	std::cin >> y;

	std::cout << x << " + " << y << " = " << x + y << '\n';

	return 0;
}
```
We can refactor it using functions:
```cpp
#include <iostream>

int getValueFromUser()
{
 	std::cout << "Enter an integer: ";
	int input{};
	std::cin >> input;

	return input;
}

int main()
{
    int x{ getValueFromUser() }; // first call to getValueFromUser
    int y{ getValueFromUser() }; // second call to getValueFromUser

    std::cout << x << " + " << y << " = " << x + y << '\n';

    return 0;
}
```

#### Summary:
- A function can return a value to the caller using the `return` statement.
- The return type of the function must match the type of the value being returned.
- `main()` must have a return type of `int` and cannot be called explicitly.
- In C++ nested functions are not allowed.


---

### S03 — 2.3 Void functions (non-value returning functions)
A function that does not return a value is called a **void function**. It has a return type of `void`.
```cpp
#include <iostream>

// void means the function does not return a value to the caller
void printHi()
{
    std::cout << "Hi" << '\n';

    // This function does not return a value so no return statement is needed
}

int main()
{
    printHi(); // okay: function printHi() is called, no value is returned

    return 0;
}
```

#### Notes:
- A `void` function doesn't need a `return` statement, but you can use `return;` to exit the function early.
- A `void` function cannot return a value. Attempting to do so will result in a compilation error.
    ```cpp
    void printHi()
    {
        return 42; // Compile error: cannot return a value from a void function
    }
    ```
- You can call a `void` function as a standalone statement or as part of an expression, but you cannot assign its result to a variable. For example, in the following code, the line `std::cout << printHi();` will produce a compile error because `printHi()` does not return a value:
    ```cpp
    #include <iostream>

    // void means the function does not return a value to the caller
    void printHi()
    {
        std::cout << "Hi" << '\n';
    }

    int main()
    {
        printHi(); // okay: function printHi() is called, no value is returned

        std::cout << printHi(); // compile error

        return 0;
    }
    ```

#### Summary:
- A void function does not return a value to the caller.
- A void function can use `return;` to exit early, but cannot return a value.
- A void function can be called as a standalone statement, but its result cannot be assigned to a variable.


---

### S04 — 2.4 Introduction to function parameters and arguments
Functions can accept input values called **parameters** (or **function parameters**) to perform operations based on those values. When calling a function, you provide **arguments** (or **actual parameters**) to the function.

```cpp
#include <iostream>

// Function that takes two parameters
int add(int a, int b)
{
    return a + b;
}

int main()
{
    int x{ 5 };
    int y{ 10 };

    // Calling the function with arguments
    int result{ add(x, y) };

    std::cout << "The sum is: " << result << '\n';

    return 0;
}
```

#### Function parameters and arguments
- **Function parameters** are the variables defined in the header of the function. They act as placeholders for the values that will be passed to the function when it is called.
    ```cpp
    int add(int a, int b) // a and b are function parameters
    {
        return a + b;
    }
    ```
- **Function arguments** are the actual values or expressions passed to the function when it is called.
    ```cpp
    int main()
    {
        int x{ 5 };
        int y{ 10 };

        // Calling the function with arguments
        int result{ add(x, y) };  // x and y are function arguments

        std::cout << "The sum is: " << result << '\n';

        return 0;
    }
    ```

When the function is called, the values of the arguments are copied into the corresponding parameters. In the example above, when `add(x, y)` is called, the value of `x` (5) is copied into parameter `a`, and the value of `y` (10) is copied into parameter `b`.

#### Notes:
- You can use return values from functions as arguments for other functions.
    ```cpp
    int main()
    {
        int x{ 5 };
        int y{ 10 };

        // Using the return value of add() as an argument for another call to add()
        std::cout << "The result is: " << add(add(x, y), 20) << '\n'; // prints 35

        return 0;
    }
    ```
- The number and types of arguments must match the number and types of parameters in the function declaration.
- Functions used as arguments are run before the outer function.

#### Examples:
Let's look at a few more examples of functions with parameters and arguments.
```cpp
#include <iostream>

int add(int x, int y)
{
    return x + y;
}

int multiply(int z, int w)
{
    return z * w;
}

int main()
{
    std::cout << add(4, 5) << '\n'; // within add() x=4, y=5, so x+y=9
    std::cout << add(1 + 2, 3 * 4) << '\n'; // within add() x=3, y=12, so x+y=15

    int a{ 5 };
    std::cout << add(a, a) << '\n'; // evaluates (5 + 5)

    std::cout << add(1, multiply(2, 3)) << '\n'; // evaluates 1 + (2 * 3)
    std::cout << add(1, add(2, 3)) << '\n'; // evaluates 1 + (2 + 3)

    return 0;
}
```
this produces the output:
```
9
15
10
7
6
```

#### Unreferenced parameters and unnamed parameters:
- If a function parameter is not used in the function body, it is called an **unreferenced parameter**. This is not an error, but it may indicate that the parameter is unnecessary.
    ```cpp
    void printValue(int value, int unusedParam) // unusedParam is unreferenced
    {
        std::cout << "Value: " << value << '\n';
    }
    ```
- If a function parameter is not used and you want to avoid compiler warnings, you can omit its name in the function definition. This is called an **unnamed parameter**.
    ```cpp
    void printValue(int value, int /*unusedParam*/) // unnamed parameter
    {
        std::cout << "Value: " << value << '\n';
    }
    ``` 

#### Summary:
- Functions can accept input values called parameters to perform operations based on those values.
- When calling a function, you provide arguments to the function.
- Function parameters are the variables defined in the function header, while function arguments are the actual values passed to the function.
- The number and types of arguments must match the number and types of parameters in the function declaration.


---

### S05 — 2.5 Introduction to local scope
**Local scope** refers to the visibility and lifetime of variables defined within a specific block of code, such as a function. Variables defined inside the body of a function are only accessible within that function. These variables are called **local variables**.

#### Example:
```cpp
#include <iostream>

void myFunction()
{
    int localVar{ 42 }; // localVar is only accessible within myFunction
    std::cout << "Local variable: " << localVar << '\n';
}

int main()
{
    myFunction();
    // std::cout << localVar; // Error: localVar is not accessible here
    return 0;
}
```

#### Local variable lifetime:
Local variables are created when the function is called and destroyed when the function exits. This means that each time a function is called, a new instance of its local variables is created. The **lifetime** of a local variable is the time between its creation and destruction.
```cpp
int add(int x, int y) // x and y created and initialized here
{
    int z{ x + y };   // z created and initialized here

    return z;
} // x, y, and z destroyed here 
```
When the object is destroyed, its memory is released and can be reused for other variables. This process is called **deallocation**.

#### Local scope (block scope):
An identifier's **scope** is the region of the program where it can be accessed. Local variables have **local scope** (or **block scope**), meaning they can only be accessed within the block of code where they are defined (e.g., within a function or a loop). When they are accessible are called they are **in scope**; when they are not accessible, they are **out of scope**.
```cpp
#include <iostream>
void myFunction()
{
    int localVar{ 42 }; // localVar is only accessible within myFunction
    std::cout << "Local variable: " << localVar << '\n'; // okay: localVar is in scope here
}
int main()
{
    myFunction();
    // std::cout << localVar; // Error: localVar is out of scope here
    return 0;
}
```

#### Functional separation:
Using functions helps to separate different parts of your code, making it easier to read and maintain.
Each function can have its own set of local variables, which helps to avoid naming conflicts and keeps related code together.
```cpp
#include <iostream>
void functionA()
{
    int value{ 10 }; // local variable for functionA
    std::cout << "Function A value: " << value << '\n';
}
void functionB()
{
    int value{ 20 }; // local variable for functionB (different from functionA's value even if it has the same name)
    std::cout << "Function B value: " << value << '\n';
}
int main()
{
    functionA();
    functionB();
    return 0;
}
```

#### Temporary objects:
Temporary objects are created during the evaluation of expressions and exist only for the duration of that expression. For example, in the expression `std::cout << (a + b);`, the result of `a + b` is a temporary object that exists only until the end of the full expression (the semicolon).
```cpp
#include <iostream>
int add(int x, int y)
{
    return x + y; // the result of x + y is a temporary object
}
int main()
{
    int a{ 5 };
    int b{ 10 };
    std::cout << "The sum is: " << add(a, b) << '\n'; // the temporary object returned by add() exists until the end of this statement
    return 0;
}
```

#### Summary:
- Local scope refers to the visibility and lifetime of variables defined within a specific block of code, such as a function.
- Local variables are only accessible within the function where they are defined.
- Local variables are created when the function is called and destroyed when the function exits.
- Using functions helps to separate different parts of your code, making it easier to read and maintain.


---

### S06 — 2.6 Why functions are useful, and how to use them effectively
Functions are useful for several reasons:
- **Organization**: Functions help to organize code into smaller, manageable pieces, making it easier to read and maintain.
- **Reusability**: Functions can be reused in different parts of the program or in other programs, reducing code duplication.
- **Testing**: Functions can be tested independently, making it easier to identify and fix bugs.
- **Extensibility**: Functions can be modified or extended without affecting the rest of the program.
- **Abstraction**: Functions allow you to hide complex implementation details behind a simple interface.
- **Collaboration**: Functions enable multiple developers to work on different parts of a program simultaneously.

#### Best practices for using functions effectively:
- Group of statements that appear together in multiple places should be made into a function.
- Code that has a well defined task and input/output should be made into a function.
- Functions should do one thing and do it well.
- When a function become too long or complex, consider breaking it into smaller functions.
- Use meaningful names for functions that describe their purpose.


---

### S07 — 2.7 Forward declarations and definitions
In C++, functions must be declared before they are used, because the compiler compiles the code in a sequential manner from top to bottom. If a function is called before it is declared, the compiler will not know about its existence and will produce an error.

#### Error example:
```cpp
#include <iostream>

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}

int add(int x, int y) // Error: 'add' was not declared in this scope
{
    return x + y;
}
```

#### How to fix this:
To fix this, you can either:
1. **Reorder the function definitions** so that they appear before any calls to them.
    ```cpp
    #include <iostream>

    int add(int x, int y) // Function definition appears before its use
    {
        return x + y;
    }

    int main()
    {
        std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
        return 0;
    }
    ```
2. **Use forward declarations** (also called **function prototypes**) to declare the function before it is used. A forward declaration provides the compiler with the function's name, return type, and parameters, allowing it to recognize the function when it is called later in the code.
    ```cpp
    #include <iostream>

    int add(int x, int y); // Forward declaration (function prototype)

    int main()
    {
        std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
        return 0;
    }

    int add(int x, int y) // Function definition
    {
        return x + y;
    }
    ```

#### Why a forward declaration?
Forward declarations are especially useful in complex programs with multiple functions that call each other, or when functions are defined in separate files. They allow you to organize your code more flexibly without worrying about the order of function definitions.

#### Declaration vs Definition:
- A **function declaration** tell the compiler about the existence of an identifier and its associated type information.
- A **function definition** is a declaration that actually implements the function, providing the body of the function.

#### One definition rule (ODR):
In C++, the **One Definition Rule (ODR)** states the following:
- Within a file, each function, variable, type, or template can have only one definition. Definitions in different scopes (e.g., different functions or blocks) are considered separate entities. *This will cause a compilation error.*
    ```cpp
    int add(int x, int y)
    {
        return x + y;
    }

    int add(int x, int y) // violation of ODR 1, we've already defined function add(int, int)
    {
        return x + y;
    }

    int main()
    {
        int x{};
        int x{ 5 }; // violation of ODR, we've already defined x
    }
    ```
- Within a program, each function or variable in a given scope can only have one definition. However, it can be declared multiple times (e.g., in different files) as long as all declarations are consistent with the single definition. *This will cause a linker error.*
- Types, templates, inline functions, and inline variables are allowed to have duplicates in different files as long as the definitions are identical. *This will cause an undefined behavior if they are not identical.*

#### Summary:
- Functions must be declared before they are used.
- You can use forward declarations (function prototypes) to declare functions before they are used.
- A function declaration tells the compiler about the existence of a function, while a function definition provides the body of the function.
- The One Definition Rule (ODR) states that each function or variable can have only one definition within a file and a program, but can be declared multiple times as long as all declarations are consistent with the single definition.


---

### S08 — 2.8 Programs with multiple files
In C++, you can organize your code into multiple files to improve readability, maintainability, and reusability. This is especially useful for larger programs where separating code into different files can help manage complexity.

#### How to compile multiple files:
When you have multiple source files (e.g., `main.cpp`, `file2.cpp`), you need to compile each file separately and then link the resulting object files together to create the final executable. This is typically done in two steps:
1. **Compilation**: Compile each source file into an object file.
    ```bash
    clang++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O2 -fcolor-diagnostics -fansi-escape-codes -g main.cpp file1.cpp -o main
    ```
    You could also use this command to compile and link all the `.cpp` files in the current directory:
    ```bash
    clang++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O2 -fcolor-diagnostics -fansi-escape-codes *.cpp -o main
    ```
2. **Running**: Run the resulting executable.
    ```bash
    ./main
    ```

#### Error example:
File `add.cpp`:
```cpp
int add(int x, int y) // Function definition
{
    return x + y;
}
``` 
File `main.cpp`:
```cpp
#include <iostream>

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n'; // Error: 'add' was not declared in this scope
    return 0;
}
```
When you try to compile `main.cpp`, you will get an error because the compiler does not know about the `add` function defined in `add.cpp`. When the compiler compiles each file individually, it does not have access to the definitions in other files, for the following reasons:
- It allows the compilation in any order.
- When we change a source file, we only need to recompile that file, not all the files that depend on it.
- It reduces the possibility of naming conflicts.

#### How to fix this:
To fix this, as a first option, you can use **forward declarations** (function prototypes) in `main.cpp` to declare the `add` function before it is used:
File `main.cpp`:
```cpp
#include <iostream>

int add(int x, int y); // Forward declaration (function prototype)

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n'; // Now the compiler knows about add()
    return 0;
}
```
In this way, the linker will be able to find the definition of `add` in `add.cpp` when linking the object files together.

#### Summary:
- You can organize your code into multiple files to improve readability, maintainability, and reusability.
- When compiling multiple files, the compiler does not have access to the definitions in other files.
- You can use forward declarations (function prototypes) to declare functions before they are used in other files.
- The linker will resolve the references to functions and variables across different files during the linking stage.


---

### S09 — 2.9 Naming collisions and an introduction to namespaces
In C++, a **naming collision** occurs when two or more identifiers (such as variable names, function names, or class names) in the same scope have the same name. This can lead to ambiguity and errors during linking, as the compiler cannot determine which identifier to use.

#### Example of naming collision:
File `file1.cpp`:
```cpp
#include <iostream>

void printMessage()
{
    std::cout << "Hello from file1.cpp\n";
}
```
File `file2.cpp`:
```cpp
#include <iostream>

void printMessage()
{
    std::cout << "Hello from file2.cpp\n";
}
```
When the compiler compiles, it will compile both files without errors (they are compiled separately). However, when the linker tries to link the object files together, it will produce an error because it finds two definitions of `printMessage`, leading to a naming collision.

#### Scope regions:
As explained in the previous section, an identifier's **scope region** is the region of the program where it can be accessed. Identifiers defined in different scope regions can have the same name without causing a naming collision. 

#### Namespaces:
A **namespace** is a declarative region that provides a scope (namespace scope) to the identifiers (names of types, functions, variables, etc) inside it. Namespaces are used to organize code and prevent naming collisions by grouping related identifiers together. 
For example, you can put all your math functions in a `math` namespace, and all your math function (unique within that namespace) will not collide with functions in other namespaces or the global namespace.

#### Global namespaces:
In C++, any identifier that is not defined inside a class, function, or a namespace is considered to be part of an implicitly-defined namespace called the **global namespace**. Identifiers in the global namespace can be accessed from anywhere in the program, but they can also lead to naming collisions if multiple files define identifiers with the same name, as shown in the previous example.

For example:
```cpp
#include <iostream> // imports the declaration of std::cout into the global scope

// All of the following statements are part of the global namespace

void foo();    // okay: function forward declaration
int x;         // compiles but strongly discouraged: non-const global variable definition (without initializer)
int y { 5 };   // compiles but strongly discouraged: non-const global variable definition (with initializer)
x = 5;         // compile error: executable statements are not allowed in namespaces

int main()     // okay: function definition
{
    return 0;
}

void goo();    // okay: A function forward declaration
```

#### The `std` namespace:
The C++ Standard Library defines its identifiers (functions, types, variables, etc.) inside a namespace called `std`. This helps to avoid naming collisions with user-defined identifiers. For example, the `std::cout` object is defined in the `std` namespace, so you need to use the `std::` prefix to access it.

Originally, all these standard function were defined in the global namespace, which led to many naming collisions. To solve this problem, the C++ Standard Library was organized into the `std` namespace.

There are two ways to access identifiers in the `std` namespace:
1. Use the **scope resolution operator** `::` to access identifiers in the `std` namespace. For example, to access `cout` in the `std` namespace, you would write `std::cout`, that is read as "`cout` that is declared in the `std` namespace".
    ```cpp
    #include <iostream>
    int main()
    {
        std::cout << "Hello, World!" << '\n'; // using std::cout
        return 0;
    }
    ```
2. Use the `using` directive to bring all identifiers from the `std` namespace into the current scope. For example, you can write `using namespace std;` at the beginning of your code, and then you can use `cout` without the `std::` prefix. However, this is generally **DISCOURAGED** in header files and large projects because it can lead to naming collisions.
    ```cpp
    #include <iostream>
    using namespace std; // brings all identifiers from std namespace into the current scope
    int main()
    {
        cout << "Hello, World!" << '\n'; // using cout without std:: prefix
        return 0;
    }
    ```

#### Summary:
- A naming collision occurs when two or more identifiers in the same scope have the same name.
- Identifiers defined in different scope regions can have the same name without causing a naming collision.
- A namespace is a declarative region that provides a scope to the identifiers inside it, helping to prevent naming collisions.
- The global namespace is the default namespace for identifiers not defined inside a class, function, or a namespace.
- The C++ Standard Library defines its identifiers inside the `std` namespace to avoid naming collisions.
- You can access identifiers in the `std` namespace using the scope resolution operator `::` or the `using` directive (the latter is generally discouraged in header files and large projects).


---

### S10 - 2.10 Introduction to the preprocessor
In C++, prior to compilation, each code (`.cpp` or `.h`) file is processed by a tool called the **preprocessor**. The preprocessor performs several tasks that happen either temporally in-memory or using temporary files.
1. **File Inclusion**: The preprocessor handles `#include` directives by including the contents of header files into the source file. This allows for code reuse and modularity.
2. **Macro Expansion**: The preprocessor replaces macros defined with `#define` with their corresponding values or code snippets. This enables code generation and simplification.
3. **Conditional Compilation**: The preprocessor can include or exclude parts of the code based on certain conditions using directives like `#ifdef`, `#ifndef`, `#if`, `#else`, and `#endif`. This is useful for platform-specific code or debugging.

#### Preprocessor directives:
Preprocessor directives are special instructions that begin with the `#` symbol and are processed by the preprocessor before the actual compilation of the code. Some common preprocessor directives include:
- `#include`: Used to include the contents of a file. When the preprocessor encounters an `#include` directive, it replaces it with the entire contents of the specified file.
    ```cpp
    #include <iostream> // includes the standard iostream header file
    #include "myheader.h" // includes a user-defined header file
    ```
- `#define`: Used to define macros (a **macro** is a fragment of code which has been given a name). Macros can be used to define constants or to create macro functions.
    ```cpp
    #include <iostream>
    #define PI 3.14159 // defines a macro named PI with the value 3.14159
    #define SQUARE(x) ((x) * (x)) // defines a macro function to calculate the square of a number
    #define MY_NAME "Alex"

    int main()
    {
        std::cout << "My name is: " << MY_NAME << '\n';
         
        return 0;
    }
    ```
- `#ifdef`, `#ifndef`, `#if`, `#else`, `#endif`: Used for **conditional compilation**. These directives allow you to include or exclude parts of the code based on whether certain macros are defined or based on specific conditions.
    ```cpp
    #include <iostream>

    #define PRINT_JOE

    int main()
    {
    #ifdef PRINT_JOE
        std::cout << "Joe\n"; // will be compiled since PRINT_JOE is defined
    #endif

    #ifdef PRINT_BOB
        std::cout << "Bob\n"; // will be excluded since PRINT_BOB is not defined
    #endif

        return 0;
    }
    ```
- `#if 0` and `#if 1`: Used to include or exclude code blocks. `#if 0` will exclude the code block, while `#if 1` will include it.
    ```cpp
    #include <iostream>

    int main()
    {
    #if 0
        std::cout << "This code is excluded and will not be compiled.\n";
    #endif

    #if 1
        std::cout << "This code is included and will be compiled.\n";
    #endif

        return 0;
    }
    ```
- `#undef`: Used to undefine a macro.
    ```cpp
    #undef PI // undefines the macro named PI
    ``` 
- `#pragma`: Used to provide special instructions to the compiler (compiler-specific).
    ```cpp
    #pragma once // ensures the header file is included only once during compilation
    ```

#### The scope of `#define`s:
Directives are resolved before compilation, from top to bottom on a file-by-file basis. Consider the following example:
```cpp
#include <iostream>

void foo()
{
#define MY_NAME "Alex"
}

int main()
{
	std::cout << "My name is: " << MY_NAME << '\n';

	return 0;
}
```
The preprocessor will does not understand C++ code and scopes, so it will define `MY_NAME` when it encounters the `#define` directive, regardless of the fact that it is inside the function `foo()`. Therefore, when `main()` tries to use `MY_NAME`, it will work correctly and print "My name is: Alex".

Defines are scoped to the file they are defined in. If you want to use a macro in multiple files, you should define it in a header file and include that header file in each source file that needs it. For example:
File `function.cpp`:
```cpp
#include <iostream>

void doSomething()
{
#ifdef PRINT
    std::cout << "Printing!\n";
#endif
#ifndef PRINT
    std::cout << "Not printing!\n";
#endif
}
```
File `main.cpp`:
```cpp
void doSomething(); // forward declaration for function doSomething()

#define PRINT

int main()
{
    doSomething();

    return 0;
}
```
When you compile and run `main.cpp`, it will print "Not printing!" because the `PRINT` macro is not defined in `function.cpp`. To fix this, you would need an **header file** to define the macro and include it in both source files.

#### Summary:
- The preprocessor processes code files before compilation, handling tasks like file inclusion, macro expansion, and conditional compilation.
- Preprocessor directives begin with the `#` symbol and include `#include`, `#define`, `#ifdef`, `#ifndef`, `#if`, `#else`, `#endif`, `#undef`, and `#pragma`.
- Macros defined with `#define` are scoped to the file they are defined in and can be used throughout that file.
- Preprocessor does not understand C++ syntax or scopes, so macros defined inside functions are still accessible outside those functions.


---

### S11 - 2.11 Header files
As we have seen in Chapter 8 (Programs with multiple files), we can use *forward declarations* (function prototypes) to declare functions before they are used in other files. However, when the program grows larger, managing these declarations can become cumbersome and error-prone. To address this, C++ provides a mechanism called **header files**.

#### Header files:
A **header file** is a file with a `.h` or `.hpp` extension that contains declarations of functions, classes, variables, and other identifiers. Header files are used to share declarations between multiple source files. By including a header file in a source file using the `#include` directive, you can make the declarations in the header file available to that source file. 
For example, you can create a header file named `math_utils.h` that contains the declaration of a function `add`.

#### Using standard library header files:
The C++ Standard Library provides a set of standard header files that contain declarations for commonly used functions and types. For example, the `<iostream>` header file contains declarations for input/output stream objects like `std::cin` and `std::cout`. To use these standard library functions and types, you need to include the appropriate header files at the beginning of your source file.
```cpp
#include <iostream>

int main()
{
    std::cout << "Hello, world!";
    return 0;
}
```
In this example, `std::cout` has been forward declarated in the `<iostream>` header file, so we can use it in our program. When the preprocessor encounters the `#include <iostream>` directive, it replaces it with the entire contents of the `<iostream>` header file, making the declarations available to the source file.

#### Using header files to propoagate forward declarations:
You can create your own header files to propagate forward declarations across multiple source files, instead of repeating the same forward declarations in each source file.
To write a header file, you would need the two following steps:
- A **header guard** to prevent multiple inclusions of the same header file. This is typically done using `#ifndef`, `#define`, and `#endif` directives.
- The actual **declarations** of functions, classes, variables, etc.
For example, for the `add` example, you will have:
File `add.h`:
```cpp
// We really should have a header guard here, but will omit it for simplicity (we'll cover header guards in the next lesson)

// This is the content of the .h file, which is where the declarations go
int add(int x, int y); // function prototype for add.h -- don't forget the semicolon!
```
File `add.cpp`:
```cpp
#include "add.h" // Insert contents of add.h at this point.  Note use of double quotes here.

int add(int x, int y)
{
    return x + y;
}
```
File `main.cpp`:
```cpp
#include <iostream>
#include "add.h" // Insert contents of add.h at this point.  Note use of double quotes here.

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n'; // Now the compiler knows about add()
    return 0;
}
```
When the preprocessor processes `main.cpp`, it will replace the `#include "add.h"` directive with the contents of `add.h`, making the declaration of `add` available to `main.cpp`. Similarly, when processing `add.cpp`, it will also include the declaration of `add` from `add.h`.

#### Notes:
- **Avoid defining functions or variables in header files (for now)**: For now, you should avoid defining function or variable definitions in header files, as this can lead to violations of the One Definition Rule (ODR) when the header file is included in multiple source files.
- **Source files should include necessary headers**: As a best practice, each source file should include its paired header file (if it has one) as the first `#include` directive. This helps to catch errors at compilation time instead of at link time.
- **Do not include `.cpp` files**: You should never include `.cpp` files in other files. Always include header files (`.h` or `.hpp`).
- **Angle brackets vs double quotes**: Use angle brackets (`<>`) for standard library headers and double quotes (`""`) for user-defined headers. This helps the compiler to locate the files correctly.
- **Include header files from other directories**: If your header files are located in different directories, you can specify the path in the `#include` directive. For example:
    ```cpp
    #include "headers/myHeader.h"
    #include "../moreHeaders/myOtherHeader.h"
    ```
- **Headers can include other headers**: Header files can include other header files. This allows you to create a hierarchy of headers and manage dependencies between them. For example:
    ```cpp
    #include <string_view> // required to use std::string_view
    std::string_view getApplicationName(); // std::string_view used here
    ```
- **Transitive inclusion**: If `fileA.h` includes `fileB.h`, and `fileB.h` includes `fileC.h`, then including `fileA.h` in a source file will also include the contents of `fileB.h` and `fileC.h`. This is called **transitive inclusion**. Be cautious with transitive inclusion, as it can lead to longer compilation times and potential naming conflicts, sicne header files are not updated that often.

#### Best practices:
- Always include header guards in your header files to prevent multiple inclusions.
- Do not define variables or functions in header files (for now).
- Give the same name to the header file as the source file it is paired with (e.g., `add.cpp` and `add.h`).
- Each header file should have specific job and independent of other headers as much as possible.
- Think about which headers a source file needs and include only those headers.
- Only include what you need.
- Do not include `.cpp` files.
- Write documentation comments for your functions in the header file.

#### Summary:
- A header file is a file with a `.h` or `.hpp` extension that contains declarations of functions, classes, variables, and other identifiers.
- Header files are used to share declarations between multiple source files.
- You can create your own header files to propagate forward declarations across multiple source files.
- Header files should include a header guard to prevent multiple inclusions.


---

### S12 - 2.12 Header guards
When a header file is included multiple times in a program, it can lead to multiple definition errors during the linking stage. This happens because the contents of the header file are copied into each source file that includes it, resulting in multiple definitions of the same functions or variables.

To prevent this issue, you can use **header guards**. A header guard is a set of preprocessor directives that ensure the contents of a header file are included only once during the compilation process.

Here an example that will cause compilation errors due to multiple definitions (we are defining functions inside the header file for simplicity, but this is generally **discouraged**):
File `square.h`:
```cpp
int getSquareSides()
{
    return 4;
}
```
File `wave.h`:
```cpp
#include "square.h" // includes square.h
```
File `main.cpp`:
```cpp
#include "square.h" // includes square.h
#include "wave.h"   // includes square.h again through wave.h

int main()
{
    return 0;
}
```
When you compile `main.cpp`, the preprocessor will include the contents of `square.h` twice (once directly and once through `wave.h`), leading to multiple definitions of the `getSquareSides` function, which violates the One Definition Rule (ODR). Basically, after the preprocessing step, `main.cpp` will look like this:
```cpp
int getSquareSides()  // from square.h
{
    return 4;
}

int getSquareSides() // from wave.h (via square.h)
{
    return 4;
}

int main()
{
    return 0;
}
```

#### Header guards:
To prevent multiple inclusions of a header file, you can use **header guards** (or also called **include guards**), that are conditionaal compilation directives that have the following form:
```cpp
#ifndef SOME_UNIQUE_NAME_HERE
#define SOME_UNIQUE_NAME_HERE

// your declarations (and certain types of definitions) here

#endif
```
When this header is `#include`d, the preprocessor checks if `SOME_UNIQUE_NAME_HERE` is already defined. If it is not defined, it defines it and includes the contents of the header file. If it is already defined, the preprocessor skips the contents of the header file, preventing multiple inclusions.

Header guards can have any name, but it is common practice to use the name of the header file in uppercase letters, replacing dots and slashes with underscores. For example, for a header file named `math_utils.h`, you could use `MATH_UTILS_H` as the unique name.

#### Previous example with header guards:
Here is the corrected version of the previous example using header guards:
File `square.h`:
```cpp
#ifndef SQUARE_H // start of header guard
#define SQUARE_H

int getSquareSides()
{
    return 4;
}
#endif // end of header guard
```
File `wave.h`:
```cpp
#ifndef WAVE_H // start of header guard
#define WAVE_H
#include "square.h" // includes square.h
#endif // end of header guard
```
File `main.cpp`:
```cpp
#include "square.h" // includes square.h
#include "wave.h"   // includes square.h again through wave.h, but header guard prevents multiple inclusion

int main()
{
    return 0;
}
```
When you compile `main.cpp`, the preprocessor will include the contents of `square.h` only once, preventing multiple definitions and avoiding compilation errors. The `main.cpp` file will look like this after preprocessing:
```cpp
// Square.h included from main.cpp
#ifndef SQUARE_H // square.h included from main.cpp
#define SQUARE_H // SQUARE_H gets defined here

// and all this content gets included
int getSquareSides()
{
    return 4;
}

#endif // SQUARE_H

#ifndef WAVE_H // wave.h included from main.cpp
#define WAVE_H
#ifndef SQUARE_H // square.h included from wave.h, SQUARE_H is already defined from above
#define SQUARE_H // so none of this content gets included

int getSquareSides()
{
    return 4;
}

#endif // SQUARE_H
#endif // WAVE_H

int main()
{
    return 0;
}
```
In this way, the first time `square.h` is included, `SQUARE_H` is not defined, so the contents of the header file are included for compilation and `SQUARE_H` gets defined. The second time `square.h` is included (through `wave.h`), `SQUARE_H` is already defined, so the preprocessor skips the contents of the header file, preventing multiple definitions.

#### Multiple inclusion of header files in different source files:
Note that the goal of header guards is to prevent a code file from receiving more than one copy of a guarded header. By design, header guards **do not prevent** multiple source files from including the same header file. The definition of the macro used in the header guard is local to each source file being compiled, so at the end of the compilation, each macro is lost and not visible from other source files.

For example, consider the following files:
File `square.h`:
```cpp
#ifndef SQUARE_H
#define SQUARE_H

int getSquareSides()
{
    return 4;
}

int getSquarePerimeter(int sideLength); // forward declaration for getSquarePerimeter

#endif
```
File `square.cpp`:
```cpp
#include "square.h"  // square.h is included once here

int getSquarePerimeter(int sideLength)
{
    return sideLength * getSquareSides();
}
```
File `main.cpp`:
```cpp
#include "square.h" // square.h is also included once here
#include <iostream>

int main()
{
    std::cout << "a square has " << getSquareSides() << " sides\n";
    std::cout << "a square of length 5 has perimeter length " << getSquarePerimeter(5) << '\n';

    return 0;
}
```
When you compile `square.cpp` and `main.cpp`, the preprocessor will include the contents of `square.h` once in each source file (fine for compilation!). During **linking stage** instead, both `square.cpp` and `main.cpp` will have their own copy of the `getSquareSides` function, and it will complain because of multiple definitions of the same function. 

To prevent this, you should put all the function definitions in the `.cpp` file, and only keep the forward declarations in the header file. Here is the corrected version:
File `square.h`:
```cpp
#ifndef SQUARE_H
#define SQUARE_H

int getSquareSides(); // forward declaration for getSquareSides
int getSquarePerimeter(int sideLength); // forward declaration for getSquarePerimeter

#endif // SQUARE_H
```
File `square.cpp`:
```cpp
#include "square.h"  // square.h is included once here
int getSquareSides()
{
    return 4;
}

int getSquarePerimeter(int sideLength)
{
    return sideLength * getSquareSides();
}  
```
In this way, when you compile `square.cpp` and `main.cpp`, the preprocessor will include the contents of `square.h` once in each source file, and during linking stage, there will be no multiple definitions of the same function, since the functions are defined only in `square.cpp`.

#### `#pragma once`:
An alternative to header guards is the `#pragma once` directive. When you include a header file that contains `#pragma once`, the preprocessor ensures that the file is included only once during the compilation process, regardless of how many times it is included in the source files. This directive is not part of the C++ standard, but it is widely supported by most modern compilers (including GCC, Clang, and MSVC).
Here is an example of using `#pragma once` in a header file:
File `square.h`:
```cpp
#pragma once // ensures the header file is included only once during compilation
int getSquareSides(); // forward declaration for getSquareSides
int getSquarePerimeter(int sideLength); // forward declaration for getSquarePerimeter
```

#### Summary:
- When a header file is included multiple times in a program, it can lead to multiple definition errors during the linking stage.
- Header guards are preprocessor directives that ensure the contents of a header file are included only once during the compilation process.
- Header guards typically use `#ifndef`, `#define`, and `#endif` directives.
- Header guards do not prevent multiple source files from including the same header file; they only prevent multiple inclusions within a single source file.
- To avoid multiple definitions, function and variable definitions should be placed in source files (`.cpp`), while only forward declarations should be placed in header files (`.h` or `.hpp`).
- An alternative to header guards is the `#pragma once` directive, which is widely supported by modern compilers.


---

### S13 - 2.13 How to design your first programs
When designing your first C++ programs, it's important to follow a structured approach to ensure that your code is organized, maintainable, and efficient. Here are some steps and best practices to help you design your programs effectively:

#### Design step 1 - define your goal:
Start by clearly defining the goal of your program. What problem are you trying to solve? What functionality do you want to implement? Having a clear understanding of your program's purpose will guide your design decisions. It is often a useful idea to express this as a user-facing outcome.

#### Design step 2 - define requirements:
Once you have a clear goal, define the requirements for your program. What inputs will it take? What outputs should it produce? What constraints or limitations should you consider? This step will help you identify the key features and functionalities your program needs to have.

#### Design step 3 - define your tools, targets, and backup plan:
Decide on the tools and technologies you will use to develop your program. This includes choosing a programming language (C++ in this case), an integrated development environment (IDE) or text editor, and any libraries or frameworks you may need. Additionally, consider your target platform (e.g., Windows, Linux, macOS) and ensure that your tools are compatible with it. Finally, have a backup plan in case you encounter issues with your chosen tools or technologies.

#### Design step 4 - break down hard problems down into easier/smaller problems:
If your program involves complex functionality, break it down into smaller, manageable problems. We usually make use of a **top-down approach**, where we start with a high-level overview of the program and then break it down into smaller components or modules. This approach helps to simplify the design process and makes it easier to implement and test each component individually.

The other approach is the **bottom-up approach**, where we start with the individual components or modules and then combine them to create the overall program and hierarchy by grouping related components together. This approach is useful when you have a clear understanding of the individual components and how they fit together.

Overall:
- Use a top-down approach for complex problems that need to be broken down into smaller components.
- Use a bottom-up approach when you have a clear understanding of the individual components and how they fit together.

#### Design step 5 - figure out the sequence of events:
Once you have broken down your program into smaller components, figure out the sequence of events or the flow of control in your program. This involves determining how the different components will interact with each other and the order in which they will be executed. You can use flowcharts, pseudocode, or diagrams to visualize the sequence of events and the relationships between different components.

#### Implementation step 1 - outlining your main function:
Now we’re ready to start implementation. The above sequences can be used to outline your main program. Don’t worry about inputs and outputs for the time being. For example:
```cpp
int main()
{
//    doBedroomThings();
//    doBathroomThings();
//    doBreakfastThings();
//    doTransportationThings();

    return 0;
}
```
or another example:
```cpp
int main()
{
    // Get first number from user
//    getUserInput();

    // Get mathematical operation from user
//    getMathematicalOperation();

    // Get second number from user
//    getUserInput();

    // Calculate result
//    calculateResult();

    // Print result
//    printResult();

    return 0;
}
```

#### Implementation step 2 - implement each function:
In this step, for each function you will:
1) Define the function prototype (input/output types).
2) Implement the function body.
3) Test the function to ensure it works correctly.

For example for the calculator example, we can focus on the first function `getUserInput()`:
```cpp
#include <iostream>

// Full implementation of the getUserInput function
int getUserInput()
{
    std::cout << "Enter an integer: ";
    int input{};
    std::cin >> input;

    return input;
}

int main()
{
    // Get first number from user
    int value{ getUserInput() }; // Note we've included code here to test the return value!
    std::cout << value << '\n'; // debug code to ensure getUserInput() is working, we'll remove this later

    // Get mathematical operation from user
//    getMathematicalOperation();

    // Get second number from user
//    getUserInput();

    // Calculate result
//    calculateResult();

    // Print result
//    printResult();

    return 0;
}
```

#### Implementation step 3 - final testing and debugging:
Once you have implemented all the functions and integrated them into your main program, it's important to perform final testing and debugging. Test your program with different inputs and scenarios to ensure that it behaves as expected. Debug any issues or errors that arise during testing, and make necessary adjustments to your code.

#### Best preactices:
- **Keep your prgram simple to start with**: Start with a simple version of your program and gradually add more features and complexity as needed. This will help you to focus on the core functionality and avoid getting overwhelmed by unnecessary details.
- **Add features over time**: Don't try to implement all the features of your program at once. Instead, add features incrementally, testing and debugging each feature as you go. This will help you to identify and fix issues early in the development process.
- **Focus on one area at the time**: When working on your program, focus on one area or component at a time. This will help you to stay organized and avoid getting distracted by other parts of the program.
- **Test each piece of code as you go**: Test each function or component of your program as you implement it. This will help you to identify and fix issues early in the development process, and ensure that each piece of code works correctly before integrating it into the larger program.
- **Do not invest in perfecting early code**: Don't spend too much time trying to perfect your code in the early stages of development. Instead, focus on getting a working version of your program first, and then refine and optimize it later as needed.
- **Optimize for maintainability, not performance**: When designing and implementing your program, prioritize maintainability over performance. Write clean, well-organized code that is easy to read and understand, even if it is not the most efficient solution. This will make it easier to maintain and update your program in the future.

#### Summary:
- Follow a structured approach when designing your C++ programs, including defining your goal, requirements, tools, and breaking down complex problems.
- Use a top-down or bottom-up approach to break down complex problems into smaller components.
- Figure out the sequence of events and flow of control in your program.
- Outline your main function and implement each function step by step, testing as you go.
- Perform final testing and debugging to ensure your program works as expected.


---

### SX - 2.x Chapter 2 summary and quiz
Have a look at the solutions inside the `sx-questions` folder, and have fun!


---

## 🧭 Summary
Functions are the building blocks for clean C++ programs. You learned how to **declare**, **define**, and **call** them; how to **return values** (or use `void`); and how to pass information through **parameters/arguments**. You explored **local scope** and **lifetime** (including temporaries), and saw how functions enable modular, testable code.

On the project side, you learned to **split code into multiple files**, compile separate **translation units**, and connect them during **linking**. You now know how to create **header files** to propagate declarations, protect them with **include guards** (or `#pragma once`), and avoid **ODR** pitfalls by keeping definitions in `.cpp` files. Finally, you touched the **preprocessor** and **namespaces** to manage includes and prevent name clashes.

**Key takeaways:** keep functions small and focused, expose clear interfaces via headers, include only what you need, and let namespaces and guards keep your codebase tidy and scalable.

### 🧱 Core Concepts You Mastered
- ⚙️ **Functions 101** — Difference between declaration, definition, and call; when to use `void` vs value-returning functions.  
- 🔁 **Return & Flow** — Using `return` correctly; understanding what happens when it’s missing.  
- 🎯 **Parameters & Arguments** — Passing and using values effectively in functions; nested and chained calls.  
- 📦 **Scope & Lifetime** — Local variables exist only inside their function; temporaries vanish after use.  
- 🧩 **Multi-File Projects** — Splitting code into multiple `.cpp` files and linking them together.  
- 📄 **Headers & Guards** — Sharing declarations via `.h` files, protecting them with include guards or `#pragma once`.  
- 🚫 **ODR & Duplicates** — Avoid multiple definitions across files; keep one definition, many declarations.  
- ⚡ **Preprocessor Basics** — How `#include`, `#define`, and conditional compilation work before actual compilation.  
- 🧭 **Namespaces** — Organizing code and avoiding naming collisions (e.g., `std::cout`).  
- 🧠 **Good Design Habits** — Write small, focused, reusable functions and include only what you need.
