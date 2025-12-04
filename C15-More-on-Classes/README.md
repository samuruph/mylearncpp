# Chapter 15 - More on Classes

## 🧭 Overview
TODO: write overview

---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch15_first
./build/ch15_first
```

---

## 🎯 Learning Outcomes

By the end of this chapter, you’ll be able to:

- TODO: write outcomes

---

## Sections

### S01 — 15.1 The hidden `this` pointer and member function chainning
One of the common questions realted to C++ classes is: *"When a member function is called, how does C++ keep track of which object the function is being called on?"* The answer to this question lies in the concept of the hidden `this` pointer. First, let's define a simple class to illustrate this concept:
```cpp
#include <iostream>

class Simple
{
private:
    int m_id{};

public:
    Simple(int id)
        : m_id{ id }
    {
    }

    int getID() const { return m_id; }
    void setID(int id) { m_id = id; }

    void print() const { std::cout << m_id; }
};

int main()
{
    Simple simple{1};
    simple.setID(2);

    simple.print();

    return 0;
}
```
This gives the output:
```
2
```
In this example, we have a class `Simple` with a private member variable `m_id` and three member functions: `getID()`, `setID(int id)`, and `print()`. Somehow, when calling `simple.setID(2);`, the member function `setID` knows that it is operating on object `simple`, and that `m_id` refers to `simple`'s member variable (`simple.m_id`). This is where the hidden `this` pointer comes into play. In this lesson, we will talk about this pointer and how it works behind the scenes.

#### The hidden `this` pointer:
Inside every member function, the keyword **`this`** is a const pointer that holds the address of the current implicit object parameter. In other words, `this` points to the object for which the member function is called. For example, in the `setID` function, `this` points to the `simple` object when we call `simple.setID(2);`. Therefore, when we write `m_id = id;`, it is equivalent to writing `this->m_id = id;`, which updates the `m_id` of the `simple` object.

Most of the time, we do not mention `thi` explicitly, as the compiler automatically adds it for us, but here a version of the `setID` function that uses `this` explicitly:
```cpp
#include <iostream>

class Simple
{
private:
    int m_id{};

public:
    Simple(int id)
        : m_id{ id }
    {
    }

    int getID() const { return this->m_id; } // use `this` pointer to access the implicit object and operator-> to select member m_id
    void setID(int id) { this->m_id = id; } // use `this` pointer to access the implicit object and operator-> to select member m_id

    void print() const { std::cout << this->m_id; } // use `this` pointer to access the implicit object and operator-> to select member m_id
};

int main()
{
    Simple simple{ 1 };
    simple.setID(2);

    simple.print();

    return 0;
}
```
These two member function work exactly the same:
```cpp
void print() const { std::cout << m_id; }       // implicit use of this
void print() const { std::cout << this->m_id; } // explicit use of this
```

When we compile the program, the compiler automatically adds the hidden `this` pointer.

#### How is `this` set ?
Let's take a closer look at this function:
```cpp
simple.setID(2);
```
from here, it looks like that thuis member function has only one argument, but in reality, the compiler transforms this call to something like this:
```cpp
Simple::setID(&simple, 2); // note that simple has been changed from an object prefix to a function argument!
```
Resulting in two arguments being passed to the `setID` function: a pointer to the `simple` object (i.e., `&simple`) and the integer value `2`. The first argument is assigned to the hidden `this` pointer, allowing the member function to access and modify the member variables of the `simple` object.

This is now a standard function call. But then, we will need to modify the member function definition to accept this additional argument, rewriting this:
```cpp
void setID(int id) { m_id = id; }
```
in something like (it is implementation-defined, so it may vary between compilers) this:
```cpp
static void setID(Simple* const this, int id) { this->m_id = id; }
```
Here you can note that the `setID` function is now a static function that takes a pointer to a `Simple` object as its first argument (the hidden `this` pointer) and an integer `id` as its second argument. Inside the function, we use the `this` pointer to access and modify the `m_id` member variable of the `Simple` object.

Overall, putting all together:
1. When we call a member function on an object (`simple.setID(2);`), the compiler actually calls a standard function, passing the address of the object as the first argument (`Simple::setID(&simple, 2);`).
2. The function has a hidden parameter named `this`, which is a pointer to the object on which the member function was called (`Simple* const this`).
3. Inside the member function, we can use the `this` pointer to access and modify the member variables of the object.

Good to know that all of this happens behind the scenes, and as a programmer, you typically don't need to worry about it. You can simply call member functions on objects, and the compiler takes care of passing the `this` pointer for you. Uou just need to remember that **all non-static member functions** have a hidden `this` pointer that points to the object on which the function was called.

> **Note:** All non-static member functions have a hidden `this` const pointer. Static member functions do not have a `this` pointer because they are not associated with any particular object instance.

#### `this` always points to the object being operated on:
New programmers may be confused on how many `this` pointers exist. Each member function has a single `this` pointer that points to the object on which the member function was called. If you have multiple objects of the same class, each object will have its own `this` pointer when its member functions are called. For example:
```cpp
int main()
{
    Simple a{1}; // this = &a inside the Simple constructor
    Simple b{2}; // this = &b inside the Simple constructor
    a.setID(3); // this = &a inside member function setID()
    b.setID(4); // this = &b inside member function setID()

    return 0;
}
```
In this example, when we create the object `a`, the `this` pointer inside the constructor points to `a`. Similarly, when we create the object `b`, the `this` pointer inside the constructor points to `b`. When we call `a.setID(3);`, the `this` pointer inside the `setID` function points to `a`, and when we call `b.setID(4);`, the `this` pointer inside the `setID` function points to `b`. So, each object has its own `this` pointer when its member functions are called.

#### Explicitly referencing `this`:
While you typically don't need to use the `this` pointer explicitly, there are some situations where it can be useful.

First, if you have a meber function that has the parameter with the same name as a data member, you can use the `this` pointer to disambiguate between the two. For example:
```cpp
struct Something
{
    int data{}; // not using m_ prefix because this is a struct

    void setData(int data)
    {
        this->data = data; // this->data is the member, data is the local parameter
    }
};
```
Using `this->data` makes it clear that we are referring to the member variable `data`, while `data` refers to the parameter of the `setData` function.

In general, using prefix `m_` for member variables (as we have done so far) is a better way to avoid such name conflicts.

#### Returning `*this`:
Second, it can be sometimes be useful to have a member function return the current object. This is often done to allow for member **function chaining** (or **method chaining**), where multiple member functions are called in a single statement. To do this, you can return `*this` from the member function.
For example, consider this simple example:
```cpp
std::cout << "Hello, " << userName;
```
The compiler evaluates the expression as follows:
```cpp
(std::cout << "Hello, ") << userName;
```
First, `operator<<` uses `std::cout` and `"Hello, "` as arguments, then it nees to return something so that the second `operator<<` can use it as the left-hand operand. It returns `std::cout` by reference, allowing the second `operator<<` to use it.
In this way, the compiler will have:
```cpp
(std::cout) << userName;
```
allowing the chaining of multiple `operator<<` calls.
In this way, we only need to specify the object once (`std::cout`), and we can chain multiple calls to `operator<<`.

Similarly, we can implement member function chaining in our own classes by returning `*this` from member functions. If we have a class like this:
```cpp
class Calc
{
private:
    int m_value{};

public:

    void add(int value) { m_value += value; }
    void sub(int value) { m_value -= value; }
    void mult(int value) { m_value *= value; }

    int getValue() const { return m_value; }
};
```
In order to add 5, subtract 3, and multiply by 4, you would need to write:
```cpp
#include <iostream>

int main()
{
    Calc calc{};
    calc.add(5); // returns void
    calc.sub(3); // returns void
    calc.mult(4); // returns void

    std::cout << calc.getValue() << '\n';

    return 0;
}
```
This works, but it requires three separate statements to perform the calculations. Instead, we can modify the member functions to return `*this`, allowing us to chain the calls together:
```cpp
class Calc
{
private:
    int m_value{};

public:
    Calc& add(int value) { m_value += value; return *this; }
    Calc& sub(int value) { m_value -= value; return *this; }
    Calc& mult(int value) { m_value *= value; return *this; }

    int getValue() const { return m_value; }
};
```
Now, we can chain the member function calls together in a single statement:
```cpp
#include <iostream>

int main()
{
    Calc calc{};
    calc.add(5).sub(3).mult(4); // method chaining (from left to right)

    std::cout << calc.getValue() << '\n';

    return 0;
}
```
This will give the same output as before, but now we can perform the calculations in a single statement by chaining the member function calls together. This will first add 5 to `m_value`, then subtract 3, and finally multiply the result by 4 to the same object `calc`.

#### Resetting a class back to default state:
If your class has a default constructor, you could be interested in resetting an object back to its default state.
As we saw in a previous chapter, constructors are only for initialization of new objects, and should not be called directly. Doing so results in undefined behavior.

The best way to reset an object back to its default state is to create a member function (`reset()` for example) that sets all member variables back to their default values. For example:
```cpp
void reset()
{
    *this = {}; // value initialize a new object and overwrite the implicit object
}
```
This `reset()` function uses the assignment operator to assign a newly value-initialized object (created using `{}`) to the current object (`*this`). This effectively resets all member variables to their default values.

Here is a full program that demonstrates this:
```cpp
#include <iostream>

