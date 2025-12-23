#include <array>
#include <iostream>
#include <string>

struct Item {
    std::string_view name {};
    int gold {};
};

template <std::size_t N>
void printStore(const std::array<Item, N>& arr)
{
    for (const auto& item: arr)
    {
        std::cout << "A " << item.name << " costs " << item.gold << " gold.\n";
    }
}

int main()
{
    constexpr std::array<Item, 4> store {{ // No CTAD, must use double braces
        {"sword", 5},
        {"dagger", 3},
        {"club", 2},
        {"spear", 7}
}};
    printStore(store);

    return 0;
}