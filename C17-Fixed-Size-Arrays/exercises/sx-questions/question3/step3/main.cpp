#include <iostream>
#include <array>

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

int main()
{
    // Print one card
    Card card { Card::five, Card::heart };
    std::cout << card << '\n';

    // Print all cards
    for (auto suit : Card::suits)
        for (auto rank : Card::nums)
            std::cout << Card { rank, suit } << ' ';
    std::cout << '\n';

    return 0;
}