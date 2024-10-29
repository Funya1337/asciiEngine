#ifndef ENGINE_H
#define ENGINE_H
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#define N_MAP_WIDTH 16
#define N_MAP_HEIGHT 16
#define N_SCREEN_WIDTH 120
#define N_SCREEN_HEIGHT 40

static int running = 1;
char map[N_MAP_WIDTH][N_MAP_HEIGHT];

void drawPixel(int x, int y, char ch);
int isRunning();
void stopRunning();

#endif
