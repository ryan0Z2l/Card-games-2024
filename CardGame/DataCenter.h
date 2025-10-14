#ifndef DATACENTER_H_INCLUDED
#define DATACENTER_H_INCLUDED
#include <vector>
#include <list>
#include "Monster.h"
#include "Tower.h"
#include "Hero.h"
#include "SheepCard.h"
#include "Card.h"

class DataCenter{
public:
    std::vector<Monster*>& get_Monster()
    {
        return monsterSet;
    }
    std::list<Tower*>& get_Tower()
    {
        return towerSet;
    }
    Hero& get_Hero()
    {
        return dragonite;
    }
    Deck& get_Deck()
    {
        return deck;
    }
    SheepCard& get_SheepCard()
    {
        return  sheep;
    }
private:
    std::vector<Monster*> monsterSet;
    std::list<Tower*> towerSet;
    std::list<SheepCard*> sheepSet;
    Hero dragonite;
    Deck deck;
    SheepCard sheep;
};

extern DataCenter* const DC;

#endif
