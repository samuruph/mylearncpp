// clang++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O2 -fcolor-diagnostics -fansi-escape-codes -g C04-Data-Types/exercises/s12-quiz/quiz1/main.cpp
#include <iostream>

int main()
{
  std::cout << "Enter a single character: ";
  char ch{ };
  std::cin >> ch;

  int ch_ascii{ };
  ch_ascii = static_cast<int>(ch);

  std::cout << "You entered '" << ch << "', which has ASCII code " << ch_ascii << "\n";

  return 0;
}