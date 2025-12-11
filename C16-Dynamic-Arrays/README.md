# Chapter 16 - Dynamic Arrays: std::vector

## 🧭 Overview


---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch16_first
./build/ch16_first
```

---

## 🎯 Learning Outcomes


---

## Sections

### S16 - 16.1 Introduction to containers and arrays
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

### S16 - 16.2 Introduction to std::vector and list constructors
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

### S16 - 16.3 `std::vector` and the unsigned length and subscript problem
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

### S16 - 16.4 Passing `std::vector`
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

### S16 - 16.5 Returning `std::vector`, and an introduction to move semantics
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

### S16 - 16.6 Arrays and loops
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

### S16 - 16.7 Arrays, loops, and sign challange solutions
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
1. **Range-based for loops:** 
2. **Iterators:**

If you’re only using the index variable to traverse the array, then prefer a method that does not use indices.

> **Best Practice:** Avoid array indexing with integral values whenver possible.

#### Summary:
- 







































---

### SX - 16.x Summary and quiz
As always, have a look at the original summary, and good luck for the quizzes!

PS: solutions are inside `exercises/sx-questions` folder. Enjoy :)


---

## 🧭 Summary


### 🧱 Core Concepts You Mastered:


