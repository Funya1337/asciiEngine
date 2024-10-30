#include "vec3.h"

vec3 vec3_add(vec3 a, vec3 b) {
    vec3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

void vec3_print(vec3 v) { printf("vec3(%f, %f, %f)\n", v.x, v.y, v.z); }