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

    Num num {};
    Suit suit {};
};