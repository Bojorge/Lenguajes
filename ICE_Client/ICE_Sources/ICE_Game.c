
#include "../ICE_Headers/ICE_Game.h"
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_native_dialog.h>
#include "allegro5/allegro_primitives.h"
#include <stdio.h>
#include "../ICE_Headers/ICE_Json.h"
#include "../ICE_Headers/ICE_Socket.h"



//************************************************************************************************************************************//
//**************************************************** GLOBAL GAME FIELDS ************************************************************//

//********************* WINDOW *********************//

const  int screenW=1000;//DETERMINES WINDOW WIDTH
const  int screenH=600;//DETERMINES WINDOW HEIGHT

//****************** GAME FIELDS *******************//

const float FPS=60;//DETERMINES FRAMES PER SECOND IN THE GAME
const float AnimationFPS=10.0;//DETERMINES ANIMATION SPEED

float movementSpeed[2]={4.0, 7.0};//CHARACTERS MOVEMENT SPEED
float acceleration[2]={0,9.8};//CHARACTER MOVEMENT ACCELERATION

int currentScene=0;//Determines WHICH SCENE THE USER IS GONNA SEE

//******************** PLAYERS *********************//

float popoPosition[2]={718,506-81};//POPO POSITION
float popoAnimation[2]={0,0};//POPO ANIMATION FRAMES
float popoScore=0;//POPO SCORE
float popoLives=3;//POPO LIVES

float nanaPosition[2]={250,506-81};//NANA POSITION
float nanaAnimation[2]={0,0};//NANA ANIMATION FRAMES
float nanaScore=0;//NANA SCORE
float nanaLives=3;//NANA LIVES

//******************** ENEMIES *********************//

float dinoPosition[2]={125,506};//DINO POSITION
float dinoAnimation[2]={0,0};//DINO ANIMATION FRAMES
int dinoDirection=1;//DINO DIRECTION
int dir=1;


//******************** CAMARA **********************//

float camaraPosition[2]={0,-2850};



//************************************************************************************************************************************//
//******************************************************* GAME COMPONENTS ************************************************************//

//********************* CAMARA *********************//

void refreshCamara(){
    if (popoPosition[1]<=200 || nanaPosition[1]<=200 || dinoPosition[1]<=300 & dinoPosition[1]>200){
        camaraPosition[1]+=6.5;
    }

    if(camaraPosition[1]>=0){
        camaraPosition[1]=0;
    }
}

void restartCamara(){
    camaraPosition[0]=0;
    camaraPosition[1]=-2850;
}

//******************* ANIMATIONS *******************//

void animateEnemy(ALLEGRO_BITMAP *dino, float dinoPosition[] ,float dinoAnimation[], int dir){


    //Animation
    dinoAnimation[0]+=al_get_bitmap_width(dino)/3;
    if(dinoAnimation[0]>=al_get_bitmap_width(dino)){
        dinoAnimation[0]=0;
    }
    //Direction
    if(dir==0 ){
        dinoAnimation[1]=0;
        if(dinoPosition[0] >= 4.0){
            dinoPosition[0]-=25;
        }else{
            dir=1;
        }
    }
    else if (dir==1 ){
        dinoAnimation[1]=(al_get_bitmap_height(dino)/2);
        if(dinoPosition[0]<=(996-al_get_bitmap_width(dino)/3)){
            dinoPosition[0]+=25;
        }else{

            dir=0;
        }
    }
}


//****************WINNER***************
int winnerScene(ALLEGRO_DISPLAY *display,int popoBears,int nanaBears,int popoSeals,int nanaSeals,int popoPenguins,int nanaPenguins,int popoYetis,int nanaYetis){
    //al_clear_to_color(al_map_rgb(0,0,0));
                                            
    ALLEGRO_BITMAP *score = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/score.png");
    ALLEGRO_BITMAP *zero=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/zero.png");
    ALLEGRO_BITMAP *one=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/one.png");
    ALLEGRO_BITMAP *two=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/two.png");
    ALLEGRO_BITMAP *three=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/three.png");
    ALLEGRO_BITMAP *four=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/four.png");
    ALLEGRO_BITMAP *five=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/five.png");
    ALLEGRO_BITMAP *six=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/six.png");
    ALLEGRO_BITMAP *seven=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/seven.png");
    ALLEGRO_BITMAP *eight=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/eight.png");
    ALLEGRO_BITMAP *nine=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/nine.png");
    ALLEGRO_BITMAP *plusTen=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/plusTen.png");


    ALLEGRO_BITMAP *popoWinner = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/popoWinner.png");
    ALLEGRO_BITMAP *nanaWinner = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/nanaWinner.png");

    if(!score || !zero || !one || !two || !three || !four || !five || !six || !seven || !eight || !nine || !plusTen || popoWinner || nanaWinner){
        al_show_native_message_box(display, "Error", "Error", "Fail to create label-number-score",NULL, ALLEGRO_MESSAGEBOX_ERROR);

    }
    al_draw_bitmap(score,0,0,0);


    if((popoBears+popoSeals+popoYetis+popoPenguins) > (nanaBears+nanaSeals+nanaYetis+nanaPenguins)){
        al_draw_bitmap(popoWinner,400,400,0);
    }
    else if((popoBears+popoSeals+popoYetis+popoPenguins) < (nanaBears+nanaSeals+nanaYetis+nanaPenguins)){
        al_draw_bitmap(nanaWinner,400,400,0);
    }


///////////////////// ENEMIES KILLED BY POPO ///////////////////

    if(popoBears >= 0){
        if(popoBears==0)
            al_draw_bitmap(zero,100,100,0);
        if(popoBears==1)
            al_draw_bitmap(one,100,100,0);
        if(popoBears==2)
            al_draw_bitmap(two,100,100,0);
        if(popoBears==3)
            al_draw_bitmap(three,100,100,0);
        if(popoBears==4)
            al_draw_bitmap(four,100,100,0);
        if(popoBears==5)
            al_draw_bitmap(five,100,100,0);
        if(popoBears==6)
            al_draw_bitmap(six,100,100,0);
        if(popoBears==7)
            al_draw_bitmap(seven,100,100,0);
        if(popoBears==8)
            al_draw_bitmap(eight,100,100,0);
        if(popoBears==9)
            al_draw_bitmap(nine,100,100,0);
        if(popoBears>=10)
            al_draw_bitmap(plusTen,100,100,0);
    }


    if(popoYetis >= 0){
        if(popoYetis==0)
            al_draw_bitmap(zero,100,100,0);
        if(popoYetis==1)
            al_draw_bitmap(one,100,100,0);
        if(popoYetis==2)
            al_draw_bitmap(two,100,100,0);
        if(popoYetis==3)
            al_draw_bitmap(three,100,100,0);
        if(popoYetis==4)
            al_draw_bitmap(four,100,100,0);
        if(popoYetis==5)
            al_draw_bitmap(five,100,100,0);
        if(popoYetis==6)
            al_draw_bitmap(six,100,100,0);
        if(popoYetis==7)
            al_draw_bitmap(seven,100,100,0);
        if(popoYetis==8)
            al_draw_bitmap(eight,100,100,0);
        if(popoYetis==9)
            al_draw_bitmap(nine,100,100,0);
        if(popoYetis>=10)
            al_draw_bitmap(plusTen,100,100,0);
    }


    if(popoSeals >= 0){
        if(popoSeals==0)
            al_draw_bitmap(zero,100,100,0);
        if(popoSeals==1)
            al_draw_bitmap(one,100,100,0);
        if(popoSeals==2)
            al_draw_bitmap(two,100,100,0);
        if(popoSeals==3)
            al_draw_bitmap(three,100,100,0);
        if(popoSeals==4)
            al_draw_bitmap(four,100,100,0);
        if(popoSeals==5)
            al_draw_bitmap(five,100,100,0);
        if(popoSeals==6)
            al_draw_bitmap(six,100,100,0);
        if(popoSeals==7)
            al_draw_bitmap(seven,100,100,0);
        if(popoSeals==8)
            al_draw_bitmap(eight,100,100,0);
        if(popoSeals==9)
            al_draw_bitmap(nine,100,100,0);
        if(popoSeals>=10)
            al_draw_bitmap(plusTen,100,100,0);
    }



    if(popoPenguins >= 0){
        if(popoPenguins==0)
            al_draw_bitmap(zero,100,100,0);
        if(popoPenguins==1)
            al_draw_bitmap(one,100,100,0);
        if(popoPenguins==2)
            al_draw_bitmap(two,100,100,0);
        if(popoPenguins==3)
            al_draw_bitmap(three,100,100,0);
        if(popoPenguins==4)
            al_draw_bitmap(four,100,100,0);
        if(popoPenguins==5)
            al_draw_bitmap(five,100,100,0);
        if(popoPenguins==6)
            al_draw_bitmap(six,100,100,0);
        if(popoPenguins==7)
            al_draw_bitmap(seven,100,100,0);
        if(popoPenguins==8)
            al_draw_bitmap(eight,100,100,0);
        if(popoPenguins==9)
            al_draw_bitmap(nine,100,100,0);
    }

///////////////////// ENEMIES KILLED BY NANA ///////////////////
    if(nanaBears >= 0){
        if(nanaBears==0)
            al_draw_bitmap(zero,100,100,0);
        if(nanaBears==1)
            al_draw_bitmap(one,100,100,0);
        if(nanaBears==2)
            al_draw_bitmap(two,100,100,0);
        if(nanaBears==3)
            al_draw_bitmap(three,100,100,0);
        if(nanaBears==4)
            al_draw_bitmap(four,100,100,0);
        if(nanaBears==5)
            al_draw_bitmap(five,100,100,0);
        if(nanaBears==6)
            al_draw_bitmap(six,100,100,0);
        if(nanaBears==7)
            al_draw_bitmap(seven,100,100,0);
        if(nanaBears==8)
            al_draw_bitmap(eight,100,100,0);
        if(nanaBears==9)
            al_draw_bitmap(nine,100,100,0);
        if(nanaBears>=10)
            al_draw_bitmap(plusTen,100,100,0);
    }


    if(nanaYetis >= 0){
        if(nanaYetis==0)
            al_draw_bitmap(zero,100,100,0);
        if(nanaYetis==1)
            al_draw_bitmap(one,100,100,0);
        if(nanaYetis==2)
            al_draw_bitmap(two,100,100,0);
        if(nanaYetis==3)
            al_draw_bitmap(three,100,100,0);
        if(nanaYetis==4)
            al_draw_bitmap(four,100,100,0);
        if(nanaYetis==5)
            al_draw_bitmap(five,100,100,0);
        if(nanaYetis==6)
            al_draw_bitmap(six,100,100,0);
        if(nanaYetis==7)
            al_draw_bitmap(seven,100,100,0);
        if(nanaYetis==8)
            al_draw_bitmap(eight,100,100,0);
        if(nanaYetis==9)
            al_draw_bitmap(nine,100,100,0);
        if(nanaYetis>=10)
            al_draw_bitmap(plusTen,100,100,0);
    }


    if(nanaSeals >= 0){
        if(nanaSeals==0)
            al_draw_bitmap(zero,100,100,0);
        if(nanaSeals==1)
            al_draw_bitmap(one,100,100,0);
        if(nanaSeals==2)
            al_draw_bitmap(two,100,100,0);
        if(nanaSeals==3)
            al_draw_bitmap(three,100,100,0);
        if(nanaSeals==4)
            al_draw_bitmap(four,100,100,0);
        if(nanaSeals==5)
            al_draw_bitmap(five,100,100,0);
        if(nanaSeals==6)
            al_draw_bitmap(six,100,100,0);
        if(nanaSeals==7)
            al_draw_bitmap(seven,100,100,0);
        if(nanaSeals==8)
            al_draw_bitmap(eight,100,100,0);
        if(nanaSeals==9)
            al_draw_bitmap(nine,100,100,0);
        if(nanaSeals>=10)
            al_draw_bitmap(plusTen,100,100,0);
    }



    if(nanaPenguins >= 0){
        if(nanaPenguins==0)
            al_draw_bitmap(zero,100,100,0);
        if(nanaPenguins==1)
            al_draw_bitmap(one,100,100,0);
        if(nanaPenguins==2)
            al_draw_bitmap(two,100,100,0);
        if(nanaPenguins==3)
            al_draw_bitmap(three,100,100,0);
        if(nanaPenguins==4)
            al_draw_bitmap(four,100,100,0);
        if(nanaPenguins==5)
            al_draw_bitmap(five,100,100,0);
        if(nanaPenguins==6)
            al_draw_bitmap(six,100,100,0);
        if(nanaPenguins==7)
            al_draw_bitmap(seven,100,100,0);
        if(nanaPenguins==8)
            al_draw_bitmap(eight,100,100,0);
        if(nanaPenguins==9)
            al_draw_bitmap(nine,100,100,0);
    }





    al_destroy_bitmap(score);
    al_destroy_bitmap(one);
    al_destroy_bitmap(two);
    al_destroy_bitmap(three);
    al_destroy_bitmap(four);
    al_destroy_bitmap(five);
    al_destroy_bitmap(six);
    al_destroy_bitmap(seven);
    al_destroy_bitmap(eight);
    al_destroy_bitmap(nine);
    al_destroy_bitmap(plusTen);
    al_destroy_bitmap(popoWinner);
    al_destroy_bitmap(nanaWinner);

    return 0;

}







//******************* Collisions *******************//
bool Collision(float xPlayer, float yPlayer, float xObstacle, float yObstacle,int playerWidth, int playerHeight,int ObstacleWidth, int ObstacleHeight){

    if(xPlayer+playerWidth <= xObstacle || xPlayer >= xObstacle+ObstacleWidth || yPlayer+playerHeight <= yObstacle+68 || yPlayer >= yObstacle+ObstacleHeight){
        return false;
    }
    return true;
}


//******************* BLOCKS *******************//
int createBlocks(ALLEGRO_DISPLAY *display,int blockX,int blockY,int level){


    ALLEGRO_BITMAP *block=NULL;
    block=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/Blocks.png");

    if(!block){
        al_show_native_message_box(display, "Error", "Error", "Fail to create block",NULL, ALLEGRO_MESSAGEBOX_ERROR);

        return 0;
    }

    if(level==1)
        al_draw_bitmap_region(block,0,0,al_get_bitmap_width(block)/3,al_get_bitmap_height(block),blockX,blockY,0);
    else if(level==2)
        al_draw_bitmap_region(block,al_get_bitmap_width(block)/3,0,al_get_bitmap_width(block)/3,al_get_bitmap_height(block),blockX,blockY,0);
    else if(level==3)
        al_draw_bitmap_region(block,(al_get_bitmap_width(block)/3)*2,0,al_get_bitmap_width(block)/3,al_get_bitmap_height(block),blockX,blockY,0);


    al_destroy_bitmap(block);

}


//************************************************************************************************************************************//
//********************************************************* GAME SCENES **************************************************************//

//****************** TITLE SCENE *******************//

int titleScene(ALLEGRO_DISPLAY *display){

    //INITIALIZE EVENT QUEUE
    ALLEGRO_EVENT_QUEUE *eventQueue=NULL;

    //INITIALIZE TIMERS
    ALLEGRO_TIMER  *timer=NULL;

    //INITIALIZE IMAGES
    ALLEGRO_BITMAP *background=NULL;

    //INITIALIZE SOUNDS
    ALLEGRO_SAMPLE *titleMusic=NULL;

    //INITIALIZE FLAGS
    bool selecting=true;
    bool redraw=true;

    //INITIALIZE MOUSE POSITION
    float mouseX;
    float mouseY;

    //DECLARE TIMERS
    timer = al_create_timer(1.0 / FPS);

    //VALIDATE TIMERS
    if(!timer){
        al_show_native_message_box(display, "Error", "Error", "Fail to create timer",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return 0;
    }

    //LOAD IMAGES
    background = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/TitleScreen.jpeg");

    //VALIDATE IMAGES
    if(!background) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image file",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_timer(timer);
        al_destroy_display(display);
        return 0;
    }

    //LOAD AUDIO FILES
    titleMusic = al_load_sample("/home/manuel/Descargas/ICE_Climber/ICE_Client/_sounds/_TitleScreen.wav" );

    //VALIDATE AUDIO FILES
    if (!titleMusic) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load audio clip",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_bitmap(background);
        return 0;
    }

    //DECLARE EVENT QUEUE
    eventQueue=al_create_event_queue();

    //VALIDATE EVENT QUEUE
    if(!eventQueue){
        al_show_native_message_box(display, "Error", "Error", "Fail to create Event Queue",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_timer(timer);
        al_destroy_sample(titleMusic);
        al_destroy_bitmap(background);
        al_destroy_display(display);
        return 0;
    }

    //REGISTER EVENTS TO EVENT QUEUE (LINK THEM)
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_mouse_event_source());

    //SET DISPLAY BACKGROUND COLOR
    al_clear_to_color(al_map_rgb(0,0,0));

    //PLAY TITLE MUSIC
    al_play_sample(titleMusic, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    //START TIMERS
    al_start_timer(timer);

    while(selecting){

        //ADD EVENTS TO QUEUE
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue,&event);

        //SET REDRAW TRUE
        if(event.type == ALLEGRO_EVENT_TIMER){
            redraw=true;
        }

        //CLOSE WINDOW
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            currentScene=4;
            break;
        }

        //ASSIGN MOUSE POSITION VALUES
        else if(event.type==ALLEGRO_EVENT_MOUSE_AXES)
        {
            mouseX=event.mouse.x;
            mouseY=event.mouse.y;
        }

        //VALIDATE MOUSE CLICK
        else if(event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

            //SELECT ONE PLAYER MODE
            if(mouseX>309 & mouseX<716 & mouseY>352 & mouseY<380){
                currentScene=2;
                break;
            }
            //SELECT TWO PLAYERS MODE
            else if(mouseX>309 & mouseX<716 & mouseY>439 & mouseY<466){
                currentScene=1;
                break;
            }
        }

        //DRAWING TO DISPLAY
        if(redraw && al_is_event_queue_empty(eventQueue)){
            redraw=false;
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_bitmap(background,0,0,0);
            al_flip_display();
        }

    }

    //FREE MEMORY
    al_destroy_timer(timer);
    al_destroy_event_queue(eventQueue);
    al_destroy_sample(titleMusic);
    al_destroy_bitmap(background);

    return 0;
}

//***************** GAME MODE SCENE ****************//

int gameModeScene(ALLEGRO_DISPLAY *display){

    //INITIALIZE EVENT QUEUE
    ALLEGRO_EVENT_QUEUE *eventQueue=NULL;

    //INITIALIZE TIMERS
    ALLEGRO_TIMER  *timer=NULL;

    //INITIALIZE IMAGES
    ALLEGRO_BITMAP *background=NULL;
    ALLEGRO_BITMAP *screenMode=NULL;
    ALLEGRO_BITMAP *localMode=NULL;
    ALLEGRO_BITMAP *onlineMode=NULL;

    //INITIALIZE SOUNDS
    ALLEGRO_SAMPLE *titleMusic=NULL;

    //INITIALIZE FLAGS
    bool selecting=true;
    bool redraw=true;

    //INITIALIZE MOUSE POSITION
    float mouseX;
    float mouseY;

    //DECLARE TIMERS
    timer = al_create_timer(1.0 / FPS);

    //VALIDATE TIMERS
    if(!timer){
        al_show_native_message_box(display, "Error", "Error", "Fail to create timer",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return 0;
    }

    //LOAD IMAGES
    background = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/Backgrounds.png");
    screenMode = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/ScreenMode.png");
    localMode = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/LocalMode.png");
    onlineMode = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/OnlineMode.png");

    //VALIDATE IMAGES
    if(!background || !screenMode || !localMode || !onlineMode) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image file",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_timer(timer);
        al_destroy_display(display);
        return 0;
    }

    //LOAD AUDIO FILES
    titleMusic = al_load_sample("/home/manuel/Descargas/ICE_Climber/ICE_Client/_sounds/_TitleScreen.wav" );

    //VALIDATE AUDIO FILES
    if (!titleMusic) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load audio clip",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_bitmap(background);
        al_destroy_bitmap(screenMode);
        al_destroy_bitmap(localMode);
        al_destroy_bitmap(onlineMode);

        return 0;
    }

    //DECLARE EVENT QUEUE
    eventQueue=al_create_event_queue();

    //VALIDATE EVENT QUEUE
    if(!eventQueue){
        al_show_native_message_box(display, "Error", "Error", "Fail to create Event Queue",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_timer(timer);
        al_destroy_sample(titleMusic);
        al_destroy_bitmap(background);
        al_destroy_bitmap(screenMode);
        al_destroy_bitmap(localMode);
        al_destroy_bitmap(onlineMode);
        al_destroy_display(display);
        return 0;
    }

    //REGISTER EVENTS TO EVENT QUEUE (LINK THEM)
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_mouse_event_source());

    //SET DISPLAY BACKGROUND COLOR
    al_clear_to_color(al_map_rgb(0,0,0));

    //PLAY TITLE MUSIC
    al_play_sample(titleMusic, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    //START TIMERS
    al_start_timer(timer);

    while(selecting){

        //ADD EVENTS TO QUEUE
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue,&event);

        //SET REDRAW TRUE
        if(event.type == ALLEGRO_EVENT_TIMER){
            redraw=true;
        }

            //CLOSE WINDOW
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            currentScene=4;
            break;
        }

            //ASSIGN MOUSE POSITION VALUES
        else if(event.type==ALLEGRO_EVENT_MOUSE_AXES)
        {
            mouseX=event.mouse.x;
            mouseY=event.mouse.y;
        }
            //VALIDATE MOUSE CLICK
        else if(event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

            //SELECT SAME SCREEN MODE
            if(mouseX>177.5 & mouseX<822.5 & mouseY>150 & mouseY<150+al_get_bitmap_height(screenMode)){
                currentScene=2;
                break;
            }
            //SELECT ONLINE MODE
            else if(mouseX>283 & mouseX<717 & mouseY>250 & mouseY<250+al_get_bitmap_height(onlineMode)){
                currentScene=2;
                break;
            }
            //SELECT LOCAL MODE
            else if(mouseX>290.5 & mouseX<709.5 & mouseY>350 & mouseY<350+al_get_bitmap_height(localMode)){
                currentScene=2;
                break;
            }
        }

        //DRAWING TO DISPLAY
        if(redraw && al_is_event_queue_empty(eventQueue)){
            redraw=false;
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_bitmap_region(background,1035,0,1000,3450,0,-2850,0);
            al_draw_bitmap(screenMode,screenW/2-al_get_bitmap_width(screenMode)/2,150,0);
            al_draw_bitmap(onlineMode,screenW/2-al_get_bitmap_width(onlineMode)/2,250,0);
            al_draw_bitmap(localMode,screenW/2-al_get_bitmap_width(localMode)/2,350,0);
            al_flip_display();
        }

    }

    //FREE MEMORY
    al_destroy_timer(timer);
    al_destroy_event_queue(eventQueue);
    al_destroy_sample(titleMusic);
    al_destroy_bitmap(background);
    al_destroy_bitmap(screenMode);
    al_destroy_bitmap(localMode);
    al_destroy_bitmap(onlineMode);

    return 0;

}

//************* ENEMY SELECTION SCENE **************//

