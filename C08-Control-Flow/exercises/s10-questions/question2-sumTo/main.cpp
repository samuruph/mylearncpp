#include <iostream>

int sumTo (int value) {
    int res { 0 };

    for (int i {1}; i <= value; ++i) {
        res += i;
    }
    return res;
}

int main () {
    int value {};
    std::cout << "Insert an integer value: ";
    std::cin >> value;
    std::cout << "The sum from 1 to " << value << " is: " << sumTo(value) << "\n";
    return 0;
}