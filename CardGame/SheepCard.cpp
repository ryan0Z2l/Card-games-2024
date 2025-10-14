#include "SheepCard.h"
#include <iostream>

SheepCard::SheepCard()
{
    for (int i = 0; i < 7; ++i) {
    Supply.push_back({Type1});
    Supply.push_back({Type3});
    Supply.push_back({Type10});
    Supply.push_back({Type30});
    Supply.push_back({Type100});
    Supply.push_back({Type300});
    Supply.push_back({Type1000});
    }
}


void SheepCard::Draw_field()
{
    const int startX = 60;  // 起始的 x 座標
    const int startY = 250;  // 起始的 y 座標
    int now_pos =0;
    for (const auto& entry : Field) {
        SheepCardType type = entry.first;
        int num = entry.second;

        // 檢查是否有對應的圖像數據
        //if (static_cast<size_t>(type) < imgData.size()) {
            // 繪製相應數量的羊卡圖像
            for (int i = 0; i < num; ++i) {
                 int x = startX + now_pos * 160;  // 調整 x 座標以防止重疊
                 int y = startY;
                now_pos++;
                // 繪製羊卡圖像
                al_draw_bitmap(imgData[type], x, y, 0);
            }
       // }
    }
}
void SheepCard::init()
{
    char buffer[50];
    for(int i = 0 ;i<7 ;i++)
    {
        sprintf(buffer, "./sheep/%s_sheep.png", SheepClass[i]);
        ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
        imgData.push_back(img);
    }

}
void SheepCard::destroy()
{
    for (ALLEGRO_BITMAP* img : imgData) {
        if (img) {
            al_destroy_bitmap(img);
        }
    }
    imgData.clear();
}

void SheepCard::Field_initialize()
{
    Field.clear();
    Field[Type1]=1;
}
bool SheepCard::No_Sheep()
{
    for(auto entry: Field)
    {
        if(entry.second!=0)
            return false;
    }
    return true;
}
bool SheepCard::Victory()
{
    if(Field[Type10]>=1)return true;
    else return false;
}
