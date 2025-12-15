#include <iostream>
#include <vector>
#include <cassert>

namespace Items
{
    enum Type {
        health_potion,
        torch,
        arrow,
        max_items
    };
}

// Inventory items should have integral quantities, so we don't need a function template here
int countTotalItems(const std::vector<int>& inventory)
{
    int sum { 0 };
    for (auto el: inventory)
        sum += el;
    return sum;
}

int main()
{
    std::vector inventory {1, 5, 10};
    // Make sure our inventory has the correct number of initializers
    assert(inventory.size() == Items::max_items);
    std::cout << "You have " << countTotalItems(inventory) << " total items.\n";

    return 0;
}
