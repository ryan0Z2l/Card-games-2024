#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include <vector>
#include <algorithm>
#include <ctime>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "../algif5/src/algif.h"
#include "SheepCard.h"
enum FunctionCardType {
    A_BeFruitful,   // �h�� *3
    A_FullTheEarth, // ���a�� *2
    A_Multiply,     // �T���� *2
    A_Golden,       // �����Ͽ� *2
    B_FallingRock,  // ���� *2
    B_Slump,        // �ɸ� *2
    B_Plague,       // �̯f *1
    B_Lightning,    // ���p *2
    B_Storm,        // �P *1
    S_Dominion,     // �βv *2
    S_SheepDog      // ���Ϥ� *2
};

struct Card {
    FunctionCardType type;
    bool operator==(const Card& other) const {
        return type == other.type;
    }
};



class Deck {
private:
    std::vector<Card> cards;
    std::vector<Card> discardPile;  // �s�W��P��
    std::vector<Card> hand;
    std::vector<ALLEGRO_BITMAP*>imgData;//store photo
public:
    Deck();

    Card drawCard();

    void init();
    void Deck_initialize();

    void Draw_hand();

    void discardPile_clear();

    std::map<SheepCardType,int> event(FunctionCardType , std::vector<SheepCardType> ,SheepCard);

    void shuffle();

    void destroy();

    void discardCard(Card& card);
    void hand_clear();
    bool NoCard();
    std::vector<Card> drawHand(int numCards);

    // �s�� discardPile ���禡
    const std::vector<Card>& getDiscardPile() const {
        return discardPile;
    }
    const std::vector<Card>& getHand() const {
        return hand;
    }
};

#endif // CARD_H_INCLUDED
