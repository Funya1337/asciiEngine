#ifndef ENGINE_H
#define ENGINE_H
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>

#include "player.h"
#include "map.h"
#include "vec3.h"
#include "../libs/vector.h"
#include "global.h"

struct winsize w;

typedef struct {
    float x;
    float y;
} vec2;

typedef struct {
    int a;
    int b;
} connection;

void handleUserInput();
void update_screen_size();
void handle_winch(int sig);
void engine_align_coords_center(void *points);
void engine_input_points(void *points, void *connections);
void engine_scale_shape(void *points, int size, int scale);
void engine_draw_line(vec2 *v1, vec2 *v2, char ch);
void engine_rotate(vec3 *point, float x, float y, float z);
int isRunning();
void stopRunning();

#endif
