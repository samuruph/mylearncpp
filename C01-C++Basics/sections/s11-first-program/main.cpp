// clang++ -std=gnu++14 -fcolor-diagnostics -fansi-escape-codes -g C01-C++Basics/sections/s11-first-program/main.cpp -o C01-C++Basics/sections/s11-first-program/main
#include <iostream>

int main()
{      
    // Ask to enter an integer
    std::cout << "Enter an integer: ";

    // Define the integer variable x
    int x {};

    // Input the integer number from user
    std::cin >> x;

    // Print the doubled number using an expression
    std::cout << "Double that number is: " << (x * 2) << "\n";
    return 0;
}