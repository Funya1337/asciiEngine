#ifndef ENGINE_H
#define ENGINE_H
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#define MS_PER_FRAME 16

static int running = 1;

void drawPixel(int x, int y, char ch);
int isRunning();
void setIsRunning();

#endif
