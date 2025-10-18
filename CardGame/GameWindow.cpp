#include "GameWindow.h"
#include "global.h"
#include <iostream>
#include "Card.h"
#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))



int TURN;// present turn == 4 lose


void
GameWindow::game_init()//load �귽
{

    icon = al_load_bitmap("./icon.png");
    background = al_load_bitmap("./background (1).png");
    start_background = al_load_bitmap("./StartBackground.png");
    intro = al_load_bitmap("./introduction.png");
    WIN_GAME = al_load_bitmap("./you_win_text.png");
    LOSE_GAME = al_load_bitmap("./you_lose_text.png");

    for(int i = 0; i < Num_sheepType; i++)
    {
        char buffer[50];
        sprintf(buffer, "./sheep/%s_sheep.png", SheepClass[i]);
        sheep[i] = al_load_bitmap(buffer);
    }
    window =0;
    al_set_display_icon(display, icon);
    al_reserve_samples(3);

    sample = al_load_sample("yell.mp3");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());

    sample = al_load_sample("BackGroundMusic.mp3");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());


    DC->get_Deck().init();
    DC->get_SheepCard().init();
}

bool//judge whether mouse on the special area
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;

    return false;
}



void
GameWindow::game_play()
{
    int msg;

    srand(time(NULL));

    msg = -1;
    game_reset();
    game_begin();

    while(msg != GAME_EXIT)
    {
        msg = game_run();
    }

    show_err_msg(msg);
}

void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);
    printf("Game Initializing...\n");
    display = al_create_display(window_width, window_height);
    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / FPS);
    monster_pro = al_create_timer(1.0 / FPS);

    if(timer == NULL || monster_pro == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",48,0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_timer_event_source(monster_pro));

    game_init();
}

void
GameWindow::game_begin()
{

    draw_running_map();
    al_play_sample_instance(startSound);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_LOOP);
    while(al_get_sample_instance_playing(startSound));
    al_play_sample_instance(backgroundSound);

    al_start_timer(timer);
    al_start_timer(monster_pro);
}

int
GameWindow::game_run()
{
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}

int
GameWindow::game_update()
{


    return GAME_CONTINUE;
}

void
GameWindow::game_reset()
{

    DC->get_Deck().hand_clear();
    DC->get_Deck().Deck_initialize();
    DC->get_Deck().drawHand(5);//initialize hand
    DC->get_Deck().discardPile_clear();//initialize discardPile
    DC->get_SheepCard().Field_initialize();
    TURN =1;

    mute = false;
    redraw = false;


    // stop sample instance
    al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(startSound);

    // stop timer
    al_stop_timer(timer);
    al_stop_timer(monster_pro);
}

void
GameWindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);


    for(int i=0;i<Num_sheepType;i++)
        al_destroy_bitmap(sheep[i]);
    DC->get_Deck().destroy();
    DC->get_SheepCard().destroy();
    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);
    al_destroy_bitmap(WIN_GAME);
    al_destroy_bitmap(LOSE_GAME);
    al_destroy_bitmap(intro);
    al_destroy_sample(sample);
    al_destroy_sample_instance(startSound);
    al_destroy_sample_instance(backgroundSound);

}

