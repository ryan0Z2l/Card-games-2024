#include "Card.h"
#include <iostream>
#include "global.h"
Deck::Deck()
{
    Deck_initialize();
}
void Deck::Deck_initialize()
{
    cards.clear();
    // 放入每種型態註解的數量的牌
    for (int i = 0; i < 3; ++i) { cards.push_back({ A_BeFruitful }); }
    for (int i = 0; i < 2; ++i) { cards.push_back({ A_FullTheEarth }); }
    for (int i = 0; i < 2; ++i) { cards.push_back({ A_Multiply }); }
    for (int i = 0; i < 2; ++i) { cards.push_back({ A_Golden }); }
    for (int i = 0; i < 2; ++i) { cards.push_back({ B_FallingRock }); }
    for (int i = 0; i < 2; ++i) { cards.push_back({ B_Slump }); }
    cards.push_back({ B_Plague });
    for (int i = 0; i < 2; ++i) { cards.push_back({ B_Lightning }); }
    cards.push_back({ B_Storm });
    for (int i = 0; i < 2; ++i) { cards.push_back({ S_Dominion }); }
    for (int i = 0; i < 2; ++i) { cards.push_back({ S_SheepDog }); }

    shuffle();
}
void Deck::shuffle() {
    std::srand(static_cast<unsigned int>(std::time(0)));
    std::random_shuffle(cards.begin(), cards.end());
}

std::vector<Card> Deck::drawHand(int numCards) {

    for (int i = 0; i < numCards; ++i) {
        hand.push_back(cards.back());
        cards.pop_back();
    }
    std::cout << "Current Hand: ";
        for (const auto& card : hand) {
            std::cout << card.type << " ";
        }
         std::cout << "Current Deck: ";
        for (const auto& card : cards) {
            std::cout << card.type << " ";
        }
        std::cout<<std::endl;
    return hand;
}

Card Deck::drawCard() {
    Card card = cards.back();
    cards.pop_back();
    return card;
}

void Deck::discardCard(Card& card) {
    auto it = std::find(hand.begin(), hand.end(), card);

    if (it != hand.end()) {
        // 將要丟棄的牌放入棄牌區
        discardPile.push_back(*it);

        // 從手牌中移除丟棄的牌
        hand.erase(it);

        // 抽一張新牌進入下一回合
        if(!cards.empty())
        {
             Card newCard = drawCard();
            hand.push_back(newCard);
        }


        // 顯示當前的手牌、該回合丟棄的牌和棄牌區的狀態
        std::cout << "Current Deck: ";
        for (const auto& card : cards) {
            std::cout << card.type << " ";
        }
        std::cout << "\nDiscarded Card: " << card.type << "\n";
        std::cout << "Discard Pile: ";
        for (const auto& card : discardPile) {
            std::cout << card.type << " ";
        }
        std::cout << "\n\n";
    }
}
void  Deck::discardPile_clear()
{
    discardPile.clear();
}

void Deck::init()
{
    char buffer[50];
    for(int i =0;i<11;i++)
    {
        sprintf(buffer,"./Function/%s.png",FunctionClass[i]);
        ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
        imgData.push_back(img);
    }

}

