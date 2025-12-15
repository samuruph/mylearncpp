#include <iostream>
#include <limits>
#include <vector>

template <typename T>
std::pair<std::size_t, std::size_t> findMinMaxIndices(const std::vector<T>& v)
{
    // Assume element 0 is the minimum and the maximum
    std::size_t minIndex { 0 };
    std::size_t maxIndex { 0 };

    // Look through the remaining elements to see if we can find a smaller or larger element
    for (std::size_t index { 1 }; index < v.size(); ++index)
    {
        if (v[index] < v[minIndex])
            minIndex = index;
        if (v[index] > v[maxIndex])
            maxIndex = index;
    }

    return { minIndex, maxIndex };
}

template <typename T>
void printArray(const std::vector<T>& v)
{
    bool comma { false };
    std::cout << "With array ( ";
    for (const auto& e: v)
    {
        if (comma)
            std::cout << ", ";

        std::cout << e;
        comma = true;
    }
    std::cout << " ):\n";
}

int main()
{
    std::vector<int> v1 { };
    std::cout << "Enter numbers to add (use -1 to stop): ";

    while (true)
    {
        int input{};
        std::cin >> input;
        if (input == -1)
            break;

        if (!std::cin) // if the previous extraction failed
        {
            std::cin.clear(); // put us back in 'normal' operation mode
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // and remove the bad input
            continue;
        }

        v1.push_back(input);
    }

    // If the array is empty
    if (v1.size() == 0)
    {
        std::cout << "The array has no elements\n";
    }
    else
    {
        printArray(v1);

        auto m1 { findMinMaxIndices(v1) };
        std::cout << "The min element has index " << m1.first << " and value " << v1[m1.first] << '\n';
        std::cout << "The max element has index " << m1.second << " and value " << v1[m1.second] << '\n';
    }

    return 0;
}