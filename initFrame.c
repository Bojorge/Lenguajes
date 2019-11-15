//
// Created by manuel on 14/11/19.
//

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro_primitives.h>


#define ScreenWidth 1100
#define  ScreenHeight 619


void main(){
    if(!al_init())
    {
        al_show_native_message_box(NULL,NULL,NULL,"failed to init allegro!",NULL,0);
    }

    //esta funcion permite usar el teclado
    al_install_keyboard();

    //permite cargar imagenes
    al_init_image_addon();

    // Crea un puntero a un DISPLAY y un BITMAP
    ALLEGRO_DISPLAY *frame=NULL;
    ALLEGRO_BITMAP *background=al_load_bitmap("/home/manuel/CLionProjects/interfaz/cover.png");

    //con esto se obtinene cual tecla es precionada en ese instante
    ALLEGRO_KEYBOARD_STATE keyState;

    //cola de eventos
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();

    //  al_create_display(X,Y) y crea un ALLEGRO_DISPLAY de las dimensiones especificadas
    frame = al_create_display(ScreenWidth,ScreenHeight);

    if(!frame) //si no se puede crear la ventana, muestra un error
    {
        al_show_native_message_box(NULL,NULL,NULL,"failed to init frame!",NULL,0);
    }

    al_install_mouse();

    //Posicion de la ventana
    al_set_window_position(frame,50,50);
    al_set_new_display_flags(ALLEGRO_NOFRAME);

    al_init_primitives_addon();
    if(!al_init_image_addon()) {
        al_show_native_message_box(frame, "Error", "Error", "Failed to initialize al_init_image_addon!",NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

    ALLEGRO_TIMER_EVENT *timer=al_create_timer(1.0/60);

    //registra la fuente del evento, recibe una cola de eventos y el tipo de evento
    al_register_event_source(event_queue,al_get_mouse_event_source());
    al_register_event_source(event_queue,al_get_display_event_source(frame));
    al_register_event_source(event_queue,al_get_timer_event_source(timer));

    //al_draw_bitmap(background,0,0,NULL);




    int x=10, y=10, moveSpeed=5;

    ALLEGRO_COLOR Green=al_map_rgb(0,255,0);
    ALLEGRO_COLOR Blue=al_map_rgb(0,0,255);
    ALLEGRO_COLOR Red=al_map_rgb(255,0,0);

    //al_flip_display();

    //al_hide_mouse_cursor(frame);

    bool done=false;

    al_start_timer(timer);



    while(!done) {
        //instancia un nuevo evento
        ALLEGRO_EVENT events;
        //funcion que esta a la escucha de algun evento
        al_wait_for_event(event_queue,&events);
        //al_get_keyboard_state(&keyState);

        if(events.type==ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done=true;
        }
        else if(events.type==ALLEGRO_EVENT_MOUSE_AXES)
        {
            x=events.mouse.x;
            y=events.mouse.y;
        }

        else if(events.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        {
            if(events.mouse.button & 1) {
                if(x>0 & x>200 & y>0 & y>200){
                    al_draw_filled_rectangle(x,y,x+20,y+20,Green);
                }

            }
        }


        al_draw_bitmap(background,0,0,NULL);
        //al_draw_filled_rectangle(x,y,x+20,y+20,Green);
        al_flip_display();



    }

    //elimina la cola de eventos
    al_destroy_event_queue(event_queue);
    //elimina el bitmap
    al_destroy_bitmap(background);
    //elimina el timer
    al_destroy_timer(timer);
    //elimina el contenido bajo el puntero de ventana, esto eliminará a la ventana de la memoria.
    al_destroy_display(frame);

}