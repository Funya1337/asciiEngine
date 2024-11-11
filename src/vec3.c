#include "vec3.h"

vec3 vec3_sum(vec3 a, vec3 b) {
    vec3 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

void vec3_scale(vec3 *a, int scale) {
    a->x *= scale;
    a->y *= scale;
    a->z *= scale;
}

void vec3_add_const(vec3 *a, int value) {
    a->x += value;
    a->y += value;
    a->z += value;
}

void vec3_add_each(vec3 *a, int valueX, int valueY, int valueZ) {
    a->x += valueX;
    a->y += valueY;
    a->z += valueZ;
}

vec3 vec3_calc_center(vec3 *points, int num_points) {
    vec3 center = {0, 0, 0};
    for (int i = 0; i < num_points; i++) {
        center.x += points[i].x;
        center.y += points[i].y;
        center.z += points[i].z;
    }
    center.x /= num_points;
    center.y /= num_points;
    center.z /= num_points;
    return center;
}

void vec3_print(vec3 v) { printf("vec3(%f, %f, %f)\n", v.x, v.y, v.z); }