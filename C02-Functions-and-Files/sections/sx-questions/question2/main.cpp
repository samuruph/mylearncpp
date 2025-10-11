// clang++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O2 -fcolor-diagnostics -fansi-escape-codes -g main.cpp io.cpp -o main
#include <iostream>

int readNumber();

void writeAnswer(int x);

int main (){

    int a {readNumber()};
    int b {readNumber()};
    
    int sum {a + b};
    writeAnswer(sum);

    return 0;

}