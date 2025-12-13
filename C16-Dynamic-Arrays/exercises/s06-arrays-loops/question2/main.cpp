#include <iostream>
#include <vector>

// Implement printArray() here
template <typename T>
void printArray(std::vector<T>& arr)
{
    for(std::size_t i = 0; i < arr.size(); ++i)
    {
        std::cout << arr[i] << ' ';
    }

    if (arr.size() > 0)
        std::cout << '\n';
    return;
}

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    printArray(arr); // use function template to print array

    return 0;
}