#include <iostream>

void printUpto(int outer, int maxColumns)
{
    // Print spaces for alignment first
    int spaces = maxColumns - outer;
    while (spaces > 0)
    {
        std::cout << "  ";
        --spaces;
    }

    // Then print numbers from outer down to 1
    int num = outer;
    while (num >= 1)
    {
        std::cout << num << ' ';
        --num;
    }
}

int main()
{
    const int maxColumns{5};
    int outer{1};

    while (outer <= maxColumns)
    {
        printUpto(outer, maxColumns);
        std::cout << '\n';
        ++outer;
    }

    return 0;
}
