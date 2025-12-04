# Chapter 14 - Introduction to Classes

## 🧭 Overview

In this chapter you met the core abstraction tool of C++: **classes**.  
You moved from thinking in terms of free functions operating on data (procedural style) to **object‑oriented programming (OOP)**, where data and behavior are bundled together with clear interfaces, invariants, and construction rules.

---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch14_first
./build/ch14_first
```

---

## 🎯 Learning outcomes

By the end of this chapter, you should be able to:

- Explain the difference between *procedural* and *object‑oriented* design in C++.
- Define a `class` with data members and member functions, and understand the idea of a **class invariant**.
- Use **public / private** access control to design a clean **public interface** and hide implementation details.
- Write and use **constructors**, including default, delegating, and copy constructors, and use **member initializer lists** correctly.
- Recognize when a member function should be marked **`const`** and call such functions on const objects.
- Understand how **aggregate initialization** differs from class initialization and why non‑aggregate classes need constructors.
- Describe what **copy elision** is and how it relates to the **as‑if rule**.
- Control **implicit conversions** with converting constructors and the `explicit` keyword.
- Understand that member functions (including constructors) can be `constexpr` and what that implies.

---

## Sections

### S01 — 14.1 Introduction to object-oriented programming
#### Procedural programming:
In **procedural programming**, the focus is on writing procedures or functions that operate on data. The data and functions are separate, and the program is structured around these procedures (which in C++ are called functions). This will reasult in something like this:
```cpp
eat(you, apple);
```

We previously defined **objects** as "pieces of memory that can be used to store values", and **variables** as "named objects". In procedural programming, data is typically stored in variables, and functions operate on these variables. Objects have two main components:
- Some number of associated properties (e.g., weight, color, size, etc.)
- Some number of associated behaviors (e.g., eat, sleep, run, etc.)

In programming, properties are typically represented by objects, and behaviors are represented by functions. And so, procedural programming separates data (objects/variables) and functions (behaviors), representing the reality poorly.

#### Object-oriented programming:
In **object-oriented programming (OOP)**, the focus is on creating objects that encapsulate both data and behaviors. This leads to code similar to this:
```cpp
you.eat(apple);
```

OOP makes clearer the relationship between data and behaviors, as behaviors are associated with the objects they operate on, stating clearly who is the subject and who is the object of the action. Since there is no more this separation between data and behaviors, OOP allows for better organization of code, making it easier to understand, maintain, and extend.

#### A procedural vs OOP-like example:
Here is a short program in procedural style that print the name and the number of legs of an animal:
```cpp
#include <iostream>
#include <string_view>

enum AnimalType
{
    cat,
    dog,
    chicken,
};

constexpr std::string_view animalName(AnimalType type)
{
    switch (type)
    {
    case cat: return "cat";
    case dog: return "dog";
    case chicken: return "chicken";
    default:  return "";
    }
}

constexpr int numLegs(AnimalType type)
{
    switch (type)
    {
    case cat: return 4;
    case dog: return 4;
    case chicken: return 2;
    default:  return 0;
    }
}


int main()
{
    constexpr AnimalType animal{ cat };
    std::cout << "A " << animalName(animal) << " has " << numLegs(animal) << " legs\n";

    return 0;
}
```
In this example, we have two separate functions (`animalName` and `numLegs`) that operate on the same data type (`AnimalType`). The relationship between the data and the functions is not explicit, making it harder to understand the code. For example, imagine we want to add a new animal type `snake`. We would need to modify both functions and add the new type to the `AnimalType` enum.

In contrast, here is a similar program written in an OOP-like style (not yet there, but getting closer):
```cpp
#include <iostream>
#include <string_view>

struct Cat
{
    std::string_view name{ "cat" };
    int numLegs{ 4 };
};

struct Dog
{
    std::string_view name{ "dog" };
    int numLegs{ 4 };
};

struct Chicken
{
    std::string_view name{ "chicken" };
    int numLegs{ 2 };
};

int main()
{
    constexpr Cat animal;
    std::cout << "a " << animal.name << " has " << animal.numLegs << " legs\n";

    return 0;
}
```
In this case, each animal has its own program-defined type (struct) that encapsulates both the data (name and number of legs). The relationship between the data and the behaviors is more explicit, making it easier to understand the code. If we want to add a new animal type `Snake`, we can simply define a new struct for it without modifying existing code.

You can easily see, that this code has a lot of repetition, but what if you want to add a new member to a specific animal (e.g., `sound`)? You would need to modify each struct, leading to code duplication and maintenance challenges. This is where classes and other OOP concepts come into play, allowing us to define a common structure and behavior for all animals, and restricting some members to just specific animals (this is called inheritance and access control, which we will see later).

#### OOP brings other benefits on the table:
OOP brings other benefits, such as:
- **Encapsulation**: Bundling data and methods that operate on that data within a single unit (class), restricting direct access to some of the object's components.
- **Abstraction**: Hiding complex implementation details and exposing only the necessary parts of an object.
- **Inheritance**: Creating new classes based on existing ones, promoting code reuse and establishing hierarchical relationships.
- **Polymorphism**: Allowing objects of different classes to be treated as objects of a common superclass, enabling a single interface to represent different underlying forms (data types).

We will explore these concepts in the upcoming sections.

#### The term "objeect":
Note that in OOP, the term "object" has a slightly different meaning than what we have seen so far. In OOP, an object is an instance of a class that encapsulates both data (attributes/properties) and behaviors (methods/functions). Objects are created based on the blueprint provided by a class, and they can interact with each other through their methods.

> **Note:** We will favour the traditional meaning of "object" (i.e., piece of memory that can store values) throughout this chapter, referring to OOP object as "class object".

#### Summary:
- **Procedural programming** separates data and functions, leading to less organized code.
- **Object-oriented programming (OOP)** encapsulates data and behaviors within objects, improving code organization and maintainability.
- OOP introduces concepts like **encapsulation**, **abstraction**, **inheritance**, and **polymorphism** that enhance code structure and reusability.
- The term "object" in OOP refers to instances of classes that encapsulate both data and behaviors.


---

### S02 — 14.2 Introduction to classes
In the previous chapter we have seen how `struct` can be used to group related data together. Consider the following example:
```cpp
#include <iostream>

struct Date
{
    int day{};
    int month{};
    int year{};
};

void printDate(const Date& date)
{
    std::cout << date.day << '/' << date.month << '/' << date.year; // assume DMY format
}

int main()
{
    Date date{ 4, 10, 21 }; // initialize using aggregate initialization
    printDate(date);        // can pass entire struct to function

    return 0;
}
```
In the above example, we defined a `Date` struct to group together related data (day, month, year). We also defined a function `printDate` that takes a `Date` struct as an argument and prints it in a specific format. This will output:
```
4/10/21
```

However, what if we want to add functionality to the `Date` struct, such as adding days, months, or years? We would need to define separate functions for each operation, leading to code duplication and maintenance challenges. This is where classes come into play. Classes allow us to define both data and behaviors within a single unit, promoting better organization and encapsulation.

Now, we will analyze the problem that `struct` has when used in this way, and how classes can help us solve it.

#### The class invariant problem:
One of the biggest problems that structs have is that they do not provide an effective way to document and enforce **class invariants**. In a previous chapter, we defined **invariants** as *a condition that must be true while some component is executing*. A **class invariant** is a condition that must always be true for all instances of a class (or struct, or union), throughout their lifetime, in order for the object to remain in a valid state. An object that violates its class invariant is considered to be in an **invalid state**, and using such an object can lead to undefined behavior, errors, or unexpected results.

Let us consider the following struct `Pair`, which represents a pair of integers:
```cpp
struct Pair
{
    int first {};
    int second {};
};
```
The `first` and `second` members of the `Pair` struct can take any integer values, so `Pair` has no invariants.

Now, consider this example:
```cpp
struct Fraction
{
    int numerator { 0 };
    int denominator { 1 };
};
```
In this case, we have a `Fraction` struct that represents a mathematical fraction. A key invariant for fractions is that the denominator must never be zero, as division by zero is undefined. However, since `Fraction` is defined as a simple struct, there is no way to enforce this invariant. A user of the `Fraction` struct could inadvertently set the denominator to zero, leading to an invalid state. For example:
```cpp
#include <iostream>

struct Fraction
{
    int numerator { 0 };
    int denominator { 1 }; // class invariant: should never be 0
};

void printFractionValue(const Fraction& f)
{
     std::cout << f.numerator / f.denominator << '\n';
}

int main()
{
    Fraction f { 5, 0 };   // create a Fraction with a zero denominator
    printFractionValue(f); // cause divide by zero error

    return 0;
}
```
In this example, we create a `Fraction` object with a zero denominator, violating the class invariant. When we attempt to print the value of the fraction, it results in a divide-by-zero error, leading to undefined behavior.

#### A more complex class invariant:
The class invariant problem can become even more complex when dealing with multiple related members. Consider the following `Eployee` struct:
```cpp
#include <string>

struct Employee
{
    std::string name { };
    char firstInitial { }; // should always hold first character of `name` (or `0`)
};
```
In the above (poorly designed) struct, we have a class invariant that states that `firstInitial` should always hold the first character of `name` (or be `0` if `name` is empty). However, since `Employee` is defined as a simple struct, there is no way to enforce this invariant. A user of the `Employee` struct could inadvertently set `name` and `firstInitial` to inconsistent values, leading to an invalid state. In general, replying on the user to maintain class invariants is error-prone and can lead to bugs!

Ideally, we would like to ensure that the object cannot be put into an invalid state, or at least it signals an error when that happens. Structs (as aggregates) do not have the capability to enforce such invariants, as they allow direct access to their members.

> **Note:** While it is possible to enforce class invariants using functions that operate on structs, this approach is error-prone and relies on the user to always use those functions correctly. Classes provide a more robust solution by encapsulating data and behaviors, allowing us to enforce invariants more effectively.

#### Introduction to classes:
When developing C++, Bjarne Stroustrup wanted to introduce capabilities that would allow developers to create program-defined types that could be used more intuitively.
To achieve this, he introduced the concept of **classes**. Just as structs, a **class** is a program-defined compund type that can have many member variables with different types. However, classes go beyond structs by allowing us to define member functions (also called **methods**) that operate on the data within the class. This encapsulation of data and behaviors within a single unit promotes better organization, maintainability, and the ability to enforce class invariants.

#### Defining a class:
In C++, a class is defined using the `class` keyword, followed by the class name and a pair of curly braces that enclose the class members. Here is an example of defining a simple class `Employee`:
```cpp
class Employee
{
    int m_id {};
    int m_age {};
    double m_wage {};
};
```
In this example, we defined a class `Employee` with three member variables: `m_id`, `m_age`, and `m_wage`. The `m_` prefix is a common convention used to indicate that these variables are member variables of the class.

To show how similar structs and classes are, here a previous `Date` struct rewritten as a class:
```cpp
#include <iostream>

class Date       // we changed struct to class
{
public:          // and added this line, which is called an access specifier
    int m_day{}; // and added "m_" prefixes to each of the member names
    int m_month{};
    int m_year{};
};

void printDate(const Date& date)
{
    std::cout << date.m_day << '/' << date.m_month << '/' << date.m_year;
}

int main()
{
    Date date{ 4, 10, 21 };
    printDate(date);

    return 0;
}
```
This prints the same output as before:
```
4/10/21
```
In this example, we changed the `Date` struct to a class by replacing the `struct` keyword with `class`. We also added the `public:` access specifier to indicate that the member variables are accessible from outside the class. Finally, we added the `m_` prefix to each member variable name to follow the common convention for member variables.

#### Most of the C++ standard library is classes:
It is worth noting that most of the C++ standard library is implemented using classes. For example, both `std::string` and `std::string_view` are classes that encapsulate string data and provide various member functions to manipulate and access that data. Similarly, containers like `std::vector`, `std::list`, and `std::map` are all implemented as classes, providing a rich set of functionalities for managing collections of data.

Classes are so at the center of C++, that originally it was called "C with classes"!

#### Summary:
- Structs have limitations when it comes to enforcing class invariants, as they allow direct access to their members.
- Classes provide a way to encapsulate data and behaviors within a single unit, promoting better organization and maintainability.
- Classes allow us to define member functions (methods) that operate on the data within the class, enabling us to enforce class invariants more effectively.
- Most of the C++ standard library is implemented using classes, showcasing their importance in C++ programming.


---

### S03 — 14.3 Member functions
In a previous section, we have seen that we can use structs to group related data together. However, structs do not provide a way to define behaviors (functions) that operate on that data. For example, we need to define separate functions to manipulate the data in a struct, leading to code duplication and maintenance challenges:
```cpp
#include <iostream>

struct Date
{
    // here are our member variables
    int year {};
    int month {};
    int day {};
};

void print(const Date& date)
{
    // member variables accessed using member selection operator (.)
    std::cout << date.year << '/' << date.month << '/' << date.day;
}

int main()
{
    Date today { 2020, 10, 14 }; // aggregate initialize our struct

    today.day = 16; // member variables accessed using member selection operator (.)
    print(today);   // non-member function accessed using normal calling convention

    return 0;
}
```
This in not ideal, as the relationship between the data and the functions is not explicit, making it harder to understand and maintain the code. To solve this problem, C++ introduces the concept of **member functions** (also called **methods**), which are functions that are defined within a class and operate on the data of that class.

#### The separation of properties and actions:
In proghramming, we represent properties with variables, and actions with functions. In OOP, we group related properties and actions together within a class. In the example before with `Date` struct, this was handled separately, meaning that we had to define functions that operated on the struct from the outside. With member functions, we can define actions that operate on the data within the class itself, leading to better organization and encapsulation.

#### Membder functions:
In addition to member variables, classes can also have **member functions** (also called **Methods** in other OO languages like Java or C#). Member functions are functions that are defined within a class and operate on the data of that class. Member functions must be declared inside the class definition, and they can be defined either inside or outside the class definition (a definition is also a declaration).

To keep things simple, we will define our member functions inside the class definition for now.

#### A member function example:
Let's modify our previous `Date` example to include a member function that prints the date:
```cpp
// Member function version
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() // defines a member function named print
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // aggregate initialize our struct

    today.day = 16; // member variables accessed using member selection operator (.)
    today.print();  // member functions also accessed using member selection operator (.)

    return 0;
}
```
This will output:
```
2020/10/16
```
As you can see, to define a member function, we simply declare it inside the class definition. In this case, we defined a member function named `print` that prints the date in a specific format. To call the member function, we use the member selection operator (`.`) on an instance of the class (in this case, `today.print()`).

There are three main differences between the non-member and member example:
1. **Where** we declared (and define) the `print` function: in the non-member example, it was declared outside the `Date` struct, while in the member example, it was declared inside the `Date` struct.
2. **How** we **call** the `print` function: in the non-member example, we called it using the normal function calling convention (`print(today)`), while in the member example, we called it using the member selection operator (`today.print()`).
3. **How** the member function **accesses** the member variables: in the non-member example, we accessed the member variables using the member selection operator (`date.year`, `date.month`, `date.day`), while in the member example, we accessed them directly by their names (`year`, `month`, `day`).

Let's exlore each of this in turn.

#### Member function are declared inside the class type definition:
In the non-member example, the `print` function was declared outside the `Date` struct, in the global namespace. By default it has external linkage, so it could be called from other translation units (source files).

In the member example, the `print` function is declared inside the `Date` struct. This means that the `print` function is a member of the `Date` class, and it can only be called on instances of the `Date` class. Member function defined inside the class type definition are implicitly `inline`, so they will not violate the one-definition rule if included in multiple translation units.

#### Calling member function (and the implicit object):
In the non-member example, we called the `print` function using the normal function calling convention, passing the `today` object as an argument: `print(today)`.

In the member example, we called the `print` function using the member selection operator (`.`) on the `today` object: `today.print()`. When we call a member function in this way, the object on which the function is called (`today` in this case) is implicitly passed to the member function as a special parameter called `this`. The `this` pointer is a hidden parameter that points to the object on which the member function was called, so we will not need to pass it explicitly. The object that a member function is called on is often referred to as the **implicit object**.

#### Accessing members inside a member function uses the implicit object:
Here is the non-member example again:
```cpp
// non-member version of print
void print(const Date& date)
{
    // member variables accessed using member selection operator (.)
    std::cout << date.year << '/' << date.month << '/' << date.day;
}
```
This version has reference parameter `const Date& date`, which is used to access the member variables of the `Date` struct using the member selection operator (`.`). When `print(today)` is called, the `date` parameters is bound to the `today` object, allowing us to access its member variables.

Now, let us look at the member function version again:
```cpp
void print() // defines a member function named print()
{
    std::cout << year << '/' << month << '/' << day;
}
```
In this version, we do not have any parameters. Instead, we access the member variables directly by their names (`year`, `month`, `day`). This is because the member function has access to the implicit object (`this`), which points to the object on which the member function was called. Therefore, when we access `year`, `month`, and `day`, we are actually accessing `this->year`, `this->month`, and `this->day`.

#### ANother member function example:
Here is another example that demonstrates member functions:
```cpp
#include <iostream>
#include <string>

struct Person
{
    std::string name{};
    int age{};

    void kisses(const Person& person)
    {
        std::cout << name << " kisses " << person.name << '\n';
    }
};

int main()
{
    Person joe{ "Joe", 29 };
    Person kate{ "Kate", 27 };

    joe.kisses(kate);

    return 0;
}
```
This outputs:
```
Joe kisses Kate
```
In this example, we defined a `Person` struct with two member variables (`name` and `age`) and a member function (`kisses`). The `kisses` member function takes another `Person` object as a reference parameter and prints a message indicating that the implicit object (the person calling the function) kisses the other person.

#### Member variables and functions can be defined in any order:
The C++ compiler normally compile the code from top to bottom. For each name encountered, the compiler determines whether it has already seen a declaration for that name. If it has, it can use that declaration to determine the type of the name (type checking). If it has not, it will generate an error.

Non-members must be declared before they can be used, or the compiler will complain about an unknown name:
```cpp
int x()
{
    return y(); // error: y not declared yet, so compiler doesn't know what it is
}

