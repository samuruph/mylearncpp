# Chapter 13 - Compound Types: Enums and Structs

## 🧭 Overview
Chapter 13 introduces **program-defined types** in C++, focusing on enumerations, structs, aggregates, and class templates.  
You learn how to create custom data types, how to group related variables together, how enums improve code clarity and type safety, and how aggregate initialization simplifies working with plain data structures.  
These concepts form the foundation for understanding **classes**, the most important feature of C++ which will come next.

---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch13_first
./build/ch13_first
```

---

## 🎯 Learning Outcomes
By the end of this chapter, you understand:

- 🌐 What **program-defined types** are and why they matter.  
- 🔢 The difference between **unscoped** and **scoped enumerations**.  
- 🧱 How to define and use **structs** to group related data.  
- 📦 How **aggregate initialization** works, including C++20 designated initializers.  
- 🧰 How **default member initializers** simplify struct definitions.  
- 🧩 What **padding** is and how it affects struct size.  
- 🧬 Basics of **class templates** and **class template argument deduction (CTAD)**.  
- 📚 How type definitions interact with the **one-definition rule (ODR)**.

---

## Sections

### S01 — 13.1 Introduction to program-defined (user-defined) types
Fundamental types are defined by the programming language, so you can directly use them in your programs (simoply writing `int`, `char`, `double`, etc.).

This is also true fro compund types that are simple extentions of fundamental types, like functions, pointers, references, and arrays:
```cpp
void fcn(int) {}; // define a function of type void(int)
int* ptr; // define variable of compound type 'pointer to int'
int& ref { x }; // define variable of compound type 'reference to int' (initialized with x)
int arr[5]; // define an array of 5 integers of type int[5] (we'll cover this in a future chapter)
```
This works because C++ already knows about these compound types.

However, consider the case of type aliases, that allow us to define new names for existing typess (that must be defined before it can be used):
```cpp
#include <iostream>

using Length = int; // define a type alias with identifier 'Length'

int main()
{
    Length x { 5 }; // we can use 'length' here since we defined it above
    std::cout << x << '\n';

    return 0;
}
```
If we were omitting the definition of `Length` above, the compiler would complain that it doesn't know what `Length` is.

#### What are user-defined / program-defined types?
**User-defined types** (also called **program-defined types**) are new custom types that you can define and use in your programs.

C++ has two different categories of compund types that can be used to define program-defined types:
1. **Enumeratated types (`enum`)**, including unscoped and scoped enumerations
2. **Class types (`struct`, `class`, and `union`)**, including structs, classes, and unions

#### Defining program-defined types:
Like type aliases, program-defined types must be defined before they can be used, and its definition is called **type definition**.

Altough we did not cover what a `struct` is yet, here's an example of defining a program-defined type using `struct`:
```cpp
// Define a program-defined type named Fraction so the compiler understands what a Fraction is
// (we'll explain what a struct is and how to use them later in this chapter)
// This only defines what a Fraction type looks like, it doesn't create one
struct Fraction
{
	int numerator {};
	int denominator {};
};

// Now we can make use of our Fraction type
int main()
{
	Fraction f { 3, 4 }; // this actually instantiates a Fraction object named f

	return 0;
}
```
In this example, we defined a program-defined type named `Fraction` using `struct`, and then we used it to instantiate and initialize a `Fraction` object named `f`.

> **Note:** Do not forget to end your type definitions with a semicolon (`;`), as shown in the example above.

#### Naming program-defined types:
By convention, program-defined types are names starting with a capital letter and do not use a suffix (e.g., `Fraction`, `Color`, `Person`, etc., instead of `fraction`, `color_t`, `person_type`, etc.).

> **Best Practice:** Name program-defined types using **PascalCase** (also called **UpperCamelCase**), where each word starts with a capital letter and there are no underscores or other separators.

So you can instantiate a `Fraction` object like this:
```cpp
Fraction myFraction; // instantiate a Fraction object named myFraction
```

#### using program-defined types throughout a multi-file program:
Every code file that is using a program-defined type must be able to see its full type definition (a forward declaration is not enough), so that the compiler knows how much memory to allocate for objects of that type and how to access its members.

To propagate program-defined types across multiple code files, you typically define them in header files (`.h` or `.hpp`), and then include those header files in any code file that needs to use the type. For example:

Fraction.h:
```cpp
#ifndef FRACTION_H
#define FRACTION_H

// Define a new type named Fraction
// This only defines what a Fraction looks like, it doesn't create one
// Note that this is a full definition, not a forward declaration
struct Fraction
{
	int numerator {};
	int denominator {};
};

#endif
```
Fraction.cpp:
```cpp
#include "Fraction.h" // include our Fraction definition in this code file

// Now we can make use of our Fraction type
int main()
{
	Fraction f{ 3, 4 }; // this actually creates a Fraction object named f

	return 0;
}
```
In this way, any code file that includes `Fraction.h` can use the `Fraction` type.

#### Type definitions are partially exempt from the one-definition rule (ODR):
In a previous chapter, we said that each function and global variable must have exactly one definition across the entire program (the **one-definition rule**, or **ODR**). To use fthese functions or global variables in files ion which they are not defined, you can use forward declarations. This works because the compiler only needs to know the signature of functions and the type of global variables to compile code that uses them.

However, forward declaration do not work for program-defined types, because the compiler needs to know the full definition of a type to allocate memory for objects of that type and access their members. To allow for this, C++ partially exempts type definitions from the ODR: you can define the same program-defined type in multiple code files, as long as the definitions are identical. This is typically achieved by defining the type in a header file and including that header file in multiple code files.

#### Nomenclature: user-defined types vs program-defined types:
The term "user-defined type" is sometimes used in casual conversation, while "program-defined type" is more precise and formal. In this book, we will use both terms interchangeably.

In C++ language, **user-defined type** is any class type or enumerated type that ius defined by you, the standard library, or the implementation (e.g., `std::string` is a user-defined type defined by the standard library).

To avoid confusion, C++20 language specification introduced the term **program-defined type** to specifically refer to types defined by you in your program (i.e., excluding types defined by the standard library or implementation).

| Type         | Meaning                         | Example                |
|--------------|---------------------------------|------------------------|
| Fundamental  | Built-in types defined by C++   | `int`, `char`, `double`|
| Compound     | Built-in types composed of other types | `int*`, `int&`, `void()` |
| User-defined | A class type or enumerated type (defined by you, standard library, or implementation) | `std::string`, `Fraction` |
| Program-defined | A class type or enumerated type defined by you in your program | `Fraction`, `Color` |

#### Summary:
- Program-defined types are custom types that you define in your programs using enumerated types (`enum`) or class types (`struct`, `class`, and `union`).
- Program-defined types must be defined before they can be used, and their definitions are called type definitions.
- By convention, program-defined types are named using PascalCase.
- Every code file that uses a program-defined type must see its full type definition, typically by including a header file that contains the definition (e.g., `#include "Fraction.h"`).


---

### S02 — 13.2 Unscoped enumerations
C++ contains many useful fundamntal types and compund types, but sometimes you need to define your own custom types to better represent the data in your programs. For example, let's say you want to keep track the color of an apple in your program. You could use integer values like this:
```cpp
int main()
{
    int appleColor{ 0 }; // my apple is red
    int shirtColor{ 1 }; // my shirt is green

    return 0;
}
```
But it is not intuitive, and moreover magic numbers (like `0` and `1` here) are generally discouraged in programming because they make code harder to read and maintain.

We can get rid of the magig numbers by using symbolic constants:
```cpp
constexpr int red{ 0 };
constexpr int green{ 1 };
constexpr int blue{ 2 };

int main()
{
    int appleColor{ red };
    int shirtColor{ green };

    return 0;
}
```
While this is a bit better, it still has some problems. The user is still left to deduce that `appleColor` and `shirtColor` are supposed to hold specific values representing colors, and there is nothing preventing the user from assigning invalid values (e.g., `3`, `4`, etc.) to these variables.

We could make it a bit more clear by using type aliases:
```cpp
using Color = int; // define a type alias named Color

// The following color values should be used for a Color
constexpr Color red{ 0 };
constexpr Color green{ 1 };
constexpr Color blue{ 2 };

int main()
{
    Color appleColor{ red };
    Color shirtColor{ green };

    return 0;
}
```
This is better, but it still has the same problems as before: there is nothing preventing the user from assigning invalid values to `appleColor` and `shirtColor`, and the user still has to deduce that these variables are supposed to hold specific values representing colors (e.g., `Color appleColor{ 5 };` is still valid code).

Luckily, we can do better than this! Let's consider the `bool` type. This is good because only two values are allowed: `true` and `false`. If we try to assign any other value to a `bool` variable, the compiler will complain.

If we could define our own custom type that only allows specific values, that would be ideal! This is exactly what **enumerated types** (or **enums**) allow us to do.

#### Enumerations:
An **enumeration** (or **enum**) is a compund data type that consists of a set of named symbolic constants called **enumerators**. Each enumerator represents a distinct value of the enumeration type.

In C++, there are two kinds of enumerations: **unscoped enumerations** and **scoped enumerations**. In this section, we will cover unscoped enumerations.

Enumerations are program-defined types, so you need to define them before you can use them.

#### Unscoped enumerations:
An **unscoped enumeration** is defined using the `enum` keyword followed by the enumeration name and a list of enumerators enclosed in curly braces. For example, here is how to define an unscoped enumeration named `Color`:
```cpp
enum Color
{
    // Here are the enumerators
    // These symbolic constants define all the possible values this type can hold
    // Each enumerator is separated by a comma, not a semicolon
    red,
    green,
    blue, // trailing comma optional but recommended
}; // the enum definition must end with a semicolon
```
Once you have defined an unscoped enumeration, you can use it to declare variables of that type:
```cpp
int main()
{
    // Define a few variables of enumerated type Color
    Color apple { red };   // my apple is red
    Color shirt { green }; // my shirt is green
    Color cup { blue };    // my cup is blue

    Color socks { white }; // error: white is not an enumerator of Color
    Color hat { 2 };       // error: 2 is not an enumerator of Color

    return 0;
}
```
In this example, we defined an unscoped enumeration named `Color` with three enumerators: `red`, `green`, and `blue`. We then declared three variables of type `Color` and initialized them with valid enumerators. If we try to initialize a `Color` variable with an invalid enumerator (like `white`) or an integer value (like `2`), the compiler will complain.

To recap: an **enumerator** (or **enumerated type**) is the program-defined type itself (e.g., `Color`), while an **enumerator** is one of the named symbolic constants that define the possible values of that type (e.g., `red`, `green`, `blue`).

#### Naming enumerations and enumerators:
By convention, enumeration names use PascalCase (e.g., `Color`, `Direction`, `Status`), while enumerators do not have a specific naming convention, but they are often written in lowercase (e.g., `red`, `green`, `blue`).

#### Enumerated types are distinct types:
Each enumerated type you create is considered a **distinct type** by the compiler, even if two enumerated types have the same enumerators. For example:
```cpp
enum Color
{
    red,
    green,
    blue,
};
enum Direction
{
    red,
    green,
    blue,
};
int main()
{
    Color appleColor { red };       // OK
    Direction travelDirection { red }; // OK

    appleColor = travelDirection; // error: cannot assign Direction to Color

    return 0;
}
```
In this example, `Color` and `Direction` are two distinct types, even though they have the same enumerators. The compiler will not allow you to assign a `Direction` value to a `Color` variable.

#### Putting enumerations to use:
enuemrations are useful to imporve code readability and maintainability by providing meaningful names for sets of related values. They also help prevent invalid values from being assigned to variables of the enumerated type. For example, commonly used enumerations include:
```cpp
enum DaysOfWeek
{
    sunday,
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
};

enum CardinalDirections
{
    north,
    east,
    south,
    west,
};

enum CardSuits
{
    clubs,
    diamonds,
    hearts,
    spades,
};
```

Another example related to error codes, instead of using magic numbers:
```cpp
int readFileContents()
{
    if (!openFile())
        return -1;
    if (!readFile())
        return -2;
    if (!parseFile())
        return -3;

    return 0; // success
}
```
We can improve this by using an enumeration:
```cpp
enum FileReadResult
{
    readResultSuccess,
    readResultErrorFileOpen,
    readResultErrorFileRead,
    readResultErrorFileParse,
};

FileReadResult readFileContents()
{
    if (!openFile())
        return readResultErrorFileOpen;
    if (!readFile())
        return readResultErrorFileRead;
    if (!parseFile())
        return readResultErrorFileParse;

    return readResultSuccess;
}
```
So that the caller can handle the result more easily:
```cpp
if (readFileContents() == readResultSuccess)
{
    // do something
}
else
{
    // print error message
}
```

Enumerated types can also be useful in games:
```cpp
enum ItemType
{
	sword,
	torch,
	potion,
};

int main()
{
	ItemType holding{ torch };

	return 0;
}
```

Or can be used in function parameters, when the user needs to make a choice between a set of options:
```cpp
enum SortOrder
{
    alphabetical,
    alphabeticalReverse,
    numerical,
};

void sortData(SortOrder order)
{
    switch (order)
    {
        case alphabetical:
            // sort data in forwards alphabetical order
            break;
        case alphabeticalReverse:
            // sort data in backwards alphabetical order
            break;
        case numerical:
            // sort data numerically
            break;
    }
}

int main()
{
    sortData(alphabetical); // sort data in forwards alphabetical order

    return 0;
}
```

Since enumerations are small and inexpensive to copy, they are often passed (and returned) **by value**.

In a previous chapter we have seen bit flags. We can use enumerations to define bit flags as well:
```cpp
#include <bitset>
#include <iostream>

namespace Flags
{
    enum State
    {
        isHungry,
        isSad,
        isMad,
        isHappy,
        isLaughing,
        isAsleep,
        isDead,
        isCrying,
    };
}

int main()
{
    std::bitset<8> me{};
    me.set(Flags::isHappy);
    me.set(Flags::isLaughing);

    std::cout << std::boolalpha; // print bool as true/false

    // Query a few states (we use the any() function to see if any bits remain set)
    std::cout << "I am happy? " << me.test(Flags::isHappy) << '\n';
    std::cout << "I am laughing? " << me.test(Flags::isLaughing) << '\n';

    return 0;
}
```
If you are wondering how you can pass an enumerator to a function that expects an integer, just remember that enumerators are implicitly convertible to **integers** (but not the other way around). We will cover this in the next section.

#### The scope of unscoped enumerations:
Unscoped enumerations are named such because their enumerators are placed into the same scope as the enumeration definition iself (instead of creating a new scope region like a namespace does). For example:
```cpp
enum Color // this enum is defined in the global namespace
{
    red, // so red is put into the global namespace
    green,
    blue,
};

int main()
{
    Color apple { red }; // my apple is red

    return 0;
}
```
In this case, the enumerators `red`, `green`, and `blue` are placed in the global namespace, so you can use them directly without any qualification.

