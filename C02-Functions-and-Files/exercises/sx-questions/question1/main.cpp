// clang++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O2 -fcolor-diagnostics -fansi-escape-codes -g main.cpp -o main
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

int main (){

    int a {readNumber()};
    int b {readNumber()};
    
    int sum {a + b};
    writeAnswer(sum);
    return 0;

}