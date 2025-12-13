// h/t to reader Waldo for suggesting this quiz
#include <cassert>
#include <iostream>
#include <string_view>
#include <vector>

void fizzbuzz(int count)
{
	// We'll make these static so we only have to do initialization once
	static const std::vector divisors                { 3, 5, 7, 11, 13, 17, 19 };
	static const std::vector<std::string_view> words { "fizz", "buzz", "pop", "bang", "jazz", "pow", "boom" };
	assert(std::size(divisors) == std::size(words) && "fizzbuzz: array sizes don't match");

	// Loop through each number between 1 and count (inclusive)
	for (int i{ 1 }; i <= count; ++i)
	{
		bool printed{ false };

		// Check the current number against each possible divisor
		for (std::size_t j{ 0 }; j < divisors.size(); ++j)
		{
			if (i % divisors[j] == 0)
			{
				std::cout << words[j];
				printed = true;
			}
		}

		// If there were no divisors
		if (!printed)
			std::cout << i;

		std::cout << '\n';
	}
}

int main()
{
	fizzbuzz(150);

	return 0;
}