int enemySelectionScene(ALLEGRO_DISPLAY *display){

    //INITIALIZE EVENT QUEUE
    ALLEGRO_EVENT_QUEUE *eventQueue=NULL;

    //INITIALIZE TIMERS
    ALLEGRO_TIMER  *timer=NULL;

    //INITIALIZE IMAGES
    ALLEGRO_BITMAP *background=NULL;
    ALLEGRO_BITMAP *titleText=NULL;
    ALLEGRO_BITMAP *playText=NULL;
    ALLEGRO_BITMAP *Oso=NULL;
    ALLEGRO_BITMAP *Yeti=NULL;
    ALLEGRO_BITMAP *Foca=NULL;
    ALLEGRO_BITMAP *Pajaro=NULL;

    //INITIALIZE SOUNDS
    ALLEGRO_SAMPLE *titleMusic=NULL;

    //INITIALIZE FLAGS
    bool osoSelected=false;
    bool yetiSelected=false;
    bool focaSelected=false;
    bool pajaroSelected=false;
    bool selecting=true;
    bool redraw=true;


    //INITIALIZE RECTANGLE VALUES
    float rectangleW=100;
    float rectangleH=100;

    //INITIALIZE MOUSE POSITION
    float mouseX;
    float mouseY;

    //DECLARE TIMERS
    timer = al_create_timer(1.0 / FPS);

    //VALIDATE TIMERS
    if(!timer){
        al_show_native_message_box(display, "Error", "Error", "Fail to create timer",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        return 0;
    }

    //DECLARE  COLORS
    ALLEGRO_COLOR enemyAvailable= al_map_rgb(0,43.9,92.5);
    ALLEGRO_COLOR enemySelected= al_map_rgb(89.4, 0, 34.5);
    ALLEGRO_COLOR osoColor=enemyAvailable;
    ALLEGRO_COLOR yetiColor=enemyAvailable;
    ALLEGRO_COLOR focaColor=enemyAvailable;
    ALLEGRO_COLOR pajaroColor=enemyAvailable;

    //LOAD IMAGES
    background = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/Backgrounds.png");
    titleText = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/SelectEnemy.png");
    playText = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/PLAY.png");
    Oso = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/Oso.png");
    Yeti = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/Yeti.png");
    Foca = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/Foca.png");
    Pajaro = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/Pajaro.png");

    //VALIDATE IMAGES
    if(!background || !titleText || !playText || !Oso || !Yeti || !Foca || !Pajaro) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image file",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_timer(timer);
        al_destroy_display(display);
        return 0;
    }

    //LOAD AUDIO FILES
    titleMusic = al_load_sample("/home/manuel/Descargas/ICE_Climber/ICE_Client/_sounds/_TitleScreen.wav" );

    //VALIDATE AUDIO FILES
    if (!titleMusic) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load audio clip",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_bitmap(background);
        al_destroy_bitmap(titleText);
        al_destroy_bitmap(playText);
        al_destroy_bitmap(Oso);
        al_destroy_bitmap(Yeti);
        al_destroy_bitmap(Foca);
        al_destroy_bitmap(Pajaro);

        return 0;
    }

    //DECLARE EVENT QUEUE
    eventQueue=al_create_event_queue();

    //VALIDATE EVENT QUEUE
    if(!eventQueue){
        al_show_native_message_box(display, "Error", "Error", "Fail to create Event Queue",NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_timer(timer);
        al_destroy_sample(titleMusic);
        al_destroy_bitmap(background);
        al_destroy_bitmap(titleText);
        al_destroy_bitmap(playText);
        al_destroy_bitmap(Oso);
        al_destroy_bitmap(Yeti);
        al_destroy_bitmap(Foca);
        al_destroy_bitmap(Pajaro);
        al_destroy_display(display);
        return 0;
    }

    //REGISTER EVENTS TO EVENT QUEUE (LINK THEM)
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_mouse_event_source());

    //SET DISPLAY BACKGROUND COLOR
    al_clear_to_color(al_map_rgb(0,0,0));

    //PLAY TITLE MUSIC
    al_play_sample(titleMusic, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);

    //START TIMERS
    al_start_timer(timer);

    while(selecting){

        //ADD EVENTS TO QUEUE
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue,&event);

        //SET REDRAW TRUE
        if(event.type == ALLEGRO_EVENT_TIMER){
            redraw=true;
        }

            //CLOSE WINDOW
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            currentScene=4;
            break;
        }

            //ASSIGN MOUSE POSITION VALUES
        else if(event.type==ALLEGRO_EVENT_MOUSE_AXES)
        {
            mouseX=event.mouse.x;
            mouseY=event.mouse.y;
        }
            //VALIDATE MOUSE CLICK
        else if(event.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

            //SELECT OSO
            if(mouseX>300 & mouseX<300+rectangleW & mouseY>140 & mouseY<140+rectangleH){

                if(osoSelected==false){
                    osoSelected=true;
                    osoColor=enemySelected;
                }else{
                    osoSelected=false;
                    osoColor=enemyAvailable;
                }

            }
            //SELECT YETI
            else if(mouseX>600 & mouseX<600+rectangleW & mouseY>140 & mouseY<140+rectangleH){

                if(yetiSelected==false){
                    yetiSelected=true;
                    yetiColor=enemySelected;
                }else{
                    yetiSelected=false;
                    yetiColor=enemyAvailable;
                }
            }
            //SELECT FOCA
            else if(mouseX>300 & mouseX<300+rectangleW & mouseY>300 & mouseY<300+rectangleH){

                if(focaSelected==false){
                    focaSelected=true;
                    focaColor=enemySelected;
                }else{
                    focaSelected=false;
                    focaColor=enemyAvailable;
                }
            }
            //SELECT PAJARO
            else if(mouseX>600 & mouseX<600+rectangleW & mouseY>300 & mouseY<300+rectangleH){

                if(pajaroSelected==false){
                    pajaroSelected=true;
                    pajaroColor=enemySelected;
                }else{
                    pajaroSelected=false;
                    pajaroColor=enemyAvailable;
                }
            }
            //SELECT START
            else if(mouseX>417 & mouseX<417+al_get_bitmap_width(playText) & mouseY>450 & mouseY<450+al_get_bitmap_height(playText)){
                currentScene=3;
                break;

            }

        }

        //DRAWING TO DISPLAY
        if(redraw && al_is_event_queue_empty(eventQueue)){
            redraw=false;
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_bitmap_region(background,1035,0,1000,3450,0,-2850,0);

            //FIRST ROW OF ENEMIES
            al_draw_bitmap_region(Oso,0,0,al_get_bitmap_width(Oso)/3,al_get_bitmap_height(Oso)/3,325,140,0);
            al_draw_rectangle(300,140,300+rectangleW,140+rectangleH,osoColor,10);
            al_draw_bitmap_region(Yeti,0,0,al_get_bitmap_width(Yeti)/3,al_get_bitmap_height(Yeti)/3,622,156,0);
            al_draw_rectangle(600,140,600+rectangleW,140+rectangleH,yetiColor,10);

            //SECOND ROW OF ENEMIES
            al_draw_bitmap_region(Foca,0,0,al_get_bitmap_width(Foca)/3,al_get_bitmap_height(Foca)/3,322,315,0);
            al_draw_rectangle(300,300,300+rectangleW,300+rectangleH,focaColor,10);
            al_draw_bitmap_region(Pajaro,0,0,al_get_bitmap_width(Pajaro)/2,al_get_bitmap_height(Pajaro)/3,625,325,0);
            al_draw_rectangle(600,300,600+rectangleW,300+rectangleH,pajaroColor,10);

            al_draw_bitmap(titleText,500-al_get_bitmap_width(titleText)/2,40,0);
            al_draw_bitmap(playText,500-al_get_bitmap_width(playText)/2,450,0);
            al_flip_display();
        }

    }

    //FREE MEMORY
    al_destroy_timer(timer);
    al_destroy_event_queue(eventQueue);
    al_destroy_sample(titleMusic);
    al_destroy_bitmap(titleText);
    al_destroy_bitmap(playText);
    al_destroy_bitmap(background);
    al_destroy_bitmap(Oso);
    al_destroy_bitmap(Yeti);
    al_destroy_bitmap(Foca);
    al_destroy_bitmap(Pajaro);

    return 0;



}

//*************** GAME LEVEL INTRO ******************//

