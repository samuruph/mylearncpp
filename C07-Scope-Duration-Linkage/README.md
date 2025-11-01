# Chapter 07 - Scope, Duration, and Linkage

## 🧭 Overview
This chapter explores how **scope**, **duration**, and **linkage** determine where identifiers (variables, functions, etc.) can be accessed, how long they exist in memory, and whether they can be shared across different source files.  
These three concepts form the foundation for understanding how data and identifiers behave across the lifetime of a C++ program.

You’ll learn how local and global variables differ, how to use namespaces to avoid naming collisions, and how to control identifier visibility using linkage rules.  
The chapter also covers modern tools such as **inline variables**, **static local variables**, and **unnamed or inline namespaces**, which enhance modularity and safety in modern C++.

> **Key idea:** Scope defines *where* an identifier is visible, duration defines *how long* it exists, and linkage defines *whether* it refers to the same entity across translation units.

---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch07_first
./build/ch07_first
```

---

## 🎯 Learning Outcomes

By the end of this chapter, you’ll be able to:

- Understand and differentiate between **scope**, **duration**, and **linkage** in C++.
- Identify the **lifetime and accessibility** of local and global variables.
- Use **user-defined namespaces** and the **scope resolution operator** to avoid naming collisions.
- Distinguish between **internal** and **external** linkage, and control visibility with `static`, `extern`, and `inline`.
- Recognize and avoid **variable shadowing** (name hiding) in nested scopes.
- Share global constants safely across translation units using **inline constexpr variables**.
- Utilize **static local variables** for persistent state without global scope.
- Explain why **non-const global variables** are dangerous and when they can be justified.
- Apply **using-declarations** and **using-directives** correctly to improve readability without compromising safety.
- Understand **unnamed** and **inline namespaces** for encapsulation and versioning in libraries.


---

## Sections

### S01 — 7.1 Compound statements (blocks)
A **compound statement** (or **block**) is a group of zero or more statements that is treated as a single statement by the compiler.  
A block is delimited by a pair of curly braces `{}`, and no semicolon is needed after the closing brace.

#### Blocks inside other blocks:
Although functions cannot be nested inside other functions, blocks can be nested inside other blocks.
For example:
```cpp
int add(int x, int y)
{ // block
    return x + y;
} // end block

int main()
{ // outer block

    // multiple statements
    int value {};

    { // inner/nested block
        add(3, 4);
    } // end inner/nested block

    return 0;

} // end outer block
```

When blocks are nested, the enclosing block is called the **outer block**, and the block inside it is called the **inner block**.

#### Using blocks to execute multiple statements conditionally:
Blocks are often used to group multiple statements that should be executed conditionally, coupling them with control flow statements like `if`, `while`, and `for`. By default, these control flow statements only apply to the single statement that immediately follows them. For example:
```cpp
if (condition)
    statement1;
    statement2; // This statement always executes, regardless of the condition.
```
To ensure that both `statement1` and `statement2` are executed only when the condition is true, you can use a block:
```cpp
if (condition)
{
    statement1;
    statement2; // This statement now only executes if the condition is true.
}
```

In a more complex example:
```cpp
#include <iostream>

