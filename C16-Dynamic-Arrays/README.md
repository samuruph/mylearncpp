# Chapter 16 - Dynamic Arrays: std::vector

## 🧭 Overview

This chapter introduces **containers** and focuses on arrays, especially `std::vector`, as your first real workhorse data structure.  
You learn how arrays store elements **contiguously in memory**, how to access them efficiently with `operator[]`, and when to prefer safer tools like `at()`.  
On top of that, the chapter connects arrays with **copy vs move semantics**, shows how `std::vector` grows (length vs capacity), and how to use it both as a dynamic array *and* as a stack-like container with `push_back` / `emplace_back`.


---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch16_first
./build/ch16_first
```

---

## 🎯 Learning Outcomes

By the end of this chapter, you’ll be able to:
- ✅ Explain what a **container** is and how arrays / `std::vector` fit into that picture.
- ✅ Use `std::vector<T>` with list initialization, e.g. `std::vector<int> v{1, 2, 3};`.
- ✅ Safely access elements via `v[i]` and `v.at(i)`, and know why `operator[]` is **unchecked**.
- ✅ Use `v.size()`, `std::size(v)`, and `std::ssize(v)` and understand `size_type` (usually `std::size_t`).
- ✅ Traverse containers with classic `for` + indices and with **range-based for**: `for (const auto& x : v)`.
- ✅ Describe **copy semantics** vs **move semantics**, and why returning `std::vector` or `std::string` by value is okay (moves instead of heavy copies).
- ✅ Manage dynamic growth of vectors with `resize()`, `reserve()`, `capacity()`, `shrink_to_fit()`.
- ✅ Use `std::vector` as a **stack** with `push_back` / `emplace_back`, and know when `emplace_back(args...)` is more efficient.
- ✅ Recognize the quirks of `std::vector<bool>` and why it’s usually better to avoid it.


---

## Sections

### S01 - 16.1 Introduction to containers and arrays
#### The variable scalability challange:
Consider a scenario where you want to record the test scores of 30 students and calculate the average for the class. To do so, with the knowledge you have so far, you would create 30 variables to hold each student's score:
```cpp
// allocate 30 integer variables (each with a different name)
int testScore1 {};
int testScore2 {};
int testScore3 {};
// ...
int testScore30 {};
```
And to calculate the average, you would need to sum all these variables and divide by 30:
```cpp
int average { (testScore1 + testScore2 + testScore3 + testScore4 + testScore5
     + testScore6 + testScore7 + testScore8 + testScore9 + testScore10
     + testScore11 + testScore12 + testScore13 + testScore14 + testScore15
     + testScore16 + testScore17 + testScore18 + testScore19 + testScore20
     + testScore21 + testScore22 + testScore23 + testScore24 + testScore25
     + testScore26 + testScore27 + testScore28 + testScore29 + testScore30)
     / 30; };
```
This approach is clearly not scalable. If the number of students changes, you would have to manually adjust the number of variables and the calculation logic, which is inefficient and error-prone. Moreover, there is a lot of repetitive code that makes it hard to read and maintain.

We could put our data inside a `struct`:
```cpp
struct testScores
{
// allocate 30 integer variables (each with a different name)
int score1 {};
int score2 {};
int score3 {};
// ...
int score30 {};
}
```
But this still does not solve the scalability issue. If the number of students changes, we would still have to modify the struct definition and the associated logic.

#### Containers:
To solve this problem, we can use containers. **Containers** are data types that provide storage for a collection of unnamed objects (called **elements**). Containers can dynamically manage the memory for these elements, allowing us to easily add or remove elements as needed.

For example, you already used containers in the past lessons, such as `std::string`, which is a container for characters:
```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name{ "Alex" }; // strings are a container for characters
    std::cout << name; // output our string as a sequence of characters

    return 0;
}
```
In this example, `std::string` is a container that holds a sequence of characters.

#### The elements of a container are unnamed:
While the container object itself typically has a name (like `name` in the example above), the individual elements inside the container do not have names. This is done in order to put as many elements as needed inside the container without having to name each one individually. This is one reason why `struct` is not considered a container, since each member of a struct has its own name.

In the example before, our string container has a name (`name`), but the individual characters inside the string do not have names (`A`, `l`, `e`, `x` are just elements inside the container).

This could raise a question: if the elements inside a container do not have names, how can we access them? The answer is that containers provide mechanisms to access their elements, typically through **indices** or **iterators**. We will explore these mechanisms in more detail in the following.

#### The length of a container:
In programming, the term **length*** of a container refers to the number of elements it currently holds. Different containers have different ways to determine their length. For example, in a previous chapter, we have seen how to compute the length of a `std::string` using the `length()` member function:
```cpp
#include <iostream>
#include <string>

int main()
{
    std::string name{ "Alex" };
    std::cout << name << " has " << name.length() << " characters\n";

    return 0;
}
```
This prints:
```
Alex has 4 characters
```
In this example, the `length()` member function of the `std::string` container returns the number of characters it holds.

In C++, the term **size** is also commonly used for the number of elements in a container. This is an unfortunate choice since we have already used the term "size" to refer to the amount of memory allocated for a type or object (in bytes). For this reason, we will prefer to the term **length** when referring to the number of elements in a container, to avoid confusion with memory size.

#### Container operations:
Containers typically provide a set of operations to manage their elements. Common operations include:
- **Create**: Initialize a container to hold elements.
- **Access**: Retrieve elements in the container.
- **Insert**: Add new elements to the container.
- **Delete**: Remove elements from the container.
- **Length**: Determine the number of elements in the container.

Containers can also provide other operations, such as sorting, searching, and iterating over elements. The specific operations available depend on the type of container being used.
Every container type has its own characteristics, advantages, and disadvantages. Choosing the right container for a specific task is an important aspect of programming in C++.

#### Elements types:
In most programming languages (including C++), containers are **homogeneous**, meaning that all elements in a container must be of the same type. For example, a container that holds integers cannot also hold strings or floating-point numbers. This homogeneity ensures that operations on the elements can be performed consistently and efficiently.

Some containers uses a preset element type (e.g., `std::string` is a container for `char`), while others allow you to specify the element type when you create the container (e.g., `std::vector<int>` is a container for `int`). This makes the containers more flexible and reusable for different types of data.

#### Containers in C++:
The **Containers library** is a part of the C++ standard library that provides a variety of container types for storing and managing collections of objects. A class type that implements a container is called a **container class**.


Some of the most commonly used containers in C++ include:
- `std::vector`: A dynamic array that can grow and shrink in size. 
- `std::list`: A doubly linked list that allows for efficient insertion and deletion of elements.
- `std::deque`: A double-ended queue that allows for efficient insertion and deletion of elements at both ends.
- `std::set`: A collection of unique elements that are sorted in a specific order.
- `std::map`: A collection of key-value pairs that allows for efficient retrieval of values based on their keys.
- `std::string`: A container for characters that represents a sequence of characters.

The full list of containers available in the C++ standard library can be found in the [C++ reference](https://en.cppreference.com/w/cpp/container.html).

In C++, the definition of “container” is narrower than the general programming definition. Only the class types in the Containers library are considered to be containers in C++. We will use the term “container” when talking about containers in general, and “container class” when talking specifically about the container class types that are part of the Containers library.

#### Introduction to arrays:
An **array** is a container data type that stores a sequence of elements of the same type in a **contiguous** block of memory. Arrays allow fast, direct access to any element using its **index** (or position) in the sequence. The first element of an array is at index `0`, the second element is at index `1`, and so on.

C++ contains three types of arrays:
- **C-style arrays**: These are the traditional arrays inherited from the C programming language. They have a fixed size that must be known at compile time and cannot be changed during runtime.
- **std::vector** (since C++03): This is a dynamic array provided by the C++ Standard Library. It can grow and shrink in size as needed during runtime, making it more flexible than C-style arrays.
- **std::array** (since C++11): This is a fixed-size array provided by the C++ Standard Library. Unlike C-style arrays, `std::array` is a class template that provides additional functionality and safety features.

#### Moving forward:
In the next lesson, we will introduce our first container, `std::vector`, and explore its features and capabilities in detail.

#### Summary:
- **Containers** are data types that provide storage for a collection of unnamed objects (called **elements**).
- The **length** of a container refers to the number of elements it currently holds.
- Containers typically provide operations to create, access, insert, delete, and determine the length of their elements.
- Containers in C++ are part of the **Containers library** in the C++ standard library.
- C++ provides three types of arrays: **C-style arrays**, **std::vector**, and **std::array**.



---

### S02 - 16.2 Introduction to std::vector and list constructors
In this lessos we will introduce `std::vector`, solving one part of the scalability challenge we saw in the previous lesson.

#### Introduction to `std::vector`:
`std::vector` is one of the container classes in the C++ Standard Library that implements a dynamic array. It is implemented in the `<vector>` header file as a class template, with a template type parameter that specifies the type of elements the vector will hold. Thus, you can create vectors to hold any data type, such as `int`, `double`, `std::string`, or even user-defined types, by simply writing `std::vector<type>`.

You can instantiate a `std::vector` like this:
```cpp
#include <vector>

int main()
{
	// Value initialization (uses default constructor)
	std::vector<int> empty{}; // vector containing 0 int elements

	return 0;
}
```
In this example, we create an empty vector of integers named `empty`. Because we used value initialization (with `{}`), the vector is initialized to contain zero (no) elements.

#### Initializing a `std::vector` with a list of values:
Since the goal of a container is to hold multiple elements, we can also initialize a `std::vector` with a list of values using **list initialization**:
```cpp
#include <vector>

int main()
{
	// List construction (uses list constructor)
	std::vector<int> primes{ 2, 3, 5, 7 };          // vector containing 4 int elements with values 2, 3, 5, and 7
	std::vector vowels { 'a', 'e', 'i', 'o', 'u' }; // vector containing 5 char elements with values 'a', 'e', 'i', 'o', and 'u'.  Uses CTAD (C++17) to deduce element type char (preferred).

	return 0;
}
```
In this example, we create two vectors: `primes`, which holds four integer elements representing the first four prime numbers, and `vowels`, which holds five character elements representing the vowels in the English alphabet. Note that in the second vector, we used **Class Template Argument Deduction (CTAD)** (available since C++17) to let the compiler deduce the element type (`char` in this case) based on the provided values.

#### List constructors and initializer lists:
Now we will talk about how this works under the hood. In a previous chapter about struc aggregate initialization, we defined an initializer list as a braced list of comma-separated values (e.g., `{ 2, 3, 5, 7 }`).

Containers typically have special constructors called **list constructors** that accept an **initializer list** as an argument. The list constructor does three things:
- Ensure the container has enough storage to hold all the elements in the initializer list.
- Sets the length of the container to match the number of elements in the initializer list.
- Initializes each element in the container with the corresponding value from the initializer list.

Thus, when we provide an initializer list to a container's list constructor, the list constructor is called automatically to set up the container with the specified elements.

> **Best Practice:** When initializing a container with a list of values, prefer using **list initialization** (with `{}`) to take advantage of the container's list constructor.

#### Accesing array elements using the subscript opetrator (`operator[]`):
After we correctly initialize a `std::vector`, how can we access its elements? 

The most common way to access array elements in C++ is by using the **subscript operator** (`operator[]`), which uses an *integral value* (usually an `int` or `std::size_t`) as an **index** to specify the position of the element we want to access. The index is **zero-based**, meaning that the first element is at index `0`, the second element is at index `1`, and so on. For example:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> primes{ 2, 3, 5, 7 };

    // Accessing elements using the subscript operator
    std::cout << "First prime: " << primes[0] << '\n'; // Output: 2
    std::cout << "Second prime: " << primes[1] << '\n'; // Output: 3
    std::cout << "Third prime: " << primes[2] << '\n'; // Output: 5
    std::cout << "Fourth prime: " << primes[3] << '\n'; // Output: 7

    return 0;
}
```
This will output:
```
First prime: 2
Second prime: 3
Third prime: 5
Fourth prime: 7
```
In this example, we create a vector of integers named `primes` and use the subscript operator to access and print each of its elements.

In this way, we will no longer have to define separate variables for each element, and we can easily access any element in the vector using its index.

