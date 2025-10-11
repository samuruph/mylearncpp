#include <iostream>

int readNumber() {
    int x {};
    std::cout << "Insert a number: \n";
    std::cin >> x;
    return x;
}

void writeAnswer(int x) {
    std::cout << "The return is: " << x << "\n";
}