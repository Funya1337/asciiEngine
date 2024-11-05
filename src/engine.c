#include "engine.h"

void mat4_mult(vec3 *i, vec3 *o, mat4 *m) {
    o->x = i->x * m->m[0][0] + i->y * m->m[1][0] + i->z * m->m[2][0] + m->m[3][0];
    o->y = i->x * m->m[0][1] + i->y * m->m[1][1] + i->z * m->m[2][1] + m->m[3][1];
    o->z = i->x * m->m[0][2] + i->y * m->m[1][2] + i->z * m->m[2][2] + m->m[3][2];
    float w = i->x * m->m[0][3] + i->y * m->m[1][3] + i->z * m->m[2][3] + m->m[3][3];

    if (w != 0.0f) o->x /= w;
    o->y /= w;
    o->z /= w;
}

void engine_normalize2d(vec2 *v) { v->x *= ASPECT * PIXEL_ASPECT; }
void engine_normalize3d(vec3 *v) { v->x *= ASPECT * PIXEL_ASPECT; }

void engine_rotate(vec3 *point, float x, float y, float z) {
    float rad = 0;
    rad = x;
    point->y = cos(rad) * point->y - sin(rad) * point->z;
    point->z = sin(rad) * point->y + cos(rad) * point->z;

    rad = y;
    point->x = cos(rad) * point->x + sin(rad) * point->z;
    point->z = -sin(rad) * point->x + cos(rad) * point->z;

    rad = z;
    point->x = cos(rad) * point->x - sin(rad) * point->y;
    point->y = sin(rad) * point->x + cos(rad) * point->y;
}

void engine_draw_line(vec2 *v1, vec2 *v2, char ch) {
    float dx = v2->x - v1->x;
    float dy = v2->y - v1->y;

    float length = sqrt(dx * dx + dy * dy);
    float angle = atan2(dy, dx);

    for (float i = 0; i < length; ++i) mvaddch(v1->y + sin(angle) * i, v1->x + cos(angle) * i, ch);
}

void handleUserInput() {
    switch (getch()) {
        case 'q':
            stopRunning();
            break;
    }
}

int isRunning() { return running; }

void stopRunning() { running = 0; }