#### Subscript out of bounds:
One important thing to note when using the subscript operator is that it does not perform **any bounds checking**. This means that if you try to access an element at an index that is outside the valid range of the vector (i.e., less than `0` or greater than or equal to the vector's length `N`), you will get **undefined behavior**. This can lead to crashes, data corruption, or other unexpected results. In general, an `N`-length vector has valid indices from `0` to `N-1` (inclusive). So, the last valid index is always `length - 1`, not `length`.

**Note:** Since the indexes are zero-based, the last valid index of a vector is always `length - 1`, not `length`.

#### Arrays are contiguous in memory:
One of the defining characteristics of arrays (including `std::vector`) is that their elements are stored in a **contiguous block of memory**. This means that all elements are stored one after the other in memory, without any gaps in between. This property allows for efficient access to elements using their indices, as the memory address of any element can be calculated directly based on its index.
For example:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector primes { 2, 3, 5, 7, 11 }; // hold the first 5 prime numbers (as int)

    std::cout << "An int is " << sizeof(int) << " bytes\n";
    std::cout << &(primes[0]) << '\n';
    std::cout << &(primes[1]) << '\n';
    std::cout << &(primes[2]) << '\n';

    return 0;
}
```
This might output something like (on a 32-bit system):
```
An int is 4 bytes
00DBF720
00DBF724
00DBF728
```
You can see that the memory addresses of the elements are 4 bytes apart (the size of an `int`), confirming that the elements are stored contiguously in memory. Note that, sicne we are on a 32-bit system, each `int` occupies 4 bytes of memory, and so each cell of memory address increases by 4 for each subsequent element.

Arrays are one of the few container types that allow for **random access**, meaning that you can access any element directly using its index in constant time (O(1)). This is in contrast to other container types, such as linked lists, where accessing an element may require traversing the list from the beginning to the desired position (sequential access, O(n) time complexity).

#### Constructing a `std::vector` of a specific length:
Consider an example where we want the user to input 10 values that we will store in a `std::vector`. In this case, we want a vector that has a specific length (10 elements) but we don't know the values yet. 

We could attempt to initialize the vector with 10 default values like this:
```cpp
std::vector<int> data { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // vector containing 10 int values
```
However, this approach is not scalable, as we would have to manually type out 10 zeros.

Luckily for us, `std::vector` has an explicit constructor (`explicit std::vector<T>(std::size_t)`) that takes a single `std::size_t` argument representing the desired length of the vector. This constructor initializes the vector to the specified length, with each element being value-initialized (default-initialized for built-in types). For example:
```cpp
std::vector<int> data( 10 ); // vector containing 10 int elements, value-initialized to 0
```
In this way, we can create a vector of a specific length without having to manually type out each element. In this example, since we elements are of type `int`, they are value-initialized to `0`.

One non-obious thing about this constructor is that **it must be called using direct initialization** (with parentheses `()`), not list initialization (with braces `{}`). If you try to use list initialization with a single integer value, the compiler will interpret it as a list constructor call instead, resulting in a vector with a single element containing that integer value.

**Note:** Call this constructor using direct initialization (with parentheses `()`), not list initialization (with braces `{}`).

#### Non-empty initializer lists prefer list constructors:
To understand why the previous constructor must be called using direct initialization (with parentheses `()`), consider the following example:
```cpp
std::vector<int> data{ 10 }; // what does this do?
```
There are two different constructors that match this initialization:
1. The list constructor that takes an initializer list with a single element `10`, resulting in a vector containing one element with the value `10`.
2. The constructor that takes a single `std::size_t` argument representing the desired length of the vector, resulting in a vector containing ten elements, each value-initialized to `0`.

Normally when a class type definition matches more than one constructor, the match is considered ambiguous and the compiler will generate an error. However, C++ has a special rule for this case: **when an initializer list is non-empty, a matching list constructor will be selected over other constructors**. This means that in the example above, the list constructor is chosen, and `data` will be a vector containing one element with the value `10`.

Here we can have a better idea of all the cases:
```cpp
// Copy init
std::vector<int> v1 = 10;     // 10 not an initializer list, copy init won't match explicit constructor: compilation error

// Direct init
std::vector<int> v2(10);      // 10 not an initializer list, matches explicit single-argument constructor

// List init
std::vector<int> v3{ 10 };    // { 10 } interpreted as initializer list, matches list constructor

// Copy list init
std::vector<int> v4 = { 10 }; // { 10 } interpreted as initializer list, matches list constructor
std::vector<int> v5({ 10 });  // { 10 } interpreted as initializer list, matches list constructor

// Default init
std::vector<int> v6 {};       // {} is empty initializer list, matches default constructor
std::vector<int> v7 = {};     // {} is empty initializer list, matches default constructor
```
In this case:
- `v1` results in a compilation error because copy initialization cannot match the explicit constructor.
- `v2` creates a vector with 10 elements, each value-initialized to `0`, since it uses direct initialization with parentheses.
- `v3`, `v4`, and `v5` create vectors with one element containing the value `10`, since they use list initialization with a non-empty initializer list.
- `v6` and `v7` create empty vectors, since they use list initialization with an empty initializer list.

**Best Practice:** When constructing a container (or any type that has a list constructor) with initializers that are not element values, use direct initialization.

#### Const and constexpr `std::vector`:
You can declare a `std::vector` as `const`:
```cpp
#include <vector>

int main()
{
    const std::vector<int> prime { 2, 3, 5, 7, 11 }; // prime and its elements cannot be modified

    return 0;
}
```
A `const std::vector` must be initialized, and then cannot be modified afterwards. This means that each element in the vector is also `const`, and cannot be changed.
Moreover, the element type of a `std::vector` must not be definied as const (e.g., `std::vector<const int>` is not allowed).

One of the biggest downsides of `std::vector` is that it cannot be made `constexpr`, because its size can change at runtime. This means that you cannot use `std::vector` in `constexpr` contexts, such as `constexpr` functions or `constexpr` variables.
If you need a `constexpr` arrau, use `std::array` instead, which has a fixed size known at compile time.

#### Why is it called a vector?
In the book “From Mathematics to Generic Programming”, Alexander Stepanov wrote, “The name vector in STL was taken from the earlier programming languages Scheme and Common Lisp. Unfortunately, this was inconsistent with the much older meaning of the term in mathematics… this data structure should have been called array. Sadly, if you make a mistake and violate these principles, the result might stay around for a long time.”

So, the name `vector` was chosen for historical reasons, even though it would have been more appropriate to call it `array`.

#### Summary:
- `std::vector` is a dynamic array container class in the C++ Standard Library.
- You can initialize a `std::vector` using list initialization with an initializer list of values.
- You can access elements in a `std::vector` using the subscript operator (`operator[]`).
- `std::vector` elements are stored in a contiguous block of memory, allowing for efficient random access.
- You can construct a `std::vector` of a specific length using the explicit constructor that takes a `std::size_t` argument.
- When initializing a `std::vector` with a single integer value, use direct initialization (with parentheses) to avoid ambiguity with the list constructor.
- `std::vector` cannot be made `constexpr` due to its dynamic size.


---

### S03 - 16.3 `std::vector` and the unsigned length and subscript problem
In the previous lesson, we introduced `operator[]`, which can be used to subscript an array (including `std::vector`) using an integral index. In this lesson, we will look at other ways to access array elements, as well as few additional ways to get the length of an container class.

But first, we need to discuss one majopr mistake that the designers of C++ made when defining the Containers library: they defined the length of a container as an **unsigned** integer type (`std::size_t`), instead of a signed integer type (e.g., `int` or `std::ptrdiff_t`).

#### The container length isgn problem:
First ,one assertion: the data type used for subscripting arrays should match the data type used for the length of the array. This is so that all elements in the longest possible array can be indexed, and no more.

As Bjarne Stroustrup recalls, when the container classes in the C++ standard library was being designed (circa 1997), the designers had to choose whether to make the length (and array subscripts) signed or unsigned. They chose to make them **unsigned**. The reasons given for this: the subscripts of the standard library array types can’t be negative, using an unsigned type allows arrays of greater length due to the extra bit (something that was important in the 16-bit days), and range-checking the subscript requires one conditional check instead of two (since no check was needed to ensure the index was less than 0).

We now know that using unsigned values to try to enforce non-negativity is a bad idea due to the implicit conversion rules in C++ (since a negative singed integer will be implicitly converted to a large positive unsigned integer). This can lead to unexpected behavior and bugs in the code.

In a previous chapter, we have seen that mixing signed and unsigned integers in expressions can lead to unexpected results. This is especially true when comparing signed and unsigned integers, as the signed integer will be implicitly converted to an unsigned integer, which can lead to incorrect comparisons.

For now, we need to adapt to this design decision, and be careful when using signed integers (e.g., `int`) to subscript arrays or to compare with the length of a container (which is of type `std::size_t`).

#### A review: sign conversion are narrowing conversion, except when constexpr:
First of all, let's recap what we learned about signed/unsigned conversions (integral conversions from signed to unsigned types and vice versa).

Sign conversions are considered to be narrowing conversion because they can lead to loss of information (they cannot hold the same range of values). When these conversion are performed at runtime, the compiler will issue an error where narrowing conversions are disallowed (e.g., list initialization), and may or may not issue a warning in other contexts (e.g., copy initialization, direct initialization, implicit conversions in expressions).

For example:
```cpp
#include <iostream>

void foo(unsigned int)
{
}

int main()
{
    int s { 5 };

    [[maybe_unused]] unsigned int u { s }; // compile error: list initialization disallows narrowing conversion
    foo(s);                                // possible warning: copy initialization allows narrowing conversion

    return 0;
}
```
In this example, the list initialization of `u` from `s` results in a compile error because it disallows narrowing conversions. However, passing `s` to the function `foo`, which expects an `unsigned int`, may only generate a warning, as copy initialization allows narrowing conversions (for GCC and Clang, this is controlled by the `-Wsign-conversion` flag).

However, if the value to be sign-converted is a `constexpr` and can be converted to an equivalent value in the opposite type without loss of information, the conversion is allowed (not considered narrowing). For example:
```cpp
#include <iostream>

void foo(unsigned int)
{
}

int main()
{
    constexpr int s { 5 };                 // now constexpr
    [[maybe_unused]] unsigned int u { s }; // ok: s is constexpr and can be converted safely, not a narrowing conversion
    foo(s);                                // ok: s is constexpr and can be converted safely, not a narrowing conversion

    return 0;
}
```
In this case, since `s` is a `constexpr` with a value of `5`, it can be safely converted to an `unsigned int` without loss of information (since `5` is non-negative and within the range of `unsigned int`), so both the list initialization of `u` and the function call to `foo` are allowed without errors or warnings.

This non-narrowing constexpr conversion (from `constexpr int` to `constexpr std::size_t`) is important when working with array subscripts and lengths, as we will see next.

#### The length and inidices of a `std::vector` have type `size_type`:
In a previous chapter, we said that typedefs and aliases are often used in cases where we need a name for a type that may vary (because it is implementation-defined). For example, `std::size_t` is an alias for some large unsigned integral type, usually `unsigned long` or `unsigned long long`, that is used to represent sizes and lengths in the standard library.

Each of the standard library container class defines a nested typedf memebr named `size_type`, which is an alias for the type used to represent the length of the container and the indices used to subscript the container.

`size_type` is almost always an alias for `std::size_t`, but can be overridden (in rare cases) to use a different type.

When accessing the `size_type` member of a container class, we must scope it using the full template name of the container class, including its template arguments. For example `std::vector<int>::size_type` is the `size_type` for a vector of integers.

#### Getting the length of a `std::vector` using the `size` member function or `std::size()`:
We can get the length of a container class object using its `size()` member function, which returns the length of the container as a value of type `size_type`. For example:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime { 2, 3, 5, 7, 11 };
    std::cout << "length: " << prime.size() << '\n'; // returns length as type `size_type` (alias for `std::size_t`)
    return 0;
}
```
This will output:
```
length: 5
```

Unlike `std::string` and `std::string_view`, which have both `length()` and `size()` member functions doing the same thing, `std::vector` only has the `size()` member function to get its length.

In C++17, we can also use the `std::size()` non-member function to get the length of a container class object:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime { 2, 3, 5, 7, 11 };
    std::cout << "length: " << std::size(prime); // C++17, returns length as type `size_type` (alias for `std::size_t`)

    return 0;
}
```

If we want to use either of the above method to store the length in a variable with a signed type (e.g., `int`), the easiest way is to use a `static_cast` to convert the returned value to the desired type:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime { 2, 3, 5, 7, 11 };
    int length { static_cast<int>(prime.size()) }; // static_cast return value to int
    std::cout << "length: " << length ;

    return 0;
}
```

#### getting the length of a `std::vector` using the `std::ssize` function (C++20):
C++20 introduced the `std::ssize()` non-member function in the `<iterator>` header, which returns the length of a container as a large **signed** integral type (`std::ptrdiff_t`). This is useful when we want to work with signed lengths and avoid the issues associated with mixing signed and unsigned types.
For example:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };
    std::cout << "length: " << std::ssize(prime); // C++20, returns length as a large signed integral type

    return 0;
}
```

This is the only function of the three that returns a signed length directly.

If you want to use this method to store the length in a variable with a signed type, you have a couple of options.
1. Because `int` type may not be large enough to hold the length of very large returned value by `std::ssize()`, you should `static_cast` the result to `int` to make such conversion explicit:
    ```cpp
    #include <iostream>
    #include <vector>

    int main()
    {
        std::vector prime{ 2, 3, 5, 7, 11 };
        int length { static_cast<int>(std::ssize(prime)) }; // static_cast return value to int
        std::cout << "length: " << length;

        return 0;
    }
    ```
2. Alternatively, you can use `auto` to have the compiler deduce the correct signed type for you:
    ```cpp
    #include <iostream>
    #include <vector>

    int main()
    {
        std::vector prime{ 2, 3, 5, 7, 11 };
        auto length { std::ssize(prime) }; // use auto to deduce signed type, as returned by std::ssize()
        std::cout << "length: " << length;

        return 0;
    }
    ```

#### Accessing array elements using `operator[]` does no bounds checking:
As we saw in the previous lesson, using the subscript operator (`operator[]`) to access array elements does not perform any bounds checking. This means that if you try to access an element at an index that is outside the valid range of the vector (i.e., less than `0` or greater than or equal to the vector's length), you will get **undefined behavior** (it will give you whatever is at that memory location, which may lead to crashes, data corruption, or other unexpected results). For example:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::cout << prime[3];  // print the value of element with index 3 (7)
    std::cout << prime[9]; // invalid index (undefined behavior)

    return 0;
}
```
In this example, accessing `prime[9]` is out of bounds, as the valid indices for the `prime` vector are `0` to `4`. This results in undefined behavior.

> **Note:** Indices passed to `operator[]` can be non-const values.

#### Accessing array elements using the `.at()` member function does runtime bounds checking:
The array container classes in the C++ standard library provide a member function named `at()` that can be used to access array elements with **runtime bounds checking**. This means that if you try to access an element at an index that is outside the valid range of the vector, the `at()` function will throw an `std::out_of_range` exception instead of resulting in undefined behavior. For example:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::cout << prime.at(3); // print the value of element with index 3
    std::cout << prime.at(9); // invalid index (throws exception)

    return 0;
}
```
In this example, accessing `prime.at(9)` will throw an `std::out_of_range` exception, which can be caught and handled appropriately, instead of returning a garbage value or causing a crash.

As with `operator[]`, the index passed to `at()` can be a non-const value.

Because it does runtime bounds checking, using `at()` is generally slower than using `operator[]`. Therefore, you should use `at()` when safety is more important than performance, such as when dealing with user input or untrusted data.

#### Indexing `std::vector` with a constepxr signed int:
When indexing a `std::vector` using a `constexpr` signed integer (e.g., `constexpr int`), we can let the compiler implicitly convert this to a `std::size_t` (the type used for indices) because the conversion is non-narrowing (the value is known at compile time and is non-negative). For example:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::cout << prime[3] << '\n';     // okay: 3 converted from int to std::size_t, not a narrowing conversion

    constexpr int index { 3 };         // constexpr
    std::cout << prime[index] << '\n'; // okay: constexpr index implicitly converted to std::size_t, not a narrowing conversion

    return 0;
}
```

