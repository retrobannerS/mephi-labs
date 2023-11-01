#ifndef LAB1_sqmatr_H
#define LAB1_sqmatr_H
#include "ringinfo.h"

typedef struct sqmatr{
    RingInfo* ringinfo;
    unsigned int sizeofmatr;
    void* matrixpointer;
} sqmatr;

//Создание
sqmatr* Newsqmatrix(RingInfo* ring, unsigned int sizeofmatr);

//Заполнение
void Zerosqmatrix(sqmatr* A);
void E_matrix(sqmatr* A);
void Inputsqmatrix(sqmatr* A);
void Putvalue(sqmatr* A, unsigned int row_adress, unsigned int col_adress, sqmatr* value);

//Копирование
void Sqmatrixcopy(const sqmatr* A, sqmatr* result);

//Удаление
void Sqmatrixdelete(sqmatr* A);

//Декомпозиция
void* Getvalue(const sqmatr* A, unsigned int row_adress, unsigned int col_adress);

//Печать
void Sqmatrixprint(const sqmatr* A);

//Операции
void Sqmatrixsum(const sqmatr* A, const sqmatr* B, sqmatr* result);
void Sqmatrixmult(const sqmatr* A, const sqmatr* B, sqmatr* result);
void Sqmatrixscalarmult(const sqmatr* scalar, const sqmatr* A, sqmatr* result);
void Sqmatrixalgcompl(const sqmatr* A, unsigned int row_adress, unsigned int col_adress, sqmatr* result);
void Sqmatrixdet(const sqmatr* A, sqmatr* result);
void Sqmatrixtranspose(const sqmatr* A, sqmatr* result);
void Sqmatrixinverse(const sqmatr* A, sqmatr* result);
void Sqmatrixlincombofrows(sqmatr* A, unsigned int row_adress, const void* coefs);
void Sqmatrixlincombofcols(sqmatr* A, unsigned int col_adress, const void* coefs);

#endif //LAB1_sqmatr_H
