// clang++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O2 -fcolor-diagnostics -fansi-escape-codes -g C04-Data-Types/exercises/s12-quiz/quiz1/main.cpp
#include <iostream>

int main()
{   
    double a {};
    double b {};
    char op {};
    double tot {};
	std::cout << "Enter a double value: ";
	std::cin >> a;
    std::cout << "Enter a double value: ";
	std::cin >> b;

    std::cout << "Enter +, -, * or /: ";
	std::cin >> op;

    if (op == '+') {
        tot = a + b;
    } else if (op == '-') {
        tot = a - b;
    } else if (op == '*') {
        tot = a * b;
    } else if (op == '/') {
        tot = a / b;
    } else {
        std::cout << "The selected operation is not supported \n";
        return -1;
    }

    std::cout << a << " " << op << " " << b << " = " << tot << "\n";

	return 0;
}