#### Indexing `std::vector` with a non-constexpr value:
The subscripts used to index an array can be non-const:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::size_t index { 3 };           // non-constexpr
    std::cout << prime[index] << '\n'; // operator[] expects an index of type std::size_t, no conversion required

    return 0;
}
```

However, following our best practices, we generally avoid using unsigned types to hold quantities.

When our subscript is a non-constexpr signed value, we run into problems:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    int index { 3 };                   // non-constexpr
    std::cout << prime[index] << '\n'; // possible warning: index implicitly converted to std::size_t, narrowing conversion

    return 0;
}
```
In this example, the non-constexpr signed integer `index` is implicitly converted to `std::size_t` when used to subscript the `prime` vector, since the subscript of `operator[]` defined in `std::vector` is of type `size_type` (an alias for `std::size_t`). This conversion is considered a narrowing conversion, which may lead to unexpected behavior if `index` were to hold a negative value.

At runtime, if `index` is negative, it will be converted to a large positive value when cast to `std::size_t`, leading to an out-of-bounds access and undefined behavior. This will then raise a warning (rememebr to set `-Wsign-conversion` flag for GCC and Clang).

Because array subscripting is common, and each such conversion will generate a warning, this can easily clutter up your compilation log with spurious warnings. Or, if you have “treat warning as errors” enabled (`-Werror` flag), it can even prevent your code from compiling.

There are many possible ways to avoid this issue (e.g., `static_cast` your `int` to a `std::size_t` every time you subscript an array), but all will end up cluttering or complicating your code in some way. The simplest thing to do in this case is use a variable of type `std::size_t` to hold the index, and do not use this variable for anything but indexing arrays.
For example:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector prime{ 2, 3, 5, 7, 11 };

    std::size_t index { 3 };           // use std::size_t for array index
    std::cout << prime[index] << '\n'; // no conversion required

    return 0;
}
```

#### Summary:
- The length of a container class in C++ is represented using an unsigned integer type (`std::size_t`).
- Mixing signed and unsigned integers can lead to unexpected behavior due to implicit conversions.
- The `size_type` member of a container class is an alias for the type used to represent the length and indices of the container.
- You can get the length of a `std::vector` using the `size()` member function or the `std::size()` non-member function.
- C++20 introduced the `std::ssize()` non-member function, which returns the length of a container as a signed integer type (`std::ptrdiff_t`).
- The subscript operator (`operator[]`) does not perform bounds checking, while the `at()` member function does runtime bounds checking and throws an exception if the index is out of range.
- When indexing a `std::vector` with a `constexpr` signed integer, the compiler can implicitly convert it to `std::size_t` without issues.
- When indexing a `std::vector` with a non-`constexpr` signed integer, it is recommended to use a variable of type `std::size_t` to avoid implicit narrowing conversions and potential warnings.


---

### S04 - 16.4 Passing `std::vector`
As for `std::string`, we prefer passing `std::vector` objects by `const` reference to avoid unnecessary (expensive) copies. Doing so, we should always specify the template argument(s) explicitly, as CTAD (Class Template Argument Deduction) does not apply to function parameters.
```cpp
#include <iostream>
#include <vector>

void passByRef(const std::vector<int>& arr) // we must explicitly specify <int> here
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes);

    return 0;
}
```
In this example, we define a function `passByRef` that takes a `const` reference to a `std::vector<int>`. Inside the function, we can access the elements of the vector without making a copy of it. In the `main` function, we create a vector of integers named `primes` and pass it to the `passByRef` function.

#### Passing `std::vector` of different element types:
Because our function `passByRef` is defined to take a `std::vector<int>`, we can only pass vectors of integers to it. If we try to pass a vector of a different type (e.g., `std::vector<double>`), we will get a compilation error:
```cpp
#include <iostream>
#include <vector>

void passByRef(const std::vector<int>& arr)
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes);  // ok: this is a std::vector<int>

    std::vector dbl{ 1.1, 2.2, 3.3 };
    passByRef(dbl); // compile error: std::vector<double> is not convertible to std::vector<int>

    return 0;
}
```
In this example, passing the `dbl` vector (of type `std::vector<double>`) to the `passByRef` function results in a compilation error, as it is not convertible to `std::vector<int>`.

In C++17 or newer, you might try to use CTAD (Class Template Argument Deduction) to deduce the type of the vector parameter automatically:
```cpp
#include <iostream>
#include <vector>

void passByRef(const std::vector& arr) // compile error: CTAD can't be used to infer function parameters
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 }; // okay: use CTAD to infer std::vector<int>
    passByRef(primes);

    return 0;
}
```
However, this will also result in a compilation error, as CTAD cannot be used to infer function parameters.

To fix this, we could make use of function templates to create a function that can accept vectors of any element type:
```cpp
#include <iostream>
#include <vector>

template <typename T>
void passByRef(const std::vector<T>& arr)
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes); // ok: compiler will instantiate passByRef(const std::vector<int>&)

    std::vector dbl{ 1.1, 2.2, 3.3 };
    passByRef(dbl);    // ok: compiler will instantiate passByRef(const std::vector<double>&)

    return 0;
}
```
In this way, the `passByRef` function is defined as a function template that can accept a `std::vector` of any element type `T`. The compiler will instantiate the appropriate version of the function based on the type of the vector passed to it.

So, we just created a single function template that can handle vectors of different element types, without having to define separate functions for each type.

#### Passing `std::vector` using a generic template or abbreviated function template:
We can also create a function template that accepts any type of container (not just `std::vector`), by using a generic template parameter:
```cpp
#include <iostream>
#include <vector>

template <typename T>
void passByRef(const T& arr) // will accept any type of object that has an overloaded operator[]
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes); // ok: compiler will instantiate passByRef(const std::vector<int>&)

    std::vector dbl{ 1.1, 2.2, 3.3 };
    passByRef(dbl);    // ok: compiler will instantiate passByRef(const std::vector<double>&)

    return 0;
}
```
In this example, the `passByRef` function template accepts any type `T`, allowing it to work with any object that has an overloaded `operator[]`, such as `std::vector`, `std::array`, or even user-defined container types.

In C++20, we can use an abbreviated function template (via an `auto` parameter) to achieve the same effect:
```cpp
#include <iostream>
#include <vector>

void passByRef(const auto& arr) // abbreviated function template
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::vector primes{ 2, 3, 5, 7, 11 };
    passByRef(primes); // ok: compiler will instantiate passByRef(const std::vector<int>&)

    std::vector dbl{ 1.1, 2.2, 3.3 };
    passByRef(dbl);    // ok: compiler will instantiate passByRef(const std::vector<double>&)

    return 0;
}
```
In this way, the `passByRef` function is defined using an `auto` parameter, allowing it to accept any type of object, similar to the previous example, but without explicitly defining a template parameter.

The potential downside of using generic templates or abbreviated function templates is that they may accept types that do not behave like arrays (i.e., do not have an overloaded `operator[]`), which could lead to compilation errors when trying to access elements.

#### Asserting on array length:
Consider the following example (similar to the previous one):
```cpp
#include <iostream>
#include <vector>

template <typename T>
void printElement3(const std::vector<T>& arr)
{
    std::cout << arr[3] << '\n';
}

int main()
{
    std::vector arr{ 9, 7, 5, 3, 1 };
    printElement3(arr);

    return 0;
}
```
In this case, the `printElement3` function template attempts to print the element at index `3` of the passed vector. However, if we were to call this function with a vector that has fewer than 4 elements, it would result in undefined behavior due to out-of-bounds access. For example:
```cpp
#include <iostream>
#include <vector>

template <typename T>
void printElement3(const std::vector<T>& arr)
{
    std::cout << arr[3] << '\n';
}

int main()
{
    std::vector arr{ 9, 7 }; // a 2-element array (valid indexes 0 and 1)
    printElement3(arr);

    return 0;
}
```
Now, calling `printElement3` with a vector containing only 2 elements will lead to undefined behavior when trying to access `arr[3]`.

One option to solve this, would be to assert on `arr.size()`, which will catch the error when run in a debug build configuration. Because `std::vector::size()` is a non-const function, we can only do it at runtime.

The best option is to avoid writing functions that rely on the user passing in a vector with a minimum length in the first place.

> **Best Practice:** Avoid writing functions that rely on the user passing in a vector with a minimum length.

#### Summary:
- Prefer passing `std::vector` objects by `const` reference to avoid unnecessary copies.
- When defining functions that accept `std::vector`, always specify the template argument(s) explicitly.
- Use function templates to create functions that can accept `std::vector` of different element types.
- You can also use generic templates or abbreviated function templates to create functions that accept any type of container.
- Be cautious when writing functions that rely on the user passing in a vector with a minimum length, as this can lead to undefined behavior if the vector is too short.


---

### S05 - 16.5 Returning `std::vector`, and an introduction to move semantics
In the last lessos, we said that we prefer passing `std::vector` objects by `const` reference to avoid unnecessary copies. However, when returning a `std::vector` from a function, we usually return it **by value**. 

If you are surprised by this, don't worry, I was as well...

#### Copy semantics:
Consider the following example:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector arr1 { 1, 2, 3, 4, 5 }; // copies { 1, 2, 3, 4, 5 } into arr1
    std::vector arr2 { arr1 };          // copies arr1 into arr2

    arr1[0] = 6; // We can continue to use arr1
    arr2[0] = 7; // and we can continue to use arr2

    std::cout << arr1[0] << arr2[0] << '\n';

    return 0;
}
```
When `arr2` is initialized with `arr1`, the copy constructor of `std::vector` is called, which copies the contents of `arr1` into `arr2`. This means that `arr1` and `arr2` are two separate vectors, each with their own copy of the data. Making a copy is the only viable option in this case, as both `arr1` and `arr2` need to remain valid and usable after the copy, and moreover independent of each other.

The term **copy semmantics** referes to the rules that determine how copies of objects are made. When we say a type supports copy semantics, we mean that objects of that type are copyable, because the rules for making such copies have been defined. When we say copy semantics are being invoked, that means we’ve done something that will make a copy of an object.

For class type, copy semantics are typically implemented using a copy constructor and a copy assignment operator. The copy constructor is used to create a new object as a copy of an existing object, while the copy assignment operator is used to assign the value of one existing object to another existing object.

#### When copy semantics is not optimal:
Now consider this example:
```cpp
#include <iostream>
#include <vector>

std::vector<int> generate() // return by value
{
    // We're intentionally using a named object here so mandatory copy elision doesn't apply
    std::vector arr1 { 1, 2, 3, 4, 5 }; // copies { 1, 2, 3, 4, 5 } into arr1
    return arr1;
}

int main()
{
    std::vector arr2 { generate() }; // the return value of generate() dies at the end of the expression

    // There is no way to use the return value of generate() here
    arr2[0] = 7; // we only have access to arr2

    std::cout << arr2[0] << '\n';

    return 0;
}
```
In this example, the `generate` function creates a local `std::vector<int>` named `arr1` and returns it by value. When the function returns, a copy of `arr1` is made to create the return value of the function. This copy is then used to initialize `arr2` in the `main` function.
However, since `arr1` is a local object that goes out of scope when the function returns, there is no way to use `arr1` after the function has returned. The only way to access the data is through the return value, which is a copy of `arr1`.

In this case, making a copy of `arr1` is not optimal, as we are creating a temporary object that is only used to initialize `arr2`, and then immediately discarded. This can lead to unnecessary overhead, especially if the vector is large.

#### Introduction to move semantics:
Instead, what if there was a way to transfer the contents of `arr1` to the return value, without making a copy? This is where **move semantics** comes into play. When ownership of data is transferred from one object to another, we say that data has been **moved**. Its cost is typically trivially small, as it usually involves just copying a few pointers and size values, rather than copying all the data.

This is the essence of move semantics: it allows us to transfer ownership of resources from one object to another, without the overhead of making a copy. When moved semantics is invoked, any data member that can be moved is moved, and any data member that cannot be moved is copied.

#### How move semantics is invoked:
Normally, when an object is being initialized with (or assigned) an object of the same type, copy semantics will be used (assuming the copy isn’t elided).

However, when all of the following conditions are met, move semantics will be invoked instead:
- The type of the object supports move semantics (i.e., it has a move constructor and/or move assignment operator defined).
- The object is being initialized with (or assigned) an rvalue (temporary) of the same type.
- The move is not elided (i.e., the compiler is not able to optimize away the move).

But, *not that many types support move semantics*. In fact, most built-in types (e.g., `int`, `double`, etc.) do not support move semantics, as they are trivially copyable. However, many standard library types (e.g., `std::vector`, `std::string`, etc.) do support move semantics, as they manage resources that can be transferred.

We will dig into how move semantics works in more detail in chapter 22. For now, just remember that when returning a `std::vector` from a function, move semantics will be invoked (assuming the conditions above are met), allowing us to transfer ownership of the vector's data to the caller without making a copy.

#### We can return move-capable types like `std::vector` by value efficiently:
Because return by value returns an rvalue, if the returned type supports move semantics, the move constructor will be invoked instead of the copy constructor (assuming the move is not elided). This allows us to return `std::vector` objects by value efficiently, without the overhead of making a copy.

#### Expensive-to-copy types, if they are move-capable, can be returned by value?
Yes! Types that are expensive to copy, but support move semantics (like `std::vector`), can be returned by value efficiently. This is because the move constructor will be invoked instead of the copy constructor, allowing us to transfer ownership of the resources without the overhead of making a copy.

One of the most common things we do in C++ is pass a value to some function, and get a different value back. When the passed values are class types, that process involves 4 steps:
1. Construct the value to be passed (if it is not already constructed).
2. Actually pass the value to the function.
3. Construct the value to be returned inside the function.
4. Return the value to the caller.

