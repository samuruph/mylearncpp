#include <iostream>
#include <vector>

int main()
{
    std::vector<char> word {'h', 'e', 'l', 'l', 'o'};
    std::cout << "The array has " << word.size() << " elements. \n";
    std::cout << word[1] << word.at(1) << "\n";
    return 0;
}

// a) What is size_type and what is it used for?
// size_type is a nested typedef that is an alias for the type used to store the length (and indices, if supported) of a standard library container.

// b) What type does size_type default to? Is it signed or unsigned?
// std::size_t, which is an unsigned type.

// c) Which functions to get the length of a container return size_type?
// The size() member function and std::size both return size_type.