int levelIntro(ALLEGRO_DISPLAY *display) {

    ALLEGRO_EVENT_QUEUE *eventQueue = NULL;

    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_TIMER *frameTimer = NULL;

    ALLEGRO_SAMPLE *introMusic = NULL;

    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *dino = NULL;

    bool running = true;
    bool redraw = true;

    //CREATE TIMER
    timer = al_create_timer(1.0 / FPS);
    frameTimer = al_create_timer(1.0 / AnimationFPS);
    if (!timer || !frameTimer) {
        al_show_native_message_box(display, "Error", "Error", "Fail to create timer", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    background = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/Backgrounds.png");
    dino = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/Dino.png");
    if (!background || !dino) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image file",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);

        al_destroy_timer(timer);
        al_destroy_timer(frameTimer);
        al_destroy_display(display);
        return 0;
    }

    al_convert_mask_to_alpha(dino, al_map_rgb(0, 0, 0));

    //LOADING AUDIO FILES
    introMusic = al_load_sample("/home/manuel/Descargas/ICE_Climber/ICE_Client/_sounds/IntroMusic.wav");
    if (!introMusic) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load audio clip", NULL,
                                   ALLEGRO_MESSAGEBOX_ERROR);

        al_destroy_timer(timer);
        al_destroy_timer(frameTimer);
        al_destroy_bitmap(background);
        al_destroy_bitmap(dino);
        al_destroy_display(display);
        return 0;
    }

    //CREATE AND MANAGE EVENT QUEUE
    eventQueue = al_create_event_queue();
    if (!eventQueue) {
        al_show_native_message_box(display, "Error", "Error", "Fail to create Event Queue",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_timer(timer);
        al_destroy_timer(frameTimer);
        al_destroy_bitmap(background);
        al_destroy_bitmap(dino);
        al_destroy_sample(introMusic);
        al_destroy_display(display);

        return 0;
    }

    //REGISTER EVENTS TO EVENT QUEUE (LINK THEM)
    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_timer_event_source(frameTimer));


    al_clear_to_color(al_map_rgb(0, 0, 0));

    //FLIP IMAGE BUFFERED
    al_flip_display();

    //START TIMER
    al_start_timer(timer);
    al_start_timer(frameTimer);


    //gain=volume-pan=side of sound
    al_play_sample(introMusic, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

    while (running) {

        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);


        if (event.type == ALLEGRO_EVENT_TIMER) {

            if(event.timer.source==timer){

                if(dinoPosition[1]>=300) {
                    dinoPosition[1] -= 20;
                }
                else if (camaraPosition[1]==0){
                    al_rest(0.5);
                    dinoPosition[1]=506;
                    break;
                }
            }

            if (event.timer.source == frameTimer) {
                dinoAnimation[0]+=al_get_bitmap_width(dino)/3;
                if(dinoAnimation[0]>=al_get_bitmap_width(dino)){
                    dinoAnimation[0]=0;
                }
            }

            refreshCamara();
            redraw = true;


        }


        if (redraw && al_is_event_queue_empty(eventQueue)) {

            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));

            al_draw_bitmap_region(background, 0, 0, 1000, 3450, camaraPosition[0], camaraPosition[1], 0);
            al_draw_bitmap_region(dino, dinoAnimation[0], dinoAnimation[1], al_get_bitmap_width(dino) / 3,al_get_bitmap_height(dino) / 2, 500-(al_get_bitmap_width(dino)/3)/2, dinoPosition[1], 0);


            al_flip_display();


        }

    }

    //FREE MEMORY
    al_destroy_timer(timer);
    al_destroy_timer(frameTimer);
    al_destroy_bitmap(background);
    al_destroy_bitmap(dino);
    al_destroy_sample(introMusic);
    al_destroy_event_queue(eventQueue);

    return 0;

}

//*************** GAME LEVEL 1 SCENE ***************//

