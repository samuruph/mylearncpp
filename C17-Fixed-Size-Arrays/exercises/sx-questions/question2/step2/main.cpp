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
};

void shop() {
    std::cout << "Here is our selection for today:\n";

    for (auto& p: Potion::types)
        std::cout << p << ") " << Potion::names[p] << " costs " << Potion::costs[p] << "\n";
    std::cout << "\n";

    return;
}

int main() {
    std::cout << "Welcome to Roscoe's potion emporium!\n";

    std::string name {};
    std::cout << "Enter your name: ";
    std::cin >> name;

    Player player (name);

    std::cout << "Hello, " << player.get_name() << ", you have " << player.get_gold() << " gold.\n\n";

    shop();

    std::cout << "Thanks for shopping at Roscoe's potion emporium!\n";
    
    return 0;
}