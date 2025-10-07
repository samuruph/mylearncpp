// /usr/bin/clang++ -std=gnu++14 -fcolor-diagnostics -fansi-escape-codes -g C01-C++Basics/sections/sx-summary-quiz/main.cpp -o C01-C++Basics/sections/sx-summary-quiz/main
#include <iostream>

int main() 
{
    int a {};
    int b {};

    std::cout << "Enter an integer: ";
    std::cin >> a;

    std::cout << "Enter another integer: ";
    std::cin >> b;

    std::cout << a << " + " << b << " is " << (a + b) << ".\n";
    std::cout << a << " - " << b << " is " << (a - b) << ".\n";
}