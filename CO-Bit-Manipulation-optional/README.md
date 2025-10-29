# Chapter O (Optional) — Bit Manipulation

## 🧭 Overview
Bit manipulation allows you to directly operate on the binary representation of data — controlling, setting, or reading individual bits.  
Although modern C++ provides higher-level abstractions, bitwise operations remain essential in performance-critical applications such as **embedded systems**, **graphics**, **cryptography**, and **compression**.  

This chapter introduces bitwise concepts, `std::bitset`, and bit masking techniques. You’ll learn how to use these tools to efficiently represent and manipulate boolean flags, control hardware-level data, and optimize memory usage.  

> **Key idea:** Bit manipulation trades simplicity for control and efficiency — understanding it is crucial for low-level programming and system design.

---

## 🧱 Build / Run (TODO)

TODO: check and update this in all readmes
```bash
cmake --build build --target chO_first
./build/chO_first
```

---

## 🎯 Learning Outcomes

By the end of this chapter, you’ll be able to:

- Explain what **bit manipulation** is and why it’s important in systems and performance programming.
- Understand how to represent and operate on individual bits using `std::bitset`.
- Use **bitwise operators** (`&`, `|`, `^`, `~`, `<<`, `>>`) safely and effectively.
- Apply **bit masks** to set, clear, toggle, and test specific bits.
- Recognize the role of **integral promotions** and why smaller integer types require explicit casting.
- Convert between **binary** and **decimal** representations manually and programmatically.
- Explain **two’s complement** and how signed integers are represented in binary.
- Apply bit manipulation techniques to real-world tasks, such as flag management and color extraction from packed values.

---

## Sections

### S01 — O.1 Bit flags and bit manipulation via `std::bitset` (easy way)
On modern computer, the smallest addressable unit of memory is the byte (8 bits). This means that all objects need to be at least one byte in size. For **boolean** values, this is quite wasteful, since a boolean value only needs one bit to represent its two possible states (true or false), and the rest 7 bits wouldn't be used at all.

Normally, this is fine, since memory is cheap and boolean values are not used in large quantities. However, in some cases, such as storage-intensive applications or performance-critical systems, it may be necessary to optimize memory usage by packing multiple boolean values into a single byte or word. This is where **bit manipulation** comes into play.

#### Bit flags:
Up to now, we have used variables to hold single values. However, sometimes is useful to treat each bit of a byte (or larger data type) as a separate boolean flag. When individual bits of an object are used as independent boolean values, the bits are called **bit flags**.

To define a set of bit flags, we will typically use an unsigned integer of appropriate size (8, 16, 32, etc. bits), or `std::bitset`, which is a standard library class that provides a convenient way to work with bit flags.
```cpp
#include <bitset> // for std::bitset

std::bitset<8> mybitset {}; // 8 bits in size means room for 8 flags
```

Given a sequence of bits, we number the bits from right to left, starting from 0. For example, in the following bitset:
```
std::bitset<8> mybitset { 0b00001101 };
```
The bits are numbered as follows:
```
Bit position:  7 6 5 4 3 2 1 0
Bit value:     0 0 0 0 1 1 0 1
```

#### Manipulating bits via `std::bitset`:
`std::bitset` provides several member functions to manipulate individual bits or groups of bits:
- `test(pos)`: Returns the value of the bit at position `pos`,and give whether a bit is set (1) or not (0).
- `set(pos)`: Sets the bit at position `pos` to 1.
- `reset(pos)`: Sets the bit at position `pos` to 0.
- `flip(pos)`: Toggles the bit at position `pos` (if it's 0, it becomes 1; if it's 1, it becomes 0).

For example:
```cpp
#include <bitset>
#include <iostream>

int main()
{
    std::bitset<8> bits{ 0b0000'0101 }; // we need 8 bits, start with bit pattern 0000 0101
    bits.set(3);   // set bit position 3 to 1 (now we have 0000 1101)
    bits.flip(4);  // flip bit 4 (now we have 0001 1101)
    bits.reset(4); // set bit 4 back to 0 (now we have 0000 1101)

    std::cout << "All the bits: " << bits<< '\n';
    std::cout << "Bit 3 has value: " << bits.test(3) << '\n';
    std::cout << "Bit 4 has value: " << bits.test(4) << '\n';

    return 0;
}
```
prints:
```
All the bits: 00001101
Bit 3 has value: 1
Bit 4 has value: 0
```

Giving our bits some names, makes the code more readable:
```cpp
#include <bitset>
#include <iostream>

int main()
{
    [[maybe_unused]] constexpr int  isHungry   { 0 };
    [[maybe_unused]] constexpr int  isSad      { 1 };
    [[maybe_unused]] constexpr int  isMad      { 2 };
    [[maybe_unused]] constexpr int  isHappy    { 3 };
    [[maybe_unused]] constexpr int  isLaughing { 4 };
    [[maybe_unused]] constexpr int  isAsleep   { 5 };
    [[maybe_unused]] constexpr int  isDead     { 6 };
    [[maybe_unused]] constexpr int  isCrying   { 7 };

    std::bitset<8> me{ 0b0000'0101 }; // we need 8 bits, start with bit pattern 0000 0101
    me.set(isHappy);      // set bit position 3 to 1 (now we have 0000 1101)
    me.flip(isLaughing);  // flip bit 4 (now we have 0001 1101)
    me.reset(isLaughing); // set bit 4 back to 0 (now we have 0000 1101)

    std::cout << "All the bits: " << me << '\n';
    std::cout << "I am happy: " << me.test(isHappy) << '\n';
    std::cout << "I am laughing: " << me.test(isLaughing) << '\n';

    return 0;
}
```
prints:
```
All the bits: 00001101
I am happy: 1
I am laughing: 0
```

