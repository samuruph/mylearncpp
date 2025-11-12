#include <iostream>

template <int N>
constexpr int factorial()
{
    static_assert(N >= 0, "Factorial is not defined for negative numbers.");
    int prod { 1 };
    for (int i { 2 }; i <= N; ++i)
    {
        prod *= i;
    }
    return prod;
}


int main()
{
    static_assert(factorial<0>() == 1);
    static_assert(factorial<3>() == 6);
    static_assert(factorial<5>() == 120);

    factorial<-3>(); // should fail to compile

    return 0;
}

// it will give something like:
// main.cpp:6:19: error: static assertion failed due to requirement '-3 >= 0': Factorial is not defined for negative numbers.
// 6 |     static_assert(N >= 0, "Factorial is not defined for negative numbers.");