Here is an example using `std::vector`:
```cpp
#include <iostream>
#include <vector>

std::vector<int> doSomething(std::vector<int> v2)
{
    std::vector v3 { v2[0] + v2[0] }; // 3 -- construct value to be returned to caller
    return v3; // 4 -- actually return value
}

int main()
{
    std::vector v1 { 5 }; // 1 -- construct value to be passed to function
    std::cout << doSomething(v1)[0] << '\n'; // 2 -- actually pass value

    std::cout << v1[0] << '\n';

    return 0;
}
```
First, let's assume that `std::vector` is not move-capable (i.e., it only supports copy semantics). In this case, the following would happen:
1. Constructing the value to be passed copies the initializer list into `v1`.
2. Actually passing the value to the function copies argument `v1` into function parameter `v2`.
3. Constructing the value to be returned copies the initializer into `v3`.
4. Actually returning the value to the caller copies `v3` into the return value.

This results in a total of 4 copies, which can be expensive if the vectors are large.

Now, let's see how we could optimize the code above: pass by reference or address, elision (copy elision or return value optimization), move semantics, and out parameters.

We cannot optimize copies 1 and 3, since we need a `std::vector` to pass to the function, and we need a `std::vector` to return from the function. `std::vector` is an owner of its data, so we need to create a new `std::vector` in both cases.
What we can optimize is copies 2 and 4.

Copy 2 is made because we are passing `v1` by value to the function. Let's analyze which options we have to avoid this copy:
- Pass by refrence or address: we are guaranteed that the arguemnt will exist for the entire duration of the function call, so the caller does not ahve to worry about the lifetime of the argument.
- Elision: not possible, since elision only works when we are making a redundant copy or move, and in this case, we are not.
- Out parameter: not possible, since we are passing a value to the function, not returning a value from the function.
- Move semantics: not possible, since `v1` is an lvalue, and move semantics only works with rvalues. If we moved data from `v1` to `v2`, `v1` would become an empty vector, which is not what we want.

Clearly, pass by const reference is the best option to avoid copy 2, as it avoid the copy, avoids null pointer issues, and works with both lvalues and rvalues.

Copy 4 is made because we are returning `v3` by value from the function. Let's analyze which options we have to avoid this copy:
- Return by reference or address: not possible, since `v3` is a local variable, and returning a reference or address to a local variable would result in undefined behavior, sine the local variable would go out of scope when the function returns.
- Elision: possible, since the return value is a temporary that is being used to initialize `doSomething(v1)[0]` in the caller. The compiler can optimize away the copy by constructing the return value directly in the memory location of the caller's temporary.
- Out parameter: possible. Instead of constructing `v3` as a local variable, we could construct an empty `std::vector` object in the scope of the caller, and pass it to the function by non-const reference. The function would then fill in the contents of the vector, and the caller would have access to the filled-in vector after the function returns.
- Move semantics: possible, since `v3` is a local variable that is being returned by value. The return value is an rvalue, so the move constructor of `std::vector` will be invoked instead of the copy constructor, allowing us to transfer ownership of the resources without the overhead of making a copy.

Elision is the best option in this case, but wheteher it happens is up to the compiler. Move semantics is the next best option, as it allows us to transfer ownership of the resources without the overhead of making a copy (for move-capable types).

> **Best Practice:**For move-capable types, prefer to pass by const reference and return by value (to take advantage of move semantics).

#### Summary:
- When returning a `std::vector` from a function, we usually return it by value.
- Move semantics allows us to transfer ownership of resources from one object to another without the overhead of making a copy.
- Move semantics is invoked when an object is being initialized with (or assigned) an rvalue of the same type, and the type supports move semantics.
- Types that are expensive to copy, but support move semantics (like `std::vector`), can be returned by value efficiently.
- To optimize the number of copies when passing and returning `std::vector`, prefer to pass by const reference and return by value.


---

### S06 - 16.6 Arrays and loops
In the introduction of this chapter, we showed the scalability challenges that arise when using multiple individual variables to represent a collection of related data. We then introduced arrays as a solution to this problem, allowing us to group related data together in a single object that can be easily managed and manipulated. In this lesson, we will discuss more in depth how arrays and loops work together to process collections of data efficiently.

#### The variable scalability challange, revisited:
Consider the case where we want to find the average test score for a class of students. To keep these examples concise, we’ll assume the class has only 5 students.

Here is how we could implement this using individual variables:
```cpp
#include <iostream>

int main()
{
    // allocate 5 integer variables (each with a different name)
    int testScore1{ 84 };
    int testScore2{ 92 };
    int testScore3{ 76 };
    int testScore4{ 81 };
    int testScore5{ 56 };

    int average { (testScore1 + testScore2 + testScore3 + testScore4 + testScore5) / 5 };

    std::cout << "The class average is: " << average << '\n';

    return 0;
}
```
In this example, we have 5 individual variables to store the test scores of each student. This approach works fine for a small number of students, but it quickly becomes unmanageable as the number of students increases. If we had 100 students, we would need to declare 100 individual variables, which would be tedious and error-prone. Additionally, calculating the average would require us to manually sum all the individual variables, which is not scalable.

By now, you know that we should be using an array when we have a collection of related data. Here is how we could implement the same functionality using an array:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector testScore { 84, 92, 76, 81, 56 };
    std::size_t length { testScore.size() };

    int average { (testScore[0] + testScore[1] + testScore[2] + testScore[3] + testScore[4])
        / static_cast<int>(length) };

    std::cout << "The class average is: " << average << '\n';

    return 0;
}
```
This is way better, since we only need to declare a single array to store all the test scores. However, we still have a scalability problem when calculating the average, as we still need to manually sum each element of the array. If we had 100 students, we would need to write out 100 terms in the sum, which is still not scalable.

What we really need is a way to process each element of the array in a loop, allowing us to perform the same operation on each element without having to write out each term manually.

#### Arrays and loops:
In previous lessons, we noted that arrays subscripts do not need to be constant expressions, meaning that can be runtime exprtessions. This allows us to use a value of a variable as an index to access different elements of the array in a loop (e.g., `data[i]`).

For example, we can use a `for` loop to iterate over each element of the `testScore` array and calculate the sum of all the test scores:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector testScore { 84, 92, 76, 81, 56 };
    std::size_t length { testScore.size() };

    int average { 0 };
    for (std::size_t index{ 0 }; index < length; ++index) // index from 0 to length-1
        average += testScore[index];                      // add the value of element with index `index`
    average /= static_cast<int>(length);                  // calculate the average

    std::cout << "The class average is: " << average << '\n';

    return 0;
}
```
In this example, we use a `for` loop to iterate over each index of the `testScore` array. The loop variable `index` starts at `0` and increments by `1` until it reaches `length - 1`. Inside the loop, we access each element of the array using the current value of `index` and add it to the `average` variable. After the loop, we divide the total sum by the number of elements to calculate the average.

This solution is ideal in terms of maintainability and scalability. If we need to change the number of students, we only need to update the initialization of the `testScore` array, and the loop will automatically adjust to process all elements of the array.

Accessing each element of a container in some order is called **traversal**, or **traversing** the container. In this case, we are traversing the `testScore` array from the first element (index `0`) to the last element (index `length - 1`). Traversal is also often called **iteration**, or **iterating over** or **iterating through** the container.

#### Templates, arrays, and loops unlock scalability:
- **Arrays** provide a way to store multiple objects without having to name each element.
- **Loops** provide a way to traverse/iterate over each element of an array without having to write out each operation manually.
- **Templates** provide a way to parametrize the element type.

Together, templates, arrays, and loops allow us to write code that can operate on a container of elements, regardless of the element type or number of elements in the container!

To show this fact more clearly:
```cpp
#include <iostream>
#include <vector>

// Function template to calculate the average of the values in a std::vector
template <typename T>
T calculateAverage(const std::vector<T>& arr)
{
    std::size_t length { arr.size() };

    T average { 0 };                                      // if our array has elements of type T, our average should have type T too
    for (std::size_t index{ 0 }; index < length; ++index) // iterate through all the elements
        average += arr[index];                            // sum up all the elements
    average /= static_cast<int>(length);                  // divide by count of items (integral in nature)

    return average;
}

int main()
{
    std::vector class1 { 84, 92, 76, 81, 56 };
    std::cout << "The class 1 average is: " << calculateAverage(class1) << '\n'; // calc average of 5 ints

    std::vector class2 { 93.2, 88.6, 64.2, 81.0 };
    std::cout << "The class 2 average is: " << calculateAverage(class2) << '\n'; // calc average of 4 doubles

    return 0;
}
```
This prints:
```
The class 1 average is: 77
The class 2 average is: 81.75
```
In this example, we define a function template `calculateAverage` that takes a `std::vector` of any type `T` and calculates the average of its elements. The function uses a loop to traverse the array and sum up the elements, and then divides the total by the number of elements to calculate the average.
In the `main` function, we create two vectors: `class1` containing integers and `class2` containing doubles. We then call the `calculateAverage` function for each vector, demonstrating that the same function can handle different element types seamlessly.

#### What we can do with arrays and loops:
Let's have a look at the most common things we can do with arrays and loops:
- Compute a new value based on the values in the array (e.g., sum, average, min, max, etc.).
- Search for an existing element (e.g., has exact match, count occurrences, find first occurrence, etc.).
- Operate on each element (e.g., print all elements, modify all elements, etc.).
- Reorder the elements (e.g., sort, shuffle, etc.).

The first three operations are straightforward to implement using loops, by simply iterating over each element of the array and performing the desired operation. The last operation, reordering the elements, is more complex and typically requires more advanced algorithms.

#### Arrays and off-by-one errors:
When working with arrays and loops, a common mistake is to make off-by-one errors. This occurs when the loop iterates one too many or one too few times, leading to accessing elements outside the bounds of the array. For example, consider the following code that attempts to print all elements of an array:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector arr { 10, 20, 30, 40, 50 };
    std::size_t length { arr.size() };

    for (std::size_t index{ 0 }; index <= length; ++index) // off-by-one error: should be < length
        std::cout << arr[index] << '\n';                   // accessing out-of-bounds element when index == length

    return 0;
}
```
In this example, the loop condition `index <= length` causes the loop to iterate one too many times, leading to an attempt to access `arr[length]`, which is out of bounds (since arryas in C++ are zero-based). This results in undefined behavior.

**Remember:** When iterating over an array of length `n`, the valid indices are from `0` to `n-1`. Therefore, the loop condition should be `index < length` to avoid off-by-one errors.

#### Summary:
- Arrays allow us to group related data together in a single object.
- Loops enable us to traverse/iterate over each element of an array efficiently.
- Templates allow us to parametrize the element type, enabling us to write generic functions that can operate on arrays of different types.
- Together, arrays, loops, and templates provide a powerful way to process collections of data in a scalable and maintainable manner.
- Be cautious of off-by-one errors when working with arrays and loops, ensuring that loop conditions correctly reflect the valid range of indices for the array.


---

### S07 - 16.7 Arrays, loops, and sign challange solutions
In a previous chapter, we noted how we generally prefer to use signed values to hold quantities, because unsigned values can act in unexpected ways when they go below zero (e.g., wrap around to a large positive value). However, when working with arrays and loops, we often need to use unsigned values (e.g., `std::size_t`) to represent the length of the array and the indices used to access its elements. This can lead to problems as this one:
```cpp
#include <iostream>
#include <vector>

template <typename T>
void printReverse(const std::vector<T>& arr)
{
    for (std::size_t index{ arr.size() - 1 }; index >= 0; --index) // index is unsigned
    {
        std::cout << arr[index] << ' ';
    }

    std::cout << '\n';
}

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    printReverse(arr);

    return 0;
}
```
This code will print:
```
9 1 2 8 3 7 6 4 
```
followed by a large number of garbage values, and then likely crash with a segmentation fault.

The problem here is that the loop condition `index >= 0` will always be true, because `index` is of type `std::size_t`, which is an unsigned type. When `index` reaches `0` and is decremented, it wraps around to a large positive value (the maximum value representable by `std::size_t`), causing the loop to continue indefinitely and access out-of-bounds elements of the array.

To fix this, for example, we could use a signed integer type (e.g., `int` or `std::ptrdiff_t`) for the loop variable, even though it brings additional challenges:
```cpp
#include <iostream>
#include <vector>

template <typename T>
void printReverse(const std::vector<T>& arr)
{
    for (int index{ static_cast<int>(arr.size()) - 1}; index >= 0; --index) // index is signed
    {
        std::cout << arr[static_cast<std::size_t>(index)] << ' ';
    }

    std::cout << '\n';
}

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    printReverse(arr);

    return 0;
}
```
In this corrected version, we use an `int` type for the loop variable `index`, allowing it to go below zero without wrapping around. We also cast `arr.size()` to `int` to ensure that the subtraction is performed correctly. Inside the loop, we cast `index` back to `std::size_t` when accessing the array elements, ensuring that we are using the correct type for indexing.

As you can see, there is a lot of casting going on here, which is not ideal.

Here is another example of using signed indexing:
```cpp
#include <iostream>
#include <vector>

// Function template to calculate the average value in a std::vector
template <typename T>
T calculateAverage(const std::vector<T>& arr)
{
    int length{ static_cast<int>(arr.size()) };

    T average{ 0 };
    for (int index{ 0 }; index < length; ++index)
        average += arr[static_cast<std::size_t>(index)];
    average /= length;

    return average;
}

int main()
{
    std::vector testScore1 { 84, 92, 76, 81, 56 };
    std::cout << "The class 1 average is: " << calculateAverage(testScore1) << '\n';

    return 0;
}
```
The cluttering caused by casting is pretty bad, making the code harder to read and maintain.

So what we should do instead? This is one area in which there is no an ideal solution, but there are many viable options, presented from worst to best.

#### 1. Leave signed/unsigned conversion warnings off:
The worst option is to simply ignore the signed/unsigned conversion warnings generated by the compiler. This is not recommended, as it can lead to unexpected behavior and bugs in the code.

#### 2. Using an unsigned loop variable:
Many developers believe that since the standard library array types were designed to use unsigned indices, then we should use unsigned indices! This is a completely reasonable position. We just need to be extra careful that we do not run into signed/unsigned mismatches when doing so. If possible, avoid using the index loop variable for anything but indexing.

If we decide to use this approach, which unsigned type should we actually use? In. aprevious lesson, we saw that the standard library container classes defined nested typed `size_def`, which is an unsigned integral type used for array lengths and indices. For example, we could do this:
```cpp
#include <iostream>
#include <vector>

