#include <iostream>
// #include <string>
// #include <string_view>

enum class MonsterType
{
    Ogre,
    Dragon,
    Orc,
    GiantSpider,
    Slime
};

struct Monster
{
    MonsterType type{};
    std::string name{};
    int health{};
};

// Here std::string_view works because the string literals have static storage duration, so they will exists for the lifetime of the program (also outside the function)
// We need this conversion function to print the MonsterType enum as a string, otherwise we would just get an integer value when printing, or an error.
constexpr std::string_view MonsterType2String(MonsterType type)
{
    switch(type)
    {
        case MonsterType::Ogre: return "Ogre";
        case MonsterType::Dragon: return "Dragon";
        case MonsterType::Orc: return "Orc";
        case MonsterType::GiantSpider: return "Giant Spider";
        case MonsterType::Slime: return "Slime";
        default: return "Unknown";
    }
}

void printMonster(Monster monster)
{
    std::cout << "This " << MonsterType2String(monster.type) << " is named " << monster.name << " and has " << monster.health << " health. \n";
    return; 
}

int main()
{
    Monster ogre{MonsterType::Ogre, "Torg", 145};
    Monster slime{MonsterType::Slime, "Blurp", 23};
    Monster dragon{MonsterType::Dragon, "Smaug", 300};

    printMonster(ogre);
    printMonster(slime);
    printMonster(dragon);

    return 0;
}