int y()
{
    return 5;
}
```
For example here, the compiler will generate an error because `y` is used before it is declared.

However, inside a class definition, member variables and member functions can be defined in any order. This is because the entire class definition is considered as a single scope, and the compiler will see all member declarations before it processes any of them. Therefore, you can define member functions before or after member variables, and they can refer to each other without any issues:
```cpp
struct Foo
{
    int z() { return m_data; } // We can access data members before they are defined
    int x() { return y(); }    // We can access member functions before they are defined

    int m_data { y() };        // This even works in default member initializers (see warning below)
    int y() { return 5; }
};
```
We discuss a recommended order for member variables and functions later in this chapter.

> **Warning:** Data members are initialized in order of declaration. If the initialization of a data acccesses another data member that is not yet initialized, the behavior is undefined. For example, in the above code, `m_data` is initialized using the `y()` member function, which is fine because `y()` does not access any uninitialized members. However, if `y()` were to access another member that has not yet been initialized, it would lead to undefined behavior.

#### Member functions can be overlaoded:
Just like non-member functions, member functions can be **overloaded**, so long as each member function can ve differentiated by its parameter list (number and/or types of parameters). Here is an example:
```cpp
#include <iostream>
#include <string_view>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print()
    {
        std::cout << year << '/' << month << '/' << day;
    }

    void print(std::string_view prefix)
    {
        std::cout << prefix << year << '/' << month << '/' << day;
    }
};

int main()
{
    Date today { 2020, 10, 14 };

    today.print(); // calls Date::print()
    std::cout << '\n';

    today.print("The date is: "); // calls Date::print(std::string_view)
    std::cout << '\n';

    return 0;
}
```
This prints:
```
2020/10/14
The date is: 2020/10/14
```
In this example, we defined two member functions named `print` with different parameter lists. The first `print` function takes no parameters and prints the date, while the second `print` function takes a `std::string_view` parameter and prints the date with a prefix. When we call `today.print()`, the compiler determines which version of the `print` function to call based on the arguments provided.

#### Structs and member functions:
In C, structs cannot have member functions, they only have member variables. However, in C++, structs can have member functions, just like classes. The only difference between structs and classes in C++ is the default access level: in structs, members are `public` by default, while in classes, members are `private` by default. Other than that, structs and classes are functionally equivalent in C++.

> **Best Practice:** Member functions can be used with both structs and classes in C++. However, it is generally recommended to use classes when defining types that encapsulate both data and behaviors, as classes provide better support for encapsulation and access control (which we will see later). Structs are typically used for simple data structures that primarily hold data without complex behaviors.

#### Class types with no data members:
It is possible to create class types without data members, containing only member functions. Such class types can be useful for grouping related functions together, providing a namespace-like functionality. Here is an example:
```cpp
#include <iostream>

struct Foo
{
    void printHi() { std::cout << "Hi!\n"; }
};

int main()
{
    Foo f{};
    f.printHi(); // requires object to call

    return 0;
}
```

However, if a class does not have any data members, it is often more appropriate to use a namespace instead. Namespaces provide a way to group related functions together without the need to create an object to call them. Here is the same example using a namespace:
```cpp
#include <iostream>

namespace Foo
{
    void printHi() { std::cout << "Hi!\n"; }
};

int main()
{
    Foo::printHi(); // no object needed

    return 0;
}
```

> **Best Practice:** Use namespaces to group related functions together when there is no need for data members. This avoids the unnecessary overhead of creating objects and makes the code cleaner and more efficient.

#### Summary:
- Member functions (methods) are functions defined within a class that operate on the data of that class.
- Member functions are declared inside the class type definition and can be defined either inside or outside the class definition.
- Member functions are called using the member selection operator (`.`) on an instance of the class, with the implicit object being passed as a hidden parameter (`this`).
- Inside member functions, member variables can be accessed directly by their names, as they are accessed through the implicit object.
- Member functions can be overloaded based on their parameter lists.


---

### S04 — 14.4 Const class objects and const member functions
In. aprevious chapter, you have seen that objects of fundamental data types can be made `const`, meaning that their values cannot be modified after initialization.
```cpp
const int x;      // compile error: not initialized
const int y{};    // ok: value initialized
const int z{ 5 }; // ok: list initialized
z = 10;           // compile error: cannot modify a const object
```
Similarly, class objects can also be made `const`, meaning that their member variables cannot be modified after initialization. Such objects must also be initialized at the time of creation.
```cpp
struct Date
{
    int year {};
    int month {};
    int day {};
};

int main()
{
    const Date today { 2020, 10, 14 }; // const class type object
    today.day = 16;                    // compile error: cannot modify member of const object
    return 0;
}
```
In this example, we created a `const` object of type `Date` named `today`. When we try to modify the `day` member of the `today` object, the compiler generates an error, as we cannot modify members of a `const` object.

#### Modifing the data members of const objects is disallowed:
As shown in the previous example, attempting to modify the member variables of a `const` class object results in a compile-time error. This is because `const` objects are read-only, and any attempt to modify their state violates the `const` qualifier. For example:
```cpp
struct Date
{
    int year {};
    int month {};
    int day {};

    void incrementDay()
    {
        ++day;
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.day += 1;        // compile error: can't modify member of const object
    today.incrementDay();  // compile error: can't call member function that modifies member of const object

    return 0;
}
```

#### Const objects may not call non-const member functions:
This code:
```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print()
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.print();  // compile error: can't call non-const member function

    return 0;
}
```
will also generate a compile-time error when we try to call the `print` member function on the `const` object `today`. This is because the `print` function is not marked as `const`, and therefore cannot be called on a `const` object.

> **Note:** By default, member functions are non-`const`, meaning they can modify the state of the object. To allow a member function to be called on `const` objects, we need to explicitly mark it as `const`.

#### Const member functions:
To fix the above issue, we can mark the `print` member function as `const` by adding the `const` qualifier after the parameter list:
```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() const // now a const member function
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.print();  // ok: const object can call const member function

    return 0;
}
```
Now, the `print` member function is marked as `const` (it is a **const member function**), allowing it to be called on `const` objects. Inside a `const` member function, we are not allowed to modify any member variables of the object, as doing so would violate the `const` qualifier.

A const member function that attempts to modify a member variable will result in a compile-time error:
```cpp
struct Date
{
    int year {};
    int month {};
    int day {};

    void incrementDay() const // made const
    {
        ++day; // compile error: const function can't modify member
    }
};

int main()
{
    const Date today { 2020, 10, 14 }; // const

    today.incrementDay();

    return 0;
}
```
In this example, the `incrementDay` member function is marked as `const`, but it attempts to modify the `day` member variable. This results in a compile-time error, as `const` member functions cannot modify the state of the object.

Const member functions can modify non-members (such as local variables and function parameters) and call non-member functions per usual. The const only applies to members.

#### Const member functions may be called on non-const objects:
Const member function can also be called on non-`const` objects. This is because non-`const` objects can be treated as `const` objects when calling `const` member functions. For example:
```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() const // const
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // non-const

    today.print();  // ok: can call const member function on non-const object

    return 0;
}
```

> **Best Practice:** It is a good practice to mark member functions that do not modify the state of the object as `const`. This allows them to be called on both `const` and non-`const` objects, improving code flexibility and safety.

#### Const objects via pass by const reference:
Although instantiating const local variables is one way to create const objects, a more common way to get a const object is by passing an object to a function by const reference. This is a common practice to avoid unnecessary copying of objects while ensuring that the function does not modify the original object. For example:
```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() // non-const
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

void doSomething(const Date& date)
{
    date.print();
}

int main()
{
    Date today { 2020, 10, 14 }; // non-const
    today.print();

    doSomething(today);

    return 0;
}
```
In this example, the `doSomething` function takes a `const Date&` parameter, meaning that it receives a reference to a `const` `Date` object. Inside the function, we can only call `const` member functions on the `date` parameter, since it is treated as a `const` object. If we try to call a non-`const` member function on the `date` parameter (like in this case with `print`), the compiler will generate an error.

We can fix this by marking the `print` member function as `const`:
```cpp
#include <iostream>

struct Date
{
    int year {};
    int month {};
    int day {};

    void print() const // now const
    {
        std::cout << year << '/' << month << '/' << day;
    }
};

void doSomething(const Date& date)
{
    date.print();
}

int main()
{
    Date today { 2020, 10, 14 }; // non-const
    today.print();

    doSomething(today);

    return 0;
}
```
In this way, the `print` member function is marked as `const`, allowing it to be called on the `const` `date` parameter inside the `doSomething` function.

#### Member function const and non-const overloading:
Finally, even though it is not done very often, it is possible to overload a member function to have a `const` and a non-`const` version. The compiler will determine which version to call based on the constness of the object on which the member function is called. For example:
```cpp
#include <iostream>

struct Something
{
    void print()
    {
        std::cout << "non-const\n";
    }

    void print() const
    {
        std::cout << "const\n";
    }
};

int main()
{
    Something s1{};
    s1.print(); // calls print()

    const Something s2{};
    s2.print(); // calls print() const

    return 0;
}
```
This will output:
```
non-const
const
```
In this example, we defined two versions of the `print` member function: one non-`const` and one `const`. When we call `s1.print()`, the non-`const` version is called, while when we call `s2.print()`, the `const` version is called.

This is pretty rare, but it can be useful in some situations where you want to provide different behavior for `const` and non-`const` objects.

#### Summary:
- Class objects can be made `const`, preventing modification of their member variables after initialization.
- Attempting to modify member variables of a `const` object results in a compile-time error.
- `const` objects can only call `const` member functions, which are marked with the `const` qualifier after the parameter list.
- `const` member functions cannot modify the state of the object, and attempting to do so results in a compile-time error.
- `const` member functions can be called on both `const` and non-`const` objects.
- Passing objects by `const` reference is a common way to create `const` objects in functions.
- Member functions can be overloaded to have both `const` and non-`const` versions, allowing different behavior based on the constness of the object.


---

### S05 — 14.5 Public and private members and access specifiers
In this section, we will explore how to control access to the members of a class using **access specifiers**. Access specifiers allow us to define the visibility and accessibility of class members (both member variables and member functions) from outside the class. The two most common access specifiers in C++ are `public`, `private`, and `protected`.

#### Member access:
Each member of a class has a specific **access level**, which determines who can access that member. There are three access levels in C++:
1. **Public**: Members declared as `public` can be accessed from anywhere in the program, both inside and outside the class.
2. **Private**: Members declared as `private` can only be accessed from within the class itself. They cannot be accessed from outside the class using the member selection operator (`.`).
3. **Protected**: Members declared as `protected` can be accessed from within the class itself and from derived classes (subclasses), but not from outside the class.

Whenever a member is access, the compiler check if the access level of that member permits the access. If the access level does not permit the access, the compiler generates an error. This is also known as **access control**.

#### The members of a struct are public by default:
In C++, the members of a `struct` are `public` by default. **Public members** are members of a class type that do not have any restrictions on how they can be accessed. This means that they can be accessed from anywhere in the program (public), both inside and outside the class, as long as they are in scope. For example:
```cpp
#include <iostream>

struct Date
{
    // struct members are public by default, can be accessed by anyone
    int year {};       // public by default
    int month {};      // public by default
    int day {};        // public by default

    void print() const // public by default
    {
        // public members can be accessed in member functions of the class type
        std::cout << year << '/' << month << '/' << day;
    }
};

// non-member function main is part of "the public"
int main()
{
    Date today { 2020, 10, 14 }; // aggregate initialize our struct

    // public members can be accessed by the public
    today.day = 16; // okay: the day member is public
    today.print();  // okay: the print() member function is public

    return 0;
}
```
In this example, members are accessed in three different places:
1. Inside the `print` member function of the `Date` struct (`year`, `month`, `day`).
2. Inside the `main` function, which is a non-member function (`today.day`).
3. When calling the `print` member function from `main` (`today.print()`).

All three of these accesses are valid because the members of a `struct` are `public` by default, and they can be accessed from anywhere in the program.

#### The members of a class are private by default:
In contrast to `structs`, the members of a `class` are `private` by default. **Private members** are members of a class type that can **only** be accessed by other members of the same class type (including member functions). They cannot be accessed from outside the class (public) using the member selection operator (`.`). For example:
```cpp
#include <iostream>

class Date // now a class instead of a struct
{
    // class members are private by default, can only be accessed by other members
    int m_year {};     // private by default
    int m_month {};    // private by default
    int m_day {};      // private by default

    void print() const // private by default
    {
        // private members can be accessed in member functions
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }
};

int main()
{
    Date today { 2020, 10, 14 }; // compile error: can no longer use aggregate initialization

    // private members can not be accessed by the public
    today.m_day = 16; // compile error: the m_day member is private
    today.print();    // compile error: the print() member function is private

    return 0;
}
```
In this example, we changed the `Date` struct to a `class`. As a result, the members of the `Date` class are now `private` by default. This means that they can only be accessed from within the class itself. When we try to access the `m_day` member and the `print` member function from the `main` function, the compiler generates errors, as they are `private` and cannot be accessed from outside the class (`main` is the public).

Perhaps surprisingly, a third compilation error is generated: when we initialize `today`. In a previous chapter we said that "an aggregate can have no private or protected non-static data members". This means that since `Date` is now a class with private members, it is no longer an aggregate, and therefore cannot be initialized using aggregate initialization.

> **Note 1:** The default access level for members of a `struct` is `public`, while the default access level for members of a `class` is `private`. This is a key difference between `structs` and `classes` in C++.

> **Note 2:** When a class have private members, it is no more an aggregate, and therefore cannot be initialized using aggregate initialization.

#### Naming your private member variables:
A common convention when naming private member variables is to use the `m_` prefix (short for "member"). This convention helps to distinguish member variables from local variables and function parameters, making the code easier to read and understand. For example:
```cpp
// Some member function that sets private member m_name to the value of the name parameter
void setName(std::string_view name)
{
    m_name = name;
}
```
In this example, we have a member function `setName` that takes a parameter named `name` and assigns its value to the private member variable `m_name`. The `m_` prefix makes it clear that `m_name` is a member variable, while `name` is a local parameter.

So this convetions helps us to:
- Differentiate member variables from local variables and function parameters.
- Prevent naming conflicts between member variables and local variables or function parameters.

> **Best Practice:** Use the `m_` prefix for private member variables to improve code readability and avoid naming conflicts.

#### Setting access levels via access specifiers:
As we said, by default, members of a `struct` are `public`, while members of a `class` are `private`. However, we can explicitly set the access level of members using **access specifiers**. Access specifiers are keywords that define the access level of **all** the member that follow them, until the next access specifier or the end of the class definition. The three access specifiers in C++ are:
- `public:`: Members declared after this specifier are `public` and can be accessed from anywhere in the program.
- `private:`: Members declared after this specifier are `private` and can only be accessed from within the class itself.
- `protected:`: Members declared after this specifier are `protected` and can be accessed from within the class itself and from derived classes.

Here is an example that demonstrates the use of access specifiers:
```cpp
class Date
{
// Any members defined here would default to private

public: // here's our public access specifier

    void print() const // public due to above public: specifier
    {
        // members can access other private members
        std::cout << m_year << '/' << m_month << '/' << m_day;
    }

private: // here's our private access specifier

    int m_year { 2020 };  // private due to above private: specifier
    int m_month { 14 }; // private due to above private: specifier
    int m_day { 10 };   // private due to above private: specifier
};

int main()
{
    Date d{};
    d.print();  // okay, main() allowed to access public members

    return 0;
}
```
In this example, we defined a `Date` class with both `public` and `private` members:
- The `print` member function is declared after the `public:` access specifier, making it `public` and accessible from outside the class. It means that we can call `d.print()` from the `main` function.
- The member variables `m_year`, `m_month`, and `m_day` are declared after the `private:` access specifier, making them `private` and only accessible from within the class itself. This means that we cannot access them directly from the `main` function.

Note that because we have private members, we cannot aggregate initialize the `Date` object `d` in `main`. In this example we used default member initialization instead, as a temporary workaround (we will see better ways to initialize private members later in this chapter).

Since classes default to private access, if we had omitted the `private:` access specifier, the member variables would still be `private`. However, it is a good practice to explicitly specify the access level of members using access specifiers for clarity and maintainability.

#### Access level summary:
Here is a simple table that summarizes the access levels of class members based on their access specifiers:
| Access level | Access specifier | Member access | Derived class access | Public access |
|--------------|------------------|---------------|----------------------|---------------|
| Public       | public:          | Yes           | Yes                  | Yes           |
| Protected    | protected:       | Yes           | Yes                  | No            |
| Private      | private:         | Yes           | No                   | No            |

#### Access level best practices for structs and classes:
In general, **structs** should avoid access specifiers all together, as they are primarily intended for simple data structures with public members. We want our structs to be aggregates, and they can only have public members. So, in general, avoid using access specifiers in structs.

**Classes**, on the other hand, should generally only have private (or protected) data memebrs, either by using the default private access level or by explicitly specifying `private:` or `protected:` access specifiers. Classes normally have public memebr functions, so that they can be used by the public after object is created. This encapsulation of data and behavior is a key principle of object-oriented programming, and it helps to ensure that the internal state of the class is protected from unintended modifications. Sometimes, some member functions are made private or protected, in case they are not intended to be used by the public.

> **Best Practice:** Avoid using access specifiers in structs to maintain their aggregate nature. For classes, prefer private (or protected) data members and public member functions to encapsulate data and behavior effectively.

#### Access levels work on a per-class basis:
Access levels are enforced on a per-class basis, not on a per-object basis. This means that the access level of a member is determined by the class type, not by the specific object being accessed. For example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Person
{
private:
    std::string m_name{};

public:
    void kisses(const Person& p) const
    {
        std::cout << m_name << " kisses " << p.m_name << '\n';
    }

    void setName(std::string_view name)
    {
        m_name = name;
    }
};

int main()
{
    Person joe;
    joe.setName("Joe");

    Person kate;
    kate.setName("Kate");

    joe.kisses(kate);

    return 0;
}
```
This will output:
```
Joe kisses Kate
```
In this example, the `Person` class has a private member variable `m_name`. The `kisses` member function is `public` and can be called from outside the class. Inside the `kisses` function, we access the private member `m_name` of both the implicit object (`this->m_name`) and the `p` parameter (`p.m_name`). Since `p` is of type `Person`, the `kisses` function is allowed to access its private member `m_name` (of the same class type), even though `p` is a different object.

