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
    const int startX = 60;  // �_�l�� x �y��
    const int startY = 250;  // �_�l�� y �y��
    int now_pos =0;
    for (const auto& entry : Field) {
        SheepCardType type = entry.first;
        int num = entry.second;

        // �ˬd�O�_���������Ϲ��ƾ�
        //if (static_cast<size_t>(type) < imgData.size()) {
            // ø�s�����ƶq���ϥd�Ϲ�
            for (int i = 0; i < num; ++i) {
                 int x = startX + now_pos * 160;  // �վ� x �y�ХH����|
                 int y = startY;
                now_pos++;
                // ø�s�ϥd�Ϲ�
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
