#include <iostream>
#include <string>
#include <string_view>

class Ball
{
private:
	std::string m_color{ "black" };
	double m_radius{ 10.0 };

public:
	// Default constructor (color and radius will use default value)
	Ball()
	{
            print();
	}

	// Constructor with only radius parameter (color will use default value)
	Ball(double radius)
		: m_radius{ radius }
	{
            print();
	}

	// Constructor with only color parameter (radius will use default value)
	Ball(std::string_view color)
		: m_color{ color }
	{
            print();
	}

	// Constructor with both color and radius parameters
	Ball(std::string_view color, double radius)
		: m_color{ color }
		, m_radius{ radius }
	{
            print();
	}

    void print() const
    {
        std::cout << "Ball(" << m_color << ", " << m_radius << ")\n";
    }
};

int main()
{
    Ball def{};
    Ball blue{ "blue" };
    Ball twenty{ 20.0 };
    Ball blueTwenty{ "blue", 20.0 };

    return 0;
}