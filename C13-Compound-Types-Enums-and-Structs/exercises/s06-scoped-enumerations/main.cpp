#include <iostream>
#include <string_view>

enum class Animal 
{ 
    pig,
    chicken,
    goat,
    cat,
    dog,
    duck
};

std::string_view getAnimalName(Animal animal)
{   
    switch (animal)
    {
        case Animal::pig: return "pig";
        case Animal::chicken: return "chicken";
        case Animal::goat: return "goat";
        case Animal::cat: return "cat";
        case Animal::dog: return "dog";
        case Animal::duck: return "duck";
        default: return "unknown";
    }
}

void printNumberOfLegs(Animal animal)
{   
    int nLegs {0};
    switch (animal)
    {
        case Animal::pig:
        case Animal::goat:
        case Animal::cat:
        case Animal::dog:
            nLegs = 4;
            break;
        case Animal::chicken:
        case Animal::duck:
            nLegs = 2;
            break;
        default:
            break;
    }
    if (nLegs == 0)
    {
        std::cout << "Unknown number of legs for animal type.\n";
        return;
    }
    std::cout << "A " << getAnimalName(animal) << " has " << nLegs << " legs.\n";
}

int main()
{
    printNumberOfLegs(Animal::cat);
    printNumberOfLegs(Animal::chicken);

    return 0;
}