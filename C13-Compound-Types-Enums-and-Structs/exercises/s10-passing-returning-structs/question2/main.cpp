#include <iostream>

struct Fraction
{
    int numerator {0};
    int denominator {1};
};

// This return by value (and not by reference) to avoid returning a dangling reference
Fraction getFractionFromUser()
{
    Fraction tempFraction {};
    std::cout << "Enter numerator: ";
    std::cin >> tempFraction.numerator;
    std::cout << "Enter denominator: ";
    std::cin >> tempFraction.denominator;
    return tempFraction;
}

Fraction multiplyFractions(const Fraction& frac1, const Fraction& frac2)
{
    return {frac1.numerator * frac2.numerator, frac1.denominator * frac2.denominator};
}

void printFraction(const Fraction& frac)
{
    std::cout << "Fraction: " << frac.numerator << "/" << frac.denominator << '\n';
}


int main()
{
    // Get fractions from user
    Fraction frac1 {getFractionFromUser()};
    Fraction frac2 {getFractionFromUser()};

    // Multiply fractions
    Fraction result {multiplyFractions(frac1, frac2)};

    // Print result
    printFraction(result);

}