> **Note:** Access levels are determined by the class type, not by the specific object being accessed. Members of the same class type can access each other's private members.

#### The technical and practical difference between structs and classes:
Technically, the only difference between `structs` and `classes` in C++ is the default access level of their members: `struct` members are `public` by default, while `class` members are `private` by default. Other than that, they are functionally equivalent.

Practically, however, there is a strong convention in C++ programming structs and classes usage. As a general rule of thumb, use a **structs** when all of the following are true:
- You have a simple collection of data that does not benefit from restricting access to its members.
- Aggregate initialization is desired/sufficient.
- You have no class invariants (rules that must always be true for the data members), setup needs, or cleanup needs.

Use a **class** otherwise.

#### Summary:
- Access specifiers (`public:`, `private:`, `protected:`) control the visibility and accessibility of class members.
- Members of a `struct` are `public` by default, while members of a `class` are `private` by default.
- `public` members can be accessed from anywhere in the program.
- `private` members can only be accessed from within the class itself.
- `protected` members can be accessed from within the class and from derived classes.
- It is a common convention to use the `m_` prefix for private member variables to improve code readability.
- Access levels are enforced on a per-class basis, allowing members of the same class type to access each other's private members.


---

### S06 — 14.6 Access functions
Consider the following `Date` example:
```cpp
#include <iostream>

class Date
{
private:
    int m_year{ 2020 };
    int m_month{ 10 };
    int m_day{ 14 };

public:
    void print() const
    {
        std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
    }
};

int main()
{
    Date d{};  // create a Date object
    d.print(); // print the date

    return 0;
}
```
Yhis class allows the user to print the date, but it does not allow the user for example to print the year only, or to modify the date. This will not allow since the member variables are private. In some cases, it can be nice and good to have more control over how the member variables are accessed and modified. This is where **access functions** (also known as **getter** and **setter** functions) come into play.

#### Access functions:
An **acess function** is a trivial public member function whose job is to get (read) or set (modify) the value of a private member variable. Access functions provide a controlled way to access and modify private member variables from outside the class, while still maintaining encapsulation and data integrity.

Access function are of two types:
1. **Getter functions**: These are public member functions that return the value of a private member variable. They are used to read the value of a private member variable from outside the class. They are also acalled **accessors**.
2. **Setter functions**: These are public member functions that take a parameter and set the value of a private member variable. They are used to modify the value of a private member variable from outside the class. They are also called **mutators**, and they should generally be non-`const`.

Here our updated example with access functions:
```cpp
#include <iostream>

class Date
{
private:
    int m_year { 2020 };
    int m_month { 10 };
    int m_day { 14 };

public:
    void print()
    {
        std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
    }

    int getYear() const { return m_year; }        // getter for year
    void setYear(int year) { m_year = year; }     // setter for year

    int getMonth() const  { return m_month; }     // getter for month
    void setMonth(int month) { m_month = month; } // setter for month

    int getDay() const { return m_day; }          // getter for day
    void setDay(int day) { m_day = day; }         // setter for day
};

int main()
{
    Date d{};
    d.setYear(2021);
    std::cout << "The year is: " << d.getYear() << '\n';

    return 0;
}
```
This will output:
```
The year is: 2021
```
In this example, we added getter and setter functions for each of the private member variables (`m_year`, `m_month`, `m_day`). The getter functions (`getYear`, `getMonth`, `getDay`) return the value of the corresponding member variable, while the setter functions (`setYear`, `setMonth`, `setDay`) set the value of the corresponding member variable. This allows controlled access to the private member variables from outside the class.

> **Best Practice:** Use access functions to provide controlled access to private member variables. This allows you to enforce class invariants, validate input, and maintain encapsulation.

#### Access function naming:
There is no common convention for naming access functions, but there are few common patterns:
- Prefix with `get` for getters and `set` for setters (e.g., `getYear`, `setYear`). In this way you make clear that these functions are access functions.
- No prefix in both cases (e.g., `year()`, `year(int)`). This is a more concise approach, but it may be less clear that these functions are access functions.
- `set` prefix only for setters (e.g., `year()`, `setYear(int)`). This is a compromise between the two previous approaches.

#### Getters should return by value or by const lvalue reference:
Getters should provide **read-only** access data members. Therefore, they should return either by value or by `const` lvalue reference. Returning by value is generally preferred for fundamental data types (like `int`, `double`, etc.) and small structs, as it avoids potential issues with dangling references. Returning by `const` lvalue reference can be used for larger objects to avoid unnecessary copying, but care must be taken to ensure that the returned reference remains valid.

Since this is non trivial as it seems, we will cover this topic in more detail later in the chapter.

#### Access functions concerns:
While access functions provide a way to access and modify private member variables, they can also introduce some concerns:
- **Encapsulation violation**: Excessive use of access functions can lead to a violation of encapsulation, as they expose the internal state of the class to the outside world. This can make it difficult to maintain and modify the class in the future.
- **Class invariants**: Access functions can make it difficult to enforce class invariants, as they allow direct modification of member variables. It is important to ensure that access functions validate input and maintain class invariants.
- **Increased complexity**: Adding access functions can increase the complexity of the class, making it harder to understand and maintain.

For now, we recommend the following best practices:
- If your class has no invariants and requires a lot of access functions, consider using a `struct` with public members instead.
- Prefer implementing behaviors or actions instead of access functions. For example, instead of a `setAlive(bool)` setter, prefer a `kill()` or `resurrect()` member function.
- Only provide access functions in cases where the public would reasonably expect to be able to access or modify the member variable.

#### Summary:
- Access functions (getters and setters) provide controlled access to private member variables.
- Getter functions return the value of a private member variable, while setter functions modify the value of a private member variable.
- Getters should return by value or by `const` lvalue reference.
- Access functions should be used judiciously to maintain encapsulation and enforce class invariants.


---

### S07 — 14.7 Member functions returning references to data members
In a previous chapter we noted that *"an objecct returned by reference must exist after the function call completes"*. This means that **we should not return local variables (which go out of scope when the function ends) by reference**. However, it is generally safe to return by reference function parameter passed by reference, or variables with static duration (either static local variables or global variables), as they will generally outlive the function call. For example:
```cpp
// Takes two std::string objects, returns the one that comes first alphabetically
const std::string& firstAlphabetical(const std::string& a, const std::string& b)
{
	return (a < b) ? a : b; // We can use operator< on std::string to determine which comes first alphabetically
}

int main()
{
	std::string hello { "Hello" };
	std::string world { "World" };

	std::cout << firstAlphabetical(hello, world); // either hello or world will be returned by reference

	return 0;
}
```
Here it is safe to return either `a` or `b` by reference, since they are function parameters passed by reference, and therefore will outlive the function call.

**Member functions** they can also return by reference, and they follow the same rules as regular functions. However, member functions have an additional case: member functions that return **data members** by reference. This is usually seen in getter access functions, but it is in general possible in any member function.

This is generally safe, since data members of class objects will generally outlive the member function call, as long as the object itself outlives the member function call. But let's see in more details.

#### Returning data members by value can be expensive:
Consider the following example:
```cpp
#include <iostream>
#include <string>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	std::string getName() const { return m_name; } //  getter returns by value
};

int main()
{
	Employee joe{};
	joe.setName("Joe");
	std::cout << joe.getName();

	return 0;
}
```
In this example, the `getName` member function returns the `m_name` data member of type `std::string` by value. This means that when we call `joe.getName()`, a copy of the `m_name` string is created and returned. For small data types (like `int`, `double`, etc.), returning by value is generally fine, but for larger objects (like `std::string`), returning by value can be expensive in terms of performance, as it involves copying the entire object. Especially due to the fact that access function will generally be called often, and we want to avoid unnecessary copies that will slow down our program.

#### Returning data members by lvalue reference:
Member functions can also return data members by **(const) lvalue reference**. Data members have the same lifetime as the object they belong to. Since member functions are always called on an object, the data members will generally outlive the member function call, as long as the object itself outlives the member function call. Therefore, it is generally safe to return data members by lvalue reference from member functions. Let's update the example above to return `m_name` by `const` lvalue reference:
```cpp
#include <iostream>
#include <string>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	const std::string& getName() const { return m_name; } //  getter returns by const reference
};

int main()
{
	Employee joe{}; // joe exists until end of function
	joe.setName("Joe");

	std::cout << joe.getName(); // returns joe.m_name by reference

	return 0;
}
```
Now, the `getName` member function returns the `m_name` data member by `const` lvalue reference. This means that when we call `joe.getName()`, we get a reference to the `m_name` string, rather than a copy of it. This avoids the overhead of copying the string, improving performance. The `const` qualifier ensures that the caller cannot modify the `m_name` string through the returned reference, maintaining encapsulation.

> **Note:** The `const` qualifier in the return type of the `getName` function is important, as it prevents the caller from modifying the `m_name` string through the returned reference. This helps to maintain encapsulation and data integrity.

> **Best Practice:** When returning data members from member functions, prefer returning by `const` lvalue reference for larger objects to avoid unnecessary copies, while ensuring that the returned reference remains valid.

#### The return type of a member function returning a reference to a data member should match the data member type:
When a member function returns a reference to a data member, the return type of the member function should match the type of the data member. For example, if a data member is of type `std::string`, the member function should return a `std::string&` or `const std::string&`. Mismatched types can lead to compilation errors or undefined behavior.

For getters, using `auto` to have the compiler deduce the return type from the member being returned is a good way to ensure that the return type matches the data member type. For example:
```cpp
#include <iostream>
#include <string>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	const auto& getName() const { return m_name; } // uses `auto` to deduce return type from m_name
};

int main()
{
	Employee joe{}; // joe exists until end of function
	joe.setName("Joe");

	std::cout << joe.getName(); // returns joe.m_name by reference

	return 0;
}
```
However, using `auto` return type obscures the return type of the getter from a documentation perspective. Therefore, it is often better to explicitly specify the return type of the getter, especially in public APIs. For example:
```cpp
const auto& getName() const { return m_name; } // uses `auto` to deduce return type from m_name
```
it does not clearly specify which exactly string type returns (it could be `std::string`, `std::string_view`, or any other string-like type).

> **Best Practice:** Ensure that the return type of member functions returning references to data members matches the type of the data member. Prefer explicit return types for clarity, especially in public APIs.

#### Rvalue implicit objects and return by reference:
There is a case where we need to be careful when returning data members by reference: when the member function is called on an rvalue implicit object (temporary object). In this case, the data members of the temporary object will be destroyed at the end of the full expression, which means that returning a reference to a data member of a temporary object will result in a dangling reference. For example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
	std::string m_name{};

public:
	void setName(std::string_view name) { m_name = name; }
	const std::string& getName() const { return m_name; } //  getter returns by const reference
};

// createEmployee() returns an Employee by value (which means the returned value is an rvalue)
Employee createEmployee(std::string_view name)
{
	Employee e;
	e.setName(name);
	return e;
}

int main()
{
	// Case 1: okay: use returned reference to member of rvalue class object in same expression
	std::cout << createEmployee("Frank").getName();

	// Case 2: bad: save returned reference to member of rvalue class object for use later
	const std::string& ref { createEmployee("Garbo").getName() }; // reference becomes dangling when return value of createEmployee() is destroyed
	std::cout << ref; // undefined behavior

	// Case 3: okay: copy referenced value to local variable for use later
	std::string val { createEmployee("Hans").getName() }; // makes copy of referenced member
	std::cout << val; // okay: val is independent of referenced member

	return 0;
}
```
When `createEmployee()` is called, it will return an `Employee` object by value, which is a temporary rvalue object. 

In Case 1, we immediately use the returned reference to the `m_name` member of the temporary object in the same expression, which is safe, since the returned value is still alive during the full expression.

In case 2, we have some issues. First, `createEmployee("Garbo")` returns a temporary rvalue object. We then call `getName()` on that temporary object, which returns a reference to the `m_name` member of the temporary object. However, since the temporary object is destroyed at the end of the full expression, the returned reference becomes a dangling reference. When we try to use `ref` later, it results in undefined behavior. 

We could instead copy the referenced value to a local variable, as shown in Case 3. This way, we create a copy of the `m_name` member, which is independent of the temporary object, and we can safely use it later. Since we use a non-reference local variable (`val`), the returned reference value will be copied into `val`, and `val` will remain valid even after the temporary object is destroyed.

#### Using member functions that return by reference safely:
Despite the potential danger with rvalue implicit objects, it is conventional for getters to return types that are expensive to copy by const reference, not by value. Let's explore how we can do that safely:
- Prefer to use the return value of a member function that returns by reference immediately (case 1 above). This will work for both lvalue and rvalue implicit objects.
- Do not "save" a returned reference to use later (case 2), unless you are sure the implicit object is an lvalue (i.e., it has a name and a longer lifetime).
- If you do need to persist a returned reference for use later and you are not sure the object is an lvalue, using the returned reference as an initializer for a non-reference local variable (case 3) is a safe way to do so, as it will create a copy of the referenced value.

> **Best Practice:** Prefer to use the return value of a member function that returns by reference immediately.

#### Do not return non-const references to private data members:
Because a reference acts just like the object being referenced, a member function that returns a non-`const` reference to a private data member would allow the caller to modify that private data member directly, bypassing any encapsulation or validation logic that the class might have. This can lead to unintended side effects, violations of class invariants, and maintenance challenges. Therefore, it is generally considered a bad practice to return non-`const` references to private data members. For example:
```cpp
#include <iostream>

class Foo
{
private:
    int m_value{ 4 }; // private member

public:
    int& value() { return m_value; } // returns a non-const reference (don't do this)
};

int main()
{
    Foo f{};                // f.m_value is initialized to default value 4
    f.value() = 5;          // The equivalent of m_value = 5
    std::cout << f.value(); // prints 5

    return 0;
}
```
Because the member function returns a non-const reference, the caller can modify the private data member directly, which breaks encapsulation and can lead to maintenance challenges.

> **Best Practice:** Avoid returning non-`const` references to private data members to maintain encapsulation and data integrity.

#### Const member functions cannot return non-const references to data members:
A `const` member function is not allowed to modify the state of the object it is called on. Therefore, it cannot return a non-`const` reference to a data member, as doing so would allow the caller to modify the data member, violating the `const`-ness of the member function. For example:
```cpp
#include <iostream>

class Foo
{
private:
    int m_value{ 4 }; // private member
public:
    int& value() const { return m_value; } // compile error: cannot return non-const reference from const member function
};

int main()
{
    Foo f{};
    std::cout << f.value();

    return 0;
}
```
In this example, the `value` member function is declared as `const`, but it attempts to return a non-`const` reference to the `m_value` data member. This results in a compilation error, as it violates the `const`-ness of the member function.

Remind that when a member function is declared as `const`, it means that the function promises not to modify the state of the object it is called on. Therefore, it can only return `const` references to data members, or return by value.

#### Summary:
- Member functions can return data members by reference, which is generally safe as long as the object outlives the member function call.
- Returning data members by `const` lvalue reference is preferred for larger objects to avoid unnecessary copies.
- The return type of a member function returning a reference to a data member should match the type of the data member.
- Be cautious when returning references to data members from member functions called on rvalue implicit objects, as it can lead to dangling references.


---

### S08 — 14.8 The benefits of data hiding (encapsulation)
In a previous section, we said that one of the main reasons to use classes is to **hide** data members from the public, exposing them only through public member functions. This concept is known as **data hiding** or **encapsulation**. In this section, we will explore the benefits of data hiding in more detail.

You can think about this as an electronic device, like a smartphone. The internal components of the smartphone (like the processor, memory, etc.) are hidden from the user, who interacts with the smartphone through a user interface (like the touchscreen). This allows the user to use the smartphone without needing to understand its internal workings.

This separation of **interface** and **implementation** is extremely useful because it allows the implementation to change without affecting the interface. For example, a smartphone manufacturer can change the internal components of the smartphone (like upgrading the processor) without changing the user interface. This allows for easier maintenance and upgrades.

#### Implementation and interfaces in class types:
The **interface** of a class (also called **class interface**) defines how a user of the class type will ijnteract with objects of that class type. Because only public members can be accessed from outside the class, the interface of a class is defined by its public members (both data members and member functions). This is sometimes called the **public interface** of the class.

The **implementation** of a class consist of the code that actually makes the class behave as intended. This includes the private members of the class (both data members and member functions), as well as the code inside the public member functions. The implementation is hidden from the user of the class, who only interacts with the class through its public interface.

#### Data hiding:
In programming, **data hiding** (or **information hiding** or **data abstraction**) is a technique used to enforce the separation of interface and implementation by making data members private, and exposing them only through public member functions. This allows the class to control how its data members are accessed and modified, ensuring that the internal state of the class remains consistent and valid.

Implementing data hiding in C++ class types is simple. First, we ensure the data members of the class are private (either by using the default private access level of classes, or by explicitly specifying the `private:` access specifier). Then, we provide public member functions (like access functions) to allow controlled access to the private data members. 

By following these rules, we force the user to interact with the class only through its public interface, which allows us to maintain control over the internal state of the class. This will increase code maintainability, as we can change the implementation of the class without affecting the interface.

#### Encapsulation:
In programming, the term **encapsulation** typically referes to one of the two related concepts:
- The enclosing of one or more items within a container of some kind. For example, a class encapsulates its data members and member functions.
- The bunding of data and the methods that operate on that data within a single unit, such as a class. This helps to keep related data and behavior together, making the code easier to understand and maintain.

#### Data hiding make classes easier to use, and reduces complexity:
To use an encampsulated class, the user only needs to understand its public interface, which is typically much smaller and simpler than the entire implementation of the class. This reduces the cognitive load on the user, making it easier to use the class correctly. For example:
```cpp
#include <iostream>
#include <string_view>

