#include <iostream>

class Fraction
{
private:
    int m_numerator { 0 };
    int m_denominator { 1 };

public:
    // Marked as explicit to prevent implicit conversions (e.g., avoid f1.multiply(true))
    // In this way, only calls with zero, one, or two integer arguments are valid
    explicit Fraction(int numerator=0, int denominator=1)
    : m_numerator { numerator }
    , m_denominator { denominator }
    {}

    // This could be made non-member, to allow the initialization of Fraction objects in one step:
    // Fraction f1 {getFraction()};
    void getFraction()
    {
        std::cout << "Enter a value for numerator: ";
        std::cin >> m_numerator;
        std::cout << "Enter a value for denominator: ";
        std::cin >> m_denominator;
        std::cout << '\n';
    }

    Fraction multiply(const Fraction& fraction)
    {
        return Fraction { m_numerator * fraction.m_numerator, m_denominator * fraction.m_denominator };
    }

    // This could also be made a non-member function (using getters member function), 
    // so that it is more robust to changes in the class implementation
    void printFraction() const
    {
        std::cout << m_numerator << '/' << m_denominator << '\n';
    }

};

int main()
{
    Fraction f1{};
    f1.getFraction();

    Fraction f2{};
    f2.getFraction();

    std::cout << "Your fractions multiplied together: ";
    f1.multiply(f2).printFraction();

    return 0;
}