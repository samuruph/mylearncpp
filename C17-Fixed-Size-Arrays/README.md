# Chapter 17 - Fixed Size Arrays: std::array and C-Style Arrays

## 🧭 Overview
This chapter deepens your understanding of **fixed-size arrays** in C++ — both `std::array` and C-style arrays — and contrasts them with dynamic arrays like `std::vector`.  
You learn:

- How `std::array` is designed (as a small, constexpr-friendly aggregate).
- How C-style arrays behave at the language level (decay, pointer arithmetic).
- How to safely get sizes and index elements.
- How to handle **arrays of references** and **multidimensional layouts**.

Everything here is about writing array code that is **safer**, **clearer**, and **more expressive**.


---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target ch17_first
./build/ch17_first
```

---

## 🎯 Learning Outcomes
By the end of this chapter, you’ll be able to:

- 📦 Distinguish between:
  - Fixed-size arrays: `std::array`, C-style arrays
  - Dynamic arrays: `std::vector`
- 🧮 Declare and initialize `std::array<T, N>`:
  - With explicit type and size:  
    ```cpp
    std::array<int, 3> a{ 1, 2, 3 };
    ```
  - With CTAD (class template argument deduction):  
    ```cpp
    std::array a{ 1, 2, 3 }; // deduces std::array<int, 3>
    ```
- 📏 Obtain array lengths using:
  - `arr.size()`
  - `std::size(arr)`
  - `std::ssize(arr)` (signed length)
- 🎯 Choose appropriate indexing APIs:
  - `operator[]`, `.at()`, and `std::get<N>(arr)`
- 🧷 Use `std::reference_wrapper`, `std::ref`, and `std::cref` to emulate **arrays of references**.
- 🧭 Explain **array decay** and perform basic **pointer arithmetic** on C-style arrays.
- 🧱 Work with **multidimensional arrays** and understand how `std::mdspan` provides a multidimensional view over contiguous memory.


---

## Sections

### S01 - 17.1 Introduction to `std::array`
In the previous chapter, we introduced containers and arrays. To summarize:
- Containers can provide storage for a collection of unnamed elements (typically of the same type).
- Arrays allocate their elements contiguously in memory, and provide fast access to elements via `operator[]`.
- C++ has three different array types commonly used:
    - `std::vector`: a dynamic array that can grow and shrink in size at runtime.
    - `std::array`: a fixed-size array that has a known size at compile time.
    - C-style arrays: a fixed-size array that has a known size at compile time.

In a lesson of that chapter, we mentioned that arrays falls into two categories:
- **Fixed-size arrays**: requires that the length of the array is known at the point of instantiation (e.g. `int arr[5]`), and the length cannot be changed later (e.g., C-style arrays and `std::array`).
- **Dynamic-size arrays**: arrays that can be resized at runtime (e.g., `std::vector`).

In the previous chapter, we focused on `std::vector`, as it is fast, comparatevely easy to use, and versatile.

#### So why not to use dynamic arrays for everything?
Dynamic arrays, as every structure, makes tradeoff to offer certain features:
- `std::vector` is slightly less performant than the fixed-size arrays, due to the need to manage dynamic memory and handle reallocations.
- `std::vector` only supports `constexpr` in very limited cases, while fixed-size arrays can be used in `constexpr` contexts.

> **Best Practice**: Use `std::array` for constexpr arrays, and `std::vector` for non-constexpr arrays.

#### Defining a `std::array`:
`std::array` is defined in the `<array>` header, and it is used as follows:
```cpp
#include <array>  // for std::array
#include <vector> // for std::vector

int main()
{
    std::array<int, 5> a {};  // a std::array of 5 ints

    std::vector<int> b(5);    // a std::vector of 5 ints (for comparison)

    return 0;
}
```
Differently to `std::vector`, `std::array` has two template arguments:
- The type template argument defining the type of the array elements (e.g., `int`)
- The integral non-type template argument defining the size of the array (e.g., `5`).

As you can see, both element type and size are required at compile time, and cannot be changed later.

#### The length of a `std::array` must be a constant expression:
Unlike `std::vector`, which can be resized at runtime, the length of a `std::array` must be a constant expression (i.e., a value that can be evaluated at compile time). Most often, this will be an integer literal, constexpr variable, or an unscoped enumerator:
```cpp
#include <array>

int main()
{
    std::array<int, 7> a {}; // Using a literal constant

    constexpr int len { 8 };
    std::array<int, len> b {}; // Using a constexpr variable

    enum Colors
    {
         red,
         green,
         blue,
         max_colors
    };

    std::array<int, max_colors> c {}; // Using an enumerator

#define DAYS_PER_WEEK 7
    std::array<int, DAYS_PER_WEEK> d {}; // Using a macro (don't do this, use a constexpr variable instead)

    return 0;
}
```

It is important to note that non-const variables and runtime constants cannot be sued for the size of a `std::array`:
```cpp
#include <array>
#include <iostream>

void foo(const int length) // length is a runtime constant
{
    std::array<int, length> e {}; // error: length is not a constant expression
}

int main()
{
    // using a non-const variable
    int numStudents{};
    std::cin >> numStudents; // numStudents is non-constant

    std::array<int, numStudents> {}; // error: numStudents is not a constant expression

    foo(7);

    return 0;
}
```

#### Aggregate initialization of a `std::array`:
Perhaps surprisingly, `std::array` is an **aggregate** type, and so does not have any constructor, and it is initialized using aggregate initialization:
```cpp
#include <array>

int main()
{
    std::array<int, 6> fibonnaci = { 0, 1, 1, 2, 3, 5 }; // copy-list initialization using braced list
    std::array<int, 5> prime { 2, 3, 5, 7, 11 };         // list initialization using braced list (preferred)

    return 0;
}
```
This is different from `std::vector`, which has a constructor that takes a size and an initial value, e.g. `std::vector<int> v(5, 0);`.

If a `std::array` is defined without an initializer, the elements will be default initialized (in most cases, they will be left uninitialized, but this is implementation-defined, so it is better to always initialize them explicitly).

It is preferred to value initialize a `std::array`, since we usually want our elements to be initialized:
```cpp
#include <array>
#include <vector>

int main()
{
    std::array<int, 5> a;   // Members default initialized (int elements are left uninitialized)
    std::array<int, 5> b{}; // Members value initialized (int elements are zero initialized) (preferred)

    std::vector<int> v(5);  // Members value initialized (int elements are zero initialized) (for comparison)

    return 0;
}
```
In this way, we ensure that our elements are initialized to a known value, and we avoid undefined behavior.

Additionally, if more than one initializer is provided, the compiler will error, while if less than the size of the array, the remaining elements will be value initialized:
```cpp
#include <array>

int main()
{
    std::array<int, 4> a { 1, 2, 3, 4, 5 }; // compile error: too many initializers
    std::array<int, 4> b { 1, 2 };          // b[2] and b[3] are value initialized

    return 0;
}
```

#### Const and constexpr `std::array`:
A `std::array` can be const:
```cpp
#include <array>

int main()
{
    const std::array<int, 5> prime { 2, 3, 5, 7, 11 };

    return 0;
}
```
This is different from `std::vector`, which can be const, but the elements of a const `std::vector` can still be modified.

Moreover, a `std::array` can be constexpr, while a `std::vector` cannot:
```cpp
#include <array>

int main()
{
    constexpr std::array<int, 5> prime { 2, 3, 5, 7, 11 };

    return 0;
}
```
This is the key reason why we should use `std::array` for constexpr arrays, and `std::vector` for non-constexpr arrays.

> **Best Practice**: Define your `std::array` as constexpr whenever possible, if your array is not constexpr, consider using a `std::vector` instead.

#### Class template argument deduction (CTAD) for `std::array` (C++17):
With CTAD (C++17 and later), we can let the compiler deduce both the type and the size of the array from a list of initializers:
```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array a1 { 9, 7, 5, 3, 1 }; // The type is deduced to std::array<int, 5>
    constexpr std::array a2 { 9.7, 7.31 };     // The type is deduced to std::array<double, 2>

    return 0;
}
```
We favor this syntax whenever practical. If your compiler is not C++17 capable, you’ll need to explicitly provide the type and length template arguments.

> **Best Practice**: Use CTAD for `std::array` whenever possible.
CTAD does not support partial omission of template arguments (as of C++23), so there is no way to use a core language feature to omit just the length or just the type of a `std::array`:
```cpp
#include <iostream>

int main()
{
    constexpr std::array<int> a2 { 9, 7, 5, 3, 1 };     // error: too few template arguments (length missing)
    constexpr std::array<5> a2 { 9, 7, 5, 3, 1 };       // error: too few template arguments (type missing)

    return 0;
}
```
So, you can deduce both together, or not at all. 

#### Omitting just the array length using `std::to_array` (C++20):
TAD (template argument deduction, used for function template resolution) does support partial omission of template arguments. Since C++20, it is possible to omit the array length by using the `std::to_array` function template:
```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr auto myArray1 { std::to_array<int, 5>({ 9, 7, 5, 3, 1 }) }; // Specify type and size
    constexpr auto myArray2 { std::to_array<int>({ 9, 7, 5, 3, 1 }) };    // Specify type only, deduce size
    constexpr auto myArray3 { std::to_array({ 9, 7, 5, 3, 1 }) };         // Deduce type and size

    return 0;
}
```
In this way, by using a function template, we can omit the array length, and let the compiler deduce it from the initializer list.

Unfortunately, this comes at a cost, This is generally more expensive than creating a `std::array` directly, because it creates a temporary array and copies the elements into the new array. For example, you could use `std::to_array` like this:
```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr auto shortArray { std::to_array<short>({ 9, 7, 5, 3, 1 }) };
    std::cout << sizeof(shortArray[0]) << '\n';

    return 0;
}
```
In this case, this is preferred because there is no way to specify a literal of type `short` in C++, and if you do not want to specify the length of the array, you can use `std::to_array`.

#### Accessing array elements using `operator[]`:
Like `std::vector`, the most common way to access an element of a `std::array` is using the subscript operator `operator[]`:
```cpp
#include <array> // for std::array
#include <iostream>

int main()
{
    constexpr std::array<int, 5> prime{ 2, 3, 5, 7, 11 };

    std::cout << prime[3]; // print the value of element with index 3 (7)
    std::cout << prime[9]; // invalid index (undefined behavior)

    return 0;
}
```
Exactly as with `std::vector`, accessing an element using `operator[]` with an invalid index is undefined behavior, since this is not performing bounds checking.

#### Summary:
- `std::array` is a fixed-size array container that provides a way to store a fixed number of elements of the same type.
- `std::array` can be constexpr, while `std::vector` cannot.
- Use `std::array` when the size of the array is known at compile time, and `std::vector` when the size of the array is known at runtime.
- To define a `std::array`, you need to specify the type and the size of the array (e.g., `std::array<int, 5> myArray`), and you can initialize it using an initializer list (e.g., `std::array<int, 5> myArray { 1, 2, 3, 4, 5 }`).
- You can use CTAD (C++17 and later) to let the compiler deduce both the type and the size of the array from a list of initializers (e.g., `std::array a1 { 9, 7, 5, 3, 1 }`).
- If you want to omit the array length, you can use `std::to_array` (C++20 and later) (e.g., `std::to_array<short>({ 9, 7, 5, 3, 1 })`).
- To access an element of a `std::array`, you can use the subscript operator `operator[]` (e.g., `myArray[2]`), without bounds checking.


---

### S02 - 17.2 `std::array` length and indexing
In the last chapter, we vastly discussed about the unfortunate decision to make the standard library container classes use **unsigned** values for lengths and indices. Because `std::array` is a standard library container class, it is also affected by this decision.

In this lesson, we will recap some ways to index and get the length of a `std::array`. This is very similar to `std::vector` (they have a similar interface), but since `std::array` can also be constexpr, we will see it more in details.

A small recap: *"sign conversions are narrowing conversions, except when constexpr"*. This is because when a value is constexpr, the compiler can check at compile time if the conversion is valid (if it is inside the range of the destination type), and if it is not, it will generate a compile-time error.

#### The length of a `std::array` has type `std::size_t`:
`std::array` is implemented as a template struct whose declaration looks like this:
```cpp
template<typename T, std::size_t N> // N is a non-type template parameter
struct array;
```
As you can see, the non-type template parameter representing the array length (`N`) has type `std::size_t`. So, the length of a `std::array` is a large unsigned integral type.

Because this value, in the case of `std::array`, must be a **constexpr**, we will not run into sign conversions issues, as the compiler will happily convert a signed integral value to a `std::size_t` at compile time, without being considered a narrowing conversion.

#### The length and indices of `std::array` have type `size_type`, which is always `std::size_t`:
Like `std::vector`, `std::array` defines a nested typedef member named `size_type`, which is an alias for the type used for the length (and indices, if supported) of the container. In case of `std::array`, this is **always** `std::size_t`. In the non-type template parameter `N`, this has type `std::size_t` since `size_type` is a memebr of `std::array`, and at that point it is not yet defined. Anywhere else in the code, `size_type` will be used.

#### Getting the length of a `std::array`:
There are three common ways to get the length of a `std::array`, returning an **unsigned** `size_type`:
- Using the `size` member function:
    ```cpp
    #include <array>
    #include <iostream>

    int main()
    {
        constexpr std::array arr { 9.0, 7.2, 5.4, 3.6, 1.8 };
        std::cout << "length: " << arr.size() << '\n'; // returns length as type `size_type` (alias for `std::size_t`)
        return 0;
    }
    ```
- In C++17 and later, you can use the `std::size` non-member function template to get the length of a `std::array`, returning an **unsigned** `size_type`:
    ```cpp
    #include <array>
    #include <iostream>

    int main()
    {
        constexpr std::array arr{ 9, 7, 5, 3, 1 };
        std::cout << "length: " << std::size(arr); // C++17, returns length as type `size_type` (alias for `std::size_t`)

        return 0;
    }
    ```
- In C++20 and later, you can use the `std::ssize` non-member function template to get the length of a `std::array`, returning a **signed** `std::ptrdiff_t`:
    ```cpp
    #include <array>
    #include <iostream>

    int main()
    {
        constexpr std::array arr { 9, 7, 5, 3, 1 };
        std::cout << "length: " << std::ssize(arr); // C++20, returns length as a large signed integral type

        return 0;
    }
    ```

#### Getting the length of a `std::array` as a constexpr value:
Because the length of a `std::array` is a constexpr, each of the above functions will return the length of the array as a constexpr value (even when called on a non-constexpr array). This measn we can use these functions in constant expressions, and the returned value can be implicitely converted to an `int` without loss of information:
```cpp
#include <array>
#include <iostream>

