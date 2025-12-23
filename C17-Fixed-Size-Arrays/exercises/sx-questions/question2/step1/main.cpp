#include <array>
#include <iostream>
#include <string_view>

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

void shop() {
    std::cout << "Here is our selection for today:\n";

    for (auto& p: Potion::types)
        std::cout << p << ") " << Potion::names[p] << " costs " << Potion::costs[p] << "\n";

    return;
}

int main() {
    shop();
    
    return 0;
}