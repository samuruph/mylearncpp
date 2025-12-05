#include <iostream>
#include <string>

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

int main()
{
	Monster skeleton{ Monster::skeleton, "Bones", "*rattle*", 4 };
	skeleton.print();

	Monster vampire{ Monster::vampire, "Nibblez", "*hiss*", 0 };
	vampire.print();

	return 0;
}