int main()
{
    std::array arr { 9, 7, 5, 3, 1 }; // note: not constexpr for this example
    constexpr int length{ std::size(arr) }; // ok: return value is constexpr std::size_t and can be converted to int, not a narrowing conversion

    std::cout << "length: " << length << '\n';

    return 0;
}
```

#### Subscripting `std::array` using `operator[]` or the `at` member function:
In a previous lesson, we ahve seen that the most common indexing method (`operator[]`) does not perform bounds checking, and it can lead to undefined behavior if the index is out of bounds. 

Just like `std::vector`, `std::array` also has an `at()` member function, which performs runtime bounds checking. We generally recommend avoiding this functions since we typically want to do bounds checking before indexing, or want compile-time bounds checking.
Both of these function expect the index to be of type `size_type` (alias for `std::size_t`).

> **Best practice**: Avoid using `at()`, since it performs runtime bounds checking.

If either of these functions are called with a constexpr value, the compiler will do a constexpr conversion to `size_type` (alias for `std::size_t`), and if the conversion is not valid, it will generate a compile-time error.

#### `std::get()` does compile-time bounds checking for constexpr indices:
Since the length of a `std::array` is a constexpr, if our index is also a constexpr value, the compiler should be able to validate the index at compile time that our index is within bounds, and generate a compile-time error if the index is out of bounds.

However, `operator[]` does not eprform nounds checking at all, and `at()` performs runtime bounds checking. Moreover, function parameters can’t be constexpr (even for constexpr or consteval functions), so how do we even pass a constexpr index?

To solve this, we can use the `std::get()` function template, which takes the index as a non-type template argument:
```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array prime{ 2, 3, 5, 7, 11 };

    std::cout << std::get<3>(prime); // print the value of element with index 3
    std::cout << std::get<9>(prime); // invalid index (compile error)

    return 0;
}
```
Inside its implementation, there is a `static_assert` that checks if the index is within bounds, and if it is not, it will generate a compile-time error.

#### Summary:
- The length and indices of `std::array` have type `size_type`, which is always `std::size_t`.
- To get the length of a `std::array`, we can use the `size` member function, the `std::size` non-member function template, or the `std::ssize` non-member function template. The last one returns a signed integral value.
- We can use any of the above functions to get the length of a `std::array` as a constexpr value, and the returned value can be implicitely converted to an `int` without loss of information.
- `operator[]` does not perform bounds checking at all, and `at()` performs runtime bounds checking (avoid using `at()`).
- `std::get()` performs compile-time bounds checking for constexpr indices (e.g., `std::get<3>(arr)`), and it will generate a compile-time error if the index is out of bounds.


---

### S03 - 17.3 Passing and returning `std::array`
An object of type `std::array` can be passed to a function just like any other object, and the function can return an `std::array` as well. If you pass it by value, an expensive copy will be made. So in general, we typically pass `std::array` by (const) reference to avoid the copy.

With a `std::array`, both the element type and the array length are part of the type information of the object, so we need to specify both when we declare a function parameter or return type:
```cpp
#include <array>
#include <iostream>

void passByRef(const std::array<int, 5>& arr) // we must explicitly specify <int, 5> here
{
    std::cout << arr[0] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 }; // CTAD deduces type std::array<int, 5>
    passByRef(arr);

    return 0;
}
```

CTAD does not currently work with function parameters, so we must explicitly specify the template arguments.

#### Using function template to pass `std::array` of different element types or lengths:
To write a function that accept `std::array` with any kind of element type or length, we can use a function template to parameterize the element type and the array length:
```cpp
#include <array>
#include <iostream>

template <typename T, std::size_t N> // note that this template parameter declaration matches the one for std::array
void passByRef(const std::array<T, N>& arr)
{
    static_assert(N != 0); // fail if this is a zero-length std::array

    std::cout << arr[0] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 }; // use CTAD to infer std::array<int, 5>
    passByRef(arr);  // ok: compiler will instantiate passByRef(const std::array<int, 5>& arr)

    std::array arr2{ 1, 2, 3, 4, 5, 6 }; // use CTAD to infer std::array<int, 6>
    passByRef(arr2); // ok: compiler will instantiate passByRef(const std::array<int, 6>& arr)

    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // use CTAD to infer std::array<double, 5>
    passByRef(arr3); // ok: compiler will instantiate passByRef(const std::array<double, 5>& arr)

    return 0;
}
```
In this way, we can write a function that accept `std::array` of any element type and any length, without the need to specify the actual type and length of the array (e.g., `passByRef(const std::array<int, 5>& arr)`). The compiler, when we call `passByRef(arr)` will deduce the template arguments (e.g., `int` and `5`), and instantiate the function template with those arguments.

If desired, it is possible to only template one of the two arguments, and explicitely define the other one:
```cpp
#include <array>
#include <iostream>

template <std::size_t N> // note: only the length has been templated here
void passByRef(const std::array<int, N>& arr) // we've defined the element type as int
{
    static_assert(N != 0); // fail if this is a zero-length std::array

    std::cout << arr[0] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 }; // use CTAD to infer std::array<int, 5>
    passByRef(arr);  // ok: compiler will instantiate passByRef(const std::array<int, 5>& arr)

    std::array arr2{ 1, 2, 3, 4, 5, 6 }; // use CTAD to infer std::array<int, 6>
    passByRef(arr2); // ok: compiler will instantiate passByRef(const std::array<int, 6>& arr)

    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // use CTAD to infer std::array<double, 5>
    passByRef(arr3); // error: compiler can't find matching function

    return 0;
}
```
This is a normal behavior of template argument deduction, so everything works as expected.

#### Auto non-type template parameter (C++20):
Since having to remember (or look up) the type of the non-type template parameter can be a bit of a hassle, C++20 introduced the `auto` keyword for non-type template parameters:
```cpp
#include <array>
#include <iostream>

template <typename T, auto N> // now using auto to deduce type of N
void passByRef(const std::array<T, N>& arr)
{
    static_assert(N != 0); // fail if this is a zero-length std::array

    std::cout << arr[0] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 }; // use CTAD to infer std::array<int, 5>
    passByRef(arr);  // ok: compiler will instantiate passByRef(const std::array<int, 5>& arr)

    std::array arr2{ 1, 2, 3, 4, 5, 6 }; // use CTAD to infer std::array<int, 6>
    passByRef(arr2); // ok: compiler will instantiate passByRef(const std::array<int, 6>& arr)

    std::array arr3{ 1.2, 3.4, 5.6, 7.8, 9.9 }; // use CTAD to infer std::array<double, 5>
    passByRef(arr3); // ok: compiler will instantiate passByRef(const std::array<double, 5>& arr)

    return 0;
}
```
In this way, we can write a function that accept `std::array` of any element type and any length, without the need to specify the actual type of the non-type template parameter (`std::size_t` in this case).

#### Static asserting on array length:
Consider the following example (similar to the one before):
```cpp
#include <array>
#include <iostream>

template <typename T, std::size_t N>
void printElement3(const std::array<T, N>& arr)
{
    std::cout << arr[3] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 };
    printElement3(arr);

    return 0;
}
```
This will compile and run successfully, printing `3` to the console. However, if we try to access an element that is out of bounds, we will get undefined behavior:
```cpp
#include <array>
#include <iostream>

template <typename T, std::size_t N>
void printElement3(const std::array<T, N>& arr)
{
    std::cout << arr[3] << '\n'; // invalid index
}

int main()
{
    std::array arr{ 9, 7 }; // a 2-element array (valid indexes 0 and 1)
    printElement3(arr);

    return 0;
}
```
This is because the compiler will let you pass any index to the function, even if it is out of bounds. 

Ideally, we would like to let the compiler warn us if we try to access an element that is out of bounds. One advantage that template parameters have over function parameters is that template parameters are compile-time constants, so we can take advantage of capabilities that require constant expressions.

One option would be to use `std::get` (compile-time bounds checking) instead of `operator[]` (no bounds checking at all):
```cpp
#include <array>
#include <iostream>

template <typename T, std::size_t N>
void printElement3(const std::array<T, N>& arr)
{
    std::cout << std::get<3>(arr) << '\n'; // checks that index 3 is valid at compile-time
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 };
    printElement3(arr); // okay

    std::array arr2{ 9, 7 };
    printElement3(arr2); // compile error

    return 0;
}
```
In this case, the compiler will emit an error if we try to access an element that is out of bounds, as it can perform compile-time bounds checking.

An alternative solution is to use `static_assert` to validate a precondition on the array length at compile time ourselfs:
```cpp
#include <array>
#include <iostream>

template <typename T, std::size_t N>
void printElement3(const std::array<T, N>& arr)
{
    // precondition: array length must be greater than 3 so element 3 exists
    static_assert (N > 3);

    // we can assume the array length is greater than 3 beyond this point

    std::cout << arr[3] << '\n';
}

int main()
{
    std::array arr{ 9, 7, 5, 3, 1 };
    printElement3(arr); // okay

    std::array arr2{ 9, 7 };
    printElement3(arr2); // compile error

    return 0;
}
```
In this case, when the compiler reaches the call to `printElement3(arr2);`, it will instantiate the function `printElement3(const std::array<int, 2>& arr)`, with `T` deduced as `int` and `N` deduced as `2`. The `static_assert` will fail at compile time, as `N` (equal to `2`) is not greater than `3`.

#### Returning a `std::array`:
Syntax aside, passing a `std::array` to a function is quite easy: pass it by (const) reference. 

Retrning a `std::arra` from a function instead, it is a little bit more complex. Unlike `std::vector`, `std::array` is **not move-capable**, so returning a `std::array` from a function will make a copy of the array, which is not efficient. 

There are two conventional options to return a `std::array` from a function:
- Return a `std::array` by value
- Return a `std::array` via an out parameter

#### Returning a `std::array` by value:
It is okay to return a `std::array` by value when all of the following are true:
- The array isn't huge.
- The element type is cheap to copy (or move).
- The code isn't being used in a performance-critical context.

```cpp
#include <array>
#include <iostream>
#include <limits>

// return by value
template <typename T, std::size_t N>
std::array<T, N> inputArray() // return by value
{
	std::array<T, N> arr{};
	std::size_t index { 0 };
	while (index < N)
	{
		std::cout << "Enter value #" << index << ": ";
		std::cin >> arr[index];

		if (!std::cin) // handle bad input
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		++index;
	}

	return arr;
}

int main()
{
	std::array<int, 5> arr { inputArray<int, 5>() };

	std::cout << "The value of element 2 is " << arr[2] << '\n';

	return 0;
}
```

There are some nice things about this method:
- It uses the most conventional way to return data from a function.
- It is obvious what the function is returning (the array).
- We can define an array and use the function to initialize it in a single line (using this function).

There are also some downsides to this method:
- The function returns a copy of the array, which is not efficient.
- When we call the function, we must explicitely supply the template arguments since there is no parameter to deduce them from.

#### Returning a `std::array` via an out parameter:
In cases where the array is huge or the element type is expensive to copy, we can return a `std::array` via an out parameter. In this case, the caller must provide the array of type `std::array` by **non-const** reference (or address), and the function can then modify the array in place. For example:
```cpp
#include <array>
#include <limits>
#include <iostream>

template <typename T, std::size_t N>
void inputArray(std::array<T, N>& arr) // pass by non-const reference
{
	std::size_t index { 0 };
	while (index < N)
	{
		std::cout << "Enter value #" << index << ": ";
		std::cin >> arr[index];

		if (!std::cin) // handle bad input
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		++index;
	}

}

int main()
{
	std::array<int, 5> arr {};
	inputArray(arr);

	std::cout << "The value of element 2 is " << arr[2] << '\n';

	return 0;
}
```
The main advantage of this method is that it is more efficient than returning a `std::array` by value, as it avoids making a copy of the array.

Some downsides to this method are:
- This method is non-conventional, and it is not clearly obvious what the function is modifying/returning.
- We can only use this approach to assign values to the array, not to initialize it.
- Such function cannot be used to produce temporary arrays, as we need a non-const reference to modify the array in place.

#### Returning a `std::vector` instead:
Unlike `std::array`, `std::vector` is move-capable, so returning a `std::vector` from a function is more efficient than returning a `std::array` from a function. If you are returning a `std::array` by value, your returned object probably isn't constexpr, and you should consider using (and returning) a `std::vector` instead.

#### Summary:
- Use function templates to pass `std::array` of different types or lengths (e.g., `template <typename T, std::size_t N> void func(const std::array<T, N>& arr)`).
- From C++20, you can use `auto` instead of explicitly writing `std::size_t` (e.g., `template <typename T, auto N> void func(const std::array<T, N>& arr)`).
- You can perform bounds checking using `std::get` (e.g., `std::get<3>(arr)`) or directly using `static_assert` (e.g., `static_assert(N > 3)`) with the template parameter.
- Unlike `std::vector`, `std::array` is not move-capable, so returning a `std::array` from a function is less efficient than returning a `std::vector` from a function.
- You can return a `std::array` by value, but it is not recommended for large arrays or expensive-to-copy element types.
- Otherwise, you can return a `std::array` via an out parameter, but it is non-conventional and not clearly obvious what the function is modifying/returning.


---

### S04 - 17.4 `std::array` of class types, and brace elision
`std::array` is not limited to elements of fundamental types, instead elements of any type can be stored in an `std::array`, including compound types (e.g., arrays, structs, classes, etc.). This means you can create a `std::array` of pointers, or a `std::array` of structs (or classes).

The last case can be a bit tricky, so we will spend this lesson on it.

#### Defining and assigning to a `std::array` of structs:
Here is a simple struct:
```cpp
struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};
```
We can define an `std::array` of `House` like this:
```cpp
std::array<House, 3> houses{};
```
and the overall code will look like this:
```cpp
#include <array>
#include <iostream>

struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};

int main()
{
    std::array<House, 3> houses{};

    houses[0] = { 13, 1, 7 };
    houses[1] = { 14, 2, 5 };
    houses[2] = { 15, 2, 4 };

    for (const auto& house : houses)
    {
        std::cout << "House number " << house.number
                  << " has " << (house.stories * house.roomsPerStory)
                  << " rooms.\n";
    }

    return 0;
}
```
This will print:
```
House number 13 has 7 rooms.
House number 14 has 10 rooms.
House number 15 has 8 rooms.
```

This is quite easy, you initialize the array specifying the tpye of the elements and the size of the array as done previously, and then you can assign values to the elements using the array subscript operator.

#### Initializing a `std::array` of structs:
We can also initialize a `std::array` of structs in a more compact way, using brace elision. For example, we can initialize the `houses` array like this:
```cpp
constexpr std::array houses{ // use CTAD to deduce template arguments <House, 3>
    House{ 13, 1, 7 },
    House{ 14, 2, 5 },
    House{ 15, 2, 4 },
};
```
In this example, we have used CTAD (Class Template Argument Deduction) to deduce the template arguments of the `std::array` from the initializer list.

#### Initialization without explicitly specifying the element type for each element:
You might think we could initialize the `std::array` without specifying the element type for each element:
```cpp
// doesn't work
constexpr std::array<House, 3> houses { // we're telling the compiler that each element is a House
        { 13, 1, 7 }, // but not mentioning it here
        { 14, 2, 5 },
        { 15, 2, 4 }
    };
```
Instead, this is not working. Let's see why.

A `std::array` is defined as a struct that contains a single C-style array member (whose name is implementation-defined) like this:
```cpp
template<typename T, std::size_t N>
struct array
{
    T implementation_defined_name[N]; // a C-style array with N elements of type T
}
```
We haven't covered C-style arrays yet, but you can think of it as a fixed-size array of N elements of type T.

So, when we try to initialize `houses` with the above code, the comliler interprets the initialization like this:
```cpp
// Doesn't work
constexpr std::array<House, 3> houses { // initializer for houses
    { 13, 1, 7 }, // initializer for C-style array member with implementation_defined_name
    { 14, 2, 5 }, // ?
    { 15, 2, 4 }  // ?
};
```
The compiler will interpret `{ 13, 1, 7 }` as an initializer for the first member of `houses`, which is the C-style array with the implementation-defined name. This then will initialize the C-style array element `0` with the value `{ 13, 1, 7 }`, and the rest of the elements will be zero-initialized. Then, the compiler will find out that we provided two more initialization values (`{ 14, 2, 5 }` and `{ 15, 2, 4 }`), and it will produce a compilation error telling us that we have provided too many initialization values.

The correct way to initialize it is by adding an extra set of braces as follows:
```cpp
// This works as expected
constexpr std::array<House, 3> houses { // initializer for houses
    { // extra set of braces to initialize the C-style array member with implementation_defined_name
        { 13, 4, 30 }, // initializer for array element 0
        { 14, 3, 10 }, // initializer for array element 1
        { 15, 3, 40 }, // initializer for array element 2
     }
};
```
In this way, the compiler will interpret the initialization as follows:
- `{ 13, 4, 30 }` as an initializer for the first member of `houses`
- `{ 14, 3, 10 }` as an initializer for the second member of `houses`
- `{ 15, 3, 40 }` as an initializer for the third member of `houses`

Here is a full example:
```cpp
#include <array>
#include <iostream>

