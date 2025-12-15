#include <cassert>
#include <iostream>
#include <string_view>
#include <type_traits> // for std::is_integral and std::is_enum
#include <vector>

namespace Items
{
    enum Type: int
    {
        health_potion,
        torch,
        arrow,
        max_items
    };
}

std::string_view getItemNamePlural(Items::Type type)
{
    switch (type)
    {
        case Items::health_potion:  return "health potions";
        case Items::torch:          return "torches";
        case Items::arrow:          return "arrows";

        default:                    return "???";
    }
}

std::string_view getItemNameSingular(Items::Type type)
{
    switch (type)
    {
        case Items::health_potion:  return "health potion";
        case Items::torch:          return "torch";
        case Items::arrow:          return "arrow";

        default:                    return "???";
    }
}

// Helper function to convert `value` into an object of type std::size_t
// UZ is the suffix for literals of type std::size_t.
template <typename T>
constexpr std::size_t toUZ(T value)
{
    // make sure T is an integral type
    static_assert(std::is_integral<T>() || std::is_enum<T>());

    return static_cast<std::size_t>(value);
}


void printInventoryItem(const std::vector<int>& inventory, Items::Type type)
{
    bool plural { inventory[toUZ(type)] != 1 };
    std::cout << "You have " << inventory[toUZ(type)] << ' ';
    std::cout << (plural ? getItemNamePlural(type) : getItemNameSingular(type)) << '\n';
}

// Inventory items should have integral quantities, so we don't need a function template here
int countTotalItems(const std::vector<int>& inventory)
{
    int sum { 0 };
    for (auto e: inventory)
        sum += e;
    return sum;
}

int main()
{
    std::vector inventory { 1, 5, 10 };
    assert(std::size(inventory) == Items::max_items); // make sure our inventory has the correct number of initializers

    // Since we can't iterate over an enumerated type using a ranged-for, we'll need to use a traditional for-loop here
    for (int i=0; i < Items::max_items; ++i)
    {
        auto item { static_cast<Items::Type>(i) };
        printInventoryItem(inventory, item);
    }

    std::cout << "You have " << countTotalItems(inventory) << " total items\n";

    return 0;
}