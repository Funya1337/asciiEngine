#include "vector.h"

int compare(const void* left, const void* right) {
    const Pair* pair1 = (const Pair*)left;
    const Pair* pair2 = (const Pair*)right;
    return pair1->first - pair2->first;
}