#include <iostream>
#include <string>
#include <string_view>
#include "Random.h"

class Monster
{
public:
    enum Type
    {
        dragon, 
        goblin,
        ogre, 
        orc, 
        skeleton, 
        troll, 
        vampire, 
        zombie,
        maxMonsterTypes
    };
private:
    Type m_type {};
    std::string m_name {"unknown"};
    std::string m_roar {"unknown"};
    int m_points {};   

public:
    Monster(Type type, std::string_view name, std::string_view roar, int points)
    : m_type {type}
    , m_name {name}
    , m_roar {roar}
    , m_points {points}
    {}

    std::string getTypeString()
    {
        switch (m_type)
        {
            case dragon: return "dragon";
            case goblin: return "goblin";
            case ogre: return "ogre";
            case orc: return "orc";
            case skeleton: return "skeleton";
            case troll: return "troll";
            case vampire: return "vampire";
            case zombie: return "zombie";
            default: return "unknown";
        }
    }

    void print()
    {   
        std::cout << m_name << " the " << getTypeString();
        if (m_points <= 0)
        {
            std::cout << " is dead.\n";
            return;
        }
        std::cout << " has " << m_points << " hit points and says " << m_roar << '\n';
    }

};

namespace MonsterGenerator
{
    std::string_view getName(int n)
	{
        switch (n)
        {
            case 0:  return "Blarg";
            case 1:  return "Moog";
            case 2:  return "Pksh";
            case 3:  return "Tyrn";
            case 4:  return "Mort";
            case 5:  return "Hans";
            default: return "unknown";
        }
    }

    std::string_view getRoar(int n)
	{
        switch (n)
        {
            case 0:  return "*ROAR*";
            case 1:  return "*peep*";
            case 2:  return "*squeal*";
            case 3:  return "*whine*";
            case 4:  return "*growl*";
            case 5:  return "*burp*";
            default: return "unknown";
        }
    }

	Monster generate()
	{
		return Monster{ 
            static_cast<Monster::Type>(Random::get(0, Monster::maxMonsterTypes-1)),
            getName(Random::get(0, 5)), 
            getRoar(Random::get(0, 5)), 
            Random::get(0, 100)
            };
	}

};

int main()
{
	Monster m{ MonsterGenerator::generate() };
	m.print();

	return 0;
}