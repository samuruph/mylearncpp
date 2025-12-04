#include <iostream>
#include <string>
#include <string_view>

class Ball
{
private:
    std::string m_color {""};
    double m_radius {0.0};

public:
    // Declare a constructor that uses a member initializer list (in public section)
    Ball(std::string_view color, double r)
            : m_color {color}, 
            m_radius { r }
        {
            // Constructor body (if needed)
        }
    
    // Here I can return a reference because m_color is guaranteed to outlive the reference
    // since it's a member of the class (object lifetime)
    const std::string& getColor() const 
        { 
            return m_color; 
        }

    // Here I return by value since double is a primitive type
    double getRadius() const 
        { 
            return m_radius; 
        }

};

// Declare a print function that takes a Ball object by reference 
// Not declared a a member function, to keep encapsulation robust (no access to private members)
void print(const Ball& ball)
{
    std::cout << "Ball(" << ball.getColor() 
              << ", " << ball.getRadius() 
              << ")\n";
}

int main()
{
	Ball blue { "blue", 10.0 };
	print(blue);

	Ball red { "red", 12.0 };
	print(red);

	return 0;
}