class Calc
{
private:
    int m_value{};

public:
    Calc& add(int value) { m_value += value; return *this; }
    Calc& sub(int value) { m_value -= value; return *this; }
    Calc& mult(int value) { m_value *= value; return *this; }

    int getValue() const { return m_value; }

    void reset() { *this = {}; }
};


int main()
{
    Calc calc{};
    calc.add(5).sub(3).mult(4);

    std::cout << calc.getValue() << '\n'; // prints 8

    calc.reset();

    std::cout << calc.getValue() << '\n'; // prints 0

    return 0;
}
```
This program defines a `Calc` class with member functions for addition, subtraction, multiplication, and resetting the object to its default state. The `reset()` function uses the assignment operator to assign a newly value-initialized object to the current object, effectively resetting all member variables to their default values.

When we run this program, it will output:
```
8
0
```
showing that the `calc` object was successfully reset to its default state after performing some calculations.

#### `this` and const objects:
For non-const member functions, `this` is a const pointer (meaning that the pointer itself cannot be changed to point to another object), to a non-const value. This means that `this` cannot be pointed at something else, but the object pointing to may be modified).

However, for const member functions, `this` is a const pointer to a const value. This means that within a const member function, you cannot modify the object that `this` points to. For example, if you attempt to modify a member variable inside a const member function, the compiler will generate an error:
```cpp
error C2662: 'int Something::getValue(void)': cannot convert 'this' pointer from 'const Something' to 'Something &'
error: passing 'const Something' as 'this' argument discards qualifiers [-fpermissive]
```
or similar error messages depending on your compiler. This means that const member functions are not allowed to modify the state of the object they are called on.

#### Why `this` a pointer and not a reference?
Since the `this` pointer always points to the implicit object (and can never be a null pointer unless you have done something to cause undefined behaviors), you may be wondering why `this` is a pointer and not a reference. 
The reason is that when `this` was added to C++, references didn't exist yet. Pointers were the only way to refer to other objects at that time. Therefore, `this` was implemented as a pointer to maintain compatibility with the existing C++ language features.

If `this` was implemented today, it would likely be a reference, as references are generally safer and easier to use than pointers (for example C# and Java use references for `this`).

#### Summary:
- Inside every non-static member function, there is a hidden `this` pointer that points to the object on which the member function was called.
- The compiler automatically adds the `this` pointer as the first argument to non-static member functions.
- You can use the `this` pointer explicitly to refer to the current object, but it is usually not necessary.
- Returning `*this` from a member function allows for method chaining.


---

### S02 — 15.2 Classses and header files
All of the classes that we have written so far have been simple enough that we have been able to implement the member functions directly inside the class definition itself. For example, here is a simple `Date` class where all member functions are implemented inside the class definition:
```cpp
#include <iostream>

class Date
{
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day)
        : m_year { year }
        , m_month { month }
        , m_day { day}
    {
    }

    void print() const { std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n"; }

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
};

int main()
{
    Date d { 2015, 10, 14 };
    d.print();

    return 0;
}
```
However, as classes get longer and more complicated, having all the member function definitions inside the class can make the class harder to manage and work with. Using an already-written class only requires understanding its `public` interface (the public member functions), not how the class works underneath the hood. The member function implementations clutter up the public interface with details that aren’t relevant to actually using the class.

C++ helps us in this by letting us seprata the "declaration" of a class from its "implementation". The declaration of a class includes the class name, its member variables, and the signatures of its member functions (but not their implementations). The implementation of a class includes the actual code for the member functions.

Here is the same `Date` class, but with the member function implementations separated from the class declaration:
```cpp
#include <iostream>

class Date
{
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day); // constructor declaration

    void print() const; // print function declaration

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const  { return m_day; }
};

Date::Date(int year, int month, int day) // constructor definition
    : m_year{ year }
    , m_month{ month }
    , m_day{ day }
{
}

void Date::print() const // print function definition
{
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
};

int main()
{
    const Date d{ 2015, 10, 14 };
    d.print();

    return 0;
}
```

Memebr functions can be defined outside the class by specifying the class name followed by the scope resolution operator (`::`) before the function name. This tells the compiler that the function being defined is a member of the specified class.

#### Putting class definitions in a header file:
In larger projects, it is common practice to put class declarations in header files (`.h` or `.hpp` files) and the member function implementations in source files (`.cpp` files). This helps to keep the code organized and makes it easier to manage large codebases. In this way, as we did for functions, you can include the header file wherever you need to use the class, without needing to include the implementation details.

Here is how you can separate the `Date` class into a header file and a source file:

Datae.h (class declaration):
```cpp
#ifndef DATE_H
#define DATE_H

class Date
{
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day);

    void print() const;

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
};

#endif // DATE_H
```

Date.cpp (class implementation):
```cpp
#include "Date.h"

Date::Date(int year, int month, int day) // constructor definition
    : m_year{ year }
    , m_month{ month }
    , m_day{ day }
{
}

void Date::print() const // print function definition
{
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
};
```

Main.cpp (using the Date class):
```cpp
#include <iostream>
#include "Date.h"

int main()
{
    const Date d{ 2015, 10, 14 };
    d.print();

    return 0;
}
```
In this example, the `Date` class declaration is placed in the `Date.h` header file, while the member function implementations are placed in the `Date.cpp` source file. The `Main.cpp` file includes the `Date.h` header file to use the `Date` class.

When compiling the program, you need to compile both the `Date.cpp` and `Main.cpp` files together to create the final executable.

> **Best Practice:** Prefer to put your class definitions in a header file and the member function implementations in a source file. This helps to keep your code organized and makes it easier to manage large codebases. Trivial member functions (like simple getters and setters) can be defined inside the class definition in the header file for simplicity.

#### Doesn’t defining a class in a header file violate the one-definition rule if the header is #included more than once?
Types are exempt from the one-definition rule (ODR) as long as each definition is identical. This means that you can define a class in a header file and include that header file in multiple source files without violating the ODR, as long as the class definition is the same in each inclusion.

Including the header file multiple times in the same source file can lead to redefinition errors. To prevent this, we use include guards (as shown in the `Date.h` example) or `#pragma once` to ensure that the header file is only included once per compilation unit.

#### Inline member functions:
Member functions are not exempt from the one-definition rule instead. So you may wonder how we avoid ODR violations when defining member functions inside the class definition in a header file that is included in multiple source files.

In general, member functions defined **inside** the class definition are implicitly treated as `inline` functions by the compiler. This means that you can define member functions inside the class definition in a header file without violating the ODR, as long as the definitions are identical in each inclusion.

Instead, member functions defined **outside** the class definition in a header file are not implicitly treated as `inline` functions. This is why such member functions should be defined in a source file (`.cpp` file) to avoid ODR violations.

Alternatively, member functions defined outside the class definition in a header file can be explicitly marked as `inline` to avoid ODR violations. For example:

Date.h:
```cpp
#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date
{
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day);

    void print() const;

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
};

inline Date::Date(int year, int month, int day) // now inline
    : m_year{ year }
    , m_month{ month }
    , m_day{ day }
{
}

inline void Date::print() const // now inline
{
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
};

#endif
// DATE_H
```
In this way, the member functions are explicitly marked as `inline`, allowing them to be defined in the header file without violating the ODR.

#### Inline expansion of member functions:
Generally, the compiler **must** see the **full** definition of a function in order to inline it (i.e., replace the function call with the actual function code). This is why member functions defined inside the class definition are implicitly treated as `inline`, as the compiler can see their full definitions whenever the header file is included.

#### So why not putting everything in the header file?
While putting everything in the header file compiles, there are few reasons why this is not a good idea:
- Defining all member functions inside the class definition clutters up the public interface of the class, making it harder to read and understand.
- If you change any of the code in the header, then all source files that include that header need to be recompiled, which can slow down compilation times in large projects. Instead, if you put member function implementations in a source file, only that source file needs to be recompiled when you make changes.


There are few exceptions where putting everything in the header file is acceptable:
- For small classes that are used in only one or two source files.
- If a class has a small number of non-trivial member functions that are unlikely to change.
- In modern C++, classes or libraries are increasingly distributed as header-only libraries, where all code is in header files for ease of distribution and use. This make the distribution and usage easier, but may lead to longer compilation times.
- For template classes, which must be defined entirely in header files to allow the compiler to generate code for different template instantiations.

#### Default arguments for member functions:
In a previous chapter, we said: "If the function has a forward declaration (especially one in a header file), put the default argument there. Otherwise, put the default argument in the function definition".

Because member functions are typically declared in header files and defined in source files, the best practice for member functions is simpler: **always put the default argument inside the class definition**.

> **Best Practice:** Put any default arguments for member functions inside the class definition.

For example:
```cpp
class Example
{
public:
    void func(int x = 42); // default argument in class definition
};

void Example::func(int x) // no default argument in function definition
{
    // function implementation
}
```

#### Libraries:
Throughout your programs, you’ve used classes that are part of the standard library, such as `std::string`. To use these classes, you simply include the appropriate header file (e.g., `<string>`) without having to add any code files (e.g., `string.cpp`) to your project.

