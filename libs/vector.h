#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
#include <stdlib.h>
#include "pair.h"

typedef struct {
    size_t used;
    size_t size;
    Pair *data;
} Vector;

Vector *initVector(size_t initialSize);
void push_back(Vector *vect, Pair *pair);
void printVector(Vector **vect);
void empty_vector(Vector *vect);
int compare(const void* left, const void* right);

#endif