> **Note:** If we want to get or set multiple bits at once, we will need more traditional methods, since `std::bitset` does not provide built-in support for that (next lessons).

#### The size of `std::bitset`:
Surprisingly, `std::bitset` is optimized for **speed**, not **memory usage**. This means that while it provides fast access and manipulation of individual bits, it may not be the most memory-efficient way to store large numbers of boolean flags. The size of a `std::bitset` is typically the number of bytes required to store the specified number of bits, rounded up to the nearest `size_of(size_t)`, that is usually 4 bytes on a 32-bit system and 8 bytes on a 64-bit system.

> **Note:** If memory efficiency is a primary concern, and you need to store a large number of boolean flags, consider using other techniques.

#### Querying `std::bitset`:
There are few other member functions that can be useful to query the state of a `std::bitset`:
- `size()`: Returns the number of bits in the bitset.
- `count()`: Returns the number of bits that are set to 1 (true).
- `all()`: Returns boolean indicating whether all bits are set to 1.
- `any()`: Returns boolean indicating whether at least one bit is set to 1.
- `none()`: Returns boolean indicating whether no bits are set to 1.

For example:
```cpp
#include <bitset>
#include <iostream>

int main()
{
    std::bitset<8> bits{ 0b0000'1101 };
    std::cout << bits.size() << " bits are in the bitset\n";
    std::cout << bits.count() << " bits are set to true\n";

    std::cout << std::boolalpha;
    std::cout << "All bits are true: " << bits.all() << '\n';
    std::cout << "Some bits are true: " << bits.any() << '\n';
    std::cout << "No bits are true: " << bits.none() << '\n';

    return 0;
}
```
prints:
```
8 bits are in the bitset
3 bits are set to true
All bits are true: false
Some bits are true: true
No bits are true: false
```

#### Summary:
- `std::bitset` provides a convenient way to manage multiple boolean flags using individual bits.
- You can manipulate individual bits using member functions like `set()`, `reset()`, `flip()`, and `test()`.
- `std::bitset` is optimized for speed rather than memory efficiency.
- You can query the state of a `std::bitset` using functions like `size()`, `count()`, `all()`, `any()`, and `none()`.


---

### S02 — O.2 Bitwise operators
#### The bitwise operators:
C++ provides a set of **bitwise operators** that allow you to manipulate individual bits within integer types. These operators work directly on the binary representation of the data. The main bitwise operators are:

| Operator | Symbol | Form | Description                          |
|----------|--------|------|--------------------------------------|
| Left Shift | `<<` | x << n | Shifts the bits of `x` to the left by `n` positions. New bits on the right are filled with `0`s. |
| Right Shift | `>>` | x >> n | Shifts the bits of `x` to the right by `n` positions. New bits on the left are filled with `0`s for unsigned types, and with the sign bit for signed types (arithmetic shift). |
| Bitwise NOT | `~` | ~x | Inverts all bits of `x` (0s become 1s and 1s become 0s). |
| Bitwise AND | `&` | x & y | Performs a logical AND operation on each pair of corresponding bits of `x` and `y`. |
| Bitwise OR | `\|` | x \| y | Performs a logical OR operation on each pair of corresponding bits of `x` and `y`. |
| Bitwise XOR | `^` | x ^ y | Performs a logical XOR operation on each pair of corresponding bits of `x` and `y`. |

These are **non-modifying** operators, meaning they do not change the original values but return a new value with the result of the operation.

The bitwise operators are defined for integral types (e.g., `int`, `unsigned int`, `char`, etc.) and `std::bitset`.

> **Note:** Avoid using bitwise operators on signed integral operands, as the behavior is implementation-defined for negative values.

#### Bitwise left shift (`<<`) and right shift (`>>`) operators:
The left shift operator (`<<`) shifts the bits of its left operand to the left by the number of positions specified by its right operand. The right shift operator (`>>`) shifts the bits of its left operand to the right by the number of positions specified by its right operand. New bits are filled with `0`s for unsigned types, and with the sign bit for signed types (arithmetic shift, but avoid this!).

Here some examples of left and right shift operations:
```
0011 (3 in decimal) << 1 = 0110 (6 in decimal)
0011 (3 in decimal) << 2 = 1100 (12 in decimal)
0011 (3 in decimal) << 3 = 1000 (24 in decimal)

1100 (12 in decimal) >> 1 = 0110 (6 in decimal)
1100 (12 in decimal) >> 2 = 0011 (3 in decimal)
1100 (12 in decimal) >> 3 = 0001 (1 in decimal)
```

Another example using C++ code:
```cpp
#include <bitset>
#include <iostream>

int main()
{
    std::bitset<4> x { 0b1100 };

    std::cout << x << '\n';
    std::cout << (x >> 1) << '\n'; // shift right by 1, yielding 0110
    std::cout << (x << 1) << '\n'; // shift left by 1, yielding 1000

    return 0;
}
```
prints:
```
1100
0110
1000
```

#### Difference with `<<` and `>>` stream operators:
Be careful not to confuse the bitwise shift operators (`<<` and `>>`) with the stream insertion and extraction operators, which use the same symbols. The context in which they are used determines their meaning. For example:
```cpp
#include <bitset>
#include <iostream>

int main()
{
    unsigned int x { 0b0100 };
    x = x << 1; // use operator<< for left shift
    std::cout << std::bitset<4>{ x } << '\n'; // use operator<< for output

    return 0;
}
```
prints:
```
1000
```

The `operator<<` understands whether it is used for bit shifting or for output based on the types of its operands. For example, when the left operand is an integral type, it performs a bitwise shift. When the left operand is an output stream (like `std::cout`), it performs stream insertion. The same applies to the `>>` operator for right shifts and stream extraction.

