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
    A_BeFruitful,   // 多產 *3
    A_FullTheEarth, // 滿地羊 *2
    A_Multiply,     // 三隻羊 *2
    A_Golden,       // 黃金羊蹄 *2
    B_FallingRock,  // 落石 *2
    B_Slump,        // 暴落 *2
    B_Plague,       // 疫病 *1
    B_Lightning,    // 落雷 *2
    B_Storm,        // 嵐 *1
    S_Dominion,     // 統率 *2
    S_SheepDog      // 牧羊犬 *2
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
    std::vector<Card> discardPile;  // 新增棄牌區
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

    // 存取 discardPile 的函式
    const std::vector<Card>& getDiscardPile() const {
        return discardPile;
    }
    const std::vector<Card>& getHand() const {
        return hand;
    }
};

#endif // CARD_H_INCLUDED
