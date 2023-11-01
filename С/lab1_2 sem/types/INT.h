#ifndef LAB1_INT_H
#define LAB1_INT_H
#define INTsize sizeof(int)

extern int int0, int1;
void Intsum(void* A, void* B, void* result);
void Intmult(void* A, void* B, void* result);
void Intminus(void* A, void* result);
void Intinverse(void* A, void* result);
void Intprint(void* A);
void Intinput(void* A);


#endif //LAB1_INT_H
