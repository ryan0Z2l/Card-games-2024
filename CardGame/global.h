#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>

#define font_size 15
#define grid_width 40
#define grid_height 40

#define window_width 1280
#define window_height 640
#define field_width 600
#define field_height 600

#define Num_TowerType 5
#define Num_MonsterType 4
#define Num_sheepType 7 // the kinds of sheep card
#define NumOfGrid (field_width / grid_width) * (field_height / grid_height)

extern int TowerRadius[];
extern char TowerClass[][20];
extern char SheepClass[][10];
extern char FunctionClass[][20];


/*TODO:*/
// Declare key_state
extern bool key_state[ALLEGRO_KEY_MAX];



#endif // GLOBAL_H_INCLUDED
