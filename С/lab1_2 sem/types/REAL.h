#ifndef LAB1_REAL_H
#define LAB1_REAL_H
#define REALsize sizeof(long double)

extern long double real0, real1;
void Realsum(void* A, void* B, void* result);
void Realmult(void* A, void* B, void* result);
void Realminus(void* A, void* result);
void Realinverse(void* A, void* result);
void Realprint(void* A);
void Realinput(void* A);

#endif //LAB1_REAL_H
