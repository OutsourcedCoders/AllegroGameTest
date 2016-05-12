//#include <cstdlib>
#include <iostream>
#include <stdio.h>

#define ALLEGRO_STATICLINK
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

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
    ALLEGRO_BITMAP *TestWorld = NULL;
    ALLEGRO_SAMPLE *TestSound = NULL;
    float testchar_x = SCREEN_W / 2.0 - TESTCHAR_SIZE / 2.0;
    float testchar_y = SCREEN_H / 2.0 - TESTCHAR_SIZE / 2.0;
    bool key[4] = {false, false, false, false};
    bool redraw = true;
    bool doexit = false;
    cout << "Welcome to Jasonface900's program.\n";
    cout << "You'll like this, trust me.\n";
    
    //Begin error checks
    if(!al_init()){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to initialize Allegro!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
    
    if(!al_install_audio()){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to initialize the audio!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
    
    if(!al_init_acodec_addon()){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to initialize audio codecs!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
    
    if(!al_reserve_samples(1)){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to reserve sounds!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
    
    TestSound = al_load_sample("resources/sounds/boop.wav");
    if(!TestSound){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Can't find resources/sounds/boop.wav!",
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
    
    TestWorld = al_load_bitmap("resources/images/map.png");
    
    if(!TestWorld){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to create map!!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(TestDisplay);
        al_destroy_timer(TestTimer);
        al_destroy_bitmap(TestChar);
        return 0;
    }
    
    //sets edit target to my bitmap named TestChar
    al_set_target_bitmap(TestChar);
    
    al_set_target_bitmap(al_get_backbuffer(TestDisplay));
    
    testeventq = al_create_event_queue();
    if(!testeventq){
        al_show_native_message_box(TestDisplay, "Error", "Error", "Failed to initialize event queue!",
                NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_bitmap(TestChar);
        al_destroy_bitmap(TestWorld);
        al_destroy_display(TestDisplay);
        al_destroy_timer(TestTimer);
        return 0;
    }
    
    //End error checks
    
    al_register_event_source(testeventq, al_get_display_event_source(TestDisplay));
    
    al_register_event_source(testeventq, al_get_timer_event_source(TestTimer));
    
    al_register_event_source(testeventq, al_get_keyboard_event_source());
    
//    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    al_flip_display();//refreshes screen, switching from first frame to second
    
    al_start_timer(TestTimer);
    
    while(!doexit){
        ALLEGRO_EVENT ev;
        al_wait_for_event(testeventq, &ev);
        
        if(ev.type == ALLEGRO_EVENT_TIMER){
            //Movement code
            if(key[KEY_UP] && testchar_y >= 4.0){
                testchar_y -= 4.0;
                TestChar = al_load_bitmap("resources/images/playercharup.png");
                cout << "Moved up.\n";
            }
            if(key[KEY_DOWN] && testchar_y <= SCREEN_H - TESTCHAR_SIZE - 4.0){
                testchar_y += 4.0;
                TestChar = al_load_bitmap("resources/images/playerchardown.png");
                cout << "Moved down.\n";
            }
            if(key[KEY_LEFT] && testchar_x >= 4.0){
                testchar_x -= 4.0;
                TestChar = al_load_bitmap("resources/images/playercharleft.png");
                cout << "Moved left.\n";
            }
            if(key[KEY_RIGHT] && testchar_x <= SCREEN_W - TESTCHAR_SIZE - 4.0){
                testchar_x += 4.0;
                TestChar = al_load_bitmap("resources/images/playercharright.png");
                cout << "Moved right.\n";
            }
            //Collision code
            if(testchar_x >= SCREEN_W - TESTCHAR_SIZE - 4.0 || testchar_y >= SCREEN_H - TESTCHAR_SIZE - 4.0){
                al_play_sample(TestSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                cout << "You hit the wall. Boop.\n";
            } else if(testchar_x <= 0 || testchar_y <= 0){
                al_play_sample(TestSound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                cout << "You hit the wall. Boop.\n";
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
            
            al_set_target_bitmap(TestWorld);
            al_set_target_bitmap(al_get_backbuffer(TestDisplay));
            
            TestWorld = al_load_bitmap("resources/images/map.png");
            
            
            al_set_target_bitmap(TestChar);
            al_set_target_bitmap(al_get_backbuffer(TestDisplay));
            
            al_draw_bitmap(TestChar, testchar_x, testchar_y, 0);
            
            al_flip_display();
        }
    }
    cout << "Goodbye D:\n";
    cout << "Come back later!\n";
    cout << "BTW, this is still not final version";
    
    al_destroy_display(TestDisplay);
    al_destroy_bitmap(TestChar);
    al_destroy_bitmap(TestWorld);
    al_destroy_timer(TestTimer);
    al_destroy_event_queue(testeventq);
    al_destroy_sample(TestSound);
    
    return 0;
}