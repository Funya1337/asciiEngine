#include "engine.h"

void drawPixel(int x, int y, char ch) {
    move(y, x);
    printw("%c", ch);
}

int isRunning() { return running; }

void stopRunning() { running = 0; }