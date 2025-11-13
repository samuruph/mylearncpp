#include <iostream>

// Not constexpr because I/O can only be done at runtime
//
// gets tower height from user and returns it
double getTowerHeight()
{
	std::cout << "Enter the height of the tower in meters: ";
	double towerHeight{};
	std::cin >> towerHeight;
	return towerHeight;
}

// Constexpr because it just calculates a value using constant values and parameters
// Reminder: a constexpr function can be evaluated at compile time or runtime
// - If its arguements are constant expressions, it can be evaluated at compile time
// - If its arguments are not constant expressions, it is evaluated at runtime
// In this case, towerHeight and seconds are not constant expressions (they are determined at runtime),
// so this function will be evaluated at runtime
//
// Returns ball height from ground after "seconds" seconds
constexpr double calculateBallHeight(double towerHeight, int seconds)
{
	constexpr double gravity{ 9.8 };

	// Using formula: [ s = u * t + (a * t^2) / 2 ], here u(initial velocity) = 0
    // These variables can't be constexpr since their initializers aren't constant expressions
	const double distanceFallen{ (gravity * (seconds * seconds)) / 2.0 };
	const double currentHeight{ towerHeight - distanceFallen };

	return currentHeight;
}

// Not constexpr because I/O can only be done at runtime
//
// Prints ball height above ground
void printBallHeight(double ballHeight, int seconds)
{
	if (ballHeight > 0.0)
		std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
	else
		std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
}

// Not constexpr because I/O can only be done at runtime
//
// Calculates the current ball height and then prints it
// This is a helper function to make it easier to do this
void printCalculatedBallHeight(double towerHeight, int seconds)
{
	double ballHeight{ calculateBallHeight(towerHeight, seconds) };
	printBallHeight(ballHeight, seconds);
}

int main()
{
	double towerHeight{ getTowerHeight() };

	printCalculatedBallHeight(towerHeight, 0);
	printCalculatedBallHeight(towerHeight, 1);
	printCalculatedBallHeight(towerHeight, 2);
	printCalculatedBallHeight(towerHeight, 3);
	printCalculatedBallHeight(towerHeight, 4);
	printCalculatedBallHeight(towerHeight, 5);

	return 0;
}