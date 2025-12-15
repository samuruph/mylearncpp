#include <iostream>
#include <vector>
#include "Random.h"

namespace WordList
{
    // Define your list of words here
    std::vector<std::string_view> words { "mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage" };

    std::string_view getRandomWord()
    {
        return words[Random::get<std::size_t>(0, words.size()-1)];
    }
}

class Session
{
    private:
        std::string_view m_word { WordList::getRandomWord() };

    public:
        std::string_view getWord() const { return m_word; }
};

void displaySessionState(const Session& session)
{   
    std::cout << "\n";
    std::cout << "The word: ";
    for ([[maybe_unused]] std::size_t i { 0 }; i < session.getWord().size() - 1; ++i)
        std::cout << "_";
    std::cout << "\n";
    return;
}

char getGuess()
{
    while (true)
    {
        std::cout << "Enter your next letter: ";

        char c{};
        std::cin >> c;

        // If user did something bad, try again
        if (!std::cin)
        {
            // Fix it
            std::cin.clear();
            std::cout << "That wasn't a valid input.  Try again.\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Clear out any extraneous input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // If the user entered an invalid char, try again
        if (c < 'a' || c > 'z')
        {
            std::cout << "That wasn't a valid input.  Try again.\n";
            continue;
        }

        return c;
    }
}

int main()
{
    std::cout << "Welcome to C++man (a variant of Hangman)\n";
    std::cout << "To win: guess the word.  To lose: run out of pluses.\n";

    Session s{};

    displaySessionState(s);
    char c { getGuess() };
    std::cout << "You guessed: " << c << '\n';

    return 0;
}