#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
#include <stdlib.h>
#include "pair.h"

#define typename(x) _Generic((x), char: "%c", int: "%d", float: "%f", double: "%lf", default: "other")

#define Vector(DATATYPE) \
    struct {             \
        DATATYPE *data;  \
        int length;      \
        int capacity;    \
    }

#define vector_init(vector)                                  \
    do {                                                    \
        (vector)->data = malloc(sizeof(*((vector)->data))); \
        (vector)->length = 1;                               \
        (vector)->capacity = 0;                             \
    } while (0)

#define vector_clear(vector)    \
    do {                       \
        free((vector)->data);  \
        (vector)->data = NULL; \
    } while (0)

#define vector_push_back(vector, value)                                               \
    do {                                                                            \
        if ((vector)->length == (vector)->capacity) {                               \
            int newLength = (vector)->length * 2;                                   \
            void *p = realloc((vector)->data, sizeof(*(vector)->data) * newLength); \
            if (p) {                                                                \
                (vector)->data = p;                                                 \
                (vector)->length = newLength;                                       \
            } else {                                                                \
                printf("[vectorPushBack]: failed to allocate memory");              \
            }                                                                       \
        }                                                                           \
        (vector)->data[(vector)->capacity++] = value;                               \
    } while (0)

// WORK WITH DEFAULT C TYPES: INT, FLOAT, DOUBLE, CHAR
#define vector_print(vector)                                     \
    int length = (vector)->length;                              \
    for (int i = 0; i < length; ++i) {                          \
        printf(typename((vector)->data[0]), (vector)->data[i]); \
        if (i == length - 1)                                    \
            printf("\n");                                       \
        else                                                    \
            printf(" ");                                        \
    }

int compare(const void* left, const void* right);

#endif
