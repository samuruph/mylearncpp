#include <iostream>
#include "Random.h" // https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/


void ignoreLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// returns true if extraction failed, false otherwise
bool clearFailedExtraction()
{
    // Check for failed extraction
    if (!std::cin) // If the previous extraction failed
    {
        if (std::cin.eof()) // If the stream was closed
        {
            std::exit(0); // Shut down the program now
        }

        // Let's handle the failure
        std::cin.clear(); // Put us back in 'normal' operation mode.
        ignoreLine();     // And remove the bad input

        return true;
    }

    return false;
}

// Get a valid guess from the user between min and max (inclusive)
int getGuess(int min, int max)
{
    int guess{};

    while (true)
    {
        std::cout << "Enter your guess: ";
        std::cin >> guess;

        if (clearFailedExtraction())
        {
            std::cout << "Invalid input. Please enter an integer value.\n";
            continue;
        }
        ignoreLine(); // remove any extra input on the line (e.g., `43x`), takes the first integer only

        if (guess < min || guess > max)
        {
            std::cout << "Invalid guess. Please enter a number between " << min << " and " << max << ".\n";
            continue;
        }

        return guess;
    }
}

// Returns true if the user won, false if they lost
// We don't use the return value in this program, but it doesn't add complexity to have it, and may be useful in a future update
// (e.g. if we wanted to move the won/lost messages out of the function, or conditionalize other behavior based on won/lost)
bool playHiLo(int guesses, int min, int max)
{
	std::cout << "Let's play a game. I'm thinking of a number between " << min << " and " << max << ". You have " << guesses << " tries to guess what it is.\n";
	const int number { Random::get(min, max) }; // this is the number the user needs to guess

	// Loop through all of the guesses
	for (int count{ 1 }; count <= guesses; ++count)
	{
		std::cout << "Guess #" << count << ": ";

		int guess = getGuess(min, max);

		if (guess > number)
			std::cout << "Your guess is too high.\n";
		else if (guess < number)
			std::cout << "Your guess is too low.\n";
		else // guess == number, so the user won
		{
			std::cout << "Correct! You win!\n";
			return true;
		}
	}

	// The user lost
	std::cout << "Sorry, you lose. The correct number was " << number << '\n';
	return false;
}

bool playAgain()
{
	// Keep asking the user if they want to play again until they pick y or n.
	while (true)
	{
		char ch{};
		std::cout << "Would you like to play again (y/n)? ";
		std::cin >> ch;

		switch (ch)
		{
		case 'y': return true;
		case 'n': return false;
		}
	}
}

int main()
{
	constexpr int guesses { 7 }; // the user has this many guesses
	constexpr int min     { 1 };
	constexpr int max     { 100 };

	do
	{
		playHiLo(guesses, min, max);
	} while (playAgain());

	std::cout << "Thank you for playing.\n";

	return 0;
}