If you are using `operator<<` for both output and shift, parenthesization is required to avoid ambiguity. For example:
```cpp
#include <bitset>
#include <iostream>

int main()
{
	std::bitset<4> x{ 0b0110 };

	std::cout << x << 1 << '\n'; // print value of x (0110), then 1
	std::cout << (x << 1) << '\n'; // print x left shifted by 1 (1100)

	return 0;
}
```
prints:
```
01101
1100
```

#### Bitwise NOT (`~`):
The bitwise NOT operator (`~`) inverts all bits of its operand. This means that all `0`s become `1`s and all `1`s become `0`s. For example:
```
~0011 (3 in decimal) = 1100 (12 in decimal, for a 4-bit representation)
~0000 0100 (4 in decimal) = 1111 1011 (251 in decimal, for an 8-bit representation)
```

The NOT operator depends on the number of bits used to represent the value. For example, applying `~` to an 8-bit value will yield a different result than applying it to a 16-bit value. For example:
```cpp
#include <bitset>
#include <iostream>

int main()
{
    std::bitset<8> a { 0b0000'0100 }; // 8 bits
    std::bitset<16> b { 0b0000'0000'0000'0100 }; // 16 bits

    std::cout << "~a: " << ~a << '\n'; // inverts all 8 bits
    std::cout << "~b: " << ~b << '\n'; // inverts all 16 bits

    return 0;
}
```
prints:
```
~a: 11111100
~b: 1111111111111011
```

#### Bitwise OR (`|`):
The bitwise OR operator (`|`) performs a logical OR operation on each pair of corresponding bits of its two operands. The result bit is `1` if at least one of the operand bits is `1`; otherwise, it is `0`. For example:
```
0011 (3 in decimal) | 0101 (5 in decimal) = 0111 (7 in decimal)
1100 (12 in decimal) | 1010 (10 in decimal) = 1110 (14 in decimal)
```

You can visualize it like this:
```
0 0 1 1 OR
0 1 0 1
-------
0 1 1 1
```

We can do the same with compund assignment operator `|`, for example, `0b0111 | 0b0011 | 0b0001`:
```
0 1 1 1 OR
0 0 1 1 OR
0 0 0 1
-------
0 1 1 1
```

#### Bitwise AND (`&`):
The bitwise AND operator (`&`) performs a logical AND operation on each pair of corresponding bits of its two operands. The result bit is `1` only if both operand bits are `1`; otherwise, it is `0`. For example:
```
0011 (3 in decimal) & 0101 (5 in decimal) = 0001 (1 in decimal)
1100 (12 in decimal) & 1010 (10 in decimal) = 1000 (8 in decimal)
```

You can visualize it like this:
```
0 1 0 1 AND
0 1 1 0
-------
0 1 0 0
```

We can do the same with compund assignment operator `&`, for example, `0b0111 & 0b0011 & 0b0001`:
```
0 1 1 1 AND
0 0 1 1 AND
0 0 0 1
-------
0 0 0 1
```

#### Bitwise XOR (`^`):
The bitwise XOR operator (`^`) performs a logical exclusive OR operation on each pair of corresponding bits of its two operands. The result bit is `1` if the operand bits are different (one is `1` and the other is `0`); otherwise, it is `0`. For example:
```
0011 (3 in decimal) ^ 0101 (5 in decimal) = 0110 (6 in decimal)
1100 (12 in decimal) ^ 1010 (10 in decimal) = 0110 (6 in decimal)
```

You can visualize it like this:
```
0 1 0 1 XOR
0 1 1 0
-------
0 0 1 1
```

#### Bitwise assignment operators:
Similar to the arithmetic assignement operators (like `+=`, `-=`, etc.), C++ provides compound assignment operators for bitwise operations. These operators combine a bitwise operation with assignment, allowing you to modify the value of a variable in place. The bitwise assignment operators are:

| Operator | Symbol | Form | Description                          |
|----------|--------|------|--------------------------------------|
| Left Shift Assignment | `<<=` | x <<= n | The bits of `x` are shifted to the left by `n` positions, and the result is assigned back to `x`. New bits on the right are filled with `0`s. |
| Right Shift Assignment | `>>=` | x >>= n | The bits of `x` are shifted to the right by `n` positions, and the result is assigned back to `x`. New bits on the left are filled with `0`s for unsigned types, and with the sign bit for signed types (arithmetic shift). |
| Bitwise AND Assignment | `&=` | x &= y | A bitwise AND operation is performed between `x` and `y`, and the result is assigned back to `x`. |
| Bitwise OR Assignment | `\|=` | x \|= y | A bitwise OR operation is performed between `x` and `y`, and the result is assigned back to `x`. |
| Bitwise XOR Assignment | `^=` | x ^= y | A bitwise XOR operation is performed between `x` and `y`, and the result is assigned back to `x`. |

For example, instead of writing `x = x << 2;`, you can write `x <<= 2;`.

#### Bitwise operators perform integral promotions on smaller types (advanced):
If the operand(s) of a bitwise operator are an integral type smaller than `int` (such as `char` or `short`), they are **promoted** to `int` or `unsigned int` before the operation is performed, and return type is also `int` or `unsigned int`. This means that when using bitwise operators on smaller types, the result may not fit back into the original type without an explicit cast. 

For example, if our operands are `unsigned short`, they will be promoted to `unsigned int` before the operation, and the result will also be of type `unsigned int`.

When doing bitwise operations on smaller types, be aware of these two main issues:
- `operator~` and `operator<<` are width-sensitive, meaning that the number of bits in the type affects the result.
- Initializing or assigning the result of a bitwise operation back to a smaller type may lead to data loss if the result exceeds the range of the smaller type.

