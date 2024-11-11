#ifndef VEC3_H
#define VEC3_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
} vec3;

vec3 vec3_sum(vec3 a, vec3 b);
void vec3_scale(vec3 *a, int scale);
void vec3_add(vec3 *a, int value);
void vec3_add_each(vec3 *a, int valueX, int valueY, int valueZ);
vec3 vec3_calc_center(vec3 *points, int num_points);
void vec3_print(vec3 v);

#endif
