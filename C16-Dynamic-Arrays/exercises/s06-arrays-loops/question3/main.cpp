#include <iostream>
#include <limits>
#include <vector>

int getValidNumber()
{
    // First, read in valid input from user
    int num {};
    do
    {
        std::cout << "Enter a number between 1 and 9: ";
        std::cin >> num;

        // if the user entered an invalid character
        if (!std::cin)
            std::cin.clear(); // reset any error flags

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore any extra characters in the input buffer (regardless of whether we had an error or not)

    } while (num < 1 || num > 9);

    return num;
}

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

template <typename T>
int findIndex(std::vector<T>& array, T value)
{
    for (std::size_t index {0}; index < array.size(); ++index)
    {
        if (array[index] == value)
        {
            return static_cast<int>(index);
        }
    }
    return -1; // value not found
}

int main()
{
    std::vector arr{ 4, 6, 7, 3, 8, 2, 1, 9 };

    int num { getValidNumber() };

    printArray(arr);

    int index { findIndex(arr, num) };

    if (index != -1)
        std::cout << "The number " << num << " has index " << index << '\n';
    else
        std::cout << "The number " << num << " was not found\n";

    return 0;
}