For example:
```cpp
#include <bitset>
#include <cstdint>
#include <iostream>

int main()
{
    std::uint8_t c { 0b00001111 };

    std::cout << std::bitset<32>(~c) << '\n';     // incorrect: prints 11111111111111111111111111110000
    std::cout << std::bitset<32>(c << 6) << '\n'; // incorrect: prints 0000000000000000001111000000
    std::uint8_t cneg { ~c };                     // error: narrowing conversion from unsigned int to std::uint8_t
    c = ~c;                                       // possible warning: narrowing conversion from unsigned int to std::uint8_t

    return 0;
}
```
prints:
```
11111111111111111111111111110000
0000000000000000001111000000
```
In this case, to get the expected results, we need to cast the results back to `std::uint8_t`:
```cpp
#include <bitset>
#include <cstdint>
#include <iostream>

int main()
{
    std::uint8_t c { 0b00001111 };

    std::cout << std::bitset<32>(static_cast<std::uint8_t>(~c)) << '\n';     // correct: prints 00000000000000000000000011110000
    std::cout << std::bitset<32>(static_cast<std::uint8_t>(c << 6)) << '\n'; // correct: prints 0000000000000000000011000000
    std::uint8_t cneg { static_cast<std::uint8_t>(~c) };                     // compiles
    c = static_cast<std::uint8_t>(~c);                                       // no warning

    return 0;
}
```
prints:
```
00000000000000000000000011110000
0000000000000000000011000000
```

> **Best practice:** Avoid using bitwise operators on smaller integral types unless you are fully aware of the implications of integral promotions and type conversions.

#### Summary:
- Bitwise operators allow you to manipulate individual bits within integer types.
- The main bitwise operators are left shift (`<<`), right shift (`>>`), bitwise NOT (`~`), bitwise AND (`&`), bitwise OR (`|`), and bitwise XOR (`^`).
- Bitwise assignment operators combine a bitwise operation with assignment, allowing you to modify the value of a variable in place.
- Be cautious when using bitwise operators on smaller integral types, as they are promoted to `int` or `unsigned int` before the operation, which may lead to unexpected results or data loss if not handled properly.


---

### S03 - O.3 Bit manipulation with bitwise operators and bit masks
Let's have a look on how bitwise operators are commonly used.

#### Bit masks:
A **bit mask** is a binary pattern that is used to select or manipulate specific bits within a larger binary value. Bit masks are typically created using bitwise operators to set, clear, or toggle specific bits.
For example, consider a byte (8 bits) where each bit represents a different feature or option. We can use bit masks to enable or disable specific features by manipulating the corresponding bits.

#### Defining bit masks in C++14 and later:
The easiest way to define bit masks in C++14 and later is to use symbolic constants with binary literals:
```cpp
#include <cstdint>

constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7
```

#### Defining bit masks in C++11 and earlier:
because C++11 does not support binary literals, we need to use other methods to set the symbolic constants for bit masks. Tehere are two good methods to do this:
1. Using hexadecimal literals:
    ```cpp
    constexpr std::uint8_t mask0{ 0x01 }; // hex for 0000 0001
    constexpr std::uint8_t mask1{ 0x02 }; // hex for 0000 0010
    constexpr std::uint8_t mask2{ 0x04 }; // hex for 0000 0100
    constexpr std::uint8_t mask3{ 0x08 }; // hex for 0000 1000
    constexpr std::uint8_t mask4{ 0x10 }; // hex for 0001 0000
    constexpr std::uint8_t mask5{ 0x20 }; // hex for 0010 0000
    constexpr std::uint8_t mask6{ 0x40 }; // hex for 0100 0000
    constexpr std::uint8_t mask7{ 0x80 }; // hex for 1000 0000
    ```
2. Using left shift operator:
    ```cpp
    constexpr std::uint8_t mask0{ 1 << 0 }; // 0000 0001
    constexpr std::uint8_t mask1{ 1 << 1 }; // 0000 0010
    constexpr std::uint8_t mask2{ 1 << 2 }; // 0000 0100
    constexpr std::uint8_t mask3{ 1 << 3 }; // 0000 1000
    constexpr std::uint8_t mask4{ 1 << 4 }; // 0001 0000
    constexpr std::uint8_t mask5{ 1 << 5 }; // 0010 0000
    constexpr std::uint8_t mask6{ 1 << 6 }; // 0100 0000
    constexpr std::uint8_t mask7{ 1 << 7 }; // 1000 0000
    ```

#### Testing a bit (to see if it is on or off):
To test whether a specific bit is set (1) or not (0), we can use the bitwise **AND** operator (`&`) with the appropriate bit mask. If the result of the AND operation is non-zero, the bit is set; otherwise, it is not set. For example:
```cpp
#include <cstdint>
#include <iostream>

int main()
{
	[[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
	[[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
	[[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
	[[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
	[[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
	[[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
	[[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
	[[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

	std::uint8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags

	std::cout << "bit 0 is " << (static_cast<bool>(flags & mask0) ? "on\n" : "off\n");
	std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1) ? "on\n" : "off\n");

	return 0;
}
```
prints:
```
bit 0 is on
bit 1 is off
```

Let's see how this works. First, we perform the bitwise AND operation between `flags` and `mask0`:
```
0000'0101 &
0000'0001
-----------
0000'0001
```
Then, we cast the result to `bool`. Since the result is non-zero (`0000'0001`), it evaluates to `true`, indicating that bit 0 is set (on).

In case of bit 1:
```
0000'0101 &
0000'0010
-----------
0000'0000
```
The result is zero (`0000'0000`), which evaluates to `false`, indicating that bit 1 is not set (off).