int main()
{
    std::string_view sv{ "Hello, world!" };
    std::cout << sv.length();

    return 0;
}
```
In this example, we use the `std::string_view` class from the C++ Standard Library. The user of the `std::string_view` class only needs to understand its public interface (like the `length` member function) to use it effectively. The internal implementation of the `std::string_view` class is hidden from the user, which reduces complexity and makes it easier to use.

#### Data hiding allows us to mantain class invariants:
As a reminder, class invariants are rules that must always be true for the data members of a class throughout the lifetime of the class object. Consider the following example:
```cpp
#include <iostream>
#include <string>

struct Employee // members are public by default
{
    std::string name{ "John" };
    char firstInitial{ 'J' }; // should match first initial of name

    void print() const
    {
        std::cout << "Employee " << name << " has first initial " << firstInitial << '\n';
    }
};

int main()
{
    Employee e{}; // defaults to "John" and 'J'
    e.print();

    e.name = "Mark"; // change employee's name to "Mark"
    e.print(); // prints wrong initial

    return 0;
}
```
This prints:
```
Employee John has first initial J
Employee Mark has first initial J
```
In this example, we have an `Employee` struct with two public data members: `name` and `firstInitial`. The `firstInitial` member is supposed to match the first initial of the `name` member. However, since both members are public, the user can modify them independently, leading to a violation of the class invariant (the `firstInitial` no longer matches the first initial of the `name`).

When we give the users direct access to the implementation of a class, they become their responsibility to maintain any class invariants. This can lead to bugs and inconsistencies in the code. Let's fix this by encapsulating the `Employee` class:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee // members are private by default
{
    std::string m_name{};
    char m_firstInitial{};

public:
    void setName(std::string_view name)
    {
        m_name = name;
        m_firstInitial = name.front(); // use std::string::front() to get first letter of `name`
    }

    void print() const
    {
        std::cout << "Employee " << m_name << " has first initial " << m_firstInitial << '\n';
    }
};

int main()
{
    Employee e{};
    e.setName("John");
    e.print();

    e.setName("Mark");
    e.print();

    return 0;
}
```
In this updated example, we encapsulated the `Employee` class by making its data members private and providing a public member function `setName` to set the employee's name. The `setName` function also updates the `m_firstInitial` member to ensure that it always matches the first initial of the `m_name` member. This way, we maintain the class invariant, and the user cannot violate it by directly modifying the data members.

#### Data hiding allows us to do better error detection (and handling):
In the previous example, the invariant that `m_firstInitial` must match the first initial of `m_name` exists only because `m_firstInitial` exists indipendently of `m_name`. We can remove this class invariant by replacing data member `m_firstInitial` with a member function that returns the initial on demand:
```cpp
#include <iostream>
#include <string>

class Employee
{
    std::string m_name{ "John" };

public:
    void setName(std::string_view name)
    {
        m_name = name;
    }

    // use std::string::front() to get first letter of `m_name`
    char firstInitial() const { return m_name.front(); }

    void print() const
    {
        std::cout << "Employee " << m_name << " has first initial " << firstInitial() << '\n';
    }
};

int main()
{
    Employee e{}; // defaults to "John"
    e.setName("Mark");
    e.print();

    return 0;
}
```
In this way, we eliminate the class invariant altogether, since `firstInitial()` always returns the first initial of `m_name`, and there is no risk of inconsistency between two separate data members.

This program though has another class invariant: the employee's name should not be empty. If we try to call the `firstInitial()` function when the name is empty, it will result in undefined behavior. We would like to prevent this sitation.

If the user had public access to `m_name` directly, they could set `name = ""`, and we would have no way to prevent that. But since `m_name` is private, and the user only has access to it through the `setName` member function, we can add validation logic to the `setName` function to ensure that the name is not empty. If the name is an empty string, we can do one of the following:
- Ignore the request to set the name to an empty string and return the caller.
- Assert out.
- Throw an exception.

So, we can handle it as we think is better for our application.

#### Data hiding makes it possible to change implementation details without breaking existing programs:
Consider this example:
```cpp
#include <iostream>

struct Something
{
    int value1 {};
    int value2 {};
    int value3 {};
};

int main()
{
    Something something;
    something.value1 = 5;
    std::cout << something.value1 << '\n';
}
```
While this works fine, what if we want to change the implementation of the class like this:
```cpp
#include <iostream>

struct Something
{
    int value[3] {}; // uses an array of 3 values
};

int main()
{
    Something something;
    something.value1 = 5;
    std::cout << something.value1 << '\n';
}
```
This will not compile, since `value1` is no longer a member of the `Something` struct. Any existing code that uses the `Something` struct will break if we change its implementation like this.

Instead, data hiding gives us the ability to change how classes are implemented without affecting the code that uses them. For example we can start from this:
```cpp
#include <iostream>

class Something
{
private:
    int m_value1 {};
    int m_value2 {};
    int m_value3 {};

public:
    void setValue1(int value) { m_value1 = value; }
    int getValue1() const { return m_value1; }
};

int main()
{
    Something something;
    something.setValue1(5);
    std::cout << something.getValue1() << '\n';
}
```
and modify it to this:
```cpp
#include <iostream>

class Something
{
private:
    int m_value[3]; // note: we changed the implementation of this class!

public:
    // We have to update any member functions to reflect the new implementation
    void setValue1(int value) { m_value[0] = value; }
    int getValue1() const { return m_value[0]; }
};

int main()
{
    // But our programs that use the class do not need to be updated!
    Something something;
    something.setValue1(5);
    std::cout << something.getValue1() << '\n';
}
```
In this example, we changed the implementation of the `Something` class to use an array to store the values instead of separate member variables. However, since the public interface of the class (the `setValue1` and `getValue1` member functions) remained the same, any existing code that uses the `Something` class does not need to be updated. This allows us to change the implementation of the class without breaking existing programs.

So basically, we can change public member functions as needed to reflect changes in the implementation, while keeping the public interface the same. This allows us to maintain backward compatibility with existing code that uses the class.

> **Best Practice:** Use data hiding to encapsulate class implementation details, allowing for easier maintenance and evolution of the class without breaking existing code.

#### Classes with interfaces are easier to debug:
Finally, encapsulation can help with debugging. When a class encapsulates its data members and exposes them only through public member functions, it becomes easier to track down bugs related to the internal state of the class. This is because any changes to the internal state of the class must go through the public member functions, which can include validation logic and error handling. This makes it easier to identify where the bug is occurring and to fix it.

For example, if a specific member variable can only be chnaged in one single member function, we could place a breakpoint just there, and we will make our job easier.

#### Prefer non-member function to member functions:
In C++, if a function can be implemented as a non-member function, prefer the non-member implementation over the member one. This has numerous benefits:
- Non-member functions are not part of the interface of your class, and it will keeep your interface small and clean.
- Non-member functions enforce encapsulation, there is no tentation to access the members at all.
- Non-member functions tend to be easier to debug.
- Non-member functions containing application-specific data and logic can be seprated from the reusable portions of the class.

If you know C# or Jave, this might surprise you, sicne these languages put member functions at the center of their language, and in fact Jave and C# do not even support non-memeber functions.

> **Best Practice:** Prefer non-member function implementation when possible (especially functions that contain application specific data or logic).

Let's see this with three similar examples (from worst to best).

Worst version:
```cpp
#include <iostream>
#include <string>

class Yogurt
{
    std::string m_flavor{ "vanilla" };

public:
    void setFlavor(std::string_view flavor)
    {
        m_flavor = flavor;
    }

    const std::string& getFlavor() const { return m_flavor; }

    // Worst: member function print() uses direct access to m_flavor when getter exists
    void print() const
    {
        std::cout << "The yogurt has flavor " << m_flavor << '\n';
    }
};

int main()
{
    Yogurt y{};
    y.setFlavor("cherry");
    y.print();

    return 0;
}
```
This is the worst version, since the `print` member function accesses the private data member `m_flavor` directly, even though a getter function `getFlavor` exists. This breaks encapsulation and makes it harder to maintain the class.

Better version:
```cpp
#include <iostream>
#include <string>

class Yogurt
{
    std::string m_flavor{ "vanilla" };

public:
    void setFlavor(std::string_view flavor)
    {
        m_flavor = flavor;
    }

    const std::string& getFlavor() const { return m_flavor; }

    // Better: member function print() has no direct access to members
    void print(std::string_view prefix) const
    {
        std::cout << prefix << ' ' << getFlavor() << '\n';
    }
};

int main()
{
    Yogurt y{};
    y.setFlavor("cherry");
    y.print("The yogurt has flavor");

    return 0;
}
```
This is a better version, since the `print` member function uses the `getFlavor` getter function to access the private data member `m_flavor`. This maintains encapsulation and makes it easier to maintain the class. This is still not great, since `print()` is a member function, and it is part of the class interface.

Best version:
```cpp
#include <iostream>
#include <string>

class Yogurt
{
    std::string m_flavor{ "vanilla" };

public:
    void setFlavor(std::string_view flavor)
    {
        m_flavor = flavor;
    }

    const std::string& getFlavor() const { return m_flavor; }
};

// Best: non-member function print() is not part of the class interface
void print(const Yogurt& y)
{
        std::cout << "The yogurt has flavor " << y.getFlavor() << '\n';
}

int main()
{
    Yogurt y{};
    y.setFlavor("cherry");
    print(y);

    return 0;
}
```
This is the best version, since the `print` function is a non-member function that uses the `getFlavor` getter function to access the private data member `m_flavor`. This keeps the class interface small and clean, maintains encapsulation, and makes it easier to maintain the class. In this way, each application can provide its own `print` function as needed, without cluttering the class interface.

#### The order of class member declaration:
When writing code outside of a class definition, we need to declare variables and functions before we can use them. However, inside a class definition, the order of member declaration does not matter. This is because the entire class definition is processed before any member functions are compiled. Therefore, member functions can access data members and other member functions regardless of their order of declaration within the class.

So, how should we order them? There are two different approaches:
1. List your private members first, and then list your public member functions. This follows traditional style of declare-before-use, possibly making reading and understanding the class easier.
2. List your public members first, and then list your private members. This is because someone is looking at a class is likely more interested in its public interface than its private implementation details.

In modern C++, the second approach (public members first) is generally preferred, as it emphasizes the class interface and makes it easier for users to understand how to interact with the class.

> **Best Practice:** When defining a class, list public members first, protected members second, and private members last to emphasize the class interface.

#### Summary:
- Data hiding (encapsulation) is a technique used to enforce the separation of interface and implementation by making data members private and exposing them only through public member functions.
- Data hiding makes classes easier to use, reduces complexity, helps maintain class invariants, allows for better error detection and handling, enables implementation changes without breaking existing code, and simplifies debugging.
- Prefer non-member functions over member functions when possible to keep class interfaces small and clean.
- When defining a class, list public members first, protected members second, and private members last to emphasize the class interface.

---

### S09 — 14.9 Introduction to constructors
When a class type is an aggregate, we can use aggregate initialization to initialize the class type directly:
```cpp
struct Foo // Foo is an aggregate
{
    int x {};
    int y {};
};

int main()
{
    Foo foo { 6, 7 }; // uses aggregate initialization

    return 0;
}
```
This allows us to initialize the data members of the class directly when creating an object of that class type.

However, as soon as we make the class non-aggregate (for example, by adding a private data member or a user-defined constructor), we can no longer use aggregate initialization:
```cpp
class Foo // Foo is not an aggregate (has private members)
{
    int m_x {};
    int m_y {};
};

int main()
{
    Foo foo { 6, 7 }; // compile error: can not use aggregate initialization

    return 0;
}
```

Not allowing aggregate initialization for non-aggregate makes sense because:
- Aggregate initialization requires knowing about the implementation of the class (the data members), which breaks encapsulation.
- If your class have some kind of class invariants, aggregate initialization would allow the user to violate those invariants by initializing the data members directly.

So, how can we initialize non-aggregate class types? The answer is **constructors**.

#### Constructors:
A **constructor** is a special member function of a class that is automatically called after a non-aggregate class type object is created. The purpose of a constructor is to initialize the data members of the class and perform any other setup required for the object to be in a valid state.

When a non-aggregate class type object is defined, the compiler looks to see if it can find an accessible constructor that matches the way the object is being created. 
- If it finds a matching constructor, it allocates memory for the object and then calls the constructor to initialize the object.
- If it does not find a matching constructor, it results in a compilation error.

Beyond determining how an object may be cretaed, a constructor does two functions:
1. It typically performs initialization of any member variable (via member initializer list or assignment in the constructor body).
2. It may perform any other setup required for the object to be in a valid state. For example, it may perform error checking, allocate resources, or register the object with some kind of manager.

After the constructor run, we say that the object has been **constructed**.

> **Note:** Aggregates are not allowed to have constructors. If you need to initialize an aggregate, you must use aggregate initialization.

#### Naming constructors:
Unlike normal member functions, constructors have specific rules for their names:
- The name of a constructor must match the name of the class exactly, including capitalization. For template classes, this name excludes the template parameters.
- Constructors do not have a return type, not even `void`. This is because constructors do not return a value; they simply initialize the object.

#### A basic constructor example:
Let's add a constructor to the example of before:
```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y) // here's our constructor function that takes two initializers
    {
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo{ 6, 7 }; // calls Foo(int, int) constructor
    foo.print();

    return 0;
}
```
It will print:
```
Foo(6, 7) constructed
Foo(0, 0)
```
In this example,when the compiler sees the line `Foo foo{ 6, 7 };`, it looks for a constructor in the `Foo` class that takes two `int` parameters. It finds the constructor `Foo(int x, int y)`, allocates memory for the `foo` object, and then calls the constructor to initialize the object. The constructor prints a message indicating that the object has been constructed. However, note that the data members `m_x` and `m_y` are not initialized in the constructor, so they remain at their default values of `0`. We will see how to initialize data members in the next section.

#### Constructor implicit conversion of arguments:
In a previous chapter we noticed that compiler will perform implicit conversions on function arguments when needed. The same applies to constructor arguments. For example:
```cpp
class Foo
{
public:
    Foo(int x, int y)
    {
    }
};

int main()
{
    Foo foo{ 'a', true }; // will match Foo(int, int) constructor

    return 0;
}
```
Here the compiler will implicitly convert the `char` argument `'a'` to an `int` (with value `97`), and the `bool` argument `true` to an `int` (with value `1`), in order to match the `Foo(int, int)` constructor.

#### Constructors should not be const:
A constructor needs to be able to initialize the object being constructed. Therefore, it cannot be declared as `const`, since a `const` member function promises not to modify the state of the object it is called on. Declaring a constructor as `const` would prevent it from being able to initialize the object, which defeats the purpose of the constructor. For example:
```cpp
#include <iostream>

class Something
{
private:
    int m_x{};

public:
    Something() // constructors must be non-const
    {
        m_x = 5; // okay to modify members in non-const constructor
    }

    int getX() const { return m_x; } // const
};

int main()
{
    const Something s{}; // const object, implicitly invokes (non-const) constructor

    std::cout << s.getX(); // prints 5

    return 0;
}
```
In this example, the `Something` class has a non-`const` constructor that initializes the `m_x` data member to `5`. The constructor is able to modify the state of the object being constructed, which is necessary for proper initialization.

#### Constructors versus setters:
Constructors are designed to initialize the entire object at the time of its creation, ensuring that the object is in a valid state from the moment it is created. Setters, on the other hand, are member functions that allow modification of individual data members after the object has been created.

#### Summary:
- A constructor is a special member function of a class that is automatically called after a non-aggregate class type object is created.
- The purpose of a constructor is to initialize the data members of the class and perform any other setup required for the object to be in a valid state.
- Constructors must have the same name as the class and do not have a return type.
- Constructors should not be declared as `const`, as they need to modify the state of the object being constructed.


---

### S10 — 14.10 Constructor member initializer list
This lesson will continue our discussion of constructors by exploring how to initialize data members of a class using a **member initializer list**.

#### Member initialization via a member initialization list:
A **member initializer list** is a special syntax used in the definition of a constructor to initialize data members of a class before the constructor body is executed. The member initializer list is specified after the constructor's parameter list and before the constructor body, using a colon (`:`) followed by a comma-separated list of member initializations. For example:
```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y)
        : m_x { x }, m_y { y } // here's our member initialization list
    {
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo{ 6, 7 };
    foo.print();

    return 0;
}
```
This will print:
```
Foo(6, 7) constructed
Foo(6, 7)
```
In this example, the member initializer list `: m_x { x }, m_y { y }` initializes the data members `m_x` and `m_y` with the values of the constructor parameters `x` and `y`, respectively. This ensures that the data members are properly initialized before the constructor body is executed.

#### Member initializer list formatting:
C++ provides a lot of freedom to format member initializer lists. Here are some common formatting styles:
- All on one line:
    ```cpp
    Foo(int x, int y) : m_x { x }, m_y { y }
    {
    }
    ```
- Each member on its own line (version 1):
    ```cpp
    Foo(int x, int y) :
        m_x { x },
        m_y { y }
    {
    }
    ```
- Each member on its own line (version 2):
    ```cpp
    Foo(int x, int y)
        : m_x { x }
        , m_y { y }
    {
    }
    ```

Our recommendation is to use the third style, as it makes it easy to add or remove members from the initializer list without needing to modify commas on other lines. So, basically:
- Put the colon `:` on the line after the constructor parameters.
- Put each member initialization on its own line, starting with a comma `,`, and indented.

#### Member initialization order:
C++ initializes data members in the order they are declared in the class definition, not in the order they appear in the member initializer list. For example:
```cpp
#include <iostream>
class Foo
{
private:
    int m_x {};
    int m_y {};
public:
    Foo(int x, int y)
        : m_y { y }, m_x { x } // initializer list order is m_y, m_x
    {
    }
    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};
int main()
{
    Foo foo{ 6, 7 };
    foo.print();

    return 0;
}
```
This will print:
```
Foo(6, 7)
```
In this example, even though `m_y` appears before `m_x` in the member initializer list, `m_x` is initialized first because it is declared first in the class definition (`private: int m_x {}; int m_y {};`). This is important to remember, especially when one data member depends on another for its initialization.

