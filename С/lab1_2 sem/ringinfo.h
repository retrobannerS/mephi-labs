#ifndef LAB1_RINGINFO_H
#define LAB1_RINGINFO_H
#include <stddef.h>

typedef struct RingInfo{
    size_t size;
    void (*sum)(void* A, void* B, void* res);
    void (*mult)(void* A, void* B, void* res);
    void* zero;
    void* one;
    void (*minus)(void* A, void* res);
    void (*inverse)(void* A, void* res);
    void (*print)(void* A);
    void (*input)(void* A);
} RingInfo;

void NewRing(RingInfo* new,
                 size_t size,
                 void (*sum)(void* A, void* B, void* res),
                 void (*mult)(void* A, void* B, void* res),
                 void* zero,
                 void* one,
                 void (*minus)(void* A, void* res),
                 void (*inverse)(void* A, void* res),
                 void (*print)(void* A),
                 void (*input)(void* A));

#endif //LAB1_RINGINFO_H
