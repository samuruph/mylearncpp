#include <iostream>
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
    std::vector v1 { 3, 8, 2, 5, 7, 8, 3 };
    printArray(v1);

    auto m1 { findMinMaxIndices(v1) };
    std::cout << "The min element has index " << m1.first << " and value " << v1[m1.first] << '\n';
    std::cout << "The max element has index " << m1.second << " and value " << v1[m1.second] << '\n';

    std::cout << '\n';

    std::vector v2 { 5.5, 2.7, 3.3, 7.6, 1.2, 8.8, 6.6 };
    printArray(v2);

    auto m2 { findMinMaxIndices(v2) };
    std::cout << "The min element has index " << m2.first << " and value " << v2[m2.first] << '\n';
    std::cout << "The max element has index " << m2.second << " and value " << v2[m2.second] << '\n';

    return 0;
}