#include <array>
#include <iostream>
#include <string_view>
#include "Random.h"

namespace Potion {
    enum Type {
        healing,
        mana,
        speed,
        invisibility,
        n_potions
    };

    // array of our enum
    constexpr std::array types { healing, mana, speed, invisibility };

    // use sv suffix so std::array will infer type as std::string_view
    using namespace std::string_view_literals; // for sv suffix

    constexpr std::array costs { 20, 30, 12, 50};
    constexpr std::array names { "healing"sv, "mana"sv, "speed"sv, "invisibility"sv};

    // make sure vectors and enum have the same size
    static_assert(std::size(types) == n_potions);
    static_assert(std::size(costs) == n_potions);
    static_assert(std::size(names) == n_potions);
}

class Player {
    private:
        std::string m_name {};
        std::array<int, Potion::n_potions> m_inventory {};
        int m_gold {};

    public:
        // if marked as explicit, the compiler cannot perform implicit conversions when called
        explicit Player(std::string_view name)
            : m_name {name} 
            , m_gold {Random::get<int>(80, 120)} {};

        std::string_view get_name() const { return m_name; }
        int get_inventory(Potion::Type potion_type) const { return m_inventory[potion_type]; }
        int get_gold() const { return m_gold; }

        // return true if succeed, false otherwise (not enough gold)
        bool buy(Potion::Type type) {
            if (m_gold < Potion::costs[type])
                return false;

            ++m_inventory[type];
            m_gold -= Potion::costs[type];            
            return true;
        }
};

int charNumToInt(char c)
{
    return c - '0';
}

Potion::Type selectPotion(){
    std::cout << "Enter the number of the potion you'd like to buy, or 'q' to quit: ";
    char selection {};
    while (true)
    {
        std::cin >> selection;

        // If user did something bad, try again
        if (!std::cin)
        {
            // Fix it
            std::cin.clear();
            std::cout << "That is an invalid input.  Try again: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        // Clear out any extraneous input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (selection == 'q')
            return Potion::n_potions;

        // If the user entered an invalid char, try again
        if (charNumToInt(selection) < 0 || charNumToInt(selection) >= Potion::Type::n_potions)
        {
            std::cout << "That is an invalid input.  Try again: ";
            continue;
        }

        // If we got here, this must be a valid guess
        return static_cast<Potion::Type>(charNumToInt(selection));
    }
}

void shop(Player& player) {
    while (true) {
        std::cout << "Here is our selection for today:\n";

        for (auto& p: Potion::types)
            std::cout << p << ") " << Potion::names[p] << " costs " << Potion::costs[p] << "\n";
        std::cout << "\n";

        Potion::Type selection { selectPotion() };
        if (selection == Potion::n_potions)
            return;

        bool success { player.buy(selection) };
        if (!success)
            std::cout << "You can not afford that.\n\n";
        else
            std::cout << "You purchased a potion of " << Potion::names[selection] << ".  You have " << player.get_gold() << " gold left.\n\n";

    }
}

void printInventory(Player& player)
{
    std::cout << "Your inventory contains: \n";

    for (auto p: Potion::types)
    {
        if (player.get_inventory(p) > 0)
            std::cout << player.get_inventory(p) << "x potion of " << Potion::names[p] << '\n';
    }

    std::cout << "You escaped with " << player.get_gold() << " gold remaining.\n";
}

int main() {
    std::cout << "Welcome to Roscoe's potion emporium!\n";

    std::string name {};
    std::cout << "Enter your name: ";
    std::cin >> name;

    Player player (name);

    std::cout << "Hello, " << player.get_name() << ", you have " << player.get_gold() << " gold.\n\n";

    shop(player);
    
    std::cout << '\n';

    printInventory(player);

    std::cout << "\nThanks for shopping at Roscoe's potion emporium!\n";

    return 0;
}