struct House
{
    int number{};
    int stories{};
    int roomsPerStory{};
};

int main()
{
    constexpr std::array<House, 3> houses {{ // note double braces
        { 13, 1, 7 },
        { 14, 2, 5 },
        { 15, 2, 4 }
    }};

    for (const auto& house : houses)
    {
        std::cout << "House number " << house.number
                  << " has " << (house.stories * house.roomsPerStory)
                  << " rooms.\n";
    }

    return 0;
}
```

#### brace elision for aggregates:
Given the explanation above, you may be wondering why the above case requires double braces, but all other cases we’ve seen only require single braces:
```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array<int, 5> arr { 1, 2, 3, 4, 5 }; // single braces

    for (const auto n : arr)
        std::cout << n << '\n';

    return 0;
}
```

It turns out that you can also supply double braces for this case, and it will work as expected:
```cpp
#include <array>
#include <iostream>

int main()
{
    constexpr std::array<int, 5> arr {{ 1, 2, 3, 4, 5 }}; // double braces

    for (const auto n : arr)
        std::cout << n << '\n';

    return 0;
}
```


However, aggregates in C++ supports a concept called **brace elision**, which covers some rules for when multiple braces may be omitted. Generally, you can omit braces when initializing a `std::array` with scalar (single) values, or when initializing with class types or arrays where the type is explicitely names with each element (as in the previous example with `House` specified for each element).

There is no harm in always initializing with double braces, and it can make the code more readable.

#### Another example:
Herre is one more example where we initialize `std::array` with `Student` struct:
```cpp
#include <array>
#include <iostream>
#include <string_view>

// Each student has an id and a name
struct Student
{
	int id{};
	std::string_view name{};
};

// Our array of 3 students (single braced since we mention Student with each initializer)
constexpr std::array students{ Student{0, "Alex"}, Student{ 1, "Joe" }, Student{ 2, "Bob" } };

const Student* findStudentById(int id)
{
	// Look through all the students
	for (auto& s : students)
	{
		// Return student with matching id
		if (s.id == id) return &s;
	}

	// No matching id found
	return nullptr;
}

int main()
{
	constexpr std::string_view nobody { "nobody" };

	const Student* s1 { findStudentById(1) };
	std::cout << "You found: " << (s1 ? s1->name : nobody) << '\n';

	const Student* s2 { findStudentById(3) };
	std::cout << "You found: " << (s2 ? s2->name : nobody) << '\n';

	return 0;
}
```
This prints:
```
You found: Joe
You found: nobody
```
Note that since `std::array students` is constexpr, our `findStudentById` function must return a const pointer, which means our `Student` pointers in `main()` must also be const.

#### Summary:
- You can define a `std::array` of structs or classes (e.g., `std::array<Student, 3>`).
- You can initialize a `std::array` of structs or classes using brace elision (e.g., `std::array students{ Student{0, "Alex"}, Student{ 1, "Joe" }, Student{ 2, "Bob" } }`).
- Or you can use double braces (e.g., `std::array<Students, 3> students {{ Student{0, "Alex"}, Student{ 1, "Joe" }, Student{ 2, "Bob" } }}`).


---

### S05 - 17.5 Arrays of references via `std::reference_wrapper`
In the prior lesson, we mentioned that arrays can have elements of any object type. This includes objects with fundamental types (e.g. int) and objects with compound types (e.g. pointer to int).
```cpp
#include <array>
#include <iostream>
#include <vector>

int main()
{
    int x { 1 };
    int y { 2 };

    [[maybe_unused]] std::array valarr { x, y };   // an array of int values
    [[maybe_unused]] std::vector ptrarr { &x, &y }; // a vector of int pointers

    return 0;
}
```
However, because **refernces are not objects**, you cannot make an array of ereferences. The elements of an array must also be assignable, and references cannot be reseated.
```cpp
#include <array>
#include <iostream>

int main()
{
    int x { 1 };
    int y { 2 };

    [[maybe_unused]] std::array<int&, 2> refarr { x, y }; // compile error: cannot define array of references

    int& ref1 { x };
    int& ref2 { y };
    [[maybe_unused]] std::array valarr { ref1, ref2 }; // ok: this is actually a std::array<int, 2>, not an array of references

    return 0;
}
```
In this example, we show that we cannot define an array of references to `int` (`int&`), because we must have assignable objects in an array. The second case works because we are storing the references in a `std::array` of `int`, not in an array of references.

This is euqlly applicable to **all array types**, not only `std::array`.

If you really want an array of references, there is a way to do it using `std::reference_wrapper`.

#### `std::reference_wrapper`:
`std::reference_wrapper` is a standard library class template that lives in the `<functional>` header. It takes a type template argument `T`, and then behaves like a modifiable lvalue reference to `T`. Basically, it is a wrapper for a reference that can be stored in a container.

There are few things to note about `std::reference_wrapper`:
- `operator=` will reseat a `std::reference_wrapper` to a different object (change which object is being referenced).
- `std::reference_wrapper<T>` will implicitly convert to `T&`.
- The `get()` member function can be used to get a `T&` to the object being referenced. This is useful when we want to update the value of the object being referenced.

Here is a simple example:
```cpp
#include <array>
#include <functional> // for std::reference_wrapper
#include <iostream>

int main()
{
    int x { 1 };
    int y { 2 };
    int z { 3 };

    std::array<std::reference_wrapper<int>, 3> arr { x, y, z };

    arr[1].get() = 5; // modify the object in array element 1

    std::cout << arr[1] << y << '\n'; // show that we modified arr[1] and y, prints 55

    return 0;
}
```
This will print:
```
55
```
In this example, we define an array of 3 `std::reference_wrapper<int>` objects, and initialize it with `x`, `y`, and `z`. We then modify the object in array element 1 using `arr[1].get() = 5;`, which modifies `y` (the value of the object being referenced) to 5. Finally, we print `arr[1]` and `y`, which both print 5.
When printing `arr[1]`, the compiler will realize it cannot print a `std::reference_wrapper<int>`, so it will use the implicit conversion to `int&` and print the value of `y` (5).

#### `std::ref` and `std::cref`:
Prior to C++17, CTAD (class template argument deduction) didn’t exist, so all template arguments for a class type needed to be listed explicitly. Thus, to create a `std::reference_wrapper<int>`, we needed to use `std::reference_wrapper<int>`, you could do either of these:
```cpp
int x { 5 };

std::reference_wrapper<int> ref1 { x };        // C++11
auto ref2 { std::reference_wrapper<int>{ x }}; // C++11
```
Due to the long name and having to explicitly list the template argument, C++11 introduced `std::ref` and `std::cref` to make the process more convenient. `std::ref` creates a `std::reference_wrapper<T>` from an lvalue, and `std::cref` creates a `std::reference_wrapper<const T>` from an lvalue.
```cpp
int x { 5 };
auto ref { std::ref(x) };   // C++11, deduces to std::reference_wrapper<int>
auto cref { std::cref(x) }; // C++11, deduces to std::reference_wrapper<const int>
```
In this way, we can create a `std::reference_wrapper<int>` from an lvalue without having to explicitly list the template argument.

Of course, now that we have CTAD (from C++17), we can also do this:
```cpp
std::reference_wrapper ref1 { x };        // C++17
auto ref2 { std::reference_wrapper{ x }}; // C++17
```

But still, since `std::ref` and `std::cref` are shorter, they are still widely used to create `std::reference_wrapper` objects.

#### Summary:
- You cannot define an array of references, as references are not objects.
- You can use `std::reference_wrapper` to create an array of references to objects (e.g., `std::array<std::reference_wrapper<int>, 3> arr { x, y, z };`).
- `std::ref` and `std::cref` can be used to create `std::reference_wrapper` objects from lvalues.


---

### S06 - 17.6 `std::array` and enumerations
In the previous chapter, we talked about arrays and enumerations. Now that we are dealing with `constexpr std::array`, we will show a few additional tricks.

#### Using `static_assert` to ensure the proper number of array initializers:
When initializing a `constexpr std::array` using CTAD, the compiler will deduce how long the array should be from the number of initializers provided.  If less initializers are provided than the array size, the array will be shorter than expected, potentially leading to undefined behavior while indexing.
For example:
```cpp
#include <array>
#include <iostream>

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
    constexpr std::array testScores { 78, 94, 66, 77 }; // oops, only 4 values

    std::cout << "Cartman got a score of " << testScores[StudentNames::cartman] << '\n'; // undefined behavior due to invalid index

    return 0;
}
```

Every time the number of initializers in a `constexpr std::array` can be sanity checked, you should use `static_assert` to ensure the proper number of initializers are provided:
```cpp
#include <array>
#include <iostream>

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
    constexpr std::array testScores { 78, 94, 66, 77 };

    // Ensure the number of test scores is the same as the number of students
    static_assert(std::size(testScores) == max_students); // compile error: static_assert condition failed

    std::cout << "Cartman got a score of " << testScores[StudentNames::cartman] << '\n';

    return 0;
}
```
In this way, if you add an enumerator, or change the number of initializers, the compiler will catch the error at compile time.

Additionally, you can also use `static_assert` to ensure multiple arrays have the same sizes (e.g., `static_assert(std::size(testScores) == std::size(testGrades));`).

#### Using `constexpr` arrays for better enumeration input and output:
In a previous chapter we covered a few ways to input and output the names of the enumerators. To do so, we had an helper function that was covnerting an enumerator to a string and vice-versa. These functions had their own set of strings literals (duplicate), and specific logic was needed (e.g., `switch` statement). For example:
```cpp
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
```
As you can see, this is not the best way to do it, as it requires duplicate strings literals (`"cat"`, `"dog"`, `"pig"`, `"whale"`), and specific logic (e.g., `switch` statement).
This is error prone, since if you want to change the enumerator (add or remove one), you need to update the helper functions as well.

To improve this functions, in cases where the value of enumerators starts at 0 and proceed in a sequential manner (most of the cases), we can use an array to hold the name of each enumerator, and use the enumerator value as the index of the array. This allows us to do two things:
- Index the array using the enumerator's value to get the name of that enumerator (enumerator -> index -> name).
- Use a loop to iterate through all of the names, and be able to correlate a name back to the enumerator based on the index (name -> index -> enumerator).

For example:
```cpp
#include <array>
#include <iostream>
#include <string>
#include <string_view>

namespace Color
{
    enum Type
    {
        black,
        red,
        blue,
        max_colors
    };

    // use sv suffix so std::array will infer type as std::string_view
    using namespace std::string_view_literals; // for sv suffix
    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

    // Make sure we've defined strings for all our colors
    static_assert(std::size(colorName) == max_colors);
};

