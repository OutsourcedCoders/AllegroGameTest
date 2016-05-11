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
const int TESTCHAR_SIZE = 32;
enum MYKEYS{
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int main(int argc, char** argv) {

    ALLEGRO_DISPLAY *TestDisplay = NULL;
    ALLEGRO_EVENT_QUEUE *testeventq = NULL;
    ALLEGRO_TIMER *TestTimer = NULL;
    ALLEGRO_BITMAP *TestChar = NULL;
    float testchar_x = SCREEN_W / 2.0 - TESTCHAR_SIZE / 2.0;
    float testchar_y = SCREEN_H / 2.0 - TESTCHAR_SIZE / 2.0;
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
    
    TestDisplay = al_create_display(SCREEN_W, SCREEN_H);
    if(!TestDisplay){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to create display!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_timer(TestTimer);
        return 0;
    }
    
    if(!al_init_image_addon()){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to initialize al_init_image_addon!", 
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
    
    TestChar = al_load_bitmap("resources/images/playerchar.png");
    
    if(!TestChar){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to create player!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(TestDisplay);
        al_destroy_timer(TestTimer);
        return 0;
    }
    
    al_set_target_bitmap(TestChar);
    
//    al_clear_to_color(al_map_rgb(255, 0, 255));
    
    al_set_target_bitmap(al_get_backbuffer(TestDisplay));
    
    testeventq = al_create_event_queue();
    if(!testeventq){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to initialize event queue!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_bitmap(TestChar);
        al_destroy_display(TestDisplay);
        al_destroy_timer(TestTimer);
        return 0;
    }
    
    al_register_event_source(testeventq, al_get_display_event_source(TestDisplay));
    
    al_register_event_source(testeventq, al_get_timer_event_source(TestTimer));
    
    al_register_event_source(testeventq, al_get_keyboard_event_source());
    
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    al_flip_display();
    
    al_start_timer(TestTimer);
    
    while(!doexit){
        ALLEGRO_EVENT ev;
        al_wait_for_event(testeventq, &ev);
        
        if(ev.type == ALLEGRO_EVENT_TIMER){
            if(key[KEY_UP] && testchar_y >= 4.0){
                testchar_y -= 4.0;
                TestChar = al_load_bitmap("resources/images/playercharup.png"); 
            }
            if(key[KEY_DOWN] && testchar_y <= SCREEN_H - TESTCHAR_SIZE - 4.0){
                testchar_y += 4.0;
                TestChar = al_load_bitmap("resources/images/playerchardown.png");
            }
            if(key[KEY_LEFT] && testchar_x >= 4.0){
                testchar_x -= 4.0;
                TestChar = al_load_bitmap("resources/images/playercharleft.png");
            }
            if(key[KEY_RIGHT] && testchar_x <= SCREEN_W - TESTCHAR_SIZE - 4.0){
                testchar_x += 4.0;
                TestChar = al_load_bitmap("resources/images/playercharright.png");
            }
            
            redraw = true;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
            break;
        }
        
        else if(ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = true;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    break;
            }
            
//            redraw = true;
        }
        
        else if(ev.type == ALLEGRO_EVENT_KEY_UP){
            switch(ev.keyboard.keycode){
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = false;
                    break;
                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = false;
                    break;
                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = false;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = false;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    doexit = true;
                    break;
            }
            
//            redraw = true;
        }
        
        if(redraw && al_is_event_queue_empty(testeventq)){
            redraw = false;
            
            al_clear_to_color(al_map_rgb(0, 0, 0));
            
            al_draw_bitmap(TestChar, testchar_x, testchar_y, 0);
            
            al_flip_display();
        }
    }
    al_destroy_display(TestDisplay);
    al_destroy_bitmap(TestChar);
    al_destroy_timer(TestTimer);
    al_destroy_event_queue(testeventq);
    
    return 0;
}