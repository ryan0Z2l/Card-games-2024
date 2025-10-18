#ifndef DATACENTER_H_INCLUDED
#define DATACENTER_H_INCLUDED
#include <vector>
#include <list>
#include "SheepCard.h"
#include "Card.h"

class DataCenter{
public:
    
    Deck& get_Deck()
    {
        return deck;
    }
    SheepCard& get_SheepCard()
    {
        return  sheep;
    }
private:

    std::list<SheepCard*> sheepSet;
    Deck deck;
    SheepCard sheep;
};

extern DataCenter* const DC;

#endif