constexpr std::string_view getColorName(Color::Type color)
{
    // We can index the array using the enumerator to get the name of the enumerator
    return Color::colorName[static_cast<std::size_t>(color)];
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout
// The return type and parameter type are references (to prevent copies from being made)!
std::ostream& operator<<(std::ostream& out, Color::Type color)
{
    return out << getColorName(color);
}

// Teach operator>> how to input a Color by name
// We pass color by non-const reference so we can have the function modify its value
std::istream& operator>> (std::istream& in, Color::Type& color)
{
    std::string input {};
    std::getline(in >> std::ws, input);

    // Iterate through the list of names to see if we can find a matching name
    for (std::size_t index=0; index < Color::colorName.size(); ++index)
    {
        if (input == Color::colorName[index])
        {
            // If we found a matching name, we can get the enumerator value based on its index
            color = static_cast<Color::Type>(index);
            return in;
        }
    }

    // We didn't find a match, so input must have been invalid
    // so we will set input stream to fail state
    in.setstate(std::ios_base::failbit);

    // On an extraction failure, operator>> zero-initializes fundamental types
    // Uncomment the following line to make this operator do the same thing
    // color = {};
    return in;
}

int main()
{
    auto shirt{ Color::blue };
    std::cout << "Your shirt is " << shirt << '\n';

    std::cout << "Enter a new color: ";
    std::cin >> shirt;
    if (!std::cin)
        std::cout << "Invalid\n";
    else
        std::cout << "Your shirt is now " << shirt << '\n';

    return 0;
}
```
This will output:
```
Your shirt is blue
Enter a new color: red
Your shirt is now red
```
Here we did multiple things:
- Use an array to hold the name of the enumerators.
- Static assert to ensure the number of names is the same as the number of enumerators.
- Use the enumerator value as the index of the array to get the name of the enumerator (`getColorName`).
- Use the index of the array to get the enumerator value (`operator>>`).
- In boith cases, `static_cast` is used to convert the enumerator value to an index, and vice-versa.

#### Range-based for-loops and enumerations:
From times to times, we could be required to iterate over enumerators of an enumeration. To do so, we could use a normal for loop, but this would require many static casting of the integer `index` to the enumerator type (e.g., `static_cast<Color::Type>(i)`). Here you can see the issue:
```cpp
#include <array>
#include <iostream>
#include <string_view>

namespace Color
{
    enum Type
    {
        black,
        red,
        blue,
        max_colors
    };

    // use sv suffix so std::array will infer type as std::string_view
    using namespace std::string_view_literals; // for sv suffix
    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

    // Make sure we've defined strings for all our colors
    static_assert(std::size(colorName) == max_colors);
};

constexpr std::string_view getColorName(Color::Type color)
{
    return Color::colorName[color];
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout
// The return type and parameter type are references (to prevent copies from being made)!
std::ostream& operator<<(std::ostream& out, Color::Type color)
{
    return out << getColorName(color);
}

int main()
{
    // Use a for loop to iterate through all our colors
    for (int i=0; i < Color::max_colors; ++i )
        std::cout << static_cast<Color::Type>(i) << '\n';

    return 0;
}
```

Unfortunately, range-based for-loops **do not** work with enumerators:
```cpp
#include <array>
#include <iostream>
#include <string_view>

namespace Color
{
    enum Type
    {
        black,
        red,
        blue,
        max_colors
    };

    // use sv suffix so std::array will infer type as std::string_view
    using namespace std::string_view_literals; // for sv suffix
    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };

    // Make sure we've defined strings for all our colors
    static_assert(std::size(colorName) == max_colors);
};

constexpr std::string_view getColorName(Color::Type color)
{
    return Color::colorName[color];
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout
// The return type and parameter type are references (to prevent copies from being made)!
std::ostream& operator<<(std::ostream& out, Color::Type color)
{
    return out << getColorName(color);
}

int main()
{
    for (auto c: Color::Type) // compile error: can't traverse enumeration
        std::cout << c < '\n';

    return 0;
}
```
As you can see, this will cause a compile error while trying to traverse the enumeration.

Tehere are many creative solutions for this issue.

For example, since we can use a range-based for-loop on an array, one of the most straight-forward solutions is to cretae a `constexpr std::array` containing each of our enumerators, and then use a range-based for-loop on that array (NB: this works only if our enumerators have unique values, i.e., they are not repeated):
```cpp
#include <array>
#include <iostream>
#include <string_view>

namespace Color
{
    enum Type
    {
        black,     // 0
        red,       // 1
        blue,      // 2
        max_colors // 3
    };

    using namespace std::string_view_literals; // for sv suffix
    constexpr std::array colorName { "black"sv, "red"sv, "blue"sv };
    static_assert(std::size(colorName) == max_colors);

    constexpr std::array types { black, red, blue }; // A std::array containing all our enumerators
    static_assert(std::size(types) == max_colors);
};

constexpr std::string_view getColorName(Color::Type color)
{
    return Color::colorName[color];
}

// Teach operator<< how to print a Color
// std::ostream is the type of std::cout
// The return type and parameter type are references (to prevent copies from being made)!
std::ostream& operator<<(std::ostream& out, Color::Type color)
{
    return out << getColorName(color);
}

int main()
{
    for (auto c: Color::types) // ok: we can do a range-based for on a std::array
        std::cout << c << '\n';

    return 0;
}
```
This will output:
```
black
red
blue
```
In this example, since the element of `Color::types` are of type `Color::Type`, variable `c` in the range-based for-loop will be deducted as a `Color::Type`, giving us a working solution.

#### Summary:
- When using `constexpr std::array` with enumerators, you can use `static_assert` to ensure the array has the same size as the number of enumerators.
- You can use `constexpr std::array` to facilitate input and output of enumerators.
- You cannot iterate over enumerators using a range-based for-loop.
- To use range-based for-loops with enumerators, you can create a `constexpr std::array` containing all the enumerators, and iterate over that array.


---

### S07 - 17.7 Introduction to C-style arrays
Now that we covered `std::vector` and `std::arrays`, we will complete our coverage of arrays by learning about C-style arrays. As mentioned before, C-style arrays were inherited from C language, and are built-in to the core language of C++ (unlike the rest of the array types, which are standard library container classes). This means that no inclusion of headers is required to use them, and they are available in every C++ program.

#### Declaring a C-style array:
Because they are part of the core language, C-style arrays have their own special declaration syntax. Similar to C, to declare a C-style array, we use square brackets (`[]`) to tell the compiler that we are declaring an array. Inside the brackets, we can optionally provide the length of the array (integral value of type `size_t`). For example, the following definition creates a C-style array variable names `testScore` which containes 30 elements of type `int`:
```cpp
int main()
{
    int testScore[30] {};      // Defines a C-style array named testScore that contains 30 value-initialized int elements (no include required)

//  std::array<int, 30> arr{}; // For comparison, here's a std::array of 30 value-initialized int elements (requires #including <array>)

    return 0;
}
```

The length of C-style arrays must be at least one, differently from `std::array` which can be empty.

#### The array length of a C-style array must be a constant expression:
Similar to `std::array`, when declaring a C-style array, the array length must be a constant expression (i.e., it must be a compile-time constant) of type `size_t`.

#### Subscripting a C-style array:
Just like `std::array`, we can subscript a C-style array using the subscript operator (`operator[]`):
```cpp
#include <iostream>

int main()
{
    int arr[5]; // define an array of 5 int values

    arr[1] = 7; // use subscript operator to index array element 1
    std::cout << arr[1]; // prints 7

    return 0;
}
```

One important difference is that, unlike standard library container classes (which use unsigned indices of type `std::size_t` only), the index of a C-style array can be a value of **any integral type** (signed or unsigned), or an unscoped enumeration. This means that, luckily, C-style arrays are not subject to all of the sign conversion indexing issues that we discussed in the previous chapter.
```cpp
#include <iostream>

int main()
{
    const int arr[] { 9, 8, 7, 6, 5 };

    int s { 2 };
    std::cout << arr[s] << '\n'; // okay to use signed index

    unsigned int u { 2 };
    std::cout << arr[u] << '\n'; // okay to use unsigned index

    return 0;
}
```

As for other arrays instead, `operator[]` does not perform bounds checking, so it is up to the programmer to ensure that the index is within the valid range.

#### Aggregate initialization of a C-style array:
Similar to `std::array`, C-style arrays are aggregates, which means they can be initialized using aggregate initialization (as a reminder, aggregate initialization allows us to directly initialize an array using an initializer list):
```cpp
int main()
{
    int fibonnaci[6] = { 0, 1, 1, 2, 3, 5 }; // copy-list initialization using braced list
    int prime[5] { 2, 3, 5, 7, 11 };         // list initialization using braced list (preferred)

    return 0;
}
```
This performs initialization in sequence, starting from the first element and moving to the last element.

If you do not provide an initializer for a C-style array, the elements will be default initialized. In most cases, this will result in elements being left uninitialized. Because we generally want our elements to be initialized, C-style arrays should be value initialized (using empty braces) when defined with no initializers.
```cpp
int main()
{
    int arr1[5];    // Members default initialized int elements are left uninitialized)
    int arr2[5] {}; // Members value initialized (int elements are zero uninitialized) (preferred)

    return 0;
}
```

In case you provide more initializers than the number of elements in the array, the compiler will error out. If you provide fewer initializers than the number of elements in the array, the remaining elements will be value initialized:
```cpp
int main()
{
    int a[4] { 1, 2, 3, 4, 5 }; // compile error: too many initializers
    int b[4] { 1, 2 };          // arr[2] and arr[3] are value initialized

    return 0;
}
```

One downside of C-style arrays is that the element's type must be explicitly specified (CTAD does not work because C-style arrays are not class templates). Using `auto` to try to deduce the element type does not work either, because the type of the array is not the type of its elements:
```cpp
int main()
{
    auto squares[5] { 1, 4, 9, 16, 25 }; // compile error: can't use type deduction on C-style arrays

    return 0;
}
```

#### Omitted length:
Consider the following example:
```cpp
int main()
{
    const int prime[5] { 2, 3, 5, 7, 11 }; // prime has length 5

    return 0;
}
```
As you may notie, there is some redundancy in this code: the length of the array is specified twice, once in the type and once in the initializer. 

So, in general, when we initialize a C-style array with an initializer list, we can omit the length of the array from the type, and let the compiler deduce it from the initializer list:
```cpp
int main()
{
    const int prime1[5] { 2, 3, 5, 7, 11 }; // prime1 explicitly defined to have length 5
    const int prime2[] { 2, 3, 5, 7, 11 };  // prime2 deduced by compiler to have length 5

    return 0;
}
```

This only works when initializers are explicitly provided for all elements of the array. If you omit some initializers, the compiler will error out:
```cpp
int main()
{
    int bad[] {}; // error: the compiler will deduce this to be a zero-length array, which is disallowed!

    return 0;
}
```

> **Best Practice:** Prefer omitting the length of a C-style array when initializing it with an initializer list (when every element has an initializer).

#### Const and constexpr C-style arrays:
Like `std::array`, C-style arrays can be declared as `const` or `constexpr`, and like other const variables, they must be initialized at the point of declaration, and cannot be modified after initialization:
```cpp
#include <iostream>

namespace ProgramData
{
    constexpr int squares[5] { 1, 4, 9, 16, 25 }; // an array of constexpr int
}

int main()
{
    const int prime[5] { 2, 3, 5, 7, 11 }; // an array of const int
    prime[0] = 17; // compile error: can't change const int

    return 0;
}
```

#### The `sizeof` operator for C-style arrays:
Previously, we used `sizeof()` operator to get the size of an object or types in bytes. If applied to a C-style array, it returns the total size of the array in bytes, not the number of elements in the array:
```cpp
#include <iostream>

int main()
{
    const int prime[] { 2, 3, 5, 7, 11 }; // the compiler will deduce prime to have length 5

    std::cout << sizeof(prime); // prints 20 (assuming 4 byte ints)

    return 0;
}
```
This returns 20, since the array has 5 elements, and each element is 4 bytes in size.

#### Getting the length of a C-style array:
From C++17, we can use `std::size()` (defined in the `<iterator>` header) to get the length of a C-style array, as an unsigned integral value (of type `std::size_t`). In C++20, we can also use `std::ssize()`, which returns the length of the array as a signed integral value (probably of type `std::ptrdiff_t`):
```cpp
#include <iostream>
#include <iterator> // for std::size and std::ssize

int main()
{
    const int prime[] { 2, 3, 5, 7, 11 };   // the compiler will deduce prime to have length 5

    std::cout << std::size(prime) << '\n';  // C++17, returns unsigned integral value 5
    std::cout << std::ssize(prime) << '\n'; // C++20, returns signed integral value 5

    return 0;
}
```
Compared to `sizeof()`, these functions return the number of elements in the array, not the total size of the array in bytes.

#### Getting the length of a C-style array (C++14 or older):
Prior to C++17, there was no standard library function to get the length of a C-style array.

If you’re using C++11 or C++14, you can use this function instead:
```cpp
#include <cstddef> // for std::size_t
#include <iostream>

template <typename T, std::size_t N>
constexpr std::size_t length(const T(&)[N]) noexcept
{
	return N;
}

int main() {

	int array[]{ 1, 1, 2, 3, 5, 8, 13, 21 };
	std::cout << "The array has: " << length(array) << " elements\n";

	return 0;
}
```
This uses a function template that takes a C-style array by reference, and then returns the non-type template parameter representing the length of the array.

In much older codebases, ou may see the length of a C-style array computed dividing the size of the entire array by the size of an element:
```cpp
#include <iostream>

int main()
{
    int array[8] {};
    std::cout << "The array has: " << sizeof(array) / sizeof(array[0]) << " elements\n";

    return 0;
}
```
This prints:
```
The array has: 8 elements
```
since `sizeof(array)` returns the total size of the array in bytes, and `sizeof(array[0])` returns the size of a single element in bytes.

#### C-style arrays does not support assignment:
Perhaps surprisingly, C++ arrays don’t support assignment:
```cpp
int main()
{
    int arr[] { 1, 2, 3 }; // okay: initialization is fine
    arr[0] = 4;            // assignment to individual elements is fine
    arr = { 5, 6, 7 };     // compile error: array assignment not valid

    return 0;
}
```
Technically, this is not possible since assignment requires the left-operand to be a modifiable lvalue, and arrays are not modifiable lvalues, while the single elements are modifiable lvalues. This is why `arr[0] = 4;` is valid, while `arr = { 5, 6, 7 };` is not.

If you need to assign a new list of values to a C-style array, it is better to use a `std::vector` instead. Alternatively, you can assign new values element-by-element, or use `std::copy` to copy an existing C-style array to another C-style array:
```cpp
#include <algorithm> // for std::copy

int main()
{
    int arr[] { 1, 2, 3 };
    int src[] { 5, 6, 7 };

    // Copy src into arr
    std::copy(std::begin(src), std::end(src), std::begin(arr));

    return 0;
}
```

#### Summary:
- C-style arrays are built-in types, and can be declared like this: `type name[length];` or `type name[] { values };`.
- You can subscript an array using the subscript operator `[]`.
- Since C-style arrays are aggregates, you can initialize them using an initializer list (aggregate initialization).
- You can make C-style arrays `const` and `constexpr`.
- To get the length of a C-style array, you can use `std::size()` (C++17) or `std::ssize()` (C++20).
- C-style arrays do not support assignment (you can perform assignment on the single elements of the array, but not on the array itself).


---

### S08 - 17.8 C-style array decay
#### The C-style array passing challenge:
The designers of C language had a problem. Consider this example:
```cpp
#include <iostream>

void print(int val)
{
    std::cout << val;
}

int main()
{
    int x { 5 };
    print(x);

    return 0;
}
```
When `print(x)` is called, the value of arguemnt `x` (`5`) is copied into parameter `val` (`int val`). Here there is no problem, since `int` is a built-in type, and copying an `int` is a simple operation.

Now consider this example:
```cpp
#include <iostream>

void printElementZero(int arr[1000])
{
    std::cout << arr[0]; // print the value of the first element
}

int main()
{
    int x[1000] { 5 };   // define an array with 1000 elements, x[0] is initialized to 5
    printElementZero(x);

    return 0;
}
```
This program also compiles and prints the expected value `5`, but it doesn't work exactly as you may think. This is due to the choice of the C language designers to solve two main problems regarding C-style arrays:
1. Copying a 1000-length array is a very expensive operation, and C doesn't support pass by reference, so it can't pass the array to the function by reference.
2. We would like to have a function that supports arrays of any size (not just 1000-length arrays), and with this implementation, we would need to write a function for every possible array size, since C doesnt't support syntax to specify "any length" arrays, nor supports templates, nor arrays of one lenght can be converted to arrays of another length.

To solve these problems, the C language designers came up with a clever solution (inherited from C++ for compatibility reasons) that solves for both of these issues:
```cpp
#include <iostream>

void printElementZero(int arr[1000]) // doesn't make a copy
{
    std::cout << arr[0]; // print the value of the first element
}

int main()
{
    int x[7] { 5 };      // define an array with 7 elements
    printElementZero(x); // somehow works!

    return 0;
}
```
Somehow, the function `printElementZero` can accept an array of any size (e.g., `int x[7]`), and it doesn't make a copy of the array. 

In this lecture we wil see how this is possible, and why the solution picked from the C language designers is not the best one for modern C++.


But first, we need to cover two subtopics.

#### Array to pointer converions (array decay):
In most cases when a C-style array is used in an expression, the array is implicitly converted to a pointer to the element type, initialized with the address of the first element of the array (e.g., `int arr[7]` is converted to `int*` initialized with the address of `arr[0]`).

Here is a program explaining it:
```cpp
#include <iomanip> // for std::boolalpha
#include <iostream>

int main()
{
    int arr[5]{ 9, 7, 5, 3, 1 }; // our array has elements of type int

    // First, let's prove that arr decays into an int* pointer

    auto ptr{ arr }; // evaluation causes arr to decay, type deduction should deduce type int*
    std::cout << std::boolalpha << (typeid(ptr) == typeid(int*)) << '\n'; // Prints true if the type of ptr is int*

    // Now let's prove that the pointer holds the address of the first element of the array

    std::cout << std::boolalpha << (&arr[0] == ptr) << '\n';

    return 0;
}
```
This program may print:
```
true
true
```
Here, `arr` is decayed into an `int*` pointer, and `ptr` is initialized with the address of the first element of the array, as expected.

Similarily, a const array (e.g., `const int arr[5]{ 9, 7, 5, 3, 1 };`) is decayed into a `const int*` pointer.

But be careful, **arrays are not pointers**. It is a common misconception to think that arrays are pointers, since they decay into pointers in most cases. An array, instead, is a sequence of elements, whereas a pointer object just holds an address.
Moreover, the type information of an array (e.g., `int[5]`) is different than the type information of a pointer (e.g., `int*`). Also, the array type contains information about the length of the array (e.g., `int[5]` has length 5), while the pointer type does not contain information about the length of the array (e.g., `int*` does not contain information about the length of the array).

#### Subscripting a C-style array actually applies `operator[]` to the decayed pointer:
Since a C-style array **decays to a pointer when evaluated**, subscripting a C-style array actually applies `operator[]` to the decayed pointer, not to the array itself. Here is a program explaining it:
```cpp
#include <iostream>

int main()
{
    const int arr[] { 9, 7, 5, 3, 1 };
    std::cout << arr[2]; // subscript decayed array to get element 2, prints 5

    return 0;
}
```
Here, `arr` is decayed into an `int*` pointer, and `arr[2]` is equivalent to `*(arr + 2)`, which prints the value of the third element of the array, as expected.

We can also use `operator[]` directly on a pointer to access elements of the array, if this pointer is holding the address of the first element of the array:
```cpp
#include <iostream>

int main()
{
    const int arr[] { 9, 7, 5, 3, 1 };

    const int* ptr{ arr };  // arr decays into a pointer
    std::cout << ptr[2];    // subscript ptr to get element 2, prints 5

    return 0;
}
```
We will see where this is convenient in the next lecture, going deeper in this topic.

#### Array decay solves our C-style array passing issue:
Array decays solves both issues we presented:
- When passing a C-style array as an argument, the array decays into a pointer, and the pointer holding the address of the first element of the array is what gets passed to the function.
- This allows passing arrays of any size to the function, since the function doesn't need to know the size of the array, it just needs to know the type of the elements (both `int[5]` and `int[7]` decay into `int*`).

In the following example we will illustrate two things:
- We can pass arrays of different lengths to a single function (because both decays into the same pointer type).
- Our function parameter receiving the array can be a (const) pointer of the element type, and it doesn't need to know the size of the array.

```cpp
#include <iostream>

void printElementZero(const int* arr) // pass by const address
{
    std::cout << arr[0];
}

int main()
{
    const int prime[] { 2, 3, 5, 7, 11 };
    const int squares[] { 1, 4, 9, 25, 36, 49, 64, 81 };

    printElementZero(prime);   // prime decays to an const int* pointer
    printElementZero(squares); // squares decays to an const int* pointer

    return 0;
}
```
This will print:
```
2
1
```
Inside `main()`, when we call `printElementZero(prime);`, the array `prime` decays into a `const int*` pointer, and this pointer is passed to the function. The function then prints the first element of the array, which is `2`.
Similarly, when we call `printElementZero(squares);`, the array `squares` decays into a `const int*` pointer, and this pointer is passed to the function. The function then prints the first element of the array, which is `1`.

Because we are actually passing an address to the function, this function has direct access to the array (not just a copy), and it could modify the array if it wanted to. For this reason, it is safer to pass the array as a (const) pointer, and not as a (const) array, when we do not need direct array modification.

> **Best practice:** Pass arrays to functions as (const) pointers, and not as (const) arrays, when we do not need direct array modification.

#### C-style array function parameter syntax:
One issue of defining the function parameter as a (const) pointer (e.g., `int*`) is that it is not obvious that the array is supposed to be a pointer to an array of values, or just a pointer to a single value. For this reason, to explicitly define the function parameter as a pointer to an array of values, it is preferable to use the alternate declaration form (e.g., `int arr[]`) to define the pointer to an array of values:
```cpp
#include <iostream>

void printElementZero(const int arr[]) // treated the same as const int*
{
    std::cout << arr[0];
}

int main()
{
    const int prime[] { 2, 3, 5, 7, 11 };
    const int squares[] { 1, 4, 9, 25, 36, 49, 64, 81 };

    printElementZero(prime);  // prime decays to a pointer
    printElementZero(squares); // squares decays to a pointer

    return 0;
}
```
In this way, the function parameter is explicitly defined as a pointer to an array of values, and it is clear that the array is supposed to be a pointer to an array of values, and not just a pointer to a single value. More importantly, this program is exactly the same as the previous one, as `const int arr[]` is treated the same as `const int*`.

> **Best practice:** A function parameter expecting a C-style array type should use the array syntax (e.g., `int arr[]`) to define the pointer to an array of values, and not the pointer syntax (e.g., `int*`).

The downside to use this syntax is that it makes less obvious that the array is being decayed, and it is actually a pointer to the first element of the array. 

#### The problems with array decay:
Although array decay solves our C-style array passing issue, it also creates other issues, since you lost the information about the size of the array. 

First, `sizeof()` will return different vlaues for arrays and decayed arrays (that are pointers):
```cpp
#include <iostream>

void printArraySize(int arr[])
{
    std::cout << sizeof(arr) << '\n'; // prints 4 (assuming 32-bit addresses)
}

int main()
{
    int arr[]{ 3, 2, 1 };

    std::cout << sizeof(arr) << '\n'; // prints 12 (assuming 4 byte ints)

    printArraySize(arr);

    return 0;
}
```
This will print:
```
12
4
```
This means that using `sizeof()` on a C-style operator is potentially dangerous, since you will have to make sure you are actually applying it to the array, and not to the decayed pointer.

Luckily, C++17's better replacement `std::size()` (and C++20's `std::ssize()`) will fail to compile if passed a pointer, and not an array:
```cpp
#include <iostream>

int printArrayLength(int arr[])
{
    std::cout << std::size(arr) << '\n'; // compile error: std::size() won't work on a pointer
}

int main()
{
    int arr[]{ 3, 2, 1 };

    std::cout << std::size(arr) << '\n'; // prints 3

    printArrayLength(arr);

    return 0;
}
```

Second, and most importantly, array decay can make refactoring (breaking long functions into shorter, more modular functions) more difficult, since you will have to make sure you are not accidentally passing a decayed array to a function that expects an array.

Third, not ahving length information creates several programmatic challenges (sanity checks, bounds checking, etc.). User could easily pass arrays that are shorter than expected to functions that expect arrays of a certain length, which will cause undefined behavior when subscribed with an invalid index:
```cpp
#include <iostream>

void printElement2(int arr[])
{
    // How do we ensure that arr has at least three elements?
    std::cout << arr[2] << '\n';
}

int main()
{
    int a[]{ 3, 2, 1 };
    printElement2(a);  // ok

    int b[]{ 7, 6 };
    printElement2(b);  // compiles but produces undefined behavior

    int c{ 9 };
    printElement2(&c); // compiles but produces undefined behavior

    return 0;
}
```
Not having the array length creates challenges when we want to traverse the array, since we don't know how many elements it has.

In general, there are solutions to these issues, tbut they add complexity and fragility to the code, and make it more error-prone.

#### Working around array length issues:
Historically, programmers have worked around the lack of array length information via one of two methods.

First, we can pass in both the array and the array length as separate arguments:
```cpp
#include <cassert>
#include <iostream>

void printElement2(const int arr[], int length)
{
    assert(length > 2 && "printElement2: Array too short"); // can't static_assert on length

    std::cout << arr[2] << '\n';
}

int main()
{
    constexpr int a[]{ 3, 2, 1 };
    printElement2(a, static_cast<int>(std::size(a)));  // ok

    constexpr int b[]{ 7, 6 };
    printElement2(b, static_cast<int>(std::size(b)));  // will trigger assert

    return 0;
}
```
However, this has a number of issues:
- The caller needs to make sure that the length argument matches the array length.
- Potential sign covnersion issues with `std::size()`, since it returns a `size_t`.
- Runtime asserts only triggers at runtime, not at compile time. If our testing path does not cover all possible array lengths, we will not catch the error at compile time, and potentially shipping a bug to production. In modern C++, we prefer using `static_assert` to catch such errors at compile time, but we cannot with this approach, since function parameters cannot be `constexpr`.
- This method only works if we are making an explicit function call. If the function call is implicit (e.g., calling an operator with the array as an operand), we will not be able to pass the array length as an argument.

As a second option, if there is an element value that is not semantically valid (e.g., a test score of `-1`), we could mark the end of the array with such a value, and then use a loop to traverse the array until we reach such a value. The nice thing about this approach is that it works also for implicit function calls.

But this approach has a number of issues:
- If the terminating element does not exist, we would get undefined behavior.
- Functions that traverse the array need special handling (e.g., we do nott want to print, or do operations, on the last element, since it is the terminating element).
- There is a mismatch between the actual array length and the number of semantically valid elements.
- This works only when such a semantically invalid element exists, which is not always the case.

#### C-style arrays should be avoided in most cases:
Because of the non-standard passing semantics (pass by address is used instead of pass by value) and risks associated with decayed arrays losing their length information, C-style arrays have generally fallen out of favor. We recommend avoiding them as much as possible.

> **Best Practice:** Avoid C-style arrays when practical.

- Prefer `std::string_view` for read-only strings (string literal symbolic constants and string parameters).
- Prefer `std::string` for modifiable strings.
- Prefer `std::array` for non-global constexpr arrays, since it is a fixed-size array that is initialized at compile time.
- Prefer `std::vector` for non-constexpr arrays, since it is a dynamic-size array that is initialized at runtime.

It is okay to use C-style arrays for global constexpr arrays. We’ll discuss this in a moment.

#### So when are C-style arrays used in modern C++?
In modern C++, C-style arrays are typically used in two cases:
- To store constexpr global (or constexpr static local) program data. This is because these arrays can be accessed globally, and we will not pass them to functions, which makes them a good fit for C-style arrays.
- As parameters to function or classes that want to handle non-constexpr C-style string arguments directly, without copying or converting the string.

#### Summary:
- 


---

### S09 - 17.9 Pointer arithmetic and subscripting
In the previous chapter we said that arrays are stored sequentially in memory. Here we will go a bit deeper into how arrays indexing math works exactly. Although we will not use indexing math in future lessons, this topic will give you a clearer vision of how range-based for loops work, and 

#### What is a pointer arithmetic?
**Pointer arithmetic** is a feature that allows us to apply certain integer arithemtic operators (addition, subtraction, increment, decrement) to pointers to produce a *new memory address*.

Specifically, given some pointer `ptr`, `ptr + 1` returns the address of the **next** object in memory (based on the type being pointed). So, for example, if `ptr` is an `int*`, and an `int` is 4 bytes, then `ptr + 1` returns the memory address that is 4 bytes after `ptr`, and `ptr + 2` returns the memory address that is 8 bytes after `ptr`.
```cpp
#include <iostream>

int main()
{
    int x {};
    const int* ptr{ &x }; // assume 4 byte ints

    std::cout << ptr << ' ' << (ptr + 1) << ' ' << (ptr + 2) << '\n';

    return 0;
}
```
This may print (with 4 byte ints):
```
00AFFD80 00AFFD7C 00AFFD78
```

Applying the increment (`++`) and decrement (`--`) operators to a pointer is equivalent to perform addition and subtraction with the pointer (by 1), respectively, but actually modify the address held by the pointer, instead of creating a new pointer.
For example, given some int value `x`, `++x` is equivalent to `x + 1`. In a similar way, given some pointer `ptr`, `++ptr` is equivalent to `ptr + 1`, which does pointer arithemtic and assign the result back to `ptr`.
```cpp
#include <iostream>

int main()
{
    int x {};
    const int* ptr{ &x }; // assume 4 byte ints

    std::cout << ptr << '\n';

    ++ptr; // ptr = ptr + 1
    std::cout << ptr << '\n';

    --ptr; // ptr = ptr - 1
    std::cout << ptr << '\n';

    return 0;
}
```
This may print (with 4 byte ints):
```
00AFFD80 00AFFD84 00AFFD80
```

> **Note:** `++x` and `x++` are different. The first one is a pre-increment (increment happens prior to assignment), while the second one is a post-increment (increment happens after assignment). In other words, with `++x` you first increment the value, and then assign it to the variable. With `x++` you first assign the value to the variable, and then increment it.

#### Subscripting is implemented via pointer arithmetic:
In a prior lesson, we said that `operator[]` can be applied to a pointer:
```cpp
#include <iostream>

int main()
{
    const int arr[] { 9, 7, 5, 3, 1 };

    const int* ptr{ arr }; // a normal pointer holding the address of element 0
    std::cout << ptr[2];   // subscript ptr to get element 2, prints 5

    return 0;
}
```
Now, let us take a deeper look into it.

It turns out that subscript operation `ptr[n]` is equivalent to `*((ptr) + (n))`, where `n` is the index of the element we want to access.

Specifically, in the example above, we first initialize `ptr` with `arr`, that when evaluated decays to a pointer to the first element of `arr` (i.e., the address of the first element of `arr`). Next, when printing `ptr[2]`, this is equivalent to `*((ptr) + (2))`, which returns the address of the third element of `arr`, and then we dereference it (using `*`) to get the value of the third element of `arr`.

Let's have a look at another example:
```cpp
#include <iostream>

int main()
{
    const int arr[] { 3, 2, 1 };

    // First, let's use subscripting to get the address and values of our array elements
    std::cout << &arr[0] << ' ' << &arr[1] << ' ' << &arr[2] << '\n';
    std::cout << arr[0] << ' ' << arr[1] << ' ' << arr[2] << '\n';

    // Now let's do the equivalent using pointer arithmetic
    std::cout << arr<< ' ' << (arr+ 1) << ' ' << (arr+ 2) << '\n';
    std::cout << *arr<< ' ' << *(arr+ 1) << ' ' << *(arr+ 2) << '\n';

    return 0;
}
```
This may print:
```
00AFFD80 00AFFD84 00AFFD88
3 2 1
00AFFD80 00AFFD84 00AFFD88
3 2 1
```
Here you can notice that both addresses and values are the same, since `arr` is a pointer to the first element of `arr`.

#### Pointer arithemtic and subscripting are relative addresses:
It is not always clear that array indices are actuall **relative addresses**. This means that are relative to the address pointed by the pointer, and not to the absolute address of the array. In general, we usually start pointing from the first element of the array, but this is not a requirement. For example, let's say that `ptr` is pointing to the second element of `arr`, then `ptr[1]` is equivalent to `*((ptr) + (1))`, which returns the third element of `arr`, not the second element of `arr`. For example:
```cpp
#include <array>
#include <iostream>

int main()
{
    const int arr[] { 9, 8, 7, 6, 5 };
    const int *ptr { arr }; // arr decays into a pointer to element 0

    // Prove that we're pointing at element 0
    std::cout << *ptr << ptr[0] << '\n'; // prints 99
    // Prove that ptr[1] is element 1
    std::cout << *(ptr+1) << ptr[1] << '\n'; // prints 88

    // Now set ptr to point at element 3
    ptr = &arr[3];

    // Prove that we're pointing at element 3
    std::cout << *ptr << ptr[0] << '\n'; // prints 66
    // Prove that ptr[1] is element 4!
    std::cout << *(ptr+1) << ptr[1] << '\n'; // prints 55

    return 0;
}
```
This may print:
```
9 9
8 8
6 6
5 5
```
However, you can see that this program is way more confusing, and it is generally recommended to start pointing from the first element of the array, always.

> **Best practice:** Always start pointing from the first element of the array, always.

#### Nagtive indices:
In the last lesson, we said that unlike standard library container classses, the index of C-style array can either be an unsigned integer or a signed integer. This is the case because it is actually possible to index a C-style array with a negative index. Here it is why.

We said that `*(ptr + 1)` return the *next object* in memory, and that `ptr[1]` is a conveninent equivalent syntax for it. Previously we also said that `*(ptr - 1)` returns the *previous object* in memory. So it must be possible to index a C-style array with a negative index, and the equivalent syntax is `ptr[-1]`.
```cpp
#include <array>
#include <iostream>

int main()
{
    const int arr[] { 9, 8, 7, 6, 5 };

    // Set ptr to point at element 3
    const int* ptr { &arr[3] };

    // Prove that we're pointing at element 3
    std::cout << *ptr << ptr[0] << '\n'; // prints 66
    // Prove that ptr[-1] is element 2!
    std::cout << *(ptr-1) << ptr[-1] << '\n'; // prints 77

    return 0;
}
```
This may print:
```
6 6
7 7
```
This shows that it is actually possible to index a C-style array with a negative index.

#### Pointer arithemtic can be used to traverse an array:
One of the most common uses of pointer arithemtic is to traverse a C-style array without explicit indexing. The following example shows how to traverse an array using pointer arithemtic:
```cpp
#include <iostream>

int main()
{
	constexpr int arr[]{ 9, 7, 5, 3, 1 };

	const int* begin{ arr };                // begin points to start element
	const int* end{ arr + std::size(arr) }; // end points to one-past-the-end element

	for (; begin != end; ++begin)           // iterate from begin up to (but excluding) end
	{
		std::cout << *begin << ' ';     // dereference our loop variable to get the current element
	}

	return 0;
}
```
This will print:
```
9 7 5 3 1
```

In this example:
- `begin` points to the first element of `arr`
- `end` points to one-past-the-end element of `arr` (i.e., the address of the element after the last element of `arr`)
- loop from the first element of `arr` to the last element of `arr`, since `begin != end` is true as long as `begin` is not pointing at the one-past-the-end element of `arr`
- `++begin` increments `begin` to point at the next element of `arr`
- `*begin` dereferences `begin` to get the value of the element it points at

This is actually correct, since the end condition of the for loop is exclusive (i.e., it stops when `begin` is pointing at the one-past-the-end element of `arr`, and it will exit the loop).

One neat thing about this traversing an array this way is that we can refactor the loop part of the above example into a separate function exactly as written, and it will still work:
```cpp
#include <iostream>

void printArray(const int* begin, const int* end)
{
	for (; begin != end; ++begin)   // iterate from begin up to (but excluding) end
	{
		std::cout << *begin << ' '; // dereference our loop variable to get the current element
	}

	std::cout << '\n';
}

int main()
{
	constexpr int arr[]{ 9, 7, 5, 3, 1 };

	const int* begin{ arr };                // begin points to start element
	const int* end{ arr + std::size(arr) }; // end points to one-past-the-end element

	printArray(begin, end);

	return 0;
}
```
Here you can see that the function `printArray` is a generic function that can be used to print any array (of any size) as long as we pass it the correct `begin` and `end` pointers. This is possible because all the information needed to traverse the array is contained in the `begin` and `end` pointers, since they are continuous in memory.

#### Range-based for loops over C-style arrays are implemented using pointer arithmetic:
Consider the following range-based for loop:
```cpp
#include <iostream>

int main()
{
	constexpr int arr[]{ 9, 7, 5, 3, 1 };

	for (auto e : arr)         // iterate from `begin` up to (but excluding) `end`
	{
		std::cout << e << ' '; // dereference our loop variable to get the current element
	}

	return 0;
}
```
This will print:
```
9 7 5 3 1
```

If you look at the documentation for range-based for loops, you will see that they are usually implemented like this:
```
{
    auto __begin = begin-expr;
    auto __end = end-expr;

    for ( ; __begin != __end; ++__begin)
    {
        range-declaration = *__begin;
        loop-statement;
    }
}
```

Let's implement the range-based for loop with this implementation:
```cpp
#include <iostream>

int main()
{
	constexpr int arr[]{ 9, 7, 5, 3, 1 };

	auto __begin = arr;                // arr is our begin-expr
	auto __end = arr + std::size(arr); // arr + std::size(arr) is our end-expr

	for ( ; __begin != __end; ++__begin)
	{
		auto e = *__begin;         // e is our range-declaration
		std::cout << e << ' ';     // here is our loop-statement
	}

	return 0;
}
```
Note that this is very similar to the example of the previous section. Here we just had to assign `*__begin` to `e` rather than just using `*__begin` directly in the loop statement.

#### Summary:
- Pointer arithmetic allows us to apply certain arithmetics to pointers, such as addition, subtraction, and increment/decrement of the stored address.
- Subscript operator (`ptr[i]`) is implemented via pointer arithemtic, and it is actually equivalent to `*(ptr + i)`.
- These two methods are relative addresses.
- You can index a C-style array with a negative index.
- You can use pointer arithemtic to traverse a C-style array without explicit indexing (e.g., `for (; begin != end; ++begin)`).
- Range-based for loops are implemented using pointer arithemtic.


---
### S10 - 17.10 C-style strings
In chapter 5, we defined a string as a collection of sequential characters (e.g., `"Hello"` is a string of 5 characters: `H`, `e`, `l`, `l`, `o`), and introduced C-style string literals. We also mentioned that C-style string literals like "Hello, world!" has type `const char[14]` (13 characters + null terminator).

Now it is eveident, that C-style string literals are just C-style arrays ehose element type is `char` or `const char`.

In general, we said that in modern C++, we prefer to use `std::string` and `std::string_view` over C-style strings, since they are more flexible and safer to use. C-style strings are still used in some older code, so you should know them to fully understand the code you read.

In this lesson, we will see the most important points regarding C-style string objects in modern C++.

#### Defining C-style strings:
In order to define a C-style string variable, you should simply declare a C-style array variable of type `char` (or `const char` / `constexpr char` if you want to make it immutable):
```cpp
char str1[8]{};                    // an array of 8 char, indices 0 through 7

const char str2[]{ "string" };     // an array of 7 char, indices 0 through 6
constexpr char str3[] { "hello" }; // an array of 6 const char, indices 0 through 5
```
But remember that we will need an extra character for the **null terminator**. So, when defining a C-style string, we recommend to omit the length of the array, and let the compiler deduce it from the initializer loist. In this way, if you change the initializer list, the array size will be automatically adjusted, and you will not risk to forget to update the array size.

#### C-style strings will decay:
Because C-style strings are just C-style arrays of characters, they will decay to pointers to their first element (`const char*` or `char*`) when passed to a function in most of the cases. When this happens, as in the standard case of C-style arrays, the length information of the array is lost.

This loss of length ifnormation is why we have a null terminator at the end of C-style strings. In this way, the length of the string can be (inefficiently) regenerated by traversing the string from the start to the null terminator, and counting the number of characters.

#### Outputting a C-style string:
You can output a C-style string using `std::cout` in the same way you would output a C-style array. `std::cout` outputs characters until it encounters the null terminator, and then it stops. In this way we can output both non-decayed and decayed C-style strings:
```cpp
#include <iostream>

void print(char ptr[])
{
    std::cout << ptr << '\n'; // output string
}

int main()
{
    char str[]{ "string" };
    std::cout << str << '\n'; // outputs string

    print(str);

    return 0;
}
```
If you try to print a string without null terminator, as in this example, the result will be an undefined behavior. In this particular case, the most likely outcome will be that the program will print all characters in `str`, and it will just keep printing everything in adjacent memory slots until it encounters a byte of memory containing `0`, that will be interpreted as a null terminator. This is clearly not we want, and it is why we need to make sure that our C-style strings are null-terminated.

#### Inputting C-style strings:
Consider the case where we are asking the user to roll a die as many times as they wish and enter the numbers rolled without spaces (e.g. `524412616`). In this case, we have no clue about how many characters the user will enter, so, if we want to use a C-style string, we will need to define an array larger than we are ever likely to need:
```cpp
#include <iostream>

int main()
{
    char rolls[255] {}; // declare array large enough to hold 254 characters + null terminator
    std::cout << "Enter your rolls: ";
    std::cin >> rolls;
    std::cout << "You entered: " << rolls << '\n';

    return 0;
}
```
Prior to C++20, `std::cin >> rolls` would extarct as many characters as possible to 'rolls', and stop when it encounters a whitespace (e.g., a space, a newline, or a tab). If the user input was longer than the array, the behavior was undefined, since `std::cin` will keep extracting characters, overflowing the array.

This is also a security issue, since memory beyond the allocated array will be overwritten, and it may contain sensitive data, not protected by the array bounds.

In C++20, `operator>>` was changed so that it only works for inputting **non-decayed** C-style strings. In this way, `operator>>` will only extract as many characters as the C-style string's length allows, preventing overflow and undefined behavior. But unfortunately, this also means that you cannot use `operator>>` to input decayed C-style strings.

The recommended way to read C-style strings using `std::cin` is to use `std::cin.getline`:
```cpp
#include <iostream>
#include <iterator> // for std::size

int main()
{
    char rolls[255] {}; // declare array large enough to hold 254 characters + null terminator
    std::cout << "Enter your rolls: ";
    std::cin.getline(rolls, std::size(rolls));
    std::cout << "You entered: " << rolls << '\n';

    return 0;
}
```
This call to `std::cin.getline()` will read up to 254 characters (inclusing whitespaces) into `rolls`. Any additional characters will be discarded, and the null terminator will be added at the end of the string. Because `std::cin.getline()` get a length parameter, it can prevent overflow. Anyways, if the C-style string is actually deacyes, we have to determine the length of the array in some other ways than using `std::size()`, and proving wrong length to the function, would lead to undefined behavior and security issues.

#### Modifying C-style strings:
As for standard C-style arrays, you can initialize string upon creation, but you cannot assign values to it using the assignment operator after that!
```cpp
char str[]{ "string" }; // ok
str = "rope";           // not ok!
```

Instead, you can use the subscript operator `[]` to change individual characters in the string:
```cpp
#include <iostream>

int main()
{
    char str[]{ "string" };
    std::cout << str << '\n';
    str[1] = 'p';
    std::cout << str << '\n';

    return 0;
}
```
printing:
```
string
sprng
```


#### Getting the length of an C-style string:
As for standard C-style arrays, you can use the `std::size` function (or `std::ssize` in C++20) to get the length of a C-style string. It is important to note two things here:
- This does not work on decayed strings.
- Returns the actual length of the C-style array, not the length of the string (`255` in this case, not `6`).

```cpp
#include <iostream>

int main()
{
    char str[255]{ "string" }; // 6 characters + null terminator
    std::cout << "length = " << std::size(str) << '\n'; // prints length = 255

    char *ptr { str };
    std::cout << "length = " << std::size(ptr) << '\n'; // compile error

    return 0;
}
```

Alternatively, you could use `strlen()` function, which is defined in the `<cstring>` header. This function also works on decayed arrays, returning the length of the string being held, excluding the null terminator:
```cpp
#include <cstring> // for std::strlen
#include <iostream>

int main()
{
    char str[255]{ "string" }; // 6 characters + null terminator
    std::cout << "length = " << std::strlen(str) << '\n'; // prints length = 6

    char *ptr { str };
    std::cout << "length = " << std::strlen(ptr) << '\n';   // prints length = 6

    return 0;
}
```
However, `strlen()` is slow, as it has to traverse the entire array to find the null terminator.

#### Other C-style string manipulating functions:
There are several function inherited from C that can be used to manipulate C-style strings. Some of the most common are:
- `strlen()`: returns the length of a C-style string.
- `strcpy()`, `strncpy()`, `strcpy_s()`: overwrites one C-style string with another.
- `strcat()`, `strncat()`: appends one C-style string to the ned of another one.
- `strcmp()`, `strncmp()`: compares two C-style strings (returns `0` if equal).

Except for `strlen()`, we generally suggest to avoid these functions, as they are not type-safe and can lead to undefined behavior.

> **Best practice:** Avoid using C-style string functions, as they are not type-safe and can lead to undefined behavior.

#### Avoid non-const C-style string objects:
Unless you have a specific, compelling reason to use non-const C-style strings, they are best avoided, as they are awkward to work with and are prone to overruns, which will cause undefined behavior (and are potential security issues).
In the rare case that you do need to work with C-style strings or fixed buffer sizes (e.g. for memory-limited devices), we’d recommend using a well-tested 3rd party fixed-length string library designed for the purpose.

> **Best practice:** Avoid using non-const C-style strings in favour of `std::string` or `std::string_view`.

#### Summary:
- C-style strings are C-style arrays of characters (`char str[]`), terminated by a null character (`\0`).
- C-style strings decay the same way as C-style arrays.
- To input C-style strings, use `std::cin.getline(str, size)`.
- You can modify individual characters in a C-style string using the subscript operator `[]`.
- To get the length of a C-style string, use `std::size` (doesn't work on decayed strings) or `std::strlen` (works on decayed strings).
- Avoid using non-const C-style strings in favour of `std::string` or `std::string_view`.


---

### S11 - 17.11 C-style string symbolic constants
In the previous lesson, we saw how to cretae and initialize C-style string objects:
```cpp
#include <iostream>

int main()
{
    char name[]{ "Alex" }; // C-style string
    std::cout << name << '\n';

    return 0;
}
```

C++ supports two different way to create C-style string symbolic constants:
```cpp
#include <iostream>

int main()
{
    const char name[] { "Alex" };        // case 1: const C-style string initialized with C-style string literal
    const char* const color{ "Orange" }; // case 2: const pointer to C-style string literal

    std::cout << name << ' ' << color << '\n';

    return 0;
}
```
This prints:
```
Alex Orange
```

Specifically:
1. `const char name[] { "Alex" };` `Alex"` is put into a (probably) read-only memory location (copying). Then the program allocates memory for a C-style array of length 5 (4 characters + null terminator) and initialize the memory with the string `Alex"` (copying). So, at the end, we have 2 copies of the string `Alex"`: one in global memory, and the other owned by `name`. Since `name` is a `const`, and it will, be never modified, making a copy is inefficient. 
2. `const char* const color{ "Orange" };` How the compiler handles this is implemnetation-defined. *Usually*, the compiler places the string `Orange` into a (probably) read-only memory location (copying). Then it initialize the pointer with the address of the string (no copying, just a pointer to the address of the string).

For optimization purposes, multiple string literals may be consolidated into a single value. For example:
```cpp
const char* name1{ "Alex" };
const char* name2{ "Alex" };
```
here there are two string literals with the same value (`"Alex"`). Since these are constants, the compiler may optimize to save memory by combining these two into a single shared string literal, with both `name1` and `name2` pointing to the same memory location.

#### Try deduction with const C-style strings:
Type dduction with C-style string is quite strightforward:
```cpp
auto s1{ "Alex" };  // type deduced as const char*
auto* s2{ "Alex" }; // type deduced as const char*
auto& s3{ "Alex" }; // type deduced as const char(&)[5]
```

#### Outputting pointers and C-style strings:
`std::cout` handles pointers of different types in an interesting way. Consider this example:
```cpp
#include <iostream>

int main()
{
    int narr[]{ 9, 7, 5, 3, 1 };
    char carr[]{ "Hello!" };
    const char* ptr{ "Alex" };

    std::cout << narr << '\n'; // narr will decay to type int*
    std::cout << carr << '\n'; // carr will decay to type char*
    std::cout << ptr << '\n'; // name is already type char*

    return 0;
}
```
This could print:
```
003AF738
Hello!
Alex
```
Why the `int` array didn't print the array's contents, while both `char` arrays did?

The answer is that the output stream (e.g., `std::cout`) makes some assumptions about your intent based on the operand type:
- If you pass a **non-char** pointer: it will simply print the content of that pointer (the address that the pointer is holding).
- If you pass a **char** pointer (`char*` or `const char*`): it will assume you want to print the a string, and it will print the string being pointed to, instead of simply the address.

While this is desired most of the time, it can lead to unexpected results. Consider the following case:
```cpp
#include <iostream>

int main()
{
    char c{ 'Q' };
    std::cout << &c;

    return 0;
}
```
In this case, the programmer would like to print the address of the character `c`. However, `&c` has type `char*`, and `std::cout` will try to print the string being pointed to, but since this has no null terminator, it will print undefined behavior. This is a plausible output you could get:
```
Q╠╠╠╠╜╡4;¿■A
```

Let us understand better why this happens. `&c` has type `char*`, and it is a C-style array. So, `std::cout` will print the content of the string, and not the address (as done for non-`char` arrays). The program will first print `Q` (correct content of the array), but then, since there is no null terminator, it will keep printing the content of subsequent memory locations until it finds a `0` value, that is interpreted as a null terminator, and it will stop printing.

If you actually want to print the address of a `char` pointer, and not the string it points to, you can `static_cast` it to type `const void*`:
```cpp
#include <iostream>

int main()
{
    const char* ptr{ "Alex" };

    std::cout << ptr << '\n';                           // print ptr as C-style string
    std::cout << static_cast<const void*>(ptr) << '\n'; // print address held by ptr

    return 0;
}
```
In this way, since the operand of `std::cout` is no more of type `char*`, `std::cout` will not do assumption done for `char*` operands, and it will print the address held by the pointer.

#### Favor `std::string_view` for C-style string symbolic constants:
There is little reason to use C-style string symbolic constants in modern C++. Instead, favor `constexpr std::string_view` objects, which tend to be as fast (if not faster) and behave more consistently than C-style strings.

> **Best practice:** Avoid using C-style symbolic constants in favour of `constexpr std::string_view`.

#### Summary:
- C++ supports two different ways to create C-style string symbolic constants:
    1. `const char name[] { "Alex" };` (2 copies, less efficient)
    2. `const char* const color{ "Orange" };` (1 copy, more efficient, since `color` is a pointer to a string literal)
- Type deduction can be used to create C-style string symbolic constants: `auto s1{ "Alex" };`
- Outputting pointers and C-style strings can be tricky, since `std::cout` makes some assumptions based on the operand type:
    - If you pass a **non-char** pointer: it will simply print the content of that pointer (the address that the pointer is holding).
    - If you pass a **char** pointer (`char*` or `const char*`): it will assume you want to print the a string, and it will print the string being pointed to, instead of simply the address.
- To print the address held by a `char` pointer, you can `static_cast` it to type `const void*` (`std::cout << static_cast<const void*>(ptr) << '\n';`)
- Avoid using C-style string symbolic constants in modern C++ in favor of `constexpr std::string_view` objects.


---

### S12 - 17.12 Multidimensional C-style arrays
Consider a game like [tic-tac-toe](https://en.wikipedia.org/wiki/Tic-tac-toe). The standard board is a 3x3 grid, with players placing a mark (X or O) in each cell. The first player to get three of their marks in a row wins. 

With the knowledge you have so far, you could store the board as a 1D array of 9 elements:
```cpp
int ttt[9]; // a C-style array of ints (value 0 = empty, 1 = player 1, 2 = player 2)
```
This will define a C-style array with 9 sequential elements, each of type `int`. We can imagine this like:
```
// ttt[0] ttt[1] ttt[2] ttt[3] ttt[4] ttt[5] ttt[6] ttt[7] ttt[8]
```

The **dimension** of an array is the *number of indices needed to select a single element*. An array having only one signle dimension, like `ttt`, is called **single-dimension array** or **one-dimensional array** (1D array).

However, you immediately notice that this is not the best way to represent the board, as it is not clear which element is in which row and column. A more natural way to represent the board would be to use a 2D array, with 3 rows and 3 columns.

#### Two-dimensional arrays:
Previously, we mentioned that the elements of an array can be of **any type**. This means elements of an array can be arrays themselves. The definition is quite simple: 
```cpp
int a[3][5]; // a 3-element array of 5-element arrays of int
```
This will define a C-style array with 3 elements, each of which is a C-style array of 5 elements of type `int`. We can imagine this 3x5 array like:
```
// col 0    col 1    col 2    col 3    col 4
// a[0][0]  a[0][1]  a[0][2]  a[0][3]  a[0][4]  row 0
// a[1][0]  a[1][1]  a[1][2]  a[1][3]  a[1][4]  row 1
// a[2][0]  a[2][1]  a[2][2]  a[2][3]  a[2][4]  row 2
```

To access a single element, you can use the following syntax:
```cpp
a[2][3] = 7; // a[row][col], where row = 2 and col = 3
```

Thus, for our tic-tac-toe example, we can define a board as a 2D array (`int ttt[3][3];`).

#### Multidimensional arrays:
Arrays with more than one dimension are called **multidimensional arrays**. 

C++ supports multidimensional arrays of more than 2 dimension (e.g., `int threedee[3][3][3];`). For example, the terrain in minecraft is divided into 16x16x16 blocks (called chunk sections).

Arrays of more than 3 dimensions are also supported, but they are rare.

#### How 2d arrays are laid out in memory:
Memory is **linear** (i.e., it is a sequence of 1D bytes), so multidimensional arrays are actually stored as a sequencial list of elements.

For example, this array:
```cpp
// col 0   col 1   col 2   col 3   col 4
// [0][0]  [0][1]  [0][2]  [0][3]  [0][4]  row 0
// [1][0]  [1][1]  [1][2]  [1][3]  [1][4]  row 1
// [2][0]  [2][1]  [2][2]  [2][3]  [2][4]  row 2
```
can be stored into two different ways:
1. **Row-major order (C++, common):** elements are sequentially stored in memory row by row, ordered from left to right, top to bottom:
    ```
    [0][0] [0][1] [0][2] [0][3] [0][4] [1][0] [1][1] [1][2] [1][3] [1][4] [2][0] [2][1] [2][2] [2][3] [2][4]
    ```
2. **Column-major order (Fortran):** elements are sequentially stored in memory column by column, ordered from top to bottom, left to right:
    ```
    [0][0] [1][0] [2][0] [0][1] [1][1] [2][1] [0][2] [1][2] [2][2] [0][3] [1][3] [2][3] [0][4] [1][4] [2][4]
    ```

In C++, when initializing an array, elements are initialized in row-major order. And when traversing an array, it is most efficient to access elements in the order they are laid out in memory.

#### Initializing two-dimensional arrays:
When initializing a 2D array, it is easiest to use **nested brackets**, with each set of numbers representing a row of the array:
```cpp
int array[3][5]
{
  { 1, 2, 3, 4, 5 },     // row 0
  { 6, 7, 8, 9, 10 },    // row 1
  { 11, 12, 13, 14, 15 } // row 2
};
```
Although some compiler will let you omit the inner brackets, it is a good practice to include them for clarity.

When using inner braces, missing initializers will be **value-initialized** (i.e., initialized to 0 for integrals, to `nullptr` for pointers, etc.):
```cpp
int array[3][5]
{
  { 1, 2 },          // row 0 = 1, 2, 0, 0, 0
  { 6, 7, 8 },       // row 1 = 6, 7, 8, 0, 0
  { 11, 12, 13, 14 } // row 2 = 11, 12, 13, 14, 0
};
```

An initialized multidimensional array can omit (only) the leftmost length specification:
```cpp
int array[][5]
{
  { 1, 2, 3, 4, 5 },
  { 6, 7, 8, 9, 10 },
  { 11, 12, 13, 14, 15 }
};
```
In this case, the compiler can infer the number of rows from the initialization list.

Omitting non-leftmost length specifications is not allowed:
```cpp
int array[][]
{
  { 1, 2, 3, 4 },
  { 5, 6, 7, 8 }
};
```

Like normal arrays, multidimensional arrays can be initialized to 0 as follows (using list initialization):
```cpp
int array[3][5] {};
```

#### Two-dimensional arrays and loops:
With a one-dimensional array, we can use a single loop to iterate through all of the elements in the array:
```cpp
#include <iostream>

int main()
{
    int arr[] { 1, 2, 3, 4, 5 };

    // for-loop with index
    for (std::size_t i{0}; i < std::size(arr); ++i)
        std::cout << arr[i] << ' ';

    std::cout << '\n';

    // range-based for-loop
    for (auto e: arr)
        std::cout << e << ' ';

    std::cout << '\n';

    return 0;
}
```

With a two-dimensional array, we will need two nested loops to iterate through all of the elements in the array, and since C++ uses row-major order, the outer loop will iterate through the rows and the inner loop will iterate through the columns:
```cpp
#include <iostream>

int main()
{
    int arr[3][4] {
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }};

    // double for-loop with indices
    for (std::size_t row{0}; row < std::size(arr); ++row) // std::size(arr) returns the number of rows
    {
        for (std::size_t col{0}; col < std::size(arr[0]); ++col) // std::size(arr[0]) returns the number of columns
            std::cout << arr[row][col] << ' ';

        std::cout << '\n';
    }

    // double range-based for-loop
    for (const auto& arow: arr)   // get each array row
    {
        for (const auto& e: arow) // get each element of the row
            std::cout << e << ' ';

        std::cout << '\n';
    }

    return 0;
}
```
In this case, `std::size(arr)` returns the number of rows, and `std::size(arr[0])` returns the number of columns.

#### A two-dimensional array example:
Let us have a look at a more practical example of a two-dimensional array: 
```cpp
#include <iostream>

int main()
{
    constexpr int numRows{ 10 };
    constexpr int numCols{ 10 };

    // Declare a 10x10 array (C-style)
    int product[numRows][numCols]{};

    // Calculate a multiplication table
    // We don't need to calc row and col 0 since mult by 0 always is 0
    for (std::size_t row{ 1 }; row < numRows; ++row)
    {
        for (std::size_t col{ 1 }; col < numCols; ++col)
        {
            product[row][col] = static_cast<int>(row * col);
        }
     }

    for (std::size_t row{ 1 }; row < numRows; ++row)
    {
        for (std::size_t col{ 1 }; col < numCols; ++col)
        {
            std::cout << product[row][col] << '\t';
        }

        std::cout << '\n';
     }


    return 0;
}
```
This program computes and prints a multiplication table for all values between 1 and 9 (inclusive). When printing the table, we avoid printing the first row and column, since they are just `0`s. 
Moreover, here you can see how `\t` (horizontal tab) is used to print the table in a more readable way. This character is used to print a tab (i.e., a horizontal space) between the elements of the table.

The output of this program is the following:
```
1    2    3    4    5    6    7    8    9
2    4    6    8    10   12   14   16   18
3    6    9    12   15   18   21   24   27
4    8    12   16   20   24   28   32   36
5    10   15   20   25   30   35   40   45
6    12   18   24   30   36   42   48   54
7    14   21   28   35   42   49   56   63
8    16   24   32   40   48   56   64   72
9    18   27   36   45   54   63   72   81
```

#### Cartesian coordinates versus array indices:
In geometry, cartesian coordinates are often used to represent a 2D geometric space. This representation has two axis ("x" and "y"). The "x' axis is the horizontal one, while the "y" axis is the vertical one. The origin (i.e., the point where the two axis intersect) is at (0, 0). In two diemnsions, the cartesian position of an object can be represented by a pair of coordinates `{ x, y }`.

Now, take a lok at this 2D array layout in C++:
```cpp
// col 0   col 1   col 2   col 3   col 4
// [0][0]  [0][1]  [0][2]  [0][3]  [0][4]  row 0
// [1][0]  [1][1]  [1][2]  [1][3]  [1][4]  row 1
// [2][0]  [2][1]  [2][2]  [2][3]  [2][4]  row 2
```
This also can represent a 2D geometric space, where an element can be described as `[row][column]`.

While the two disjoint are quite easy to understand, converting from cartesian coordinates `{ x, y }` to array indices `[row][column]` is a bit counter-intuitive. 

The key aspect to get is that the x-coordinate in a cartesian system describes which *columns* is being selected in the array indexing system (i.e., the inner loop), while the y-coordinate describes which *row* is being selected (i.e., the outer loop). Therefore, an `{ x, y }` cartesian coordinate translates to an `[y][x]` array coordinate.

This leads to this C++ implementation, where we switch `x` and `y` in the array indices:
```cpp
for (std::size_t y{0}; y < std::size(arr); ++y) // outer loop is rows / y
{
    for (std::size_t x{0}; x < std::size(arr[0]); ++x) // inner loop is columns / x
        std::cout << arr[y][x] << ' '; // index with y (row) first, then x (col)
}
```

#### Summary:
- You can define and create arrays with more than one dimension (e.g., 2D arrays), with this syntax (2D example): `type arrayName[rowSize][colSize]`.
- To initialize a multidimensional array, you can use list initialization (e.g., `int array[rowSize][colSize] { { ... }, { ... }, ... };`). Try to always specify the inner brackets, to avoid any confusion and readability issues.
- Elements not specified in the initialization list will be initialized to 0 (if the array is of a numeric type).
- You can omit (only) the leftmost dimension size, as the compiler can infer it from the initialization list (e.g., `int array[][colSize] { { ... }, { ... }, ... };`).
- To iterate over a multidimensional array, you can use nested loops (e.g., for 2D arrays: `for (std::size_t row{0}; row < std::size(arr); ++row) { for (std::size_t col{0}; col < std::size(arr[0]); ++col) { ... } }`).
- To convert from cartesian coordinates `{ x, y }` to array indices `[row][column]`, you need to switch `x` and `y` in the array indices (i.e., `[y][x]`).


---

### S13 - 17.13 Multidimensional `std::array`
In the previous lesson, we talked about multidimensional C-style arrays, how to define and initialize them, and how to iterate over them:
```cpp
// C-style 2d array
int arr[3][4] {
    { 1, 2, 3, 4 },
    { 5, 6, 7, 8 },
    { 9, 10, 11, 12 }};
```

But in modern C++, **we generally want to avoid C-style arrays**, unless they are used to store global data.

In this lesson instead, we will go over multidimensional arrays implemented with `std::array`.

#### There is no standard library multidimensional array class:
You should initially note that `std::array` is implemented a s single-dimensional array. So, you should first ask yourself if there exist a standard library class for multidimensional arrays.

Unfortunately, the answer in this case is negative. No such class exists :(.

#### A two-dimensional `std::array`:
The common way to create two-dimensional array of `std::array` is to create an array of `std::array`s. In C++, this means creating a `std::array` where the template type argument is another `std::array`. This is the syntax:
```cpp
std::array<std::array<int, 4>, 3> arr {{  // note double braces
    { 1, 2, 3, 4 },
    { 5, 6, 7, 8 },
    { 9, 10, 11, 12 }}};
```

There are some things that you should know about this:
- When initializing a multidimensional `std::array`, you should use double-brackets (e.g., `std::array<std::array<int, 4>, 3> arr {{ ... }};`).
- This syntax is verbose and hard to read.
- Because of the way templates get nested, the array dimension are switched in the initialization list (e.g., `std::array<std::array<int, 4>, 3>`, instead of a C-style array version `arr[3][4]`).

Indexing this object instead is the same as usual:
```cpp
std::cout << arr[1][2]; // print the element in row 1, column 2
```

We can also pass a two-dimensional `std::array` to a function just like a one-dimensional one:
```cpp
#include <array>
#include <iostream>

template <typename T, std::size_t Row, std::size_t Col>
void printArray(const std::array<std::array<T, Col>, Row> &arr)
{
    for (const auto& arow: arr)   // get each array row
    {
        for (const auto& e: arow) // get each element of the row
            std::cout << e << ' ';

        std::cout << '\n';
    }
}

int main()
{
    std::array<std::array<int, 4>, 3>  arr {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }}};

    printArray(arr);

    return 0;
}
```
But you can see how verbose it is for just a two-dimensional array. Imagine how bad it would be for a three-dimensional one!

#### Making 2D `std::array` easier using an alias template:
In a previous chapter, we introduced type aliases using `using` and `typedef`. We said that one of the use of type aliases is to make complex types easier to use.

However, with a normal type alias, we must explicitly specify all template arguments like this:
```cpp
using Array2dint34 = std::array<std::array<int, 4>, 3>;
```
You can see yourself, that this is not very convenient, as we will need one such alias for each different dimension size.

This is. aperfet occasion to use **alias templates**, which let us specify the element type, row length, and column length for a type alias as template arguments:
```cpp
// An alias template for a two-dimensional std::array
template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;
```
Here you can see that to define an alias template, we first define a template parameter list, then we use the `using` keyword to define the alias, and finally we specify the template arguments for the type we are aliasing.

We can then use, for example, `Array2d<int, 3, 4>` to define a two-dimensional array of `int` with 3 rows and 4 columns (3x4).

Here is a full example:
```cpp
#include <array>
#include <iostream>

// An alias template for a two-dimensional std::array
template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;

// When using Array2d as a function parameter, we need to respecify the template parameters
template <typename T, std::size_t Row, std::size_t Col>
void printArray(const Array2d<T, Row, Col> &arr)
{
    for (const auto& arow: arr)   // get each array row
    {
        for (const auto& e: arow) // get each element of the row
            std::cout << e << ' ';

        std::cout << '\n';
    }
}

int main()
{
    // Define a two-dimensional array of int with 3 rows and 4 columns
    Array2d<int, 3, 4> arr {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }}};

    printArray(arr);

    return 0;
}
```
It is eveident how this is way more concise and easy to use than the previous version. Here, we typically follow `std::array` parameters order, where we first specify the type, then the row length, and finally the column length.

This is easily extendable to higher dimensions, as we can define an alias template for a three-dimensional array as follows:
```cpp
// An alias template for a three-dimensional std::array
template <typename T, std::size_t Row, std::size_t Col, std::size_t Depth>
using Array3d = std::array<std::array<std::array<T, Depth>, Col>, Row>;
```

#### Getting the dimensional lengths of a two-dimensional `std::array`:
With one-dimensional array, we can use `size()` member function (or `std::size()`) to get the length of the array. With have more than one dimension, `size()` will only return the length of the first dimension!

One appealing, but dangerous, solution would be to call `size()` on each dimension array (`arr.size()`, `arr[0].size()`, `arr[0][0].size()`, etc.):
```cpp
#include <array>
#include <iostream>

// An alias template for a two-dimensional std::array
template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;

int main()
{
    // Define a two-dimensional array of int with 3 rows and 4 columns
    Array2d<int, 3, 4> arr {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }}};

    std::cout << "Rows: " << arr.size() << '\n';    // get length of first dimension (rows)
    std::cout << "Cols: " << arr[0].size() << '\n'; // get length of second dimension (cols), undefined behavior if length of first dimension is zero!

    return 0;
}
```
Here:
- `arr.size()` returns the length of the first dimension (rows)
- `arr[0].size()` returns the length of the second dimension (columns)
- In case of 3D arrays, `arr[0][0].size()` would return the length of the third dimension (depth)

The problem is that this is undefined behavior if the length of the first dimension is zero!

A better solution would be to use a function template to return the length of the dimension directly from the associated non-type template parameter:
```cpp
#include <array>
#include <iostream>

// An alias template for a two-dimensional std::array
template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;

// Fetch the number of rows from the Row non-type template parameter
template <typename T, std::size_t Row, std::size_t Col>
constexpr int rowLength(const Array2d<T, Row, Col>&) // you can return std::size_t if you prefer
{
    return Row;
}

// Fetch the number of cols from the Col non-type template parameter
template <typename T, std::size_t Row, std::size_t Col>
constexpr int colLength(const Array2d<T, Row, Col>&) // you can return std::size_t if you prefer
{
    return Col;
}

int main()
{
    // Define a two-dimensional array of int with 3 rows and 4 columns
    Array2d<int, 3, 4> arr {{
        { 1, 2, 3, 4 },
        { 5, 6, 7, 8 },
        { 9, 10, 11, 12 }}};

    std::cout << "Rows: " << rowLength(arr) << '\n'; // get length of first dimension (rows)
    std::cout << "Cols: " << colLength(arr) << '\n'; // get length of second dimension (cols)

    return 0;
}
```
This approach uses the type information of the array directly, instead of using the actual data of the array to compute the length of the dimension. This also, avoid undefined behavior, since if the length of the first dimension is zero, the function will still return the correct value. This also allow us to return the value as an `int` if we desire, without using explicit `static_cast`, since it is converting from a `constexpr std::size_t` to `constexpr int` (non-narrowing).

#### Flatting a two-dimensional array:
Arrays with two or more dimensions have some challanges:
- They rae more verbose to define and work with.
- It is painful to get the length of dimensions greater than the first one.
- They are incrisingly hard to iterate over (one more loop for each added dimension).

One solution to make multidimensional arrays easier to work with is to flatten them into a one-dimensional array. **Flattening** an array is a process of reducing the dimensionality of an array (often to one dimension) while preserving the data and its relativ order.

For example, instead of creating a 2D array with `Row` and `Col` dimensions, we can create a 1D array with `Row * Col` elements, and use the row and column indices to access the elements in the flattened array. However, because the data is stored in a linear fashion, we need to convert the 2D indices to a 1D index, and we can handle this conversion with a specific interface, so that we can treat the flattened array as a 2D array.

This interface will accepts two-dimensional coordinates (`Row` and `Col`), and will returned the mapped unique index in the flattened one-dimensional array.

The conversion works as follows:
- `Row` is the index of the row in the 2D array
- `Col` is the index of the column in the 2D array
- The unique index in the flattened array is computed as `row * Col + col`, where:
    - `row` is the index of the row in the 2D array
    - `col` is the index of the column in the 2D array
    - `Col` is the number of columns in the 2D array

Here the C++ code:
```cpp
#include <array>
#include <iostream>
#include <functional>

// An alias template to allow us to define a one-dimensional std::array using two dimensions
template <typename T, std::size_t Row, std::size_t Col>
using ArrayFlat2d = std::array<T, Row * Col>;

// A modifiable view that allows us to work with an ArrayFlat2d using two dimensions
// This is a view, so the ArrayFlat2d being viewed must stay in scope
template <typename T, std::size_t Row, std::size_t Col>
class ArrayView2d
{
private:
    // You might be tempted to make m_arr a reference to an ArrayFlat2d,
    // but this makes the view non-copy-assignable since references can't be reseated.
    // Using std::reference_wrapper gives us reference semantics and copy assignability.
    std::reference_wrapper<ArrayFlat2d<T, Row, Col>> m_arr {};

public:
    ArrayView2d(ArrayFlat2d<T, Row, Col> &arr)
        : m_arr { arr }
    {}

    // Get element via single subscript (using operator[])
    T& operator[](int i) { return m_arr.get()[static_cast<std::size_t>(i)]; }
    const T& operator[](int i) const { return m_arr.get()[static_cast<std::size_t>(i)]; }

    // Get element via 2d subscript (using operator(), since operator[] doesn't support multiple dimensions prior to C++23)
    T& operator()(int row, int col) { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }
    const T& operator()(int row, int col) const { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }

    // in C++23, you can uncomment these since multidimensional operator[] is supported
//    T& operator[](int row, int col) { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }
//    const T& operator[](int row, int col) const { return m_arr.get()[static_cast<std::size_t>(row * cols() + col)]; }

    int rows() const { return static_cast<int>(Row); }
    int cols() const { return static_cast<int>(Col); }
    int length() const { return static_cast<int>(Row * Col); }
};

int main()
{
    // Define a one-dimensional std::array of int (with 3 rows and 4 columns)
    ArrayFlat2d<int, 3, 4> arr {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12 };

    // Define a two-dimensional view into our one-dimensional array
    ArrayView2d<int, 3, 4> arrView { arr };

    // print array dimensions
    std::cout << "Rows: " << arrView.rows() << '\n';
    std::cout << "Cols: " << arrView.cols() << '\n';

    // print array using a single dimension
    for (int i=0; i < arrView.length(); ++i)
        std::cout << arrView[i] << ' ';

    std::cout << '\n';

    // print array using two dimensions
    for (int row=0; row < arrView.rows(); ++row)
    {
        for (int col=0; col < arrView.cols(); ++col)
            std::cout << arrView(row, col) << ' ';
        std::cout << '\n';
    }

    std::cout << '\n';

    return 0;
}
```
This prints:
```
Rows: 3
Cols: 4
1 2 3 4 5 6 7 8 9 10 11 12
1 2 3 4
5 6 7 8
9 10 11 12
```

Because `operator[]` can only accept a single subscript prior to C++23, there are two alternative approaches:
- Use `operator()`, which can accept multiple subscripts. In this way you can use `[]` for a single index, and `()` for multiple indices. This is the approach used in the example above.
- Have `operator[]` return a subview that also overloads `operator[]` to accept a second subscript. This is more complex, and it doesn't scale well to higher dimensions.

In C++23, `operator[]` was extended to accept multiple subscripts, so you can overload it to handle single and multiple subscripts.

#### `std::mdspan` (C++23):
In C++23, `std::mdspan` has been introduced as a modifiable view that provides a multidimensional array interface for contiguous sequence of elements. By 8modifiable view*, we means that `std::mdspan` is not just a read-only view (like `std::string_view`), but it also allows to modify the elements it views, if they are non-`const`.

The following example prints the same output as the previous one, but uses `std::mdspan` instead of the custom `ArrayView2d` class:
```cpp
#include <array>
#include <iostream>
#include <mdspan>

// An alias template to allow us to define a one-dimensional std::array using two dimensions
template <typename T, std::size_t Row, std::size_t Col>
using ArrayFlat2d = std::array<T, Row * Col>;

int main()
{
    // Define a one-dimensional std::array of int (with 3 rows and 4 columns)
    ArrayFlat2d<int, 3, 4> arr {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12 };

    // Define a two-dimensional span into our one-dimensional array
    // We must pass std::mdspan a pointer to the sequence of elements
    // which we can do via the data() member function of std::array or std::vector
    std::mdspan mdView { arr.data(), 3, 4 };

    // print array dimensions
    // std::mdspan calls these extents
    std::size_t rows { mdView.extents().extent(0) };
    std::size_t cols { mdView.extents().extent(1) };
    std::cout << "Rows: " << rows << '\n';
    std::cout << "Cols: " << cols << '\n';

    // print array in 1d
    // The data_handle() member gives us a pointer to the sequence of elements
    // which we can then index
    for (std::size_t i=0; i < mdView.size(); ++i)
        std::cout << mdView.data_handle()[i] << ' ';
    std::cout << '\n';

    // print array in 2d
    // We use multidimensional [] to access elements
    for (std::size_t row=0; row < rows; ++row)
    {
        for (std::size_t col=0; col < cols; ++col)
            std::cout << mdView[row, col] << ' ';
        std::cout << '\n';
    }
    std::cout << '\n';

    return 0;
}
```
This should be fairly straightforward, but there are a few things worth noting:
- `std::mdspan` let us define a view with as many dimensions as we want, not just 2.
- The first parameter to the constructor of `std::mdspan` should be a pointer to the array data. This can be a decayed C-style array, or we can use `data()` member function of `std::array` or `std::vector` to get a pointer to the array data.
- To index a `std::mdspan` in one-dimension, we must fetch the pointer to the array data (doing `mdView.data_handle()`), and then index it as a regular C-style array.
- To index a `std::mdspan` in multiple dimensions, we can use the multidimensional subscript operator `[]` with more than one subscript (since C++23 allows it).

Note that C++26 will include `std::mdarray`, which combines `std::array` and `std::mdspan` into owning multidimensional arrays. Pretty cool, right?

#### Summary:
- There is no standard library for multidimensional arrays (until now).
- To define a two-dimension array, you can do like this: `std::array<std::array<T, cols>, rows>`.
- To make the readability better, you can use alias templates (`template <typename T, std::size_t Row, std::size_t Col>` and `using Array2d = std::array<std::array<T, Col>, Row>`). You can then define a 2D array like this: `Array2d<int, 3, 4> arr { ... }`.
- To get the dimension of a multidimensional array, you make use of the template parameters.
- To make the handling of multidimensional arrays easier, you can flatten them into a one-dimensional array and provide an interface to access the elements in a multidimensional way (`1d_index = row * n_cols + col`).
- To make the handling of multidimensional arrays even easier, you can use `std::mdspan` (C++23), that provides a modifiable view to multidimensional arrays.


---

### SX - 17.x Summary and quiz
As always, have a look at the original summary, and good luck for the quizzes!

PS: solutions are inside `exercises/sx-questions` folder. Enjoy :)


---

## 🧭 Summary
### 1. Fixed-size vs dynamic arrays

- **Fixed-size arrays**:
  - Length is known at instantiation and cannot change.
  - Examples:
    - `std::array<T, N>`
    - C-style arrays: `T arr[N];`
- **Dynamic arrays**:
  - Length can be changed at runtime.
  - Example: `std::vector<T>`

Use fixed-size arrays when the size is compile-time and stable; prefer `std::vector` when you need runtime resizing.

---

### 2. `std::array` essentials

- `std::array` is declared as:
  ```cpp
  template <typename T, std::size_t N>
  struct array;
  ```
- Key properties:
  - `N` is a **non-type template parameter** of type `std::size_t`.
  - It is an **aggregate** → no constructors; uses **aggregate initialization**:
    ```cpp
    std::array<int, 4> a{ 1, 2, 3, 4 };
    ```
  - Often a great fit for `constexpr`:
    ```cpp
    constexpr std::array primes{ 2, 3, 5, 7 };
    ```
- Length access:
  - `a.size()` — member function, returns unsigned `size_type`.
  - `std::size(a)` — C++17, forwards to `.size()`.
  - `std::ssize(a)` — C++20, returns signed length (usually `std::ptrdiff_t`).

---

### 3. Indexing `std::array`

- `operator[]`:
  - No bounds checking.
  - Invalid index ⇒ **undefined behavior**.
  ```cpp
  int x = a[1];
  ```
- `.at(i)`:
  - Runtime bounds checking (slower).
  - Throws `std::out_of_range` if `i` is invalid.
- `std::get<N>(a)`:
  - Template-based indexing:
    ```cpp
    auto x = std::get<2>(a);
    ```
  - Index `N` is a template parameter.
  - Checked at **compile time**.

Use `std::get` for compile-time-known indices, `.at()` for guarded runtime access, and `operator[]` when you know indices are valid.

---

### 4. Passing and returning `std::array`

- Pass `std::array`:
  - By (const) reference for efficiency:
    ```cpp
    template <typename T, std::size_t N>
    void print(const std::array<T, N>& arr);
    ```
- Return `std::array` by value:
  - Copies the array and all elements.
  - Often acceptable for small arrays or cheap-to-copy types.
  - For performance-critical cases, consider out-parameters or views.

---

### 5. Arrays of references via `std::reference_wrapper`

- You **cannot** have `T& arr[N];` as a real array of references.
- Instead, use `std::reference_wrapper<T>`:
  ```cpp
  int a{1}, b{2}, c{3};
  std::array<std::reference_wrapper<int>, 3> refs{ a, b, c };

  refs[0].get() = 42;  // modifies a
  int& r = refs[1];    // implicit conversion to int&
  ```
- Important properties:
  - `operator=` reseats the wrapper (changes what it refers to).
  - `std::ref(obj)` and `std::cref(obj)` create wrappers conveniently.

---

### 6. C-style arrays

- Declaration:
  ```cpp
  int arr[3]{ 1, 2, 3 };
  ```
- Characteristics:
  - Part of the **core language**.
  - Length must be a **constant expression**.
  - Are **aggregates**, initialized with aggregate initialization.
- Length:
  - `std::size(arr)` (C++17) → `std::size_t`.
  - `std::ssize(arr)` (C++20) → signed length (`std::ptrdiff_t`).
- Indexing:
  - Via `operator[]` as usual.
  - Indices can be signed or unsigned integers, or **unscoped enums**.
  - This avoids some of the sign-conversion issues seen with standard library containers.

---

### 7. Array decay and pointer arithmetic

- In most expressions, a C-style array **decays** to a pointer to its first element:
  ```cpp
  int arr[]{ 1, 2, 3, 4 };
  int* p = arr;        // arr decays to &arr[0]
  ```
- Pointer arithmetic:
  ```cpp
  int* q = p + 2;      // points to arr[2]
  int value = *(p + 3); // arr[3]
  ```
- Rules of thumb:
  - Use **subscripting** when indexing from the start:
    ```cpp
    arr[i];
    ```
  - Use **pointer arithmetic** when doing relative positioning from a known element.

C-style strings (`char[]` / `const char[]`) are just C-style arrays of `char` and also decay in the same way.

---

### 8. Multidimensional arrays

- Dimension = number of indices required:
  - 1D: `int a[5];`
  - 2D: `int m[3][4];`  // array of arrays
- Multidimensional arrays are conceptually **arrays of arrays**.
- **Flattening**:
  - Transforming higher-dimensional arrays into a single 1D layout for processing or interfacing with APIs.
- `std::mdspan` (C++23):
  - A **view** providing a multidimensional indexing interface over a contiguous sequence:
    - Separates **memory layout** from **indexing**.
    - Lets you treat a flat buffer as a matrix, tensor, etc., without copying.


### 🧱 Core Concepts You Mastered:
- 🧊 **Fixed-size vs dynamic arrays**
  - Fixed-size: `std::array`, C-style arrays
  - Dynamic: `std::vector` with runtime-resizable length

- 🧩 **`std::array` design**
  - Aggregate type with `T` and `N` (non-type template parameter of `std::size_t`)
  - Great candidate for `constexpr` usage
  - Works well with CTAD for concise declarations

- 📐 **Getting sizes correctly**
  - `.size()` for containers
  - `std::size()` (C++17) and `std::ssize()` (C++20) for signed/unsigned length
  - All usable with `std::array` and C-style arrays

- 🎛 **Safe and expressive indexing**
  - `operator[]` (fast, no checks)
  - `.at()` (runtime bounds checking via exceptions)
  - `std::get<N>()` (compile-time-checked indexing for `std::array`)

- 🧷 **Arrays of references**
  - Use `std::reference_wrapper<T>` instead of actual reference arrays
  - Create them with `std::ref()` / `std::cref()`
  - Reseat and access via `operator=` and `.get()`

- 🧮 **Array decay & pointer arithmetic**
  - C-style arrays decay to `T*` in most expressions
  - Pointer arithmetic (`p + k`, `*(p + k)`) for relative indexing
  - Knowing when to prefer subscripting vs pointer arithmetic

- 🧱 **Multidimensional structures**
  - Understanding 1D, 2D, and higher-dimensional arrays as “arrays of arrays”
  - Concept of flattening for storage or performance
  - Role of `std::mdspan` as a modern, flexible multidimensional view