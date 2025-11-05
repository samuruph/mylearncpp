#include <iostream>

void fizzbuzz (int value) {

    for (int i {1}; i <= value; ++i) {
        if (i % 3 == 0 && i % 5 == 0) {
            std::cout << "fizzbuzz";
        } else if (i % 3 == 0) {
            std::cout << "fizz";
        } else if (i % 5 == 0) {
            std::cout << "buzz";
        } else {
            std::cout << i;
        }
        std::cout << "\n";
    }
}

int main () {
    int value {};
    std::cout << "Insert an integer value: ";
    std::cin >> value;
    fizzbuzz(value);
    return 0;
}