#### Setting a bit (turning it on):
To set a specific bit to `1` (turn it on), we can use the bitwise **OR** operator (`|`) with the appropriate bit mask. This operation will set the desired bit to `1` while leaving all other bits unchanged. For example:
```cpp
#include <cstdint>
#include <iostream>

int main()
{
    [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
    [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
    [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
    [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
    [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
    [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
    [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
    [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

    std::uint8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags

    std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1) ? "on\n" : "off\n");

    flags |= mask1; // turn on bit 1

    std::cout << "bit 1 is " << (static_cast<bool>(flags & mask1) ? "on\n" : "off\n");

    return 0;
}
```
prints:
```
bit 1 is off
bit 1 is on
```

We can also turn on multiple bits at once by combining multiple masks using the bitwise OR operator:
```cpp
flags |= (mask1 | mask3); // set bits 1 and 3
```

#### Resetting a bit (turning it off):
To reset a specific bit to `0` (turn it off), we can use the bitwise **AND** operator (`&`) in combination with the bitwise **NOT** operator (`~`). First, we invert the bit mask using the NOT operator, which creates a mask with all bits set to `1` except for the bit we want to reset, which is set to `0`. Then, we perform the AND operation between the original value and the inverted mask. This operation will reset the desired bit to `0` while leaving all other bits unchanged. For example:
```cpp
#include <cstdint>
#include <iostream>

int main()
{
    [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
    [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
    [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
    [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
    [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
    [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
    [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
    [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

    std::uint8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags

    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");

    flags &= ~mask2; // turn off bit 2

    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");

    return 0;
}
```
prints:
```
bit 2 is on
bit 2 is off
```

We can also turn off multiple bits at once by combining multiple masks using the bitwise OR operator before inverting:
```cpp
flags &= ~(mask2 | mask3); // reset bits 2 and 3
```

#### Toggling a bit (flipping its state):
To toggle a specific bit (change it from `0` to `1` or from `1` to `0`), we can use the bitwise **XOR** operator (`^`). The XOR operation will flip the desired bit while leaving all other bits unchanged. For example:
```
#include <cstdint>
#include <iostream>

int main()
{
    [[maybe_unused]] constexpr std::uint8_t mask0{ 0b0000'0001 }; // represents bit 0
    [[maybe_unused]] constexpr std::uint8_t mask1{ 0b0000'0010 }; // represents bit 1
    [[maybe_unused]] constexpr std::uint8_t mask2{ 0b0000'0100 }; // represents bit 2
    [[maybe_unused]] constexpr std::uint8_t mask3{ 0b0000'1000 }; // represents bit 3
    [[maybe_unused]] constexpr std::uint8_t mask4{ 0b0001'0000 }; // represents bit 4
    [[maybe_unused]] constexpr std::uint8_t mask5{ 0b0010'0000 }; // represents bit 5
    [[maybe_unused]] constexpr std::uint8_t mask6{ 0b0100'0000 }; // represents bit 6
    [[maybe_unused]] constexpr std::uint8_t mask7{ 0b1000'0000 }; // represents bit 7

    std::uint8_t flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags

    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");
    flags ^= mask2; // flip bit 2
    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");
    flags ^= mask2; // flip bit 2
    std::cout << "bit 2 is " << (static_cast<bool>(flags & mask2) ? "on\n" : "off\n");

    return 0;
}
```
prints:
```
bit 2 is on
bit 2 is off
bit 2 is on
```

This is because the XOR operation works as follows:
```
0000'0101 ^
0000'0100
-----------
0000'0001
```
The bit at position 2 is flipped from `1` to `0`.

We can also toggle multiple bits at once by combining multiple masks using the bitwise OR operator:
```cpp
flags ^= (mask0 | mask3); // toggle bits 0 and 3
```

#### Bit masks and `std::bitset`:
We can also use bit masks with `std::bitset` to manipulate individual bits. The same principles apply, but we use `std::bitset` member functions instead of bitwise operators. For example:
```cpp
#include <bitset>
#include <iostream>

int main()
{
	[[maybe_unused]] constexpr std::bitset<8> mask0{ 0b0000'0001 }; // represents bit 0
	[[maybe_unused]] constexpr std::bitset<8> mask1{ 0b0000'0010 }; // represents bit 1
	[[maybe_unused]] constexpr std::bitset<8> mask2{ 0b0000'0100 }; // represents bit 2
	[[maybe_unused]] constexpr std::bitset<8> mask3{ 0b0000'1000 }; // represents bit 3
	[[maybe_unused]] constexpr std::bitset<8> mask4{ 0b0001'0000 }; // represents bit 4
	[[maybe_unused]] constexpr std::bitset<8> mask5{ 0b0010'0000 }; // represents bit 5
	[[maybe_unused]] constexpr std::bitset<8> mask6{ 0b0100'0000 }; // represents bit 6
	[[maybe_unused]] constexpr std::bitset<8> mask7{ 0b1000'0000 }; // represents bit 7

	std::bitset<8> flags{ 0b0000'0101 }; // 8 bits in size means room for 8 flags
	std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n");
	std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n");

	flags ^= (mask1 | mask2); // flip bits 1 and 2
	std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n");
	std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n");

	flags |= (mask1 | mask2); // turn bits 1 and 2 on
	std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n");
	std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n");

	flags &= ~(mask1 | mask2); // turn bits 1 and 2 off
	std::cout << "bit 1 is " << (flags.test(1) ? "on\n" : "off\n");
	std::cout << "bit 2 is " << (flags.test(2) ? "on\n" : "off\n");

	return 0;
}
```
prints:
```
bit 1 is off
bit 2 is on
bit 1 is on
bit 2 is off
bit 1 is on
bit 2 is on
bit 1 is off
bit 2 is off
```

