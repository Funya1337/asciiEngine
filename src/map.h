#ifndef MAP_H
#define MAP_H
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "../libs/vector.h"

#define N_MAP_WIDTH 16
#define N_MAP_HEIGHT 16
#define N_SCREEN_WIDTH 120
#define N_SCREEN_HEIGHT 40

char map[N_MAP_WIDTH][N_MAP_HEIGHT];

#endif
