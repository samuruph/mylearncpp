// clang++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O2 -fcolor-diagnostics -fansi-escape-codes -g main.cpp get_integer.cpp -o main
#include <iostream>

int getInteger();

int main()
{
	int x{ getInteger() };
	int y{ getInteger() };

	std::cout << x << " + " << y << " is " << x + y << '\n';
	return 0;
}