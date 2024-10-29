#include "vector.h"

Vector *initVector(size_t initialSize)
{
    Vector *vect = malloc(sizeof(Vector));
    if (vect) {
        vect->data = malloc(initialSize * sizeof(Pair));
        vect->used = 0;
        vect->size = initialSize;
        return vect;
    }
    return NULL;
}

void push_back(Vector *vect, Pair *pair) {
    if (vect->size == vect->used)
    {
        size_t newSize = vect->size * 2;
        Pair *p = realloc(vect->data, sizeof(Pair) * newSize);
        if (p) {
            vect->data = p;
            vect->size = newSize;
        }
    }
    vect->data[vect->used++] = *pair;
}

void empty_vector(Vector *vect)
{
    if (vect) {
        free(vect->data);
        free(vect);
    }
}

int compare(const void* left, const void* right) {
    const Pair* pair1 = (const Pair*)left;
    const Pair* pair2 = (const Pair*)right;
    return pair1->first - pair2->first;
}

void printVector(Vector **vect)
{
    size_t used = (*vect)->used;
    printf("------------------\n");
    for (size_t i = 0; i < used; ++i)
    {
        printf("%f %f\n", (*vect)->data[i].first, (*vect)->data[i].second);
    }
    printf("------------------\n");
}