// FunctionCard.h

#ifndef FUNCTIONCARD_H
#define FUNCTIONCARD_H

#include <string>

enum class FunctionCardType {
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

class FunctionCard {
public:
    // 構造函數
    FunctionCard(FunctionCardType type);

    // 繪製卡牌圖片到螢幕上的方法
    //void draw() const;

    // 獲取卡牌數量的方法
    int num() const;

    // 獲取卡牌類型的方法
    FunctionCardType getType() const;

    // 獲取卡牌名稱的方法
    std::string getName() const;

    // 打印卡牌信息的方法
    void printCardInfo() const;

    // 執行卡牌動作的虛擬方法
    virtual void executeAction() = 0;

protected:
    FunctionCardType type; // 卡牌類型
    std::string name;      // 卡牌名稱
    int quantity;          // 卡牌數量
    ALLEGRO_BITMAP *func = NULL;

private:
    // 加載卡牌圖片的方法（具體實現取決於使用的圖形庫）
    void loadCardImage();
};

#endif // FUNCTIONCARD_H

