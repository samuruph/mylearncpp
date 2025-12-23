#include <iostream>

// void printArray(int array[])
// FIX:
template < typename T, std::size_t N>
void printArray(std::array<T, N> array)
{
    for (int element : array)
    {
        std::cout << element << ' ';
    }
}

int main()
{
    // int array[] { 9, 7, 5, 3, 1 };
    // C-style array decays into a pointer to the first element when passed to the function,
    // range-based for loop will not work
    // FIX:
    std::array array { 9, 7, 5, 3, 1 };  // does not decay into a pointer

    printArray(array);

    std::cout << '\n';

    return 0;
}