int main()
{
	std::vector arr { 1, 2, 3, 4, 5 };

	for (std::vector<int>::size_type index { 0 }; index < arr.size(); ++index)
		std::cout << arr[index] << ' ';

	return 0;
}
```
However, using `size_type` has a major downside: since it is a nested type, to use it we have to explicitly prefix the name with the fully templated name of the container type (e.g., `std::vector<int>::size_type`), which is cumbersome and makes the code harder to read.

When used inside a function template, we can use `T` for the template arguements, but we also need to prefix the type with the `typename` keyword:
```cpp
#include <iostream>
#include <vector>

template <typename T>
void printArray(const std::vector<T>& arr)
{
	// typename keyword prefix required for dependent type
	for (typename std::vector<T>::size_type index { 0 }; index < arr.size(); ++index)
		std::cout << arr[index] << ' ';
}

int main()
{
	std::vector arr { 9, 7, 5, 3, 1 };

	printArray(arr);

	return 0;
}
```
This works, but the code is even more cluttered now.

Additionally, you may occasionally see the array type aliased to make the loop easier to read:
```cpp
using arrayi = std::vector<int>;
for (arrayi::size_type index { 0 }; index < arr.size(); ++index)
```
This is better, but still not ideal.

A more general solution is to have the compiler fetch the type of the array type object for us, so that we don't have to write it out ourselves. We can do this using the **`decltype`** keyword, which returns the type of its parameter:
```cpp
// arr is some non-reference type
for (decltype(arr)::size_type index { 0 }; index < arr.size(); ++index) // decltype(arr) resolves to std::vector<int>
```

However, if `arr` is a refernce type (e.g., an array passed by reference), this is not working. We should first remove the reference from `arr`:
```cpp
template <typename T>
void printArray(const std::vector<T>& arr)
{
	// arr can be a reference or non-reference type
	for (typename std::remove_reference_t<decltype(arr)>::size_type index { 0 }; index < arr.size(); ++index)
		std::cout << arr[index] << ' ';
}
```
Unfortunately, this is no longer concise or easy to remember and read.

Because `size_type` is almost always a typedef for `size_t`, many programmers prefer to use `size_t` directly:
```cpp
for (std::size_t index { 0 }; index < arr.size(); ++index)
```
Unless you are using custom allocators, this could be a good option.

#### 3. Using a signed loop variable:
Although it makes working with the standard library container types a bit more difficult, using a signed loop variable is consistent with the best practices employed in the rest of our code (to favor signed values for quantities). And the more we can consistently apply our best practices, the fewer errors we will have overall.

If we decide to use this approach, we need to be extra careful about three issues:
- What signed type should we use?
- Getting the length of the array as a signed value.
- Converting the signed loop variable to an unsigned index when accessing the array.

#### What signed type should we use?
There are three (sometimes four) options for the signed type:
1. Unless you are working with a very larga array, you can use `int` for the signed type.
2. If you are working with a very large array, you can use `std::ptrdiff_t`. This typedef is often used as the signed counterpart to `std::size_t`.
3. Because `std::ptrdiff_t` has a weird name, another good option is to define your own type alias for indices:
    ```cpp
    using Index = std::ptrdiff_t;

    // Sample loop using index
    for (Index index{ 0 }; index < static_cast<Index>(arr.size()); ++index)
    ```
4. In cases where you can derive the type of your loop variable from the initializer, you can use `auto` to have the compiler deduce the correct signed type for you:
    ```cpp
    for (auto index{ static_cast<std::ptrdiff_t>(arr.size())-1 }; index >= 0; --index)
    ```

#### Getting the length of the array as a signed value:
1. Pre-C++20, the best option is to `static_cast` the returned value from the `size()` member function or `std::size()` non-member function to the desired signed type:
    ```cpp
    #include <iostream>
    #include <vector>

    using Index = std::ptrdiff_t;

    int main()
    {
        std::vector arr{ 9, 7, 5, 3, 1 };

        for (auto index{ static_cast<Index>(arr.size())-1 }; index >= 0; --index)
            std::cout << arr[static_cast<std::size_t>(index)] << ' ';

        return 0;
    }
    ```
    In this way, the unsigned value returned by `arr.size()` is converted to the desired signed type (so that our comparison operator can work correctly), avoiding the wrap-around problem, since signed indices will not overflow when they go negative. 
    
    The downside of this approach is that it clutters up our loop variable declaration with a lot of casting. We could improve this by moving the length out of the loop variable declaration:
    ```cpp
    #include <iostream>
    #include <vector>

    using Index = std::ptrdiff_t;

    int main()
    {
        std::vector arr{ 9, 7, 5, 3, 1 };

        auto length{ static_cast<Index>(arr.size()) };
        for (auto index{ length-1 }; index >= 0; --index)
            std::cout << arr[static_cast<std::size_t>(index)] << ' ';

        return 0;
    }
    ```
2. In C++20, we can use the `std::ssize()` non-member function to get the length of the array as a signed value directly (likely `ptrdiff_t`):
    ```cpp
    #include <iostream>
    #include <vector>

    int main()
    {
        std::vector arr{ 9, 7, 5, 3, 1 };

        for (auto index{ std::ssize(arr)-1 }; index >= 0; --index) // std::ssize introduced in C++20
            std::cout << arr[static_cast<std::size_t>(index)] << ' ';

        return 0;
    }
    ```
    This is the only function of the three that returns a signed length directly.

#### Converting the signed loop variable to an unsigned index:
Once we have a signed loop variable, we are going to run into implicit sign conversions when accessing array elements, because the subscript of `operator[]` is of type `size_type` (an alias for `std::size_t`). So we would need some way to convert our signed loop variable to an unsigned index when accessing array elements:
1. The obvious option is to `static_cast` our signed loop variable to `std::size_t` every time we access an array element. This is not so practical since wer will have to do this for every array element we access.
2. Use a conversion function with a short name:
    ```cpp
    #include <iostream>
    #include <type_traits> // for std::is_integral and std::is_enum
    #include <vector>

    using Index = std::ptrdiff_t;

    // Helper function to convert `value` into an object of type std::size_t
    // UZ is the suffix for literals of type std::size_t.
    template <typename T>
    constexpr std::size_t toUZ(T value)
    {
        // make sure T is an integral type
        static_assert(std::is_integral<T>() || std::is_enum<T>());

        return static_cast<std::size_t>(value);
    }

    int main()
    {
        std::vector arr{ 9, 7, 5, 3, 1 };

        auto length { static_cast<Index>(arr.size()) };  // in C++20, prefer std::ssize()
        for (auto index{ length-1 }; index >= 0; --index)
            std::cout << arr[toUZ(index)] << ' '; // use toUZ() to avoid sign conversion warning

        return 0;
    }
    ```
    In this way, we can avoid the sign conversion warning by using the `toUZ()` function to convert our signed loop variable to an unsigned index when accessing array elements.

    The downside of this approach is that we need to write the `toUZ()` function for every array we want to access.
    
3. Use a custom view. In a previous chapter, we have discussed about `std::string_view`, which is a lightweight, non-owning view into a sequence of characters. We can use a similar approach to create a custom view for our array. 

    In the following example, we define a custom view class that can view any standard library container that supports indexing. Our interface will do two things:
    - Allow us to access elements using `operator[]` with a signed integral type.
    - Get the length of the container as a signed integral type (since `std::ssize()` is only available in C++20).

Here is the *SignedArrayView.h* header file:
```cpp
#ifndef SIGNED_ARRAY_VIEW_H
#define SIGNED_ARRAY_VIEW_H

#include <cstddef> // for std::size_t and std::ptrdiff_t

// SignedArrayView provides a view into a container that supports indexing
// allowing us to work with these types using signed indices
template <typename T>
class SignedArrayView // requires C++17
{
private:
    T& m_array;

public:
    using Index = std::ptrdiff_t;

    SignedArrayView(T& array)
        : m_array{ array } {}

    // Overload operator[] to take a signed index
    constexpr auto& operator[](Index index) { return m_array[static_cast<typename T::size_type>(index)]; }
    constexpr const auto& operator[](Index index) const { return m_array[static_cast<typename T::size_type>(index)]; }
    constexpr auto ssize() const { return static_cast<Index>(m_array.size()); }
};

#endif
```
That can be used in the *main.cpp* file as follows:
```cpp
#include <iostream>
#include <vector>
#include "SignedArrayView.h"

int main()
{
    std::vector arr{ 9, 7, 5, 3, 1 };
    SignedArrayView sarr{ arr }; // Create a signed view of our std::vector

    for (auto index{ sarr.ssize() - 1 }; index >= 0; --index)
        std::cout << sarr[index] << ' '; // index using a signed type

    return 0;
}
```
In this way, we can avoid the sign conversion warning by using the `SignedArrayView` class to convert our signed loop variable to an unsigned index when accessing array elements. This works, but you would still have to create a new view for each array you want to access.

#### Index the underlying C-style array instead:
In a previous lesson of this chapter, we have seen that, instead of using the `operator[]` of the container class, we can index the underlying C-style array directly using the `data()` member function, and index that instead.

Since the `data()` returns the array data as a C-style array, and C-style array allows indexing with both signed and unsigned types, we can use this approach to index the array without any sign conversion warnings.
```cpp
int main()
{
    std::vector arr{ 9, 7, 5, 3, 1 };

    auto length { static_cast<Index>(arr.size()) };  // in C++20, prefer std::ssize()
    for (auto index{ length - 1 }; index >= 0; --index)
        std::cout << arr.data()[index] << ' ';       // use data() to avoid sign conversion warning

    return 0;
}
```
This is the best approach, because it is the most concise and easy to read. The main benefits are:
- We can use signed loop variable and indices without any sign conversion warnings or complex conversions.
- We do not have to define any custom types or type aliases.
- The hit to readability from using `data()` is almost negligible.
- There should be no performance hit in optimized code.

#### The only sane choice: avoid indexing altogether!
All of the options presented above have their own downsides, so it’s hard to recommend one approach over the other. However, there is a choice that is far more sane than the others: avoid indexing with integral values altogether.

C++ provides several other approaches to traverse arrays, without using indices at all, avoiding all of these signed-unsigned conversion issues. 

Two common methods for array traversal are:
1. **Range-based for loops:** iterate directly over elements without indices.  
2. **Iterators:** pointer-like objects enabling safe forward/backward traversal without numeric indices.

If you’re only using the index variable to traverse the array, then prefer a method that does not use indices.

> **Best Practice:** Avoid array indexing with integral values whenver possible.

#### Summary:
- Unsigned indices (`size_t`) can cause wrap-around bugs when decremented (e.g., reverse loops).  
- Signed indices avoid wrap-around but require many casts when indexing STL containers.  
- Using container-specific `size_type` works but is verbose and hurts readability.  
- Casting `size()` to a signed type works but clutters the code.  
- Using helper functions (`toUZ`) or custom signed array views reduces clutter but adds complexity.  
- Indexing via `arr.data()[index]` avoids sign-conversion warnings and keeps code readable.  
- The safest and cleanest approach: **avoid integral indexing altogether**.  
- Prefer **range-based for loops** when you only need the elements.  
- Prefer **iterators** when you need controlled traversal (forward/backward/custom).  


---

### S08 - 16.8 Range-based for loops (for-each)
Here another example of using a for loop to traverse an array:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

    std::size_t length { fibonacci.size() };
    for (std::size_t index { 0 }; index < length; ++index)
       std::cout << fibonacci[index] << ' ';

    std::cout << '\n';

    return 0;
}
```
Although for-loops provide a convenient and flexible way to iterate through an array, they are also easy to mess up, prone to off-by-one errors, and subject to array indexing sign problems.

Because iterating over an array is so common, C++ supports another type of for loop, called **range-based for loop** or **for-each loop**. This for loop allows traversal of a container without having to do explicit indexing or iteration control. This is generally simpler, safer, and more readable than using a for loop.

#### Range-based for loops:
The **range-based for loop** has the following syntax:
```cpp
for (element_declaration : container)
    statement;
```
Where:
- `element_declaration` is a variable declaration that will be initialized with each element of the container in turn.
- `container` is the container to be traversed.
- `statement` is the code to be executed for each element of the container.

When the loop starts, the `element_declaration` is initialized with the first element of the container, and the `statement` is executed. Then, the `element_declaration` is initialized with the second element of the container, and the `statement` is executed again, and so on, until all elements of the container have been processed. At the end, this loop will iterate over all elements of `container` and execute `statement` for each element.

For best results, `element_declaration` should have the same type as the container's elements, otherwise type conversion will occur, which can be unexpected or even dangerous.

> **Best Practice:** Use range-based for loops to iterate over containers, as they are generally simpler, safer, and more readable than using a for loop.

Here is. a simple example of using a range-based for loop to iterate over an array:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

    for (int num : fibonacci) // iterate over array fibonacci and copy each value into `num`
       std::cout << num << ' '; // print the current value of `num`

    std::cout << '\n';

    return 0;
}
```
Printing:
```
0 1 1 2 3 5 8 13 21 34 55 89 
```
In this way, no index or array's length is needed to iterate over the array.

#### Range-based for loops and empty containers:
If the container is empty, the range-based for loop will not execute at all, and the `statement` will not be executed:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector empty { };

    for (int num : empty)
       std::cout << "Hi mom!\n";

    return 0;
}
```
This code will not print anything, because the container is empty.

