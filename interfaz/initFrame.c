//
// Created by manuel on 14/11/19.
//



#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_primitives.h>
#include "SelectEnemies.h"
#include "GameMode.h"


#define ScreenWidth 1200
#define  ScreenHeight 600


int initFrame(){

    const float FPS=60.0;

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
    ALLEGRO_DISPLAY *display=NULL;
    ALLEGRO_BITMAP *background=al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/cover.png");

    //con esto se obtinene cual tecla es precionada en ese instante
    ALLEGRO_KEYBOARD_STATE keyState;



    //  al_create_display(X,Y) y crea un ALLEGRO_DISPLAY de las dimensiones especificadas
    display = al_create_display(ScreenWidth,ScreenHeight);

    if(!display) //si no se puede crear la ventana, muestra un error
    {
        al_show_native_message_box(NULL,NULL,NULL,"failed to init frame!",NULL,0);
        return -1;
    }

    al_set_window_title(display," iCE Climber ");
    al_set_new_display_flags(ALLEGRO_NOFRAME);
    al_install_mouse();

    //Posicion de la ventana
    al_set_window_position(display,50,50);
    al_set_new_display_flags(ALLEGRO_NOFRAME);

    al_init_primitives_addon();
    if(!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon!",NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);

    //cola de eventos
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();

    //registra la fuente del evento, recibe una cola de eventos y el tipo de evento
    al_register_event_source(event_queue,al_get_mouse_event_source());
    al_register_event_source(event_queue,al_get_display_event_source(display));
    al_register_event_source(event_queue,al_get_timer_event_source(timer));

    int x=0, y=0;

    bool done=false,one=false,two=false;

    al_start_timer(timer);

    while(!done && !one && !two) {
        //instancia un nuevo evento
        ALLEGRO_EVENT events;
        //funcion que esta a la escucha de algun evento
        al_wait_for_event(event_queue,&events);
        //al_get_keyboard_state(&keyState);

        if(events.type==ALLEGRO_EVENT_KEY_UP) {
            switch (events.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    done=true;
                    break;
            }
        }


        if(events.type==ALLEGRO_EVENT_MOUSE_AXES)
        {
            x=events.mouse.x;
            y=events.mouse.y;
        }

        if(events.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(events.mouse.button & 1) {
                //Si el juego es para 1 jugador se va a la pantalla de seleccionar enemigos
                if(x>412 & x<819 & y>352 & y<380){
                    one=true;
                }
                //AQUI VAN LAS OPCIONES SI SE SELECCIONAN 2 JUGADORES
                else if(x>412 & x<819 & y>404 & y<431){
                    two=true;
                }
            }
        }






        al_draw_bitmap(background,0,0,0);
        //al_draw_filled_rectangle(x,y,x+20,y+20,Green);
        al_flip_display();

    }

    //elimina la cola de eventos
    al_destroy_event_queue(event_queue);
    //elimina el bitmap
    al_destroy_bitmap(background);
    //elimina el timer
    al_destroy_timer(timer);

    if(one)
        displayEnemies(display);
    if(two)
        selectMode(display);

    //elimina el contenido bajo el puntero de ventana, esto eliminará a la ventana de la memoria.
    al_destroy_display(display);

    return 0;

}
