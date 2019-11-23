//
// Created by gunther on 16/11/19.
//

#ifndef UNTITLED_ICE_GAME_H
#define UNTITLED_ICE_GAME_H


#include <allegro5/haptic.h>

int startGame();
int createBlocks(ALLEGRO_DISPLAY *display,int blockX,int blockY,int level);
int winnerScene(ALLEGRO_DISPLAY *display,int popoBears,int nanaBears,int popoSeals,int nanaSeals,int popoPenguins,int nanaPenguins,int popoYetis,int nanaYetis);

#endif //UNTITLED_ICE_GAME_H