The header files provide the declarations that the compiler requires in order to validate that the programs you’re writing are syntactically correct. However, the implementations for the classes that belong to the C++ standard library are contained in a precompiled file that is linked in automatically at the link stage. You never see the code.

Most of the time, libraries provide header files (that you will need to include in your code) and precompiled binary files (that you will need to link against when building your program). This way, you can use the classes and functions provided by the library without needing to see or modify their implementations.

This has several advantages:
- You don’t need to worry about how the library works internally; you just need to understand its public interface.
- You can use libraries that have been optimized for performance without needing to understand the optimizations.
- You can use libraries that have been written by other people without needing to read or understand their code.
- You can distribute your code without needing to distribute the source code for the libraries you’re using.

#### Summary:
- Separating class declarations from their implementations helps to keep code organized and easier to manage.
- Class declarations are typically placed in header files, while member function implementations are placed in source files.
- Member functions defined inside the class definition are implicitly treated as `inline` functions.
- Default arguments for member functions should be placed inside the class definition.


---

### S03 — 15.3 Nested types (member types)
COnsider the following short program:
```cpp
#include <iostream>

enum class FruitType
{
	apple,
	banana,
	cherry
};

class Fruit
{
private:
	FruitType m_type { };
	int m_percentageEaten { 0 };

public:
	Fruit(FruitType type) :
		m_type { type }
	{
	}

	FruitType getType() { return m_type; }
	int getPercentageEaten() { return m_percentageEaten; }

	bool isCherry() { return m_type == FruitType::cherry; }

};

int main()
{
	Fruit apple { FruitType::apple };

	if (apple.getType() == FruitType::apple)
		std::cout << "I am an apple";
	else
		std::cout << "I am not an apple";

	return 0;
}
```
This program defines an `enum class` named `FruitType` to represent different types of fruit. The `Fruit` class uses this `enum class` to specify the type of fruit it represents. The `main` function creates an instance of the `Fruit` class and checks its type using the `getType` member function.

While this approach works, it can lead to namespace pollution if you have many related types. To avoid this, C++ allows you to define types inside classes.

#### Nested types (member types):
So far, we have seen class types with two different kinds of members:
1. Member variables
2. Member functions

However, classes can also contain other types as members. These are called **nested types** or **member types**. Nested types can be classes, structs, enums, or type aliases defined within the scope of another class.
To create a nested type, you simply define the type inside the class definition. For example:
```cpp
#include <iostream>

class Fruit
{
public:
	// FruitType has been moved inside the class, under the public access specifier
        // We've also renamed it Type and made it an enum rather than an enum class
	enum Type
	{
		apple,
		banana,
		cherry
	};

private:
	Type m_type {};
	int m_percentageEaten { 0 };

public:
	Fruit(Type type) :
		m_type { type }
	{
	}

	Type getType() { return m_type;  }
	int getPercentageEaten() { return m_percentageEaten;  }

	bool isCherry() { return m_type == cherry; } // Inside members of Fruit, we no longer need to prefix enumerators with FruitType::
};

int main()
{
	// Note: Outside the class, we access the enumerators via the Fruit:: prefix now
	Fruit apple { Fruit::apple };

	if (apple.getType() == Fruit::apple)
		std::cout << "I am an apple";
	else
		std::cout << "I am not an apple";

	return 0;
}
```
In this example, we moved the `FruitType` enum class inside the `Fruit` class and renamed it to `Type`. Now, the `Type` enum is a nested type within the `Fruit` class. Inside the member functions of `Fruit`, we can access the enumerators directly without needing to prefix them with `Fruit::Type::`. However, outside the class, we still need to use the `Fruit::` prefix to access the enumerators. Note that we had to change our enumerated from scoped to unscoped, since the class itself provides the necessary scoping.

> **Best Practice:** Define any nested types at the top of the class definition, before any member variables or member functions. This is required since nested types must be fully defined before they are used in member variable declarations or member function definitions.

#### Nested typedefs and type aliases:
Class types can also contain nested type aliases or typedefs(`using` or `typedef`). This can be useful for defining types that are closely related to the class. For example:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
public:
    using IDType = int; // nested type alias for employee ID type

private:
    std::string m_name{};
    IDType m_id{};
    double m_wage{};

public:
    Employee(std::string_view name, IDType id, double wage)
        : m_name { name }
        , m_id { id }
        , m_wage { wage }
    {
    }

    const std::string& getName() { return m_name; }
    IDType getId() { return m_id; } // can use unqualified name within class
};

int main()
{
    Employee john { "John", 1, 45000 };
    Employee::IDType id { john.getId() }; // must use fully qualified name outside class

    std::cout << john.getName() << " has id: " << id << '\n';

    return 0;
}
```
This prints:
```
John has id: 1
```
In this example, we defined a nested type alias `IDType` inside the `Employee` class to represent the type of employee IDs (`int`). Inside the class, we can use `IDType` without qualification, but outside the class, we need to use the fully qualified name `Employee::IDType`.

For example, as for now, `std::string` defines 10 nested typedefs!

#### Nested classes and access to outer class members:
It is quite uncommon to define a class inside another class, but it is still possible. In C++, a nested class does not have access to the `this` pointer of the outer class. Therefore, a nested class cannot directly access the member variables or member functions of the outer class unless it has an instance of the outer class to work with. Here is an example to illustrate this:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
public:
    using IDType = int;

    class Printer
    {
    public:
        void print(const Employee& e) const
        {
            // Printer can't access Employee's `this` pointer
            // so we can't print m_name and m_id directly
            // Instead, we have to pass in an Employee object to use
            // Because Printer is a member of Employee,
            // we can access private members e.m_name and e.m_id directly
            std::cout << e.m_name << " has id: " << e.m_id << '\n';
        }
    };

private:
    std::string m_name{};
    IDType m_id{};
    double m_wage{};

public:
    Employee(std::string_view name, IDType id, double wage)
        : m_name{ name }
        , m_id{ id }
        , m_wage{ wage }
    {
    }

    // removed the access functions in this example (since they aren't used)
};

int main()
{
    const Employee john{ "John", 1, 45000 };
    const Employee::Printer p{}; // instantiate an object of the inner class
    p.print(john);

    return 0;
}
```
This prints:
```
John has id: 1
```
In this example, we defined a nested class `Printer` inside the `Employee` class. The `Printer` class has a member function `print` that takes an `Employee` object as a parameter and prints its name and ID. Since `Printer` is a member of `Employee`, it can access the private members of the `Employee` object passed to it.

In one case, nested classes are actually used. This is the case of **iterators** (see later chapters), where the iterator class is defined inside the container class (e.g., `std::vector::iterator`). for example, `std::string::iterator` is a nested class inside `std::string`.

#### Nested types and forward declarations:
A nested type can be forward declarated within the class that contains it. The nested type can then be defined later, either within the enclosing class, or outside of it. For example:
```cpp
#include <iostream>

class outer
{
public:
    class inner1;   // okay: forward declaration inside the enclosing class okay
    class inner1{}; // okay: definition of forward declared type inside the enclosing class
    class inner2;   // okay: forward declaration inside the enclosing class okay
};

class inner2 // okay: definition of forward declared type outside the enclosing class
{
};

int main()
{
    return 0;
}
```
However, a nested type cannot be forward declared prior to the definition of the enclosing class:
```cpp
#include <iostream>

class outer;         // okay: can forward declare non-nested type
class outer::inner1; // error: can't forward declare nested type prior to outer class definition

class outer
{
public:
    class inner1{}; // note: nested type declared here
};

class outer::inner1; // okay (but redundant) since nested type has already been declared as part of outer class definition

int main()
{
    return 0;
}
```
This results in a compilation error because the compiler does not yet know about the `outer` class when it encounters the forward declaration of `outer::inner1`.

> **Best Practice:** Avoid forward declaring nested types outside of their enclosing class. Instead, define them directly within the enclosing class or after the enclosing class definition.

#### Summary:
- Classes can contain nested types (member types) such as enums, structs, classes, and type aliases.
- Nested types help to organize related types and avoid namespace pollution.
- Nested types are typically defined at the top of the class definition.


---

### S04 — 15.4 Introduction to destructors
#### The cleanup problem:
Let’s say that you are writing a program that needs to send some data over a network. However, establishing a connection to the server is expensive, so you want to collect a bunch of data and then send it all at once. Such a class might be structured like this:
```cpp
// This example won't compile because it is (intentionally) incomplete
class NetworkData
{
private:
    std::string m_serverName{};
    DataStore m_dataQueue{};

public:
	NetworkData(std::string_view serverName)
		: m_serverName { serverName }
	{
	}

	void addData(std::string_view data)
	{
		m_dataQueue.add(data);
	}

	void sendData()
	{
		// connect to server
		// send all data
		// clear data
	}
};

int main()
{
    NetworkData n("someipAddress");

    n.addData("somedata1");
    n.addData("somedata2");

    n.sendData();

    return 0;
}
```
In this example, the `NetworkData` class is responsible for managing a connection to a server and sending data. The `addData` member function adds data to a queue, and the `sendData` member function connects to the server, sends all the data, and clears the queue.

However, this `NetworkData` class has a problem: what happens if the user of the class forgets to call `sendData()` before the `NetworkData` object goes out of scope? In that case, any data that was added to the queue will be lost, and the connection to the server will not be properly closed. So, it relies on the `sendData()` being explicitly called by the user of the class, before the object is destroyed or the program ends.

