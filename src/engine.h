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
static const float ASPECT = (float)N_SCREEN_WIDTH / N_SCREEN_HEIGHT;
static const float PIXEL_ASPECT = 11.0f / 24.0f;

typedef struct {
    vec3 p[3];
} Triangle;

typedef struct {
    float x;
    float y;
} vec2;

typedef struct {
    Vector(Triangle) tris;
} mesh;

typedef struct {
    int a;
    int b;
} connection;

typedef struct {
    float m[4][4];
} mat4;

void mat4_mult(vec3 *i, vec3 *o, mat4 *m);
void handleUserInput();
void engine_draw_line(vec2 *v1, vec2 *v2, char ch);
void engine_rotate(vec3 *point, float x, float y, float z);
void engine_normalize2d(vec2 *v);
void engine_normalize3d(vec3 *v);
int isRunning();
void stopRunning();

#endif
