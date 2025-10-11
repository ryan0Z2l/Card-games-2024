/*TODO:*/
// Complete Hero class
#ifndef HERO_H_INCLUDED
#define HERO_H_INCLUDED
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "../algif5/src/algif.h"
#include <vector>
#include <map>
#include "global.h"
#include "Monster.h"



enum class HeroState
{
    LEFT,
    RIGHT,
    FRONT,
    BACK,
    ATTACK,
};

class Hero{

public:
    Hero() = default;
    void Init();
    void Update();
    void Draw();

private:
    // move content
    int x, y;
    int counter;
    int sprite_pos;
    int speed;
    HeroState state;
    std::map< HeroState, std::vector<ALLEGRO_BITMAP*> > imgData;
    std::map< HeroState, int> imgCount;
    // attack content
    int atk_x, atk_y;
    int atk_duration;
    HeroState attack_pos;
    std::map< HeroState, ALGIF_ANIMATION*> attackGif;
};
#endif
