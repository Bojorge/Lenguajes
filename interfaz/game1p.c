//
// Created by manuel on 17/11/19.
//

#include "game1p.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/bitmap.h>
#include <tgmath.h>


// x, y son las coordenadas de player. ex, ey las del enemigo
bool Collision(float x, float y, float ex, float ey,int width, int height){


    if(x+width < ex || x > ex+width || y+height < ey || y > ey+height){
        return false;
    }
    return true;
}



int play1(ALLEGRO_DISPLAY *frame) {

    int playerWidth=0;
    int playerHeight=0;
    int bottom=640;
    const float FPS=60.0; //fotogramas por segundos
    const float frameFPS=60.0;
    enum Direction {RIGHT,LEFT,DOWN,UP};
    //posiciones horizontal y vertical
    float x=10,y=10;
    //velocidad del movimiento
    float moveSpeed=7;
    float velX, velY;
    velX=velY=0;
    int direction=RIGHT, spriteSheetX=51,spriteSheetY=0;
    bool draw=true, active=false;
    //variable para salir del loop
    bool done=false;
    const float gravity=1;
    bool jump=false;
    float jumpSize=25;



    //  Inicia allegro5, esto es necesario para realizar cualquier función de allegro
    //  Verifica si la función devuelve 0, si es asi, generará un mensaje de
    //  error, y el programa retornará -1 lo cual denota un programa fallido
    if(!al_init())
    {
        al_show_native_message_box(NULL,NULL,NULL,"failed to init allegro!",NULL,0);
        return -1;
    }


    //esta funcion permite usar el teclado
    al_install_keyboard();

    //permite cargar imagenes
    al_init_image_addon();

    // Crea un puntero a un DISPLAY y un BITMAP
    //ALLEGRO_DISPLAY* frame=NULL;
    ALLEGRO_BITMAP *player=NULL;
    ALLEGRO_BITMAP *background=NULL;

    //se declara un color
    //ALLEGRO_COLOR electBlue=al_map_rgb(66,66,255);
    //ALLEGRO_COLOR electGreen=al_map_rgb(66,255,66);

    //con esto se obtinene cual tecla es precionada en ese instante
    ALLEGRO_KEYBOARD_STATE keyState;

    //actualiza la ventana cada 0.01666 milisegundos
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    ALLEGRO_TIMER *frameTimer=al_create_timer(1.0/frameFPS);

    //cola de eventos
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();

    if(!al_init_image_addon()) {
        al_show_native_message_box(frame, "Error", "Error", "Failed to initialize al_init_image_addon!",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    player = al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/popo.png");
    background = al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/background.png");
    playerWidth=al_get_bitmap_width(player);
    playerHeight=al_get_bitmap_height(player);



    //registra la fuente del evento, recibe una cola de eventos y el tipo de evento
    al_register_event_source(event_queue,al_get_keyboard_event_source());
    al_register_event_source(event_queue,al_get_timer_event_source(timer));
    al_register_event_source(event_queue,al_get_timer_event_source(frameTimer));
    al_register_event_source(event_queue,al_get_display_event_source(frame));
    //al_register_event_source(event_queue,al_get_mouse_event_source());

    al_hide_mouse_cursor(frame); //muestra el cursor

    al_start_timer(timer);
    al_start_timer(frameTimer);

    //loop del juego
    while(!done) {
        //instancia un nuevo evento
        ALLEGRO_EVENT events;
        //funcion que esta a la escucha de algun evento
        al_wait_for_event(event_queue,&events);
        al_get_keyboard_state(&keyState);

        if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if(events.type==ALLEGRO_EVENT_TIMER){


            if(events.timer.source==timer){
                active=true;
                if(al_key_down(&keyState,ALLEGRO_KEY_RIGHT) && x <= 1305 - playerWidth - 4.0){
                    velX=moveSpeed;
                    direction = RIGHT;
                }
                else if(al_key_down(&keyState,ALLEGRO_KEY_LEFT) && x >= 4.0){
                    velX=-moveSpeed;
                    direction = LEFT;
                } else{
                    velX=0;
                    active=false;

                    if(al_key_down(&keyState,ALLEGRO_KEY_UP) && jump){
                        velY=-jumpSize;
                        jump=false;
                    }
                }
                /*
                if(Collision(x,y,200,527,51,51)) { // al_get_bitmap_width(player) = 32
                    if(direction==DOWN)
                        y-=10;
                    else if(direction==UP)
                        y+=10;
                    else if(direction==RIGHT)
                        x-=10;
                    else if(direction==LEFT)
                        x+=10;
                }
                 */
            }

            else if(events.timer.source==frameTimer){
                if(active)
                    spriteSheetX+=playerWidth/3;
                else
                    spriteSheetX=playerWidth/3;

                if(spriteSheetX>=playerWidth)
                    spriteSheetX=0;

                spriteSheetY=direction;
            }


            if(!jump)
                velY+=gravity; //al saltar, la velocidad sera hacia abajo en la pantalla aumentando en Y
            else
                velY=0;
            x+=velX;
            y+=velY;

            jump=(y+playerHeight>=bottom);

            if(jump)
                y=bottom-playerHeight;

            draw=true;
        }
        if(draw){

            al_draw_bitmap_region(player,spriteSheetX,spriteSheetY*playerHeight/2,50,50,x,y,NULL);


            //  Intercambia los buffers, ahora la ventana mostrará fond de color
            al_flip_display();

            //  La función limpia el buffer, con un color determinado, recibe como parámetro un ALLEGRO_COLOR.
            al_clear_to_color(al_map_rgb(255,255,255));

            al_draw_bitmap(background,0,0,0);
        }

    }

    //elimina el bitmap
    al_destroy_bitmap(player);
    al_destroy_bitmap(background);
    //elimina el timer
    al_destroy_timer(timer);
    //elimina el contenido bajo el puntero de ventana, esto eliminará a la ventana de la memoria.
    al_destroy_display(frame);
    //elimina la cola de eventos
    al_destroy_event_queue(event_queue);

    return 0;
}