This could pollute the global namespace if you define many enumerations with common enumerator names, increasing the chance of name collisions. One consequence is that an enumerator name cannot be used in multiple enumerations within the same scope:
```cpp
enum Color
{
    red,
    green,
    blue, // blue is put into the global namespace
};

enum Feeling
{
    happy,
    tired,
    blue, // error: naming collision with the above blue
};

int main()
{
    Color apple { red }; // my apple is red
    Feeling me { happy }; // I'm happy right now (even though my program doesn't compile)

    return 0;
}
```

Unscoped enumerations also provide a named scope region for their enumerators (much like namespaces do). This means that you can qualify enumerators with the enumeration name to avoid naming collisions:
```cpp
enum Color
{
    red,
    green,
    blue, // blue is put into the global namespace
};

int main()
{
    Color apple { red }; // okay, accessing enumerator from global namespace
    Color raspberry { Color::red }; // also okay, accessing enumerator from scope of Color

    return 0;
}
```
Most often, unscoped enumerators are used without qualification, but you can use qualification when needed to avoid naming collisions.

#### Avoiding enumerator name collisions:
There are quite a few common ways to prevent unscoped enumerator naming collisions.

One way is to prefix each enumerator with the name of the enumeration itself:
```cpp
enum Color
{
    color_red,
    color_blue,
    color_green,
};

enum Feeling
{
    feeling_happy,
    feeling_tired,
    feeling_blue, // no longer has a naming collision with color_blue
};

int main()
{
    Color paint { color_blue };
    Feeling me { feeling_blue };

    return 0;
}
```
This still polluted the global namespace, but at least it avoids naming collisions.

A better option is to put the enumerated type inside something that creates a new scope region, like a namespace or a class/struct. For example, using a namespace:
```cpp
namespace Color
{
    // The names Color, red, blue, and green are defined inside namespace Color
    enum Color
    {
        red,
        green,
        blue,
    };
}

namespace Feeling
{
    enum Feeling
    {
        happy,
        tired,
        blue, // Feeling::blue doesn't collide with Color::blue
    };
}

int main()
{
    Color::Color paint{ Color::blue };
    Feeling::Feeling me{ Feeling::blue };

    return 0;
}
```
This means we now have to prefix our enumeration and enumerator names with the name of the scoped region.

Classes also provide a scope region, and it’s common to put enumerated types related to a class inside the scope region of the class. 

Another option, if an enumeration is only used inside the body of a single function, is to define it inside that function. This way, the enumerators are only visible within that function, avoiding any naming collisions with other parts of the program.

#### Comparing against enumerators:
We can use the equality operators (`operator==` and `operator!=`) to compare variables of enumerated types against enumerators:
```cpp
#include <iostream>

enum Color
{
    red,
    green,
    blue,
};

int main()
{
    Color shirt{ blue };

    if (shirt == blue) // if the shirt is blue
        std::cout << "Your shirt is blue!";
    else
        std::cout << "Your shirt is not blue!";

    return 0;
}
```

#### Summary:
- **Unscoped enumerations** are program-defined types that consist of a set of named symbolic constants called **enumerators**.
- Unscoped enumerations are defined using the `enum` keyword followed by the enumeration name and a list of enumerators enclosed in curly braces.
- Each enumerated type is considered a **distinct type** by the compiler, even if two enumerated types have the same enumerators.
- Unscoped enumerators are placed into the same scope as the enumeration definition itself (that's why they are named "unscoped").
- Unscoped enumerators can be qualified with the enumeration name to avoid naming collisions.


---

### S03 — 13.3 Unscoped enumerator integral conversions
In the previous section, we said that enumerators are symbolic constants that define the possible values of an enumerated type. But what are their actual values?

By default, the underlying type of an unscoped enumeration is an implementation-defined integral type that can represent all the enumerator values. The compiler automatically assigns integer values to the enumerators, starting from `0` for the first enumerator and incrementing by `1` for each subsequent enumerator. For example:
```cpp
enum Color
{
    black,   // 0
    red,     // 1
    blue,    // 2
    green,   // 3
    white,   // 4
    cyan,    // 5
    yellow,  // 6
    magenta, // 7
};

int main()
{
    Color shirt{ blue }; // shirt actually stores integral value 2

    return 0;
}
```
In this example, the enumerators `black`, `red`, `blue`, etc., are assigned integer values starting from `0`, until `7` for `magenta`.

It is also possible to explicitly specify the integer values of enumerators:
```cpp
enum Animal
{
    cat = -3,    // values can be negative
    dog,         // -2
    pig,         // -1
    horse = 5,
    giraffe = 5, // shares same value as horse
    chicken,     // 6
};
```
In here, we explicitly set the value of `cat` to `-3`, and the subsequent enumerators (`dog` and `pig`) are automatically assigned values of `-2` and `-1`, respectively. We also set `horse` to `5`, and `giraffe` shares the same value as `horse` (they are basically interchangeable). Finally, `chicken` is automatically assigned a value of `6`.

> **Best Practice:** Avoid assigning explicit values to your enumerators unless you have a specific reason to do so. Let the compiler automatically assign values to avoid potential errors and improve code readability.

#### Value-initializing an enumeration:
When you zero-initialize an enumeration variable (e.g., `Color myColor{};`), it is initialized to the value of the first enumerator (which is `0` by default). For example:
```cpp
#include <iostream>

enum Animal
{
    cat = -3,    // -3
    dog,         // -2
    pig,         // -1
    // note: no enumerator with value 0 in this list
    horse = 5,   // 5
    giraffe = 5, // 5
    chicken,     // 6
};

int main()
{
    Animal a {}; // value-initialization zero-initializes a to value 0
    std::cout << a; // prints 0

    return 0;
}
```
In this example, since there is no enumerator with a value of `0`, the variable `a` is initialized to `0`, which does not correspond to any valid enumerator of the `Animal` enumeration.

This has two main semnatic implications:
1. If there is an enumerator with value `0`, value-initializing an enumeration variable will initialize it to that enumerator. So, it is a good idea to make the `0` enumerator represent a default or "none" value. For example, avoid something like this:
    ```cpp
    enum UniverseResult
    {
        destroyUniverse, // default value (0)
        saveUniverse
    };
    ```
2. If there is no enumerator with value `0`, value-initializing an enumeration variable will initialize it to an invalid value (i.e., a value that does not correspond to any enumerator). In this case it is a good practice to explicitly define a `none` or `invalid` enumerator with value `0`. For example:
    ```cpp
    enum UniverseResult
    {
        none = 0,        // default value (0)
        destroyUniverse,
        saveUniverse
    };
    ```

#### Unscoped enumerations will implicitly convert to integral values:
Even though enumerations store integral values, they are not considered integral types by the compiler, but they are considered compund types. However, unscoped enumerations will be implicitly converted to their underlying integral type when needed. Since enumerators are **compile-time** constants, this is a constexpr conversion that happens at compile time. For example:
```cpp
#include <iostream>

enum Color
{
    black, // assigned 0
    red, // assigned 1
    blue, // assigned 2
    green, // assigned 3
    white, // assigned 4
    cyan, // assigned 5
    yellow, // assigned 6
    magenta, // assigned 7
};

int main()
{
    Color shirt{ blue };

    std::cout << "Your shirt is " << shirt << '\n'; // what does this do?

    return 0;
}
```
will print:
```
Your shirt is 2
```
because the `shirt` variable of type `Color` is implicitly converted to its underlying integral value (`2` for `blue`) when passed to `std::cout`. In practice, the compiler will first try to find an appropriate overload of `operator<<` that accepts a `Color` type, but since there is none, it will convert `shirt` to its underlying integral type and call the overload that accepts an integer.

#### Enumeration size and underlying type (base):
We said that the underlying type of an unscoped enumeration is an implementation-defined integral type that can represent all the enumerator values. But which integral type is used?

The specific integral type used is called the **underlying type** (or **base type**) of the enumeration. For unscoped enumerations, the C++ standard does not specify which integral type should be used as the underlying type, leaving it up to the implementation (i.e., the compiler). However, the underlying type must be able to represent all the enumerator values.

Most compilers will use `int` as the underlying type for unscoped enumerations, unless the enumerator values require a larger type (e.g., if you have very large enumerator values).

You can additionally specify the underlying type of an unscoped enumeration explicitly by using a colon (`:`) followed by the desired integral type after the enumeration name. For example:
```cpp
#include <cstdint>  // for std::int8_t

// Use an 8-bit integer as the enum underlying type
enum Color : std::int8_t
{
    black,
    red,
    blue,
};
```

And you can check the size of an enumeration using the `sizeof` operator:
```cpp
#include <iostream>

int main()
{
    Color c{ black };
    std::cout << sizeof(c) << '\n'; // prints 1 (byte)

    return 0;
}
```

> **Best Practice:** Specify the base type of an enumeration only when necessary. Most of the time, you can let the compiler choose the underlying type automatically.

#### Integer to unscoped enumerator conversion:
While unscoped enumerations can be implicitly converted to their underlying integral type, the reverse is not true: integral values cannot be implicitly converted to unscoped enumerations. For example:
```cpp
enum Pet // no specified base
{
    cat, // assigned 0
    dog, // assigned 1
    pig, // assigned 2
    whale, // assigned 3
};

int main()
{
    Pet pet { 2 }; // compile error: integer value 2 won't implicitly convert to a Pet
    pet = 3;       // compile error: integer value 3 won't implicitly convert to a Pet

    return 0;
}
```
This is because allowing implicit conversion from integers to enumerations could lead to invalid values being assigned to enumeration variables.

However, there are two ways to work around this restriction:
1. You can use a `static_cast` to explicitly convert an integer to an enumeration type:
    ```cpp
    enum Pet // no specified base
    {
        cat, // assigned 0
        dog, // assigned 1
        pig, // assigned 2
        whale, // assigned 3
    };

    int main()
    {
        Pet pet { static_cast<Pet>(2) }; // convert integer 2 to a Pet
        pet = static_cast<Pet>(3);       // our pig evolved into a whale!

        return 0;
    }
    ```
    However, be careful when using `static_cast` to convert integers to enumerations, as it can lead to invalid enumeration values if the integer is not inside the range of valid enumerators.
2. As of C++17, if an unscoped enumeration has an explicitely specified base, then the compiler will allow you to list initialize an unscoped enumeration using an integral value of the same type as the base:
    ```cpp
    enum Pet: int // we've specified a base
    {
        cat, // assigned 0
        dog, // assigned 1
        pig, // assigned 2
        whale, // assigned 3
    };

    int main()
    {
        Pet pet1 { 2 }; // ok: can brace (list) initialize unscoped enumeration with specified base with integer (C++17)
        Pet pet2 (2);   // compile error: cannot direct initialize with integer
        Pet pet3 = 2;   // compile error: cannot copy initialize with integer

        pet1 = 3;       // compile error: cannot assign with integer

        return 0;
    }
    ```

#### Summary:
- By default, unscoped enumerations have an implementation-defined underlying integral type that can represent all the enumerator values.
- The compiler automatically assigns integer values to enumerators, starting from `0` and incrementing by `1` for each subsequent enumerator, unless explicit values are provided.
- Unscoped enumerations can be implicitly converted to their underlying integral type when needed.
- Integral values cannot be implicitly converted to unscoped enumerations, but you can use `static_cast` to explicitly convert an integer to an enumeration type.
- As of C++17, if an unscoped enumeration has an explicitly specified base type, you can list initialize it with an integer of the same type as the base.


---

### S04 — 13.4 Converting an enumerator to and from a string
In the previous section, we showed this example:
```cpp
#include <iostream>

enum Color
{
    black, // 0
    red,   // 1
    blue,  // 2
};

int main()
{
    Color shirt{ blue };

    std::cout << "Your shirt is " << shirt << '\n';

    return 0;
}
```
Since `operator<<` is not defined for `Color`, the compiler implicitly converts `shirt` to its underlying integral value (`2` for `blue`) when passing it to `std::cout`, resulting in the output:
```
Your shirt is 2
```

Most of the time, printing the integral value of an enumerator is not very useful. Instead, we would like to print the name of the enumerator itself (e.g., `blue` instead of `2`). Unfortunately, C++ does not provide a built-in way to convert enumerators to strings or vice versa. However, we can implement this functionality ourselves using various techniques.

#### Getting the name of an enumerator:
The typical way to get the name of an enumerator as a string is to write a function that takes an enumerator as input and returns the corresponding string. There are two common ays to do this: using a `switch` statement or using an array of strings.

First, let's see how to do this using a `switch` statement:
```cpp
#include <iostream>
#include <string_view>

enum Color
{
    black,
    red,
    blue,
};

constexpr std::string_view getColorName(Color color)
{
    switch (color)
    {
    case black: return "black";
    case red:   return "red";
    case blue:  return "blue";
    default:    return "???";
    }
}

int main()
{
    constexpr Color shirt{ blue };

    std::cout << "Your shirt is " << getColorName(shirt) << '\n';

    return 0;
}
```
This program will output:
```
Your shirt is blue
```
In this example, we defined a `getColorName` function that uses a `switch` statement to return the name of the enumerator as a string.

> **Note:** Because C-style string literals exists for the entire duration of the program, we can return a `std::string_view` pointing to a string literal safely.

While this lets us get the name of an enumerator, it has some drawbacks:
- The `switch` statement can become quite long and unwieldy if the enumeration has many enumerators.
- If you add or remove enumerators from the enumeration, you need to remember to update the `getColorName` function accordingly.
- You need to call the function every time you want to get the name of an enumerator (`getColorName(shirt)`).

So, the second way to implement this functionality is to use an array (we will cover this in a later chapter) of strings:
```cpp
#include <iostream>
#include <string_view>

enum Color
{
    black,
    red,
    blue,
    colorCount // always keep this as the last enumerator
};

constexpr std::string_view colorNames[] =
{
    "black",
    "red",
    "blue",
};

int main()
{
    constexpr Color shirt{ blue };

    std::cout << "Your shirt is " << colorNames[shirt] << '\n';

    return 0;
}
```
This program will output:
```
Your shirt is blue
```
In this example, we defined an array of strings named `colorNames`, where each string corresponds to an enumerator in the `Color` enumeration. We also added a `colorCount` enumerator to keep track of the number of colors (this is a common technique). We can then use the enumerator value as an index into the `colorNames` array to get the corresponding string.

#### Unscoped enumerator input:
Now, let's focus on an input case:
```cpp
#include <iostream>

enum Pet
{
    cat,   // 0
    dog,   // 1
    pig,   // 2
    whale, // 3
};

int main()
{
    Pet pet { pig };
    std::cin >> pet; // compile error: std::cin doesn't know how to input a Pet

    return 0;
}
```
In this example, we try to read a `Pet` value from standard input using `std::cin`, but the compiler complains because `operator>>` is not defined for `Pet`.

One simple way to work around this, as we have seen in the previous section, is to read an integer value from input and then convert it to a `Pet` using `static_cast`:
```cpp
#include <iostream>
#include <string_view>

enum Pet
{
    cat,   // 0
    dog,   // 1
    pig,   // 2
    whale, // 3
};

constexpr std::string_view getPetName(Pet pet)
{
    switch (pet)
    {
    case cat:   return "cat";
    case dog:   return "dog";
    case pig:   return "pig";
    case whale: return "whale";
    default:    return "???";
    }
}

int main()
{
    std::cout << "Enter a pet (0=cat, 1=dog, 2=pig, 3=whale): ";

    int input{};
    std::cin >> input; // input an integer

    if (input < 0 || input > 3)
        std::cout << "You entered an invalid pet\n";
    else
    {
        Pet pet{ static_cast<Pet>(input) }; // static_cast our integer to a Pet
        std::cout << "You entered: " << getPetName(pet) << '\n';
    }

    return 0;
}
```
This program will prompt the user to enter a pet by its corresponding integer value, read the input as an integer, and then convert it to a `Pet` using `static_cast`. It also checks if the input is valid before performing the conversion.

While this works, it is a bit clunky, as the user has to remember the integer values corresponding to each enumerator. It would be nicer if the user could enter the name of the pet directly (e.g., "cat", "dog", etc.).

#### Getting an enumerator from a string:
Instead of inputting a number, we could input a string and then convert that string to the corresponding enumerator. easy to say, but we would need to first solve some challenges:
- We cannot switch on a string, so we will need to use something else to match the string user passed in. The simplest way is to use a series of `if`/`else if` statements).
- We need to handle invalid input (i.e., strings that do not correspond to any enumerator). One option could be to add an enumerator to represent an invalid value (e.g., `invalidPet`), or we could use `std::optional` (covered in a previous chapter) to indicate whether the conversion was successful or not.