#### Range-based for loops and type deduction using `auto` keyword:
Because `element_declaration` should have the same type as the container's elements, we can use `auto` to let the compiler deduce the type of the elements, reducing risks of type conversion and making the code more readable:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector fibonacci { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89 };

    for (auto num : fibonacci) // compiler will deduce type of num to be `int`
       std::cout << num << ' ';

    std::cout << '\n';

    return 0;
}
```
In this way, we are sure that the type of `num` (deduced to `int` by the compiler) is the same as the type of the elements in the container (`std::vector fibonacci` has elements of type `int`), and we avoid type conversion issues.

> **Best Practice:** Use `auto` to let the compiler deduce the type of the elements in the container, reducing risks of type conversion and making the code more readable.

Another benefit of using `auto` is that if the element type of the array changes, we don't need to change the type of the `element_declaration`.

#### Avoid element copies using references:
Consider the following range-based for loop example, which iterates over an array of `std::string` objects:
```cpp
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words{ "peter", "likes", "frozen", "yogurt" };

    for (auto word : words)
        std::cout << word << ' ';

    std::cout << '\n';

    return 0;
}
```
For each iteration of the loop, the `word` variable is initialized with a copy of the current element of the `words` vector. This can be inefficient if the elements are large objects, such as `std::string` objects.
In general, we want to avoid unnecessary copies like in this case, since we are just printing the elements.

To solve this issue, we can simply make our `element_declaration` (`word`) a (const) reference to the current element of the container, which will avoid unnecessary copies:
```cpp
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words{ "peter", "likes", "frozen", "yogurt" };

    for (const auto& word : words) // word is now a const reference
        std::cout << word << ' ';

    std::cout << '\n';

    return 0;
}
```
Doing so, at each iteration, `word` will be bound to the next array element.

If the reference is made non-const, the elements of the container can be also modified (something not possible if our `element_declaration` was a copy or a const reference).

#### When to use `auto` vs `auto&` vs `const auto&`:
Normally:
- Use `auto` for cheap-to-copy types (e.g., `int`, `double`, etc)
- Use `auto&` when you want to modify the elements of the container
- Use `const auto&` for expensive-to-copy types (e.g., `std::string`, `std::vector`, etc)

In case of range-based for loops, many developers think it is preferenable to always use `const auto&` because it is more future-proof, since it will work even if the container is modified in the future.

For example:
```cpp
#include <iostream>
#include <string_view>
#include <vector>

int main()
{
    std::vector<std::string_view> words{ "peter", "likes", "frozen", "yogurt" }; // elements are type std::string_view

    for (auto word : words) // We normally pass string_view by value, so we'll use auto here
        std::cout << word << ' ';

    std::cout << '\n';

    return 0;
}
```
In this example, we have a `std::vector` containing `std::string_view` objects, and we want to print them. Since we usually pass `std::string_view` by value, `auto` here seems appropriate.

Consider now what would happen if `words` is later updated to an array of `std::string` objects:
```cpp
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> words{ "peter", "likes", "frozen", "yogurt" }; // obvious we should update this

    for (auto word : words) // Probably not obvious we should update this too
        std::cout << word << ' ';

    std::cout << '\n';

    return 0;
}
```
With this code, we are copying each `std::string` object into `word`, which is not efficient, getting a huge performance hit just changing few characters in the code.

There are a couple of reasonable ways to avoid this issue:
- Do not use type duduction at all. If we defined `element_declaration` as `std::string_view`, the compiler will implicitly convert the `std::string` objects to `std::string_view` objects, avoiding the copy.
- Use `const auto&` instead of `auto`. In this way, we avoid the copy and we can still modify the elements of the container.

> **Best Practice:** For range-based for loops, prefer to define the element type as:
> - `auto` when you want to modify copies of the elements.
> - `auto&` when you want to modify the original elements.
> - `const auto&` otherwise (e.g., when you just need to view the original elements).

#### Range-based for loops and other standard container types:
Range-based for loops work with a wide variety of array types, including (non-decayed) C-style arrays, `std::array`, `std::vector`, `std::list`, `std::set`, `std::map`, and more.

#### Getting the index of the current element:
Range-based for loops **do not** provide a way to get the index of the current element. This is because many of the data structure that work with range-based for loops do not support indices (e.g., `std::list` and `std::set`).

To get this, you can always defined a counter variable and increment it at each iteration!

#### Range-based for loops in reverse (C++20):
Prior to C++20, there was no way to iterate over a container in reverse order using a range-based for loop. 
As of C++20 instead, we can use `std::views::reverse` to reverse the order of the elements in the container:
```cpp
#include <iostream>
#include <ranges> // C++20
#include <string_view>
#include <vector>

int main()
{
    std::vector<std::string_view> words{ "Alex", "Bobby", "Chad", "Dave" }; // sorted in alphabetical order

    for (const auto& word : std::views::reverse(words)) // create a reverse view
        std::cout << word << ' ';

    std::cout << '\n';

    return 0;
}
```
This will print the elements in reverse order:
```
Dave
Chad
Bobby
Alex
```

> **Best Practice:** Use `std::views::reverse` to reverse the order of the elements in the container (C++20).

#### Summary:
- Range-based for loops are a powerful and concise way to iterate over the elements of a container:
    ```cpp
    for (element_declaration : container)
        statement;
    ```
- Use `auto` for cheap-to-copy types, `auto&` when you want to modify the elements of the container, and `const auto&` otherwise.
- Range-based for loops work with a wide variety of array types, including (non-decayed) C-style arrays, `std::array`, `std::vector`, `std::list`, `std::set`, `std::map`, and more.
- Range-based for loops **do not** provide a way to get the index of the current element.
- As of C++20, you can use `std::views::reverse` to reverse the order of the elements in the container.


---

### S09 - 16.9 Array indexing and length using enumerators
One of the biggest documentation problems with arrays is that integer do not provide any kind of information about the meaning of the value they store. For example, consider the following code:
```cpp
#include <vector>

int main()
{
    std::vector testScores { 78, 94, 66, 77, 14 };

    testScores[2] = 76; // who does this represent?
}
```
Who is the student at position `2`? We have no idea! 

#### Using unscoped enumerators for indexing:
In a previous lessons, we have seen that the index of `std::vector<T>::operator[]` (and the other standard container types) is of type `size_type`, that is generally an alias for `std::size_t`. Therefore, our indices must be of type `size_type` as well. 

Since unscoped enumerators will implicitly convert to a `size_type`, we can use them as indices for standard containers. For example:
```cpp
#include <vector>

namespace Students
{
    enum Names
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        max_students // 5
    };
}

int main()
{
    std::vector testScores { 78, 94, 66, 77, 14 };

    testScores[Students::stan] = 76; // we are now updating the test score belonging to stan

    return 0;
}
```
In this example, it is much clearer what each of the array elements represents. Because enumerators are implicitly `constexpr`, conversion of an enumerator to an unsigned integral type is not a narrowing conversion, and the code is valid.

#### Using a non-`constepxr` unscoped enumeration for indexing:
The underlying type of an unscoped enumeration is implementation defined (and thus, could be either a signed or unsigned integral type). This means that we cannot use a non-`constexpr` unscoped enumeration as an index for a standard container, because the conversion of a non-`constexpr` unscoped enumeration to an unsigned integral type is a narrowing conversion. For example:
```cpp
#include <vector>

namespace Students
{
    enum Names
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        max_students // 5
    };
}

int main()
{
    std::vector testScores { 78, 94, 66, 77, 14 };
    Students::Names name { Students::stan }; // non-constexpr

    testScores[name] = 76; // may trigger a sign conversion warning if Student::Names defaults to a signed underlying type

    return 0;
}
```
In this case, the conversion of `name` (of type `Students::Names`) to `size_type` (of type `std::size_t`) is a narrowing conversion, and the code is invalid, since name is a non-`constexpr` unscoped enumeration. 

Another option would be to explicitly specify the underlying type of the unscoped enumeration to be an unsigned int:
```cpp
#include <vector>

namespace Students
{
    enum Names : unsigned int // explicitly specifies the underlying type is unsigned int
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        max_students // 5
    };
}

int main()
{
    std::vector testScores { 78, 94, 66, 77, 14 };
    Students::Names name { Students::stan }; // non-constexpr

    testScores[name] = 76; // not a sign conversion since name is unsigned

    return 0;
}
```
In this last example, since the underlying type of `Names` is `unsigned int`, the conversion of `name` (of type `Students::Names`) to `size_type` (of type `std::size_t`) is not a narrowing conversion, and the code is valid.

#### Using count enumerator:
In the last example we have defined an extra enumerator `max_students` to represent the number of students (in the example, it will have value `5`). Informally, we will call this **count enumerator**, as its value represents the number of elements in the array. 

This count enumerator can then be used anywhere we need a count of the prior enumerators, for example:
```cpp
#include <iostream>
#include <vector>

namespace Students
{
    enum Names
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        // add future enumerators here
        max_students // 5
    };
}

int main()
{
    std::vector<int> testScores(Students::max_students); // Create a vector with 5 elements

    testScores[Students::stan] = 76; // we are now updating the test score belonging to stan

    std::cout << "The class has " << Students::max_students << " students\n";

    return 0;
}
```
Here, `Students::max_students` is used to create a vector with 5 elements, and to print the number of students in the class. 

This is nice because if we add or remove students from the `Names` enumerator, we do not need to update the code that uses `max_students`:
```cpp
#include <vector>
#include <iostream>

namespace Students
{
    enum Names
    {
        kenny, // 0
        kyle, // 1
        stan, // 2
        butters, // 3
        cartman, // 4
        wendy, // 5 (added)
        // add future enumerators here
        max_students // now 6
    };
}

int main()
{
    std::vector<int> testScores(Students::max_students); // will now allocate 6 elements

    testScores[Students::stan] = 76; // still works

    std::cout << "The class has " << Students::max_students << " students\n";

    return 0;
}
```
This will work without any issues, and the count enumerator will be updated automatically.

#### Asserting on array length with a count enumerator:
More often, we’re creating an array using an initializer list of values, with the intent of indexing that array with enumerators. In such cases, it can be useful to assert that the size of the container equals our count enumerator. If this assert triggers, it means that either our enumerators have changed, or our initializer list has changed, and we need to update the code that uses the count enumerator.

For example:
```cpp
#include <cassert>
#include <iostream>
#include <vector>

enum StudentNames
{
    kenny, // 0
    kyle, // 1
    stan, // 2
    butters, // 3
    cartman, // 4
    max_students // 5
};

int main()
{
    std::vector testScores { 78, 94, 66, 77, 14 };

    // Ensure the number of test scores is the same as the number of students
    assert(std::size(testScores) == max_students);

    return 0;
}
```
If `max_students` changes, the assert will trigger, and we will need to update the code that uses `max_students`.

> **Best Practice:** Use a `static_assert` to ensure the length of your constexpr array matches your count enumerator.

> **Best Practice:** Use an `assert` to ensure the length of your non-constexpr array matches your count enumerator.

#### Arrays and enum classes:
Because unscoped enumerations pollute the namespace they are defined in with their enumerators, it is preferable to use enum classes in cases where the enum is not already contained in another scope region (e.g. a namespace or class).

However, because enum class do not have an implicit conversion to integarl types, we run into problem when using them as array indices:
```cpp
#include <iostream>
#include <vector>

enum class StudentNames // now an enum class
{
    kenny, // 0
    kyle, // 1
    stan, // 2
    butters, // 3
    cartman, // 4
    max_students // 5
};

int main()
{
    // compile error: no conversion from StudentNames to std::size_t
    std::vector<int> testScores(StudentNames::max_students);

    // compile error: no conversion from StudentNames to std::size_t
    testScores[StudentNames::stan] = 76;

    // compile error: no conversion from StudentNames to any type that operator<< can output
    std::cout << "The class has " << StudentNames::max_students << " students\n";

    return 0;
}
```

There are a few ways to fix this. The most obvious is to `static_cast` the enum class to an integer type:
```cpp
#include <iostream>
#include <vector>

enum class StudentNames
{
    kenny, // 0
    kyle, // 1
    stan, // 2
    butters, // 3
    cartman, // 4
    max_students // 5
};

int main()
{
    std::vector<int> testScores(static_cast<int>(StudentNames::max_students));

    testScores[static_cast<int>(StudentNames::stan)] = 76;

    std::cout << "The class has " << static_cast<int>(StudentNames::max_students) << " students\n";

    return 0;
}
```

However, this is not optimal since it is painful to type and also clutters the code. 

A better option is to use the helper function we introduced in the previous chapter, which allows us to convert enumerators of enum classes to integral values using unary `operator+`:
```cpp
#include <iostream>
#include <type_traits> // for std::underlying_type_t
#include <vector>

enum class StudentNames
{
    kenny, // 0
    kyle, // 1
    stan, // 2
    butters, // 3
    cartman, // 4
    max_students // 5
};

// Overload the unary + operator to convert StudentNames to the underlying type
constexpr auto operator+(StudentNames a) noexcept
{
    return static_cast<std::underlying_type_t<StudentNames>>(a);
}

int main()
{
    std::vector<int> testScores(+StudentNames::max_students);

    testScores[+StudentNames::stan] = 76;

    std::cout << "The class has " << +StudentNames::max_students << " students\n";

    return 0;
}
```
However, if you’re going to be doing a lot of enumerator to integral conversions, it’s probably better to just use a standard enum inside a namespace (or class).

## Summary
- Raw integer indices provide no semantic meaning and make array access hard to understand.
- Unscoped enums can be safely used as array indices **when constexpr**, improving readability.
- Non-`constexpr` unscoped enums may cause narrowing/sign-conversion issues unless their underlying type is explicitly unsigned.
- A **count enumerator** (e.g. `max_students`) is useful to represent array size and keep code consistent when enums change.
- Use `assert` / `static_assert` to ensure array size matches the count enumerator.
- `enum class` avoids namespace pollution but requires explicit conversion to integral types for indexing.
- Frequent enum-to-integer conversions favor unscoped enums in a namespace over `enum class`.


---

### S10 - 16.10 `std::vector` resizing and capacity
While in the previous lessons we applied the concepts we learnt on `std::vector` specifically, we can apply the same concepts to any array type (e.g., `std::array` or C-style arrays).
In the remaining lessons in this chapter, we are going to focus on the main thing that makes `std::vector` unique compared to the other array types: its dynamic size, that is the ability to resize itself after it has been instantiated.

#### Fixed-size arrays vs dynamic arrays:
Most array types have. acommon limitation: the length of the array must be known at the point of instantiation, and cannot be changed. uch arrays are called **fixed-size arrays**. On the other hand, `std::vector` is a **dynamic array**, that is an array that can be resized after it has been instantiated.

Overall, we have two main types of arrays:
- **fixed-size arrays**: the length of the array is known at the point of instantiation and cannot be changed (e.g., C-style arrays, `std::array`)
- **dynamic arrays**: the length of the array can be changed after the array has been instantiated (e.g., `std::vector`).

#### Resizing a `std::vector` at runtime:
We can resize a `std::vector` at runtime using the `resize` member function:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector v{ 0, 1, 2 }; // create vector with 3 elements
    std::cout << "The length is: " << v.size() << '\n';

    v.resize(5);              // resize to 5 elements
    std::cout << "The length is: " << v.size() << '\n';

    for (auto i : v)
        std::cout << i << ' ';

    std::cout << '\n';

    return 0;
}
```
This prints:
```
The length is: 3
The length is: 5
0 1 2 0 0
```
To resize a `std::vector`, we can use the `resize` member function, which takes a single argument: the new size of the vector.