int level1(ALLEGRO_DISPLAY *display){

    ALLEGRO_EVENT_QUEUE *eventQueue=NULL;

    ALLEGRO_TIMER *timer=NULL;
    ALLEGRO_TIMER *frameTimer=NULL;

    ALLEGRO_SAMPLE *titleMusic=NULL;
    ALLEGRO_SAMPLE *jumpSound=NULL;
    ALLEGRO_SAMPLE *fieldSound=NULL;

    ALLEGRO_BITMAP *background=NULL;
    ALLEGRO_BITMAP *popoMove=NULL;
    ALLEGRO_BITMAP *nanaMove=NULL;
    ALLEGRO_BITMAP *dino=NULL;
    ALLEGRO_BITMAP *bouncer3=NULL;
    ALLEGRO_BITMAP *block=NULL;

    //KEY VALUES (Determines which keys are able to be recognize)
    enum KEYS {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_W, KEY_S, KEY_A, KEY_D};
    bool key[8] = { false, false, false, false, false, false, false, false };
    bool redraw=true;
    bool exit=false;
    bool jump=false;

    //CREATE TIMER
    timer = al_create_timer(1.0 / FPS);
    frameTimer = al_create_timer(1.0 / AnimationFPS);
    if(!timer || !frameTimer){
        al_show_native_message_box(display, "Error", "Error", "Fail to create timer",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    //LOAD IMAGE FILES
    popoMove=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/Popo.png");
    nanaMove=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/Nana.png");
    background = al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/Backgrounds.png");
    block=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/Blocks.png");
    dino=al_load_bitmap("/home/manuel/Descargas/ICE_Climber/ICE_Client/_imgs/Dino.png");
    if(!popoMove || !nanaMove || !background || !dino) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load image file",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);

        al_destroy_timer(timer);
        al_destroy_display(display);
        return 0;
    }

    //MASK BLACK COLOR FROM IMAGES
    al_convert_mask_to_alpha(popoMove,al_map_rgb(0,0,0));
    al_convert_mask_to_alpha(nanaMove,al_map_rgb(0,0,0));
    al_convert_mask_to_alpha(dino,al_map_rgb(0,0,0));

    //LOADING AUDIO FILES
    titleMusic = al_load_sample("/home/manuel/Descargas/ICE_Climber/ICE_Client/_sounds/LevelMusic.wav" );
    jumpSound = al_load_sample("/home/manuel/Descargas/ICE_Climber/ICE_Client/_sounds/Jump.wav" );
    fieldSound = al_load_sample("/home/manuel/Descargas/ICE_Climber/ICE_Client/_sounds/DestroyField.wav" );
    if (!titleMusic || !jumpSound || !fieldSound) {
        al_show_native_message_box(display, "Error", "Error", "Failed to load audio clip",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_bitmap(background);
        al_destroy_bitmap(dino);
        al_destroy_bitmap(nanaMove);
        al_destroy_timer(frameTimer);
        al_destroy_bitmap(popoMove);

        return 0;
    }


    //CREATE BITMAP
    bouncer3=al_create_bitmap(1000,20);
    if(!bouncer3){
        al_show_native_message_box(display, "Error", "Error", "Fail to create bitmap",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_bitmap(background);
        al_destroy_timer(timer);
        al_destroy_sample(titleMusic);
        al_destroy_sample(jumpSound);
        al_destroy_sample(fieldSound);
        al_destroy_timer(frameTimer);
        al_destroy_display(display);
        al_destroy_bitmap(dino);
        al_destroy_bitmap(nanaMove);
        al_destroy_bitmap(popoMove);
        return 0;
    }

    //DRAWING BITMAPS

    al_set_target_bitmap(bouncer3);
    al_clear_to_color(al_map_rgb(0, 255, 0));
    al_set_target_bitmap(al_get_backbuffer(display));


    //CREATE AND MANAGE EVENT QUEUE
    eventQueue=al_create_event_queue();
    if(!eventQueue){
        al_show_native_message_box(display, "Error", "Error", "Fail to create Event Queue",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        al_destroy_display(display);
        al_destroy_timer(timer);
        al_destroy_timer(frameTimer);
        al_destroy_sample(titleMusic);
        al_destroy_bitmap(bouncer3);
        al_destroy_bitmap(nanaMove);
        al_destroy_bitmap(popoMove);
        al_destroy_sample(jumpSound);
        al_destroy_sample(fieldSound);
        al_destroy_bitmap(background);
        al_destroy_bitmap(dino);
        return 0;
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


    //gain=volume-pan=side of sound
    al_play_sample(titleMusic, 0.5, 0.0,1.0,ALLEGRO_PLAYMODE_LOOP,NULL);




    //GAME LOOP
    while(!exit){
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue,&event);



        if(event.type==ALLEGRO_EVENT_TIMER) {

            jump=(popoPosition[1]<=425 && popoPosition[1]>0.4);

            //SET SCREEN LIMITS TO BOUNCER
            //if (key[KEY_UP] && jump) {
              //  popoPosition[1]-=20;
               // jump=false;
                //key[KEY_UP] = false;

            if (key[KEY_UP] && popoPosition[1] >= 4.0 ) {
                popoPosition[1] -= movementSpeed[1];
                //key[KEY_UP] = false;
            }
            if(!key[KEY_UP] && popoPosition[1] < 506-32){
                popoPosition[1]+=acceleration[1];
            }
            if (key[KEY_DOWN] &&popoPosition[1] <= screenH - 81 - 4.0-94) {
                //player1_y += 4.0;
                //jump=true;

            }
            if (key[KEY_LEFT]) {
                //jump=true;
                if(event.timer.source ==frameTimer) {
                    popoAnimation[0] += al_get_bitmap_width(popoMove) / 5;
                    popoAnimation[1] = 0;
                }

                if (popoAnimation[0]>(al_get_bitmap_width(popoMove)/5)*3){
                    popoAnimation[0]=0;
                }

                if (popoPosition[0]<-32){
                    popoPosition[0]=1000;
                }else {
                    popoPosition[0]-= movementSpeed[0];
                }
            }
            if (key[KEY_RIGHT]) {
                //jump=true;
                if(event.timer.source ==frameTimer) {
                    popoAnimation[0] += al_get_bitmap_width(popoMove) / 5;
                    popoAnimation[1] = al_get_bitmap_height(popoMove) / 2;
                }

                if (popoAnimation[0]>(al_get_bitmap_width(popoMove)/5)*3){
                    popoAnimation[0]=0;
                }
                if (popoPosition[0]>1000){
                    popoPosition[0]=0;
                }else {
                    popoPosition[0] += movementSpeed[0];
                }
            }


            if (key[KEY_W] && nanaPosition[1] >= 4.0 && nanaPosition[1] < 500.0) {
                nanaPosition[1]-= movementSpeed[1];
            }
            if(!key[KEY_W] && nanaPosition[1]<506-32){
                nanaPosition[1]+=acceleration[1];
            }
            if (key[KEY_S] && nanaPosition[1] <= screenH - 81 - 4.0-94) {
                //player2_y += 4.0;
            }
            if (key[KEY_A]) {

                nanaAnimation[0]+=al_get_bitmap_width(nanaMove)/5;
                nanaAnimation[1]=0;

                if (nanaAnimation[0]>(al_get_bitmap_width(nanaMove)/5)*3){
                    nanaAnimation[0]=0;
                }


                if (nanaPosition[0]<-32){
                    nanaPosition[0]=1000;
                }else {
                    nanaPosition[0]-= movementSpeed[0];
                }
            }
            if (key[KEY_D]) {

                nanaAnimation[0]+=al_get_bitmap_width(nanaMove)/5;
                nanaAnimation[1]=al_get_bitmap_height(nanaMove)/2;

                if (nanaAnimation[0]>(al_get_bitmap_width(nanaMove)/5)*3){
                    nanaAnimation[0]=0;
                }

                if (nanaPosition[0]>1000){
                    nanaPosition[0]=0;
                }else {
                    nanaPosition[0] += movementSpeed[0];
                }
            }

            //initClient(jsonWriter(1,player1_x, player1_y, 0, 3));
            if(event.timer.source ==frameTimer) {
                animateEnemy(dino,dinoPosition,dinoAnimation, &dir);
            }
            refreshCamara();
            redraw = true;
        }
        else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            break;
        }
        else if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch(event.keyboard.keycode) {
                case ALLEGRO_KEY_UP:
                    key[KEY_UP] = true;
                    al_play_sample(jumpSound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    break;

                case ALLEGRO_KEY_DOWN:
                    key[KEY_DOWN] = true;
                    al_play_sample(fieldSound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    break;

                case ALLEGRO_KEY_LEFT:
                    key[KEY_LEFT] = true;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    key[KEY_RIGHT] = true;
                    break;

                case ALLEGRO_KEY_W:
                    key[KEY_W] = true;
                    al_play_sample(jumpSound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
                    break;

                case ALLEGRO_KEY_S:
                    key[KEY_S] = true;
                    al_play_sample(fieldSound, 1.0, 0.0,1.0,ALLEGRO_PLAYMODE_ONCE,NULL);
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //***********************BONUS WALL***********************************
        if(Collision(popoPosition[0],popoPosition[1],80,-1175+camaraPosition[1]+2850,al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,10,175)) {
            if(key[KEY_RIGHT])
                popoPosition[0]-=10;
            else if(key[KEY_LEFT])
                popoPosition[0]+=10;
        }

        //COPIAR Y CAMBIAR x


        //***********************BONUS PLATFORM***********************************
        if(Collision(popoPosition[0],popoPosition[1],290,((-2850+1850)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,175,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if(popoPosition[1]<=((-2850+1850)+camaraPosition[1]+2850))
                popoPosition[1]-=10;
        }
        if(Collision(popoPosition[0],popoPosition[1],550,((-2850+1850)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,155,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+1850)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }
        if(Collision(popoPosition[0],popoPosition[1],800,((-2850+1850)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,120,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+1850)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }

        if(Collision(popoPosition[0],popoPosition[1],96,((-2850+1850)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,110,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+1850)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }

        //2 bonus plataforms
        if(Collision(popoPosition[0],popoPosition[1],200,((-2850+1725)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,105,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+1725)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }
        if(Collision(popoPosition[0],popoPosition[1],420,((-2850+1725)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,160,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+1725)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }
        if(Collision(popoPosition[0],popoPosition[1],710,((-2850+1725)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,100,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+1725)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }

///////////////////////

        if(Collision(popoPosition[0],popoPosition[1],170,((-2850+1347)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,200,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+1347)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }



        if(Collision(popoPosition[0],popoPosition[1],580,((-2850+1380)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,110,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+1380)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }



        if(Collision(popoPosition[0],popoPosition[1],390,((-2850+1192)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,170,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+1192)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }



        if(Collision(popoPosition[0],popoPosition[1],675,((-2850+1224)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,80,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+1224)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }



        if(Collision(popoPosition[0],popoPosition[1],270,((-2850+847)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,80,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+847)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }



        if(Collision(popoPosition[0],popoPosition[1],520,((-2850+878)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,110,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+878)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }



        if(Collision(popoPosition[0],popoPosition[1],610,((-2850+753)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,85,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+753)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }



        if(Collision(popoPosition[0],popoPosition[1],390,((-2850+690)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,80,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+690)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }



        if(Collision(popoPosition[0],popoPosition[1],455,((-2850+595)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,110,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+595)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }




        if(Collision(popoPosition[0],popoPosition[1],190,((-2850+439)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,205,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+439)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }



        if(Collision(popoPosition[0],popoPosition[1],640,((-2850+439)+camaraPosition[1]+2850),al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,180,33)) {
            if(key[KEY_UP])
                popoPosition[1]+=10;
            else if((popoPosition[1]<=((-2850+439)+camaraPosition[1]+2850)))
                popoPosition[1]-=10;
        }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if(redraw && al_is_event_queue_empty(eventQueue)){
            redraw=false;
            al_clear_to_color(al_map_rgb(0,0,0));
            //al_draw_bitmap(bouncer3, 0, 506, 0);
            al_draw_bitmap_region(background,0,0,1000,3450,camaraPosition[0],camaraPosition[1],0);
            al_draw_bitmap_region(popoMove, popoAnimation[0], popoAnimation[1], al_get_bitmap_width(popoMove)/5,al_get_bitmap_height(popoMove)/2,popoPosition[0],popoPosition[1]-60,0);
            al_draw_bitmap_region(nanaMove, nanaAnimation[0], nanaAnimation[1], al_get_bitmap_width(nanaMove)/5,al_get_bitmap_height(nanaMove)/2,nanaPosition[0],nanaPosition[1]-60,0);
            al_draw_bitmap_region(dino, dinoAnimation[0], dinoAnimation[1], al_get_bitmap_width(dino)/3,al_get_bitmap_height(dino)/2,dinoPosition[0],dinoPosition[1],0);


            for(int b=125;b<=800;b+=34){
                createBlocks(display,b,320+camaraPosition[1]+2850,1);
            }

            for(int b=157;b<=800;b+=34){
                createBlocks(display,b,132+camaraPosition[1]+2850,2);
            }

            for(int b=120;b<=800;b+=34){
                createBlocks(display,b,50+camaraPosition[1]+2850,3);
            }

            //al_draw_bitmap(bouncer3, 0, 506, 0);
            al_flip_display();
        }

    }

    //FREE MEMORY AFTER CLOSE PROGRAM
    al_destroy_bitmap(background);
    al_destroy_sample(titleMusic);
    al_destroy_sample(jumpSound);
    al_destroy_sample(fieldSound);
    al_destroy_bitmap(popoMove);
    al_destroy_bitmap(nanaMove);
    al_destroy_bitmap(bouncer3);
    al_destroy_timer(frameTimer);
    al_destroy_bitmap(dino);
    al_destroy_bitmap(block);
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(eventQueue);

    return 0;
}

//************************************************************************************************************************************//
//****************************************************** GAME SCENE MANAGER **********************************************************//


//******************* START GAME *******************//

int startGame(int players) {

    //CREATING INTERFACE FIELDS
    ALLEGRO_DISPLAY *display=NULL;
    //
    bool running=true;


    //INIT ALLEGRO LIBRARY
    if(!al_init()){
        al_show_native_message_box(display, "Error", "Error", "Fail to init Allegro",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    //CREATE IMAGE LOADER
    if(!al_init_image_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize al_init_image_addon",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    //HANDLE KEYBOARD EVENTS
    if(!al_install_keyboard()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize the keyboard",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    //HANDLE MOUSE EVENTS
    if(!al_install_mouse()) {
        fprintf(stderr, "failed to initialize the mouse!\n");
        return -1;
    }

    //CREATE PRIMITIVE FORMS DRAWER
    if(!al_init_primitives_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize primitive forms drawer!",NULL, ALLEGRO_MESSAGEBOX_ERROR);
    }

    //CREATE SOUND SYSTEM
    if(!al_install_audio()){
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize audio",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    //LOAD AUDIO FORMATS
    if(!al_init_acodec_addon()) {
        al_show_native_message_box(display, "Error", "Error", "Failed to initialize audio codecs",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }

    //RESERVE A NUMBER OF AUDIO SAMPLES, AND CREATES A DEFAULT MIXER
    if (!al_reserve_samples(5)){
        al_show_native_message_box(display, "Error", "Error", "Failed to reserve samples",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }


    //CREATE DISPLAY WINDOW
    display=al_create_display(screenW,screenH);
    if(!display){
        al_show_native_message_box(display, "Error", "Error", "Fail to init Window",
                                   NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return 0;
    }
    //SET WINDOW TITLE
    al_set_window_title(display,"ICE-CLimber");

    winnerScene(display,5,5,5,5,5,5,5,5);
    while (running) {

        if(currentScene==0) {
            titleScene(display);
        }
        else if(currentScene==1){
            gameModeScene(display);
        }
        else if(currentScene==2) {
            enemySelectionScene(display);
        }
        else if(currentScene==3){
            levelIntro(display);
            restartCamara();
            level1(display);
        }
        else{
            break;
        }

    }


    al_destroy_display(display);


}





