// clang++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O2 -fcolor-diagnostics -fansi-escape-codes main.cpp
#include <iostream>
#include <string>

std::string get_name() {
  std::cout << "Enter your full name :";
  std::string full_name {};
  std::getline(std::cin, full_name);
  return full_name;
}

int get_age() {
  std::cout << "Enter your age :";
  int age {};
  std::cin >> age;
  return age;
}

int main() {

  std::string full_name {get_name()};
  int age {get_age()};

  int result {static_cast<int>(full_name.length()) + age};
  std::cout << "Your age + length of name is: " << result << '\n';

  return 0;
}