Some different cases could happen here:
- if the new size is smaller than the current size, the vector is truncated.
- if the new size is larger than the current size, the vector is padded with value-initialized (default-initialization for class type, and zero-initialization for other types) elements, and the existing elements are preserved.

In case we resize a vector to be smaller:
```cpp
#include <iostream>
#include <vector>

void printLength(const std::vector<int>& v)
{
	std::cout << "The length is: "	<< v.size() << '\n';
}

int main()
{
    std::vector v{ 0, 1, 2, 3, 4 }; // length is initially 5
    printLength(v);

    v.resize(3);                    // resize to 3 elements
    printLength(v);

    for (int i : v)
        std::cout << i << ' ';

    std::cout << '\n';

    return 0;
}
```
This prints:
```
The length is: 5
The length is: 3
0 1 2
```
As you can see, the existing elements are preserved, and the vector is truncated to the new size.

#### The length vs capacity of a `std::vector`:
Up to this point, we have only talked about the **length** of a `std::vector`, that is the number of elements it contains in the current moment. However, `std::vector` also has a **capacity**, that is how many elements the `std::vector` (in this case) has allocated storage for.

A `std::vector` with a capcity of 5 has allocated space for 5 elements, but it may contain fewer elements. For example, if the vector contains 2 elements, it will have a capacity of 5, but a length of 2. 

#### getting the capacity of a `std::vector`:
We can get the capacity of a `std::vector` using the `capacity` member function:
```cpp
#include <iostream>
#include <vector>

void printCapLen(const std::vector<int>& v)
{
	std::cout << "Capacity: " << v.capacity() << " Length:"	<< v.size() << '\n';
}

int main()
{
    std::vector v{ 0, 1, 2 }; // length is initially 3

    printCapLen(v);

    for (auto i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    v.resize(5); // resize to 5 elements

    printCapLen(v);

    for (auto i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}
```
This could print (depending on the machine and the implementation of `std::vector`):
```
Capacity: 3 Length: 3
0 1 2
Capacity: 5 Length: 5
0 1 2 0 0
```
In this example, the initial capacity of the vector was 3, but after resizing to 5 elements, the capacity was increased to 5.

Most of the time, you will not use the capacity of a `std::vector` directly, but we will use in the following examples to understand how `std::vector` works at low level.

#### Reallocation of storage, and why it is expensive:
When a `std::vector` changes the amount of storage it is managing, this process ic called **reallocation**. Informally, this process goes as follows:
- The `std::vector` acquires new memory with capacity for the desired number of elements (e.g., `new_size * sizeof(T)` bytes).
- These elements are value-initialized.
- The elements in the old memory are copied (or moved, if possible) to the new memory. The old memory is then returned to the system and released.
- The capacity and the length of the `std::vector` are updated to reflect the new state.

From outside, it seems that the `std::vector` has just changed its capacity, but in reality, it has acquired new memory and copied the elements to the new memory. This process is expensive because it involves copying (or moving) elements, and it also involves allocating and deallocating memory.

#### Why differentiate length and capacity?
If a `std::vector` had only have its length, then every `resize()` request would require a reallocation to the new length. Having both length and capacity instead, gives the object the ability to decide when a reallocation is actually needed or not.

For example:
```cpp
#include <iostream>
#include <vector>

void printCapLen(const std::vector<int>& v)
{
	std::cout << "Capacity: " << v.capacity() << " Length:"	<< v.size() << '\n';
}

int main()
{
    // Create a vector with length 5
    std::vector v{ 0, 1, 2, 3, 4 };
    v = { 0, 1, 2, 3, 4 }; // okay, array length = 5
    printCapLen(v);

    for (auto i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    // Resize vector to 3 elements
    v.resize(3); // we could also assign a list of 3 elements here
    printCapLen(v);

    for (auto i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    // Resize vector back to 5 elements
    v.resize(5);
    printCapLen(v);

    for (auto i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}
```
This prints:
```
Capacity: 5  Length: 5
0 1 2 3 4 
Capacity: 5  Length: 3
0 1 2 
Capacity: 5  Length: 5
0 1 2 0 0
```
In this example:
- The initial capacity is 5, and the initial length is 5.
- When we resize the vector to 3 elements, the capacity is still 5, but the length is 3. This means that the vector has not been reallocated, leading to a more efficient operation.
- Finally, when we resize the vector back to 5 elements, the capacity is still 5, but the length is 5. It simply changed the length back to 5, without touching the memory, sicne that vector already had a capacity of 5.

By separating length and capacity, we avoided 2 reallocations, leading to a more efficient operation.

#### Vector indexing is based on length, not capacity:
Perhaps surprisingly, the subscript operator `operator[]` and `at()` member function are based on the length of the vector, not its capacity. So for example, in the example before, when `v` has capacity 5 and length 3, `v[3]` and `v.at(3)` will throw an exception, since there is no valid element at index 3.

#### Shrinking a `std::vector`:
Note this difference:
- When resizing to a larger size: both length and capacity (if required) will be increased.
- When resizing to a smaller size: only the length will be decreased, the capacity will remain the same.

Sometimes, we may want to shrink the capacity of a `std::vector` to match its length, for example when we resize a very large vector to a smaller size (this would potentially lead to a big memory waste). This can be done using the `shrink_to_fit` member function, that requests the `std::vector` to release any unused memory:
```cpp
#include <iostream>
#include <vector>

void printCapLen(const std::vector<int>& v)
{
	std::cout << "Capacity: " << v.capacity() << " Length:"	<< v.size() << '\n';
}

int main()
{

	std::vector<int> v(1000); // allocate room for 1000 elements
	printCapLen(v);

	v.resize(0); // resize to 0 elements
	printCapLen(v);

	v.shrink_to_fit();
	printCapLen(v);

	return 0;
}
```
This could print (depending on the machine):
```
Capacity: 1000 Length: 1000
Capacity: 1000 Length: 0
Capacity: 0 Length: 0
```
As you can see, when `shrink_to_fit` is called, the capacity is reduced to 0, matching the length.

Note that this request is **non-binding**, meaning that the implementation is free to ignore it. 

#### Summary:
- `std::vector` is a dynamic array that can grow and shrink as needed. This is different from `std::array` and `std::span`, which have a fixed size at compile time.
- `std::vector` can be resized using the `resize` member function, which changes the length of the vector.
- Allocated memory by `std::vector` (its capacity) is not automatically released when the vector is resized to a smaller size. 
- `shtink_to_fit` requests the `std::vector` to release any unused memory (make its capacity equal to its length), but it is non-binding, meaning that the implementation is free to ignore it.


---

### S11 - 16.11 `std::vector` and stack behavior
Consider the case where you are writing a program where the user will enter a list of values (such as a bunch of test scores). In this case, the number of values that they will be entering is not known at compile time, and could vary every time they run the program. 
In this case, we can use a `std::vector` to store the values, and we can resize it as needed. 

Based on what we have discussed so afr, there are few ways to approach this:
1. You could ask the user how many entried they have, create a vector of that size (`std::vector<int> v(size);`), and then fill it with the values. This requires the user to know in advance how many values they will be entering, and it might not be ideal.
2. You could assume that the user will not enter more than a certain number of values (e.g., 100), and create a vector of that size (`std::vector<int> v(100);`). Then, you could use a loop to fill the vector with the values, and resize it to the actual number of values entered. This is a common approach, and it is not too bad, but it is not the best, since the user is limited to enter at maximum `N` values.
3. We could address the problem by adding some logic to resize the vector larger when the user reaches the maximum number of values. This will increase the code complexity, and definitely lead to additional bugs.

The problem here is that we are trying to guess the number of values that the user will enter, and this is not a good idea, since there are situation when the number of values is really unknown a priori. To handle this case, there is a better approach, that we will discuss in the next.

Fist, some background.

#### What is a stack?
A **stack** is a data structure that stores elements in a Last In First Out (LIFO) manner. This means that the last element added to the stack is the first one to be removed.
Think about it as a stack of plates. You can only add a plate to the top of the stack, and you can only remove a plate from the top of the stack. 

#### Stacks in programming:
In programming, a **stack** is a container data type where the insertion and removal of elements occurs in a Last In First Out (LIFO) manner. This is commonly implemented by two main operations:
- `push`: add an element to the top of the stack
- `pop`: remove the top element from the stack

| Operation Name | Behavior | Required? | Notes |
| --- | --- | --- | --- |
| Push | Add an element to the top of the stack | Yes |                                     |
| Pop  | Remove the top element from the stack | Yes | May return the removed element or void|
| Top or Peek | Return the top element of the stack | Optional | Does not remove the element             |
| Empty| Return true if the stack is empty, false otherwise | Optional |                                     |
| Size | Return the number of elements in the stack | Optional |                                     |

For example, here’s a short sequence showing how pushing and popping on a stack works:
```
       (Stack: empty)
Push 1 (Stack: 1)
Push 2 (Stack: 1 2)
Push 3 (Stack: 1 2 3)
Pop    (Stack: 1 2)
Push 4 (Stack: 1 2 4)
Pop    (Stack: 1 2)
Pop    (Stack: 1)
Pop    (Stack: empty)
```

#### Stacks in C++:
In some languages, a stack is implemented as its own discrete container data type. But this could be limited, since you could not iterate over it without modifying the data structure itself.

In C++, stack-like operations were instead added (as member functions) to the existing standard library container classes that support efficient insertion and removal of elements at one end (`std::vector`, `std::queue` and `std::list`). This allows you to use these containers as stacks, without the need to implement a separate stack data structure.

In the following, we will nalyze how the stack interface of `std::vector` works, and how can be useful to solve the challange we discussed at the begining of this section.

#### Stack behavior with `std::vector`:
Stack behavior with `std::vector` is implemented with the following member functions:

| Function Name | Stack Operation | Behavior | Notes |
| `push_back` | Push | Add an element to the top of the stack | Adds the element to the end of vector |
| `pop_back`  | Pop  | Remove the top element from the stack | Returns void, removes the last element from the vector |
| `back`  | Top or Peek | Return the top element of the stack | Does not remove the element |
| `emplace_back` | Push | Add an element to the top of the stack | Alternative to `push_back` that constructs the element in place (could be more efficient) |

Let's have a look at an example:
```cpp
#include <iostream>
#include <vector>

void printStack(const std::vector<int>& stack)
{
	if (stack.empty()) // if stack.size == 0
		std::cout << "Empty";

	for (auto element : stack)
		std::cout << element << ' ';

	// \t is a tab character, to help align the text
	std::cout << "\tCapacity: " << stack.capacity() << "  Length " << stack.size() << "\n";
}

int main()
{
	std::vector<int> stack{}; // empty stack

	printStack(stack);

	stack.push_back(1); // push_back() pushes an element on the stack
	printStack(stack);

	stack.push_back(2);
	printStack(stack);

	stack.push_back(3);
	printStack(stack);

	std::cout << "Top: " << stack.back() << '\n'; // back() returns the last element

	stack.pop_back(); // pop_back() pops an element off the stack
	printStack(stack);

	stack.pop_back();
	printStack(stack);

	stack.pop_back();
	printStack(stack);

	return 0;
}
```
On GCC or Clang this will print:
```
Empty   Capacity: 0  Length: 0
1       Capacity: 1  Length: 1
1 2     Capacity: 2  Length: 2
1 2 3   Capacity: 4  Length: 3
Top:3
1 2     Capacity: 4  Length: 2
1       Capacity: 4  Length: 1
Empty   Capacity: 4  Length: 0
```
As you can see, `push_back()` (and `emplace_back()`) will increment the length of the vector, and will increase the capacity when needed. In this example, the vector gets reallocated 3 times, with a capacity of 1, 2 and 4.

#### Extra capacity from pushing:
In the example above, notice how the capacity of the vector is 4 after the third push, even though we only pushed 3 elements. When pushing triggers a reallocation, `std::vector` will typically allocate some extra capacity to allow additional elements to be added without triggering another reallocation (since this is an expensive operation).

How much exta capacity is left up to the compiler's implementation of `std::vector`, and it is not specified by the standard. Different compiler will typically do two things:
- GCC and Clang doubles the current capacity (e.g., when the last resize is triggered, it will be 2 * 2 = 4)
- Visual Studio 2022 mutiplies the current capacity by 1.5 (when the last resize is triggered, it will be 2 * 1.5 = 3)

#### Resizing a vector does not work with stack behavior:
Reallocating a vector is computationally expensive (proportional to the length of the vector), so we want to avoid reallocations when reasonable to do so. In the example above, we could avoid the vector being reallocated 3 times if we manually resized the vector to capacity 3 at the start of the program.

Let's have a look at what happens if we change line 18 to the following:
```cpp
std::vector<int> stack(3); // parenthesis init to set vector's capacity to 3
```

Now, the output will be:
```
0 0 0 	Capacity: 3  Length 3
0 0 0 1 	Capacity: 6  Length 4
0 0 0 1 2 	Capacity: 6  Length 5
0 0 0 1 2 3 	Capacity: 6  Length 6
Top: 3
0 0 0 1 2 	Capacity: 6  Length 5
0 0 0 1 	Capacity: 6  Length 4
0 0 0 	Capacity: 6  Length 3
```
This is clearly not right! The issue here is that we are using the parenthesis initialization to set the capacity of the vector, but this will initialize all the elements to 0, and the length of the vector will be 3 at the beginning.

