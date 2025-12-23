#include <iostream>
#include <limits>
#include <vector>

constexpr int perfectSquares[] {0, 1, 4, 9, 16, 25, 36, 49, 64, 81};

bool isPerfectSquare(int n)
{
    for (auto& square: perfectSquares)
    {
        if (n == square)
            return true;
    }
    return false;
}

int main()
{
    while (true)
    {   
        std::cout << "Enter a single digit integer, or -1 to quit: ";
        
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

        if (isPerfectSquare(input))
            std::cout << input << " is a perfect square.\n";
        else
            std::cout << input << " is not a perfect square.\n";
    }

    std::cout << "Bye\n";

    return 0;
}

