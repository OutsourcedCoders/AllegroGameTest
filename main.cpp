//#include <cstdlib>
#include <iostream>
#include <stdio.h>

#define ALLEGRO_STATICLINK
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

using namespace std;
const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32;
enum MYKEYS{
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int main(int argc, char** argv) {

    ALLEGRO_DISPLAY *TestDisplay = NULL;
    ALLEGRO_EVENT_QUEUE *TestEventQ = NULL;
    ALLEGRO_TIMER *TestTimer = NULL;
    ALLEGRO_BITMAP *TestChar = NULL;
    float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
    float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
    bool key[4] = {false, false, false, false};
    bool redraw = true;
    bool doexit = false;
    
    if(!al_init()){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to initialize Allegro!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
    
    if(!al_install_keyboard()){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to initialize the keyboard!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
    
    TestTimer = al_create_timer(1.0 / FPS);
    if(!TestTimer){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to create a timer!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
    
    if(!al_init_image_addon()){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to initialize al_init_image_addon!", 
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
    
    TestDisplay = al_create_display(800, 600);
    
    if(!TestDisplay){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to create display!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_timer(TestTimer);
        return 0;
    }
    
    TestChar = al_load_bitmap("resources/images/test.bmp");
    
    if(!TestChar){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to create player!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(TestDisplay);
        al_destroy_timer(TestTimer);
        return 0;
    }
    
    al_set_target_bitmap(TestChar);
    
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    al_set_target_bitmap(al_get_backbuffer(TestDisplay));
    
    TestEventQ = al_create_event_queue();
    if(!TestEventQ){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to initialize event queue!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_bitmap(TestChar);
        al_destroy_display(TestDisplay);
        al_destroy_timer(TestTimer);
        return 0;
    }
    
//    
//    al_draw_bitmap(TestCharacter, 200, 200, 0);
//    
//    al_flip_display();
//    al_rest(2);
//    
//    al_destroy_display(TestDisplay);
//    al_destroy_bitmap(TestCharacter);
//    
    return 0;
}