For example:
```cpp
#include <iostream>
#include <optional> // for std::optional
#include <string>
#include <string_view>

enum Pet
{
    cat,   // 0
    dog,   // 1
    pig,   // 2
    whale, // 3
};

constexpr std::string_view getPetName(Pet pet)
{
    switch (pet)
    {
    case cat:   return "cat";
    case dog:   return "dog";
    case pig:   return "pig";
    case whale: return "whale";
    default:    return "???";
    }
}

constexpr std::optional<Pet> getPetFromString(std::string_view sv)
{
    // We can only switch on an integral value (or enum), not a string
    // so we have to use if-statements here
    if (sv == "cat")   return cat;
    if (sv == "dog")   return dog;
    if (sv == "pig")   return pig;
    if (sv == "whale") return whale;

    return {};
}

int main()
{
    std::cout << "Enter a pet: cat, dog, pig, or whale: ";
    std::string s{};
    std::cin >> s;

    std::optional<Pet> pet { getPetFromString(s) };

    if (!pet)
        std::cout << "You entered an invalid pet\n";
    else
        std::cout << "You entered: " << getPetName(*pet) << '\n';

    return 0;
}
```
In this example, we defined a `getPetFromString` function that takes a string as input and returns an `std::optional<Pet>`. If the input string matches one of the enumerator names, it returns the corresponding `Pet` value; otherwise, it returns an empty `std::optional`, indicating that the conversion was unsuccessful.

Similar to the output case, it would be better to just do `std::cin >> pet;` directly, and we will cover this in the next section.

#### Summary:
- C++ does not provide built-in functionality to convert enumerators to strings or vice versa, but you can implement this functionality yourself using functions.
- To get the name of an enumerator as a string, you can use a `switch` statement or an array of strings.
- To convert a string to an enumerator, you can use a series of `if`/`else if` statements and return an `std::optional` to indicate whether the conversion was successful or not.


---

### S05 — 13.5 Introduction to overloading the I/O operators
In the previous section, we saw how to convert enumerators to strings and vice versa using custom functions. However, it would be more convenient if we could use the standard input/output operators (`operator<<` and `operator>>`) directly with our enumerated types. This way, we could write code like this:
```cpp
#include <iostream>

enum Color
{
    black,
    red,
    blue,
};

int main()
{
    Color shirt{ blue };

    std::cout << "Your shirt is " << shirt << '\n'; // print the color name

    std::cout << "Enter a color (black, red, blue): ";
    std::cin >> shirt; // read the color name

    return 0;
}
```

To achieve this, we need to overload the input/output operators for our enumerated types. Overloading these operators allows us to define custom behavior for how our enumerated types are printed to output streams and read from input streams.

#### Introduction to operator overloading:
In a previous chapter, we introduced function overloading, which allows us to define multiple functions with the same name so long as each function has unique function prototypes. With these, we were able to create variations of functions that worked with different types.

Similarly, C++ also supports **operator overloading**, which allows us to define custom behavior for operators (like `+`, `-`, `<<`, `>>`, etc.) when they are used with program-defined types (like classes, structs, and enumerations).

This process is fairly straightforward:
- Define a function using the name of the operator as the function's name (e.g., `operator<<` for the output operator).
- Add a parameter of the appropriate type for each operand (in left-to-right order). One of these parameters must be user-defined type (e.g., class type or an enumerated type).
- Set the return type to the appropriate type.
- Use a return statement to return the result of the operation.

When the compiler encounters the use of an operator in an expression and one of more of the operand is a user-defined type, the compiler will check to see if there is an overloaded version of that operator that matches the operand types. If a matching overloaded operator is found, the compiler will use that function to perform the operation. 

For example, given the expression `x + y`, the compiler will use function overload resolution to see if there is an overloaded `operator+` function that matches the types of `x` and `y`. if an non-ambiguous match is found, the compiler will call that function to perform the addition.

#### overloading `operator<<` to print an enumerator:
Before we start, let's recap the `operator<<` for output streams. Consider a simple expression like `std::cout << 5;`. Here, `std::cout` is an object of type `std::ostream` (which is a user-defined type in standard library), and `5` is an integer literal of type `int` (which is a built-in type).

When this epxression is evaluated, the compiler will look for an overloaded `operator<<` function that matches the types of the operands (`std::ostream` and `int`). It will find such a function (defined in the I/O library) and call it. Inside that function, `std::cout` is used to output the integer value `5` to the standard output stream. Finally, the `operator<<` function return its left-operand (in this case `std::cout`), allowing for chaining of output operations (e.g., `std::cout << 5 << 10;`).

With this in mind, we can overload `operator<<` for our enumerated type. Here is an example:
```cpp
#include <iostream>
#include <string_view>

enum Color
{
	black,
	red,
	blue,
};

constexpr std::string_view getColorName(Color color)
{
    switch (color)
    {
    case black: return "black";
    case red:   return "red";
    case blue:  return "blue";
    default:    return "???";
    }
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout, std::cerr, etc...
// The return type and parameter type are references (to prevent copies from being made)
std::ostream& operator<<(std::ostream& out, Color color)
{
    out << getColorName(color); // print our color's name to whatever output stream out
    return out;                 // operator<< conventionally returns its left operand

    // The above can be condensed to the following single line:
    // return out << getColorName(color)
}

int main()
{
	Color shirt{ blue };
	std::cout << "Your shirt is " << shirt << '\n'; // it works!

	return 0;
}
```
This will output:
```
Your shirt is blue
```

In this example, we defined an overloaded `operator<<` (same name as the operator we want to overload) that takes two parameters: a reference to an `std::ostream` object (the output stream, that will be match with the left operand) and a `Color` enumerator (the value to be printed, that will be matched with the right operand). 
We use pass by non-const reference here because we do not want to make a copy of a `std::ostream` object (which could be expensive), and we want to modify the original stream (by writing to it).

Inside the function, we use the `getColorName` function to get the name of the color as a string and print it to the output stream using `out << getColorName(color);`. Finally, we return the output stream `out` to allow for chaining of output operations, as is the convention for `operator<<`.

Putting all together, when we call `std::cout << shirt;`, the compiler will use our overloaded `operator<<` function to print the name of the color instead of its underlying integral value, since `shirt` is of type `Color`. Our overloaded function is called with `std::cout` as the first parameter (`out`) and `shirt` as the second parameter (`color`).

#### Overloading `operator>>` to input an enumerator:
Similar to `operator<<`, we can overload `operator>>` to read an enumerator from an input stream. Here is an example:
```cpp
#include <iostream>
#include <limits>
#include <optional>
#include <string>
#include <string_view>

enum Pet
{
    cat,   // 0
    dog,   // 1
    pig,   // 2
    whale, // 3
};

constexpr std::string_view getPetName(Pet pet)
{
    switch (pet)
    {
    case cat:   return "cat";
    case dog:   return "dog";
    case pig:   return "pig";
    case whale: return "whale";
    default:    return "???";
    }
}

constexpr std::optional<Pet> getPetFromString(std::string_view sv)
{
    if (sv == "cat")   return cat;
    if (sv == "dog")   return dog;
    if (sv == "pig")   return pig;
    if (sv == "whale") return whale;

    return {};
}

// pet is an in/out parameter
std::istream& operator>>(std::istream& in, Pet& pet)
{
    std::string s{};
    in >> s; // get input string from user

    std::optional<Pet> match { getPetFromString(s) };
    if (match) // if we found a match
    {
        pet = *match; // dereference std::optional to get matching enumerator
        return in;
    }

    // We didn't find a match, so input must have been invalid
    // so we will set input stream to fail state
    in.setstate(std::ios_base::failbit);

    // On an extraction failure, operator>> zero-initializes fundamental types
    // Uncomment the following line to make this operator do the same thing
    // pet = {};

    return in;
}

int main()
{
    std::cout << "Enter a pet: cat, dog, pig, or whale: ";
    Pet pet{};
    std::cin >> pet;

    if (std::cin) // if we found a match
        std::cout << "You chose: " << getPetName(pet) << '\n';
    else
    {
        std::cin.clear(); // reset the input stream to good
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Your pet was not valid\n";
    }

    return 0;
}
```
This program will prompt the user to enter a pet by its name, read the input as a string, and then convert it to a `Pet` using our overloaded `operator>>`. If the input is valid, it will print the name of the chosen pet; otherwise, it will print an error message.

In this example, we defined an overloaded `operator>>` that takes two parameters: a reference to an `std::istream` object (the input stream, that will be match with the left operand) and a reference to a `Pet` enumerator (the variable to store the input value, that will be matched with the right operand). 
We use pass by non-const reference for both parameters because we do not want to make copies of the `std::istream` object (which could be expensive), and we want to modify the original stream (by reading from it) as well as the `Pet` variable (by assigning a value to it).

There are few differences between `operator>>` and `operator<<`:
- `std::cin` has type `std::istream`, while `std::cout` has type `std::ostream`. So we use `std::istream&` as the type of the first parameter in `operator>>`.
- The second parameter in `operator>>` is a non-const reference to a `Pet` variable, because we need to modify it to store the input value. In contrast, the second parameter in `operator<<` is a const value (not a reference) because we only need to read its value without modifying it.
- Inside `operator>>`, we read a string from the input stream and use the `getPetFromString` function to convert it to a `Pet`. If the conversion is successful, we assign the value to the `pet` variable; otherwise, we set the input stream to a fail state using `in.setstate(std::ios_base::failbit);`.

#### Summary:
- Operator overloading allows us to define custom behavior for operators when they are used with user-defined types.
- We can overload `operator<<` to print an enumerator to an output stream by defining a function that takes an `std::ostream` reference and an enumerator as parameters.
- We can overload `operator>>` to read an enumerator from an input stream by defining a function that takes an `std::istream` reference and a non-const reference to an enumerator as parameters.
- Overloading these operators allows us to use standard input/output syntax with our enumerated types, making our code more intuitive and easier to read.


---

### S06 — 13.6 Scoped enumerations (enum classes)
Although unscoped enumerations are distinct types in C++, they are not type-safe. This is because unscoped enumerators are placed into the same scope as the enumeration definition itself, which can lead to naming collisions and unintended conversions. Take this example:
```cpp
#include <iostream>

int main()
{
    enum Color
    {
        red,
        blue,
    };

    enum Fruit
    {
        banana,
        apple,
    };

    Color color { red };
    Fruit fruit { banana };

    if (color == fruit) // The compiler will compare color and fruit as integers
        std::cout << "color and fruit are equal\n"; // and find they are equal!
    else
        std::cout << "color and fruit are not equal\n";

    return 0;
}
```
This program will output:
```
color and fruit are equal
```
This happens because both `Color` and `Fruit` enumerations have enumerators that are placed in the same scope (global scope in this case). The enumerators `red` and `banana` both have the underlying integral value of `0`, so when we compare `color` and `fruit`, the compiler implicitly converts them to their underlying integral values and finds that they are equal.

This does not make sense semantically, as colors and fruits are different concepts and should not be compared directly. To solve this problem, C++ provides **scoped enumerations** (also known as **enum classes**), which offer better type safety and scoping.

#### Scoped enumerations:
A **scoped enumeration** (also called **enum class**) comes to solve these issues. They work similarly to unscoped enumerations, but with some key differences:
- They will not implicitly convert to their underlying integral type.
- Their enumerators are scoped within the enumeration itself, preventing naming collisions.

To define a scoped enumeration, we use the `enum class` keywords followed by the enumeration name and a list of enumerators enclosed in curly braces. For example:
```cpp
#include <iostream>
int main()
{
    enum class Color // "enum class" defines this as a scoped enumeration rather than an unscoped enumeration
    {
        red, // red is considered part of Color's scope region
        blue,
    };

    enum class Fruit
    {
        banana, // banana is considered part of Fruit's scope region
        apple,
    };

    Color color { Color::red }; // note: red is not directly accessible, we have to use Color::red
    Fruit fruit { Fruit::banana }; // note: banana is not directly accessible, we have to use Fruit::banana

    if (color == fruit) // compile error: the compiler doesn't know how to compare different types Color and Fruit
        std::cout << "color and fruit are equal\n";
    else
        std::cout << "color and fruit are not equal\n";

    return 0;
}
```
In this example, we defined two **scoped** enumerations: `Color` and `Fruit`. The enumerators `red`, `blue`, `banana`, and `apple` are scoped within their respective enumerations. This means that to access the enumerators, we need to qualify them with the enumeration name (e.g., `Color::red` and `Fruit::banana`).

When we try to compare `color` and `fruit`, the compiler will produce a compile-time error because it does not know how to compare different types (`Color` and `Fruit`), since it will not implicitly convert them to their underlying integral types. This prevents unintended comparisons and improves type safety.

