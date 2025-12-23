#include <array>
#include <iostream>

int main()
{
    std::cout << "Enter the number of test scores: ";
    std::size_t length{};
    std::cin >> length;

    // std::array<int, length> scores;
    // length is a non-const expression (not supported with std::array)
    // Use a std::vector in this case
    // FIX:
    std::vector<int> scores (length);  // default-initialized elements

    for (std::size_t i { 0 } ; i < length; ++i)
    {
        std::cout << "Enter score " << i << ": ";
        std::cin >> scores[i];
    }
    return 0;
}