//
// Created by manuel on 15/11/19.
//

#include <allegro5/haptic.h>
#include <allegro5/events.h>
#include <allegro5/timer.h>
#include <allegro5/system.h>
#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include "prueba.h"

const float FPS=60;
const float frameFPS=60.0;
const float gravity=1;
const  int screenW=640;
const  int screenH=480;
const  int bottom=480;
const  int bouncerSize=32;
enum KEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_W, KEY_S, KEY_A, KEY_D
};

// x, y son las coordenadas de player. ex, ey las del enemigo
bool spriteCollision(float x, float y, float ex, float ey,int width, int height){


    if(x+width < ex || x > ex+width || y+height < ey || y > ey+height){
        return false;
    }
    return true;
}

int initGame() {

    //INIT FIELDS
    //const char *output[];
    ALLEGRO_DISPLAY *display=NULL;
    ALLEGRO_EVENT_QUEUE *eventQueue=NULL;
    ALLEGRO_TIMER *timer=NULL;
    ALLEGRO_TIMER *frameTimer=NULL;
    ALLEGRO_BITMAP *bouncer=NULL;
    ALLEGRO_BITMAP *bouncer2=NULL;
    //ALLEGRO_BITMAP *player=NULL;
    float bouncer_x = screenW / 2.0 - bouncerSize / 2.0;
    float bouncer_y = screenH / 2.0 - bouncerSize / 2.0;
    float bouncerWidth;
    float bouncerHeigth;
    //int sourceX=al_get_bitmap_width(bouncer)/3,sourceY=0;

    float bouncer2_x = screenW / 2.0 - bouncerSize / 2.0;
    float bouncer2_y = screenH / 2.0 - bouncerSize / 2.0;
    float bouncer2Width;
    float bouncer2Heigth;
    //int sourceX2=al_get_bitmap_width(bouncer)/3,sourceY2=0;

    float bouncer_dx = -4.0, bouncer_dy = 4.0;
    bool key[8] = { false, false, false, false, false, false, false, false };
    bool redraw=true;
    bool exit=false;

    double velX,velY,velX2,velY2;
    velX=velY=velX2=velY2=0;
    bool jump=false;
    bool jump2=false;
    float jumpSize=20;
    float moveSpeed=4.0;
    float spriteSheetX=51,spriteSheetY=0;
    bool active=false;
    int direction=key[KEY_RIGHT];

    //INIT ALLEGRO LIBRARY
    if(!al_init()){
        printf("Fail to init Allegro");
        return -1;
    }

    //HANDLE IMAGE LOADER ERROR
    if(!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    //HANDLE KEYBOARD EVENTS
    if(!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }

    //CREATE TIMER
    timer = al_create_timer(1.0 / FPS);
    frameTimer = al_create_timer(1.0 / frameFPS);
    if(!timer || !frameTimer){
        printf("Fail to create timer");
    }

    //CREATE DISPLAY WINDOW
    display=al_create_display(screenW,screenH);
    if(!display){
        printf("Fail to init Window");
        return -1;
    }

    //LOAD IMAGE
    bouncer = al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/popo.png");
    bouncer2 = al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/nana.png");


    //CREATE BITMAP

    //bouncer=al_create_bitmap(bouncerSize,bouncerSize);
    //bouncer2=al_create_bitmap(bouncerSize,bouncerSize);


    //GETS SPRITE WIDTH AND HEIGHT
    bouncerWidth=al_get_bitmap_width(bouncer);
    bouncerHeigth=al_get_bitmap_height(bouncer);
    bouncer2Width=al_get_bitmap_width(bouncer2);
    bouncer2Heigth=al_get_bitmap_height(bouncer2);
    //************************ DRAW BITMAPS *************************
    //DRAW IMAGE
    //al_draw_bitmap(image,200,200,0);
    //DRAW BOUNCER

    //al_set_target_bitmap(bouncer);
    //al_clear_to_color(al_map_rgb(100, 0, 255));
    //al_set_target_bitmap(al_get_backbuffer(display));

    //al_set_target_bitmap(bouncer2);
    //al_clear_to_color(al_map_rgb(255, 0, 100));
    //al_set_target_bitmap(al_get_backbuffer(display));


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
    al_register_event_source(eventQueue, al_get_timer_event_source(frameTimer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_clear_to_color(al_map_rgb(0,0,0));

    //FLIP IMAGE BUFFERED
    al_flip_display();
    //START TIMER
    al_start_timer(timer);
    al_start_timer(frameTimer);

    //GAME LOOP
    while(!exit){
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue,&event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }

        else if(event.type==ALLEGRO_EVENT_TIMER) {
            active = true;

            if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
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

//////////////////////////////////////////////////////////////////////////////////

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

            //SET SCREEN LIMITS TO BOUNCER
            if (key[KEY_LEFT] && bouncer_x >= 4.0) {
                velX = -moveSpeed;
                direction=key[KEY_LEFT];
            }
            else if (key[KEY_RIGHT] && bouncer_x <= screenW - bouncerSize - 4.0) {
                velX = moveSpeed;
                direction=key[KEY_RIGHT];
            }
            else{
                velX=0;
                active=false;

                if (key[KEY_UP] && bouncer_y >= 4.0 && jump) {
                    velY = -jumpSize;
                    jump=false;
                }

            }

//////////////////////////////////////////////////////////////////////////////

            if (key[KEY_A] && bouncer2_x >= 4.0) {
                velX2 = -moveSpeed;
            }
            else if (key[KEY_D] && bouncer2_x <= screenW - bouncerSize - 4.0) {
                velX2 = moveSpeed;
            }
            else{
                velX2=0;
                if (key[KEY_W] && bouncer2_y >= 4.0 && jump2) {
                    velY2 -= jumpSize;
                    jump2=false;
                }
            }



            if(spriteCollision(bouncer_x,bouncer_y,bouncer2_x,bouncer2_y,bouncerSize,bouncerSize)) { // al_get_bitmap_width(player) = 32


                if(key[KEY_RIGHT]){
                    bouncer_x-=10;

                }
                else if(key[KEY_LEFT]){
                    bouncer_x+=10;

                }

                else if(key[KEY_D]){
                    bouncer2_x-=10;

                }
                else if(key[KEY_A]){
                    bouncer2_x+=10;
                }
            }

            //initClient(jsonWriter(bouncer_x, bouncer_y, 0, 3));
            //redraw = true;


            if(active)
                spriteSheetX+=bouncerWidth/3;
            else
                spriteSheetX=51; //la imagen tiene 3 imagenes horizontalmente, cada un de 51 pixel en el eje X

            if(spriteSheetX>=bouncerWidth)
                spriteSheetX=0;

            spriteSheetY=direction;


            if(!jump)
                velY+=gravity; //al saltar, la velocidad sera hacia abajo en la pantalla aumentando en Y
            else
                velY=0;
            bouncer_x+=velX;
            bouncer_y+=velY;

            jump=(bouncer_y+bouncerSize>=bottom);

            if(jump)
                bouncer_y=bottom-bouncerSize;

////////////////////////////////////////////////////////////////////////////////////////////
            if(!jump2)
                velY2+=gravity; //al saltar, la velocidad sera hacia abajo en la pantalla aumentando en Y
            else
                velY2=0;
            bouncer2_x+=velX2;
            bouncer2_y+=velY2;

            jump2=(bouncer2_y+bouncerSize>=bottom);

            if(jump2)
                bouncer2_y=bottom-bouncerSize;


            redraw = true;
        }







////////////////////////////////////////////////////////////////////////////////////////////

        if(redraw && al_is_event_queue_empty(eventQueue)){

            //al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0);
            al_draw_bitmap_region(bouncer,spriteSheetX,spriteSheetY*bouncerHeigth/2,51,51,bouncer_x,bouncer_y,NULL);

            //al_draw_bitmap(bouncer2, bouncer2_x, bouncer2_y, 0);
            al_draw_bitmap_region(bouncer2,spriteSheetX,spriteSheetY*bouncerHeigth/2,51,51,bouncer2_x,bouncer2_y,NULL);

            al_flip_display();
            redraw=false;
            al_clear_to_color(al_map_rgb(0,0,0));
        }

    }

    //FREE MEMORY AFTER CLOSE PROGRAM
    //al_destroy_bitmap(image);
    al_destroy_bitmap(bouncer);
    al_destroy_bitmap(bouncer2);
    al_destroy_timer(timer);
    al_destroy_timer(frameTimer);
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);

    return 0;
}

int mainx() {
    initGame();
}