int
GameWindow::process_event() // ��L�ާ@��
{
    int i;
    int instruction = GAME_CONTINUE;


    al_wait_for_event(event_queue, &event);
    redraw = false;
    if(event.type == ALLEGRO_EVENT_TIMER)
        {
        if(event.timer.source == timer)
            {
            redraw = true;
            if(DC->get_Deck().NoCard())// if there are no cards in the hand then enter next round
            {
                //enter next round
                DC->get_Deck().Deck_initialize();
                DC->get_Deck().drawHand(5);
                DC->get_Deck().discardPile_clear();
                TURN+=1;
            }
            if( TURN == 4 ||DC->get_SheepCard().No_Sheep())
            {
                window =-1;
                al_stop_sample_instance(backgroundSound);
            }
            else if(TURN<4&&DC->get_SheepCard().Victory())
            {
                window=2;
                al_stop_sample_instance(backgroundSound);
            }
        }

    }

    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event.keyboard.keycode) {

            case ALLEGRO_KEY_M:
                mute = !mute;
                if(mute)
                    al_stop_sample_instance(backgroundSound);
                else
                    al_play_sample_instance(backgroundSound);
                break;
            case ALLEGRO_KEY_ENTER:
                window = 1 ;
                break;
            case ALLEGRO_KEY_ESCAPE:
                 return GAME_EXIT;
                break;
            case ALLEGRO_KEY_P:
                window = 3;
                break;
            case ALLEGRO_KEY_R:
                game_play();
                break;
            case ALLEGRO_KEY_SPACE:
                if( !mouse_click_positions.empty()) {
                    // std::cout << "\nmouse click position = ";
                    // for(auto i = mouse_click_positions.begin(); i != mouse_click_positions.end(); i++) {
                    //     std::cout << *i << " ";
                    // }
                    std::vector<Card> Hand = DC->get_Deck().getHand();
                    FunctionCardType functionCard = Hand[mouse_click_positions[0]].type;

                    std::vector<SheepCardType> SelectedField;
                    std::vector<SheepCardType> Fieldtype;

                    std::map<SheepCardType,int> Field = DC->get_SheepCard().getField();

                    for(auto i = Field.begin(); i != Field.end(); i++) {
                        int num = i->second;
                        while(num--) {
                            Fieldtype.push_back(i->first);
                        }
                    }
                    //////////  SheepDog: discard two function cards  ////////////////
                    if(functionCard == S_SheepDog) {
                        if(mouse_click_positions.size() == 2) {
                            FunctionCardType functionCard2 = Hand[mouse_click_positions[1]].type;
                            struct Card tmp_card;
                            tmp_card.type = functionCard;
                            DC->get_Deck().discardCard(tmp_card);
                            tmp_card.type = functionCard2;
                            DC->get_Deck().discardCard(tmp_card);
                        }
                    }
                    ////////////////////  Other function cards  //////////////////////
                    else {
                        int valid = true;
                        int mouse_click_size = mouse_click_positions.size();
                        for(int i = 1; i < mouse_click_size; i++) {
                            if(mouse_click_positions[i] >= Fieldtype.size()) {
                                valid = false;
                                break;
                            }
                            SelectedField.push_back(Fieldtype[mouse_click_positions[i]]);
                        }
                        if(valid) {
                            switch(functionCard){
                                case A_BeFruitful:
                                    if(mouse_click_size != 2) valid = false;
                                    break;
                                case A_FullTheEarth:
                                    if(mouse_click_size != 1) valid = false;
                                    break;
                                case A_Multiply:
                                    if(mouse_click_size != 1) valid = false;
                                    break;
                                case A_Golden:
                                    {
                                    if(mouse_click_size != 1) valid = false;
                                    break;
                                    }
                                case B_FallingRock:
                                    if(mouse_click_size != 1) valid = false;
                                    break;
                                case B_Slump:
                                    if(mouse_click_size != 1) valid = false;
                                    break;
                                case B_Plague:
                                    if(mouse_click_size != 1) valid = false;
                                    break;
                                case B_Lightning:
                                    if(mouse_click_size != 1) valid = false;
                                    break;
                                case B_Storm:
                                    if(mouse_click_size != 1) valid = false;
                                    break;
                                case S_Dominion:
                                    if(mouse_click_size <= 1) valid = false;
                                    break;
                            }

                        }
                        if(valid) {
                            std::map<SheepCardType,int> new_field = DC->get_Deck().event(functionCard, SelectedField, DC->get_SheepCard());
                            DC->get_SheepCard().getField() = new_field;
                            struct Card tmp_card;
                            tmp_card.type = functionCard;
                            DC->get_Deck().discardCard(tmp_card);
                        }
                    }
                    mouse_click_positions.clear();
                }
                break;

        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
        if(event.mouse.button == 1) {
            // std::cout<< mouse_x << " " << mouse_y << std::endl;
            std::vector<Card> Hand = DC->get_Deck().getHand();
            int function_card = -1;
            int field_card = -1;
            if(mouse_hover(240, 470, 105, 120)) function_card = 0; //x, y, width, height
            else if(mouse_hover(400, 470, 105, 120)) function_card = 1;
            else if(mouse_hover(560, 470, 105, 120)) function_card = 2;
            else if(mouse_hover(720, 470, 105, 120)) function_card = 3;
            else if(mouse_hover(880, 470, 105, 120)) function_card = 4;
            else if(mouse_hover(83, 261, 100, 115)) field_card = 0;
            else if(mouse_hover(243, 261, 100, 115)) field_card = 1;
            else if(mouse_hover(403, 261, 100, 115)) field_card = 2;
            else if(mouse_hover(563, 261, 100, 115)) field_card = 3;
            else if(mouse_hover(723, 261, 100, 115)) field_card = 4;
            else if(mouse_hover(883, 261, 100, 115)) field_card = 5;
            else if(mouse_hover(1043, 261, 100, 115)) field_card = 6;

            // std::cout << "function card = " << function_card << " field card = " << field_card << std::endl;

            if(function_card != -1&&function_card<Hand.size()) {
                if(mouse_click_positions.empty()) {
                    mouse_click_positions.push_back(function_card);
                }
                else {
                    FunctionCardType FunctionCard1st = (DC->get_Deck().getHand())[mouse_click_positions[0]].type;
                    if(FunctionCard1st == S_SheepDog && mouse_click_positions.size() == 1) {
                        mouse_click_positions.push_back(function_card);
                    }
                    else {
                        mouse_click_positions.clear();
                        mouse_click_positions.push_back(function_card);
                    }
                }
            }else if(field_card != -1) {
                if( !mouse_click_positions.empty()) {
                    FunctionCardType FunctionCard1st = (DC->get_Deck().getHand())[mouse_click_positions[0]].type;
                    if(FunctionCard1st == S_SheepDog) {
                        mouse_click_positions.clear();
                    }
                    else if(std::find(mouse_click_positions.begin() + 1, mouse_click_positions.end(), field_card) == mouse_click_positions.end()) mouse_click_positions.push_back(field_card);
                }
            }

        }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
        mouse_x = event.mouse.x;
        mouse_y = event.mouse.y;


        }
    /*TODO:*/
    // process key board state
    if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;

    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }

    if(redraw) {
        // update each object in game
        instruction = game_update();

        // Re-draw map
        draw_running_map();
        redraw = false;
    }

    return instruction;
}