void Deck::Draw_hand() {
    const int cardWidth = 160;  // 假設每張牌的寬度為 160
    const int startY = 450;     // 起始的 y 座標

    for (int i = 0; i < hand.size(); ++i) {

        int x = 200 + i * cardWidth;

        // 繪製牌的圖像
        al_draw_bitmap(imgData[hand[i].type], x, startY, 0);
    }
}
void Deck::destroy()
{
    for (ALLEGRO_BITMAP* img : imgData) {
        if (img) {
            al_destroy_bitmap(img);
        }
    }
    imgData.clear();
}
bool Deck::NoCard()
{
    if(hand.empty())return true;
    return false;
}
void Deck::hand_clear()
{
    hand.clear();
}
std::map<SheepCardType,int> Deck::event(FunctionCardType _type, std::vector<SheepCardType> field_select,SheepCard sc)
{
    std::cout << "function type = " << _type << std::endl;
    for(auto i = field_select.begin(); i != field_select.end(); i++) {
        std::cout<< *i << " ";
    }
    std::cout << std::endl;
    // std::cout<<field_select[0]<<_type;
    std::map<SheepCardType,int>&field = sc.getField();
    int total = 0;//compute the current used block
    for(auto entry: field)
    {
        total+= entry.second;
    }
    switch(_type)
    {
        case A_BeFruitful:

            if(total<7)
            {
                field[field_select[0]]++;
            }
            break;

        case A_FullTheEarth:
            for(int i = 7-total;i>0;i--)
            {
                field[Type1]++;
            }
            break;

        case A_Multiply:

            if(total<7)
            {
                field[Type3]++;
            }

            break;

        case A_Golden:
        {
            int largest = 0;
            SheepCardType cardSequence[Num_sheepType] = {Type1, Type3, Type10, Type30, Type100, Type300, Type1000};
            for(int i = 6; i >= 0; i--)
            {
                if(field[cardSequence[i]]>0)
                {
                    largest = i;
                    break;
                }

            }
            std::cout<<largest<<std::endl;
            if(largest>0)
            {

            field[cardSequence[largest]]+=field[cardSequence[largest-1]];
                for(int i=largest-1 ;i>=1;i--){
                     field[cardSequence[i]]= field[cardSequence[i-1]];

                }
                 field[cardSequence[0]]=0;
            }

            break;

        }
        case B_FallingRock:

            	{{
             if (field[Type1] > 0)
                {
                    field[Type1]--;

                }
                else if (field[Type3] > 0)
                {
                    field[Type3]--;

                }
                else if (field[Type10] > 0)
                {
                    field[Type10]--;

                }
                else if (field[Type30] > 0)
                {
                    field[Type30]--;

                }
                else if (field[Type100] > 0)
                {
                    field[Type100]--;

                }
                else if (field[Type300] > 0)
                {
                    field[Type300]--;

                }
                else if (field[Type1000] > 0)
                {
                    field[Type1000]--;

                }
        }

        break;
        }
        case B_Slump:
        {
            int totalToDecrease = total / 2;

            while (totalToDecrease > 0)
            {
                if (field[Type1] > 0)
                {
                    field[Type1]--;
                    totalToDecrease--;
                }
                else if (field[Type3] > 0)
                {
                    field[Type3]--;
                    totalToDecrease--;
                }
                else if (field[Type10] > 0)
                {
                    field[Type10]--;
                    totalToDecrease--;
                }
                else if (field[Type30] > 0)
                {
                    field[Type30]--;
                    totalToDecrease--;
                }
                else if (field[Type100] > 0)
                {
                    field[Type100]--;
                    totalToDecrease--;
                }
                else if (field[Type300] > 0)
                {
                    field[Type300]--;
                    totalToDecrease--;
                }
                else if (field[Type1000] > 0)
                {
                    field[Type1000]--;
                    totalToDecrease--;
                }

            }

            break;
        }

        case B_Plague:
            {
                SheepCardType cardSequence[Num_sheepType] = {Type1, Type3, Type10, Type30, Type100, Type300, Type1000};
                for(int i= 0 ;i<Num_sheepType-1;i++)
                {
                    field[cardSequence[i]] = field[cardSequence[i + 1]];
                }
                break;
            }


        case B_Lightning:
            {


                if (field[Type1000] > 0)
            {
                field[Type1000]--;

            }
            else if (field[Type300] > 0)
            {
                field[Type300]--;

            }
            else if (field[Type100] > 0)
            {
                field[Type100]--;

            }
            else if (field[Type30] > 0)
            {
                field[Type30]--;

            }
            else if (field[Type10] > 0)
            {
                field[Type10]--;

            }
            else if (field[Type3] > 0)
            {
                field[Type3]--;

            }
            else if (field[Type1] > 0)
            {
                field[Type1]--;

            }
             break;
        }
        case B_Storm:
        {
           int totalToDecrease = 2;

            while (totalToDecrease > 0)
            {
                if (field[Type1] > 0)
                {
                    field[Type1]--;
                    totalToDecrease--;

                }
                else if (field[Type3] > 0)
                {
                    field[Type3]--;
                    totalToDecrease--;

                }
                else if (field[Type10] > 0)
                {
                    field[Type10]--;
                    totalToDecrease--;

                }
                else if (field[Type30] > 0)
                {
                    field[Type30]--;
                    totalToDecrease--;

                }
                else if (field[Type100] > 0)
                {
                    field[Type100]--;
                    totalToDecrease--;

                }
                else if (field[Type300] > 0)
                {
                    field[Type300]--;
                    totalToDecrease--;

                }
                else if (field[Type1000] > 0)
                {
                    field[Type1000]--;
                    totalToDecrease--;

                }

            }

            break;
        }
        case S_Dominion:
            int sum =0 ;
            int i = 1;
            for(auto entry: field_select)
            {
               if(entry == 0)
               {
                   sum+=1;
                   field[Type1]--;
               }
               else if(entry == 1)
               {
                   sum+=3;
                   field[Type3]--;
               }
                else if(entry == 2)
               {
                   sum+=10;
                   field[Type10]--;
               }
                else if(entry == 3)
               {
                   sum+=30;
                   field[Type30]--;
               }
                else if(entry == 4)
               {
                   sum+=100;
                   field[Type100]--;
               }
                else if(entry == 5)
               {
                   sum+=300;
                   field[Type300]--;
               }
            }
            if(sum>=1 && sum <3) field[Type1]++;
            else if(sum>=3 && sum<10) field[Type3]++;
            else if(sum>=10 && sum<30) field[Type10]++;
            else if(sum>=30 && sum<100) field[Type30]++;
            else if(sum>=100 && sum<300) field[Type100]++;
            else if(sum>=300 && sum<1000) field[Type300]++;
            else if(sum>=1000) field[Type1000]++;
            break;
    }
    std::cout << "Current contents of the field map:" << std::endl;
    for (auto entry : field)
    {
        std::cout << "Type: " << entry.first << ", Quantity: " << entry.second << std::endl;
    }

    return field;
}
