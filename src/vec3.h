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

vec3 vec3_add(vec3 a, vec3 b);
void vec3_print(vec3 v);

#endif