int main()
{ // start of outer block
    std::cout << "Enter an integer: ";
    int value {};
    std::cin >> value;

    if (value >= 0)
    { // start of nested block
        std::cout << value << " is a positive integer (or zero)\n";
        std::cout << "Double this number is " << value * 2 << '\n';
    } // end of nested block
    else
    { // start of another nested block
        std::cout << value << " is a negative integer\n";
        std::cout << "The positive of this number is " << -value << '\n';
    } // end of another nested block

    return 0;
} // end of outer block
```
it will output:
```
Enter an integer: 3
3 is a positive integer (or zero)
Double this number is 6
```
or
```
Enter an integer: -4
-4 is a negative integer
The positive of this number is 4
```

#### Block nesting levels:
Blocks can be nested to multiple levels. Each time a new block is opened with a `{`, a new level of nesting is created. The innermost block is the most deeply nested (has higher **nesting depth**), and each block can contain its own statements and further nested blocks.
For example:
```cpp
#include <iostream>

int main()
{ // block 1, nesting level 1
    std::cout << "Enter an integer: ";
    int value {};
    std::cin >> value;

    if (value >  0)
    { // block 2, nesting level 2
        if ((value % 2) == 0)
        { // block 3, nesting level 3
            std::cout << value << " is positive and even\n";
        }
        else
        { // block 4, also nesting level 3
            std::cout << value << " is positive and odd\n";
        }
    }

    return 0;
}
```
has a maximum nesting depth of 3.

> **Best practice:** While C++ allows deep nesting of blocks, it’s generally advisable to keep nesting levels shallow (typically no more than 3 levels deep) to maintain code readability and manageability. Excessive nesting can make code harder to understand and maintain.

#### Summary:
- A **compound statement** (or **block**) is a group of zero or more statements treated as a single statement, delimited by curly braces `{}`.
- Blocks can be nested inside other blocks, creating multiple levels of nesting.
- Each block can contain its own statements and further nested blocks.
- While C++ allows deep nesting of blocks, it’s generally advisable to keep nesting levels shallow (typically no more than 3 levels deep) to maintain code readability and manageability.


---

### S02 — 7.2 User-defined namespaces and the scope resolution operator
In a previous chapter, we introduced the concept of `naming collisions` and `namespaces` as a way to avoid them. As a reminder, a naming collision occurs when two or more identifiers (such as variable names, function names, or class names) in the same scope have the same name, leading to ambiguity and errors during compilation.  
A `namespace` is a declarative region that provides a scope to the identifiers inside it.

For example, consider two libraries that both define a function called `print()`. If you include both libraries in your program, the compiler will not know which `print()` function to use, resulting in a naming collision. If in the project you include only one library, there is no problem. But if you include both libraries, you will get a compilation or linking error.

One way to fix this would be to rename one of the functions, but this is not always possible or desirable, especially when dealing with third-party libraries. Instead, we can use namespaces to group related identifiers together and avoid naming collisions. For this reason the C++ Standard Library places all its identifiers inside the `std` namespace.

#### Defining your own namespaces:
You can define your own namespaces using the `namespace` keyword followed by the namespace name and a block of code enclosed in curly braces. For example:
```cpp
namespace NamespaceIdentifier
{
    // content of namespace here
}
```

> **Note:** We recommend using `PascalCase` for naming namespaces to distinguish them from variables and functions, which typically use `camelCase` or `snake_case`.

For example, in the previous example of naming collision with the `print()` function, we could define two namespaces, one for `libraryA.cpp` and one for `libraryB.cpp`, as follows:
```cpp
namespace LibraryA
{
    void print()
    {
        // implementation of print function for library A
    }
}
```
and
```cpp
namespace LibraryB
{
    void print()
    {
        // implementation of print function for library B
    }
}
```

Now, if we leave the main proram `main.cpp` as it is, the compiler will work, but the linker will not find the definition of `print()`, because it is looking for a function called `print()` in the global namespace, but both functions are defined inside their respective namespaces. To call the correct function, we have two different options:
1. Use the `scope resolution operator` (`::`) to specify the namespace when calling the function. For example:
    ```cpp
    #include "libraryA.cpp"
    #include "libraryB.cpp"

    int main()
    {
        LibraryA::print(); // calls print function from library A
        LibraryB::print(); // calls print function from library B

        return 0;
    }
    ```
2. Use the `using` statement (treated in a later section) to bring the namespace into the current scope. For example:
    ```cpp
    #include "libraryA.cpp"
    #include "libraryB.cpp"

    using namespace LibraryA;
    using namespace LibraryB;

    int main()
    {
        print(); // Error: ambiguous call to print()

        return 0;
    }
    ```

#### Accessing a namespace with the scope resolution operator (`::`):
The `scope resolution operator` (`::`) is used to access members of a namespace or class. It tells the compiler that the identifier specified after the operator belongs to the namespace or class specified before the operator.  
For example, to access the `print()` function from `LibraryA`, we would use:
```cpp
LibraryA::print();
```
Similarly, to access the `print()` function from `LibraryB`, we would use:
```cpp
LibraryB::print();
```

#### Using the scope reolsution operator with no name prefix:
The scope resolution operator can also be used with no name before it to refer to the global namespace. This is useful when you have a local identifier that shadows a global identifier. For example:
```cpp
    #include "libraryA.cpp"
    #include "libraryB.cpp"

    int main()
    {
        LibraryA::print(); // calls print function from library A
        LibraryB::print(); // calls print function from library B
        ::print(); // calls print function from global namespace (if defined)

        return 0;
    }
```

#### Identifier resolution from within a namespace:
When you are inside a namespace, the compiler first looks for identifiers in the current namespace before looking in the global namespace (it will be cheked last). For example:
```cpp
namespace MyNamespace
{
    void myFunction()
    {
        // implementation of myFunction
    }
    void anotherFunction()
    {
        myFunction(); // calls myFunction from MyNamespace
        ::myFunction(); // calls myFunction from global namespace (if defined)
    }
}
```

In this way, using `::` allows you to explicitly specify that you want to access the global version of an identifier, even when you are inside a namespace that has its own version of that identifier.

#### Forward declaration of content in namespaces:
You can forward declare functions, classes, and variables inside a namespace before defining them. This is useful when you want to declare the existence of an identifier without providing its full definition. For example, if we have the following project structure:

add.h
```cpp
#ifndef ADD_H
#define ADD_H

namespace BasicMath
{
    // function add() is part of namespace BasicMath
    int add(int x, int y);
}

#endif
```

add.cpp
```cpp
#include "add.h"

namespace BasicMath
{
    // define the function add() inside namespace BasicMath
    int add(int x, int y)
    {
        return x + y;
    }
}
```

main.cpp
```cpp
#include "add.h" // for BasicMath::add()

#include <iostream>

int main()
{
    std::cout << BasicMath::add(4, 3) << '\n';

    return 0;
}
```

In this way, we can separate the declaration and definition of the `add()` function while keeping it within the `BasicMath` namespace.

#### Multiple namespace blocks are allowed:
You can define multiple blocks for the same namespace in different parts of your code. The compiler will treat them as part of the same namespace. For example:

circle.h
```cpp
#ifndef CIRCLE_H
#define CIRCLE_H

namespace BasicMath
{
    constexpr double pi{ 3.14 };
}

#endif
```

growth.h
```cpp
#ifndef GROWTH_H
#define GROWTH_H

namespace BasicMath
{
    // the constant e is also part of namespace BasicMath
    constexpr double e{ 2.7 };
}

#endif
```

main.cpp
```cpp
#include "circle.h" // for BasicMath::pi
#include "growth.h" // for BasicMath::e

#include <iostream>

int main()
{
    std::cout << BasicMath::pi << '\n';
    std::cout << BasicMath::e << '\n';

    return 0;
}
```
This will output:
```
3.14
2.7
```
because both `pi` and `e` are part of the `BasicMath` namespace, even though they are defined in separate blocks.

For example, the standard library defines the `std` namespace in multiple blocks across different header files.

#### Nested namespaces:
Namespaces can be nested inside other namespaces to create a hierarchy of namespaces. For example:
```cpp
namespace OuterNamespace
{
    namespace InnerNamespace
    {
        // content of InnerNamespace here
    }
}
```
You can access members of nested namespaces using the scope resolution operator. For example:
```cpp
OuterNamespace::InnerNamespace::someFunction();
```

Since C++17, you can also define nested namespaces using a more concise syntax:
```cpp
namespace OuterNamespace::InnerNamespace
{
    // content of InnerNamespace here
}
```

If later you need to add declaration to the `OuterNamespace` namespace (only), you can do it like this:
```cpp
namespace OuterNamespace
{
    // additional content of OuterNamespace here
}
```

#### Namespaces aliases:
You can create an alias for a namespace using the `namespace` keyword followed by the alias name, an equals sign (`=`), and the original namespace name. This is useful when you have long namespace names or when you want to shorten the name for convenience. For example:
```cpp
int main ()
{
    namespace Active = BasicMath; // create an alias Active for namespace BasicMath

    std::cout << Active::add(4, 3) << '\n'; // use the alias to call add()

    return 0;
}
```

This is a nice feature, since you can chnage funcitonality simply changing the `Active` alias to point to another namespace, without changing the rest of the code.

#### How to use namespaces:
- Small applications developed for your own use may not need namespaces at all. However, for larger personal projects, it’s a good practice to define your own namespace to avoid potential naming collisions in the future.
- When developing libraries or code that will be shared with others, always use namespaces to encapsulate your identifiers and prevent naming collisions. An additional advantage of using namespaces in libraries is that allows the users to see which functions and classes belong to your library by looking at the namespace name (autocompletion will help with this).

- In multi-team organizations, two-level or even three-level namespaces are often used to avoid naming collisions between different teams or departments. For example, a company named `TechCorp` might use the namespace `TechCorp::Graphics` for its graphics library and `TechCorp::Networking` for its networking library.

#### Summary:
- A `namespace` is a declarative region that provides a scope to the identifiers inside it, helping to avoid naming collisions.
- You can define your own namespaces using the `namespace` keyword followed by the namespace name and a block of code enclosed in curly braces.
- The `scope resolution operator` (`::`) is used to access members of a namespace or class.
- You can forward declare functions, classes, and variables inside a namespace before defining them.
- Multiple blocks for the same namespace are allowed in different parts of your code.
- Namespaces can be nested inside other namespaces to create a hierarchy of namespaces.
- You can create an alias for a namespace using the `namespace` keyword followed by the alias name, an equals sign (`=`), and the original namespace name.


---

### S03 — 7.3 Local variables
In a previous chapter, we introduced `local variables` as variables that are declared inside a block (such as a function or a loop) and are only accessible within that block. It turn out that C++ does not have any single attribute or keyword to define a local variable, but rather the scope of a variable is determined by where it is declared. In that chapter, we have also introduced the concept of `scope`, which is the region of the program where an identifier (such as a variable or a function) is accessible. When an identifier is not accessible, we say that it is `out of scope`.

#### Local variables have block scope:
Local variables have `block scope`, which means that they are only accessible within the block where they are declared. For example:
```cpp
int main()
{
    int i { 5 }; // i enters scope here
    double d { 4.0 }; // d enters scope here

    return 0;
} // d and i go out of scope here
```
In this example, the variables `i` and `d` are declared inside the `main()` function, so they are only accessible within the `main()` function. When the program reaches the closing brace of the `main()` function, both `i` and `d` go out of scope and can no longer be accessed.

#### All variable names within a scope must be unique:
Within a given scope, all variable names must be unique. You cannot declare two variables with the same name in the same scope. For example, the following code will result in a compilation error:
```cpp
int main()
{
    int i { 5 };
    double i { 4.0 }; // Error: redeclaration of 'i'

    return 0;
}
```
or
```cpp
void someFunction(int x)
{
    int x{}; // compilation failure due to name collision with function parameter
}

int main()
{
    return 0;
}
```
In this example, the variable `i` is declared twice in the same scope, which is not allowed. In the second example, the variable `x` is declared as a function parameter and then again as a local variable, which also results in a name collision.

#### Local variables have automatic storage duration:
A variable's **storage duration** determines how long the variable exists in memory during program execution. Local variables have `automatic storage duration`, which means that they are created when the block where they are declared is entered and destroyed when the block is exited. For example:
```cpp
int main()
{
    { // start of block
        int i { 5 }; // i is created here
        // use i
    } // i is destroyed here
    return 0;
}
```
In this example, the variable `i` is created when the program enters the block and is destroyed when the program exits the block. This is the default behavior for local variables in C++.

#### Local variables in nested blocks:
Local variables can be declared in nested blocks, and each block has its own scope. This works the same as with functions. For example:
```cpp
int main()
{
    int x { 10 }; // x in outer block
    { // start of inner block
        int y { 20 }; // y in inner block
        // x and y are accessible here
    } // end of inner block, y goes out of scope here
    // x is still accessible here, but y is not
    return 0;
}
```
In this example, the variable `x` is declared in the outer block and is accessible throughout the entire `main()` function. The variable `y` is declared in the inner block and is only accessible within that inner block. When the program exits the inner block, `y` goes out of scope and can no longer be accessed.

> **Note:** Variables defined in the outer block are accessible in the inner block, but variables defined in the inner block are not accessible in the outer block.

#### Local variables have no linkage:
An identifier's **linkage** determines whether the same identifier in different scopes refers to the same entity or different entities. Local variables have `no linkage`, which means that they are unique to the block where they are declared and cannot be accessed from other blocks. For example:
```cpp
void someFunction()
{
    int x { 5 }; // x in someFunction, different from x in main
}
int main()
{
    int x { 10 }; // x in main, different from x in someFunction
    return 0;
}
```
In this example, the variable `x` declared in `someFunction()` is different from the variable `x` declared in `main()`. They have no linkage, so they are treated as separate entities.

#### Variables should be defined in the most limited scope:
It is a good practice to define variables in the most limited scope possible. This means that you should declare variables in the innermost block where they are needed, rather than in an outer block. This helps to reduce the risk of naming collisions and makes the code easier to read and maintain. For example:
```cpp
int main()
{
    // Bad practice: defining variables in outer block
    int i { 0 };
    for (i = 0; i < 10; ++i)
    {
        // use i
    }
    return 0;
}
```
In this example, the variable `i` is defined in the outer block of the `main()` function, even though it is only needed in the `for` loop. A better practice would be to define `i` in the `for` loop itself:
```cpp
int main()
{
    // Good practice: defining variable in the most limited scope
    for (int i = 0; i < 10; ++i)
    {
        // use i
    }
    return 0;
}
```
In this example, the variable `i` is defined in the `for` loop, which is the most limited scope where it is needed, and we will avoid potential naming collisions with other variables named `i` in the outer block.

> **Best practice:** Always strive to define variables in the most limited scope possible to enhance code clarity and reduce the likelihood of naming collisions.

#### Summary:
- Local variables have `block scope`, meaning they are only accessible within the block where they are declared.
- All variable names within a scope must be unique; redeclaring a variable with the same name in the same scope results in a compilation error.
- Local variables have `automatic storage duration`, meaning they are created when the block is entered and destroyed when the block is exited.
- Local variables can be declared in nested blocks, with outer block variables accessible in inner blocks, but not vice versa.
- Local variables have `no linkage`, meaning they are unique to the block where they are declared and cannot be accessed from other blocks.
- It is a good practice to define variables in the most limited scope possible to reduce naming collisions and improve code readability.


---

### S04 — 7.4 Introduction to global variables
In C++ variables can also be declared outside of a function or block. These variables are called `global variables` because they have `global scope`, meaning they are accessible from any part of the program after their declaration. Global variables have `static storage duration`, which means they are created when the program starts and destroyed when the program ends. Additionally, global variables have `external linkage` by default, meaning they can be accessed from other translation units (source files) in the same program.

#### Declaring global variables:
A global variable is declared outside of any function or block, below the `#include` directives and above the `main()`, in the **global namespace**. For example:
```cpp
#include <iostream>

// Variables declared outside of a function are global variables
int g_x {}; // global variable g_x 

void doSomething()
{
    // global variables can be seen and used everywhere in the file
    g_x = 3;
    std::cout << g_x << '\n';
}

int main()
{
    doSomething();
    std::cout << g_x << '\n';

    // global variables can be seen and used everywhere in the file
    g_x = 5;
    std::cout << g_x << '\n';

    return 0;
}
// g_x goes out of scope here (end of program)
```
printing:
```
3
3
5
```

#### The scope of global variables:
Identifiers declared in the global namespace have **global namespace scope** (commonly referred to as `global scope`, and soemtimes ifnormally called `file scope`), meaning they are accessible from any part of the program after their declaration, until the end of the translation unit (source file).

Global variables can also be defined inside a user-defined namespace, and they will still be accessible from any part of the program after their declaration, until the end of the translation unit (source file), but they will be part of that namespace. For example:
```cpp
#include <iostream>

namespace MyNamespace
{
    int g_y {}; // global variable g_y inside MyNamespace, but still global scope
}

void doSomething()
{
    // global variables can be seen and used everywhere in the file
    MyNamespace::g_y = 7;
    std::cout << MyNamespace::g_y << '\n';
}

int main()
{
    doSomething();
    std::cout << MyNamespace::g_y << '\n';

    // global variables can be seen and used everywhere in the file
    MyNamespace::g_y = 10;
    std::cout << MyNamespace::g_y << '\n';

    return 0;
}
// g_y goes out of scope here (end of program)
```
prints:
```
7
7
10
```

#### Global variables have static duration:
Global variables have `static storage duration`, which means they are created when the program starts (before `main()` is called) and destroyed when the program ends (after `main()` returns). This means that global variables retain their values throughout the entire execution of the program. For example:
```cpp
#include <iostream>
int g_counter {}; // global variable g_counter
void incrementCounter()
{
    ++g_counter; // increment the global counter
    std::cout << "Counter: " << g_counter << '\n';
}

int main()
{
    incrementCounter();
    incrementCounter();
    incrementCounter();

    return 0;
}
// g_counter goes out of scope here (end of program)
```
prints:
```
Counter: 1
Counter: 2
Counter: 3
```

#### Naming global variables:
When naming global variables, it is a good practice to use a naming convention that distinguishes them from local variables. A common convention is to prefix global variable names with `g` or `g_` (for static variables). This helps for:
- Avoiding naming collisions with local variables.
- Preventing inadvertent name shadowing (when a local variable has the same name as a global variable, we will see later).
- Indicating that `g_*` variables are global in scope.

#### Global variable initialization:
Unlike local variables, which are not automatically initialized and may contain garbage values if not explicitly initialized, global variables are automatically **initialized to zero** (or equivalent for their type) if not explicitly initialized. For example:
```cpp
int g_x;       // no explicit initializer (zero-initialized by default)
int g_y {};    // value initialized (resulting in zero-initialization)
int g_z { 1 }; // list initialized with specific value
```

#### Constant global variables:
It is a good practice to declare global variables as `const` whenever possible. This prevents accidental modification of the variable and makes the code easier to understand and maintain. For example:
```cpp
const double g_pi { 3.14159 }; // constant global variable
```
Using `const` for global variables also allows the compiler to perform optimizations, as it knows that the value of the variable will not change throughout the program.

If you do not initialize a `const` global variable at the point of declaration, you will get a compilation error, since `const` variables must be initialized when they are declared. For example:
```cpp
#include <iostream>

const int g_x;     // error: constant variables must be initialized
constexpr int g_w; // error: constexpr variables must be initialized

const int g_y { 1 };     // const global variable g_y, initialized with a value
constexpr int g_z { 2 }; // constexpr global variable g_z, initialized with a value

void doSomething()
{
    // global variables can be seen and used everywhere in the file
    std::cout << g_y << '\n';
    std::cout << g_z << '\n';
}

int main()
{
    doSomething();

    // global variables can be seen and used everywhere in the file
    std::cout << g_y << '\n';
    std::cout << g_z << '\n';

    return 0;
}
// g_y and g_z goes out of scope here
```

> **Best practice:** Always prefer `const` or `constexpr` for global variables to prevent accidental modifications and enhance code clarity. Avoid using non-constant global variables whenever possible.

#### Summary:
- Global variables have `global scope`, meaning they are accessible from any part of the program after their declaration.
- Global variables have `static storage duration`, meaning they are created when the program starts and destroyed when the program ends.
- Global variables have `external linkage` by default, meaning they can be accessed from other translation units (source files) in the same program.
- It is a good practice to use a naming convention (such as prefixing with `g_`) to distinguish global variables from local variables.
- Global variables are automatically initialized to zero if not explicitly initialized.
- It is a good practice to declare global variables as `const` or `constexpr` whenever possible to prevent accidental modification and improve code clarity.


---

### S05 - 7.5 Variable shadowing (name hiding)
`Variable shadowing` (or `name hiding`) occurs when a local variable defined in an inner scope has the same name as a variable defined in an outer scope. In this case, the local variable "shadows" or "hides" the outer variable within its scope. This means that any reference to the variable name within the inner scope will refer to the local variable, not the outer variable. 

#### Shadowing of local variables:
```cpp
#include <iostream>

int main()
{
    int x { 10 }; // outer x

    {
        int x { 20 }; // inner x shadows outer x
        std::cout << "Inner x: " << x << '\n'; // prints 20
    }

    std::cout << "Outer x: " << x << '\n'; // prints 10

    return 0;
}
```
prints:
```
Inner x: 20
Outer x: 10
```
In this example, the inner variable `x` shadows the outer variable `x` within the inner block. When we print `x` inside the inner block, it refers to the inner variable, while outside the block, it refers to the outer variable.

#### Shadowing of global variables:
```cpp
#include <iostream>

int g_x { 5 }; // global variable g_x

void doSomething()
{
    std::cout << "Local g_x in doSomething: " << g_x << '\n'; // prints 5, global g_x
}

int main()
{
    int g_x { 10 }; // local variable g_x shadows global g_x
    std::cout << "Local g_x: " << g_x << '\n'; // prints 10
    doSomething();

    return 0;
}
```
prints:
```
Local g_x: 10
Global g_x: 5
```
In this example, the local variable `g_x` in `main()` shadows the global variable `g_x`. When we print `g_x` in `main()`, it refers to the local variable, while in `doSomething()`, it refers to the global variable, since it is not shadowed there.

However, since global variables are part of the global namespace, we can use the scope operator `::` to access the global variable even when it is shadowed by a local variable. For example:
```cpp
#include <iostream>

int g_x { 5 }; // global variable g_x

int main()
{
    int g_x { 10 }; // local variable g_x shadows global g_x
    std::cout << "Local g_x: " << g_x << '\n'; // prints 10
    std::cout << "Global g_x: " << ::g_x << '\n'; // prints 5, accessing global g_x using scope resolution operator
    return 0;
}
```
prints:
```
Local g_x: 10
Global g_x: 5
```

#### Avoid variable shadowing:
While variable shadowing is allowed in C++, it can lead to confusion and bugs in the code. It is generally a good practice to avoid variable shadowing by using unique names for variables in different scopes. This improves code readability and reduces the risk of unintended behavior due to name collisions.

#### Summary:
- `Variable shadowing` (or `name hiding`) occurs when a local variable defined in an inner scope has the same name as a variable defined in an outer scope.
- The local variable shadows or hides the outer variable within its scope.
- Shadowing can occur with both local variables and global variables.
- The scope resolution operator (`::`) can be used to access a shadowed global variable from within a local scope.
- It is generally a good practice to avoid variable shadowing by using unique names for variables in different scopes to improve code readability and reduce the risk of unintended behavior due to name collisions.


---

### S06 - 7.6 Internal linkage
In a previous section, we introduced the concept of `linkage`, which determines whether the same identifier in different scopes refers to the same entity or different entities. We said that local variables have `no linkage`, meaning they are unique to the block where they are declared and cannot be accessed from other blocks.

Global variables and function identifiers, on the other hand, can have `internal linkage` or `external linkage`:
- `Internal linkage` means that the identifier is accessible only within the translation unit (source file) where it is defined. This is useful for encapsulating variables and functions that should not be exposed to other parts of the program.
- `External linkage` means that the identifier can be accessed from other translation units (source files) in the same program. This is the default behavior for global variables and functions.

In this section, we will focus on `internal linkage`, while in the next section we will treat `external linkage`.

#### Global variables with internal linkage:
Global variables with in internal linkage are sometimes referred to as `internal variables`. To declare a **non-constant global variable** with internal linkage, you can use the `static` keyword. For example:
```cpp
#include <iostream>

static int g_x{}; // non-constant globals have external linkage by default, but can be given internal linkage via the static keyword

const int g_y{ 1 }; // const globals have internal linkage by default
constexpr int g_z{ 2 }; // constexpr globals have internal linkage by default

int main()
{
    std::cout << g_x << ' ' << g_y << ' ' << g_z << '\n';
    return 0;
}
```
In this example, the global variable `g_x` is declared with the `static` keyword, giving it internal linkage. The constant global variables `g_y` and `g_z` have internal linkage by default.

> **Note:** Constant (`const`) and `constexpr` global variables have internal linkage by default, so you do not need to use the `static` keyword for them.

For example, if you have a project with `a.cpp` and `main.cpp`:

a.cpp
```cpp
[[maybe_unused]] constexpr int g_x { 2 }; // this internal g_x is only accessible within a.cpp
```

main.cpp
```cpp
#include <iostream>

static int g_x { 3 }; // this separate internal g_x is only accessible within main.cpp

int main()
{
    std::cout << g_x << '\n'; // uses main.cpp's g_x, prints 3

    return 0;
}
```
In this example, both `a.cpp` and `main.cpp` define their own `g_x` variable with internal linkage. The `g_x` in `a.cpp` is not accessible from `main.cpp`, and vice versa, so the program prints `3`.

#### Functions with internal linkage:
Function by default have `external linkage`, meaning they can be accessed from other translation units (source files) in the same program. However, you can give a function internal linkage by using the `static` keyword. For example:

add.cpp
```cpp
[[maybe_unused]] static int add(int x, int y) // function add() has internal linkage
{
    return x + y;
}
```

main.cpp
```cpp
#include <iostream>

int add(int x, int y); // forward declaration for function add

int main()
{
    std::cout << add(3, 4) << '\n';

    return 0;
}
```
In this example, you will get a linker error, because the `add()` function in `add.cpp` has internal linkage and is not accessible from `main.cpp`.

#### The one-definition rule and internal linkage:
In C++, the `one-definition rule` (ODR) states that an identifier (such as a variable or function) can have only one definition in a program. However, when an identifier has internal linkage, it can be defined in multiple translation units (source files) without violating the ODR, because each definition is unique to its own translation unit. For example, both `a.cpp` and `b.cpp` can define their own `static` variable with the same name without causing a conflict:
a.cpp
```cpp
static int g_counter {}; // internal variable g_counter in a.cpp
```
b.cpp
```cpp
static int g_counter {}; // internal variable g_counter in b.cpp
```
In this example, both `a.cpp` and `b.cpp` define their own `g_counter` variable with internal linkage. Each `g_counter` is unique to its own translation unit, so there is no conflict.

#### `static` vs unnamed namespaces:
Before C++11, the `static` keyword was the primary way to give variables and functions internal linkage. However, since C++11, it is recommended to use `unnamed namespaces` to achieve the same effect. An unnamed namespace is a namespace without a name, and all identifiers declared inside it have internal linkage. For example:
```cpp
#include <iostream>

namespace
{
    int g_x{}; // g_x has internal linkage
    void doSomething() // doSomething() has internal linkage
    {
        std::cout << "Doing something\n";
    }
}

int main()
{
    g_x = 5;
    std::cout << g_x << '\n';
    doSomething();

    return 0;
}
```
In this example, both the variable `g_x` and the function `doSomething()` have internal linkage because they are declared inside an unnamed namespace.

We will cover this feature in more detail in a later chapter.

#### Why bother giving identifiers internal linkage?
Giving identifiers internal linkage is a good practice for several reasons:
- **Encapsulation:** It helps to encapsulate variables and functions that should not be exposed to other parts of the program, reducing the risk of unintended interactions.
- **Avoiding naming collisions:** It prevents naming collisions between identifiers in different translation units (source files), allowing you to use the same names without conflicts.
- **Improved maintainability:** It makes the code easier to maintain by clearly indicating which identifiers are intended for use only within a specific translation unit.

#### Summary:
- `Internal linkage` means that the identifier is accessible only within the translation unit (source file) where it is defined.
- To declare a non-constant global variable with internal linkage, you can use the `static` keyword.
- Constant (`const`) and `constexpr` global variables have internal linkage by default.
- You can give a function internal linkage by using the `static` keyword.
- When an identifier has internal linkage, it can be defined in multiple translation units (source files) without violating the one-definition rule (ODR).
- Since C++11, it is recommended to use `unnamed namespaces` to achieve internal linkage instead of the `static` keyword.
- Giving identifiers internal linkage helps with encapsulation, avoiding naming collisions, and improving code maintainability.

```cpp
// Internal global variables definitions:
static int g_x;          // defines non-initialized internal global variable (zero initialized by default)
static int g_x{ 1 };     // defines initialized internal global variable

const int g_y { 2 };     // defines initialized internal global const variable
constexpr int g_y { 3 }; // defines initialized internal global constexpr variable

// Internal function definitions:
static int foo() {};     // defines internal function
```


---

### S07 - 7.7 External linkage and variable forward declarations
In the previous section, we introduced the concept of `internal linkage`, which means that an identifier is accessible only within the translation unit (source file) where it is defined. In this section, we will focus on `external linkage`, which means that an identifier can be accessed from other translation units (source files) in the same program.

An identifier with **external linkage** can be seen and used both within the translation unit where it is defined and from other translation units in the same program, through the use of `forward declarations`.

#### Functions have external linkage by default:
Functions in C++ have `external linkage` by default, meaning they can be accessed from other translation units (source files) in the same program, using forward declarations. The forward declaration tells the compiler about the existence of the function, allowing it to be called before its definition is encountered. For example:

a.cpp
```cpp
#include <iostream>

void sayHi(); // forward declaration, function has external linkage by default
{
    std::cout << "Hi!\n";
}
```

main.cpp
```cpp
#include <iostream>

void sayHi(); // forward declaration for function sayHi, making it accessible from this translation unit

int main()
{
    sayHi(); // call the function, linker will connect to the definition in a.cpp
    return 0;
}
```
prints:
```
Hi!
```

#### Global variables with external linkage:
Global variables with external linkage are sometimes called **external variables**. By default, non-constant global variables have `external linkage`, while constant (`const`) and `constexpr` global variables have `internal linkage` by default. To declare a `const` or `constexpr` global variable with external linkage, you can use the `extern` keyword. For example:
```cpp
int g_x { 2 }; // non-constant globals are external by default (no need to use extern)

extern const int g_y { 3 }; // const globals can be defined as extern, making them external
extern constexpr int g_z { 3 }; // constexpr globals can be defined as extern, making them external (but this is pretty useless, see the warning in the next section)

int main()
{
    return 0;
}
```

#### Variable forward declarations:
To access a global variable with external linkage from another translation unit (source file), you need to use a `forward declaration` with the `extern` keyword. This tells the compiler about the existence of the variable, allowing it to be used before its definition is encountered. For example, if you have a project with `a.cpp` and `main.cpp`:

a.cpp
```cpp
// global variable definitions
int g_x { 2 };              // non-constant globals have external linkage by default
extern const int g_y { 3 }; // this extern gives g_y external linkage
extern constexpr int g_z { 4 }; // this extern gives g_z external linkage (but this is pretty useless, see the warning in the next section)
```

main.cpp
```cpp
#include <iostream>

extern int g_x;          // forward declaration for non-constant global variable g_x
extern const int g_y;    // forward declaration for const global variable g_y
extern constexpr int g_z; // forward declaration for constexpr global variable g_z

int main()
{
    std::cout << "g_x: " << g_x << "\n";
    std::cout << "g_y: " << g_y << "\n";
    std::cout << "g_z: " << g_z << "\n";
    return 0;
}
```

So, the `extern` keyword is used in two ways for global variables:
- To declare a global variable with external linkage (for `const` and `constexpr` variables).
- To forward declare a global variable with external linkage in another translation unit.

Also, in general, variables and function forward declarations differs in:
- Variables forward declarations must use the `extern` keyword.
- Functions forward declarations do not require any keyword, the compiler understands it.

#### Avoid using `extern` on a non-const global variable initializer:
When defining a non-constant global variable, you should avoid using the `extern` keyword on the initializer, as this can lead to confusion and possibly to a compilation warning or error. The `extern` keyword is used for forward declarations, not for definitions. For example, the following two lines are equivalent:
```cpp
int g_x { 2 };          // correct: defines and initializes g_x
extern int g_x { 2 };   // explicitly using extern on definition, may cause a warning
```
Both lines define and initialize the global variable `g_x`. However, using `extern` in this context is unnecessary and may lead to confusion, as it suggests that `g_x` is being forward declared rather than defined.

#### Summary:
- `External linkage` means that the identifier can be accessed from other translation units (source files) in the same program.
- Functions have `external linkage` by default and can be accessed from other translation units using forward declarations.
- Non-constant global variables have `external linkage` by default.
- To declare a `const` or `constexpr` global variable with external linkage, you can use the `extern` keyword.
- To access a global variable with external linkage from another translation unit, you need to use a forward declaration with the `extern` keyword.
- Variable forward declarations must use the `extern` keyword, while function forward declarations do not require any keyword.
- Avoid using `extern` on a non-const global variable initializer, as it can lead to confusion and possibly to a compilation warning or error.

```cpp
// Global variable forward declarations (extern w/ no initializer):
extern int g_y;                 // forward declaration for non-constant global variable
extern const int g_y;           // forward declaration for const global variable
extern constexpr int g_y;       // not allowed: constexpr variables can't be forward declared

// External global variable definitions (no extern)
int g_x;                        // defines non-initialized external global variable (zero initialized by default)
int g_x { 1 };                  // defines initialized external global variable

// External const global variable definitions (extern w/ initializer)
extern const int g_x { 2 };     // defines initialized const external global variable
extern constexpr int g_x { 3 }; // defines initialized constexpr external global variable
```

To summarize, here a table with internal and external linkage:
| Identifier Type          | Default Linkage   | How to Specify Internal Linkage | How to Specify External Linkage |
|--------------------------|-------------------|----------------------------------|--------------------------|
| Non-constant global var  | External          | `static` keyword                 | (default - no keyword)      |
| Constant (`const`) global var | Internal       | (default - no keyword)           | | `extern` keyword          |
| `constexpr` global var   | Internal          | (default - no keyword)           | `extern` keyword          |
| Function                 | External          | `static` keyword                 | (default - no keyword)      |


---

### S08 - 7.8 Why (non-const) global variables are evil
In the previous sections, we have discussed global variables, their scope, duration, and linkage. In this section, we will discuss why using non-constant global variables is generally considered a bad practice in C++ programming.

#### Why (non-const) global variables are evil:
The main issue with non-constant global variables is that they can lead to `uncontrolled access` from any part of the program. This can make it difficult to track changes to the variable and understand the flow of data in the program. Here are some specific reasons why non-constant global variables are considered harmful:
1. **Unintended side effects:** Since global variables can be accessed and modified from anywhere in the program, it can be challenging to predict how changes to the variable will affect other parts of the code. This can lead to unintended side effects and bugs that are hard to trace.
2. **Reduced modularity:** Global variables can create tight coupling between different parts of the code, making it difficult to isolate and test individual components. This can lead to code that is harder to maintain and extend.
3. **Namespace pollution:** Global variables occupy the global namespace, which can lead to naming collisions and make it harder to manage the overall structure of the code.
4. **Difficulty in debugging:** When a bug arises due to the misuse of a global variable, it can be challenging to identify the source of the problem, as the variable can be modified from multiple locations in the code.
5. **Concurrency issues:** In multi-threaded programs, global variables can lead to race conditions if multiple threads access and modify the variable simultaneously without proper synchronization.

Consider the following example:
```cpp
#include <iostream>

int g_mode; // declare global variable (will be zero-initialized by default)

void doSomething()
{
    g_mode = 2; // set the global g_mode variable to 2
}

int main()
{
    g_mode = 1; // note: this sets the global g_mode variable to 1.  It does not declare a local g_mode variable!

    doSomething();

    // Programmer still expects g_mode to be 1
    // But doSomething changed it to 2!

    if (g_mode == 1)
    {
        std::cout << "No threat detected.\n";
    }
    else
    {
        std::cout << "Launching nuclear missiles...\n";
    }

    return 0;
}
```
prints:
```
Launching nuclear missiles...
```
In this example, the global variable `g_mode` is modified in the `doSomething()` function, which leads to unexpected behavior in the `main()` function. The programmer expected `g_mode` to remain `1`, but it was changed to `2`, resulting in the wrong output.

> **Best practice:** Use local variables instead of global variables whenever possible. If you need to share data between different parts of the program, consider using function parameters, return values, or encapsulating the data within classes or structures.

#### The initialization order problem of global variables:
The initialization of static variables (including global variables) takes place as part of the program startup, before the `main()` function is called. This process is divided into two phases:
1. **Static initialization:** In this phase, variables with constant initializers (e.g., `const` or `constexpr` variables) are initialized. This is divided into two sub-phases:
   - **Constant initialization:** Global variables with `constexpr` (including literals) initializers are initialized first.
   - **Zero initialization:** Global variables without explicit initializers are initialized to zero.

   For example:
   ```cpp
    constexpr int g_value1 { 5 }; // constant initialization
   ```
   ```cpp
    int g_value2; // zero initialization (initialized to 0 by default)
   ```
2. **Dynamic initialization:** In this phase, variables with non-constant initializers (non-constexpr) are initialized. For example:
    ```cpp
    int init()
    {
        return 5;
    }

    int g_something{ init() }; // non-constexpr initialization
    ```
    Within a single file, these variables are initialized in the order they are defined. For example:
    ```cpp
    #include <iostream>

    int initX();  // forward declaration
    int initY();  // forward declaration

    int g_x{ initX() }; // g_x is initialized first
    int g_y{ initY() };

    int initX()
    {
        return g_y; // g_y isn't initialized when this is called, so it will be 0
    }

    int initY()
    {
        return 5;
    }

    int main()
    {
        std::cout << g_x << ' ' << g_y << '\n';
    }
    ```
    prints:
    ```
    0 5
    ```
    In this example, `g_x` is initialized first by calling `initX()`, which tries to access `g_y`. However, `g_y` has not been initialized yet, so it contains the default value of `0`.

    However, across multiple files, the order of dynamic initialization is undefined, which can lead to the `initialization order problem`. This problem occurs when a global variable in one translation unit depends on the value of a global variable in another translation unit, and the order of initialization is not guaranteed.

#### So what are very good reasons to use non-const global variables?
While non-constant global variables are generally discouraged, there are some scenarios where their use may be justified:
- **Configuration settings:** In some cases, a non-constant global variable may be used to store configuration settings that need to be accessed throughout the program. However, it is often better to encapsulate these settings within a class or structure.
- **Logging:** A global logging level variable may be used to control the verbosity of logging output across the program. Again, consider encapsulating this within a logging class.
- **Performance optimization:** In performance-critical applications, global variables may be used to avoid the overhead of passing large data structures between functions. However, this should be done with caution and proper documentation.

#### Protecting yourself from global destruction:
Here some good practices to protect yourself from issues related to global variable destruction:
- **Prefix non-namespaced global variables** with a unique identifier (e.g., `g_` for globals) to avoid naming conflicts and make their global nature explicit. For example, instead of:
    ```cpp
    #include <iostream>

    constexpr double gravity { 9.8 }; // risk of collision with some other global variable named gravity

    int main()
    {
        std::cout << gravity << '\n'; // unclear if this is a local or global variable from the name

        return 0;
    }
    ```
    use:
    ```cpp
    #include <iostream>

    constexpr double g_gravity { 9.8 }; // clearly a global variable

    int main()
    {
        std::cout << g_gravity << '\n'; // clearly a global variable from the name

        return 0;
    }
    ```
- **Encapsulate global variables** so that can only be accessed from within the file it is declared (e.g., making the variable static or const). This reduces the risk of unintended modifications from other parts of the program. For example, instead of:

    constants.cpp:
    ```cpp
    namespace constants
    {
        extern const double gravity { 9.8 }; // has external linkage, can be accessed by other files
    }
    ```

    main.cpp:
    ```cpp
    #include <iostream>

    namespace constants
    {
        extern const double gravity; // forward declaration
    }

    int main()
    {
        std::cout << constants::gravity << '\n'; // direct access to global variable

        return 0;
    }
    ```
    use:
    constants.cpp:
    ```cpp
    namespace constants
    {
        constexpr double gravity { 9.8 }; // has internal linkage, is accessible only within this file
    }

    double getGravity() // has external linkage, can be accessed by other files
    {
        // We could add logic here if needed later
        // or change the implementation transparently to the callers
        return constants::gravity;
    }
    ```

    main.cpp:
    ```cpp
    #include <iostream>

    double getGravity(); // forward declaration

    int main()
    {
        std::cout << getGravity() << '\n';

        return 0;
    }
    ```
- **Use arguments and return values** to pass data between functions instead of relying on global variables. This makes the code more modular and easier to understand. For example, instead of:
    ```cpp
    #include <iostream>

    namespace constants
    {
        constexpr double gravity { 9.8 };
    }

    // This function is only useful for calculating your instant velocity based on the global gravity
    double instantVelocity(int time)
    {
        return constants::gravity * time;
    }

    int main()
    {
        std::cout << instantVelocity(5) << '\n';

        return 0;

    }
    ```
    use:
    ```cpp
    #include <iostream>

    namespace constants
    {
        constexpr double gravity { 9.8 };
    }

    // This function can calculate the instant velocity for any gravity value (more useful)
    double instantVelocity(int time, double gravity)
    {
        return gravity * time;
    }

    int main()
    {
        std::cout << instantVelocity(5, constants::gravity) << '\n'; // pass our constant to the function as a parameter

        return 0;
    }
    ```

#### Summary:
- Non-constant global variables can lead to uncontrolled access, unintended side effects, reduced modularity, namespace pollution, difficulty in debugging, and concurrency issues.
- It is generally a good practice to avoid using non-constant global variables and instead use local variables, function parameters, return values, or encapsulate data within classes or structures.
- The initialization order problem of global variables can lead to undefined behavior when global variables in different translation units depend on each other.
- There are some scenarios where the use of non-constant global variables may be justified, but they should be used with caution and proper documentation.
- To protect yourself from issues related to global variable destruction, consider prefixing non-namespaced global variables, encapsulating global variables, and using arguments and return values to pass data between functions.


---

### S09 - 7.9 Inline functions and variables
When you are implementing a new program, you may want to split your code into multiple source files (translation units) for better organization and maintainability. Having multiple and clear function have several benefits:
- Easier to read and understand code.
- Easier to maintain and modify code.
- Easier to reuse code across different projects.

However, one downside of using functions is that every function call introduces a small **overhead** due to the function call mechanism (pushing arguments onto the stack, jumping to the function code, returning from the function, etc.). For small functions that are called frequently, this overhead can become significant.

For example:
```cpp
#include <iostream>

int min(int x, int y)
{
    return (x < y) ? x : y;
}

int main()
{
    std::cout << min(5, 6) << '\n';
    std::cout << min(3, 2) << '\n';
    return 0;
}
```
In this example, the `min` function is called twice in the `main` function. Each call incurs the overhead of a function call, which can add up if the function is called frequently or in a performance-critical section of code.

When a function is called, the CPU must store the address of the current instruction (so it knows where to return to after the function call), push the function arguments onto the stack, jump to the function code, execute the function, and then return to the original instruction. This process can take several CPU cycles, which can be significant for small functions that are called frequently. This is called `function call overhead`.

For big and complext functions, the function call overhead is negligible compared to the time it takes to execute the function itself. However, for small functions that are called frequently, the function call overhead can become a bottleneck in performance.

#### Inline expansion:
To mitigate the function call overhead for small functions, C++ provides a mechanism called `inline expansion`. When a function is declared as `inline`, the compiler is instructed to replace each call to the function with the actual code of the function itself, effectively eliminating the function call overhead. This process is known as `inlining`. For example:
```cpp
#include <iostream>

inline int min(int x, int y) // inline function
{
    return (x < y) ? x : y;
}

int main()
{
    std::cout << min(5, 6) << '\n'; // call to inline function
    std::cout << min(3, 2) << '\n'; // call to inline function
    return 0;
}
```
In this example, the `min` function is declared as `inline`. When the compiler encounters calls to `min`, it replaces them with the actual code of the function, eliminating the function call overhead, resulting in the following equivalent code:
```cpp
#include <iostream>

int main()
{
    std::cout << ((5 < 6) ? 5 : 6) << '\n'; // inlined code
    std::cout << ((3 < 2) ? 3 : 2) << '\n'; // inlined code
    return 0;
}
```

#### Performance of inline code:
Inlining small functions allows the compiler to optimize the resulting code more effectively, leading to constant folding and other optimizations that can improve performance. However, inlining large functions can lead to code bloat, which can negatively impact performance due to increased instruction cache misses. Therefore, it is generally recommended to use inline functions for small, frequently called functions, while avoiding inlining large functions.

> **Note:** Avoid using the `inline` keyword with large functions, as it can lead to code bloat and negatively impact performance.

#### When inline expansion occurs:
Every function falls into one of the following categories regarding inlining:
- Functions that may be expanded (most functions): their function calls may be replaced with the function code if and when it is beneficial to do so.
- Functions that cannot be expanded (e.g., function whose definition is in another translation unit): their function calls cannot be replaced with the function code.

#### The `inline` keyword, historically:
The `inline` keyword was introduced in C++ to suggest to the compiler that a function should be inlined. However, modern compilers are quite good at optimizing code and can decide whether to inline a function or not based on various factors, such as the size of the function and how frequently it is called. So, in modern C++, the `inline` keyword is no longer used to request the inlining, for these reasons:
- Using `inline` to request expansion is a form of premature optimization, which is generally discouraged.
- The `inline` keyword is just a hint to the compiler, which may choose to ignore it.
- The `inline` keyword is defined at the wrong set of granularity: it applies to the function as a whole, rather than to specific calls to the function.

Modern C++ compilers use sophisticated heuristics to determine when to inline functions, based on factors such as function size, call frequency, and optimization settings. Therefore, it is generally better to rely on the compiler's optimization capabilities rather than using the `inline` keyword.

> **Best practice:** Avoid using the `inline` keyword to request function inlining. Instead, focus on writing clear and maintainable code, and let the compiler handle optimization.

#### The `inline` keyword, modernly:
In previous chapters, we have seen that global variables and functions can have either `internal linkage` or `external linkage`. When a function or variable has `internal linkage`, it is accessible only within the translation unit (source file) where it is defined. When a function or variable has `external linkage`, it can be accessed from other translation units (source files) in the same program. In general, we mentioned that you should not implement functions (with external linkage) in header files, to avoid multiple definition errors during linking.

Here it comes the modern `inline` keyword usage. It basically tells the compiler that the *"multiple definitions are allowed"* for that function or variable across different translation units, and the linker will take care of merging them into a single definition. This allows you to define functions and variables in header files without causing multiple definition errors during linking. For example, you can define an inline function in a header file like this:
```cpp
// my_header.h
#ifndef MY_HEADER_H
#define MY_HEADER_H

inline int add(int a, int b) {
    return a + b;
}
#endif // MY_HEADER_H
```
Then, you can include this header file in multiple source files without causing multiple definition errors:
file1.cpp
```cpp
#include "my_header.h"

int main() {
    int result = add(3, 4);
    return 0;
}
```
file2.cpp
```cpp
#include "my_header.h"

int main() {
    int result = add(5, 6);
    return 0;
}
```
In this example, the `add` function is defined as `inline` in the header file `my_header.h`. When this header file is included in multiple source files (`file1.cpp` and `file2.cpp`), the linker will merge the multiple definitions of the `add` function into a single definition, avoiding multiple definition errors.

Inline functions have three primary requirements:
- The compiler must see the full definition of the inline function wherever it is called (the forward declaration is not enough). Only one such definition is needed per translation unit.
- The inline function must be defined before it is called.
- Every definition for an inline function (with external linkage) must be identical.

The linker will ensure that there is only one copy of the inline function in the final executable, even if it is defined in multiple translation units.

Here an example:

main.cpp
```cpp
#include <iostream>

double circumference(double radius); // forward declaration

inline double pi() { return 3.14159; }

int main()
{
    std::cout << pi() << '\n';
    std::cout << circumference(2.0) << '\n';

    return 0;
}
```
math.cpp
```cpp
inline double pi() { return 3.14159; }

double circumference(double radius)
{
    return 2.0 * pi() * radius;
}
```
In this example, the `pi` function is defined as `inline` in both `main.cpp` and `math.cpp`. The linker will merge the multiple definitions of the `pi` function into a single definition, avoiding multiple definition errors. If you remove the `inline` keyword from the `pi` function definition in either file, you will get an ODR violation error during linking.

Typically, `inline functions` are defined in header files, so they can be included in multiple source files without causing multiple definition errors. For example:

pi.h
```cpp
#ifndef PI_H
#define PI_H

inline double pi() { return 3.14159; }

#endif // PI_H
```
main.cpp
```cpp
#include "pi.h" // will include a copy of pi() here
#include <iostream>

double circumference(double radius); // forward declaration

int main()
{
    std::cout << pi() << '\n';
    std::cout << circumference(2.0) << '\n';

    return 0;
}
```
math.cpp
```cpp
#include "pi.h" // will include a copy of pi() here

double circumference(double radius)
{
    return 2.0 * pi() * radius;
}
```
In this example, the `pi` function is defined as `inline` in the header file `pi.h`. When this header file is included in both `main.cpp` and `math.cpp`, the linker will merge the multiple definitions of the `pi` function into a single definition, avoiding multiple definition errors.

> **Best practice:** Avoid the use of the `inline` keyword unless you are defining functions or variables in header files that need to be included in multiple source files.

This is particularly useful for **header-only-libraries**, where all the code is contained in header files, and there are no separate source files, giving the user the ability to include and use the library without needing to compile separate source files.

#### Why not make all functions inline and defined in header files?
Defining all functions as `inline` in header files is generally not a good practice for several reasons:
- **Compilation time:** Including large header files with many inline functions can significantly increase compilation times, as the compiler needs to process the same code multiple times for each translation unit that includes the header (when compiler encounter `#include` directive, it literally copy-paste the content of the header file in place).
- **Code bloat:** Inlining large functions can lead to code bloat, which can negatively impact performance due to increased instruction cache misses.
- **Encapsulation:** Defining functions in source files helps to encapsulate implementation details and separate interface from implementation, making the code easier to maintain and understand.
- **Debugging:** Debugging inline functions can be more challenging, as the debugger may have difficulty stepping through inlined code.

#### Inline variables (C++17):
In C++17, the `inline` keyword was extended to variables, allowing you to define `inline variables`. An `inline variable` is a variable that can be defined in multiple translation units without violating the one-definition rule (ODR). This is particularly useful for defining global constants in header files. For example:
```cpp
// constants.h
#ifndef CONSTANTS_H
#define CONSTANTS_H

inline const double pi = 3.14159; // inline variable

#endif // CONSTANTS_H
```
Then, you can include this header file in multiple source files without causing multiple definition errors.

#### Summary:
- `Inline expansion` is a mechanism that allows the compiler to replace function calls with the actual code of the function, eliminating function call overhead for small functions.
- The `inline` keyword was historically used to suggest to the compiler that a function should be inlined, but modern compilers can decide when to inline functions based on various factors.
- In modern C++, the `inline` keyword is primarily used to allow multiple definitions of functions and variables across different translation units, enabling their definition in header files without causing multiple definition errors during linking.
- Inline functions must have their full definition visible to the compiler wherever they are called, and every definition must be identical.
- The `inline` keyword should be used judiciously, primarily for small, frequently called functions, and to define functions and variables in header files.
- In C++17, the `inline` keyword was extended to variables, allowing the definition of inline variables in header files without violating the one-definition rule (ODR).


---

# S10 - 7.10 Sharing global constants across multiple files (using inline variables)
In some applications, certain symbolic constants need to be shared across multiple source files (translation units). For example, you can have some physics and mathematics constants that are used in different parts of your program. In this section we discuss the main ways to share global constants across multiple files.

#### Global constans as internal variables:
Prior to C++17, the following is the easiest and most common solution:
1. Create a header file (e.g., `constants.h`) to contain the constant definitions.
2. Define a namespace (e.g., `constants`) to encapsulate the constants in this header file.
3. Add all the constant definitions as `constexpr` variables inside the namespace in the header file.
4. Include the header file in any source file that needs to use the constants.

For example:

constants.h
```cpp
#ifndef CONSTANTS_H
#define CONSTANTS_H

// Define your own namespace to hold constants
namespace constants
{
    // Global constants have internal linkage by default
    constexpr double pi { 3.14159 };
    constexpr double avogadro { 6.0221413e23 };
    constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
    // ... other related constants
}
#endif
```
The use the scope resolution operator (`::`) to access the constants from the namespace in any source file:

main.cpp
```cpp
#include "constants.h" // include a copy of each constant in this file

#include <iostream>

int main()
{
    std::cout << "Enter a radius: ";
    double radius{};
    std::cin >> radius;

    std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n';

    return 0;
}
```
math.cpp
```cpp
#include "constants.h" // include a copy of each constant in this file

double circumference(double radius)
{
    return 2.0 * constants::pi * radius;
}
```

In this example, the `constants.h` header file defines a namespace `constants` that contains several `constexpr` variables representing global constants. Each source file that includes this header file gets its own copy of these constants, which have `internal linkage` by default. `constexpr` is important here, as it ensures that the constants are evaluated at compile time and do not occupy storage at runtime. Moreover, since they have internal linkage, there are no multiple definition issues during linking.

While this is simple (and fine for smaller programs), it is not good when you include the header file in many source files, because each source file will have its own copy of the constants, which can lead to increased binary size. This introduces two main challenges:
- Changing a single constant requires recompiling all source files that include the header file.
- If the constants are large in size and cannot be optimized away, this can lead to increased memory usage.

Advantages:
- Works prior to C++17.
- Simple to implement and understand.
- Can be used in constant expressions.

Downsides:
- Changing anything in the header file requires recompiling all source files that include it.
- Each translation unit including the header gets its own copy of the constants.

#### Global constants as external variables:
Another approach is to define the constants as `extern` variables in a header file and provide their definitions in a single source file. For example:

constants.h
```cpp
#include "constants.h"

namespace constants
{
    // We use extern to ensure these have external linkage
    extern constexpr double pi { 3.14159 };
    extern constexpr double avogadro { 6.0221413e23 };
    extern constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
}
```

constants.cpp
```cpp
#include "constants.h"

namespace constants
{
    // We use extern to ensure these have external linkage
    extern constexpr double pi { 3.14159 };
    extern constexpr double avogadro { 6.0221413e23 };
    extern constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
}
```

main.cpp
```cpp
#include "constants.h" // include all the forward declarations

#include <iostream>

int main()
{
    std::cout << "Enter a radius: ";
    double radius{};
    std::cin >> radius;

    std::cout << "The circumference is: " << 2 * radius * constants::pi << '\n';

    return 0;
}
```

In this way, the constants are defined only once in `constants.cpp`, and all other source files that include `constants.h` will refer to the same definitions. This approach avoids multiple definition issues during linking. The symbolic constants will get initialized only once, and all source files will share the same instance of each constant.

However, this approach has some downsides:
- Only the varaible definitions are constexpr, the forward declarations are not. This means that you cannot use these constants in constant expressions (e.g., array sizes, template parameters, etc.).
- For this reason, the compiler may not be able to optimize away the storage for these constants, leading to increased memory usage. For example, variable definitions in `constants.cpp` are not visible when the compiler compiles `main.cpp`, so it cannot optimize away the storage for `constants::pi` in `main.cpp`.

Advantages:
- Work prior to C++17.
- Only one copy of each constant exists in the program.
- Only requires recompilation of one source file when changing a constant.

Disadvantages:
- Forward declararions and variable definitions are in separate files, and must be kept in sync.
- Variables not usable in constant expressions.
- May lead to increased memory usage if the compiler cannot optimize away storage for the constants.

Given these downsides, this approach is generally not recommended for defining global constants. Instead, prefer defining your constants inside header files using `inline` variables (see next section).

#### Global constants as inline variables:
With the introduction of `inline variables` in C++17, a better approach to share global constants across multiple source files is to define them as `inline constexpr` variables in a header file. This allows you to define the constants in a single header file, and include that header file in multiple source files without causing multiple definition errors during linking. For example:

constants.h
```cpp
#ifndef CONSTANTS_H
#define CONSTANTS_H

// define your own namespace to hold constants
namespace constants
{
    inline constexpr double pi { 3.14159 }; // note: now inline constexpr
    inline constexpr double avogadro { 6.0221413e23 };
    inline constexpr double myGravity { 9.2 }; // m/s^2 -- gravity is light on this planet
    // ... other related constants
}
#endif
```
Then, you can include this header file in multiple source files without causing multiple definition errors, without instatiating the constants multiple times, and while still being able to use them in constant expressions.

> **Note:** This approach keeps the recompilation disadvantage (every file including the header must be recompiled when a constant changes), but it is generally acceptable for most applications.

Advantages:
- Can be used in constant expressions in any translation unit.
- Only one copy of each constant exists in the program.

Disadvantages:
- Only works with C++17 and later.
- Changing anything in the header file requires recompiling all source files that include it.

> **Best practice:** In modern C++ (C++17 and later), prefer defining global constants as `inline constexpr` variables in header files to share them across multiple source files.


---

### S11 - 7.11 Static local variables
The term `static` can be used in different contexts in C++, and its meaning varies depending on where it is applied. In previous chapters, we have seen how global variables have static storage duration, meaning they are allocated when the program starts and deallocated when the program ends. We have also seen how the `static` keyword can be used to specify internal linkage for global variables and functions.

In this section, we will focus on the use of `static` with local variables inside functions, known as `static local variables`.

#### Static local variables:
In previous chapters, we have seen that local variables have `automatic storage duration`, meaning that they are created at the point of definition, and destroyed when the block is exited. However, when a local variable is declared with the `static` keyword, it has `static storage duration`, meaning that it is created when the program starts and destroyed when the program ends, similar to global variables.

In this example, we will see the difference between static and automatic duration for local variables:
Automatic duration (default):
```cpp
#include <iostream>

void incrementAndPrint()
{
    int value{ 1 }; // automatic duration by default
    ++value;
    std::cout << value << '\n';
} // value is destroyed here

int main()
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();

    return 0;
}
```
prints:
```
2
2
2
```
In this example, the `value` variable is declared as a local variable inside the `incrementAndPrint` function. Since it has automatic storage duration, it is created each time the function is called and destroyed when the function exits. Therefore, each time the function is called, `value` is initialized to `1`, incremented to `2`, and printed.

Static duration:
```cpp
#include <iostream>

void incrementAndPrint()
{
    static int s_value{ 1 }; // static duration via static keyword.  This initializer is only executed once.
    ++s_value;
    std::cout << s_value << '\n';
} // s_value is not destroyed here, but becomes inaccessible because it goes out of scope

int main()
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();

    return 0;
}
```
prints:
```
2
3
4
```
In this example, the `s_value` variable is declared as a `static` local variable inside the `incrementAndPrint` function. Since it has static storage duration, it is created when the program starts and destroyed when the program ends. The initializer for `s_value` is only executed once, the first time the function is called. Therefore, each time the function is called, `s_value` retains its value from the previous call, is incremented, and printed.

> **Best practice:** Initialize your `static local variables`. Static local variables are only initialized the first time the code is executed, not on subsequent calls.

#### ID generator:
A common use case for static local variables is to create an ID generator that produces unique IDs each time it is called. For example:
```cpp
int generateID()
{
    static int s_itemID{ 0 };
    return s_itemID++; // makes copy of s_itemID, increments the real s_itemID, then returns the value in the copy
}
```
In this example, the `generateID` function uses a static local variable `s_itemID` to keep track of the last generated ID. Each time the function is called, it returns the current value of `s_itemID` and then increments it, ensuring that each call produces a unique ID.

#### Static local constants:
Static local variables can also be used to define constants that are local to a function. For example:
```cpp
#include <iostream>
void printCircleArea(double radius)
{
    static constexpr double pi{ 3.14159 }; // static local constant
    double area = pi * radius * radius;
    std::cout << "Area of circle with radius " << radius << " is " << area << '\n';
}

int main()
{
    printCircleArea(5.0);
    printCircleArea(10.0);

    return 0;
}
```
prints:
```
Area of circle with radius 5 is 78.5397
Area of circle with radius 10 is 314.159
```
In this example, the `pi` constant is defined as a static local variable inside the `printCircleArea` function. This allows the constant to be used within the function without polluting the global namespace.

#### Don't use static local variables to alter flow:
While static local variables can be useful in certain scenarios, they should not be used to alter the flow of a program in unexpected ways. For example, using a static local variable to control whether a function executes certain code can lead to confusion and make the code harder to understand. Instead, consider using function parameters or return values to control the flow of your program. For example:
```cpp
#include <iostream>

int getInteger()
{
	static bool s_isFirstCall{ true };

	if (s_isFirstCall)
	{
		std::cout << "Enter an integer: ";
		s_isFirstCall = false;
	}
	else
	{
		std::cout << "Enter another integer: ";
	}

	int i{};
	std::cin >> i;
	return i;
}

int main()
{
	int a{ getInteger() };
	int b{ getInteger() };

	std::cout << a << " + " << b << " = " << (a + b) << '\n';

	return 0;
}
```
prints:
```
Enter an integer: 5
Enter another integer: 10
5 + 10 = 15
```
In this example, the `getInteger` function uses a static local variable `s_isFirstCall` to determine whether to prompt the user for the first or subsequent integer input. While this works, it can lead to confusion, as the function's behavior changes based on its internal state. A better approach would be to use a function parameter to indicate whether it is the first call or not. For example:
```cpp
#include <iostream>

int getInteger(bool isFirstCall)
{
    if (isFirstCall)
    {
        std::cout << "Enter an integer: ";
    }
    else
    {
        std::cout << "Enter another integer: ";
    }

    int i{};
    std::cin >> i;
    return i;
}

int main()
{
    int a{ getInteger(true) };
    int b{ getInteger(false) };
    std::cout << a << " + " << b << " = " << (a + b) << '\n';

    return 0;
}
```
prints:
```
Enter an integer: 5
Enter another integer: 10
5 + 10 = 15
```
In this revised example, the `getInteger` function takes a boolean parameter `isFirstCall` to determine whether to prompt the user for the first or subsequent integer input. This makes the function's behavior explicit and easier to understand.

By avoiding the use of static local variables to control the flow of the program, the code becomes more maintainable and less prone to errors. It's generally a good practice to keep function behavior predictable and based on explicit inputs rather than hidden internal state.

#### Summary:
- `Static local variables` are local variables declared with the `static` keyword inside a function.
- They have `static storage duration`, meaning they are created when the program starts and destroyed when the program ends.
- Static local variables retain their value between function calls.
- Common use cases for static local variables include ID generators and local constants.
- Avoid using static local variables to alter the flow of a program in unexpected ways; prefer using function parameters or return values instead.


---

### S12 - 7.12 Scope, duration, and linkage summary
You can have a look at the final summary, or the original blog post.


---

### S13 - 7.13 Using declarations and using directives
You might have seen this in several tutorials and code examples:
```cpp
#include <iostream>

using namespace std;

int main()
{
    cout << "Hello world!\n";

    return 0;
}
```
If you saw that, please run away as fast as you can! Just kidding. But seriously, avoid using `using namespace std;` in your code. In the next we will explain why.

#### A short history lesson:
Back before C++ had support for namespaces, all the standard library functions and types were defined in the global namespace. This led to many naming conflicts, as different libraries could define functions or types with the same name. To solve this problem, C++ introduced namespaces in 1995, and all the functionality of the standard library was moved into the `std` namespace. 

This change broke older code because it relied on the global namespace for standard library functions and types, without using `std::` prefix. Also, writing `std::` everywhere was seen as cumbersome and verbose. To make the transition easier, the `using namespace std;` directive was introduced, allowing programmers to bring all the names from the `std` namespace into the global namespace, effectively restoring the old behavior. But first, let us introduce the concepts of **qualified and unqualified names**.

#### Qualified and unqualified names:
A **qualified name** is a name that includes an associated scope or namespace. For example, `std::cout` is a qualified name because it specifies that `cout` belongs to the `std` namespace. On the other hand, an **unqualified name** is a name that does not include any scope or namespace information. For example, `cout` is an unqualified name because it does not specify which namespace it belongs to.

```cpp
std::cout // identifier cout is qualified by namespace std
::foo // identifier foo is qualified by the global namespace
foo // identifier foo is unqualified
```

#### Using-declarations:
One way of reducing the verbosity of qualified names is to use a `using-declaration`. A `using-declaration` allows you to bring a **specific name** from a namespace into the current scope, so you can use it without the namespace prefix. For example:
```cpp
#include <iostream>

using std::cout; // using-declaration for cout
using std::endl; // using-declaration for endl

int main()
{
    cout << "Hello world!" << endl; // no need for std:: prefix

    return 0;
}
```
In this example, the `using-declaration` brings the `cout` and `endl` names from the `std` namespace into the current scope, allowing you to use them without the `std::` prefix.

The using-declaration is active from the point of declaration to the end of the enclosing scope. You can use multiple using-declarations to bring in multiple names from a namespace.

#### Using-directives:
Another way of reducing the verbosity of qualified names is to use a `using-directive`. A `using-directive` allows you to bring **all** the names from a namespace into the current scope, so you can use them without the namespace prefix. For example:
```cpp
#include <iostream>

using namespace std; // using-directive for the entire std namespace

int main()
{
    cout << "Hello world!" << endl; // no need for std:: prefix
    return 0;
}
```
In this example, the `using-directive` brings all the names from the `std` namespace into the current scope, allowing you to use them without the `std::` prefix.

Using directives are the solution that was provided for old pre-namespace codebases to work with the new namespace system. However, they can lead to naming conflicts and ambiguity, especially in larger codebases or when multiple namespaces are involved.

#### Probelm with using-directives (a.k.a why you should avoid "using namespace std;"):
In modern C++, using-drectives have few benefits compared to their downsides. Here are some reasons why you should avoid using `using namespace std;` in your code:
- Using-directives allow unqualified access to **all** names in the specified namespace, potentially leading to naming conflicts if different namespaces contain names that are the same.
- Using-directives do not prefer names from the namespaace over names from the global namespace, which can lead to ambiguity if a name exists in both the namespace and the global namespace.
- Using-directives can make it harder to understand where a name comes from, especially in larger codebases with multiple namespaces.
- Using-directives can lead to unexpected behavior if a name is added to the namespace in a future version of the library, potentially breaking existing code.

The bottom line is that using-directives can lead to code that leads to naming conflicts, ambiguity, and unexpected behavior.

Here is an example:
```cpp
#include <iostream>

namespace A
{
	int x { 10 };
}

namespace B
{
	int x{ 20 };
}

int main()
{
	using namespace A;
	using namespace B;

	std::cout << x << '\n';

	return 0;
}
```
This code will not compile because the compiler cannot determine which `x` to use, leading to an ambiguity error.

Here another more subtle example:
```cpp
#include <iostream> // imports the declaration of std::cout

int cout() // declares our own "cout" function
{
    return 5;
}

int main()
{
    using namespace std; // makes std::cout accessible as "cout"
    cout << "Hello, world!\n"; // uh oh!  Which cout do we want here?  The one in the std namespace or the one we defined above?

    return 0;
}
```
This code will not compile because the compiler cannot determine whether `cout` refers to the function we defined or the `std::cout` object, leading to an ambiguity error. If we had used `std::cout`, or using-declarations instead (`using std::cout;`), the code would have compiled without issues.

>**Note:** Even if using-directive does not cause a naming collision today, it may cause one in the future if new names are added to the namespace. For example, if a future version of the standard library adds a new function or variable named `x` to the `std` namespace, it could lead to naming conflicts in code that uses `using namespace std;`.

#### The scope of using-statements:
Both using-declarations and using-directives are active from the point of declaration to the end of the enclosing scope. This means that if you declare a using-declaration or using-directive inside a function, it will only be active within that function. For example:
```cpp
#include <iostream>

int main()
{
    {
        using std::cout; // using-declaration active in this block
        cout << "Hello from inner block!\n";
    }

    // cout is not accessible here without std:: prefix
    std::cout << "Hello from outer block!\n";

    return 0;
}
```
In this example, the `using-declaration` for `cout` is only active within the inner block. Outside of that block, `cout` is not accessible without the `std::` prefix.

#### Do not use using-directives in header files, or before an `#include` directive:
A good rule of thumb is to avoid using-directives where they might have an impact on other code, or vice-versa. For example, **avoid** using-directives in **header files**, as they can affect all source files that include the header file. Similarly, **avoid** using-directives before an `#include` directive, as they can affect the included header file and potentially lead to naming conflicts.

For example, if you placed a using-statement in the global namespace of a header file, then every source file that includes that header file would be affected by the using-statement, potentially leading to naming conflicts and ambiguity. 

Here an example of what **not** to do:

FooInt.h
```cpp
namespace Foo
{
    void print(int)
    {
        std::cout << "print(int)\n" << std::endl;
    }
}
```

FooDouble.h
```cpp
namespace Foo
{
    void print(double)
    {
        std::cout << "print(double)\n" << std::endl;
    }
}
```

main.cpp (good version)
```cpp
#include <iostream>

#include "FooDouble.h"
#include "FooInt.h"

using Foo::print; // print means Foo::print

int main()
{
    print(5);  // Calls Foo::print(int)
}
```
When run, this program calls `Foo::print(int)` and prints `print(int)`.

Now, let's change `main.cpp` slightly moving the using-statement before the `#include` directive:

main.cpp (bad version)
```cpp
#include <iostream>

#include "FooDouble.h"

using Foo::print; // we moved the using-statement here, before the #include directive
#include "FooInt.h"

int main()
{
    print(5);  // Calls Foo::print(double)
}
```
When run, this program now calls `Foo::print(double)` and prints `print(double)`. This happens because the using-statement was placed before the `#include` directive for `FooInt.h`, causing the compiler to resolve `print` to `Foo::print(double)` instead of `Foo::print(int)`.

> **Best practice:** Avoid using-directives in header files or before `#include` directives to prevent unintended naming conflicts and ambiguity.

#### Cancelling or replacing using-statements:
Once a using-declaration or using-directive is in effect, there is no way to "undo" it or "cancel" it.
```cpp
int main()
{
    using namespace Foo;

    // there's no way to cancel the "using namespace Foo" here!
    // there's also no way to replace "using namespace Foo" with a different using statement

    return 0;
} // using namespace Foo ends here
```
The only way to limit the scope of a using-declaration or using-directive is to place it inside a nested scope (e.g., a block or function). Once the scope ends, the using-declaration or using-directive is no longer in effect.
```cpp
int main()
{
    {
        using namespace Foo;
        // calls to Foo:: stuff here
    } // using namespace Foo expires

    {
        using namespace Goo;
        // calls to Goo:: stuff here
    } // using namespace Goo expires

    return 0;
}
```

#### Summary:
- A **qualified name** includes an associated scope or namespace (e.g., `std::cout`), while an **unqualified name** does not (e.g., `cout`).
- A `using-declaration` brings a **specific name** from a namespace into the current scope, allowing you to use it without the namespace prefix (e.g., `using std::cout;`).
- A `using-directive` brings **all names** from a namespace into the current scope, allowing you to use them without the namespace prefix (e.g., `using namespace std;`).
- Avoid using `using namespace std;` in your code due to potential naming conflicts, ambiguity, and unexpected behavior.
- Using-declarations and using-directives are active from the point of declaration to the end of the enclosing scope.
- Do not use using-directives in header files or before `#include` directives to prevent unintended naming conflicts and ambiguity.
- There is no way to "undo" or "cancel" a using-declaration or using-directive once it is in effect; the only way to limit their scope is to place them inside a nested scope.


---

### S14 - 7.14 Unnamed and inline namespaces (optional)
C++ provides two special types of namespaces: `unnamed namespaces` and `inline namespaces`. These namespaces have unique properties that can be useful in certain scenarios.

#### Unnamed (anonymous) namespaces:
An `unnamed namespace` (also known as an `anonymous namespace`) is a namespace that does not have a name. It is defined using the `namespace` keyword without a name, like this:
```cpp
namespace
{
    // declarations and definitions here
}
```
Entities declared inside an unnamed namespace have `internal linkage`, meaning they are only accessible within the same translation unit (source file). This is similar to declaring a global variable or function as `static`, but using an unnamed namespace is generally preferred in modern C++ (instead of multiple `static` declarations). For example:
```cpp
#include <iostream>

namespace
{
    void printMessage()
    {
        std::cout << "Hello from unnamed namespace!\n";
    }
}

int main()
{
    printMessage(); // accessible here

    return 0;
}
```
In this example, the `printMessage` function is defined inside an unnamed namespace. It can be accessed within the same translation unit, but not from other source files. 

Notice that all content declared inside the unnamed namespace is treated as if is part of the **parent namespace**, but with internal linkage (in this case the parent namespace is the global namespace).

> **Best practice (1):** Prefer unnamed namespaces over `static` declarations for defining entities with internal linkage in modern C++ (especially for multiple declarations).

> **Best practice (2):** Avoid using unnamed namespaces in header files.

#### Inline namespaces:
An `inline namespace` is a namespace that is declared with the `inline` keyword. It allows the contents of the namespace to be treated as if they are part of the parent namespace, while still maintaining their own namespace scope (i.e., they do not change the linkage, unlike unnamed namespaces). 

This can be useful for versioning libraries, where you want to provide multiple versions of a library's API while allowing users to access the latest version without specifying the version namespace explicitly.

For exmaple, suppose you havw this:
```cpp
#include <iostream>

void doSomething()
{
    std::cout << "v1\n";
}

int main()
{
    doSomething();

    return 0;
}
```
and you want to change the implementation of `doSomething` to a new version, while still allowing users to access the old version if needed. You can use an inline namespace for this:
```cpp
#include <iostream>

inline namespace V1 // declare an inline namespace named V1
{
    void doSomething()
    {
        std::cout << "V1\n";
    }
}

namespace V2 // declare a normal namespace named V2
{
    void doSomething()
    {
        std::cout << "V2\n";
    }
}

int main()
{
    V1::doSomething(); // calls the V1 version of doSomething()
    V2::doSomething(); // calls the V2 version of doSomething()

    doSomething(); // calls the inline version of doSomething() (which is V1)

    return 0;
}
```
prints:
```
V1
V2
V1
```
In this example, the `V1` namespace is declared as an inline namespace. This means that its contents are treated as if they are part of the parent namespace (the global namespace in this case). Therefore, when we call `doSomething()` without a namespace qualifier, it resolves to the `doSomething` function in the `V1` inline namespace, while we can still access the `V2` version by specifying the `V2` namespace.

Alternatively, if you want to push the new version `V2` as the default version, you can declare it as an inline namespace:
```cpp
#include <iostream>

namespace V1 // declare a normal namespace named V1
{
    void doSomething()
    {
        std::cout << "V1\n";
    }
}

inline namespace V2 // declare an inline namespace named V2
{
    void doSomething()
    {
        std::cout << "V2\n";
    }
}

int main()
{
    V1::doSomething(); // calls the V1 version of doSomething()
    V2::doSomething(); // calls the V2 version of doSomething()

    doSomething(); // calls the inline version of doSomething() (which is V2)

    return 0;
}
```
prints:
```
V1
V2
V2
```
In this example, the `V2` namespace is declared as an inline namespace. Therefore, when we call `doSomething()` without a namespace qualifier, it resolves to the `doSomething` function in the `V2` inline namespace.

This allows us to change the default version of the function without affecting the calls to the old version, providing a smooth transition for users of the library.

#### Mixing inline and unnamed namespaces (optional):
You can also combine the concepts of inline and unnamed namespaces. For example:
```cpp
#include <iostream>

namespace V1
{
    void doSomething()
    {
        std::cout << "V1 unnamed doSomething\n";
    }
}

inline namespace V2
{
    namespace
    {
        void doSomething()
        {
            std::cout << "V2 unnamed doSomething\n";
        }
    }
}

int main()
{
    V1::doSomething(); // calls the V1 version of doSomething()
    doSomething();     // calls the V2 unnamed version of doSomething()

    return 0;
}
```
prints:
```
V1 unnamed doSomething
V2 unnamed doSomething
```
In this example, we have an unnamed namespace inside an inline namespace `V2`. The `doSomething` function inside the unnamed namespace has internal linkage, while still being part of the `V2` inline namespace. This allows us to have a versioned function with internal linkage.

#### Summary:
- An `unnamed namespace` is a namespace without a name, and its contents have `internal linkage`, making them accessible only within the same translation unit.
- Prefer unnamed namespaces over `static` declarations for defining entities with internal linkage in modern C++.
- Avoid using unnamed namespaces in header files to prevent multiple definition issues.
- An `inline namespace` is a namespace declared with the `inline` keyword, allowing its contents to be treated as part of the parent namespace while maintaining their own scope.
- Inline namespaces are useful for versioning libraries, allowing users to access the latest version without specifying the version namespace explicitly.


---

### SX - 7.x Summary and quiz
You will find the solution of the quiz in the `exercises` folder. 

Enjoy life! :)


