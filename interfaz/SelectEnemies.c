//
// Created by manuel on 15/11/19.
//

#include <allegro5/haptic.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "SelectEnemies.h"
#include "game1p.h"


int displayEnemies(ALLEGRO_DISPLAY* frame){



    const float FPS=60.0;

    if(!al_init())
    {
        al_show_native_message_box(NULL,NULL,NULL,"failed to init allegro!",NULL,0);
        return -1;
    }

    //esta funcion permite usar el teclado
    al_install_keyboard();

    al_init_primitives_addon();

    //permite cargar imagenes
    al_init_image_addon();

    if(!al_init_image_addon()) {
        al_show_native_message_box(frame, "Error", "Error", "Failed to initialize al_init_image_addon!",NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

    // Crea un puntero a un BITMAP
    ALLEGRO_BITMAP *bear=al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/Bear.png");
    ALLEGRO_BITMAP *yeti=al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/Yeti.png");
    ALLEGRO_BITMAP *seal=al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/Seal.png");
    ALLEGRO_BITMAP *penguin=al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/Penguin.png");
    ALLEGRO_BITMAP *button=al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/startButton.png");

    //con esto se obtinene cual tecla es precionada en ese instante
    ALLEGRO_KEYBOARD_STATE keyState;


    al_set_new_display_flags(ALLEGRO_NOFRAME);
    al_install_mouse();

    //Posicion de la ventana
    //al_set_window_position(frame,50,50);
    al_set_new_display_flags(ALLEGRO_NOFRAME);



    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);

    //cola de eventos
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();

    //registra la fuente del evento, recibe una cola de eventos y el tipo de evento
    al_register_event_source(event_queue,al_get_mouse_event_source());
    al_register_event_source(event_queue,al_get_display_event_source(frame));
    al_register_event_source(event_queue,al_get_timer_event_source(timer));

    //al_draw_bitmap(background,0,0,NULL);




    int x=0, y=0;

    ALLEGRO_COLOR BearAvailable=al_map_rgb(0,255,0);
    ALLEGRO_COLOR PenguinAvailable=al_map_rgb(0,255,0);
    ALLEGRO_COLOR SealAvailable=al_map_rgb(0,255,0);
    ALLEGRO_COLOR YetiAvailable=al_map_rgb(0,255,0);

    ALLEGRO_COLOR BearSelected=al_map_rgb(255,0,0);
    ALLEGRO_COLOR PenguinSelected=al_map_rgb(255,0,0);
    ALLEGRO_COLOR SealSelected=al_map_rgb(255,0,0);
    ALLEGRO_COLOR YetiSelected=al_map_rgb(255,0,0);

    //al_flip_display();

    //al_hide_mouse_cursor(frame);

    bool done=false,start=false;

    al_start_timer(timer);



    while(!done || !start) {
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
                if(x>100 & x<300 & y>50 & y<250){
                    BearAvailable=BearSelected;
                    //enviarle al server cero
                }
                else if(x>400 & x<600 & y>50 & y<250){
                    PenguinAvailable=PenguinSelected;
                    //enviarle al server uno
                }
                else if(x>100 & x<300 & y>300 & y<500){
                    SealAvailable=SealSelected;
                    //enviarle al server dos
                }
                else if(x>400 & x<600 & y>300 & y<500){
                    YetiAvailable=YetiSelected;
                    //enviarle al server tres
                }


                else if(x>800 & x<1050 & y>150 & y<400){ //si el boton de inicio es precionado, comienza el juego
                    start=true;
                    break;
                }
            }
        }

        al_draw_bitmap(bear,100,50,0);
        al_draw_rectangle(100,50,300,250,BearAvailable,10);

        al_draw_bitmap(penguin,400,50,0);
        al_draw_rectangle(400,50,600,250,PenguinAvailable,10);

        al_draw_bitmap(seal,100,300,0);
        al_draw_rectangle(100,300,300,500,SealAvailable,10);

        al_draw_bitmap(yeti,400,300,0);
        al_draw_rectangle(400,300,600,500,YetiAvailable,10);

        al_draw_bitmap(button,800,150,0);

        al_flip_display();
        al_clear_to_color(al_map_rgb(0,0,0));

    }

    //elimina la cola de eventos
    al_destroy_event_queue(event_queue);
    //elimina el timer
    al_destroy_timer(timer);

    if(start)
        play1(frame);
    if(done)
        //elimina el contenido bajo el puntero de ventana, esto eliminará a la ventana de la memoria.
        al_destroy_display(frame);

    return 0;

}