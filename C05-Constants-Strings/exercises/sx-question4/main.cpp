// clang++ -std=c++17 -Wall -Wextra -Wpedantic -Werror -O2 -fcolor-diagnostics -fansi-escape-codes main.cpp
#include <iostream>
#include <string>

std::string getFullName(int id) {
    std::cout << "Enter the name of person #" << id << ": ";
    std::string fullName;
    std::getline(std::cin >> std::ws, fullName);
    return fullName;
}

int getAge(std::string_view fullName) {
    std::cout << "Enter the age of " << fullName << ": ";
    int age;
    std::cin >> age;
    return age;
}

int main() {
    // Get the full name and age of the first person
    std::string fullName1 {getFullName(1)};
    int age1 {getAge(fullName1)};
    // Get the full name and age of the second person
    std::string fullName2 {getFullName(2)};
    int age2 {getAge(fullName1)};
    // Print the older person
    if (age1 < age2) {
        std::cout << fullName2 << " (age " << age2 << " )" << " is older than " << fullName1 << " (age " << age1 << ") " << ".\n";
    } else {
        std::cout << fullName1 << " (age " << age1 << " )" << " is older than " << fullName2 << " (age " << age2 << ") " << ".\n";
    }

    return 0;
}