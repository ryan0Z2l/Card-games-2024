/*TODO:*/
// Complete Hero class

#include "Hero.h"
#include "DataCenter.h"
const char direction_name[][10] = {"left", "right", "front", "back"};
const int draw_frequency = 10;
void Hero::Init(){


    imgCount[HeroState::LEFT] = 2;
    imgCount[HeroState::RIGHT] = 2;
    imgCount[HeroState::FRONT] = 2;
    imgCount[HeroState::BACK] = 2;

    char buffer[50];
    for(int i = 0; i < 4; i++)
    {
        for(int j = 1; j <= imgCount[ static_cast<HeroState>(i) ]; j++)
        {
            sprintf(buffer, "./Hero/dragonite_%s_%d.png", direction_name[i], j);
            ALLEGRO_BITMAP *img = al_load_bitmap(buffer);
            if(img)
                imgData[static_cast<HeroState>(i) ].push_back(img);
            else
                printf("[Hero] no move image!!\n");
        }
    }
    for(int i = 0 ; i < 4 ; i++){
        sprintf(buffer, "./Hero/hyperbeam_%s.gif", direction_name[i]);
        ALGIF_ANIMATION* gif = algif_load_animation(buffer);
        gif->loop = 1;
        if(gif)
            attackGif[static_cast<HeroState>(i)] = gif, printf("done\n");
        else
            printf("[Hero] no gif!!\n");
    }
    x = window_width / 2;
    y = window_height / 2;
    counter = 0;
    sprite_pos = 0;
    speed = 5;
    state = HeroState::FRONT;
    attack_pos = HeroState::FRONT;
}
void Hero::Update(){
    if(state != HeroState::ATTACK) {
        counter = (counter + 1) % draw_frequency;
        if(counter == 0) sprite_pos = (sprite_pos + 1) % imgCount[state];
        attackGif[attack_pos]->start_time = 0;
        if( key_state[ALLEGRO_KEY_W] ){
            y -= speed;
            state = HeroState::BACK;
        }else if( key_state[ALLEGRO_KEY_A] ){
            x -= speed;
            state = HeroState::LEFT;
        }else if( key_state[ALLEGRO_KEY_S] ){
            y += speed;
            state = HeroState::FRONT;
        }else if( key_state[ALLEGRO_KEY_D] ){
            x += speed;
            state = HeroState::RIGHT;
        }else if( key_state[ALLEGRO_KEY_0] ){
            attack_pos = state;
            state = HeroState::ATTACK;
            attackGif[attack_pos]->loop = 1;
            switch(attack_pos){
            case HeroState::BACK:
                atk_x = x + al_get_bitmap_width( imgData[attack_pos][0] ) / 3;
                atk_y = y - attackGif[attack_pos]->height;
                break;
            case HeroState::LEFT:
                atk_x = x - attackGif[attack_pos]->width;
                atk_y = y + al_get_bitmap_height( imgData[attack_pos][0] ) / 4;
                break;
            case HeroState::FRONT:
                atk_x = x + al_get_bitmap_width( imgData[attack_pos][0] ) / 3;
                atk_y = y + al_get_bitmap_height( imgData[attack_pos][0] );
                break;
            case HeroState::RIGHT:
                atk_x = x + al_get_bitmap_width( imgData[attack_pos][0] );
                atk_y = y + al_get_bitmap_height( imgData[attack_pos][0] ) / 4;
                break;
            default:
                break;
            }
        }
    }else{
        if(attackGif[attack_pos]->done){
            state = attack_pos;
            attackGif[attack_pos]->done = false;
        }else{
            std::vector<Monster*>& monsterSet = DC->get_Monster();
            for(int i = 0; i < monsterSet.size(); i++){
                if( monsterSet[i]->get_touch( atk_x, atk_y, attackGif[attack_pos]->width, attackGif[attack_pos]->height ) ){
                    Monster* m = monsterSet[i];
                    monsterSet.erase(monsterSet.begin() + i);
                    i--;
                    delete m;
                }
            }
        }
    }


}
void Hero::Draw(){
    if(state != HeroState::ATTACK)
        al_draw_bitmap(imgData[state][sprite_pos], x, y , 0);
    else{
        al_draw_bitmap(imgData[attack_pos][0], x, y , 0);
        ALLEGRO_BITMAP *frame = algif_get_bitmap( attackGif[attack_pos], al_get_time() );
        if (frame) al_draw_bitmap(frame, atk_x, atk_y , 0);
    }

}