Consider the following example:
```cpp
#include <algorithm> // for std::max
#include <iostream>

class Foo
{
private:
    int m_x{};
    int m_y{};

public:
    Foo(int x, int y)
        : m_y { std::max(x, y) }, m_x { m_y } // issue on this line
    {
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo { 6, 7 };
    foo.print();

    return 0;
}
```
This will print:
```
Foo(-858993460, 7)
```
In this example, `m_x` is initialized with the value of `m_y`, but since `m_x` is declared before `m_y`, it is initialized first. At the time `m_x` is initialized, `m_y` has not yet been initialized, leading to undefined behavior. To fix this, we need to ensure that `m_y` is declared before `m_x` in the class definition.

To prevent this, we should always list data members in the class definition in the order they should be initialized. Additiuonally, it is a good practice to avoid dependencies between data members during initialization (if possible).

> **Best Practice:** Always declare data members in the class definition in the order they should be initialized.

#### Member initializer list versus default member initializers:
Members can be initialized in different ways:
- If a member is listed in the **member initializer list**, it is initialized using the value provided in the member initializer list.
- Otherwise, if the member has a **default member initializer** (an initializer specified in the class definition), it is initialized using that default value.
- Otherwise, the member is **default-initialized** (for built-in types, this means they are left uninitialized).

Here an example showing the different initialization methods:
```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};    // default member initializer (will be ignored)
    int m_y { 2 }; // default member initializer (will be used)
    int m_z;      // no initializer

public:
    Foo(int x)
        : m_x { x } // member initializer list
    {
        std::cout << "Foo constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ", " << m_z << ")\n";
    }
};

int main()
{
    Foo foo { 6 };
    foo.print();

    return 0;
}
```
It will print:
```
Foo constructed
Foo(6, 2, -858993460)
```
In this example:
- `m_x` is initialized using the value provided in the member initializer list (`6`).
- `m_y` is initialized using its default member initializer (`2`), since it is not listed in the member initializer list.
- `m_z` is default-initialized, which means it is left uninitialized (resulting in an indeterminate value).

#### Constructor function bodies:
The body of a constructor function is executed **after** all data members have been initialized (either via the member initializer list, default member initializers, or default initialization). The constructor body are most often left empty, as they are mainly used for initialization, done by the member initializer list. However, the constructor body can be used to perform additional setup or validation after the data members have been initialized. 

New programmers sometimes try to initialize data members in the constructor body instead of using the member initializer list. This is incorrect, as data members are already initialized before the constructor body is executed. For example:
```cpp
#include <iostream>

class Foo
{
private:
    int m_x { 0 };
    int m_y { 1 };

public:
    Foo(int x, int y)
    {
        m_x = x; // incorrect: this is an assignment, not an initialization
        m_y = y; // incorrect: this is an assignment, not an initialization
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo { 6, 7 };
    foo.print();

    return 0;
}
```
But this is generally not a good idea, sicne they might fail in many cases.

> **Best Practice:** Prefer using member initializer lists to initialize data members in constructors, rather than assigning values in the constructor body.

#### Detecting and handling invalid arguments to constructors:
When a constructor is called, it may receive arguments that are invalid or out of range. In such cases, the constructor should handle the invalid arguments appropriately to ensure that the object is in a valid state after construction. Consider the following example:
```cpp
class Fraction
{
private:
    int m_numerator {};
    int m_denominator {};

public:
    Fraction(int numerator, int denominator):
        m_numerator { numerator }, m_denominator { denominator }
    {
    }
};
```
In this example, the `Fraction` class has a constructor that takes a numerator and a denominator. However, if the denominator is `0`, the fraction is undefined (the class has an invariant that the denominator must not be zero). 

So for example, what if the user try to create a `Fraction` object like `Fraction f{ 1, 0 };`? Inside a member initializer list, our tools for detecting and handling errors are quite limited. For example, we could do something like this:
```cpp
class Fraction
{
private:
    int m_numerator {};
    int m_denominator {};

public:
    Fraction(int numerator, int denominator):
        m_numerator { numerator }, m_denominator { denominator != 0.0 ? denominator : ??? } // what do we do here?
    {
    }
};
```
So, typically we will not do anything in the member initializer list to handle invalid arguments, but we will just assign what the user provided, and then handle the error in the constructor body, where we can use stronger tools as `assert`, `static_assert`, or throw exceptions. For example:
```cpp
class Fraction
{
private:
    int m_numerator {};
    int m_denominator {};
public:
    Fraction(int numerator, int denominator)
        : m_numerator { numerator }, m_denominator { denominator }
    {
        assert(denominator != 0 && "Denominator must not be zero");
    }
};
```
In this example, we use an `assert` statement in the constructor body to check if the denominator is zero. If it is, the program will terminate with an error message. This way, we ensure that the `Fraction` object is always in a valid state after construction.

#### When constructors fail (a prelude):
Since constructors are functions, we can apply all the techniques we have learned so far to handle errors in constructors. In a previous chapter, we suggested 4 different strategies to handle errors:
- Resolve the error within the function.
- Pass the error baclk to the caller.
- Halt the program.
- Throw an exception.

In most cases, we do not have enough information to resolve the error within the constructor itself, so we will need to either pass the error back to the caller, halt the program, or throw an exception.

Wih non-member and non-special member functions, we can pass an error back to the caller using return values. However, constructors do not have a return type, so we cannot use return values to pass errors back to the caller. In some cases, we can add an `isValid()` member function to the class that the caller can use to check if the object was constructed successfully. However, this approach is not ideal, as it requires the caller to remember to check the validity of the object after construction.

In certain types of prgram we can simply halt the execution of the program when a constructor fails, and ask the user to run the program again with valid arguments. This is generally not acceptable in production code, but it can be useful in certain situations, such as during development or in simple command-line tools.

The most common way to handle errors in constructors is to throw exceptions. When a constructor throws an exception, the object is not constructed, and the caller can catch the exception and handle it appropriately. This allows us to provide detailed error information to the caller and gives them the opportunity to recover from the error. Exceptions abort the construction process, so any resources allocated before the exception was thrown will be automatically cleaned up.

In some cases, one can have a `createObject` function that handle the creation of the object, for example:
```cpp
#include <iostream>
#include <optional>

class Fraction
{
private:
    int m_numerator { 0 };
    int m_denominator { 1 };

    // private constructor can't be called by public
    Fraction(int numerator, int denominator):
        m_numerator { numerator }, m_denominator { denominator }
    {
    }

public:
    // Allow this function to access private members
    friend std::optional<Fraction> createFraction(int numerator, int denominator);
};

std::optional<Fraction> createFraction(int numerator, int denominator)
{
    if (denominator == 0)
        return {};

    return Fraction{numerator, denominator};
}

int main()
{
    auto f1 { createFraction(0, 1) };
    if (f1)
    {
        std::cout << "Fraction created\n";
    }

    auto f2 { createFraction(0, 0) };
    if (!f2)
    {
        std::cout << "Bad fraction\n";
    }
}
```
In this example, the `Fraction` class has a private constructor that cannot be called directly by the user. Instead, the user must call the `createFraction` function, which checks if the denominator is zero. If it is, the function returns an empty `std::optional`, indicating that the fraction could not be created. Otherwise, it returns a `Fraction` object. This way, we can handle errors in the creation of the object without throwing exceptions.

#### Summary:
- A member initializer list is a special syntax used in the definition of a constructor to initialize data members of a class before the constructor body is executed.
- Data members are initialized in the order they are declared in the class definition, not in the order they appear in the member initializer list.
- Prefer using member initializer lists to initialize data members in constructors, rather than assigning values in the constructor body.
- When handling invalid arguments in constructors, consider using assertions, exceptions, or factory functions to ensure that the object is in a valid state after construction.


---

### S11 — 14.11 Default constructors and default arguments
A **default constructor** is a constructor that accepts no arguments (or all arguments have default values). Default constructors are used to create objects with default values when no specific initialization values are provided. For example:
```cpp
#include <iostream>

class Foo
{
public:
    Foo() // default constructor
    {
        std::cout << "Foo default constructed\n";
    }
};

int main()
{
    Foo foo{}; // No initialization values, calls Foo's default constructor

    return 0;
}
```
prints:
```
Foo default constructed
```
In this example, the `Foo` class has a default constructor that is called when an object of type `Foo` is created without any initialization values.

#### Value initialization versus default initialization for class types:
If a class has a default constructor, both value initialization and default initialization will call the default constructor. For example:
```cpp
Foo foo{}; // value initialization, calls Foo() default constructor
Foo foo2;  // default initialization, calls Foo() default constructor
```
will be equivalent.

However, if a class does not have a default constructor, value initialization and default initialization behave differently:
- **Value initialization** will initialize the object by calling a constructor that matches the provided arguments.
- **Default initialization** will leave the object uninitialized (for built-in types, this means they are left uninitialized).

So, in general, prefer value initialization (`Foo foo{};`) over default initialization (`Foo foo;`), since value initialization will always initialize the object properly, while default initialization may leave the object uninitialized if no default constructor is available.

> **Best Practice:** Prefer value initialization (`TypeName object{};`) over default initialization (`TypeName object;`) to ensure proper initialization of objects.

#### Constructors with default arguments:
As in functions, the rightmost parameters of constructors can have default arguments. This allows us to create objects with varying levels of initialization detail. For example:
```cpp
#include <iostream>

class Foo
{
private:
    int m_x { };
    int m_y { };

public:
    Foo(int x=0, int y=0) // has default arguments
        : m_x { x }
        , m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

int main()
{
    Foo foo1{};     // calls Foo(int, int) constructor using default arguments
    Foo foo2{6, 7}; // calls Foo(int, int) constructor

    return 0;
}
```
This will print:
```
Foo(0, 0) constructed
Foo(6, 7) constructed
```
In this example, the `Foo` class has a constructor that takes two `int` parameters with default arguments of `0`. When creating `foo1`, no arguments are provided, so the default arguments are used. When creating `foo2`, specific values are provided for both parameters.

If all the arguments have default values, the constructor is basically a default constructor, since it can be called with no arguments.

#### Overloaded constructors:
Since constructors are just special member functions, we can overload them by providing multiple constructors with different parameter lists. This allows us to create objects with varying levels of initialization detail. For example:
```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo() // default constructor
    {
        std::cout << "Foo constructed\n";
    }

    Foo(int x, int y) // non-default constructor
        : m_x { x }, m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

int main()
{
    Foo foo1{};     // Calls Foo() constructor
    Foo foo2{6, 7}; // Calls Foo(int, int) constructor

    return 0;
}
```
This will print:
```
Foo constructed
Foo(6, 7) constructed
```
In this example, the `Foo` class has two constructors: a default constructor that takes no arguments, and a non-default constructor that takes two `int` parameters. When creating `foo1`, the default constructor is called, and when creating `foo2`, the non-default constructor is called, since it matches the provided arguments.

Following the above, a class can only have **one** default constructor. If multiple constructors are provided, only one of them can be a default constructor (i.e., a constructor that can be called with no arguments):
```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo() // default constructor
    {
        std::cout << "Foo constructed\n";
    }

    Foo(int x=1, int y=2) // default constructor
        : m_x { x }, m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

int main()
{
    Foo foo{}; // compile error: ambiguous constructor function call

    return 0;
}
```
This will result in a compile error because both constructors can be called with no arguments, leading to ambiguity.

#### An implicit default constructor:
If a non-aggregate class type object has no user-declared constructors, the compiler will automatically generate a default constructor for the class. This automatically generated default constructor is called an **implicit default constructor**. For example:
```cpp
#include <iostream>

class Foo
{
private:
    int m_x{};
    int m_y{};

    // Note: no constructors declared
};

int main()
{
    Foo foo{};

    return 0;
}
```
In this example, the `Foo` class has no user-declared constructors, so the compiler automatically generates an implicit default constructor. When creating the `foo` object, the implicit default constructor is called, which initializes the data members `m_x` and `m_y` to their default values (`0`). Bacially, the compiler will generate this constructor for us:
```cpp
public:
    Foo() // implicitly generated default constructor
    {
    }
```

#### Using `= default` to generate an explicitly defaulted default constructor:
In cases where we would declare a default constructor that is identical to the implicit default constructor, we can use the `= default` syntax to explicitly request the compiler to generate the default constructor for us. In this way we make it clear to the reader that we want the default behavior. For example:
```cpp
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo() = default; // generates an explicitly defaulted default constructor

    Foo(int x, int y)
        : m_x { x }, m_y { y }
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ") constructed\n";
    }
};

int main()
{
    Foo foo{}; // calls Foo() default constructor

    return 0;
}
```
In this way, we explicitly declare the default constructor using `= default`, which tells the compiler to generate the default constructor for us.

> **Best Practice:** Use `= default` to explicitly request the compiler to generate a default constructor when needed, to improve code clarity.

#### Explicitly defaulted default constructor versus embty user-defined constructor:
There are at least two cases where we might want to declare an empty user-defined default constructor instead of using `= default`:
1. In case we value initialize a class, if the class has a user-defined default constructor, the object will be default initialized. However, if the class has a default constructor that is not user-provided (i.e., an implicit or explicitly defaulted default constructor), the object will be zero-initialized before being default initialized. For example:
    ```cpp
    #include <iostream>

    class User
    {
    private:
        int m_a; // note: no default initialization value
        int m_b {};

    public:
        User() {} // user-defined empty constructor

        int a() const { return m_a; }
        int b() const { return m_b; }
    };

    class Default
    {
    private:
        int m_a; // note: no default initialization value
        int m_b {};

    public:
        Default() = default; // explicitly defaulted default constructor

        int a() const { return m_a; }
        int b() const { return m_b; }
    };

    class Implicit
    {
    private:
        int m_a; // note: no default initialization value
        int m_b {};

    public:
        // implicit default constructor

        int a() const { return m_a; }
        int b() const { return m_b; }
    };

    int main()
    {
        User user{}; // default initialized
        std::cout << user.a() << ' ' << user.b() << '\n';

        Default def{}; // zero initialized, then default initialized
        std::cout << def.a() << ' ' << def.b() << '\n';

        Implicit imp{}; // zero initialized, then default initialized
        std::cout << imp.a() << ' ' << imp.b() << '\n';

        return 0;
    }
    ```
    This might print:
    ```
    782510864 0
    0 0
    0 0
    ```
    In this example, the `User` class has a user-defined empty default constructor, so when the `user` object is created, it is default initialized, leaving `m_a` uninitialized. The `Default` and `Implicit` classes have explicitly defaulted and implicit default constructors, respectively, so when the `def` and `imp` objects are created, they are zero-initialized before being default initialized, resulting in `m_a` being initialized to `0`. So in general, if you want to ensure that data members without default initializers are zero-initialized, use an explicitly defaulted or implicit default constructor.
2. Prioir to C==20, a class with a user-defined default constructor (even with an empty body) makes the class a non-aggregate, while a class with an implicitly generated or explicitly defaulted default constructor remains an aggregate (provided it meets the other criteria for being an aggregate). This distinction can be important if you want to use aggregate initialization for the class.

#### Only create a default constructor when it makes sense:
Not all classes should have a default constructor. If a class represents an entity that requires specific initialization values to be in a valid state, it may not make sense to provide a default constructor. For example:
```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    Fraction() = default;
    Fraction(int numerator, int denominator)
        : m_numerator{ numerator }
        , m_denominator{ denominator }
    {
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f1 {3, 5};
    f1.print();

    Fraction f2 {}; // will get Fraction 0/1
    f2.print();

    return 0;
}
```
This will print:
```
Fraction(3, 5)
Fraction(0, 1)
```
In this example, the `Fraction` class has a default constructor that initializes the fraction to `0/1`. However, in some cases, it may not make sense to have a default constructor for the `Fraction` class, as a fraction without specific numerator and denominator values may not be meaningful. In such cases, it may be better to only provide a constructor that requires specific initialization values.

Now consider this class:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name{ };
    int m_id{ };

public:
    Employee(std::string_view name, int id)
        : m_name{ name }
        , m_id{ id }
    {
    }

    void print() const
    {
        std::cout << "Employee(" << m_name << ", " << m_id << ")\n";
    }
};

int main()
{
    Employee e1 { "Joe", 1 };
    e1.print();

    Employee e2 {}; // compile error: no matching constructor
    e2.print();

    return 0;
}
```
This will result in a compile error because the `Employee` class does not have a default constructor. This is appropriate, as an `Employee` object without a name and ID may not be meaningful. In such cases, it is better to only provide constructors that require specific initialization values.

#### Summary:
- A default constructor is a constructor that accepts no arguments (or all arguments have default values).
- Prefer value initialization (`TypeName object{};`) over default initialization (`TypeName object;`) to ensure proper initialization of objects.
- Constructors can be overloaded by providing multiple constructors with different parameter lists.
- If a class has no user-declared constructors, the compiler will automatically generate an implicit default constructor for the class.
- Use `= default` to explicitly request the compiler to generate a default constructor when needed, to improve code clarity.
- Only create a default constructor when it makes sense for the class.


---


### S12 — 14.12 Delegating constructors
Whenever possible, we would like to reduce the redundant code (DRY: Don't Repeat Yourself) in our programs. Consider this example:
```cpp
void A()
{
    // statements that do task A
}

void B()
{
    // statements that do task A
    // statements that do task B
}
```
Here, the function `B` contains code that is identical to the code in function `A`. This violates the DRY principle, and it could be fixed by having `B` call `A`:
```cpp
void A()
{
    // statements that do task A
}

