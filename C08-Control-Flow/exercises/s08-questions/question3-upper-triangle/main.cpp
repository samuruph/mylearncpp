#include <iostream>

void printUpto(int outer)
{
    // loop between 1 and outer
    // note: inner will be created and destroyed at the end of the block
    while (outer >= 1)
    {
        std::cout << outer << ' ';
        --outer;
    }
} // inner destroyed here

int main()
{
    // outer loops between 1 and 5
    int outer{ 5 };
    while (outer >= 0)
    {
        // For each iteration of the outer loop, the code in the body of the loop executes once

        // This function prints numbers between 1 and outer
        printUpto(outer);

        // print a newline at the end of each row
        std::cout << '\n';
        --outer;
    }

    return 0;
}