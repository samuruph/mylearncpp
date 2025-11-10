#include <iostream>

namespace constants
{
    constexpr double pi { 3.14159 };
}

using Degrees = double; // Type alias for better code readability
using Radians = double; // Type alias for better code readability

Radians convertToRadians(Degrees degrees)
{
    return degrees * constants::pi / 180;
}

int main()
{   
    std::cout << "Enter a number of degrees: ";
    Degrees degrees{};
    std::cin >> degrees;

    Radians radians { convertToRadians(degrees) };
    std::cout << degrees << " degrees is " << radians << " radians.\n";

    return 0;
}

// Question 2b) radians = degrees will compile because both Degrees and Radians are type aliases for double, making them compatible types for assignment.