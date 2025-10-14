/*#include "FunctionCard.h"
#include <bits/stdc++.h>
// include others if need

FunctionCard::FunctionCard(FunctionCardType type)
{
    // 根據卡牌類型設定名稱和圖片路徑
    switch (type) {
        case FunctionCardType::A_BeFruitful:
            name = "BeFruitful";
            imagePath = al_load_bitmap("./BeFruitful.png");
            quantity = 3;
            //哪一區
            //location = deck;
            //座標
            break;
        case FunctionCardType::A_FullTheEarth:
            name = "FullTheEarth";
            imagePath = al_load_bitmap("./FullTheEarth.png");
            quantity = 2;
            break;
        case FunctionCardType::A_Multiply:
            name = "Multiply";
            imagePath = al_load_bitmap("./Multiply.png");
            quantity = 2;
            break;
        case FunctionCardType::A_Golden:
            name = "Golden";
            imagePath = al_load_bitmap("./Golden.png");
            quantity = 2;
            break;
        case FunctionCardType::B_FallingRock:
            name = "FallingRock";
            imagePath = al_load_bitmap("./FallingRock.png");
            quantity = 2;
            break;
        case FunctionCardType::B_Slump:
            name = "Slump";
            imagePath = al_load_bitmap("./Slump.png");
            quantity = 2;
            break;
        case FunctionCardType::B_Plague:
            name = "Plague";
            imagePath = al_load_bitmap("./Plague.png");
            quantity = 1;
            break;
        case FunctionCardType::B_Lightning:
            name = "Lightning";
            imagePath = al_load_bitmap("./Lightning.png");
            quantity = 2;
            break;
        case FunctionCardType::B_Storm:
            name = "Storm";
            imagePath = al_load_bitmap("./Storm.png");
            quantity = 1;
            break;
        case FunctionCardType::S_Dominion:
            name = "Dominion";
            imagePath = al_load_bitmap("./Dominion.png");
            quantity = 2;
            break;
        case FunctionCardType::S_SheepDog:
            name = "SheepDog";
            imagePath = al_load_bitmap("./SheepDog.png");
            quantity = 2;
            break;
    }
}
*/
//~FunctionCard()

//void FunctionCard::draw() const {
//    std::cout << "Drawing card: " << name << std::endl;
//}
/*
int FunctionCard::num() const {
    return quantity;
}

FunctionCardType FunctionCard::getType() const {
    return type;
}

std::string FunctionCard::getName() const {
    return name;
}

void FunctionCard::printCardInfo() const {
    std::cout << "Card Name: " << name << " Type: " << static_cast<int>(type) << std::endl;
}
*/
//void FunctionCard::loadCardImage() {
//    std::cout << "Loading image from: " << imagePath << std::endl;
//}

/*
class BeFruitfulCard : public FunctionCard {
public:
    BeFruitfulCard() : FunctionCard(FunctionCardType::A_BeFruitful) {}

    void executeAction() override {
        std::cout << "BeFruitful" << std::endl;
        // add functions
    }
};
*/
/*
class BeFruitfulCard : public FunctionCard {
public:
    BeFruitfulCard() : FunctionCard(FunctionCardType::A_BeFruitful) {}

    void executeAction(Field& field, Supply& supply) override {
        if (field.hasSpace()) {
            SheepCard* selectedCard = field.selectCard(); // 玩家選擇一張卡片
            if (selectedCard && supply.removeCard(selectedCard->getType())) {
                field.addCard(*selectedCard); // 在田野區複製卡片
            }
        } else {
            std::cout << "There is not enough space in the field area！" << std::endl;
        }
    }
};


class FullTheEarthCard : public FunctionCard {
public:
    FullTheEarthCard() : FunctionCard(FunctionCardType::A_FullTheEarth) {}

    void executeAction() override {
        std::cout << "FullTheEarth " << std::endl;
        // add functions
    }
};
*/

/*
#include "FunctionCard.h"
#include <iostream>

// A_BeFruitful 卡牌類別
class A_BeFruitfulCard : public FunctionCard {
public:
    A_BeFruitfulCard() : FunctionCard(FunctionCardType::A_BeFruitful, "A_BeFruitful") {}

    void executeAction() override {
        std::cout << "Perform the act of A_BeFruitful cards." << std::endl;
        // 添加具體邏輯
    }
};

// A_FullTheEarth 卡牌類別
class A_FullTheEarthCard : public FunctionCard {
public:
    A_FullTheEarthCard() : FunctionCard(FunctionCardType::A_FullTheEarth, "A_FullTheEarth") {}

    void executeAction() override {
        std::cout << "A_Perform the act of FullTheEarth cards." << std::endl;
        // 添加具體邏輯
    }
};

// A_Multiply 卡牌類別
class A_MultiplyCard : public FunctionCard {
public:
    A_MultiplyCard() : FunctionCard(FunctionCardType::A_Multiply, "A_Multiply") {}

    void executeAction() override {
        std::cout << "Perform the act of A_Multiply cards." << std::endl;
        // 添加具體邏輯
    }
};
*/


