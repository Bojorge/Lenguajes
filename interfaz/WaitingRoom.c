//
// Created by manuel on 15/11/19.
//

#include "WaitingRoom.h"

#include <allegro5/haptic.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "SelectEnemies.h"


int waiting(ALLEGRO_DISPLAY* frame){



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
    ALLEGRO_BITMAP *p1=al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/p1.png");
    ALLEGRO_BITMAP *p2=al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/p2.png");
    ALLEGRO_BITMAP *waiting=al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/waiting.png");
    ALLEGRO_BITMAP *connected=al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/connected.png");
    ALLEGRO_BITMAP *choose=al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/choose.png");

    //con esto se obtinene cual tecla es precionada en ese instante
    ALLEGRO_KEYBOARD_STATE keyState;

    //cola de eventos
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();


    al_set_new_display_flags(ALLEGRO_NOFRAME);
    al_install_mouse();

    //Posicion de la ventana
    //al_set_window_position(frame,50,50);
    al_set_new_display_flags(ALLEGRO_NOFRAME);

    al_init_primitives_addon();
    if(!al_init_image_addon()) {
        al_show_native_message_box(frame, "Error", "Error", "Failed to initialize al_init_image_addon!",NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

    ALLEGRO_TIMER_EVENT *timer=al_create_timer(1.0/FPS);

    //registra la fuente del evento, recibe una cola de eventos y el tipo de evento
    al_register_event_source(event_queue,al_get_mouse_event_source());
    al_register_event_source(event_queue,al_get_display_event_source(frame));
    al_register_event_source(event_queue,al_get_timer_event_source(timer));

    //al_draw_bitmap(background,0,0,NULL);




    int x=0, y=0;

    bool done=false;

    al_start_timer(timer);



    while(!done) {
        //instancia un nuevo evento
        ALLEGRO_EVENT events;
        //funcion que esta a la escucha de algun evento
        al_wait_for_event(event_queue,&events);
        //al_get_keyboard_state(&keyState);

        if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            done=true;
            break;
        }

        else if(events.type==ALLEGRO_EVENT_MOUSE_AXES)
        {
            x=events.mouse.x;
            y=events.mouse.y;
        }

        else if(events.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(events.mouse.button & 1) {
                if(x>900 & x<1100 & y>150 & y<350){
                    displayEnemies(frame);
                }
            }
        }

        al_draw_bitmap(p1,100,100,0);
        al_draw_bitmap(p2,100,350,0);
        al_draw_bitmap(waiting,400,50,0);
        al_draw_bitmap(connected,400,300,0);
        al_draw_bitmap(choose,900,150,0);




        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));



    }

    //elimina la cola de eventos
    al_destroy_event_queue(event_queue);
    //elimina el timer
    al_destroy_timer(timer);

    if(done){
        //elimina el contenido bajo el puntero de ventana, esto eliminará a la ventana de la memoria.
        al_destroy_display(frame);
    }


    return 0;

}