Consider a slightly more complex example:
```cpp
bool someFunction()
{
    NetworkData n("someipAddress");

    n.addData("somedata1");
    n.addData("somedata2");

    if (someCondition)
        return false;

    n.sendData();
    return true;
}
```
In this example, if `someCondition` is true, the function will return early without calling `n.sendData()`. Here the user explicitely wrote code to send data, but due to the logic of the program, it may not be called. This can lead to data loss and other issues, in a more subdle way.

To generalize, some classes that handle resources (memory, file handles, network connections, etc.) require some kind of cleanup to be performed before the object is destroyed, automatically. **Cleanup** is often referred to all the necessary steps to release resources held by an object before it is destroyed.

#### Destructors to the rescue:
In a previous lesson on classes, we covered constructors, which are special member functions that are called when an object is created. Constructors are used to initialize the object and allocate any necessary resources.

Similarly, classes can have a special member function called a **destructor**, which is called automatically when an object of a non-aggregate class type is destroyed (goes out of scope or is deleted). The destructor is used to perform any necessary cleanup before the object is destroyed, such as releasing resources held by the object.

#### Destructor naming:
Like constrcutors, destructors have specific naming conventions:
- The destructor has the same name as the class, but is prefixed with a tilde (`~`).
- The destructor cannot take any arguments.
- The destructor does not return a value (not even `void`).

Each class can only have one single destructor, and generally you should never call the destructor explicitly. The destructor is called automatically when the object goes out of scope or is deleted.

Destructors can safely call other member functions since the object is still valid when the destructor is called.

#### A destructor example:
Here is a simple example of a class with a destructor:
```cpp
#include <iostream>

class Simple
{
private:
    int m_id {};

public:
    Simple(int id)
        : m_id { id }
    {
        std::cout << "Constructing Simple " << m_id << '\n';
    }

    ~Simple() // here's our destructor
    {
        std::cout << "Destructing Simple " << m_id << '\n';
    }

    int getID() const { return m_id; }
};

int main()
{
    // Allocate a Simple
    Simple simple1{ 1 };
    {
        Simple simple2{ 2 };
    } // simple2 dies here

    return 0;
} // simple1 dies here
```
When we run this program, we get the following output:
```
Constructing Simple 1
Constructing Simple 2
Destructing Simple 2
Destructing Simple 1
```
This output shows that the constructor is called when each `Simple` object is created, and the destructor is called when each object goes out of scope (first `simple2`, then `simple1`, since it goes out of scope last at the end of `main()`).

> **Remember:** Static variables (including global variables and static local variables) are coonstructed at program startup and destructed at program termination.

#### Improving the NetworkData program with a destructor:
We can improve the `NetworkData` class from earlier by adding a destructor that automatically sends any unsent data when the object is destroyed, removing the need for the user to explicitly call `sendData()`. Here is an updated version of the `NetworkData` class with a destructor:
```cpp
class NetworkData
{
private:
    std::string m_serverName{};
    DataStore m_dataQueue{};

public:
	NetworkData(std::string_view serverName)
		: m_serverName { serverName }
	{
	}

	~NetworkData()
	{
		sendData(); // make sure all data is sent before object is destroyed
	}

	void addData(std::string_view data)
	{
		m_dataQueue.add(data);
	}

	void sendData()
	{
		// connect to server
		// send all data
		// clear data
	}
};

int main()
{
    NetworkData n("someipAddress");

    n.addData("somedata1");
    n.addData("somedata2");

    return 0;
}
```
In this updated version of the `NetworkData` class, we added a destructor that calls the `sendData()` member function. This ensures that any unsent data is automatically sent when the `NetworkData` object is destroyed, even if the user forgets to call `sendData()` explicitly. In this way, every object of this class type will always perform the necessary cleanup when it goes out of scope.

#### A warning about the `std::exit()` function:

In a previous chapter, we discussed the `std::exit()` function, which terminates the program immediately. One important thing to note is that when terminating a program immediately simply end the program. Local variables are not detryed first, and because of this, destructors for local objects are not called. This means that any cleanup that would normally be performed by destructors will not happen if `std::exit()` is called.

> **Warning:** Avoid using `std::exit()` in programs that rely on destructors for cleanup, as it can lead to resource leaks and other issues.

#### Summary:
- Destructors are special member functions that are called automatically when an object is destroyed.
- Destructors are used to perform cleanup tasks, such as releasing resources held by the object.
- Destructors have specific naming conventions and cannot take arguments or return values.


---

### S05 — 15.5 Class templates with member functions
In a previous chapter we had a look at function templates:
```cpp
template <typename T> // this is the template parameter declaration
T max(T x, T y) // this is the function template definition for max<T>
{
    return (x < y) ? y : x;
}
```
Function templates allow us to create functions that can work with different types without needing to write separate functions for each type.

Also, we had a look at class templates as well in a later chapter:
```cpp
#include <iostream>

template <typename T>
struct Pair
{
    T first{};
    T second{};
};

// Here's a deduction guide for our Pair (required in C++17 or older)
// Pair objects initialized with arguments of type T and T should deduce to Pair<T>
template <typename T>
Pair(T, T) -> Pair<T>;

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
Class templates allow us to create classes that can work with different types without needing to write separate classes for each type as well.

In this lesson, we’ll combine elements of both function templates and class templates as we take a closer look at class templates that have member functions.

#### Type template parameters in member functions:
Type template parameters defined as part of a class template parameter declaration can be used both as the type of data members and as the type of member function parameters. In the following example, we rewrite the `Pair` class template converting it from a struct to a class:
```cpp
#include <ios>       // for std::boolalpha
#include <iostream>

template <typename T>
class Pair
{
private:
    T m_first{};
    T m_second{};

public:
    // When we define a member function inside the class definition,
    // the template parameter declaration belonging to the class applies
    Pair(const T& first, const T& second)
        : m_first{ first }
        , m_second{ second }
    {
    }

    bool isEqual(const Pair<T>& pair);
};

// When we define a member function outside the class definition,
// we need to resupply a template parameter declaration
template <typename T>
bool Pair<T>::isEqual(const Pair<T>& pair)
{
    return m_first == pair.m_first && m_second == pair.m_second;
}

int main()
{
    Pair p1{ 5, 6 }; // uses CTAD to infer type Pair<int>
    std::cout << std::boolalpha << "isEqual(5, 6): " << p1.isEqual( Pair{5, 6} ) << '\n';
    std::cout << std::boolalpha << "isEqual(5, 7): " << p1.isEqual( Pair{5, 7} ) << '\n';

    return 0;
}
```
This program defines a `Pair` class template that holds two values of the same type. The class has a constructor to initialize the values and a member function `isEqual` to check if two `Pair` objects are equal. As you can see, the type template parameter `T` is used both for the data members and for the member function parameter, while defining the member function outside the class definition requires resupplying the template parameter declaration.

Some things to notice in this example:
1. because our class has private members, it is not an aggregate type anymore, so we can’t use aggregate initialization. Therefore, we defined a constructor to initialize the members.
2. Since `T` might be expensive to copy, we pass the constructor parameters and the `isEqual` parameter by `const` reference.
3. When we define the member function inside the class definition, we can use the template parameter `T` directly without needing to resupply the template parameter declaration.
4. When defining the `isEqual` member function outside the class definition, we need to specify the template parameter declaration (`template <typename T>`) and use the syntax `Pair<T>::isEqual` to indicate that this is a member function of the `Pair` class template instantiated with type `T`.

#### Injected class names:
In a prior lesson, we noted that the name of a constructor must match the name of the class exactly. However, in our class template for `Pair<T>`, we named our constructor `Pair`, without the `<T>` part. This is because of a special rule in C++ called **injected class names**. Injected class names allow us to refer to the current instantiation of a class template using just the class name without the template parameters. For example, inside the `Pair<T>` class template, we can refer to the current instantiation as `Pair` instead of `Pair<T>`. This is particularly useful for constructors, as it allows us to define the constructor without needing to include the template parameters.

To summarize, in this example, `Pair` is the injected class name of `Pair<T>` and within the scope of `Pair<T>` class template, we can use `Pair` to refer to the current instantiation of the class template. This means that we could also rewrite this:
```cpp
template <typename T>
bool Pair<T>::isEqual(const Pair<T>& pair)
{
    return m_first == pair.m_first && m_second == pair.m_second;
}
```
into this:
```cpp
template <typename T>
bool Pair<T>::isEqual(const Pair& pair) // note the parameter has type Pair, not Pair<T>
{
    return m_first == pair.m_first && m_second == pair.m_second;
}
```
since `Pair` is the injected class name for `Pair<T>`, and we are inside the scope of the `Pair<T>` class template.

#### Where to define member functions for class templates outside the class:
With member functions for class templates, the compiler needs to see both the class definition (to ensure that the member function template is declared as part of the class) and the template member function definition (to know how to instantiate the template). Therefore, we typically want to define both a class and its member function templates in the same location.

When a member function is defined *inside* the class definition, the compiler can see both the class definition and the member function definition at the same time. This is why defining member functions inside the class definition is common for class templates.

When a member function is defined *outside* the class definition, we need to ensure that both the class definition and the member function definition are visible to the compiler when it needs to instantiate the template. So, it is generally defined immediately below the class definition. In the typical case where the class template and its member function templates are defined in a header file, this means defining the member functions immediately below the class definition in the same header file.

> **Best Practice:** Any member function templates defined outside the class definition should be defined just below the class definition (in the same file).

#### Summary:
- Class templates can have member functions that use the class template's type parameters.
- Member functions defined inside the class definition can use the template parameters directly.
- Member functions defined outside the class definition need to resupply the template parameter declaration.
- Injected class names allow referring to the current instantiation of a class template without specifying the template parameters.


---

### S06 — 15.6 Static member variables
In previous chapters, we introduced global variables and static local variables. Both of them have static duration, meaning that they are allocated when the program starts and deallocated when the program ends. Such variables keep their values even if they go out of scope. For example:
```cpp
#include <iostream>