void
GameWindow::draw_running_map()//Draw the picture on the screen
{


   if(window == 0) al_draw_bitmap(start_background,0,0,0);
   else if (window ==1) //Enter game
   {
       al_draw_bitmap(background, 0, 0, 0);

       al_draw_textf(Large_font, al_map_rgb(255, 255, 255), window_width-75, window_height-625, ALLEGRO_ALIGN_CENTER, "%d", TURN);


        for(int i =0 ;i<7;i++)
        {
        al_draw_bitmap(sheep[i],(60+i*160),50,0);
        }
        DC->get_Deck().Draw_hand();
        DC->get_SheepCard().Draw_field();
   }

    else if(window ==2 ) {
            al_draw_bitmap(background, 0, 0, 0);

       al_draw_textf(Large_font, al_map_rgb(255, 255, 255), window_width-75, window_height-625, ALLEGRO_ALIGN_CENTER, "%d", TURN);


        for(int i =0 ;i<7;i++)
        {
        al_draw_bitmap(sheep[i],(60+i*160),50,0);
        }
        DC->get_Deck().Draw_hand();
        DC->get_SheepCard().Draw_field();
        al_draw_bitmap(WIN_GAME,window_width/2-200,window_height/2-200,0);
    }
   else if(window ==-1) {
       al_draw_bitmap(background, 0, 0, 0);

       al_draw_textf(Large_font, al_map_rgb(255, 255, 255), window_width-75, window_height-625, ALLEGRO_ALIGN_CENTER, "%d", TURN);


        for(int i =0 ;i<7;i++)
        {
        al_draw_bitmap(sheep[i],(60+i*160),50,0);
        }
        DC->get_Deck().Draw_hand();
        DC->get_SheepCard().Draw_field();
        al_draw_bitmap(LOSE_GAME,window_width/2-200,window_height/2-200,0);
   }
   else if(window ==3 )
   {
       al_draw_bitmap(intro,0,0,0);
   }
    al_flip_display();

}
