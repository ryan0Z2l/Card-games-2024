#include "global.h"



int TowerRadius[] = {80, 80, 70, 110, 150};
char TowerClass[][20] = {"Arcane", "Archer", "Canon", "Poison", "Storm"};
char SheepClass[][10] = {"1","3","10","30","100","300","1000"};
char FunctionClass[][20] ={
"A_BeFruitful","A_FullTheEarth","A_Multiply","A_Golden",
"B_FallingRock","B_Slump","B_Plague","B_Lightning","B_Storm",
"S_Dominion","S_SheepDog"};
int TowerWidth[] = {72, 66, 72, 59, 45};
int TowerHeight[] = {121, 108, 69, 98, 112};

/*TODO:*/
// Define key_state
bool key_state[ALLEGRO_KEY_MAX] = {0};