int generateID()
{
    static int s_id{ 0 }; // static local variable
    return ++s_id;
}

int main()
{
    std::cout << generateID() << '\n';
    std::cout << generateID() << '\n';
    std::cout << generateID() << '\n';

    return 0;
}
```
prints:
```
1
2
3
```
You can not that the static local variable `s_id` retains its value between calls to the `generateID` function.

Regarding class types, we will see two more uses for the `static` keyword:
1. Static member variables
2. Static member functions

We will talk about static member variables in this lesson, and static member functions in the next lesson.

#### Static member variables:
Before going direclty into static member variables, let’s first consider this example:
```cpp
#include <iostream>

struct Something
{
    int value{ 1 };
};

int main()
{
    Something first{};
    Something second{};

    first.value = 2;

    std::cout << first.value << '\n';
    std::cout << second.value << '\n';

    return 0;
}
```
When we instantate two objects of type `Something`, each object has its own copy of the member variable `value`. Therefore, when we modify `first.value`, it does not affect `second.value`. The output of this program is:
```
2
1
```

Member variables of a class can be made static by using the `static` keyword. A static member variable is **shared** among all instances of the same class, meaning that there is only one copy of the static member variable for the entire class, regardless of how many objects of that class are created. Here is an example:
```cpp
#include <iostream>

struct Something
{
    static int s_value; // declare s_value as static (initializer moved below)
};

int Something::s_value{ 1 }; // define and initialize s_value to 1 (we'll discuss this section below)

int main()
{
    Something first{};
    Something second{};

    first.s_value = 2;

    std::cout << first.s_value << '\n';
    std::cout << second.s_value << '\n';
    return 0;
}
```
When we run this program, we get the following output:
```
2
2
```
When the member variable `s_value` is declared as `static`, there is only one copy of `s_value` shared among all instances of the `Something` class (both `first` and `second`). Therefore, when we modify `first.s_value`, it also affects `second.s_value`, since they both refer to the same static member variable.

#### Static members are not associated with class objects:
Although you can access static member variables through class objects (e.g., `first.s_value`), static member variables are not associated with any particular object of the class. Instead, they are associated with the class itself (like a `namespace` variable). This makes sense, since static variables are created when the program starts and destroyed when the program ends, regardless of how many objects of the class are created or destroyed.

Essentially, static member variables are global variables that live inside the scope of the class, making little difference between this and a normal global variable inside a namespace.

Because of these reasons, a static member variable can be accessed directly using the class name and the scope resolution operator (`::`), without needing to create an object of the class. For example:
```cpp
class Something
{
public:
    static int s_value; // declare s_value as static
};

int Something::s_value{ 1 }; // define and initialize s_value to 1 (we'll discuss this section below)

int main()
{
    // note: we're not instantiating any objects of type Something

    Something::s_value = 2;
    std::cout << Something::s_value << '\n';
    return 0;
}
```
This allows us to access and modify the static member variable `s_value` without needing to create any objects of type `Something`.

> **Best Practice:** Access static member variables using the class name and the scope resolution operator (`::`) rather than through class objects, to make it clear that the variable is static and not associated with any particular object.

#### Defining and initializing static member variables:
When you declare a static member variable inside a class definition, you are only declaring it, not defining it. This means that you need to define the static member variable outside the class definition (in the global scope) to allocate storage for it. This is different from non-static member variables, which are defined as part of the class definition. For example, in the example above, we defined the static member variable `s_value` outside the class definition like this:
```cpp
int Something::s_value{ 1 }; // define and initialize s_value to 1
```
This line defines the static member variable `s_value` and initializes it to `1`. The syntax `Something::s_value` indicates that we are defining the static member variable `s_value` that belongs to the `Something` class.

#### Initialization of static member vatiables inside the class definition:
There are few ways to initialize static member variables inside the class definition itself:
1. When the static member is a constant integral type (e.g., `const int`, `const char`, etc.) or a const enum, you can provide an initializer inside the class definition. For example:
   ```cpp
    class Whatever
    {
    public:
        static const int s_value{ 4 }; // a static const int can be defined and initialized directly
    };
   ```
2. Since C++17, you can also initialize static member variables of `inline` variables directly inside the class definition (variables that are allowed to have multiple definitions across translation units). For example:
   ```cpp
    class Whatever
    {
    public:
        static inline int s_value{ 4 }; // an inline static int can be defined and initialized directly
    };
   ```
3. Because `constexpr` are implicitly `inline`, you can also initialize `static constexpr` member variables directly inside the class definition. For example:
   ```cpp
    #include <string_view>
    class Whatever
    {
    public:
        static constexpr double s_value{ 2.2 }; // ok
        static constexpr std::string_view s_view{ "Hello" }; // this even works for classes that support constexpr initialization
    };
   ```

> **Best Practice:** Make your static members `inline` or `constexpr` whenever possible to avoid the need for separate definitions outside the class.

#### An example of static member variables:
Why use static variables inside classes? One use is to assign a unique ID to every instance of the class. Here’s an example:
```cpp
#include <iostream>

class Something
{
private:
    static inline int s_idGenerator { 1 };
    int m_id {};

public:
    // grab the next value from the id generator
    Something() : m_id { s_idGenerator++ }
    {
    }

    int getID() const { return m_id; }
};

int main()
{
    Something first{};
    Something second{};
    Something third{};

    std::cout << first.getID() << '\n';
    std::cout << second.getID() << '\n';
    std::cout << third.getID() << '\n';
    return 0;
}
```
This program defines a `Something` class that assigns a unique ID to each instance using a static member variable `s_idGenerator`. The static variable is shared among all instances of the class, so each time a new `Something` object is created, it gets a unique ID from the static ID generator. The output of this program is:
```
1
2
3
```

This is particularly useful when you need to keep track of how many instances of a class have been created or when you need to assign unique identifiers to each instance. Or also when you have lookup tables that are shared among all instances of a class, in this way you can store only one copy of the lookup table instead of one copy per instance.

#### Only static members may use type deduction (`auto` and CTDA - Class Template Argument Deduction):
A static member variable may use `auto` to deduce its type from its initializer, or Class Type Argument Deduction (CTAD) when it is a class template. Non-static member variables may not use `auto` or CTAD. For example:
```cpp
#include <utility> // for std::pair<T, U>

class Foo
{
private:
    auto m_x { 5 };           // auto not allowed for non-static members
    std::pair m_v { 1, 2.3 }; // CTAD not allowed for non-static members

    static inline auto s_x { 5 };           // auto allowed for static members
    static inline std::pair s_v { 1, 2.3 }; // CTAD allowed for static members

public:
    Foo() {};
};

int main()
{
    Foo foo{};

    return 0;
}
```
In this example, the non-static member variables `m_x` and `m_v` cannot use `auto` or CTAD, while the static member variables `s_x` and `s_v` can use them without any issues. This is because static member variables are not associated with any particular object of the class, so their types can be deduced independently of any instance. For non-static member variables, using `auto` could cause ambiguity since their types could depend on the context of the object they belong to.

#### Summary:
- Static member variables are shared among all instances of a class.
- Static member variables are associated with the class itself, not with any particular object.
- Static member variables must be defined outside the class definition unless they are `const` integral types, `inline`, or `constexpr`.
- Static member variables can use `auto` and CTAD, while non-static member variables cannot.


---

### S07 — 15.7 Static member functions
In the previous lesson, we discussed static member variables, which are shared among all instances of a class. If a static member variable is public, it can be accessed using the class name and the scope resolution operator (`::`), without needing to create an object of the class:
```cpp
#include <iostream>

class Something
{
public:
    static inline int s_value { 1 };
};

int main()
{
    std::cout << Something::s_value; // s_value is public, we can access it directly
}
```

But what if it is private? COnsider this example:
```cpp
#include <iostream>

class Something
{
private: // now private
    static inline int s_value { 1 };
};

int main()
{
    std::cout << Something::s_value; // error: s_value is private and can't be accessed directly outside the class
}
```
This results in a compilation error because `s_value` is private and cannot be accessed directly outside the class.

Noemally, we access private member variables through public member functions. While we could create a normal public member function to access the private static member variable, this would require creating an object of the class first.
```cpp
#include <iostream>

class Something
{
private:
    static inline int s_value { 1 };

public:
    int getValue() { return s_value; }
};

