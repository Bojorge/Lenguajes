//
// Created by manuel on 15/11/19.
//

#include <allegro5/haptic.h>
#include <allegro5/events.h>
#include <allegro5/timer.h>
#include <allegro5/system.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include "prueba.h"

const float FPS=60;
const  int screenW=640;
const  int screenH=480;
const  int bouncerSize=32;
enum KEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_W, KEY_S, KEY_A, KEY_D
};

int initGame() {

    //INIT FIELDS
    //const char *output[];
    ALLEGRO_DISPLAY *display=NULL;
    ALLEGRO_EVENT_QUEUE *eventQueue=NULL;
    ALLEGRO_TIMER *timer=NULL;
    ALLEGRO_BITMAP *bouncer=NULL;
    ALLEGRO_BITMAP *bouncer2=NULL;
    //ALLEGRO_BITMAP *player=NULL;
    float bouncer_x = screenW / 2.0 - bouncerSize / 2.0;
    float bouncer_y = screenH / 2.0 - bouncerSize / 2.0;

    float bouncer2_x = screenW / 2.0 - bouncerSize / 2.0;
    float bouncer2_y = screenH / 2.0 - bouncerSize / 2.0;

    float bouncer_dx = -4.0, bouncer_dy = 4.0;
    bool key[8] = { false, false, false, false, false, false, false, false };
    bool redraw=true;
    bool exit=false;

    //INIT ALLEGRO LIBRARY
    if(!al_init()){
        printf("Fail to init Allegro");
        return -1;
    }

    //HANDLE IMAGE LOADER ERROR
    /*if(!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }*/

    //HANDLE KEYBOARD EVENTS
    if(!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }

    //CREATE TIMER
    timer = al_create_timer(1.0 / FPS);
    if(!timer){
        printf("Fail to create timer");
    }

    //CREATE DISPLAY WINDOW
    display=al_create_display(screenW,screenH);
    if(!display){
        printf("Fail to init Window");
        return -1;
    }

    //LOAD IMAGE
    /*player = al_load_bitmap("/home/gunther/CLionProjects/ICE_Client/imgs/Sprites2.png");
    if(!image) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return 0;
    }*/

    //CREATE BITMAP
    bouncer=al_create_bitmap(bouncerSize,bouncerSize);
    bouncer2=al_create_bitmap(bouncerSize,bouncerSize);
    if(!bouncer || !bouncer2){
        printf("Fail to create bitmap");
        al_destroy_display(display);
        al_destroy_timer(timer);
        //al_destroy_bitmap(image);
        return -1;
    }

    //************************ DRAW BITMAPS *************************
    //DRAW IMAGE
    //al_draw_bitmap(image,200,200,0);
    //DRAW BOUNCER
    al_set_target_bitmap(bouncer);
    al_clear_to_color(al_map_rgb(100, 0, 255));
    al_set_target_bitmap(al_get_backbuffer(display));

    al_set_target_bitmap(bouncer2);
    al_clear_to_color(al_map_rgb(255, 0, 100));
    al_set_target_bitmap(al_get_backbuffer(display));


    //CREATE AND MANAGE EVENT QUEUE
    eventQueue=al_create_event_queue();
    if(!eventQueue){
        printf("Fail to create Event Queue");
        al_destroy_display(display);
        return -1;
    }


    //REGISTER EVENTS TO EVENT QUEUE (LINK THEM)
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(0,0,0));

    //FLIP IMAGE BUFFERED
    al_flip_display();
    //START TIMER
    al_start_timer(timer);

    //GAME LOOP
    while(!exit){
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue,&event);


        if(event.type==ALLEGRO_EVENT_TIMER) {

            //SET SCREEN LIMITS TO BOUNCER
            if (key[KEY_UP] && bouncer_y >= 4.0) {
                bouncer_y -= 4.0;
            }
            if (key[KEY_DOWN] && bouncer_y <= screenH - bouncerSize - 4.0) {
                bouncer_y += 4.0;
            }
            if (key[KEY_LEFT] && bouncer_x >= 4.0) {
                bouncer_x -= 4.0;
            }
            if (key[KEY_RIGHT] && bouncer_x <= screenW - bouncerSize - 4.0) {
                bouncer_x += 4.0;
            }



            if (key[KEY_W] && bouncer2_y >= 4.0) {
                bouncer2_y -= 4.0;
            }
            if (key[KEY_S] && bouncer2_y <= screenH - bouncerSize - 4.0) {
                bouncer2_y += 4.0;
            }
            if (key[KEY_A] && bouncer2_x >= 4.0) {
                bouncer2_x -= 4.0;
            }
            if (key[KEY_D] && bouncer2_x <= screenW - bouncerSize - 4.0) {
                bouncer2_x += 4.0;
            }

            //initClient(jsonWriter(bouncer_x, bouncer_y, 0, 3));
            redraw = true;
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(event.keyboard.keycode) {
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

                case ALLEGRO_KEY_W:
                    key[KEY_W] = true;
                    break;

                case ALLEGRO_KEY_S:
                    key[KEY_S] = true;
                    break;

                case ALLEGRO_KEY_A:
                    key[KEY_A] = true;
                    break;

                case ALLEGRO_KEY_D:
                    key[KEY_D] = true;
                    break;
            }

        }
        else if(event.type == ALLEGRO_EVENT_KEY_UP) {
            switch(event.keyboard.keycode) {
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

                case ALLEGRO_KEY_W:
                    key[KEY_W] = false;
                    break;

                case ALLEGRO_KEY_S:
                    key[KEY_S] = false;
                    break;

                case ALLEGRO_KEY_A:
                    key[KEY_A] = false;
                    break;

                case ALLEGRO_KEY_D:
                    key[KEY_D] = false;
                    break;

                case ALLEGRO_KEY_ESCAPE:
                    exit = true;
                    break;
            }
        }


        if(redraw && al_is_event_queue_empty(eventQueue)){
            redraw=false;
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
            al_draw_bitmap(bouncer2, bouncer2_x, bouncer2_y, 0);
            al_flip_display();
        }

    }

    //FREE MEMORY AFTER CLOSE PROGRAM
    //al_destroy_bitmap(image);
    al_destroy_bitmap(bouncer);
    al_destroy_bitmap(bouncer2);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);

    return 0;
}

int main(){
    initGame();
}