#include <array>
#include <iostream>

template <typename T, std::size_t N>
void printArray(const std::array<T, N>& array)
{
    std::cout << "The array (";

    auto separator { "" };
    for (const auto& el: array)
    {
        std::cout << separator << el;
        separator = ", ";
    }
    std::cout << ") has length " << N << '\n';
}

int main()
{
    constexpr std::array arr1 { 1, 4, 9, 16 };
    printArray(arr1);

    constexpr std::array arr2 { 'h', 'e', 'l', 'l', 'o' };
    printArray(arr2);

    constexpr std::array arr3 { 11.0, 1.1, 0.5, 1.5, -5.1 };
    printArray(arr3);

    return 0;
}