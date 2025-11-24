
namespace Monster
{
    enum MonsterType
    {
        orc,
        goblin,
        troll,
        ogre,
        skeleton,
    };
}

int main()
{
    [[maybe_unused]] Monster::MonsterType myMonster{Monster::troll};
    
    return 0;
}