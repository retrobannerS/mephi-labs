#ifndef LAB1_COMPLEX_H
#define LAB1_COMPLEX_H
#define COMPLEXsize sizeof(complex)

typedef struct complex{
    long double Re;
    long double Im;
} complex;

extern complex complex0, complex1;
void Complexsum(void* A, void* B, void* result);
void Complexmult(void* A, void* B, void* result);
void Complexminus(void* A, void* result);
void Complexinverse(void* A, void* result);
void Complexprint(void* A);
void Complexinput(void* A);

#endif //LAB1_COMPLEX_H
