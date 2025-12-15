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
        std::vector<bool> m_letterGuessed { std::vector<bool>(26) };

        std::size_t toIndex(char c) const { return static_cast<std::size_t>((c % 32)-1); }

    public:
        std::string_view getWord() const { return m_word; }

        bool isLetterGuessed(char c) const { return m_letterGuessed[toIndex(c)]; }
        void setLetterGuessed(char c) { m_letterGuessed[toIndex(c)] = true; }
};

void displaySessionState(const Session& session)
{   
    std::cout << "\n";
    std::cout << "The word: ";
    for (auto c: session.getWord())
    {
        if (session.isLetterGuessed(c))
            std::cout << c;
        else
            std::cout << "_";
    }
    std::cout << "\n";
    return;
}

char getGuess(const Session& session)
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

        // If the letter was already guessed, try again
        if (session.isLetterGuessed(c))
        {
            std::cout << "You already guessed that.  Try again.\n";
            continue;
        }

        // If we got here, this must be a valid guess
        return c;
    }
}

int main()
{
    std::cout << "Welcome to C++man (a variant of Hangman)\n";
    std::cout << "To win: guess the word.  To lose: run out of pluses.\n";

    Session session{};

    int count { 6 };

    for (int i { 0 }; i < count; ++i)
        {
            displaySessionState(session);
            char c { getGuess(session) };
            session.setLetterGuessed(c);
        }

    return 0;
}