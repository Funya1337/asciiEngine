#ifndef ENGINE_H
#define ENGINE_H
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "player.h"
#include "map.h"
#include "vec3.h"
#include "../libs/vector.h"

static int running = 1;

// typedef struct {
//     vec3 p[3];
// } Triangle;

// typedef struct {
//     Vector *tris;
// } mesh;

int isRunning();
void stopRunning();

#endif