int main()
{
    Something s{};
    std::cout << s.getValue(); // works, but requires us to instantiate an object to call getValue()
}
```
This works, but it requires us to create an object of type `Something` just to access the static member variable `s_value`, which is not ideal since `s_value` is not associated with any particular object. 
We can do better by defining a **static member function**.

#### Static member functions:
A **static member function** is a member function of a class that is declared with the `static` keyword. Like static member variables, static member functions are associated with the class itself rather than with any particular object of the class:
```cpp
#include <iostream>

class Something
{
private:
    static inline int s_value { 1 };

public:
    static int getValue() { return s_value; } // static member function
};

int main()
{
    std::cout << Something::getValue() << '\n';
}
```
In this example, we defined a static member function `getValue()` that returns the value of the private static member variable `s_value`. Since `getValue()` is a static member function, we can call it directly using the class name and the scope resolution operator (`::`), without needing to create an object of the class. This is better!

#### Static m,ember functions have no `this` pointer:
It is important to note two main things:
1. Because static member functions are not associated with any particular object of the class, they do not have access to the `this` pointer.
2. Static member functions can access other static members (both variables and functions) of the class, but they cannot access non-static members directly, since non-static members are associated with specific objects of the class.

#### Static members defined outside the class definition:
Like non-static member functions, static member functions can be defined outside the class definition. For example:
```cpp
#include <iostream>

class IDGenerator
{
private:
    static inline int s_nextID { 1 };

public:
    static int getNextID(); // Here's the declaration for a static function
};

// Here's the definition of the static function outside of the class.  Note we don't use the static keyword here.
int IDGenerator::getNextID() { return s_nextID++; } // You can access static members directly without scope resolution

int main()
{
    for (int count{ 0 }; count < 5; ++count)
        std::cout << "The next ID is: " << IDGenerator::getNextID() << '\n';

    return 0;
}
```
This will print:
```
The next ID is: 1
The next ID is: 2
The next ID is: 3
The next ID is: 4
The next ID is: 5
```
Note that when defining the static member function outside the class definition, we do not use the `static` keyword again. The `static` keyword is only used in the declaration inside the class definition.

As noted in a previous lesson, member functions defined inside the class definition are implicitly `inline`, so defining static member functions inside the class definition is common practice. Member functions defined outside are instead not implicitly `inline`, so if you want them to be `inline`, you need to explicitly mark them as such.

#### A word of warning about classes with static members:
Be careful when writing classes with all static members (also called *monostatess). They could be useful in some cases, but they come with potential pitfalls:
- There is no way to have multiple objects of the class with different states, since all members are static and shared among all instances (without cloning the class and renaming it).
- Similar to global variables, any piece of code that can access the class (usually the class has global or public scope) can modify the static members, which can lead to unintended side effects and make debugging difficult.

Instead, consider writing a normal class with non-static members, and then create a global instance of it if you need a single shared instance.

#### Pure static classes vs namespaces:
Pure static classes have a lot in common with namespaces. Both can be used to group related functions and variables together, and both can be accessed without needing to create an object. However, one significant difference is that classes have access controls while namespaces do not, meaning that you can control the visibility of members in a class (public, private, protected), while all members of a namespace are accessible to any code that has access to the namespace.

In general, if you need access control, use a class with static members. If you don't need access control and just want to group related functions and variables together, a namespace is often a better choice.

#### C++ does not support static constructors:
While some modern languages (e.g., C#) support static constructors (special constructors that are called to initialize static members of a class), C++ does not have this feature. In C++, static member variables can be initialized directly in their declaration (if they are `const` integral types, `inline`, or `constexpr`), or they can be initialized in a separate definition outside the class definition. Here is an example:
```cpp
#include <iostream>

struct Chars
{
    char first{};
    char second{};
    char third{};
    char fourth{};
    char fifth{};
};

struct MyClass
{
	static inline Chars s_mychars { 'a', 'e', 'i', 'o', 'u' }; // initialize static variable at point of definition
};

int main()
{
    std::cout << MyClass::s_mychars.third; // print i

    return 0;
}
```
In this example, we initialize the static member variable `s_mychars` directly in its declaration using the `inline` keyword. This is the recommended way to initialize static member variables in C++.

However, if the initialization of a static member variable requires more complex logic (e.g., calling functions, performing calculations, etc.), you can use a static member function to perform the initialization. Here is an example:
```cpp
#include <iostream>

struct Chars
{
    char first{};
    char second{};
    char third{};
    char fourth{};
    char fifth{};
};

class MyClass
{
private:
    static Chars generate()
    {
        Chars c{}; // create an object
        c.first = 'a'; // fill it with values however you like
        c.second = 'e';
        c.third = 'i';
        c.fourth = 'o';
        c.fifth = 'u';

        return c; // return the object
    }

public:
	static inline Chars s_mychars { generate() }; // copy the returned object into s_mychars
};

int main()
{
    std::cout << MyClass::s_mychars.third; // print i

    return 0;
}
```
In this example, we define a static member function `generate()` that creates and initializes a `Chars` object. We then use this function to initialize the static member variable `s_mychars`. This approach allows us to perform more complex initialization logic for static member variables.

#### Summary:
- Static member functions are associated with the class itself, not with any particular object.
- Static member functions do not have access to the `this` pointer.
- Static member functions can access static members of the class, but not non-static members directly.
- Static member functions can be defined outside the class definition without using the `static` keyword again.
- Pure static classes have access control, while namespaces do not.


---

### S08 — 15.8 Friend non-member functions
In the last chapters we focused largely on access control: private memebrs can only be accessed by member functions of the same class (or friends), while public members can be accessed by any code that has access to the class. In a previous lesson we have also seen the benefits of keeping your data memebers private and providing public member functions to access and modify them (getters and setters).

For example, consider a storage class that is focused on managing some set of data. Now lets say you also want to display that data, but the code that handles the display will have lots of options and is therefore complex. You could put both the storage and display code in the same class, but this would violate the Single Responsibility Principle (SRP), which states that a class should have only one reason to change. Instead, it would be better to separate the storage and display functionality into two different classes: a storage class and a display class.
However, this display class would need access to the private data members of the storage class in order to display the data. One way to achieve this is by using **friend non-member functions**.

#### Friendship is magic:
Inside the body of a class, a **friend declaration** (using the `friend` keyword) allows you to specify that a non-member (or memeber) function (or another class) has full access to the private and protected members of the class. This is called **friendship**. In this way, a class can selectively give other functions or classes access to its private members without making those members public.

For example, if our storage class made the display class a friend, then the display class would be able to access the private members of the storage class directly, without needing to go through public member functions.

Now, let's take a look at some examples. In this lesson we will focus on **friend non-member functions**, while in the next lesson we will focus on **friend classes** and **friend member functions**.

#### Friend non-member functions:
A **friend function** is a function (member or non-member) that is given access to the private and protected members of a class through a friend declaration (as if it were a member function of the class). Here is an example of a friend non-member function:
```cpp
#include <iostream>

class Accumulator
{
private:
    int m_value { 0 };

public:
    void add(int value) { m_value += value; }

    // Here is the friend declaration that makes non-member function void print(const Accumulator& accumulator) a friend of Accumulator
    friend void print(const Accumulator& accumulator);
};

void print(const Accumulator& accumulator)
{
    // Because print() is a friend of Accumulator
    // it can access the private members of Accumulator
    std::cout << accumulator.m_value;
}

int main()
{
    Accumulator acc{};
    acc.add(5); // add 5 to the accumulator

    print(acc); // call the print() non-member function

    return 0;
}
```
In this example, we defined a class `Accumulator` that has a private member variable `m_value` and a public member function `add()` to add a value to the accumulator. We also defined a non-member function `print()` that prints the value of the accumulator. By declaring `print()` as a friend of the `Accumulator` class, we allow it to access the private member variable `m_value` directly.

To declare a non-member function as a friend of a class, we simply declare it inside the class body using the `friend` keyword, followed by the function signature. This allows the friend function to access the private and protected members of the class as if it were a member function.

Note that, since `print()` is a non-member function, it is defined outside the class body, and it does not have access to the `this` pointer. So, inside it we will have to use an object of type `Accumulator` (passed as a parameter) to access its members.

#### Defining a friend non-member inside a class:
A friend non-member function can also be defined inside the class body itself. Here is an example:
```cpp
#include <iostream>

class Accumulator
{
private:
    int m_value { 0 };

public:
    void add(int value) { m_value += value; }

    // Friend functions defined inside a class are non-member functions
    friend void print(const Accumulator& accumulator)
    {
        // Because print() is a friend of Accumulator
        // it can access the private members of Accumulator
        std::cout << accumulator.m_value;
    }
};

int main()
{
    Accumulator acc{};
    acc.add(5); // add 5 to the accumulator

    print(acc); // call the print() non-member function

    return 0;
}
```
In this example, we defined the friend non-member function `print()` directly inside the class body. This is perfectly valid, and the function still has access to the private members of the `Accumulator` class.

Note that since `print()` is defined as a `friend`, it is not a member function of the class, even though it is defined inside the class body. Therefore, it does not have access to the `this` pointer and must use an object of type `Accumulator` (passed as a parameter) to access its members.

#### Syntactically preferring a friend non-member function:
At the beginning of this lesson, we said that there were some cases when we might prefer to use non-member function over a member function. Here is an example:
```cpp
#include <iostream>

