#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include "engine.h"

typedef struct {
    float fPlayerX;
    float fPlayerY;
    float fPlayerA;
    float fFOV;
    float fDepth;
} Player;

Player playerInit();
void playerAngleRotationLeft(float offset, Player *player);
void playerAngleRotationRight(float offset, Player *player);
void playerMoveForward(float offset, Player *player);
void playerMoveBackward(float offset, Player *player);
void handlePlayerInput(Player *player);

#endif
