#include <iostream>

bool isEven(int x)
{
    // With ! operator, it returns true if x % 2 is 0 (even), false otherwise (odd)
    return !(x % 2);
}

int main()
{
    std::cout << "Enter an integer: ";
    int x{};
    std::cin >> x;

    if (isEven(x))
        std::cout << x << " is even\n";
    else
        std::cout << x << " is odd\n";

    return 0;
}