//
// Created by manuel on 11/11/19.
//
/*


#include <allegro5/allegro.h>
//#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/bitmap.h>
//#include <cursesw.h>
#include <tgmath.h>

#define ScreenWidth 800
#define  ScreenHeight 600




// x, y son las coordenadas de player. ex, ey las del enemigo
bool Collision(float x, float y, float ex, float ey,int width, int height){


    if(x+width < ex || x > ex+width || y+height < ey || y > ey+height){
        return false;
    }
    return true;
}


int main() {

    int playerWidtth=0;
    int playerHeight=0;
    const float FPS=60.0; //fotogramas por segundos
    const float frameFPS=60.0;
    enum Direction {DOWN,UP,LEFT,RIGHT};
    //posiciones horizontal y vertical
    float x=10,y=10;
    //velocidad del movimiento
    float moveSpeed=3;
    float velX, velY;
    velX=velY=0;
    int direction=DOWN, sourceX=32,sourceY=0;
    bool draw=true, active=false;
    //variable para salir del loop
    bool done=false;
    const float gravity=1;
    bool jump=false;
    float jumpSpeed=15;



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
    ALLEGRO_DISPLAY* frame=NULL;
    ALLEGRO_BITMAP *player=NULL;
    ALLEGRO_BITMAP *player2=NULL;

    //se declara un color
    ALLEGRO_COLOR electBlue=al_map_rgb(66,66,255);
    ALLEGRO_COLOR electGreen=al_map_rgb(66,255,66);

    //con esto se obtinene cual tecla es precionada en ese instante
    ALLEGRO_KEYBOARD_STATE keyState;

    //actualiza la ventana cada 0.01666 milisegundos
    ALLEGRO_TIMER *timer=al_create_timer(1.0/FPS);
    ALLEGRO_TIMER *frameTimer=al_create_timer(1.0/frameFPS);

    //cola de eventos
    ALLEGRO_EVENT_QUEUE *event_queue=al_create_event_queue();

    //  al_create_display(X,Y) y crea un ALLEGRO_DISPLAY de las dimensiones especificadas
    frame = al_create_display(ScreenWidth,ScreenHeight);

    if(!frame) //si no se puede crear la ventana, muestra un error
    {
        al_show_native_message_box(NULL,NULL,NULL,"failed to init frame!",NULL,0);
        return -1;
    }

    //Posicion de la ventana
    al_set_window_position(frame,200,100);

    //Funcion para redimensionar la pantalla
    //al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);
    //al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    al_set_new_display_flags(ALLEGRO_NOFRAME);
    //al_set_new_display_flags(ALLEGRO_OPENGL);

    //titulo de la ventana
    //al_set_window_title(frame,"Este es el titulo de la ventana");


    //esta funcion permite comenzar a dibujar las figuras
    //al_init_primitives_addon();



    //permite usar el mouse
    //al_install_mouse();


    if(!al_init_image_addon()) {
        al_show_native_message_box(frame, "Error", "Error", "Failed to initialize al_init_image_addon!",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    player = al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/a.png");
    player2= al_load_bitmap("/home/manuel/CLionProjects/interfaz/imgs/a.png");
    playerWidtth=al_get_bitmap_width(player);
    playerHeight=al_get_bitmap_height(player);



    //registra la fuente del evento, recibe una cola de eventos y el tipo de evento
    al_register_event_source(event_queue,al_get_keyboard_event_source());
    al_register_event_source(event_queue,al_get_timer_event_source(timer));
    al_register_event_source(event_queue,al_get_timer_event_source(frameTimer));
    al_register_event_source(event_queue,al_get_display_event_source(frame));
    //al_register_event_source(event_queue,al_get_mouse_event_source());

    //al_hide_mouse_cursor(frame); //muestra el cursor

    al_start_timer(timer);
    al_start_timer(frameTimer);

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
        else if(events.type==ALLEGRO_EVENT_TIMER){


            if(events.timer.source==timer){
                active=true;
                if(al_key_down(&keyState,ALLEGRO_KEY_RIGHT)){
                    velX=moveSpeed;
                    direction = RIGHT;
                }
                else if(al_key_down(&keyState,ALLEGRO_KEY_LEFT)){
                    velX=-moveSpeed;
                    direction = LEFT;
                } else{
                    velX=0;
                    active=false;

                    if(al_key_down(&keyState,ALLEGRO_KEY_UP) && jump){
                        velY=-jumpSpeed;
                        jump=false;
                    }
                }
                if(Collision(x,y,200,527,32,32)) { // al_get_bitmap_width(player) = 32
                    if(direction==DOWN)
                        y-=moveSpeed;
                    else if(direction==UP)
                        y+=moveSpeed;
                    else if(direction==RIGHT)
                        x-=moveSpeed;
                    else if(direction==LEFT)
                        x+=moveSpeed;
                }
            }

            else if(events.timer.source==frameTimer){
                if(active)
                    sourceX+=al_get_bitmap_width(player)/3;
                else
                    sourceX=32; //la imagen tiene 3 imagenes horizontalmente, cada un de 32 pixel en el eje X

                if(sourceX>=al_get_bitmap_width(player))
                    sourceX=0;

                sourceY=direction;
            }


            if(!jump)
                velY+=gravity; //al saltar, la velocidad sera hacia abajo en la pantalla aumentando en Y
            else
                velY=0;
            x+=velX;
            y+=velY;

            jump=(y+32>=560);

            if(jump)
                y=560-32;

            draw=true;
        }
        if(draw){

            al_draw_bitmap_region(player,sourceX,sourceY*al_get_bitmap_height(player)/4,32,32,x,y,NULL);

            al_draw_bitmap_region(player2,0,0,32,32,200,527,NULL);
            //pone la imagen en la ventana en la posicion (x,y)
            //al_draw_bitmap(player,x,y,0);

            //  Intercambia los buffers, ahora la ventana mostrará fond de color
            al_flip_display();

            //en este punto es donde se muestra el contenido e inmediatamente coloca el color de la ventana
            //para mostrar un nuevo cambio si que se vea el anterior


            //  La función limpia el buffer, con un color determinado, recibe como parámetro un ALLEGRO_COLOR.
            al_clear_to_color(al_map_rgb(255,255,255));
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

*/