#### Making bit masks meaningful`:
To make bit masks more meaningful, we can define symbolic constants with meaningful names. For example, consider a scenario where we want to represent the state of a person using bits:
```cpp
#include <cstdint>
#include <iostream>

int main()
{
        // Define a bunch of physical/emotional states
	[[maybe_unused]] constexpr std::uint8_t isHungry   { 1 << 0 }; // 0000 0001
	[[maybe_unused]] constexpr std::uint8_t isSad      { 1 << 1 }; // 0000 0010
	[[maybe_unused]] constexpr std::uint8_t isMad      { 1 << 2 }; // 0000 0100
	[[maybe_unused]] constexpr std::uint8_t isHappy    { 1 << 3 }; // 0000 1000
	[[maybe_unused]] constexpr std::uint8_t isLaughing { 1 << 4 }; // 0001 0000
	[[maybe_unused]] constexpr std::uint8_t isAsleep   { 1 << 5 }; // 0010 0000
	[[maybe_unused]] constexpr std::uint8_t isDead     { 1 << 6 }; // 0100 0000
	[[maybe_unused]] constexpr std::uint8_t isCrying   { 1 << 7 }; // 1000 0000

	std::uint8_t me{}; // all flags/options turned off to start
	me |= (isHappy | isLaughing); // I am happy and laughing
	me &= ~isLaughing; // I am no longer laughing

	// Query a few states
	// (we'll use static_cast<bool> to interpret the results as a boolean value)
	std::cout << std::boolalpha; // print true or false instead of 1 or 0
	std::cout << "I am happy? " << static_cast<bool>(me & isHappy) << '\n';
	std::cout << "I am laughing? " << static_cast<bool>(me & isLaughing) << '\n';

	return 0;
}
```
prints:
```
I am happy? true
I am laughing? false
```

Here the same example using the `std::bitset`:
```cpp
#include <bitset>
#include <iostream>

int main()
{
        // Define a bunch of physical/emotional states
	[[maybe_unused]] constexpr std::bitset<8> isHungry   { 0b0000'0001 };
	[[maybe_unused]] constexpr std::bitset<8> isSad      { 0b0000'0010 };
	[[maybe_unused]] constexpr std::bitset<8> isMad      { 0b0000'0100 };
	[[maybe_unused]] constexpr std::bitset<8> isHappy    { 0b0000'1000 };
	[[maybe_unused]] constexpr std::bitset<8> isLaughing { 0b0001'0000 };
	[[maybe_unused]] constexpr std::bitset<8> isAsleep   { 0b0010'0000 };
	[[maybe_unused]] constexpr std::bitset<8> isDead     { 0b0100'0000 };
	[[maybe_unused]] constexpr std::bitset<8> isCrying   { 0b1000'0000 };


	std::bitset<8> me{}; // all flags/options turned off to start
	me |= (isHappy | isLaughing); // I am happy and laughing
	me &= ~isLaughing; // I am no longer laughing

	// Query a few states (we use the any() function to see if any bits remain set)
	std::cout << std::boolalpha; // print true or false instead of 1 or 0
	std::cout << "I am happy? " << (me & isHappy).any() << '\n';
	std::cout << "I am laughing? " << (me & isLaughing).any() << '\n';

	return 0;
}
```

#### When are bit flags most useful?
Bit flags are particularly useful in scenarios where you need to manage multiple boolean options or states efficiently. Some common use cases include:
- **Configuration settings:** Storing multiple configuration options in a single variable.
- **Feature toggles:** Enabling or disabling specific features in software applications.
- **State management:** Representing the state of an object with multiple boolean attributes.
- **Function parameters:** Passing multiple boolean options to functions without using multiple parameters. For example, instead of writing `void configure(bool option1, bool option2, bool option3, bool option4, bool option5, bool option6, bool option7, bool option8);`, you can write `void configure(std::uint8_t mode2 | mode5 | mode7);`.

#### Bit masks involving multiple bits:
Bit masks can also be designed to manipulate multiple bits at once. For example, consider a scenario where we want to control color displays using RGB (Red, Green, Blue) values. Typically, each color component is represented using 8 bits (1 byte), allowing for 256 different intensity levels (0-255) for each color. Additionally, we can include an alpha channel (A) for transparency, resulting in a total of 32 bits (4 bytes) for RGBA representation.

| Bit | Color Component | Description                     |
|-----|-----------------|---------------------------------|
| 0-7 | Blue (B)       | Represents the intensity of blue |
| 8-15| Green (G)      | Represents the intensity of green|
|16-23| Red (R)        | Represents the intensity of red   |
|24-31| Alpha (A)      | Represents the transparency level |

The following program asks the user to enter a 32-bit hexadecimal value, and then extracts the 8-bit color values for R, G, B, and A:
```cpp
#include <cstdint>
#include <iostream>

int main()
{
	constexpr std::uint32_t redBits{ 0xFF000000 };
	constexpr std::uint32_t greenBits{ 0x00FF0000 };
	constexpr std::uint32_t blueBits{ 0x0000FF00 };
	constexpr std::uint32_t alphaBits{ 0x000000FF };

	std::cout << "Enter a 32-bit RGBA color value in hexadecimal (e.g. FF7F3300): ";
	std::uint32_t pixel{};
	std::cin >> std::hex >> pixel; // std::hex allows us to read in a hex value

	// use Bitwise AND to isolate the pixels for our given color,
	// then right shift the value into the lower 8 bits
	const std::uint8_t red{ static_cast<std::uint8_t>((pixel & redBits) >> 24) };
	const std::uint8_t green{ static_cast<std::uint8_t>((pixel & greenBits) >> 16) };
	const std::uint8_t blue{ static_cast<std::uint8_t>((pixel & blueBits) >> 8) };
	const std::uint8_t alpha{ static_cast<std::uint8_t>(pixel & alphaBits) };

	std::cout << "Your color contains:\n";
	std::cout << std::hex; // print the following values in hex

        // reminder: std::uint8_t will likely print as a char
        // we static_cast to int to ensure it prints as an integer
	std::cout << static_cast<int>(red)   << " red\n";
	std::cout << static_cast<int>(green) << " green\n";
	std::cout << static_cast<int>(blue)  << " blue\n";
	std::cout << static_cast<int>(alpha) << " alpha\n";

	return 0;
}
```
prints:
```
Enter a 32-bit RGBA color value in hexadecimal (e.g. FF7F3300): FF7F3300
Your color contains:
ff red
7f green
33 blue
0 alpha
```