void B()
{
    A();
    // statements that do task B
}
```

The same principle applies to constructors. If we have multiple constructors that share common initialization code, we can use **delegating constructors** to avoid code duplication. A delegating constructor is a constructor that calls another constructor in the same class to perform part of its initialization. Consider the following example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name { "???" };
    int m_id { 0 };
    bool m_isManager { false };

public:
    Employee(std::string_view name, int id) // Employees must have a name and an id
        : m_name{ name }, m_id { id }
    {
        std::cout << "Employee " << m_name << " created\n";
    }

    Employee(std::string_view name, int id, bool isManager) // They can optionally be a manager
        : m_name{ name }, m_id{ id }, m_isManager { isManager }
    {
        std::cout << "Employee " << m_name << " created\n";
    }
};

int main()
{
    Employee e1{ "James", 7 };
    Employee e2{ "Dave", 42, true };
}
```
You can see that the body of each constructor contains the same code to print the employee creation message. We can eliminate this redundancy and write:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name { "???" };
    int m_id{ 0 };
    bool m_isManager { false };

    void printCreated() const // our new helper function
    {
        std::cout << "Employee " << m_name << " created\n";
    }

public:
    Employee(std::string_view name, int id)
        : m_name{ name }, m_id { id }
    {
        printCreated(); // we call it here
    }

    Employee(std::string_view name, int id, bool isManager)
        : m_name{ name }, m_id{ id }, m_isManager { isManager }
    {
        printCreated(); // and here
    }
};

int main()
{
    Employee e1{ "James", 7 };
    Employee e2{ "Dave", 42, true };
}
```
This eliminates the redundancy, but we can do even better using delegating constructors, since in this way we have introduced a new function that is only used by the constructors, and both constructors are still initializing the common members separately. Using delegating constructors, we can imporve this, but we need a bit of time to explain how they work.

#### Calling a constructor in the body of a function creates a temporary object:
It would seem obvious to just call one constructor from another in the constructor body, as we did with functions `A` and `B` above. However, doing so will not work as expected. For example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name { "???" };
    int m_id { 0 };
    bool m_isManager { false };

public:
    Employee(std::string_view name, int id)
        : m_name{ name }, m_id { id } // this constructor initializes name and id
    {
        std::cout << "Employee " << m_name << " created\n"; // our print statement is back here
    }

    Employee(std::string_view name, int id, bool isManager)
        : m_isManager { isManager } // this constructor initializes m_isManager
    {
        // Call Employee(std::string_view, int) to initialize m_name and m_id
        Employee(name, id); // this doesn't work as expected!
    }

    const std::string& getName() const { return m_name; }
};

int main()
{
    Employee e2{ "Dave", 42, true };
    std::cout << "e2 has name: " << e2.getName() << "\n"; // print e2.m_name
}
```
This will print:
```
Employee Dave created
e2 has name: ???
```
Even though `Emplyee Dave created` was printed, after `e2` is constructed, its `m_name` member is still `???`. Why?

This is because calling `Employee(name, id);` in the body of the second constructor creates a **temporary** `Employee` object that is immediately destroyed after the constructor body finishes executing. The temporary object initializes its own `m_name` and `m_id` members, but these do not affect the `m_name` and `m_id` members of the `e2` object being constructed. As a result, `e2.m_name` remains uninitialized (or initialized to its default value).

> **Best Practice:** Do not call constructors in the body of other constructors, as this creates temporary objects that do not affect the object being constructed. If you do want a temproary object for some reason, consider using list-initialization syntax to make it clear that you are creating a temporary object (e.g., `Employee{name, id};`).

#### Delegating constructors:
Constructors are allowed to delegate (tranfer responsibility for part of their initialization) to other constructors in the same class using a special syntax in the member initializer list. This process is soemtimes called **construction chaining**, and such constructors are called **delegating constructors**. The syntax for delegating constructors is to call another constructor in the *member initializer list* using the same syntax as for constructing temporary objects. For example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name { "???" };
    int m_id { 0 };

public:
    Employee(std::string_view name)
        : Employee{ name, 0 } // delegate initialization to Employee(std::string_view, int) constructor
    {
    }

    Employee(std::string_view name, int id)
        : m_name{ name }, m_id { id } // actually initializes the members
    {
        std::cout << "Employee " << m_name << " created\n";
    }

};

int main()
{
    Employee e1{ "James" };
    Employee e2{ "Dave", 42 };
}
```
This will print:
```
Employee James created
Employee Dave created
```
In this example, the first constructor `Employee(std::string_view name)` delegates the initialization of `m_name` and `m_id` to the second constructor `Employee(std::string_view name, int id)`, which actually initializes the data members. This way, we avoid code duplication and ensure that the initialization logic is centralized in one constructor.

The donwside of this approach is that sometimes it requires duplication of initialization values. For example, if we want to provide a default ID of `0` when only a name is provided, we have to specify `0` in the delegating constructor. However, this is a small price to pay for the benefits of reduced code duplication and improved maintainability.

Other additional notes about delegating constructors:
- A constructor that delegates to another constructor cannot initialize any members itself. All member initialization must be done by the constructor being delegated to.
- Delegating constructors can be chained, meaning a constructor can delegate to another constructor that itself delegates to yet another constructor. For example, one constructor can delegate to a second constructor, which in turn delegates to the first constructor.

> **Best Practice:** Use delegating constructors to reduce code duplication and centralize initialization logic in one constructor.

#### Reducing constructors using default arguments:
Default values can be used to reduce multiple constructors into fewer constructors. For example, consider the following class:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name{};
    int m_id{ 0 }; // default member initializer

public:

    Employee(std::string_view name, int id = 0) // default argument for id
        : m_name{ name }, m_id{ id }
    {
        std::cout << "Employee " << m_name << " created\n";
    }
};

int main()
{
    Employee e1{ "James" };
    Employee e2{ "Dave", 42 };
}
```
In this example, we have a single constructor that takes a `name` and an optional `id` parameter with a default value of `0`. This allows us to create `Employee` objects with just a name or with both a name and an ID, without needing multiple constructors that handle these cases separately.

> **Best Practice:** Use default arguments in constructors to reduce the number of constructors needed for different initialization scenarios.

#### A conundrum: redundant constructors vs redundant default values:
When designing a class, we may face a conundrum between using multiple constructors to handle different initialization scenarios and using default arguments to reduce the number of constructors. Both approaches have their pros and cons:
- **Redundant constructors:** Having multiple constructors can make the code more explicit and easier to understand, as each constructor clearly defines a specific initialization scenario. However, this can lead to code duplication and increased maintenance effort.
- **Redundant default values:** Using default arguments can reduce the number of constructors and eliminate code duplication. However, it can make the code less explicit, as it may not be immediately clear which parameters are being initialized when creating an object.

Both options are valid, and the choice between them often depends on the specific use case and personal preference. In general, prefer using default arguments when the initialization scenarios are closely related and can be handled with a single constructor. Use multiple constructors when the initialization scenarios are distinct and require different logic.

#### Summary:
- A delegating constructor is a constructor that calls another constructor in the same class to perform part of its initialization.
- Delegating constructors use a special syntax in the member initializer list to call another constructor.
- Use delegating constructors to reduce code duplication and centralize initialization logic in one constructor.
- Use default arguments in constructors to reduce the number of constructors needed for different initialization scenarios.


---

### S13 — 14.13 Temporary class objects
Consider the folllowing example:
```cpp
#include <iostream>

int add(int x, int y)
{
    int sum{ x + y }; // stores x + y in a variable
    return sum;       // returns value of that variable
}

int main()
{
    std::cout << add(5, 3) << '\n';

    return 0;
}
```
In the `add()` function, the variable `sum` is used to store the result of `x + y` before returning it (this will be then evaluated in the return statement). However, in most cases when a variable is needed only once, we can avoid creating a named variable and instead use that expression directly in the statement it needs to be used. For example, we can rewrite the `add()` function as:
```cpp
#include <iostream>

int add(int x, int y)
{
    return x + y; // just return x + y directly
}

int main()
{
    std::cout << add(5, 3) << '\n';

    return 0;
}
```
This eliminates the unnecessary variable `sum`, making the code more concise.

This works not only for return values, but also with most function arguments. For example, consider this code:
```cpp
#include <iostream>

void printValue(int value)
{
    std::cout << value;
}

int main()
{
    int sum{ 5 + 3 };
    printValue(sum);

    return 0;
}
```
can be rewritten as:
```cpp
#include <iostream>

void printValue(int value)
{
    std::cout << value;
}

int main()
{
    printValue(5 + 3);

    return 0;
}
```
Note that this only works in cases where an rvalue expression is acceptable. For example, we cannot use this technique when passing an argument by non-const lvalue reference, since an rvalue cannot be bound to a non-const lvalue reference. For example:
```cpp
#include <iostream>

void addOne(int& value) // pass by non-const references requires lvalue
{
    ++value;
}

int main()
{
    int sum { 5 + 3 };
    addOne(sum);   // okay, sum is an lvalue

    addOne(5 + 3); // compile error: not an lvalue

    return 0;
}
```
This will result in a compile error because `5 + 3` is an rvalue and cannot be bound to the non-const lvalue reference parameter `value` in the `addOne` function.

#### Temporary class objects:
The same principle applies to class types. Consider the following example:
```cpp
#include <iostream>

class IntPair
{
private:
    int m_x{};
    int m_y{};

public:
    IntPair(int x, int y)
        : m_x { x }, m_y { y }
    {}

    int x() const { return m_x; }
    int y() const { return m_y; }
};

void print(IntPair p)
{
    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
}

int main()
{
    // Case 1: Pass variable
    IntPair p { 3, 4 };
    print(p); // prints (3, 4)

    return 0;
}
```
This code creates an `IntPair` object `p` and passes it to the `print` function. However, since `p` is only used once, we can improve this code.

There are two common ways to create temporary class objects:
```cpp
#include <iostream>

class IntPair
{
private:
    int m_x{};
    int m_y{};

public:
    IntPair(int x, int y)
        : m_x { x }, m_y { y }
    {}

    int x() const { return m_x; }
    int y() const{ return m_y; }
};

void print(IntPair p)
{
    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
}

int main()
{
    // Case 1: Pass variable
    IntPair p { 3, 4 };
    print(p);

    // Case 2: Construct temporary IntPair and pass to function
    print(IntPair { 5, 6 } );

    // Case 3: Implicitly convert { 7, 8 } to a temporary Intpair and pass to function
    print( { 7, 8 } );

    return 0;
}
```
Both Case 2 and Case 3 create temporary `IntPair` objects that are passed to the `print` function without needing to create a named variable. This makes the code more concise and easier to read. Specifically:
- In Case 2, we explicitly create a temporary `IntPair` object using the constructor syntax `IntPair { 5, 6 }`.
- In Case 3, we use braced-init-list syntax `{ 7, 8 }`, which the compiler implicitly converts to a temporary `IntPair` object. This could be less clear to some readers, so use it judiciously.

To summarize:
```cpp
IntPair p { 1, 2 }; // create named object p initialized with { 1, 2 }
IntPair { 1, 2 };   // create temporary object initialized with { 1, 2 }
{ 1, 2 };           // compiler will try to convert { 1, 2 } to temporary object matching expected type (typically a parameter or return type)
```
We will discuss the last case more in details in a later chapter.

Here some few more examples of using temporary class objects:
```cpp
std::string { "Hello" }; // create a temporary std::string initialized with "Hello"
std::string {};          // create a temporary std::string using value initialization / default constructor
// We did not cover this yet, consider this a small spoiler
std::vector<int> { 1, 2, 3 }; // create a temporary std::vector<int> initialized with { 1, 2, 3 }
```

#### Creating temporary objects via direct initialization (Optional):
Since we just showed temporary objects created via direct-list-initialization, you might wonder if it is also possible to create temporary objects via other forms of initialization, such as direct-initialization or copy-initialization.

Regarding copy initialization, there is no syntax to create a temporary object with that. However, you can create temporary objects using direct initialization syntax. For example:
```cpp
Foo (1, 2); //  temporary Foo, direct-initialized with (1, 2) (similar to `Foo { 1, 2 }`)
```
This creates a temporary `Foo` object that is direct-initialized with the arguments `(1, 2)`. However, this syntax can be confused with a function declaration, so it is generally not recommended to use this form for creating temporary objects. Prefer using braced-init-list (that also prevents narrowing conversion) syntax for clarity:
```cpp
Foo { 1, 2 }; // temporary Foo, direct-list-initialized with { 1, 2 }
```
This is way more clear!

The rest of the section is very weird, so it is left as optional reading for those interested.

#### Temporary objects and return by value:
When a function returns an object by value, it creates a temporary object that is returned to the caller. For example:
```cpp
#include <iostream>

class IntPair
{
private:
    int m_x{};
    int m_y{};

public:
    IntPair(int x, int y)
        : m_x { x }, m_y { y }
    {}

    int x() const { return m_x; }
    int y() const { return m_y; }
};

void print(IntPair p)
{
    std::cout << "(" << p.x() << ", " << p.y() << ")\n";
}

// Case 1: Create named variable and return
IntPair ret1()
{
    IntPair p { 3, 4 };
    return p; // returns temporary object (initialized using p)
}

// Case 2: Create temporary IntPair and return
IntPair ret2()
{
    return IntPair { 5, 6 }; // returns temporary object (initialized using another temporary object)
}

// Case 3: implicitly convert { 7, 8 } to IntPair and return
IntPair ret3()
{
    return { 7, 8 }; // returns temporary object (initialized using another temporary object)
}

int main()
{
    print(ret1());
    print(ret2());
    print(ret3());

    return 0;
}
```
This will print:
```
(3, 4)
(5, 6)
(7, 8)
```
In this example, the functions `ret1`, `ret2`, and `ret3` each return a temporary `IntPair` object that is created in different ways. The temporary objects are then passed to the `print` function.

#### A few notes:
- Just like in the case of an `int`, when used in expressions, a temporary class object is an **rvalue**. Therefore, those objects can be used only where rvalue expressions are allowed.
- Temporary objects are created at the point of definition, and destroyed at the end of the full expression in which they were created. For example, in the expression `print(IntPair { 5, 6 } );`, the temporary `IntPair` object is created when the expression is evaluated and destroyed after the `print` function call completes.

#### `static_cast` vs explicit instantiation of a temporary object:
In case where we need to convert an expression to a specific class type, we can use either `static_cast` or explicit instantiation of a temporary object. For example:
```cpp
#include <iostream>

int main()
{
    char c { 'a' };

    std::cout << static_cast<int>( c ) << '\n'; // static_cast returns a temporary int direct-initialized with value of c
    std::cout << int { c } << '\n';             // explicitly creates a temporary int list-initialized with value c

    return 0;
}
```
`static_cast<int>( c )` returns a temporary `int` that is direct-initialized with the value of `c`, while `int { c }` explicitly creates a temporary `int` that is list-initialized with the value of `c`. Both approaches achieve the same result, but the syntax is different.

Now a slightly more complex example:

