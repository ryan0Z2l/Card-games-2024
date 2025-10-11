#ifndef SHEEPCARD_H_INCLUDED
#define SHEEPCARD_H_INCLUDED

#include<map>
#include<vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "global.h"
enum SheepCardType {
        Type1,
        Type3,
        Type10,
        Type30,
        Type100,
        Type300,
        Type1000
    };

struct Sheep {
    SheepCardType type;
    bool operator==(const Sheep& other) const {
        return type == other.type;
    }
};
class SheepCard {
public:
    SheepCard();
    // Implement the pure virtual functions from the base class
    void Draw_field() ;//draw sheep on the field
    void init();//load image
    void destroy();
    void Field_initialize();
    bool No_Sheep();
    bool Victory();
    std::map<SheepCardType,int>& getField() {
        return Field;
    }
private:
    std::vector<ALLEGRO_BITMAP*>imgData;
    std::map<SheepCardType,int> Field;
    std::vector<Sheep>Supply;
};

#endif // SHEEPCARD_H_INCLUDED
