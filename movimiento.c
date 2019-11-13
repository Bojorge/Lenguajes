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

#define ScreenWidth 800
#define  ScreenHeight 600



int main() {

    //  Crea un puntero a un ALLEGRO_DISPLAY
    ALLEGRO_DISPLAY* frame = NULL;

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

    //al_hide_mouse_cursor(frame);

    al_start_timer(timer);
    //posiciones horizontal y vertical
    int x=10,y=10;
    //velocidad del movimiento
    int moveSpeed=2;

    int dir=DOWN;

    bool draw=true;

    //variable para salir del loop
    bool done=false;
    //loop del juego
    while(!done) {
        //instancia un nuevo evento
        ALLEGRO_EVENT events;
        //funcion que esta a la escucha de algun evento
        al_wait_for_event(event_queue,&events);

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
            al_get_keyboard_state(&keyState);

            if(al_key_down(&keyState,ALLEGRO_KEY_DOWN))
                y+=moveSpeed;
            else if(al_key_down(&keyState,ALLEGRO_KEY_UP))
                y-=moveSpeed;
            else if(al_key_down(&keyState,ALLEGRO_KEY_RIGHT))
                x+=moveSpeed;
            else if(al_key_down(&keyState,ALLEGRO_KEY_LEFT))
                x-=moveSpeed;

            draw=true;

        }
        if(draw){
            draw=false;
            //forma un triangulo con el borde de cierto color
            al_draw_rectangle(x,y,x+20,y+20,electBlue,5.0);
            //rellena el triangulo con cierto color
            al_draw_filled_rectangle(x,y,x+20,y+20,electGreen);

            //  Intercambia los buffers, ahora la ventana mostrará tendrá fondo
            //  de color. Si minimiza la ventana y la vuelve restaurar, se
            //  dará cuenta que ahora la pantalla muestra lo que estuvo detrás.
            //  Esto es porque el buffer ahora tiene lo que estaba detrás de la
            //  ventana.
            al_flip_display();

            //en este punto es donde se muestra el contenido e inmediatamente coloca el color de la ventana
            //para mostrar un nuevo cambio si que se vea el anterior


            //  La siguiente función limpia el buffer, con un color determinado,
            //  recibe como parámetro un ALLEGRO_COLOR.
            //  La función al_map_rgb(R,G,B) recibe como tres enteres sin signo,
            //  cada uno determina la cantidad del color rojo, verde y azul
            //  respectivamente; esta función devuelve un ALLEGRO_COLOR con lo
            //  que encaja perfecto con el parámetro que recibe la función
            //  al_clear_to_color(...)
            al_clear_to_color(al_map_rgb(0,0,0));
        }

    }
    //elimina la cola de eventos
    al_destroy_event_queue(event_queue);

    //elimina el timer
    al_destroy_timer(timer);
    //elimina el contenido bajo el puntero de ventana, esto eliminará a la ventana de la memoria.
    al_destroy_display(frame);

    return 0;
}