class Value
{
private:
    int m_value{};

public:
    explicit Value(int v): m_value { v }  { }

    bool isEqualToMember(const Value& v) const;
    friend bool isEqualToNonmember(const Value& v1, const Value& v2);
};

bool Value::isEqualToMember(const Value& v) const
{
    return m_value == v.m_value;
}

bool isEqualToNonmember(const Value& v1, const Value& v2)
{
    return v1.m_value == v2.m_value;
}

int main()
{
    Value v1 { 5 };
    Value v2 { 6 };

    std::cout << v1.isEqualToMember(v2) << '\n';
    std::cout << isEqualToNonmember(v1, v2) << '\n';

    return 0;
}
```
In this example, we defined a class `Value` that has a private member variable `m_value` and two functions to compare two `Value` objects for equality:
- a member function `isEqualToMember()`
- a friend non-member function `isEqualToNonmember()`

Both functions achieve the same result, but the friend non-member function `isEqualToNonmember()` has a more symmetric syntax when comparing two `Value` objects. This is because both objects are passed as parameters to the function, making it clear that the function is comparing two values.

#### Multiple friends:
A function can be friend of multiple classes. Here is an example:
```cpp
#include <iostream>

class Humidity; // forward declaration of Humidity because Temperature needs it

class Temperature
{
private:
    int m_temp { 0 };
public:
    explicit Temperature(int temp) : m_temp { temp } { }

    friend void printWeather(const Temperature& temperature, const Humidity& humidity); // forward declaration needed for this line
};

class Humidity
{
private:
    int m_humidity { 0 };
public:
    explicit Humidity(int humidity) : m_humidity { humidity } {  }

    friend void printWeather(const Temperature& temperature, const Humidity& humidity);
};

void printWeather(const Temperature& temperature, const Humidity& humidity)
{
    std::cout << "The temperature is " << temperature.m_temp <<
       " and the humidity is " << humidity.m_humidity << '\n';
}

int main()
{
    Humidity hum { 10 };
    Temperature temp { 12 };

    printWeather(temp, hum);

    return 0;
}
```
In this example, we defined two classes, `Temperature` and `Humidity`, each with a private member variable. We also defined a friend non-member function `printWeather()` that is a friend of both classes, allowing it to access the private members of both classes.

In this example, we should note three main things:
1. Since `printWeather()` uses both `Temperature` and `Humidity`, it does not make sense to have it be a member of either class. Therefore, we defined it as a non-member function.
2. Because `printWeather()` is a friend of both classes, it can access the private members of both classes directly (`temperature.m_temp` and `humidity.m_humidity`).
3. Note the line at the top of the example (`class Humidity;`). This is a forward declaration of the `Humidity` class, which is necessary because the `Temperature` class needs to declare `printWeather()` as a friend before the `Humidity` class is fully defined. Without this forward declaration, the compiler would not know about the `Humidity` class when it encounters the friend declaration in the `Temperature` class.

#### Doesn’t friendship violate the principle of data hiding?
No, friendship is granted **explicitly** by the class that owns the private members. Therefore, it is a conscious decision made by the class designer to allow certain functions or classes to access its private members. This is different from making members public, which allows any code that has access to the class to access those members.

Note that since friends have direct access to the implementation of the class, changes to the implementation of the class may require changes to the friend functions or classes as well. Therefore, friendship should be used judiciously and only when necessary.

So, in general, when using a friend function, prefer using the public interface over direct access to the private members, unless there is a compelling reason to do otherwise.

> **Best Practice:** A friend function should prefer using the public interface of the class over direct access to private members, unless there is a compelling reason to do otherwise.

#### Prefer non-friend function to friend functions:
In general, prefer non-friend non-member functions over friend functions whenever possible. This is because friend functions break encapsulation by accessing private members directly, which can make the code harder to maintain and understand. Non-friend functions, on the other hand, can only access the public interface of the class, which helps to maintain encapsulation and makes the code easier to reason about.

For example, here if the implementation of `Accumulator` is changed (e.g., we rename `m_value`), the friend function `print()` would also need to be updated:
```cpp
#include <iostream>

class Accumulator
{
private:
    int m_value { 0 }; // if we rename this

public:
    void add(int value) { m_value += value; } // we need to modify this

    friend void print(const Accumulator& accumulator);
};

void print(const Accumulator& accumulator)
{
    std::cout << accumulator.m_value; // and we need to modify this, that is outside the class
}

int main()
{
    Accumulator acc{};
    acc.add(5); // add 5 to the accumulator

    print(acc); // call the print() non-member function

    return 0;
}
```
A better idea would be:
```cpp
#include <iostream>

class Accumulator
{
private:
    int m_value { 0 };

public:
    void add(int value) { m_value += value; }
    int value() const { return m_value; } // added this reasonable access function
};

void print(const Accumulator& accumulator) // no longer a friend of Accumulator
{
    std::cout << accumulator.value(); // use access function instead of direct access
}

int main()
{
    Accumulator acc{};
    acc.add(5); // add 5 to the accumulator

    print(acc); // call the print() non-member function

    return 0;
}
```
In this way, if the implementation of `Accumulator` changes, we only need to update the class itself, and the `print()` function can remain unchanged.

> **Best Practice:** Prefer to implement a function as non-friend when possible and reasonable.

#### Summary:
- A friend non-member function is a non-member function that is granted access to the private and protected members of a class through a friend declaration.
- Friend non-member functions can access private members directly, but they do not have access to the `this` pointer.
- Friend non-member functions can be defined inside or outside the class body.
- Prefer non-friend non-member functions over friend functions whenever possible to maintain encapsulation.


---

### S09 — 15.9 Friend classes and friend member functions
#### Friend classes:
A **friend class** is a class that can access the private and protected members of another class. This is done by declaring the friend class inside the body of the class that is granting friendship, using the `friend` keyword followed by `class FriendClassName;`. Here is an example:
```cpp
#include <iostream>

class Storage
{
private:
    int m_nValue {};
    double m_dValue {};
public:
    Storage(int nValue, double dValue)
       : m_nValue { nValue }, m_dValue { dValue }
    { }

    // Make the Display class a friend of Storage
    // Acts as a forward declaration for Display
    friend class Display;
};

class Display
{
private:
    bool m_displayIntFirst {};

public:
    Display(bool displayIntFirst)
         : m_displayIntFirst { displayIntFirst }
    {
    }

    // Because Display is a friend of Storage, Display members can access the private members of Storage
    void displayStorage(const Storage& storage)
    {
        if (m_displayIntFirst)
            std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
        else // display double first
            std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
    }

    void setDisplayIntFirst(bool b)
    {
         m_displayIntFirst = b;
    }
};

int main()
{
    Storage storage { 5, 6.7 };
    Display display { false };

    display.displayStorage(storage);

    display.setDisplayIntFirst(true);
    display.displayStorage(storage);

    return 0;
}
```
In this example, because the `Display` class is declared as a friend of the `Storage` class, the member functions of `Display` can access the private members of `Storage` directly.
The output of this program is:
```
6.7 5
5 6.7
```

Few additional notes on friend classes:
- Friendship is not reciprocal: just because `Display` is a friend of `Storage`, it does not mean that `Storage` is a friend of `Display`. Therefore, `Storage` cannot access the private members of `Display` unless `Display` also declares `Storage` as a friend.
- Eeven though `Display` is a friend of `Storage`, `Display` has no access to the `*this` pointer of `Storage` objects. Therefore, `Display` member functions must use an object of type `Storage` (passed as a parameter) to access its members.
- Friendship is not transitive: if class A is a friend of class B, and class B is a friend of class C, class A does not automatically become a friend of class C.
- Friendship is not inherited: if class A is a friend of class B, and class B is a base class of class C, class A does not automatically become a friend of class C.
- A friend class declaration acts as a forward declaration for the friend class, so you do not need to provide a separate forward declaration (as we had to do with friend non-member functions).

#### Friend member functions:
Instead of making an entire class a friend, you can also make specific member functions of another class friends. This is done by declaring the member function as a friend inside the body of the class that is granting friendship. Note that in order to make a single member function a friend, the compiler has to have seen the full definition of the class of the friend member function (not just a forward declaration). So, for example, doing so it won't work:
```cpp
class Display; // forward declaration for class Display

class Storage
{
private:
	int m_nValue {};
	double m_dValue {};
public:
	Storage(int nValue, double dValue)
		: m_nValue { nValue }, m_dValue { dValue }
	{
	}

	// Make the Display::displayStorage member function a friend of the Storage class
	friend void Display::displayStorage(const Storage& storage); // error: Storage hasn't seen the full definition of class Display
};
```
To make a member function a friend, you need to define the friend class before the class that is granting friendship. Here is an example:
```cpp
#include <iostream>

class Display
{
private:
	bool m_displayIntFirst {};

public:
	Display(bool displayIntFirst)
		: m_displayIntFirst { displayIntFirst }
	{
	}

	void displayStorage(const Storage& storage) // compile error: compiler doesn't know what a Storage is
	{
		if (m_displayIntFirst)
			std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
		else // display double first
			std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
	}
};

class Storage
{
private:
	int m_nValue {};
	double m_dValue {};
public:
	Storage(int nValue, double dValue)
		: m_nValue { nValue }, m_dValue { dValue }
	{
	}

