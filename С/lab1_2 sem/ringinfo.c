#include "ringinfo.h"

void NewRing(struct RingInfo* new,
                 size_t size,
                 void (*sum)(void* A, void* B, void* res),
                 void (*mult)(void* A, void* B, void* res),
                 void* zero,
                 void* one,
                 void (*minus)(void* A, void* res),
                 void (*inverse)(void* A, void* res),
                 void (*print)(void* A),
                 void (*input)(void* A))
{
    new->size = size;
    new->sum = sum;
    new->mult = mult;
    new->zero = zero;
    new->one = one;
    new->minus = minus;
    new->inverse = inverse;
    new->print = print;
    new->input = input;
}