printString.h (let's say we cannot modify this file)
```cpp
#include <string>
void printString(const std::string &s)
{
    std::cout << s << '\n';
}
```

main.cpp
```cpp
#include "printString.h"
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string_view sv { "Hello" };

    // We want to print sv using the printString() function

//    printString(sv); // compile error: a std::string_view won't implicitly convert to a std::string

    printString( static_cast<std::string>(sv) ); // Case 1: static_cast returns a temporary std::string direct-initialized with sv
    printString( std::string { sv } );           // Case 2: explicitly creates a temporary std::string list-initialized with sv
    printString( std::string ( sv ) );           // Case 3: C-style cast returns temporary std::string direct-initialized with sv (avoid this one!)

    return 0;
}
```
In this example, we want to print a `std::string_view` using the `printString` function, which expects a `const std::string&` parameter. Since `std::string_view` does not implicitly convert to `std::string`, we need to create a temporary `std::string` object. We can do this using either `static_cast` (Case 1) or explicit instantiation of a temporary object (Case 2). Both approaches create a temporary `std::string` that is passed to the `printString` function.

> **Best Practice:** Prefer using `static_cast` when converting to a fundamental type (e.g., `static_cast<int>(c)`), and a list-initialized temporary (`std::string { sv }`) when converting to a class type, for clarity and to avoid potential narrowing conversions.

In general, prefere `static_cast` when any of the following apply:
- We need to perform a narrowing conversion (e.g., from `double` to `int`).
- We need to make it really obvious that we are converting to a type that will result in some different behavior (e.g., converting from `char` to `int` to print the ASCII value).
- We want to use direct-initialization syntax for some reason (although this is rare).

Prefer creating a new object (using list-initialization syntax) when any of the following apply:
- We want to use list-initialization (e.g., protection against narrowing conversions).
- We want to provide additional constructor arguments (e.g., when converting to a class type that requires multiple arguments for construction).

#### Summary:
- Temporary class objects can be created using direct-list-initialization syntax (e.g., `TypeName { args... }`) or by implicit conversion of a braced-init-list (e.g., `{ args... }`).
- Temporary class objects are rvalues and can be used only where rvalue expressions are allowed.
- Temporary class objects are created at the point of definition and destroyed at the end of the full expression in which they were created.
- When converting to a fundamental type, prefer using `static_cast`.
- When converting to a class type, prefer creating a new object using list-initialization syntax.


---

### S14 — 14.14 Introduction to the copy constructor
Consider the followoing example:
```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
    Fraction fCopy { f }; // What constructor is used here?

    f.print();
    fCopy.print();

    return 0;
}
```
This will print:
```
Fraction(5, 3)
Fraction(5, 3)
```
In this example, we create a `Fraction` object `f` using the constructor that takes two `int` parameters, with a standard brace initialization that calls `Fraction(int, int)`. However, when we create the `fCopy` object using `Fraction fCopy { f };`, we are passing an existing `Fraction` object `f` to the constructor.

In this case, the compiler automatically generates a special constructor called the **copy constructor** for the `Fraction` class. The copy constructor is used to create a new object as a copy of an existing object of the same class type.

#### The copy constructor:
A **copy constructor** is a special constructor that initialize an object with an existing object of the same class type. After this initialization is performed, the new object is a copy of the existing object.

#### An implicit copy constructor:
If you do not provide any copy constructor for your class, the compiler will automatically generate one for you. This automatically generated copy constructor is called an **implicit copy constructor** (public). The implicit copy constructor performs a member-wise copy of the data members from the existing object to the new object (e.g., each member is initialized using the corresponding member from the existing object). For example, in the `Fraction` class above, `fCopy.m_numerator` is initialized with the value of `f.m_numerator`, and `fCopy.m_denominator` is initialized with the value of `f.m_denominator`.

#### Defining your own copy constructor:
Additionally, we can also provide our own copy constructor for a class. A user-defined copy constructor has the following general form:
```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    // Copy constructor
    Fraction(const Fraction& fraction)
        // Initialize our members using the corresponding member of the parameter
        : m_numerator{ fraction.m_numerator }
        , m_denominator{ fraction.m_denominator }
    {
        std::cout << "Copy constructor called\n"; // just to prove it works
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
    Fraction fCopy { f }; // Calls Fraction(const Fraction&) copy constructor

    f.print();
    fCopy.print();

    return 0;
}
```
This will print:
```
Copy constructor called
Fraction(5, 3)
Fraction(5, 3)
```
As you can see here, we defined the copy constructor `Fraction(const Fraction& fraction)`, which takes a reference to an existing `Fraction` object and initializes the new object by copying the data members from the existing object. When we create `fCopy` using `Fraction fCopy { f };`, our user-defined copy constructor is called, and we see the message "Copy constructor called" printed to the console.

> **Warning:** Do not pass the parameter by value (e.g., `Fraction(Fraction fraction)`), as this would cause infinite recursion. This is because passing by value would require calling the copy constructor to create the parameter, which would in turn call the copy constructor again, leading to infinite recursion and a stack overflow.

> **Reminder:** Access controls work on a per-class basis (not per-object basis). Therefore, the copy constructor can access the private members of the `fraction` parameter, even though it is a different object.

**Best Practice:** Copy constructors should have no side effects beyond copying.

#### Prefer implicit copy constructors:
In most cases, the implicit copy constructor generated by the compiler is sufficient for most of our needs, especially for simple classes that only contain fundamental data types or other classes that have proper copy constructors. Therefore, it is generally recommended to prefer the implicit copy constructor unless you have a specific reason to define your own.

> **Best Practice:** Prefer the implicit copy constructor in general.

In thje next chapters, we will see cases where defining our own copy constructor is necessary, such as when dealing with dynamic memory allocation or resource management.

#### The copy constructos's parameter must be a reference:
Note that the parameter of a copy constructor must be a **lvalue reference** or **const lvalue reference** to the class type. This is because the copy constructor should not modify the existing object being copied from, and passing by reference avoids unnecessary copying of the object. So, in general, a const lvalue reference is preferred for the copy constructor parameter.

> **Best Practice:** Prefer using a const lvalue reference as the parameter type for copy constructors.

#### Pass by value and the copy constructor:
When an object is passed by alue to a function, the arguement is copied into the parameter (in general). When the argument and the parameter are of the same class type, the copy constructor is used to create a copy of the argument object for the parameter. For example:
```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator = 0, int denominator = 1)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
    }

    // Copy constructor
    Fraction(const Fraction& fraction)
        : m_numerator{ fraction.m_numerator }
        , m_denominator{ fraction.m_denominator }
    {
        std::cout << "Copy constructor called\n";
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

void printFraction(Fraction f) // f is pass by value
{
    f.print();
}

int main()
{
    Fraction f{ 5, 3 };

    printFraction(f); // f is copied into the function parameter using copy constructor

    return 0;
}
```
This will print:
```
Copy constructor called
Fraction(5, 3)
```
In this example, when we call `printFraction(f);`, the `f` object is copied into the function parameter `f` using the copy constructor. As a result, we see the message "Copy constructor called" printed to the console, before printing the fraction.

#### Return by value and the copy constructor:
In a previous chapter, we have seen that return by value creates a temporary object (holding a copy of the returned value) that is returned to the caller. When the returned value is of a class type, the copy constructor is used to create this temporary object. For example:
```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator = 0, int denominator = 1)
        : m_numerator{ numerator }, m_denominator{ denominator }
    {
    }

    // Copy constructor
    Fraction(const Fraction& fraction)
        : m_numerator{ fraction.m_numerator }
        , m_denominator{ fraction.m_denominator }
    {
        std::cout << "Copy constructor called\n";
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

void printFraction(Fraction f) // f is pass by value
{
    f.print();
}

Fraction generateFraction(int n, int d)
{
    Fraction f{ n, d };
    return f;
}

int main()
{
    Fraction f2 { generateFraction(1, 2) }; // Fraction is returned using copy constructor

    printFraction(f2); // f2 is copied into the function parameter using copy constructor

    return 0;
}
```
This will print:
```
Copy constructor called
Copy constructor called
Copy constructor called
Fraction(1, 2)
```
In this example, when we `generateFraction` returns a `Fraction` object back to the `main`, a temporary `Fraction` object is created and initialized using the copy constructor. Additionally, this object is then used to initialize `f2` using the copy constructor again. Finally, when we call `printFraction(f2);`, `f2` is copied into the function parameter using the copy constructor once more.

In some cases, the compiler may optimize away some of these copy constructor calls using a technique called **copy elision** (we will cover this in a later chapter). However, it is important to understand that the copy constructor is used in these scenarios unless optimization occurs.

#### Using `= default` to generate a default copy constructor:
If a class has no copy constructor, the compiler will automatically generate one for us. If we want to explicitly request the compiler to generate a default copy constructor, we can use the `= default` syntax. For example:
```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    // Explicitly request default copy constructor
    Fraction(const Fraction& fraction) = default;

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };
    Fraction fCopy { f };

    f.print();
    fCopy.print();

    return 0;
}
```
This code behaves the same way as if we had not defined a copy constructor at all, since we requested the compiler to generate the default copy constructor for us using `= default`. This might be better since you explicitly state your intent to use the default copy constructor.

#### Using `= delete` to prevent copying:
In some cases, we may want to prevent copying of objects of a class. For example, if a class manages a resource that should not be duplicated, we can delete the copy constructor using the `= delete` syntax. For example:
```cpp
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    // Delete the copy constructor so no copies can be made
    Fraction(const Fraction& fraction) = delete;

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };
    Fraction fCopy { f }; // compile error: copy constructor has been deleted

    return 0;
}
```
In this example, we deleted the copy constructor using `= delete`, which prevents any copying of `Fraction` objects. Attempting to create a copy of a `Fraction` object will result in a compile-time error.

Additionally, you could also prevent the public to make copy of your class by declaring the copy constructor as private (without providing a definition). However, using `= delete` is the preferred modern approach.

#### Summary:
- A copy constructor is a special constructor that initializes a new object as a copy of an existing object of the same class type.
- If no copy constructor is provided, the compiler automatically generates an implicit copy constructor that performs a member-wise copy of the data members.
- A user-defined copy constructor can be provided to customize the copying behavior (passing the object by const lvalue reference).
- Prefer the implicit copy constructor unless a specific reason exists to define your own.
- The copy constructor is used when an object is passed by value to a function or returned by value from a function.


---

### S15 — 14.15 Class initialization and copy elision
Back in the early days of our journey, we discuss 6 basic types of initialization for objects with fundamental types:
1. Default initialization (e.g., `int x;`)
2. Copy initialization (e.g., `int x = 5;`)
3. Direct initialization (e.g., `int x(5);`)

And then other 3 list initialization forms:

4. Direct list initialization (e.g., `int x{5};`)
5. Copy list initialization (e.g., `int x = {5};`)
6. Value initialization (e.g., `int x{};`)

```cpp
int a;         // no initializer (default initialization)
int b = 5;     // initializer after equals sign (copy initialization)
int c( 6 );    // initializer in parentheses (direct initialization)

// List initialization methods (C++11)
int d { 7 };   // initializer in braces (direct list initialization)
int e = { 8 }; // initializer in braces after equals sign (copy list initialization)
int f {};      // initializer is empty braces (value initialization)
```

All of these forms of initialization are also applicable to class types. However, class types have additional complexities due to the presence of constructors, copy constructors, and other special member functions.
```cpp
#include <iostream>

class Foo
{
public:

    // Default constructor
    Foo()
    {
        std::cout << "Foo()\n";
    }

    // Normal constructor
    Foo(int x)
    {
        std::cout << "Foo(int) " << x << '\n';
    }

    // Copy constructor
    Foo(const Foo&)
    {
        std::cout << "Foo(const Foo&)\n";
    }
};

int main()
{
    // Calls Foo() default constructor
    Foo f1;           // default initialization
    Foo f2{};         // value initialization (preferred)

    // Calls foo(int) normal constructor
    Foo f3 = 3;       // copy initialization (non-explicit constructors only)
    Foo f4(4);        // direct initialization
    Foo f5{ 5 };      // direct list initialization (preferred)
    Foo f6 = { 6 };   // copy list initialization (non-explicit constructors only)

    // Calls foo(const Foo&) copy constructor
    Foo f7 = f3;      // copy initialization
    Foo f8(f3);       // direct initialization
    Foo f9{ f3 };     // direct list initialization (preferred)
    Foo f10 = { f3 }; // copy list initialization

    return 0;
}
```

In modern C++, copy initialization, direct initialization, and list initialization essentially do the same thing: they initialize an object using the appropriate constructor.

In general, for all types of initialization:
- When initializing a class type, the set of constructors for that class are examined, and overload resoliution is performed to select the most appropriate constructor based on the provided arguments. This may involve implicit conversion of the arguments to match the constructor parameters.
- When initializing a non-class type, the implicit conversion rules are used to determine whether an implicit conversion exists from the initializer to the type being initialized.

Note that there exists three key differences between these initialization forms:
- List initialization prevents narrowing conversions.
- Copy initialization only considers non-explicit constructors/conversion functions (we will cover this later).
- List initialization prioritize matching list constructors over the other matching constructors (we will cover this later).

#### Unnecessay copies:
Consider this example:
```cpp
#include <iostream>

class Something
{
    int m_x{};

public:
    Something(int x)
        : m_x{ x }
    {
        std::cout << "Normal constructor\n";
    }

    Something(const Something& s)
        : m_x { s.m_x }
    {
        std::cout << "Copy constructor\n";
    }

    void print() const { std::cout << "Something(" << m_x << ")\n"; }
};

int main()
{
    Something s { Something { 5 } }; // focus on this line
    s.print();

    return 0;
}
```
This will print:
```
Normal constructor
Copy constructor
Something(5)
```
In this example, we create a temporary `Something` object using the normal constructor `Something { 5 }`, and then we use that temporary object to initialize the `s` object using the copy constructor `Something(const Something& s)`. This results in two constructor calls: one for the normal constructor and one for the copy constructor.

However, this program is quite inefficient, as it involves an unnecessary copy of the temporary object. We can optimize this by eliminating the copy constructor call:
```cpp
Something s { 5 }; // direct list initialization, no copy needed
```
This way, we directly initialize `s` using the normal constructor, avoiding the unnecessary copy.

#### Copy elision:
Since the compiler is free to rewrite statements to improve performance as long as the observable behavior of the program remains the same, it can optimize away unnecessary copies in certain situations. This optimization is called **copy elision**. For example, in the previous example, the compiler can optimize away the copy constructor call when initializing `s` with a temporary object rewriting `Something s { Something { 5 } };` to `Something s { 5 };`.

Copy elision is a compiler optimization technique that allows the compiler to remove unnecessary copying of objects in certain situations, such as when a temporary object is used to initialize another object of the same type. This optimization can improve performance by reducing the number of constructor calls and memory allocations. When the compiler optimizes away a call to the copy constructor, we say that the constructor has been **elided**.

For example, if we run the previous example with copy elision enabled, we would see:
```
Normal constructor
Something(5)
```
indicating that the copy constructor call has been elided.

#### Copy elision in pass by value and return by value:
Copy elision can also occur in other scenarios, such as when passing objects by value to functions or returning objects by value from functions, avoiding in this way unnecessary copies. For example:
```cpp
#include <iostream>

class Something
{
public:
	Something() = default;
	Something(const Something&)
	{
		std::cout << "Copy constructor called\n";
	}
};

Something rvo()
{
	return Something{}; // calls Something() and copy constructor
}

Something nrvo()
{
	Something s{}; // calls Something()
	return s;      // calls copy constructor
}

int main()
{
	std::cout << "Initializing s1\n";
	Something s1 { rvo() }; // calls copy constructor

	std::cout << "Initializing s2\n";
	Something s2 { nrvo() }; // calls copy constructor

        return 0;
}
```
In C++14 or older, with copy elision disabled, the program will call the copy constructor 4 times:
1. Once when `rvo` returns `Something` to `main`.
2. Once when the return value of `rvo()` is used to initialize `s1`.
3. Once when `nrvo` returns `Something` to `main`.
4. Once when the return value of `nrvo()` is used to initialize `s2.

However, with copy elision enabled, the compiler can optimize away many unnecessary copies. For example, on Visual Studio 2022 the compiler will elide 3 (it does not elide the case where `nrvo()` returns by value), and GCC elides all 4 copy constructor calls.

#### Mandatory copy elision in C++17 (C++17 and later):
Prior to C++17, copy elision was strictly an optional optimization that compilers could make. In C++17, copy elision became mandatory in some cases. 

#### Summary:
- All forms of initialization (copy, direct, list) for class types involve selecting the appropriate constructor based on the provided arguments.
- Copy elision is a compiler optimization that eliminates unnecessary copies of objects in certain scenarios, such as when initializing an object with a temporary object of the same type.


---

### S16 — 14.16 Converting constructors and the explicit keyword
In a previous chapter we have seen type conversion and the concept of implicit type conversion (Where the compiler automatically converts a value from one type to another when needed). This allows us to do things like:
```cpp
#include <iostream>

void printDouble(double d) // has a double parameter
{
    std::cout << d;
}

int main()
{
    printDouble(5); // we're supplying an int argument

    return 0;
}
```
Where the compiler automatically converts the `int` value `5` to a `double` when calling the `printDouble` function.

#### User-defined conversions:
Now consider this example:
```cpp
#include <iostream>

class Foo
{
private:
    int m_x{};
public:
    Foo(int x)
        : m_x{ x }
    {
    }

    int getX() const { return m_x; }
};

void printFoo(Foo f) // has a Foo parameter
{
    std::cout << f.getX();
}

int main()
{
    printFoo(5); // we're supplying an int argument

    return 0;
}
```
In this version, `printFoo` has a parameter of type `Foo`, but we are passing an `int` argument (`5`). The compiler automatically converts the `int` value `5` to a `Foo` object by calling the constructor `Foo(int x)`. This is an example of a **user-defined conversion**, where the compiler uses a constructor to convert a value from one type to another. Unlike before, where we had all fundamental types, here we are converting from a fundamental type (`int`) to a program-defined class type (`Foo`).

#### Converting constructors:
In the above example, the compiler will find a function that lets it convert an `int` to a `Foo` object. The constructor `Foo(int x)` can be used for this purpose, so the compiler uses it to create a temporary `Foo` object initialized with the value `5`, which is then passed to the `printFoo` function.

Up to this point, we’ve typically used constructors to explicitly construct objects:
```cpp
Foo x { 5 }; // Explicitly convert int value 5 to a Foo
```
This basically takes an `int` value as input, and return a `Foo` object. In the context of a function call, we are trying to solve the same problem: we have an `int` value, but we need a `Foo` object:
```cpp
printFoo(5); // Implicitly convert int value 5 into a Foo
```
Here, we are providing an `int` value, but we need a `Foo` object. The compiler sees that the constructor `Foo(int x)` can be used to convert an `int` to a `Foo`, so it uses that constructor to create a temporary `Foo` object copy initialized with the value `5`, which is then passed to the `printFoo` function.

A constructor that can be used to perform such implicit conversions is called a **converting constructor**.

#### Only one user-defined conversion may be applied:
When performing implicit conversions, the compiler is only allowed to apply one user-defined conversion (i.e., call one converting constructor or conversion operator). For example, consider this code:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name{};

public:
    Employee(std::string_view name)
        : m_name{ name }
    {
    }

    const std::string& getName() const { return m_name; }
};

void printEmployee(Employee e) // has an Employee parameter
{
    std::cout << e.getName();
}

int main()
{
    printEmployee("Joe"); // we're supplying an string literal argument

    return 0;
}
```
In this version we swap `Foo` for `Employee`, and `int` for `std::string_view`. When we call `printEmployee("Joe");`, we pass a C-style string literal (`const char*`) to a function that expects an `Employee` object, and we have a converting constructor `Employee(std::string_view name)`.

You might be surprised that this version does not compile. The reason is that the compiler is only allowed to apply **one** user-defined conversion when performing implicit conversions. In this case, converting a C-style string literal (`const char*`) to an `Employee` object would require two conversions:
1. Convert the C-style string literal (`const char*`) to a `std::string_view` (using the `std::string_view` converting constructor).
2. Convert the `std::string_view` to an `Employee` object (using the `Employee` converting constructor).

There are two ways to make this example work:
1. Use a `std::string_view` literal (using the `sv` suffix) to directly provide a `std::string_view` argument and skip the first conversion:
    ```cpp
    int main()
    {
        using namespace std::literals;
        printEmployee( "Joe"sv); // now a std::string_view literal, that is directly convertible to Employee

        return 0;
    }
    ```
2. Explicitely construct an `Employee` rather than implicitely create one:
    ```cpp
    int main()
    {
        printEmployee(Employee{ "Joe" });

        return 0;
    }
    ```

#### When converting constructors go wrong:
Consider the following example:
```cpp
#include <iostream>

class Dollars
{
private:
    int m_dollars{};

public:
    Dollars(int d)
        : m_dollars{ d }
    {
    }

    int getDollars() const { return m_dollars; }
};

void print(Dollars d)
{
    std::cout << "$" << d.getDollars();
}

int main()
{
    print(5);

    return 0;
}
```
This will print:
```
$5
```
In this example, we have a `Dollars` class with a converting constructor that takes an `int` value. When we call the `print` function with an `int` argument (`5`), the compiler automatically converts the `int` to a `Dollars` object using the converting constructor.

Although this is woring, it is not clear if this was the actual intent of the programmer. What if the programmer mistakenly passed an `int` value to the `print` function, thinking it would print the integer value directly, rather than converting it to a `Dollars` object? This could lead to confusion and unexpected behavior.

To prevent this, it would be better if our `print(Dollar)` function could only accept `Dollars` objects, and not allow implicit conversions from `int` to `Dollars`. This can be achieved by marking the converting constructor as `explicit`.

#### The explicit keyword:
To fix this issue, we can use the **`explicit`** keyword, telling the compiler that the constructor should not be used as a converting constructor. Making a constructor `explicit` has two notable effects:
1. An explicit constructor cannot be used to do copy initialization or copy list initialization (e.g., `Dollars d = 5;` or `Dollars d = {5};` will not compile).
2. An explicit constructor cannot be used for implicit conversions (e.g., passing an `int` to a function that expects a `Dollars` object will not compile), since this uses copy initialization or copy list initialization.

Let's update the previous example to use `explicit`:
```cpp
#include <iostream>

class Dollars
{
private:
    int m_dollars{};

public:
    explicit Dollars(int d) // now explicit --> cannot be used as a converting constructor
        : m_dollars{ d }
    {
    }

    int getDollars() const { return m_dollars; }
};

void print(Dollars d)
{
    std::cout << "$" << d.getDollars();
}

int main()
{
    print(5); // compilation error because Dollars(int) is explicit

    return 0;
}
```
Now the compiler can no longer use the `Dollars(int)` constructor to implicitly convert an `int` to a `Dollars` object. Attempting to call `print(5);` will result in a compilation error, preventing potential confusion. You are only allowed to create `Dollars` objects explicitly with `Dollars d{5};` or `Dollars d(5);`.

#### Explicit constructors can be used for direct and direct list initialization:
Note that marking a constructor as `explicit` does not prevent its use for direct initialization or direct list initialization:
```cpp
// Assume Dollars(int) is explicit
int main()
{
    Dollars d1(5); // ok
    Dollars d2{5}; // ok
}
```
Both of these forms of initialization are allowed, even though the constructor is marked as `explicit`.

In the previous example, by making the `Dollars(int)` constructor explicit, we ensure that `Dollars` objects can only be created explicitly, preventing unintended implicit conversions. But what if we actually want to call `print` with an `int` value? The solution is simple: instead of having the compiler implicitely convert `5` to a `Dollars` object, we can explicitly create a `Dollars` object when calling `print`:
```cpp
print(Dollars{5}); // ok: explicitly create a Dollars object
```
This way, we make it clear that we intend to create a `Dollars` object with the value `5`, and then pass that object to the `print` function.
This is allowed because we can still use explicit constructors to list initialize objects.

Note that `static_cast` returns an object that is direct-initialized, so it will consider explicit constructors as well:
```cpp
print(static_cast<Dollars>(5)); // ok: static_cast will use explicit constructors
```

**Note:** The `explicit` keyword disallows copy initialization and copy list initialization, while still allowing direct initialization and direct list initialization.

#### Return by value and explicit constructors:
When we return a value from a function, if that value does not match the return type exactly, the compiler will attempt to convert it using implicit conversions, without using any explicit constructors. For example:
```cpp
#include <iostream>

class Foo
{
public:
    explicit Foo() // note: explicit (just for sake of example)
    {
    }

    explicit Foo(int x) // note: explicit
    {
    }
};

Foo getFoo()
{
    // explicit Foo() cases
    return Foo{ };   // ok, as we're explicitly creating a Foo object
    return { };      // error: can't implicitly convert initializer list to Foo

    // explicit Foo(int) cases
    return 5;        // error: can't implicitly convert int to Foo
    return Foo{ 5 }; // ok, as we're explicitly creating a Foo object
    return { 5 };    // error: can't implicitly convert initializer list to Foo
}

int main()
{
    return 0;
}
```
In this example, the `getFoo` function has a return type of `Foo`, but both constructors of `Foo` are marked as `explicit`. Therefore, when we try to return an empty initializer list (`return { };`) or an `int` value (`return 5;`), the compiler cannot use the explicit constructors to perform implicit conversions, resulting in compilation errors. However, when we explicitly create a `Foo` object using `Foo{ }` or `Foo{ 5 }`, the return statements are valid.
Additionally, `return { 5 };` is not allowed because it is considered an mplicit conversion from an initializer list to a `Foo` object, which cannot use explicit constructors.

#### Best practices for use of `explicit`:
The modern best practice is to make any constructor that will accept a single argument `explicit` by default. This includes constructors with multiple parameters where most of them have default values, effectively making them single-argument constructors. This prevents unintended implicit conversions that can lead to confusion and bugs.

If an implicit conversion is required, only non-explicit constructors will be considered. If no non-explicit constructor can be found to perform the conversion, the compiler will error.

If such a conversion is actually needed, it is trivial to convert the implicit conversion into an explicit definition using direct list initialization syntax (e.g., `Dollars{5}`) or `static_cast` (e.g., `static_cast<Dollars>(5)`).

In general, the following **should not** be made explicit:
- Copy (and move) constructors, as those do not perform conversions.

The following **are typically not** made explicit:
- Default constructors with no parameters, as they are only used to convert `{}` to a default object.
- Constructors that only accept multiple parameters without default values, as those cannot be used for implicit conversions.

The following **should usally** be made explicit:
- Converting constructors that accept a single parameter.

There are some cases when it does make sense to make a single-argument constructor non-explicit, and can be useful when all of the following conditions are met:
- The constructed object is semantically equivalent to the argument used to construct it.
- The conversion is performant (i.e., does not involve expensive operations).

For example, the `std::string_view` constructor that accepts a C-style string argument is non-explicit, as there is unlikely to be the case that we would not be okay with a C-style string being treated as a `std::string_view`. Conversely, the `std::string` constructor that accepts a `std::string_view` argument is explicit, as converting a `std::string_view` to a `std::string` involves allocating memory and copying data, which may not be desired implicitly.

> **Best Practice:** Make single-argument constructors `explicit` by default, unless there is a compelling reason not to.

> **Best Practice:** Do not make copy (or move) constructors `explicit`, as they do not perform conversions.

#### Summary:
- A converting constructor is a constructor that can be used to perform implicit conversions from one type to another.
- The compiler can use converting constructors to implicitly convert values when needed, such as when passing arguments to functions.
- The compiler is only allowed to apply one user-defined conversion when performing implicit conversions.
- The `explicit` keyword can be used to prevent a constructor from being used as a converting constructor, disallowing implicit conversions.
- Mark single-argument constructors as `explicit` by default to prevent unintended implicit conversions.


---

### S17 — 14.17 Constexpr aggregates and classes
In a previous chapter, we introduced `constexpr` and discussed how it can be used to create constant expressions that are either evaluated at compile time or runtime. We also discussed how `constexpr` can be applied to functions and constructors to enable compile-time evaluation of objects. For example:
```cpp
#include <iostream>

constexpr int greater(int x, int y)
{
    return (x > y ? x : y);
}

int main()
{
    std::cout << greater(5, 6) << '\n'; // greater(5, 6) may be evaluated at compile-time or runtime

    constexpr int g { greater(5, 6) };  // greater(5, 6) must be evaluated at compile-time
    std::cout << g << '\n';             // prints 6

    return 0;
}
```
In this example, the `greater` function is marked as `constexpr`, allowing it to be evaluated at compile time when used in a `constexpr` context (such as initializing a `constexpr` variable). When called in a non-`constexpr` context (such as printing to the console), it may be evaluated at runtime.

Now, consider the following example:
```cpp
#include <iostream>

struct Pair
{
    int m_x {};
    int m_y {};

    int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    Pair p { 5, 6 };                  // inputs are constexpr values
    std::cout << p.greater() << '\n'; // p.greater() evaluates at runtime

    constexpr int g { p.greater() };  // compile error: greater() not constexpr
    std::cout << g << '\n';

    return 0;
}
```
In this example, we have an aggregate struct named `Pair`, and `greater()` is now a member function. However, when we try to use `greater()` in a `constexpr` context (to initialize a `constexpr` variable), we get a compilation error because `greater()` is not marked as `constexpr`.

#### COnstexpr member functions:
Just like a normal function, a member function can be marked as `constexpr` to allow it to be evaluated at compile time when used in a `constexpr` context:
```cpp
#include <iostream>

struct Pair
{
    int m_x {};
    int m_y {};

    constexpr int greater() const // can evaluate at either compile-time or runtime
    // the const instead, means this function does not modify the object
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    Pair p { 5, 6 };
    std::cout << p.greater() << '\n'; // okay: p.greater() evaluates at runtime

    constexpr int g { p.greater() };  // compile error: p not constexpr
    std::cout << g << '\n';

    return 0;
}
```
In this updated example, we marked the `greater()` member function as `constexpr`, allowing it to be evaluated at compile time when used in a `constexpr` context. However, we still get a compilation error when trying to initialize a `constexpr` variable with `p.greater()`, because `p` itself is not a `constexpr` object.

#### Constexpr aggregates:
Okay, so it is easy right? We should just make the `p` object `constexpr` as well:
```cpp
#include <iostream>

struct Pair // Pair is an aggregate
{
    int m_x {};
    int m_y {};

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    constexpr Pair p { 5, 6 };        // now constexpr
    std::cout << p.greater() << '\n'; // p.greater() evaluates at runtime or compile-time

    constexpr int g { p.greater() };  // p.greater() must evaluate at compile-time
    std::cout << g << '\n';

    return 0;
}
```
Since `Pair` is an aggregate (it has no user-defined constructors, no private or protected non-static data members, no base classes, and no virtual functions), and aggregates implicitely support `constexpr` initialization, we are done and it works. Since now both `p` and `greater()` are `constexpr`, we can use `p.greater()` in a `constexpr` context to initialize the `g` variable.

#### Constexpr class objects and constexpr constructors:
Now, let's make our `Pair` a non-aggregate by adding private data members and a user-defined constructor:
```cpp
#include <iostream>

class Pair // Pair is no longer an aggregate
{
private:
    int m_x {};
    int m_y {};

public:
    Pair(int x, int y): m_x { x }, m_y { y } {}

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    constexpr Pair p { 5, 6 };       // compile error: p is not a literal type
    std::cout << p.greater() << '\n';

    constexpr int g { p.greater() };
    std::cout << g << '\n';

    return 0;
}
```
This example is almost identical to the previous one, except that `Pair` is now a class with private data members and a user-defined constructor. When we try to create a `constexpr` object of type `Pair`, we get a compilation error because `Pair` is not a literal type. What does this mean?

In C++, a **literal type** is any type for which it might be possible to create an object within a constant expression. In other words, an object cannot be constexpr unless the type qualifies as a literal type. And our non-aggregate `Pair` class does not qualify as a literal type.

Literal types includes:
- Scalar types (those holding a single value, such as `int`, `char`, `float`, and pointers).
- Reference types.
- Most aggregate types (structs and arrays) that contain only literal types.
- Classes that have a constexpr constructor.

Now we see why our `Pair` class does not qualify as a literal type: it does not have a `constexpr` constructor. Basicaly, when the object is created using the user-defined constructor, the constructor must be `constexpr` in order for the object to be `constexpr`, otherwise you will get a non-literal type error. The fix then it is easy:
```cpp
#include <iostream>

class Pair
{
private:
    int m_x {};
    int m_y {};

public:
    constexpr Pair(int x, int y): m_x { x }, m_y { y } {} // now constexpr

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    constexpr Pair p { 5, 6 };
    std::cout << p.greater() << '\n';

    constexpr int g { p.greater() };
    std::cout << g << '\n';

    return 0;
}
```
By marking the constructor as `constexpr`, our `Pair` class now qualifies as a literal type, allowing us to create `constexpr` objects of type `Pair`.

> **Best Practice:** If you want your class to be able to evaliuate at compile time, make all member functions and constructor `constexpr`.

#### Constexpr members may be needed with non-`constexpr`/non-`const` objects:
In the example before, since the initializer of a `constexpr` variable `g` must be a constant expression, it is obvious that both `p` and `greater()` must be `constexpr`. However, if you replace `p.greater()` with a constexpr function, things get a little bit less obvious:
```cpp
#include <iostream>

class Pair
{
private:
    int m_x {};
    int m_y {};

public:
    constexpr Pair(int x, int y): m_x { x }, m_y { y } {}

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

constexpr int init()
{
    Pair p { 5, 6 };    // requires constructor to be constexpr when evaluated at compile-time
    return p.greater(); // requires greater() to be constexpr when evaluated at compile-time
}

int main()
{
    constexpr int g { init() }; // init() evaluated in compile-time context
    std::cout << g << '\n';

    return 0;
}
```
Remember that a constexpr function can evaluate at either runtime or compile-time. And when a constexpr function evaluates at compile-time, it can only call functions capable of evaluating at compile-time. In the case of a class type, that means constexpr member functions.

In this example, the `init()` function is marked as `constexpr`, and it creates a `Pair` object and calls the `greater()` member function. When `init()` is evaluated in a compile-time context (such as when initializing the `constexpr` variable `g`), both the constructor and the `greater()` function must be `constexpr` to allow for compile-time evaluation. If either the constructor or the `greater()` function were not `constexpr`, the program would fail to compile when `init()` is evaluated at compile time, giving an error.

#### Constexpr member functions may be const or non-const (C++14 and later):
In C++11, non-static constexpr member functions are implicitly const (except constructors).

However, starting from C++14, non-static constexpr member functions are no longer implicitly const. This means that if you want a constexpr function to be const, you must explicitly mark it as const. This allows constexpr member functions to modify the state of the object when evaluated at runtime, while still being able to be evaluated at compile time when used in a constexpr context.

#### Constexpr non-const member functions can change data members (Optional):
A constexpr non-const member function can change data members of the class, so long as the implicit object isn’t const. This is true even if the function is evaluating at compile-time.
```cpp
#include <iostream>

class Pair
{
private:
    int m_x {};
    int m_y {};

public:
    constexpr Pair(int x, int y): m_x { x }, m_y { y } {}

    constexpr int greater() const // constexpr and const
    {
        return (m_x > m_y  ? m_x : m_y);
    }

    constexpr void reset() // constexpr but non-const
    {
        m_x = m_y = 0; // non-const member function can change members
    }

    constexpr const int& getX() const { return m_x; }
};

// This function is constexpr
constexpr Pair zero()
{
    Pair p { 1, 2 }; // p is non-const
    p.reset();       // okay to call non-const member function on non-const object
    return p;
}

int main()
{
    Pair p1 { 3, 4 };
    p1.reset();                     // okay to call non-const member function on non-const object
    std::cout << p1.getX() << '\n'; // prints 0

    Pair p2 { zero() };             // zero() will be evaluated at runtime
    p2.reset();                     // okay to call non-const member function on non-const object
    std::cout << p2.getX() << '\n'; // prints 0

    constexpr Pair p3 { zero() };   // zero() will be evaluated at compile-time
//    p3.reset();                   // Compile error: can't call non-const member function on const object
    std::cout << p3.getX() << '\n'; // prints 0

    return 0;
}
```
As we go over this example, just remember:
- A non-const member function can modify members of non-const objects.
- A constexpr member function can be called in either runtime contexts or compile-time contexts.

In the case of `pi` and `p2`, both are non-const objects, so we can call the non-const `reset()` member function top modify their members. The fact that `reset()` is `constexpr` does not matter here because it is being called in a runtime context.

The `p2` cse is similar. The `zero()` function is `constexpr`, but when it is called to initialize `p2`, it is evaluated at runtime, so `p2` is a non-const object, and we can call the non-const `reset()` member function on it.

However, in the case of `p3`, it is a `constexpr` object, which means it is implicitly const and must have a constant expression initializer. Therefore, this call to `zero()` must be evaluated at compile-time, and so we can only call constexpr functions. Inside `zero()`, `p`p is non-const (which is allowed, even in a compile-time context), however, because we are in a compile-time context, the constructor used to create `p` must be `constexpr`, and we can only call `constexpr` member functions on `p`. However, since `reset()` is a non-const member function, we cannot call it on `p` when it is being evaluated at compile-time, resulting in a compilation error.

#### Constexpr functions that return const references (or pointers) (Optional):
Usually you will not see `constexpr` and `const` next to each other, but one case where this does happen is when a `constexpr` function returns a `const` reference (or pointer). This is useful when you want to return a reference (or pointer) to a member of a `constexpr` object without allowing modification of that member. For example:
```cpp
constexpr const int& getX() const { return m_x; }
```
In this example, the `constexpr` indicates that the member function can be evaluated at compile time, the `const int&` indicates that the function returns a reference to a constant integer, and the `const` at the end indicates that the member function cannot not modify the object.

#### Summary:
- A class must be a literal type in order to create `constexpr` objects of that class.
- A class qualifies as a literal type if it has a `constexpr` constructor.
- Member functions that need to be evaluated at compile time must be marked as `constexpr`.
- Constexpr member functions can be either `const` or non-`const` (C++14 and later).


---

### SX - 14.x Summary and quiz
Have a look at the original summary, and enjoy doing the quiz!

PS: solutions are inside `exercises/sx-questions` folder. Enjoy! :)


---

## 🧭 Summary

Classes are the core abstraction mechanism of C++: they let you bundle data and behavior, enforce invariants with constructors and access control, and expose a clean public interface while hiding implementation details.  
In this chapter, you learned how to design such types, control how objects are created and copied, and manage conversions and compile-time behavior.

### 🧱 Core Concepts You Mastered:

- Difference between **procedural** vs **object‑oriented** design (`draw(rect)` vs `rect.draw()`).
- Defining a **class** with data + member functions, and using the implicit `this` object.
- Using **`public` / `private`** and access functions (`getX()`, `setX()`) to enforce invariants and hide data.
- Writing **constructors** and **member initializer lists** to guarantee properly initialized objects:
  - `Foo(int x) : m_x{x} {}`
- Understanding **default constructors**, **delegating constructors**, and when the compiler generates one for you.
- Using **copy constructors** and recognizing how **copy elision** avoids unnecessary copies.
- Controlling implicit conversions with **`explicit`** (that makes constructors not available for implicit conversions) constructors to prevent surprising code like `foo(42)` constructing unintended objects.
- Recognizing and using **temporary objects** safely in expressions.
- Marking suitable constructors and member functions as **`constexpr`** for compile‑time computation.