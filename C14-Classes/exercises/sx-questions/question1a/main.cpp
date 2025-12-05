#include <iostream>

class Point2d
{
private:
    double m_x { 0.0 };
    double m_y { 0.0 };

public:
    // Default constructor
    // This is equivalent to:
    // Point2d()
    // : m_x {0.0}
    // , m_y {0.0}
    // {}
    Point2d() = default;

    // Parameterized constructor to support two arguments
    Point2d(double x, double y)
    : m_x {x}
    , m_y {y}
    {}

    void print() const
    {
        std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
        return;
    }

};

int main()
{
    Point2d first{};
    Point2d second{ 3.0, 4.0 };

    // should error if uncommented since there is no matching constructor with one argument
    // Point2d third{ 4.0 };

    first.print();
    second.print();

    return 0;
}