> **Note 1:** THe `class` keyword (along with the `static` keyword), is one of the most overloaded keywords in the C++ language, and can have different meanings depending on the context in which it is used. In this case, `class` is used to define a scoped enumeration, which is a distinct concept from classes in C++.

> **Note 2:** `enum struct` also works the same way as `enum class`. The only difference is that `enum struct` is non-idiomatic (not commonly used) in C++. It is recommended to use `enum class` for defining scoped enumerations.

#### Scoped enumerations define their own scope regions:
Unlike unscoped enumerations, scoped enumerations define their own scope regions. This means that the enumerators are not placed in the same scope as the enumeration definition itself, but rather within the scope of the enumeration. In other words, scoped enumerations act like namespaces for their enumerators. This helps prevent naming collisions and improves code readability. For example:
```cpp
#include <iostream>

int main()
{
    enum class Color // "enum class" defines this as a scoped enum rather than an unscoped enum
    {
        red, // red is considered part of Color's scope region
        blue,
    };

    std::cout << red << '\n';        // compile error: red not defined in this scope region
    std::cout << Color::red << '\n'; // compile error: std::cout doesn't know how to print this (will not implicitly convert to int)

    Color color { Color::blue }; // okay

    return 0;
}
```
So, to access the enumerators of a scoped enumeration, you need to qualify them with the enumeration name (e.g., `Color::red` and `Color::blue`), using the scope resolution operator (`::`) with the enumeration name as the left operand.

#### Scoped enumerations do not implicitly convert to integral values:
Another key difference between scoped and unscoped enumerations is that scoped enumerations do not implicitly convert to their underlying integral type. This means that you cannot use a scoped enumeration value in a context where an integral value is expected without an explicit conversion. For example, you can do this:
```cpp
#include <iostream>
int main()
{
    enum class Color
    {
        red,
        blue,
    };

    Color shirt { Color::red };

    if (shirt == Color::red) // this Color to Color comparison is okay
        std::cout << "The shirt is red!\n";
    else if (shirt == Color::blue)
        std::cout << "The shirt is blue!\n";

    return 0;
}
```
But you cannot do this:
```cpp
#include <iostream>
int main()
{
    enum class Color
    {
        red,
        blue,
    };

    Color shirt { Color::red };

    std::cout << "Your shirt is " << shirt << '\n'; // compile error: std::cout doesn't know how to print this (will not implicitly convert to int)
    int colorValue = shirt; // compile error: cannot implicitly convert Color to int
    if (shirt == 0) // compile error: cannot compare Color with int
        std::cout << "The shirt is red!\n";
    return 0;
}
```
This is because the compiler will not implicitly convert `shirt` (of type `Color`) to an `int` when passing it to `std::cout`, assigning it to an `int` variable, or comparing it with an `int` value. This improves type safety by preventing unintended conversions and makes the code more explicit.

If you want to explicitly convert a scoped enumeration value to its underlying integral type, you can use `static_cast`, or using `std::to_underlying()` (introduced in C++23). For example:
```cpp
#include <iostream>
#include <utility> // for std::to_underlying() (C++23)

int main()
{
    enum class Color
    {
        red,
        blue,
    };

    Color color { Color::blue };

    std::cout << color << '\n'; // won't work, because there's no implicit conversion to int
    std::cout << static_cast<int>(color) << '\n';   // explicit conversion to int, will print 1
    std::cout << std::to_underlying(color) << '\n'; // convert to underlying type, will print 1 (C++23)

    return 0;
}
```

Vice versa, you can also `static_cast` an integral value to a scoped enumeration type (useful when doing input from users). For example:
```cpp
#include <iostream>

int main()
{
    enum class Pet
    {
        cat, // assigned 0
        dog, // assigned 1
        pig, // assigned 2
        whale, // assigned 3
    };

    std::cout << "Enter a pet (0=cat, 1=dog, 2=pig, 3=whale): ";

    int input{};
    std::cin >> input; // input an integer

    Pet pet{ static_cast<Pet>(input) }; // static_cast our integer to a Pet

    return 0;
}
```

As of C++17, you can list initialize a scoped enumeration using integral values directly:
```cpp
// using enum class Pet from prior example
Pet pet { 1 }; // okay
```

> **Best Practice:** Prefer using scoped enumerations (`enum class`) over unscoped enumerations (`enum`) to improve type safety and prevent naming collisions.

Despite the benefits of scoped enumerations, there are still some scenarios where unscoped enumerations may be preferred, such as when you need implicit conversion to integral types or when working with legacy code that relies on unscoped enumerations. However, in most cases, scoped enumerations are the better choice.

#### Easing the conversion of scoped enumerators to integers (Advanced):
If you find yourself frequently needing to convert scoped enumerators to their underlying integral values, using `static_cast` or `std::to_underlying()` can become cumbersome. To ease this process, a useful hack is to overload the unary `operator+` to perform conversion from a scoped enumerator to its underlying integral type. Here's how you can do it:
```cpp
#include <iostream>
#include <type_traits> // for std::underlying_type_t

enum class Animals
{
    chicken, // 0
    dog, // 1
    cat, // 2
    elephant, // 3
    duck, // 4
    snake, // 5

    maxAnimals,
};

// Overload the unary + operator to convert an enum to the underlying type
// adapted from https://stackoverflow.com/a/42198760, thanks to Pixelchemist for the idea
// In C++23, you can #include <utility> and return std::to_underlying(a) instead
template <typename T>
constexpr auto operator+(T a) noexcept
{
    return static_cast<std::underlying_type_t<T>>(a);
}

int main()
{
    std::cout << +Animals::elephant << '\n'; // convert Animals::elephant to an integer using unary operator+

    return 0;
}
```
This program will output:
```
3
```
In this example, we defined a template overload of the unary `operator+` that takes a scoped enumeration value as input and returns its underlying integral value using `static_cast`. This allows us to use the unary `+` operator to convert scoped enumerators to integers more conveniently. For instance, `+Animals::elephant` will convert `Animals::elephant` to its underlying integral value (`3` in this case).

#### `using enum` statement (C++20):
C++20 introduced the `using enum` statement, which allows you to bring all enumerators from a scoped enumeration into the current scope. This can be useful when you want to avoid repeatedly qualifying enumerators with the enumeration name. Here's an example:
```cpp
#include <iostream>
#include <string_view>

enum class Color
{
    black,
    red,
    blue,
};

constexpr std::string_view getColor(Color color)
{
    using enum Color; // bring all Color enumerators into current scope (C++20)
    // We can now access the enumerators of Color without using a Color:: prefix

    switch (color)
    {
    case black: return "black"; // note: black instead of Color::black
    case red:   return "red";
    case blue:  return "blue";
    default:    return "???";
    }
}

int main()
{
    Color shirt{ Color::blue };

    std::cout << "Your shirt is " << getColor(shirt) << '\n';

    return 0;
}
```
In this example, we used the `using enum Color;` statement inside the `getColor` function to bring all enumerators from the `Color` scoped enumeration into the current scope. This allows us to access the enumerators directly (e.g., `black`, `red`, `blue`) without needing to prefix them with `Color::`.

You might remeber, that for usign the namespace we use the `using namespace` statement (e.g., `using namespace std;`). The `using enum` statement works similarly, but it is specifically for bringing enumerators from a scoped enumeration into the current scope.

#### Summary:
- Scoped enumerations (`enum classes`) provide better type safety and scoping compared to unscoped enumerations.
- Enumerators of scoped enumerations are scoped within the enumeration itself, preventing naming collisions.
- Scoped enumerations do not implicitly convert to their underlying integral type, improving type safety.
- You can explicitly convert scoped enumeration values to their underlying integral type using `static_cast` or `std::to_underlying()`.
- The unary `operator+` can be overloaded to ease the conversion of scoped enumerators to integers.
- The `using enum` statement (introduced in C++20) allows you to bring all enumerators from a scoped enumeration into the current scope for easier access.


---

### S07 — 13.7 Introduction to structs, members, and member selection
There are many cases in which we need mroe than one single variable to represent something of interest. For example, to represent a point in 3D space (x, y, z), or also storing information of emplyees in a company (e.g., name, ID, salary, etc.). If we were using individual variables for each piece of information, our code would quickly become unmanageable and difficult to read:
```cpp
std::string name;
std::string title;
int age;
int id;
int managerId;
double wage;
int birthdayYear;
int birthdayMonth;
int birthdayDay;
int hireYear;
int hireMonth;
int hireDay;
...
```

To solve this problem, C++ provides a way to group related variables together into a single unit called a **struct** (short for "structure"). A struct is a program-defined data type tht allows us to combine multiple variables (called **data members**, or **member variables**) of different types into a single entity. This makes it easier to manage and organize related data.

#### Defining a struct:
To define a struct, we use the `struct` keyword followed by the struct name and a list of member variables enclosed in curly braces (represented by their type, name, and optional initial value), and ending with a semicolon. For example:
```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};
```
In this example, we defined a struct named `Employee` that has three members: `id` (of type `int`), `age` (of type `int`), and `wage` (of type `double`). Each member is value-initialized to a default value (0 for `int` and 0.0 for `double`). We will discuss why the initialization is important in a later section.

As a reminder, `Employee` is just a type definition, no object has been created yet. 
#### Defining struct objects:
To create an object (also called an instance) of a struct, we use the struct name as a type and declare a variable of that type. For example:
```cpp
Employee joe {}; // Employee is the type, joe is the variable name
```
This defines a variable named `joe` of type `Employee`. The member variables of `joe` are automatically value-initialized to their default values (0 for `int` and 0.0 for `double`).

#### Accessing struct members:
Consider this example:
```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe {};

    return 0;
}
```
To access the member variables of a struct object, we use the **member selection operator** (`.`). The member selection operator is a dot (`.`) that is placed between the struct object name and the member variable name. For example:
```cpp
    joe.id = 1;        // set joe's id to 1
    joe.age = 25;      // set joe's age to 25
    joe.wage = 50000;  // set joe's wage to 50000.0
```
We can also read the values of the member variables using the member selection operator:
```cpp
    std::cout << "Employee ID: " << joe.id << '\n';
    std::cout << "Employee Age: " << joe.age << '\n';
    std::cout << "Employee Wage: " << joe.wage << '\n';
```
This will output:
```
Employee ID: 1
Employee Age: 25
Employee Wage: 50000
```

One of the biggest advantage of structs is that we only need to create a single variable (`joe` of type `Employee`) to represent all the related information about an employee, instead of creating separate variables for each piece of information. This makes our code more organized and easier to read.
```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe {};
    joe.id = 14;
    joe.age = 32;
    joe.wage = 60000.0;

    Employee frank {};
    frank.id = 15;
    frank.age = 28;
    frank.wage = 45000.0;

    int totalAge { joe.age + frank.age };
    std::cout << "Joe and Frank have lived " << totalAge << " total years\n";

    if (joe.wage > frank.wage)
        std::cout << "Joe makes more than Frank\n";
    else if (joe.wage < frank.wage)
        std::cout << "Joe makes less than Frank\n";
    else
        std::cout << "Joe and Frank make the same amount\n";

    // Frank got a promotion
    frank.wage += 5000.0;

    // Today is Joe's birthday
    ++joe.age; // use pre-increment to increment Joe's age by 1

    return 0;
}
```
This program will print:
```
Joe and Frank have lived 60 total years
Joe makes more than Frank
```

Easy right? I love it :)

#### Summary:
- A struct is a program-defined data type that allows us to group related variables (member variables) of different types into a single entity.
- We define a struct using the `struct` keyword followed by the struct name and a list of member variables enclosed in curly braces.
- We create an object of a struct by declaring a variable of the struct type.
- We access the member variables of a struct object using the member selection operator (`.`).


---

### S08 — 13.8 Struct aggregate initialization
In this lesson, we will discuss about how structs are initialized in C++.

#### Data members are not initialized by default:
Like normal variables, struct member variables are not initialized by default. This means that if we create a struct object without explicitly initializing its member variables, they will contain garbage values (i.e., whatever data was previously stored in that memory location). For example:
```cpp
#include <iostream>

struct Employee
{
    int id; // note: no initializer here
    int age;
    double wage;
};

int main()
{
    Employee joe; // note: no initializer here either
    std::cout << joe.id << '\n';

    return 0;
}
```
This program will output a garbage value for `joe.id`, since it was not initialized. Accessing uninitialized variables can lead to undefined behavior, so it is important to always initialize struct member variables before using them.

Before talking about how to initialize member variables, let's first discuss about **aggregates**.

#### What is an aggregate?
In general programming, an **aggregate data type** (also called an **aggregate**) is any type thay can contain multiple data members. Some types of aggregate allow members to be of different types (e.g., structs), while others require all members to be of the same type (e.g., arrays). Aggregates are used to group related data together into a single unit, making it easier to manage and manipulate.

In C++, the definition of an aggregate is narrower and quite a bit more complicated. We will use the term *aggregate* to refer specifically to C++ aggregates as defined by the C++ standard from here on.

An aggregate in C++ is either a C-style array, or a class type (struct, class, or union) that meets all of the following criteria:
- No user-declared constructors (including default, copy, and move constructors).
- No private or protected non-static data members (all non-static data members must be public).
- No virtual functions.

The popular type `std::array` is also an aggregate, even though it has member functions, because those member functions are not virtual.

The most important thing to know as for now, it is that structs with only data members (no member functions, no constructors, etc.) are considered aggregates.

#### Aggregate initialization of a struct:
Because a normal variable can only hold a single value, we can initialize it using a single value. But structs can hold multiple values (one for each member variable), so we need a way to initialize multiple variables. But how?

There aretwo primary way to initialize struct member variables in C++: 
```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee frank = { 1, 32, 60000.0 }; // copy-list initialization using braced list
    Employee joe { 2, 28, 45000.0 };     // list initialization using braced list (preferred)

    return 0;
}
```
Each of these initializatios (copy-list initialization and list initialization) are **memberwise initializations**, meaning that each member variable of the struct is initialized using the corresponding value from the braced list, in the order they are declared in the struct definition.

> **Best Practice:** Prefer using list initialization (using braces `{}`) over copy-list initialization (using `=` and braces `={}`) for initializing struct objects, as it is more consistent with modern C++ practices and helps prevent narrowing conversions.

In C++20, we can also initialize (some) aggregates using parenthesized list of values:
```cpp
Employee robert ( 3, 45, 62500.0 );  // direct initialization using parenthesized list (C++20)
```
However, this form of initialization is less common and not as widely supported as braced list initialization, so it is generally recommended to use braced list initialization for aggregates.

#### Missing initializers in an initializer list:
When using memberwise initialization with a braced list, if there are fewer values in the initializer list than there are member variables in the struct, then each member without an explicit initializer will be initialized as follow:
- If the member has a default member initializer (e.g., `int id {};`), it will be initialized using that default value.
- If the member does not have a default member initializer, it will be copy-initialized from an empty initializer list (`{}`). In most of the cases, it will result in value-initialization (e.g., `int` members will be initialized to `0`, `double` members will be initialized to `0.0`, etc.).

