//
// Created by manuel on 11/11/19.
//


#include <stdlib.h>
#include <unistd.h>
#include <allegro5/allegro.h>
#include <stdio.h>
//#include <allegro5/allegro_ttf.h>
//#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#define ScreenWidth 800
#define  ScreenHeight 600



int main() {

    // Crea un puntero a un ALLEGRO_DISPLAY
    ALLEGRO_DISPLAY* frame=NULL;
    ALLEGRO_BITMAP *player=NULL;

    int playerWidtth=0;
    int playerHeight=0;

    const float FPS=60.0; //fotogramas por segundos

    enum Direction {UP,DOWN,LEFT,RIGHT};

    //  Inicia allegro5, esto es necesario para realizar cualquier función de allegro
    //  Verifica si la función devuelve 0, si es asi, generará un mensaje de
    //  error, y el programa retornará -1 lo cual denota un programa fallido
    if(!al_init())
    {
        printf("Hubo un error en la inicialización de Allegro");
        return -1;
    }


    //Funcion para redimensionar la pantalla
    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
    //al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    //al_set_new_display_flags(ALLEGRO_NOFRAME);
    //al_set_new_display_flags(ALLEGRO_OPENGL);

    //  al_create_display(X,Y) crea un puntero a un ALLEGRO_DISPLAY
    //  y crea un ALLEGRO_DISPLAY de las dimensiones especificadas, en
    //  este caso X de ancho por Y de alto
    frame = al_create_display(ScreenWidth,ScreenHeight);

    //Posicion de la ventana
    al_set_window_position(frame,200,100);

    //titulo de la ventana
    al_set_window_title(frame,"Este es el titulo de la ventana");



    if(!frame)
    {
        printf("Hubo un error en la creación de la ventana");
        return -1;
    }
    //esta funcion permite comenzar a dibujar las figuras
    al_init_primitives_addon();

    //esta funcion permite usar el teclado
    al_install_keyboard();

    //permite usar el mouse
    //al_install_mouse();

    //con esto se obtinene cual tecla es precionada en ese instante
    ALLEGRO_KEYBOARD_STATE keyState;

    //permite cargar imagenes
    al_init_image_addon();

    if(!al_init_image_addon()) {
        al_show_native_message_box(frame, "Error", "Error", "Failed to initialize al_init_image_addon!",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    player = al_load_bitmap("/home/manuel/CLionProjects/interfaz/a.png");
    //playerWidtth=al_get_bitmap_width(player);
    //playerHeight=al_get_bitmap_height(player);

    //se declara un color
    ALLEGRO_COLOR electBlue=al_map_rgb(66,66,255);
    ALLEGRO_COLOR electGreen=al_map_rgb(66,255,66);


    //array de puntos para trazar una linea
    //float points[8]={0,0,400,100,50,200,ScreenWidth,ScreenHeight};
    //dibuja una linea
    //al_draw_spline(points,electBlue,1.0);


    //actualiza la ventana cada 0.01666 milisegundos
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);


    //cola de eventos
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();

    //registra la fuente del evento, recibe una cola de eventos y el tipo de evento
    al_register_event_source(event_queue,al_get_keyboard_event_source());
    al_register_event_source(event_queue,al_get_timer_event_source(timer));
    al_register_event_source(event_queue,al_get_display_event_source(frame));
    //al_register_event_source(event_queue,al_get_mouse_event_source());

    //al_hide_mouse_cursor(frame); //muestra el cursor

    al_start_timer(timer);
    //posiciones horizontal y vertical
    float x=10,y=10;
    //velocidad del movimiento
    float moveSpeed=2;



    int direction=DOWN, sourceX=32,sourceY=0;
    bool draw=true, active=false;


    //variable para salir del loop
    bool done=false;
    //loop del juego
    while(!done) {
        //instancia un nuevo evento
        ALLEGRO_EVENT events;
        //funcion que esta a la escucha de algun evento
        al_wait_for_event(event_queue,&events);
        al_get_keyboard_state(&keyState);

        if(events.type==ALLEGRO_EVENT_KEY_UP) {
            switch (events.keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    done=true;
                    break;
            }
        }
        else if(events.type==ALLEGRO_EVENT_DISPLAY_CLOSE) {
            done = true;
        }
        if(events.type==ALLEGRO_EVENT_TIMER){
            active=true;

            if(al_key_down(&keyState,ALLEGRO_KEY_DOWN)) {
                y += moveSpeed;
                direction = DOWN;
            }
            else if(al_key_down(&keyState,ALLEGRO_KEY_UP)){
                y-=moveSpeed;
                direction = UP;
            }
            else if(al_key_down(&keyState,ALLEGRO_KEY_RIGHT)){
                x+=moveSpeed;
                direction = RIGHT;
            }
            else if(al_key_down(&keyState,ALLEGRO_KEY_LEFT)){
                x-=moveSpeed;
                direction = LEFT;
            } else{
                active=false;
            }

            if(active)
                sourceX+=al_get_bitmap_width(player)/3;
            else
                sourceX=32;

            if(sourceX>=al_get_bitmap_width(player))
                sourceX=0;

            sourceY=direction;
            draw=true;
        }
        if(draw){

            al_draw_bitmap_region(player,sourceX,sourceY*al_get_bitmap_height(player)/4,32,32,x,y,NULL);

            //pone la imagen en la ventana en la posicion (x,y)
            //al_draw_bitmap(player,x,y,0);

            //  Intercambia los buffers, ahora la ventana mostrará fond de color
            al_flip_display();

            //en este punto es donde se muestra el contenido e inmediatamente coloca el color de la ventana
            //para mostrar un nuevo cambio si que se vea el anterior


            //  La función limpia el buffer, con un color determinado, recibe como parámetro un ALLEGRO_COLOR.
            al_clear_to_color(al_map_rgb(0,0,0));
        }

    }
    //elimina la cola de eventos
    al_destroy_event_queue(event_queue);

    //elimina el bitmap
    al_destroy_bitmap(player);
    //elimina el timer
    al_destroy_timer(timer);
    //elimina el contenido bajo el puntero de ventana, esto eliminará a la ventana de la memoria.
    al_destroy_display(frame);

    return 0;
}


