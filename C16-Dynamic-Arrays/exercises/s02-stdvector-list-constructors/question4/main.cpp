#include <iostream>
#include <vector>

int main()
{   
    std::vector<int> values (3);
    std::cout << "Enter 3 integers: ";
    std::cin >> values[0] >> values[1] >> values[2];

    std::cout << "The sum is: " << values[0] + values[1] + values[2] << "\n";
    std::cout << "The product is: " << values[0] * values[1] * values[2] << "\n";

    return 0;
}