What we really want is a way to chnage the capacity (to avoid future allocations) without changing the length (which has the side effect of adding new elements ot our stack).

#### The `reserve()` member function changes the capacity (but not the length):
The `reserve()` member function can be used to reallocate a `std::vector` without changing the length of the vector. 

Here is the same example as before, but using `reserve()` instead of parenthesis initialization:
```cpp
#include <iostream>
#include <vector>

void printStack(const std::vector<int>& stack)
{
	if (stack.empty()) // if stack.size == 0
		std::cout << "Empty";

	for (auto element : stack)
		std::cout << element << ' ';

	// \t is a tab character, to help align the text
	std::cout << "\tCapacity: " << stack.capacity() << "  Length " << stack.size() << "\n";
}

int main()
{
	std::vector<int> stack{};

	printStack(stack);

	stack.reserve(6); // reserve space for 6 elements (but do not change length)
	printStack(stack);

	stack.push_back(1);
	printStack(stack);

	stack.push_back(2);
	printStack(stack);

	stack.push_back(3);
	printStack(stack);

	std::cout << "Top: " << stack.back() << '\n';

	stack.pop_back();
	printStack(stack);

	stack.pop_back();
	printStack(stack);

	stack.pop_back();
	printStack(stack);

	return 0;
}
```
This could print something like:
```
Empty   Capacity: 0  Length: 0
Empty   Capacity: 6  Length: 0
1       Capacity: 6  Length: 1
1 2     Capacity: 6  Length: 2
1 2 3   Capacity: 6  Length: 3
Top: 3
1 2     Capacity: 6  Length: 2
1       Capacity: 6  Length: 1
Empty   Capacity: 6  Length: 0
```
You can notice that the capacity is 6, but the length is still 0, meaning that the vector was not initialized with any elements. In this way, no reallocation is triggered when we push the first element, leading to a more efficient implementation.

> **Note:** The `resize()` memebr function changes the length of the vector, and the capacity if necessary.
> The `reserve()` member function only changes the capacity of the vector (if necessary), and not the length.

#### `push_back()` vs `emplace_back()`:
Both `push_back()` and `emplace_back()` add an element on top of the stack. If the object to be pushed already exists, both member functions are equivalent, and `push_back()` should be preferred for its simplicity.

If the object to be pushed does not already exist (e.g., temporary object of the same type as the vector's element that we want to push) `emplace_back()` should be preferred, as it will construct the object in place, and it is generally more efficient:
```cpp
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

class Foo
{
private:
    std::string m_a{};
    int m_b{};

public:
    Foo(std::string_view a, int b)
        : m_a { a }, m_b { b }
        {}

    explicit Foo(int b)
        : m_a {}, m_b { b }
        {};
};

int main()
{
	std::vector<Foo> stack{};

	// When we already have an object, push_back and emplace_back are similar in efficiency
	Foo f{ "a", 2 };
	stack.push_back(f);    // prefer this one
	stack.emplace_back(f);

	// When we need to create a temporary object to push, emplace_back is more efficient
	stack.push_back({ "a", 2 }); // creates a temporary object, and then copies it into the vector
	stack.emplace_back("a", 2);  // forwards the arguments so the object can be created directly in the vector (no copy made)

	// push_back won't use explicit constructors, emplace_back will
	stack.push_back({ 2 }); // compile error: Foo(int) is explicit
	stack.emplace_back(2);  // ok

	return 0;
}
```
In this example, we ahve a vector of `Foo` objects, and we want to push a new `Foo` object on top of the stack.
- With `push_back({ "a", 2 })`: a temporary `Foo` object is created and initialized, which then gets copied into the vector. For expensive-to-copy types, this can be inefficient.
- With `emplace_back("a", 2)`: the `Foo` object is created in place, directly inside the vector, without any copy or move operations. This function will forward the arguments to the constructor of `Foo`, and it will create the object in place.

> **Best practice:** Prefer `emplace_back()` when creating a new temporary object to add to the container, or when you need to access an explicit constructor of the object.

> **Best practice:** Prefer `push_back()` otherwise.

#### Addressing our challenge using stack operations:
Finally, we can solve the issue we presented at the beginning (not knowing in advance the number of elements we need to store) using stack operations. If we do not know in advance how many elements will be added to our `std::vector`, we can use stack functions to insert those element one by one.

Here is an example:
```cpp
#include <iostream>
#include <limits>
#include <vector>

int main()
{
	std::vector<int> scoreList{};

	while (true)
	{
		std::cout << "Enter a score (or -1 to finish): ";
		int x{};
		std::cin >> x;

		if (!std::cin) // handle bad input
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		// If we're done, break out of loop
		if (x == -1)
			break;

		// The user entered a valid element, so let's push it on the vector
		scoreList.push_back(x);
	}

	std::cout << "Your list of scores: \n";

	for (const auto& score : scoreList)
		std::cout << score << ' ';

	return 0;
}
```
This program will keep asking the user to enter a score, and will store it in the `scoreList` vector. The loop will continue until the user enters -1, at which point the program will print the list of scores.

In this way, we are not required to do any counting, indexing, or pre-allocation of memory. We can simply push elements on the stack one by one, and let the `std::vector` handle the memory management for us.

#### Summary
- `std::vector` supports **stack behavior** via `push_back`, `pop_back`, and `back`.
- Stack usage is ideal when the number of elements is **unknown at runtime**.
- `push_back()` grows the vector and increases capacity when needed.
- Reallocation is expensive; vectors typically grow capacity geometrically.
- Parenthesis initialization sets **length and capacity**, which breaks stack semantics.
- `reserve()` increases **capacity only**, preserving correct stack behavior.
- `resize()` changes the **length** and should not be used for stacks.
- Prefer `emplace_back()` when constructing new temporary objects in-place.
- Prefer `push_back()` when the object already exists.
- Using stack operations avoids manual counting, indexing, and size guessing.


---

### S12 - 16.12 `std::vector<bool>`
In a previous chapter, we covered `std::bitset`, explaining how this has the capability to compact 8 boolean values into a byte. These bits can then be modified via te member functions of `std::bitset`.

`std::vector` has an interesting trick: it can compact boolean values into a byte, just like `std::bitset`, and it may also be more efficient than `std::bitset`.

Unlike `std::bitset`, which was designed for bit manipulation, `std::vector<bool>` lacks but manipullation member functions.

#### Using `std::vector<bool>`:
For the most part, `std::vector<bool>` works just like a normal `std::vector`:
```cpp
#include <iostream>
#include <vector>

int main()
{
    std::vector<bool> v { true, false, false, true, true };

    for (int i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    // Change the Boolean value with index 4 to false
    v[4] = false;

    for (int i : v)
        std::cout << i << ' ';
    std::cout << '\n';

    return 0;
}
```
On a 64-bit machine, this will print:
```
1 0 0 1 1
1 0 0 0 1
```
In this example, we have a `std::vector<bool>` with 5 boolean values. The output shows that the boolean values are stored in a compact form, with each boolean value occupying a single bit.

#### `std::vector<bool>` tradeoffs:
However, `std::vector<bool>` has a few tradeoffs:
- It has a fairly high amount of overhead (`sizeof(std::vector<bool>)` is 40 bytes on a 64-bit machine).
- Its performance is highly dependent upon the implementation, and so it is not stable.
- Most importantly, `std::vector<bool>` is not a vector (it is not required to be contiguous in memory), nor does it hold `bool` values (it holds a collection of bits), nor does it meet C++'s definition of a container.

Said that, `std::vector<bool>` is not fully compatible with other standard library containers. For example, this code works when `T` is any type except `bool`:
```cpp
template<typename T>
void foo( std::vector<T>& v )
{
    T& first = v[0]; // get a reference to the first element
    // Do something with first
}
```

#### Avoid using `std::vector<bool>`:
The modern consensus is to avoid using `std::vector<bool>`, as the performance gains are unlikely to be worth the incompatibility headaches due to it not being a proper container.

Our recommendation is as follows:
- Use (constexpr) `std::bitset` when the number of bits you need is known at compile time, you have a moderate number of bits to store, and the limited set of operators and member function meets your requirements.
- Prefer `std::vector<char>` when you need a resizable container of boolean values and space-saving is not necessary. This type behaves like a normal container.
- Favor 3rd party implementation of a dynamic bitset (e.g., `boost::dynamic_bitset`) when you need a resizable container of boolean values and space-saving is necessary.

> **Best practice:** Avoid using `std::vector<bool>`, as the performance gains are unlikely to be worth the incompatibility headaches due to it not being a proper container.

#### Summary:
- `std::vector<bool>` is a compact container of boolean values, but it is not a proper container.
- Use (constexpr) `std::bitset` when the number of bits you need is known at compile time, you have a moderate number of bits to store, and the limited set of operators and member function meets your requirements.
- Prefer `std::vector<char>` when you need a resizable container of boolean values and space-saving is not necessary. This type behaves like a normal container.
- Favor 3rd party implementation of a dynamic bitset (e.g., `boost::dynamic_bitset`) when you need a resizable container of boolean values and space-saving is necessary.


---

### SX - 16.x Summary and quiz
As always, have a look at the original summary, and good luck for the quizzes!

PS: solutions are inside `exercises/sx-questions` folder. Enjoy :)


---

## 🧭 Summary

In this chapter you moved from individual variables to **containers**: types that hold collections of elements (typically all of the same type) and let you work with them efficiently. You saw how **arrays** (especially `std::vector`) store elements contiguously in memory, enabling fast random access via the subscript operator `[]`, but also how this comes with no bounds checking by default.

You learned how container **size** is represented (`size()`, `std::size`, `std::ssize`, and the nested `size_type`), how to **pass vectors safely** (by `const&`), and how **copy vs move semantics** affect performance when returning or assigning containers. You also explored different ways to **traverse** containers (classic `for` loops vs range-based `for`) and how enums can make indices more readable and safer.

Finally, you dug into what makes `std::vector` a **dynamic array**: resizing, capacity, reallocation, `push_back` vs `emplace_back`, stack‑style LIFO usage, and why `std::vector<bool>` is a weird, special-case optimization that’s usually better avoided.

### 🧱 Core Concepts You Mastered:

- **Containers & arrays**
  - Containers hold collections of unnamed elements, usually of the same type.
  - Arrays are contiguous in memory and allow **random access**: `arr[i]` is O(1).

- **Size, length, and `size_type`**
  - Container length is often called **size**; get it via `v.size()` or `std::size(v)`.
  - Each container exposes a nested `size_type`, usually an alias of `std::size_t`:
    ```cpp
    std::vector<int>::size_type n = v.size();
    ```
  - `std::ssize(v)` (C++20) returns a signed length (typically `std::ptrdiff_t`).

- **`std::vector` basics & initialization**
  - `std::vector<T>` is a dynamic array class template defined in `<vector>`.
  - List vs direct initialization:
    ```cpp
    std::vector<int> v1{ 5 }; // one element: {5}
    std::vector<int> v2(5);   // five elements: {0,0,0,0,0}
    ```

- **Indexing: `operator[]` vs `.at()`**
  - `v[i]` is **fast but unchecked** (UB if `i` is out of range).
  - `v.at(i)` does **runtime bounds checking** and throws `std::out_of_range` on error.
  - Indices are expected to be of type `size_type` (unsigned), so be careful with signed/unsigned conversions.

- **Passing vectors to functions**
  - Passing by value copies all elements (expensive).
  - Prefer passing by (const) reference:
    ```cpp
    void print(const std::vector<int>& v);
    ```
  - Use function templates to accept vectors with any element type:
    ```cpp
    template <typename T>
    void print(const std::vector<T>& v);
    ```

- **Copy vs move semantics for containers**
  - **Copy semantics**: data is duplicated when copying a container.
  - **Move semantics**: ownership of internal storage is transferred when moving from an rvalue.
  - Returning a `std::vector` by value is efficient because the implementation will use move (or elide the copy) when possible:
    ```cpp
    std::vector<int> makeVec() { return {1, 2, 3}; }
    ```

- **Traversal & range-based `for`**
  - Traversal = visiting each element in some order (iteration).
  - Range-based for keeps code cleaner and avoids index bugs:
    ```cpp
    for (const auto& x : v) {
        std::cout << x << ' ';
    }
    ```
  - Use `const auto&` by default to avoid unnecessary copies unless you need to modify elements or take ownership.

- **Enums as indices**
  - Unscoped enums can document the meaning of indices:
    ```cpp
    enum FruitIndex { apple, banana, cherry, count };
    std::array<int, count> stock{ 10, 20, 30 };
    ```
  - The extra `count` enumerator conveniently encodes the array length.

- **Fixed-size vs dynamic arrays**
  - Fixed-size arrays: length chosen at instantiation, cannot change.
  - `std::vector` is a **dynamic array**: it can grow or shrink with `resize()` and stack-style operations.

- **Capacity, `resize`, `reserve`, `push_back`, `emplace_back`**
  - `size()` = how many elements are in use; `capacity()` = how many elements can fit before reallocation.
  - `resize(n)` changes the **size** (and capacity if needed).
  - `reserve(n)` changes only **capacity**, not size; good when you’ll `push_back` many elements.
  - `push_back(x)` appends an existing object.
  - `emplace_back(args...)` constructs the element in place and can avoid a temporary:
    ```cpp
    v.emplace_back(1, 2.0); // calls T{1, 2.0} directly inside the vector
    ```

- **Stack / LIFO behavior with `std::vector`**
  - Using `push_back` and `pop_back`, a vector behaves like a **stack** (LIFO).
  - Good mental model: “plate stack” – last item pushed is the first popped.

- **The `std::vector<bool>` trap**
  - `std::vector<bool>` is a space-optimized specialization that stores bits, not real `bool`s.
  - It’s not required to be contiguous like other vectors and doesn’t behave like a normal container in all cases.
  - Because of its quirks and incompatibilities, it’s usually better to avoid it (e.g., use `std::vector<char>` or `std::vector<uint8_t>` instead).



