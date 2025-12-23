#include <iostream>
#include <array>
#include <algorithm> // for std::shuffle
#include "Random.h"
#include <cassert> // for assert

struct Card {

    enum Num {
        ace,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        jack,
        queen,
        king,
        max_nums
    };

    enum Suit {
        club,
        diamond,
        heart,
        spade,
        max_suits
    };

    // static so that they will not be instantiated every time a Card object is created, but only once in the program
    static constexpr std::array nums {ace, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king};
    static constexpr std::array suits {club, diamond, heart, spade};

    Num num {};
    Suit suit {};

    // Overload operator << to format the output properly
    friend std::ostream& operator<<(std::ostream& out, const Card &card)
    {   
        static constexpr std::array charNums { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
        static constexpr std::array charSuits { 'C', 'D', 'H', 'S' };

        out << charNums[card.num] << charSuits[card.suit];
        return out;
    }

    // returns value of the card
    int value() {
        static constexpr std::array values { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
        return values[num];
    }
};

class Deck {
    private:
        std::array<Card, 52> m_cards {};
        std::size_t m_nextCardIndex { 0 };

    public:
        Deck() {
            std::size_t i { 0 };
            for (auto suit : Card::suits)
                for (auto rank : Card::nums)
                    m_cards[i++] = Card { rank, suit};
        };

        Card dealCard() {
            assert(m_nextCardIndex != 52 && "Deck::dealCard ran out of cards");
            // use post-increment, so that you return card at m_nextCardIndex, and after you increment
            return m_cards[m_nextCardIndex++];
        }

        void shuffle() {
            // Put this line in your shuffle function to shuffle m_cards using the Random::mt Mersenne Twister
            // This will rearrange all the Cards in the deck randomly
            std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
            return;
        }

};

struct Player {
    int score {};
};

bool playBlackjack() {
    Deck deck {};
    deck.shuffle();

    Player dealer { deck.dealCard().value() };
    std::cout << "The dealer is showing: " << dealer.score << '\n';

    Player player { deck.dealCard().value() };
    player.score += deck.dealCard().value();
    std::cout << "You have score: " << player.score << '\n';

    if (player.score > dealer.score)
        return true;
    else
        return false;
}

int main()
{
    if (playBlackjack()) {
        std::cout << "You win!\n";
    }
    else {
        std::cout << "You lose!\n";
    }

    return 0;
}