In this example, we define bit masks for each color component using hexadecimal literals. We then use the bitwise AND operator to isolate the bits corresponding to each color component and right shift the result to obtain the 8-bit values for red, green, blue, and alpha.

#### Summary:
- Bit masks are binary patterns used to select or manipulate specific bits within a larger binary value.
- Bit masks can be defined using binary literals (C++14 and later), hexadecimal literals, or left shift operations (C++11 and earlier).
- Bitwise operators such as AND, OR, NOT, and XOR are used to test, set, reset, and toggle bits using bit masks.
- Bit masks are useful for managing multiple boolean options or states efficiently in various scenarios, such as configuration settings, feature toggles, state management, and function parameters.


---

### S03 - O.4 Converting integers between binary and decimal representation
Converting integers between binary and decimal representation is a fundamental skill in computer science and programming. Here, we'll explore how to perform these conversions manually and with C++.

Consider a decimal integral value, such as `5623`. We intuitively know that this value is made up of the following components:
```
5 * 10^3 + 6 * 10^2 + 2 * 10^1 + 3 * 10^0
```

Binary numbers work similarly, but instead of powers of `10`, they use powers of `2`. For example, the binary number `1011` can be broken down as follows:
```
1 * 2^3 + 0 * 2^2 + 1 * 2^1 + 1 * 2^0 = 8 + 0 + 2 + 1 = 11 (in decimal)
```

The following are the first 16 decimal numbers and their binary equivalents:
| Decimal | Binary  |
|---------|---------|
| 0       | 0000    |
| 1       | 0001    |
| 2       | 0010    |
| 3       | 0011    |
| 4       | 0100    |
| 5       | 0101    |
| 6       | 0110    |
| 7       | 0111    |
| 8       | 1000    |
| 9       | 1001    |
| 10      | 1010    |
| 11      | 1011    |
| 12      | 1100    |
| 13      | 1101    |
| 14      | 1110    |
| 15      | 1111    |

#### Converting binary to decimal:
In the following examples, we assum we are dealing with unsigned integers for simplicity.

To convert a binary number to its decimal equivalent, we can follow these steps:
1. Write down the binary number.
2. Assign powers of `2` to each bit position, starting from `0` on the right.
3. For each bit that is `1`, calculate the value of `2` raised to the power of its position.
4. Sum all the values obtained in step 3 to get the decimal equivalent.

For example, let's convert the binary number `0101 1110` to decimal:
| Bit Position | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
|--------------|---|---|---|---|---|---|---|---|
| Binary Digit | 0 | 1 | 0 | 1 | 1 | 1 | 1 | 0 |
| Power of 2   |128| 64 | 32 |16 | 8 | 4 | 2 | 1 |
| Contribution | 0 |64 | 0 |16 | 8 | 4 | 2 | 0 |

Summing up, we will get `64 + 16 + 8 + 4 + 2 = 94` in decimal.

#### Converting decimal to binary (Method 1: Division by 2):
To convert a decimal number to its binary equivalent using the division by `2` method, we can follow these steps:
1. Divide the decimal number by `2`.
2. Record the quotient and the remainder.
3. Repeat the division process with the quotient until the quotient becomes `0`.
4. The binary equivalent is obtained by reading the remainders in reverse order (from last to first).

For example, let's convert the decimal number `94` to binary:
```
94 ÷ 2 = 47, remainder 0
47 ÷ 2 = 23, remainder 1
23 ÷ 2 = 11, remainder 1
11 ÷ 2 = 5, remainder 1
5 ÷ 2 = 2, remainder 1
2 ÷ 2 = 1, remainder 0
1 ÷ 2 = 0, remainder 1
```

Reading the remainders in reverse order, we get `1011110` as the binary equivalent of `94`.

You can verify the answer by converting `1011110` back to decimal, doing `(1 * 2^6) + (0 * 2^5) + (1 * 2^4) + (1 * 2^3) + (1 * 2^2) + (1 * 2^1) + (0 * 2^0) = 64 + 0 + 16 + 8 + 4 + 2 + 0 = 94`.

#### Converting decimal to binary (Method 2: Comparison with powers of 2):
Another method to convert a decimal number to its binary equivalent is by comparing it with powers of `2`. We can follow these steps:
1. Find the largest power of `2` that is less than or equal to the decimal number.
2. Subtract that power of `2` from the decimal number and record a `1` in the corresponding bit position.
3. Repeat the process with the remainder until the remainder becomes `0`.
4. For any bit positions that were not used, record a `0`.

For example, let's convert the decimal number `94` to binary using this method:
- The largest power of `2` less than or equal to `94` is `64` (2^6). We record a `1` in bit position `6` and subtract `64` from `94`, leaving us with `30`.
- The largest power of `2` less than or equal to `30` is `16` (2^4). We record a `1` in bit position `4` and subtract `16` from `30`, leaving us with `14`.
- The largest power of `2` less than or equal to `14` is `8` (2^3). We record a `1` in bit position `3` and subtract `8` from `14`, leaving us with `6`.
- The largest power of `2` less than or equal to `6` is `4` (2^2). We record a `1` in bit position `2` and subtract `4` from`6`, leaving us with `2`.
- The largest power of `2` less than or equal to `2` is `2` (2^1). We record a `1` in bit position `1` and subtract `2` from `2`, leaving us with `0`.
- Since the remainder is now `0`, we stop here. We record a `0` in bit position `5` and bit position `0`, since that power of `2` was greater than our current value.