For example:
```cpp
struct Employee
{
    int id {};
    int age {};
    double wage { 76000.0 };
    double whatever;
};

int main()
{
    Employee joe { 2, 28 }; // joe.whatever will be value-initialized to 0.0

    return 0;
}
```
In this example, we only provided two initializers (`2` and `28`) for the `id` and `age` members of the `Employee` struct. The `wage` member has a default member initializer (`76000.0`), so it will be initialized to that value. The `whatever` member does not have a default member initializer, so it will be value-initialized to `0.0`.

#### Overloading `operator<<` to print a struct:
In the previous section, we learned how to overload `operator<<` to print an enumerator. We can also overload `operator<<` to print a struct. Here is an example:
```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

std::ostream& operator<<(std::ostream& out, const Employee& e)
{
    out << e.id << ' ' << e.age << ' ' << e.wage;
    return out;
}

int main()
{
    Employee joe { 2, 28 }; // joe.wage will be value-initialized to 0.0
    std::cout << joe << '\n';

    return 0;
}
```
This program will output:
```
2 28 0
```
In this way, if one of the operand of `operator<<` is of type `Employee`, the compiler will use our overloaded function to print the member variables of the struct.

We could imporve this example by adding some formatting to the output, but the main idea is that we can overload `operator<<` to print structs in a similar way as we did for enumerators.
```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

std::ostream& operator<<(std::ostream& out, const Employee& e)
{
    out << "id: " << e.id << " age: " << e.age << " wage: " << e.wage;
    return out;
}

int main()
{
    Employee joe { 2, 28 }; // joe.wage will be value-initialized to 0.0
    std::cout << joe << '\n';

    return 0;
}
```
printing:
```
id: 2 age: 28 wage: 0
```
that is more readable.

#### Const structs:
Variables of struct type can also be declared as `const` or `constexpr`, and just like all const variables, they must be initialized at the point of declaration. For example:
```cpp
struct Rectangle
{
    double length {};
    double width {};
};

int main()
{
    const Rectangle unit { 1.0, 1.0 };
    const Rectangle zero { }; // value-initialize all members

    return 0;
}
```

#### Designated initializers (C++20):
When initializing a struct from a list of values, the initializers are applied to the members in order of declaration. 
```cpp
struct Foo
{
    int a {};
    int c {};
};

int main()
{
    Foo f { 1, 3 }; // f.a = 1, f.c = 3

    return 0;
}
```
Now consider if we are now adding a new member `b` in the middle of the struct:
```cpp
struct Foo
{
    int a {};
    int b {}; // just added
    int c {};
};

int main()
{
    Foo f { 1, 3 }; // now, f.a = 1, f.b = 3, f.c = 0

    return 0;
}
```
This change will break any existing code that initializes `Foo` objects using memberwise initialization, because the initializers will now be applied to the wrong members.

To solve this problem, C++20 introduced **designated initializers**, which allow us to specify which member variable each initializer corresponds to, regardless of the order of declaration. Here is an example:
```cpp
struct Foo
{
    int a{ };
    int b{ };
    int c{ };
};

int main()
{
    Foo f1{ .a{ 1 }, .c{ 3 } }; // ok: f1.a = 1, f1.b = 0 (value initialized), f1.c = 3
    Foo f2{ .a = 1, .c = 3 };   // ok: f2.a = 1, f2.b = 0 (value initialized), f2.c = 3
    Foo f3{ .b{ 2 }, .a{ 1 } }; // error: initialization order does not match order of declaration in struct

    return 0;
}
```
In this example, we used designated initializers to specify which member variable each initializer corresponds to. The syntax for designated initializers is to use a dot (`.`) followed by the member variable name, and then either braces (`{}`) or an equals sign (`=`) to assign the value.

> **Best Practice:** When adding a new member to a struct, prefer to add it at the end of the struct to avoid breaking existing code that uses memberwise initialization.

#### Assignment with an initializer list:
As shown in the previous lesson, we can assign values to members of structs individually:
```cpp
    joe.id = 1;
    joe.age = 25;
    joe.wage = 50000;
```

This is fine for single members, but not great if we want to assign values to multiple members at once. Fortunately, C++ allows us to use an initializer list on the right-hand side of an assignment to assign values to multiple members of a struct at once. For example:
```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe { 1, 32, 60000.0 };
    joe = { joe.id, 33, 66000.0 }; // Joe had a birthday and got a raise

    return 0;
}
```
Here, since we didn't want to change Joe's `id`, we used `joe.id` as the first value in the initializer list, and then provided new values for `age` and `wage`. This will assign the new values to the corresponding members of `joe`.

#### Assignment with designated initializers (C++20):
Designated initializers can also be used in a list assignment to specify which member variable each value corresponds to. For example:
```cpp
struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe { 1, 32, 60000.0 };
    joe = { .id = joe.id, .age = 33, .wage = 66000.0 }; // Joe had a birthday and got a raise

    return 0;
}
```
If we hadn't have specified a designated initializer for `joe.id`, it would have been value-initialized to `0`, which is not what we wanted.

#### Initializing a struct with another struct of the same type:
We can also initialize a struct object using another struct object of the same type. For example:
```cpp
#include <iostream>

struct Foo
{
    int a{};
    int b{};
    int c{};
};

std::ostream& operator<<(std::ostream& out, const Foo& f)
{
    out << f.a << ' ' << f.b << ' ' << f.c;
    return out;
}

int main()
{
    Foo foo { 1, 2, 3 };

    Foo x = foo; // copy-initialization
    Foo y(foo);  // direct-initialization
    Foo z {foo}; // direct-list-initialization

    std::cout << x << '\n';
    std::cout << y << '\n';
    std::cout << z << '\n';

    return 0;
}
```
This program will output:
```
1 2 3
1 2 3
1 2 3
```
In this example, we defined a struct `Foo` with three members: `a`, ``b`, and `c`. We then created a `Foo` object named `foo` and initialized it with values `1`, `2`, and `3`. We then created three new `Foo` objects (`x`, `y`, and `z`) using copy initialization, direct initialization, and direct-list initialization, respectively, all using the `foo` object. All three new objects will have the same member values as `foo`.

#### Summary:
- Struct member variables are not initialized by default, so it is important to always initialize them before use.
- A struct is considered an aggregate if it has no user-declared constructors, no private or protected non-static data members, and no virtual functions.
- We can initialize struct member variables using memberwise initialization with a braced list of values.
- If there are fewer values in the initializer list than member variables, the remaining members will be initialized using their default member initializers or value-initialization.
- We can overload `operator<<` to print a struct by defining a function that takes an `std::ostream` reference and a const reference to the struct as parameters.
- We can use designated initializers (C++20) to specify which member variable each initializer corresponds to, regardless of the order of declaration.
- We can assign values to multiple members of a struct at once using an initializer list on the right-hand side of an assignment.
- We can initialize a struct object using another struct object of the same type.


---

### S09 — 13.9 Default member initialization
When we define a struct (or class) type, we can provide default initializers for its member variables. For members non marked as `static`, this is sometimes called **non-static member initialization** or **default member initialization**. The initialization value is called a **default member initializer**. Here is an example:
```cpp
struct Something
{
    int x;       // no initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s1; // s1.x is uninitialized, s1.y is 0, and s1.z is 2

    return 0;
}
```
In this example, we defined a struct named `Something` with three member variables: `x`, `y`, and `z`. The member variable `x` does not have a default member initializer, so it will be uninitialized when we create a `Something` object. The member variable `y` has a default member initializer that value-initializes it to `0`, and the member variable `z` has a default member initializer that explicitly initializes it to `2`.

When we create a `Something` object named `s1`, the member variable `x` will contain a garbage value (since it is uninitialized), `y` will be initialized to `0`, and `z` will be initialized to `2`.

#### Explicit initialization values take precedence over default member initializers:
When we create a struct object using memberwise initialization (i.e., providing a braced list of values), the explicit initialization values take precedence over the default member initializers. For example:
```cpp
struct Something
{
    int x;       // no default initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s2 { 5, 6, 7 }; // use explicit initializers for s2.x, s2.y, and s2.z (no default values are used)

    return 0;
}
```
In this example, we created a `Something` object named `s2` using memberwise initialization with the values `5`, `6`, and `7`. The member variable `x` will be initialized to `5`, `y` will be initialized to `6`, and `z` will be initialized to `7`. The default member initializers for `y` and `z` are ignored in this case because we provided explicit initialization values.

#### Missing initializers in an initializer list when default values exist:
When using memberwise initialization with a braced list, if there are fewer values in the initializer list than there are member variables in the struct, then each member without an explicit initializer will be initialized with its default value (if it has one), or value-initialized (if it does not have a default value). For example:
```cpp
struct Something
{
    int x;       // no default initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s3 {}; // value initialize s3.x, use default values for s3.y and s3.z

    return 0;
}
```
In this example, we created a `Something` object named `s3` using an empty braced list. The member variable `x` does not have a default member initializer, so it will be value-initialized to `0`. The member variable `y` has a default member initializer that value-initializes it to `0`, and the member variable `z` has a default member initializer that explicitly initializes it to `2`.

#### Recapping the initialization possibilities:
If an aggregate is defined with an initializer list, each member is initialized as follows:
- If an explicit initializer is provided in the initializer list, that value is used.
- If an initializer is missing and a default member initializer exists, the default member initializer is used.
- If an initializer is missing and no default member initializer exists, the member is value-initialized.

If an aggregate is defined with no initializer list, each member is initialized as follows:
- If a default member initializer exists, the default member initializer is used.
- If no default member initializer exists, the member is left uninitialized.

Note that members are always initialized in the order of their declaration in the struct.

The following example summarizes all the different initialization possibilities:
```cpp
struct Something
{
    int x;       // no default initialization value (bad)
    int y {};    // value-initialized by default
    int z { 2 }; // explicit default value
};

int main()
{
    Something s1;             // No initializer list: s1.x is uninitialized, s1.y and s1.z use defaults
    Something s2 { 5, 6, 7 }; // Explicit initializers: s2.x, s2.y, and s2.z use explicit values (no default values are used)
    Something s3 {};          // Missing initializers: s3.x is value initialized, s3.y and s3.z use defaults

    return 0;
}
```
In this example:
- `s1` is created without an initializer list, so `s1.x` is uninitialized, `s1.y` is value-initialized to `0`, and `s1.z` is initialized to `2`.
- `s2` is created with an initializer list, so `s2.x` is initialized to `5`, `s2.y` is initialized to `6`, and `s2.z` is initialized to `7`.
- `s3` is created with an empty initializer list, so `s3.x` is value-initialized to `0`, `s3.y` is value-initialized to `0`, and `s3.z` is initialized to `2`.

> **Best Practice:** Always provide default member initializers for your struct member variables to ensure they are properly initialized and to prevent undefined behavior from uninitialized members. At least use `{}` to value-initialize them.

#### Always provide default values for your members:
To avoid unitialized members, it is a good practice to always provide default member initializers for your struct member variables. This ensures that all members are properly initialized when a struct object is created, even if no explicit initializer is provided.

Consider the following example:
```cpp
struct Fraction
{
	int numerator { }; // we should use { 0 } here, but for the sake of example we'll use value initialization instead
	int denominator { 1 };
};

int main()
{
	Fraction f1;          // f1.numerator value initialized to 0, f1.denominator defaulted to 1
	Fraction f2 {};       // f2.numerator value initialized to 0, f2.denominator defaulted to 1
	Fraction f3 { 6 };    // f3.numerator initialized to 6, f3.denominator defaulted to 1
	Fraction f4 { 5, 8 }; // f4.numerator initialized to 5, f4.denominator initialized to 8

	return 0;
}
```
In all cases, the members of the `Fraction` struct are properly initialized, preventing any undefined behavior from uninitialized members.

> **Best Practice:** Always provide default member initializers for your struct member variables to ensure they are properly initialized and to prevent undefined behavior from uninitialized members.

#### Default initialization vs value initialization for aggregates:
Taking the example of before:
```cpp
Fraction f1;          // f1.numerator value initialized to 0, f1.denominator defaulted to 1
Fraction f2 {};       // f2.numerator value initialized to 0, f2.denominator defaulted to 1
```
You see that `f1` is default initialized, while `f2` is value initialized. However, because both member variables of `Fraction` have default member initializers, both `f1` and `f2` will have their members initialized to the same values: `numerator` to `0` and `denominator` to `1`.

In general, value initialization is safer because in case a member does not have a default member initializer, it will be value-initialized (e.g., initialized to `0` for `int` members). Default initialization, on the other hand, will leave such members uninitialized, which can lead to undefined behavior if they are accessed before being explicitly initialized.

> **Best Practice:** Prefer value initialization (using `{}`) over default initialization when creating struct objects to ensure all members are properly initialized, especially if some members do not have default member initializers.

#### Summary:
- Default member initialization allows us to provide default initializers for struct member variables.
- When creating a struct object using memberwise initialization, explicit initialization values take precedence over default member initializers.
- If there are fewer values in the initializer list than member variables, the remaining members will be initialized using their default member initializers or value-initialization.
- It is a good practice to always provide default member initializers for struct member variables to ensure they are properly initialized and to prevent undefined behavior from uninitialized members.
- Prefer value initialization (using `{}`) over default initialization when creating struct objects to ensure all members are properly initialized.


---

### S10 — 13.10 Passing and returning structs
Consider an epmployee represented by 3 loose variables:
```cpp
int main()
{
    int id { 1 };
    int age { 24 };
    double wage { 52400.0 };

    return 0;
}
```
If we want to pass this employee information to a function, we would need to pass each variable individually:
```cpp
#include <iostream>

void printEmployee(int id, int age, double wage)
{
    std::cout << "ID:   " << id << '\n';
    std::cout << "Age:  " << age << '\n';
    std::cout << "Wage: " << wage << '\n';
}

int main()
{
    int id { 1 };
    int age { 24 };
    double wage { 52400.0 };

    printEmployee(id, age, wage);

    return 0;
}
```
And it is definitely not ideal. If we later decide to add more information about the employee (e.g., name, department, etc., having more than 10 variables), we would need to modify the function signature and all calls to the function to include the new parameters.

#### Passing structs by reference:
A big advantage of using structs over individual variables is that we can pass the entire struct object to a function as a single parameter. Structs are generally passed by refernce (typically by const reference) to avoid making a copy of the entire struct, which can be inefficient for large structs. Here is an example:
```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

void printEmployee(const Employee& employee) // note pass by reference here
{
    std::cout << "ID:   " << employee.id << '\n';
    std::cout << "Age:  " << employee.age << '\n';
    std::cout << "Wage: " << employee.wage << '\n';
}