---

## 🧭 Summary

## 🧭 Summary

This chapter unified the concepts of **scope**, **duration**, and **linkage** into a coherent framework for reasoning about how and where data lives in a C++ program.

You learned that:
- **Scope** determines where an identifier can be accessed.
- **Duration** determines how long the identifier’s storage persists.
- **Linkage** determines whether identifiers in different files refer to the same entity.

By mastering these, you gain fine-grained control over program structure, visibility, and memory lifecycle.

You also explored the mechanisms C++ provides for managing these relationships — including **blocks**, **namespaces**, **static and extern linkage**, **inline variables**, and **static local variables** — all of which help build modular, maintainable, and efficient systems.

### 🧱 Core Concepts You Mastered:
- **Block and file scope** — controlling variable visibility.  
- **Automatic vs. static duration** — understanding variable lifetimes.  
- **Internal and external linkage** — controlling cross-file symbol visibility.  
- **Global vs. local variables** — avoiding unintentional side effects.  
- **Namespaces and scope resolution (`::`)** — organizing code and avoiding name conflicts.  
- **Variable shadowing and name hiding** — preventing ambiguity in nested scopes.  
- **Static local variables** — persistent state without globals.  
- **Inline functions and variables** — defining safe reusable code in headers.  
- **Unnamed and inline namespaces** — encapsulation and version management.  
- **Using-declarations/directives** — simplifying access to namespaces safely.

> **Takeaway:** Mastering scope, duration, and linkage gives you precise control over your program’s structure, memory, and modularity — essential for robust and scalable C++ development.