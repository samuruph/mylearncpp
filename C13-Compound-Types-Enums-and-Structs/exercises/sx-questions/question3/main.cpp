// clang++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O2 -fcolor-diagnostics -fansi-escape-codes -g main.cpp
#include <iostream>

template <typename T>
struct Triad
{
    T a {};
    T b {};
    T c {};
};

// If you use C++17, provide a deduction guide 
// If using C++20, not needed
template <typename T>
Triad(T, T, T) -> Triad<T>;

template <typename T>
void print(const T& triad)
{
    std::cout << "[ " << triad.a << ", " << triad.b << ", " << triad.c << " ]\n";
    return;
}


int main()
{
	Triad t1{ 1, 2, 3 }; // note: uses CTAD to deduce template arguments
	print(t1);

	Triad t2{ 1.2, 3.4, 5.6 }; // note: uses CTAD to deduce template arguments
	print(t2);

	return 0;
}