int main()
{
    Employee joe { 14, 32, 24.15 };
    Employee frank { 15, 28, 18.27 };

    // Print Joe's information
    printEmployee(joe);

    std::cout << '\n';

    // Print Frank's information
    printEmployee(frank);

    return 0;
}
```
In this example, we defined a struct named `Employee` to represent an employee with three member variables: `id`, `age`, and `wage`. We then defined a function named `printEmployee` that takes a const reference to an `Employee` object as a parameter and prints its member variables.
In the `main` function, we created two `Employee` objects (`joe` and ` frank`) and passed them to the `printEmployee` function to print their information.

You can see that this is way cleaner and more manageable than passing individual variables. If we later decide to add more information about the employee, we only need to modify the `Employee` struct definition, and the function signature remains unchanged.

#### Passin temporary structs:
In the previous example, we have created Emplyee variable `joe` and `frank` before passing them to the `printEmployee` function. However, this requires two statements (one to create the variable and one to use it). In case we only need to use a variable once, we can create a temporary struct object directly in the function call. For example:
```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

void printEmployee(const Employee& employee) // note pass by reference here
{
    std::cout << "ID:   " << employee.id << '\n';
    std::cout << "Age:  " << employee.age << '\n';
    std::cout << "Wage: " << employee.wage << '\n';
}

int main()
{
    // Print Joe's information
    printEmployee(Employee { 14, 32, 24.15 }); // construct a temporary Employee to pass to function (type explicitly specified) (preferred)

    std::cout << '\n';

    // Print Frank's information
    printEmployee({ 15, 28, 18.27 }); // construct a temporary Employee to pass to function (type deduced from parameter)

    return 0;
}
```
In this example, we created temporary `Employee` objects directly in the function calls to `printEmployee`. In the first call, we explicitly specified the type `Employee` when creating the temporary object. In the second call, we omitted the type, and the compiler deduced it from the function parameter type.

Temporary objects like these, are created and initialized at the point of definition, and are destryed at the end of the full expression in which they are created (i.e., at the end of the function call in this case). Since this is an rvalue expression, can only be used where rvalues are allowed (e.g., passing to functions by value or by const reference, excluding passing by non-const reference or by address).

#### Returning structs from functions:
Just like we can pass structs to functions, we can also return structs from functions. One common way is to return a struct by value. Here is an example:
```cpp
#include <iostream>

struct Point3d
{
    double x { 0.0 };
    double y { 0.0 };
    double z { 0.0 };
};

Point3d getZeroPoint()
{
    // We can create a variable and return the variable (we'll improve this below)
    Point3d temp { 0.0, 0.0, 0.0 };
    return temp;
}

int main()
{
    Point3d zero{ getZeroPoint() };

    if (zero.x == 0.0 && zero.y == 0.0 && zero.z == 0.0)
        std::cout << "The point is zero\n";
    else
        std::cout << "The point is not zero\n";

    return 0;
}
```
Here, the `Point3d` object is returned by value from the `getZeroPoint` function. In the `main` function, we call `getZeroPoint` and use its return value to initialize a `Point3d` object named `zero`.

Structs defined inside functions are usually returned by value, avoiding returning dangling references or pointers to local variables. In this function, we just create the `temp` variable to return it, but we can simplify this by directly returning a temporary struct object:
```cpp
Point3d getZeroPoint()
{
    return Point3d { 0.0, 0.0, 0.0 }; // return an unnamed Point3d
}
```
This way, we directly create and return a temporary `Point3d` object without needing to create a named variable.

#### Deducing the return type:
In case the function has a specific return type (e.g., `Point3d` in the previous example), we can omit the type when returning a temporary struct object, and the compiler will deduce the type from the function's return type. For example:
```cpp
Point3d getZeroPoint()
{
    // We already specified the type at the function declaration
    // so we don't need to do so here again
    return { 0.0, 0.0, 0.0 }; // return an unnamed Point3d
}
```
In this case the compiler will deduce that we are returning a `Point3d` object based on the function's return type. This is considered to be an implicit conversion from the braced list to the return type.

Also note that in this case, sicne we are returning all zero values, we could have simply written:
```cpp
Point3d getZeroPoint()
{
    // We can use empty curly braces to value-initialize all members
    return {};
}
```
This will value-initialize all members of the `Point3d` object to `0.0`.

#### Structs are an important building block:
While structs are useful in and of themselves, classes (which we will discuss later) build upon the concept of structs by adding features such as member functions, access control, and inheritance. Understanding structs is an important step towards mastering classes and object-oriented programming in C++.

#### Summary:
- Structs can be passed to functions by const reference to avoid making a copy of the entire struct.
- Temporary struct objects can be created directly in function calls when passing structs to functions.
- Structs can be returned from functions by value (when defined inside functions) to avoid returning dangling references or pointers to local variables.
- Temporary struct objects can be created and returned directly from functions.


---

### S11 — 13.11 Struct miscellanea
#### Structs with program-defined members:
In C++, structs and classes can have members that are other program-defined types. There are two ways to do this.

First we can define a program-defined type (in the global scope) and then use it as a member of a struct. For example:
```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

struct Company
{
    int numberOfEmployees {};
    Employee CEO {}; // Employee is a struct within the Company struct
};

int main()
{
    Company myCompany{ 7, { 1, 32, 55000.0 } }; // Nested initialization list to initialize Employee
    std::cout << myCompany.CEO.wage << '\n'; // print the CEO's wage

    return 0;
}
```
In this example, we defined a struct named `Employee` to represent an employee with three member variables: `id`, `age`, and `wage`. We then defined another struct named `Company` that has two member variables: `numberOfEmployees` and `CEO`, where `CEO` is of type `Employee`. We then created a `Company` object named `myCompany` and initialized its members using a nested initializer list (`{ 7, { 1, 32, 55000.0 } }`), where the inner braces initialize the `CEO` member.

Second, types can also be nested inside other types. So if an `Emplyee` only exists in the scope of a `Company`, we can define it inside the `Company` struct. For example:
```cpp
#include <iostream>

struct Company
{
    struct Employee // accessed via Company::Employee
    {
        int id{};
        int age{};
        double wage{};
    };

    int numberOfEmployees{};
    Employee CEO{}; // Employee is a struct within the Company struct
};

int main()
{
    Company myCompany{ 7, { 1, 32, 55000.0 } }; // Nested initialization list to initialize Employee
    std::cout << myCompany.CEO.wage << '\n'; // print the CEO's wage

    return 0;
}
```
In this case, we defined the `Employee` struct inside the `Company` struct. To refer to the nested `Employee` type outside of the `Company` struct, we need to use the scope resolution operator (`::`) like this: `Company::Employee`. This is more often done with classes, so we will talk about it in a future lesson.

#### Structs that rae owners should have data members that are owners:
In a previous lesson (about `std::string_view`), we discussed the concept of ownership in C++ (owners vs viewers). Owners manage their own data, and control when it is destroyed. Viewers, on the other hand, do not own their data, and rely on owners to manage the data's lifetime.

In most cases, we want our structs (and classes) to be owners, meaning that they manage their own data. This gives some benefits:
- Data members will be valid for as long as the struct (or class) object exists.
- Value of those data will not change unexpectedly (unless explicitly modified).

The easiest way to make a struct (or class) an owner, is to give each data member a type that is an owner( e.g., not a viewer, pointer, or reference). If a struct (or class) has **all** of its data members as owners, then the struct (or class) itself is an owner.

If a struct (or class) has one or more data members that are viewers, pointers, or references, then the struct (or class) is not an owner. In this case, it would be possible that the data members could become invalid while the struct (or class) object still exists, leading to dangling references or pointers.

> **Best Practice:** When designing structs (or classes), prefer to use owner types for data members to ensure that the struct (or class) itself is an owner. This helps prevent dangling references or pointers and ensures that data members remain valid for the lifetime of the struct (or class) object.

This is why data memebrs preferred to be of types such as `std::string`, `std::vector`, and other standard library types that manage their own memory, rather than `std::string_view`, raw pointers, or references. For example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

struct Owner
{
    std::string name{}; // std::string is an owner
};

struct Viewer
{
    std::string_view name {}; // std::string_view is a viewer
};

// getName() returns the user-entered string as a temporary std::string
// This temporary std::string will be destroyed at the end of the full expression
// containing the function call.
std::string getName()
{
    std::cout << "Enter a name: ";
    std::string name{};
    std::cin >> name;
    return name;
}

int main()
{
    Owner o { getName() };  // The return value of getName() is destroyed just after initialization
    std::cout << "The owners name is " << o.name << '\n';  // ok

    Viewer v { getName() }; // The return value of getName() is destroyed just after initialization
    std::cout << "The viewers name is " << v.name << '\n'; // undefined behavior

    return 0;
}
```
In this example, we defined two structs: `Owner` and `Viewer`. The `Owner` struct has a data member of type `std::string`, which is an owner type. The `Viewer` struct has a data member of type `std::string_view`, which is a viewer type. When we create an `Owner` object named `o`, the `name` member is properly initialized and remains valid for the lifetime of the `o` object. However, when we create a `Viewer` object named `v`, the `name` member is initialized with a temporary `std::string` returned by the `getName` function, which is destroyed at the end of the full expression. This leads to undefined behavior when we try to access `v.name`.

#### Struct size and data structure alignment:
Typically, the size of a struct is equal to the sum of the sizes of its member variables. But be careful, not always! Due to data structure alignment requirements imposed by the underlying hardware architecture, the compiler may add padding bytes between member variables or at the end of the struct to ensure that each member variable is properly aligned in memory. For example:
```cpp
#include <iostream>

struct Foo
{
    short a {};
    int b {};
    double c {};
};

int main()
{
    std::cout << "The size of short is " << sizeof(short) << " bytes\n";
    std::cout << "The size of int is " << sizeof(int) << " bytes\n";
    std::cout << "The size of double is " << sizeof(double) << " bytes\n";

    std::cout << "The size of Foo is " << sizeof(Foo) << " bytes\n";

    return 0;
}
```
On a typical 64-bit system, this program might output:
```
The size of short is 2 bytes
The size of int is 4 bytes
The size of double is 8 bytes
The size of Foo is 16 bytes
```
As you can see, the size of `Foo` is `16` bytes, which is larger than the sum of the sizes of its member variables (`2 + 4 + 8 = 14` bytes). This is because the compiler added padding bytes to ensure that each member variable is properly aligned in memory.

So in general, we can safely say that the size of a struct is **at least** to the sum of the sizes of its member variables.

This can have a pretty significant impact on the size of the struct, as the following example shows:
```cpp
#include <iostream>

struct Foo1
{
    short a{}; // will have 2 bytes of padding after a
    int b{};
    short c{}; // will have 2 bytes of padding after c
};

struct Foo2
{
    int b{};
    short a{};
    short c{};
};

int main()
{
    std::cout << sizeof(Foo1) << '\n'; // prints 12
    std::cout << sizeof(Foo2) << '\n'; // prints 8

    return 0;
}
```
This program will output:
```
12
8
```
So, just by rearranging the member variables of `Foo1` to create `Foo2`, we were able to reduce the size of the struct from `12` bytes to `8` bytes by minimizing the amount of padding added by the compiler.

> **Best Practice:** When defining structs (or classes), consider the order of member variables to minimize padding and reduce the overall size of the struct. Group member in decreasing order of size (largest to smallest) to help achieve better alignment and reduce padding.

#### Summary:
- Structs and classes can have members that are other program-defined types, either defined in the global scope or nested inside other types.
- When designing structs (or classes), prefer to use owner types for data members to ensure that the struct (or class) itself is an owner. This helps prevent dangling references or pointers and ensures that data members remain valid for the lifetime of the struct (or class) object.
- The size of a struct is at least equal to the sum of the sizes of its member variables, but may be larger due to padding added by the compiler for data structure alignment.
- Consider the order of member variables when defining structs (or classes) to minimize padding and reduce the overall size of the struct.


---