Putting it all together, we get the binary equivalent of `94` as `1011110`.

#### Converting decimal to binary (Method 3: Division by powers of 2):
A third method to convert a decimal number to its binary equivalent is by using division by powers of `2`. We can follow these steps:
1. Determine the highest power of `2` that is less than or equal to the decimal number.
2. Divide the decimal number by that power of `2` and store `1` if the quotient is odd, or `0` if the quotient is even.
3. Keep dividing the same decimal number by decreasing powers of `2` until you reach `2^0`.

For example, let's convert the decimal number `94` to binary using this method:
- The highest power of `2` less than or equal to `94` is `64` (2^6).
- `94 / 64 = 1` (odd), so we record `1` in bit position `6`.
- `94 / 32 = 2` (even), so we record `0` in bit position `5`.
- `94 / 16 = 5` (odd), so we record `1` in bit position `4`.
- `94 / 8 = 11` (odd), so we record `1` in bit position `3`.
- `94 / 4 = 23` (odd), so we record `1` in bit position `2`.
- `94 / 2 = 47` (odd), so we record `1` in bit position `1`.
- `94 / 1 = 94` (even), so we record `0` in bit position `0`.

Overall, we get the binary equivalent of `94` as `1011110`.

#### Adding in binary:
Adding binary numbers follows similar rules to decimal addition, with the key difference being that binary only has two digits: `0` and `1`. The rules for binary addition are as follows:
- `0 + 0 = 0`
- `0 + 1 = 1`
- `1 + 0 = 1`
- `1 + 1 = 10` (which is `0` with a carry of `1`)

For example, let's add the binary numbers `0110` (which is `6` in decimal) and `0111` (which is `7` in decimal). For the first column on the right:
```
0110 +
0111
------
   1
```
For the second column:
```
 1  (carry)
0110 +
0111
------
  01
```
For the third column, we are adding `1 + 1 + 1` (including the carry), so it will give `11` (which is `3` in decimal), giving `1` and a carry of `1`:
```
11   (carry)
0110 +
0111
------
 101
```
For the fourth column:
```
11   (carry)
0110 +
0111
------
1101
```

The final result is `1101`, which is `13` in decimal.

Another example:
```
      11  (carry column)
1011 0011 (original binary number) +
0000 0001 (1 in binary)
---------
1011 0100
```

#### Signed numbers and two's complement:
When dealing with signed integers, we often use a representation called ** two's complement**. In two's complement, the most significant bit (MSB) is used as the sign bit, where `0` indicates a positive number and `1` indicates a negative number.

#### COnverting decimal to binary (two's complement):
To convert a negative decimal number to its binary equivalent in two's complement, we can follow these steps:
1. Convert the absolute value of the decimal number to binary.
2. Invert all the bits (change `0`s to `1`s and `1`s to `0`s).
3. Add `1` to the inverted binary number.

For example, let's convert `-5` to its binary equivalent in two's complement using 8 bits:
1. Convert `5` to binary: `0000 0101`
2. Invert the bits: `1111 1010`
3. Add `1`, giving `1111 1011`.

*Why adding one?* Consider the number 0. If a negative value was simply represented as the inverse of the positive number (called “one’s complement”), 0 would have two representations: `0000 0000` (positive zero) and `1111 1111` (negative zero). Adding one to the inverted bits ensures that there is only one representation of zero, since `1111 1111 + 1 = 0000 0000` (with overflow discarded).

#### Converting binary (two's complement) to decimal:
To convert a binary number in two's complement to its decimal equivalent, we can follow these steps:
1. Check the sign bit (MSB). If it is `0`, the number is positive, and we can convert it to decimal as usual.
2. If the sign bit is `1`, the number is negative. To find its decimal equivalent:
   - Invert all the bits.
   - Add `1` to the inverted binary number.
   - Convert the resulting binary number to decimal and apply a negative sign.

For example, let's convert the binary number `1001 1110` (which is `-98` in decimal) to its decimal equivalent:
1. The sign bit is `1`, indicating that the number is negative.
2. Invert the bits: `0110 0001`
3. Add `1`, giving `0110 0010`.
4. Convert `0110 0010` to decimal: `64 + 32 + 2 = 98`.
5. Apply the negative sign, resulting in `-98`.


---

## 🧭 Summary

Bit manipulation offers a powerful way to control data at the bit level, allowing you to optimize performance and storage while maintaining precise control over data representation.  
Through this chapter, you explored `std::bitset` for managing multiple boolean flags, learned how bitwise operators work on integers, and discovered how bit masks simplify setting, clearing, and toggling individual bits.

You also learned how computers represent and interpret data in binary form — from **unsigned integers** to **two’s complement signed numbers** — and practiced converting between binary and decimal formats.  
Understanding these low-level operations is crucial not only for embedded and systems programming but also for debugging, optimization, and algorithmic problem solving.

---

### 🧱 Core Concepts You Mastered
- **Bit-level data control** — managing binary information efficiently.  
- **`std::bitset`** — a convenient abstraction for handling collections of boolean flags.  
- **Bitwise operators** — manipulating bits directly using `&`, `|`, `^`, `~`, `<<`, and `>>`.  
- **Bit masks** — selectively modifying or testing bits within an integer.  
- **Integral promotions** — understanding automatic conversions of smaller types in bitwise operations.  
- **Binary ↔ Decimal conversions** — translating between human-readable and machine-level representations.  
- **Two’s complement representation** — encoding signed integers using bit inversion and addition.  
- **Practical applications** — configuration flags, feature toggles, color channels, and state encoding.