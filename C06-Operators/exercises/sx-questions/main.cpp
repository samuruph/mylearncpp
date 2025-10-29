#include <iostream>
#include <string>

// Write the function getQuantityPhrase() here
std::string getQuantityPhrase(int quantity) {

    if (quantity <= 0) {
        return "negative";
    } else if (quantity == 0) {
        return "no";
    } else if (quantity == 1) {
        return "single";
    } else if (quantity == 2) {
        return "a couple of";
    } else if (quantity == 3) {
        return "a few";
    } else if (quantity > 3) {
        return "many";
    } else {
        return "unknown quantity";
    }
}

// Write the function getApplesPluralized() here
std::string getApplesPluralized(int quantity) {
    if (quantity == 1) {
        return "apple";
    } else {
        return "apples";
    }
}

int main()
{
    constexpr int maryApples { 3 };
    std::cout << "Mary has " << getQuantityPhrase(maryApples) << ' ' << getApplesPluralized(maryApples) << ".\n";

    std::cout << "How many apples do you have? ";
    int numApples{};
    std::cin >> numApples;

    std::cout << "You have " << getQuantityPhrase(numApples) << ' ' << getApplesPluralized(numApples) << ".\n";

    return 0;
}