### S12 — 13.12 Member selection with pointers and references
#### Member selection for structs and references to structs:
In lesson [13.7 Introduction to structs, members, and member selection](#s07--137-introduction-to-structs-members-and-member-selection), we have seen that we can use the member selection operator (`.`) to access members of a struct:
```cpp
#include <iostream>

struct Employee
{
    int id {};
    int age {};
    double wage {};
};

int main()
{
    Employee joe { 1, 34, 65000.0 };

    // Use member selection operator (.) to select a member from struct object
    ++joe.age; // Joe had a birthday
    joe.wage = 68000.0; // Joe got a promotion

    return 0;
}
```

Since references to an object act just like the object itself, we can also use the member selection operator (`.`) to access members of a struct through a reference to that struct. For example:
```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

void printEmployee(const Employee& e)
{
    // Use member selection operator (.) to select member from reference to struct
    std::cout << "Id: " << e.id << '\n';
    std::cout << "Age: " << e.age << '\n';
    std::cout << "Wage: " << e.wage << '\n';
}

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    printEmployee(joe);

    return 0;
}
```
Here, we are able to access the members of the `Employee` struct through the reference parameter `e` using the member selection operator (`.`).

#### Member selection for pointers to structs:
However, the member operator (`.`) cannot be used with pointers to structs:
```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    Employee* ptr{ &joe };
    std::cout << ptr.id << '\n'; // Compile error: can't use operator. with pointers

    return 0;
}
```
In this example, we attempted to use the member selection operator (`.`) with a pointer to a struct of type `Employee`, which results in a compile-time error.

Because pointers are not the same as the objects they point to, but they store the memory address of those objects, we need to first dereference gthe pointer to get the actual object before we can access its members. We can do this using the dereference operator (`*`):
```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    Employee* ptr{ &joe };
    std::cout << (*ptr).id << '\n'; // Not great but works: First dereference ptr, then use member selection

    return 0;
}
```
In this example, we dereferenced the pointer `ptr` using the dereference operator (`*`) to get the actual `Employee` object, and then used the member selection operator (`.`) to access the `id` member. 

This works, but it is not so nice to see. Fortunately, C++ provides a more convenient way to access members of a struct through a pointer using the **member selection from pointer operator** (`->`) (also called the **arrow operator**). The arrow operator combines dereferencing the pointer and accessing the member into a single operation. Here is an example:
```cpp
#include <iostream>

struct Employee
{
    int id{};
    int age{};
    double wage{};
};

int main()
{
    Employee joe{ 1, 34, 65000.0 };

    ++joe.age;
    joe.wage = 68000.0;

    Employee* ptr{ &joe };
    std::cout << ptr->id << '\n'; // Better: use -> to select member from pointer to object

    return 0;
}
```
In this way, we can simply use the arrow operator (`->`) to access members of a struct through a pointer to that struct. Thus, `ptr->id` is equivalent to `(*ptr).id`.

> **Best Practice:** When accessing members of a struct through a pointer, prefer to use the arrow operator (`->`) for better readability and conciseness.

#### Chaining `operator->`:
The arrow operator (`->`) can be chained to access members of nested structs or classes (e.g., if the member accessed via `->` is itself a pointer to another struct or class). For example:
```cpp
#include <iostream>

struct Point
{
    double x {};
    double y {};
};

struct Triangle
{
    Point* a {};
    Point* b {};
    Point* c {};
};

int main()
{
    Point a {1,2};
    Point b {3,7};
    Point c {10,2};

    Triangle tr { &a, &b, &c };
    Triangle* ptr {&tr};

    // ptr is a pointer to a Triangle, which contains members that are pointers to a Point
    // To access member y of Point c of the Triangle pointed to by ptr, the following are equivalent:

    // access via operator.
    std::cout << (*(*ptr).c).y << '\n'; // ugly!

    // access via operator->
    std::cout << ptr -> c -> y << '\n'; // much nicer
}
```
In this example, we defined a `Point` struct and a `Triangle` struct that contains pointers to `Point` objects. We then created a pointer to a `Triangle` object and used the arrow operator (`->`) to access the `y` member of the `Point` object pointed to by the `c` member of the `Triangle` object.

#### Mixing pointers and non-pointers to members:
The member selection operator is always applied to the currently selected variable. So when mixing pointers and non-pointers, we need to be careful to use the correct operator for each level of selection. For example:
```cpp
#include <iostream>
#include <string>

struct Paw
{
    int claws{};
};

struct Animal
{
    std::string name{};
    Paw paw{};
};

int main()
{
    Animal puma{ "Puma", { 5 } };

    Animal* ptr{ &puma };

    // ptr is a pointer, use ->
    // paw is not a pointer, use .

    std::cout << (ptr->paw).claws << '\n';

    return 0;
}
```
Note that in this example, we used the arrow operator (`->`) to access the `paw` member of the `Animal` struct through the pointer `ptr` (since `ptr` is a pointer), and then used the member selection operator (`.`) to access the `claws` member of the `Paw` struct (since `paw` is not a pointer).

#### Summary:
- The member selection operator (`.`) is used to access members of a struct or class.
- The member selection operator (`.`) can also be used with references to structs or classes.
- The member selection operator (`.`) cannot be used with pointers to structs or classes.
- To access members of a struct or class through a pointer, we can use the dereference operator (`*`) followed by the member selection operator (`.`), or we can use the arrow operator (`->`) for better readability.
- The arrow operator (`->`) can be chained to access members of nested structs or classes.
- When mixing pointers and non-pointers, use the appropriate operator (`.` or `->`) for each level of selection.


---

### S13 — 13.13 Class templates
In a previous chapter we covered function templates, and how they are used to overload functions based on types. We saw that instead of doing this (declaring multiple functions with the same name but different parameter types):
```cpp
#include <iostream>

// function to calculate the greater of two int values
int max(int x, int y)
{
    return (x < y) ? y : x;
}

// almost identical function to calculate the greater of two double values
// the only difference is the type information
double max(double x, double y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(5, 6);     // calls max(int, int)
    std::cout << '\n';
    std::cout << max(1.2, 3.4); // calls max(double, double)

    return 0;
}
```
We could instead do this using a function template:
```cpp
#include <iostream>

// a single function template for max
template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max(5, 6);     // instantiates and calls max<int>(int, int)
    std::cout << '\n';
    std::cout << max(1.2, 3.4); // instantiates and calls max<double>(double, double)

    return 0;
}
```
This way, we only needed to define the `max` function once, and the compiler generates the appropriate version of the function based on the types of the arguments passed to it.

#### Aggregate types have similar chalenges:
We have similar challenges with aggregate types (both structs/classes/unions and arrays). For example, consider the following struct that represents a pair of integers:
```cpp
#include <iostream>

struct Pair
{
    int first{};
    int second{};
};

constexpr int max(Pair p) // pass by value because Pair is small
{
    return (p.first < p.second ? p.second : p.first);
}

int main()
{
    Pair p1{ 5, 6 };
    std::cout << max(p1) << " is larger\n";

    return 0;
}
```
Later, we find out that we also need to represent pairs of doubles. We could define a new struct for pairs of doubles:
```cpp
#include <iostream>

struct Pair
{
    int first{};
    int second{};
};

struct Pair // compile error: erroneous redefinition of Pair
{
    double first{};
    double second{};
};

constexpr int max(Pair p)
{
    return (p.first < p.second ? p.second : p.first);
}

constexpr double max(Pair p) // compile error: overloaded function differs only by return type
{
    return (p.first < p.second ? p.second : p.first);
}

int main()
{
    Pair p1{ 5, 6 };
    std::cout << max(p1) << " is larger\n";

    Pair p2{ 1.2, 3.4 };
    std::cout << max(p2) << " is larger\n";

    return 0;
}
```
However, this results in compile-time errors because:
- Unlike function definitions, type definitions cannot be overloaded. We cannot define two structs with the same name (`Pair`) in the same scope, even if they have different member types.
- Although functions can be overloaded based on parameter types, they cannot be overloaded based solely on return type. In this case, both `max` functions have the same parameter type (`Pair`), so the compiler cannot distinguish between them based on return type alone.
- This program is way too redundant, and violates the DRY (Don't Repeat Yourself) principle.

We could solve the first two issues by giving the structs and functions different names (e.g., `IntPair`, `DoublePair`, `maxIntPair`, `maxDoublePair`), but this would lead to a lot of code duplication and make the code harder to maintain.

Luckily, we can do better using class templates.

#### Class templates:
Like function templates, a **class template** is a template definition for instantiating class types. A class template allows us to define a blueprint for a class that can work with any data type. The compiler generates the appropriate class definition based on the types used when creating objects of the class template.

For example, here is our original `Pair` struct defined as a class template:
```cpp
struct Pair
{
    int first{};
    int second{};
};
```
can be defined as:
```cpp
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};
```
and can be used like this:
```cpp
int main()
{
    Pair<int> p1{ 5, 6 };        // instantiates Pair<int> and creates object p1
    std::cout << p1.first << ' ' << p1.second << '\n';

    Pair<double> p2{ 1.2, 3.4 }; // instantiates Pair<double> and creates object p2
    std::cout << p2.first << ' ' << p2.second << '\n';

    Pair<double> p3{ 7.8, 9.0 }; // creates object p3 using prior definition for Pair<double>
    std::cout << p3.first << ' ' << p3.second << '\n';

    return 0;
}
```
You can define a class template exactly as you did for function templates, using the `template` keyword followed by template parameters enclosed in angle brackets (`<>`). For example `template <typename T>` defines a template parameter `T` that can be used as a type within the class template definition.

When creating objects of a class template, differently from function templates, you must explicitly specify the template arguments (i.e., the types to be used) within angle brackets (`<>`) after the class template name. For example, `Pair<int>` creates a `Pair` object where `T` is replaced with `int`, and `Pair<double>` creates a `Pair` object where `T` is replaced with `double`. In the last case, since we already instantiated `Pair<double>`, we can create multiple objects of that type without needing to re-specify the template arguments.

Here is what the compiler will actually compile after all the templates instantiations are done:
```cpp
#include <iostream>

// A declaration for our Pair class template
// (we don't need the definition any more since it's not used)
template <typename T>
struct Pair;

// Explicitly define what Pair<int> looks like
template <> // tells the compiler this is a template type with no template parameters
struct Pair<int>
{
    int first{};
    int second{};
};

// Explicitly define what Pair<double> looks like
template <> // tells the compiler this is a template type with no template parameters
struct Pair<double>
{
    double first{};
    double second{};
};

int main()
{
    Pair<int> p1{ 5, 6 };        // instantiates Pair<int> and creates object p1
    std::cout << p1.first << ' ' << p1.second << '\n';

    Pair<double> p2{ 1.2, 3.4 }; // instantiates Pair<double> and creates object p2
    std::cout << p2.first << ' ' << p2.second << '\n';

    Pair<double> p3{ 7.8, 9.0 }; // creates object p3 using prior definition for Pair<double>
    std::cout << p3.first << ' ' << p3.second << '\n';

    return 0;
}
```
As you can see, the compiler generates separate class definitions for `Pair<int>` and `Pair<double>` based on the class template definition.

#### Using our class template in a function:
Now, let's go back to understand how we can make our `max()` function to support different types of `Pair` objects using our class template. Because compiler will treat `Pair<int>` and `Pair<double>` as different types, we can use function overloading to define separate `max()` functions for each type:
```cpp
constexpr int max(Pair<int> p)
{
    return (p.first < p.second ? p.second : p.first);
}

constexpr double max(Pair<double> p) // okay: overloaded function differentiated by parameter type
{
    return (p.first < p.second ? p.second : p.first);
}
```
While this compiler, it is not solving the redundancy problem. We can do better by defining `max()` as a function template that works with any type of `Pair`:
```cpp
template <typename T>
constexpr T max(Pair<T> p)
{
    return (p.first < p.second ? p.second : p.first);
}
```
This way, we only need to define the `max()` function once, and the compiler generates the appropriate version of the function based on the type of `Pair` passed to it.

Here the full example:
```cpp
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
constexpr T max(Pair<T> p)
{
    return (p.first < p.second ? p.second : p.first);
}

int main()
{
    Pair<int> p1{ 5, 6 };
    std::cout << max<int>(p1) << " is larger\n"; // explicit call to max<int>

    Pair<double> p2{ 1.2, 3.4 };
    std::cout << max(p2) << " is larger\n"; // call to max<double> using template argument deduction (prefer this)

    return 0;
}
```
You can see that is way more concise and maintainable than defining separate `max()` functions for each type of `Pair`.
The `max()` function template takes a `Pair<T>` object as a parameter and returns the larger of the two members. The compiler generates the appropriate version of the function based on the type of `Pair` passed to it.
When the `max()` function is called with a `Pair<int>` object, the compiler generates a version of `max()` that works with `Pair<int>`, namely `max<int>(Pair<int>)`. The compiler will see this:
```cpp
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
constexpr T max(Pair<T> p)
{
    return (p.first < p.second ? p.second : p.first);
}

int main()
{
    Pair<int> p1{ 5, 6 };
    std::cout << max<int>(p1) << " is larger\n"; // explicit call to max<int>

    Pair<double> p2{ 1.2, 3.4 };
    std::cout << max(p2) << " is larger\n"; // call to max<double> using template argument deduction (prefer this)

    return 0;
}
```

Regarding the function template call, we can be both implicit (calling `max(p2)`) or explicit (calling `max<int>(p1)`).

#### Class templates with template type and non-template type members:
As function templates, class templates can have both template type members and non-template type members mixed together, and it is completely fine. For example:
```cpp
template <typename T>
struct Foo
{
    T first{};    // first will have whatever type T is replaced with
    int second{}; // second will always have type int, regardless of what type T is
};
```

#### Class templates with multiple template types:
Like function templates, class templates can have multiple template parameters. For example:
```cpp
#include <iostream>

template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

template <typename T, typename U>
void print(Pair<T, U> p)
{
    std::cout << '[' << p.first << ", " << p.second << ']';
}

int main()
{
    Pair<int, double> p1{ 1, 2.3 }; // a pair holding an int and a double
    Pair<double, int> p2{ 4.5, 6 }; // a pair holding a double and an int
    Pair<int, int> p3{ 7, 8 };      // a pair holding two ints

    print(p2);

    return 0;
}
```
In this way, as we learnt with function templates, we can create class templates that can work with multiple types (here `T` and `U`).

#### Making a function template work with more than one class type:
Consider the `print()` function template from before:
```cpp
template <typename T, typename U>
void print(Pair<T, U> p)
{
    std::cout << '[' << p.first << ", " << p.second << ']';
}
```
Here, only arguments of type `Pair<T, U>` can be passed to `print()` (or those that can be implicitly converted to `Pair<T, U>`).

In some cases, we may want to make a function template that can work with more than one class type. We can achieve this by using a type template parameter as the function parameter type instead of a specific class template instantiation. For example:
```cpp
template <typename P>
void print(P p) // type template parameter will match anything
{
    std::cout << '[' << p.first << ", " << p.second << ']'; // will only compile if type has first and second members
}
```
In this way, the `print()` function template can accept any type `P` that has `first` and `second` members, not just `Pair<T, U>` objects. This makes the function template more flexible and reusable. Here is the full example:
```cpp
#include <iostream>

template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

struct Point
{
    int first{};
    int second{};
};

template <typename T>
void print(T p) // type template parameter will match anything
{
    std::cout << '[' << p.first << ", " << p.second << ']'; // will only compile if type has first and second members
}

int main()
{
    Pair<double, int> p1{ 4.5, 6 };
    print(p1); // matches print(Pair<double, int>)

    std::cout << '\n';

    Point p2 { 7, 8 };
    print(p2); // matches print(Point)

    std::cout << '\n';

    return 0;
}
```

There is one case to be careful about when using this approach. Consider this example:
```cpp
template <typename T, typename U>
struct Pair // defines a class type named Pair
{
    T first{};
    U second{};
};

template <typename Pair> // defines a type template parameter named Pair (shadows Pair class type)
void print(Pair p)       // this refers to template parameter Pair, not class type Pair
{
    std::cout << '[' << p.first << ", " << p.second << ']';
}
```
Here, we defined a class template named `Pair`, and then defined a function template with a type template parameter also named `Pair`. This shadows the class type `Pair` within the scope of the function template, meaning that inside the `print()` function template, `Pair` refers to the type template parameter, not the class type. This can lead to confusion and errors if not handled carefully.

> **Best Practice:** Stick with simple template parameter names (e.g., `T`, `U`, `Type`, etc.) to avoid shadowing class or struct type names and improve code readability.

#### `std::pair`:
The C++ Standard Library provides a class template named `std::pair` in the `<utility>` header that is similar to our `Pair` class template, since working with pairs of values is a common task in programming. `std::pair` is a general-purpose class template that can hold two values of potentially different types. Here is an example of how to use `std::pair`:
```cpp
#include <iostream>
#include <utility>

template <typename T, typename U>
void print(std::pair<T, U> p)
{
    // the members of std::pair have predefined names `first` and `second`
    std::cout << '[' << p.first << ", " << p.second << ']';
}

int main()
{
    std::pair<int, double> p1{ 1, 2.3 }; // a pair holding an int and a double
    std::pair<double, int> p2{ 4.5, 6 }; // a pair holding a double and an int
    std::pair<int, int> p3{ 7, 8 };      // a pair holding two ints

    print(p2);

    return 0;
}
```
In general, you can use `std::pair` whenever you need to work with pairs of values, instead of defining your own pair class template.

#### Using class templates in multiple files:
Like function templates, class templates are typically defined in header files, and their definitions must be available to any translation unit that uses them. This is because the compiler needs to see the full definition of the class template in order to generate the appropriate class definitions based on the template arguments used. Here is an example of how to define and use a class template in multiple files:

pair.h:
```cpp
#ifndef PAIR_H
#define PAIR_H

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
constexpr T max(Pair<T> p)
{
    return (p.first < p.second ? p.second : p.first);
}

#endif
```
foo.cpp:
```cpp
#include "pair.h"
#include <iostream>

void foo()
{
    Pair<int> p1{ 1, 2 };
    std::cout << max(p1) << " is larger\n";
}
```
main.cpp:
```cpp
#include "pair.h"
#include <iostream>

void foo(); // forward declaration for function foo()

int main()
{
    Pair<double> p2 { 3.4, 5.6 };
    std::cout << max(p2) << " is larger\n";

    foo();

    return 0;
}
```
In this example, we defined the `Pair` class template and the `max()` function template in a header file named `pair.h`. We then included this header file in both `foo.cpp` and `main.cpp`, allowing us to use the `Pair` class template and the `max()` function template in both translation units.

#### Summary:
- Class templates allow us to define blueprints for classes that can work with any data type.
- When creating objects of a class template, we must explicitly specify the template arguments (i.e., the types to be used) within angle brackets (`<>`) after the class template name.
- Class templates can have both template type members and non-template type members mixed together.
- Class templates can have multiple template parameters.
- We can make function templates work with more than one class type by using a type template parameter as the function parameter type instead of a specific class template instantiation.
- The C++ Standard Library provides a class template named `std::pair` in the `<utility>` header that can be used to work with pairs of values.
- Class templates are typically defined in header files, and their definitions must be available to any translation unit that uses them.


---

### S14 — 13.14 Class template argument deduction (CTAD) and deduction guides
#### Class template argument deduction (CTAD) (since C++17):
Starting in C++17, when instantiating an object from a class template, the compiler can deduce the template types from the constructor arguments, so you don't have to explicitly specify the template arguments. This feature is called **class template argument deduction (CTAD)**. For example:
```cpp
#include <utility> // for std::pair

int main()
{
    std::pair<int, int> p1{ 1, 2 }; // explicitly specify class template std::pair<int, int> (C++11 onward)
    std::pair p2{ 1, 2 };           // CTAD used to deduce std::pair<int, int> from the initializers (C++17)

    return 0;
}
```
In both ways (with and without explicit template arguments), the compiler generates a `std::pair<int, int>` object. In the second case, the compiler deduces the template arguments (`int` and `int`) from the types of the constructor arguments (`1` and `2`).

CTAD is only performed if no template argument list is present. SO, both of the cases below will result in errors:
```cpp
#include <utility> // for std::pair

int main()
{
    std::pair<> p1 { 1, 2 };    // error: too few template arguments, both arguments not deduced
    std::pair<int> p2 { 3, 4 }; // error: too few template arguments, second argument not deduced

    return 0;
}
```
To make it work, you should avoid using `<>` with no template arguments or providing only some of the template arguments. Instead, either provide all template arguments explicitly or let the compiler deduce them using CTAD.

Since CTAD is a form of type deduction, we can use literal suffixes to help the compiler deduce the correct types. For example:
```cpp
#include <utility> // for std::pair

int main()
{
    std::pair p1 { 3.4f, 5.6f }; // deduced to pair<float, float>
    std::pair p2 { 1u, 2u };     // deduced to pair<unsigned int, unsigned int>

    return 0;
}
```

#### Template argument deduction guides (since C++17):
In most cases, CTAD works automatically based on the constructor arguments. However, there are some cases where the compiler cannot deduce the template arguments correctly. In such cases, we will need to provide some extra help to let the compiler know how to deduce the template arguments. This is done using some **deduction guides**. A deduction guide is a special kind of declaration that tells the compiler how to deduce the template arguments based on the constructor arguments.

For example (in C++17 only), this will not compile:
```cpp
// define our own Pair type
template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

int main()
{
    Pair<int, int> p1{ 1, 2 }; // ok: we're explicitly specifying the template arguments
    Pair p2{ 1, 2 };           // compile error in C++17 (okay in C++20)

    return 0;
}
```
because CTAD does not know how to deduce the template arguemnts for aggregate class templates (like our `Pair` struct) in C++17. To fix this, we can provide a deduction guide:
```cpp
template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

// Here's a deduction guide for our Pair (needed in C++17 only)
// Pair objects initialized with arguments of type T and U should deduce to Pair<T, U>
template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;
```
First, we use the same template type definition as in our `Pair` struct: `template <typename T, typename U>`. Then, we define the deduction guide itself: `Pair(T, U) -> Pair<T, U>;`. This tells the compiler that when it sees a `Pair` object being initialized with two arguments of types `T` and `U`, it should deduce the template arguments to be `T` and `U`, resulting in a `Pair<T, U>` object.

Puttting it all together:
```cpp
template <typename T, typename U>
struct Pair
{
    T first{};
    U second{};
};

// Here's a deduction guide for our Pair (needed in C++17 only)
// Pair objects initialized with arguments of type T and U should deduce to Pair<T, U>
template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

int main()
{
    Pair<int, int> p1{ 1, 2 }; // explicitly specify class template Pair<int, int> (C++11 onward)
    Pair p2{ 1, 2 };           // CTAD used to deduce Pair<int, int> from the initializers (C++17)

    return 0;
}
```
We are telling the compiler that if it sees a declaration of `Pair` with two arguments of types `T` and `U`, it should deduce the template arguments to be `T` and `U`, resulting in a `Pair<T, U>` object.

So, when the complier sees the line `Pair p2{ 1, 2 };`, it uses the deduction guide to deduce that `T` is `int` and `U` is `int`, resulting in a `Pair<int, int>` object.

Here is a similar example:
```cpp
template <typename T>
struct Pair
{
    T first{};
    T second{};
};

// Here's a deduction guide for our Pair (needed in C++17 only)
// Pair objects initialized with arguments of type T and T should deduce to Pair<T>
template <typename T>
Pair(T, T) -> Pair<T>;

int main()
{
    Pair<int> p1{ 1, 2 }; // explicitly specify class template Pair<int> (C++11 onward)
    Pair p2{ 1, 2 };      // CTAD used to deduce Pair<int> from the initializers (C++17)

    return 0;
}
```
In this example, we defined a deduction guide that tells the compiler to deduce the template argument `T` when it sees a `Pair` object being initialized with two arguments of type `T`.

> **Note:** Non-aggregates do not need deduction guides in C++17 because the presence of a constructor serves as an implicit deduction guide.

#### Type template parameters with default values:
Like function parameters, type template parameters can also have default values. This allows us to omit the template argument when instantiating the class template, and the compiler will use the default value instead. For example:
```cpp
template <typename T=int, typename U=int> // default T and U to type int
struct Pair
{
    T first{};
    U second{};
};

template <typename T, typename U>
Pair(T, U) -> Pair<T, U>;

int main()
{
    Pair<int, int> p1{ 1, 2 }; // explicitly specify class template Pair<int, int> (C++11 onward)
    Pair p2{ 1, 2 };           // CTAD used to deduce Pair<int, int> from the initializers (C++17)

    Pair p3;                   // uses default Pair<int, int>

    return 0;
}
```
In this way, if we do not provide template arguments when instantiating the `Pair` class template, the compiler will use `int` as the default type for both `T` and `U`.

#### CTAD does not work with non-static member initialization:
CTAD does not work with class templates that use non-static member initialization, all template arguments must be specified explicitly. For example, this will not compile:
```cpp
#include <utility> // for std::pair

struct Foo
{
    std::pair<int, int> p1{ 1, 2 }; // ok, template arguments explicitly specified
    std::pair p2{ 1, 2 };           // compile error, CTAD can't be used in this context
};

int main()
{
    std::pair p3{ 1, 2 };           // ok, CTAD can be used here
    return 0;
}
```
This is because non-static member initialization occurs within the class definition, where CTAD is not applicable. Therefore, when initializing non-static members of a class template, we must explicitly specify the template arguments.

> **Recap:** Non-static member initialization happens when we provide initial values for non-static members directly within the class definition, like in the `Foo` struct above.

#### CTAD does not work with function parameters:
CTAD stand for *class* template argument deduction, not *function* template argument deduction. Therefore, CTAD cannot be used with function parameters. For example, this will not compile:
```cpp
#include <iostream>
#include <utility>

void print(std::pair p) // compile error, CTAD can't be used here
{
    std::cout << p.first << ' ' << p.second << '\n';
}

int main()
{
    std::pair p { 1, 2 }; // p deduced to std::pair<int, int>
    print(p);

    return 0;
}
```
This is because function parameters cannot use CTAD. To fix this, we need to explicitly specify the template arguments for the function parameter:
```cpp
#include <iostream>
#include <utility>

template <typename T, typename U>
void print(std::pair<T, U> p)
{
    std::cout << p.first << ' ' << p.second << '\n';
}

int main()
{
    std::pair p { 1, 2 }; // p deduced to std::pair<int, int>
    print(p);

    return 0;
}
```

#### Summary:
- Class template argument deduction (CTAD) allows the compiler to deduce template arguments from constructor arguments when instantiating objects from class templates.
- CTAD is only performed if no template argument list is present.
- Template argument deduction guides can be provided (`->`) to help the compiler deduce template arguments in cases where it cannot do so automatically.
- Type template parameters can have default values, allowing us to omit template arguments when instantiating class templates.
- CTAD does not work with non-static member initialization or function parameters; in these cases, template arguments must be specified explicitly.


---

### S15 — 13.15 Alias templates
In a previous chapter we have seen typedefs and type aliases (`using` keyword) as ways to create new names for existing types. For example:
```cpp
using IntPtr = int*; // type alias for pointer to int
typedef int* IntPtr2; // typedef for pointer to int (older syntax)
```

Creating a type alias for a class template where all template arguments are explicitly specified is straightforward. For example:
```cpp
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

template <typename T>
void print(const Pair<T>& p)
{
    std::cout << p.first << ' ' << p.second << '\n';
}

int main()
{
    using Point = Pair<int>; // create normal type alias
    Point p { 1, 2 };        // compiler replaces this with Pair<int>

    print(p);

    return 0;
}
```
In this example, we created a type alias named `Point` for `Pair<int>`, and then used `Point` to create an object of type `Pair<int>`. Such aliases can be defined locally (inside functions) or globally (at namespace scope).

#### Alias templates:
In other cases, we may want to create a type alias for a class template where some or all template arguments are not explicitly specified. In such cases, we can use **alias templates**. An alias template is a template definition for creating type aliases that can take template parameters. Here is an example:
```cpp
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

// Here's our alias template
// Alias templates must be defined in global scope
template <typename T>
using Coord = Pair<T>; // Coord is an alias for Pair<T>

// Our print function template needs to know that Coord's template parameter T is a type template parameter
template <typename T>
void print(const Coord<T>& c)
{
    std::cout << c.first << ' ' << c.second << '\n';
}

int main()
{
    Coord<int> p1 { 1, 2 }; // Pre C++-20: We must explicitly specify all type template argument
    Coord p2 { 1, 2 };      // In C++20, we can use alias template deduction to deduce the template arguments in cases where CTAD works

    std::cout << p1.first << ' ' << p1.second << '\n';
    print(p2);

    return 0;
}
```
In this example, we defined an alias template named `Coord` that takes a type template parameter `T` and creates a type alias for `Pair<T>`. We then used the `Coord` alias template to create objects of type `Pair<T>`.

There are few things that we need to keep in mind when using alias templates:
- Unlike normal aliases (that can be defined inside a block), alias templates must be defined in the global scope (as all templates).
- Prior to C++20, we must explicitly specify all template arguments when using alias templates (e.g., `Coord<int>`). Starting in C++20, we can use alias template deduction to deduce the template arguments in cases where CTAD works (e.g., `Coord p2 { 1, 2 };`).
- Because CTAD does not work on function parameters, alias template deduction also does not work on function parameters. Namely, we need to do this:
    ```cpp
    template <typename T>
    void print(const Coord<T>& c)
    {
        std::cout << c.first << ' ' << c.second << '\n';
    }
    ```
    and not this:
    ```cpp
    void print(const Coord& c) // won't work, missing template arguments
    {
        std::cout << c.first << ' ' << c.second << '\n';
    }
    ```

There is no difference if we had used `Pair` or `Pair<T>` directly instead of using the alias template `Coord`. The alias template is just a convenient way to create a new name for an existing class template with some or all template arguments specified.

#### Summary:
- Alias templates allow us to create type aliases for class templates that can take template parameters.
- Alias templates must be defined in the global scope.
- Prior to C++20, we must explicitly specify all template arguments when using alias templates. Starting in C++20, we can use alias template deduction to deduce the template arguments in cases where CTAD works.


---

### SX - 13.x Summary and quiz
Have a look at the original summary, and enjoy doing the quiz!

PS: solutions are inside `exercises/sx-questions` folder. Enjoy! :)


---

## 🧾 Chapter Summary
C++ allows you to create **program-defined types** such as structs, enums, and class templates.  
Enums define a type whose values are symbolic constants (enumerators). Unscoped enums implicitly convert to integers and place their enumerators in the surrounding scope, while scoped enums (`enum class`) avoid implicit conversions and keep enumerators within the enum’s scope.

Structs allow bundling multiple related variables into a single compound type. These data members are accessed through the dot operator (for objects and references) or the arrow operator (for pointers). Structs with only data members are considered aggregates and support aggregate initialization, letting you initialize each member directly using braces.  
C++20 adds **designated initializers**, allowing explicit mapping of initializers to members.

Structs can also have **default member initializers**, providing fallback values when members aren’t explicitly initialized.  
Because of alignment requirements, the compiler may add **padding** inside structs, influencing their final size.

The chapter also introduces **class templates**, which allow defining generic struct/class types. Thanks to CTAD (C++17), template parameters can often be deduced automatically from initializers.

### 🧱 Core Concepts You Mastered:
- **Program-defined types**: Custom types created using enums, structs, classes, and unions.

- **Enumerations**  
  - *Unscoped enums*: enumerators injected into outer scope, implicitly convert to integers.  
  - *Scoped enums (`enum class`)*: strongly typed, scoped enumerators, no implicit conversions.

- **Structs**: Bundles of related variables (data members), accessed via `.` or `->`.

- **Aggregates & Initialization**  
  - Memberwise initialization using braces.  
  - C++20 designated initializers for clearer initialization.

- **Default Member Initializers**: Built-in fallback values for struct members.

- **Padding & Memory Layout**: Extra gaps inserted by the compiler to satisfy alignment constraints.

- **Class Templates & CTAD**: Generic class/struct definitions where types may be deduced automatically from initialization.