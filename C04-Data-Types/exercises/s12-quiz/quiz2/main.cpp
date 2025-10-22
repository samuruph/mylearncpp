// clang++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O2 -fcolor-diagnostics -fansi-escape-codes -g C04-Data-Types/exercises/s12-quiz/quiz1/main.cpp
#include <iostream>

int main()
{
	std::cout << "Enter a single character: ";
	char c{};
	std::cin >> c;

	int ascii{ c };
	std::cout << "You entered '" << c << "', which has ASCII code " << ascii << ".\n";

	return 0;
}