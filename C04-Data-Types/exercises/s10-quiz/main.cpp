// clang++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O2 -fcolor-diagnostics -fansi-escape-codes -g C04-Data-Types/exercises/s10-quiz/main.cpp
#include <iostream>

bool isDigitPrime(int x)
{
  // if x is not 2, 3, 5 or 7, it is not a prime digit
  return (x == 2 || x == 3 || x == 5 || x == 7);
}

int main()
{
  std::cout << "Enter a single digit integer: ";
  int x{ };
  std::cin >> x;

  if (isDigitPrime(x))
    std::cout << x << " is a prime digit\n";
  else
    std::cout << x << " is either not prime or not a digit\n";

  return 0;
}