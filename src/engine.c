#include "engine.h"

void drawPixel(int x, int y, char ch) {
    move(y, x);
    printw("%c", ch);
}

mesh createMesh() {
    mesh m;
    m.tris = initVector(10);
    return m;
}

int isRunning() { return running; }

void stopRunning() { running = 0; }