	// Make the Display::displayStorage member function a friend of the Storage class
	friend void Display::displayStorage(const Storage& storage); // okay now
};

int main()
{
    Storage storage { 5, 6.7 };
    Display display { false };
    display.displayStorage(storage);

    return 0;
}
```
In this example, we defined the `Display` class before the `Storage` class, allowing us to declare the `Display::displayStorage()` member function as a friend of the `Storage` class. This allows the `displayStorage()` function to access the private members of `Storage` directly.

However, we have another problem now: inside the `Display::displayStorage()` member function, the compiler does not know what a `Storage` is, since `Storage` is defined after `Display`. To fix this, we can:
1. First, we can add a forward declaration of the `Storage` class before the `Display` class (`class Storage;`).
2. Then, we can move the definition of the `Display::displayStorage()` member function outside the `Display` class body, so that the compiler has seen the full definition of the `Storage` class by the time it encounters the function definition.

Here is the corrected example:
```cpp
#include <iostream>

class Storage; // forward declaration for class Storage

class Display
{
private:
	bool m_displayIntFirst {};

public:
	Display(bool displayIntFirst)
		: m_displayIntFirst { displayIntFirst }
	{
	}

	void displayStorage(const Storage& storage); // forward declaration for Storage needed for reference here
};

class Storage // full definition of Storage class
{
private:
	int m_nValue {};
	double m_dValue {};
public:
	Storage(int nValue, double dValue)
		: m_nValue { nValue }, m_dValue { dValue }
	{
	}

	// Make the Display::displayStorage member function a friend of the Storage class
	// Requires seeing the full definition of class Display (as displayStorage is a member)
	friend void Display::displayStorage(const Storage& storage);
};

// Now we can define Display::displayStorage
// Requires seeing the full definition of class Storage (as we access Storage members)
void Display::displayStorage(const Storage& storage)
{
	if (m_displayIntFirst)
		std::cout << storage.m_nValue << ' ' << storage.m_dValue << '\n';
	else // display double first
		std::cout << storage.m_dValue << ' ' << storage.m_nValue << '\n';
}

int main()
{
    Storage storage { 5, 6.7 };
    Display display { false };
    display.displayStorage(storage);

    return 0;
}
```
Now, the program works as expected, and the `Display::displayStorage()` member function can access the private members of the `Storage` class directly.

#### Summary:
- A friend class is a class that is granted access to the private and protected members of another class.
- A friend member function is a member function of another class that is granted access to the private and protected members of a class.
- Friendship is not reciprocal, transitive, or inherited.
- A friend class declaration acts as a forward declaration for the friend class.
- To declare a member function as a friend, the full definition of the friend class must be known to the compiler (not just a forward declaration).


---

### S10 — 15.10 Ref qualifiers
In a chapter on member functions, we discussed how calling access functions that return references to data members can be dangerous when the implicit object is an rvalue. Here is a quick recap of the problem:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
	std::string m_name{};

public:
	Employee(std::string_view name): m_name { name } {}
	const std::string& getName() const { return m_name; } //  getter returns by const reference
};

// createEmployee() returns an Employee by value (which means the returned value is an rvalue)
Employee createEmployee(std::string_view name)
{
	Employee e { name };
	return e;
}

int main()
{
	// Case 1: okay: use returned reference to member of rvalue class object in same expression
	std::cout << createEmployee("Frank").getName() << '\n';

	// Case 2: bad: save returned reference to member of rvalue class object for use later
	const std::string& ref { createEmployee("Garbo").getName() }; // reference becomes dangling when return value of createEmployee() is destroyed
	std::cout << ref << '\n'; // undefined behavior

	return 0;
}
```
In this example, the `getName()` member function returns a `const` reference to the private member variable `m_name`. In Case 1, we use the returned reference immediately, which is safe. However, in Case 2, we store the returned reference in a variable, which becomes dangling when the temporary `Employee` object returned by `createEmployee()` is destroyed at the end of the full expression. This leads to undefined behavior when we try to use the dangling reference later.

This second case present somewhat a conondrum:
- If our `getName()` function returns by value, this is safe but potentially inefficient, especially for large objects.
- If our `getName()` function returns by reference, this is efficient but can lead to dangling references when called on rvalues.

Since member functions are typically called on lvalue implicit objects, the conventional approach is to return by const reference. However, to handle the case when the implicit object is an rvalue, we can use **ref qualifiers**.

#### Ref qualifiers:
The root of the problem is that we want different behavior depending on whether the implicit object is an lvalue or an rvalue. What is optimal for one case is not optimal for the other. To solve this, C++ provides **ref qualifiers**, which allow us to overload member functions based on whether it is being called on an lvalue or an rvalue implicit object. Using this feature, we are able to create two versions of the `getName()` function: one for lvalue implicit objects that returns by const reference, and another for rvalue implicit objects that returns by value. 

First, let's start with our non-ref-qualified version of `getName()`:
```cpp
const std::string& getName() const { return m_name; } // callable with both lvalue and rvalue implicit objects
```
This version can be called with both lvalue and rvalue implicit objects. However, as we have seen, this can lead to dangling references when called on rvalues.

In order to ref-qualify this member function, we can add either an `&` or `&&` after the `const` qualifier:
- Adding `&` makes the member function callable **only** when the implicit object is an lvalue.
- Adding `&&` makes the member function callable **only** when the implicit object is an rvalue.

Using this knowledge, we can define two versions of `getName()`:
```cpp
const std::string& getName() const &  { return m_name; } //  & qualifier overloads function to match only lvalue implicit objects, returns by reference
std::string        getName() const && { return m_name; } // && qualifier overloads function to match only rvalue implicit objects, returns by value
```
In this example:
- The first version of `getName()` is ref-qualified with `&`, making it callable only when the implicit object is an lvalue. It returns a `const` reference to `m_name`, which is efficient and safe in this case.
- The second version of `getName()` is ref-qualified with `&&`, making it callable only when the implicit object is an rvalue. It returns `m_name` by value, which is safe in this case since the temporary object will be destroyed at the end of the full expression.

Here is the complete example using ref qualifiers:
```cpp
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
	std::string m_name{};

public:
	Employee(std::string_view name): m_name { name } {}

	const std::string& getName() const &  { return m_name; } //  & qualifier overloads function to match only lvalue implicit objects
	std::string        getName() const && { return m_name; } // && qualifier overloads function to match only rvalue implicit objects
};

// createEmployee() returns an Employee by value (which means the returned value is an rvalue)
Employee createEmployee(std::string_view name)
{
	Employee e { name };
	return e;
}

int main()
{
	Employee joe { "Joe" };
	std::cout << joe.getName() << '\n'; // Joe is an lvalue, so this calls std::string& getName() & (returns a reference)

	std::cout << createEmployee("Frank").getName() << '\n'; // Frank is an rvalue, so this calls std::string getName() && (makes a copy)

	return 0;
}
```
In this example, when we call `getName()` on the lvalue `joe`, it calls the ref-qualified version with `&`, returning a `const` reference. When we call `getName()` on the rvalue returned by `createEmployee("Frank")`, it calls the ref-qualified version with `&&`, returning `m_name` by value. In this way, we get both efficiency (by returning by reference for lvalues) and safety (by returning by value for rvalues).

#### Some notes about ref-qualified member functions:
Here are some additional notes about ref-qualified member functions:
- For a given function, non-ref-qualified overloads and ref-qualified overloads cannot coexist. For example, you cannot have both `const std::string& getName() const` and `const std::string& getName() const &` in the same class.
- Similar to how a const lvalue reference can bind to an rvalue, if only a const lvalue-qualified member function is available, it can be called on both lvalue and rvalue implicit objects. This means that if you only define the `const &` version of a member function, it can still be called on rvalues, but it may lead to dangling references if the function returns a reference to a member variable.
- Either qualified overloads can be explicitly deleted (using `= delete`), just like normal member functions.

#### So why don't we recommend using ref-qualifiers?
Ref-qualifiers can be a useful tool for optimizing member functions based on the value category of the implicit object. However, they also have some downsides:
- Adding rvalue overloads to every getter that returns a reference can lead to code bloat and increased complexity, especially in large classes with many member functions.
- Having an rvalue overload return by value means we have to pay for the cost of the copy (or move) even in cases we could have used a reference safely.

Moreover:
- Most C++ developers are not aware of ref-qualifiers, so using them can make your code less readable and harder to understand for others (and even for yourself in the future).
- The standard library typically does not use ref-qualifiers for its member functions.

#### Summary:
- Ref qualifiers allow you to overload member functions based on whether the implicit object is an lvalue or an rvalue.
- The `&` ref qualifier makes a member function callable only on lvalue implicit objects.
- The `&&` ref qualifier makes a member function callable only on rvalue implicit objects.
- Ref-qualified member functions can help optimize behavior based on the value category of the implicit object, but they can also increase code complexity and reduce readability.
- Consider the trade-offs before using ref-qualifiers in your code.


---

### SX - 15.x Summary and quiz
As always, have a look at the original summary, and good luck for the quizzes!

PS: solutions are inside `exercises/sx-questions` folder. Enjoy! :)


## 🧭 Summary

TODO: write summary

### 🧱 Core Concepts You Mastered:
- TODO: list concepts