#include "Square_Matrix.h"
#include "Errors.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

sqmatr* Newsqmatrix(RingInfo* ring, unsigned int sizeofmatr)
{
    sqmatr* new = (sqmatr*)malloc(sizeof(sqmatr));
    if(new && ring)
    {
        new->ringinfo = ring;
        new->sizeofmatr = sizeofmatr;
        void* arr = malloc(ring->size * sizeofmatr * sizeofmatr);
        if(arr)
        {
            new->matrixpointer = arr;
            return new;
        }
    }
    //double else
    err = failed_to_allocate_memory;
    free(new);
    return NULL;
}

void Zerosqmatrix(sqmatr* A)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0)
    {
        err = bad_matrix_in_function;
        return;
    }
    unsigned int sizeofmatr = A->sizeofmatr;
    RingInfo* ring = A->ringinfo;
    for (int i = 0; i < sizeofmatr; ++i)
        for (int j = 0; j < sizeofmatr; ++j)
            memcpy(Getvalue(A, i, j), ring->zero, ring->size);
}

void E_matrix(sqmatr* A)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0)
    {
        err = bad_matrix_in_function;
        return;
    }
    unsigned int sizeofmatr = A->sizeofmatr;
    RingInfo* ring = A->ringinfo;
    for (int i = 0; i < sizeofmatr; ++i)
        for (int j = 0; j < sizeofmatr; ++j)
            if(i == j)
                memcpy(Getvalue(A, i, j), ring->one, ring->size);
            else
                memcpy(Getvalue(A, i, j), ring->zero, ring->size);
}

void Inputsqmatrix(sqmatr* A)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0)
    {
        err = bad_matrix_in_function;
        return;
    }
    RingInfo* ring = A->ringinfo;
    unsigned int sizeofmatr = A->sizeofmatr;
    void (*input)(void*);
    input = ring->input;
    for (int i = 0; i < sizeofmatr; ++i)
        for (int j = 0; j < sizeofmatr; ++j)
        {
            printf("A[%d][%d]:", i, j);
            input(Getvalue(A, i, j));
        }
    printf("\n");
}

void Putvalue(sqmatr* A, unsigned int row_adress, unsigned int col_adress, sqmatr* value)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0)
    {
        err = bad_matrix_in_function;
        return;
    }
    unsigned int sizeofmatr = A->sizeofmatr;
    unsigned int onesize = value->sizeofmatr;
    RingInfo* ring1 = A->ringinfo;
    RingInfo* ring2 = value->ringinfo;
    if(onesize == 1 && ring1==ring2 && row_adress <= sizeofmatr && col_adress <= sizeofmatr)
        memcpy(Getvalue(A, row_adress, col_adress), Getvalue(value, 0, 0), ring1->size);
    else
    {
        if(onesize != 1)
            err = bad_size_of_matrix_in_function;
        else if(ring1 != ring2)
            err = rings_are_not_equal_in_function;
        else if(row_adress > sizeofmatr)
            err = row_adress_is_larger_than_size_of_matrix;
        else if(col_adress > sizeofmatr)
            err = col_adress_is_larger_than_size_of_matrix;
    }
}

void Sqmatrixcopy(const sqmatr* A, sqmatr* result)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0)
    {
        err = bad_matrix_in_function;
        return;
    }
    RingInfo* ring1 = A->ringinfo;
    RingInfo* ring2 = result->ringinfo;
    unsigned int sizeofmatr1 = A->sizeofmatr;
    unsigned int sizeofmatr2 = result->sizeofmatr;
    if(sizeofmatr1 == sizeofmatr2 && ring1 == ring2)
    {
        for (int i = 0; i < sizeofmatr1; ++i)
            for (int j = 0; j < sizeofmatr2; ++j)
                memcpy(Getvalue(result, i, j), Getvalue(A, i, j), ring1->size);
    }
    else
    {
        if(sizeofmatr1 != sizeofmatr2)
            err = sizes_of_matrix_are_not_equal_in_function;
        else if(ring1 != ring2)
            err = rings_are_not_equal_in_function;

    }
}

void Sqmatrixdelete(sqmatr* A)
{
    free(A->matrixpointer);
    free(A);
}

void* Getvalue(const sqmatr* A, unsigned int row_adress, unsigned int col_adress)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0)
    {
        err = bad_matrix_in_function;
        return NULL;
    }
    unsigned int sizeofmatr = A->sizeofmatr;
    RingInfo* ring = A->ringinfo;
    return(A->matrixpointer + row_adress * sizeofmatr * ring->size + col_adress * ring->size);
}

void Sqmatrixprint(const sqmatr* A)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0)
    {
        err = bad_matrix_in_function;
        return;
    }
    unsigned int sizeofmatr = A->sizeofmatr;
    void (*print)(void* A);
    print = A->ringinfo->print;
    for (int i = 0; i < sizeofmatr; ++i)
    {
        printf("|  ");
        for (int j = 0; j < sizeofmatr; ++j)
        {
            print(Getvalue(A, i, j));
            printf("  |  ");
        }
        printf("\n");
    }
    printf("\n");
}

void Sqmatrixsum(const sqmatr* A, const sqmatr* B, sqmatr* result)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0 || !B || !B->ringinfo || B->sizeofmatr == 0 ||
       !result || !result->ringinfo || !result->sizeofmatr)
    {
        err = bad_matrix_in_function;
        return;
    }
    RingInfo* ring1 = A->ringinfo;
    RingInfo* ring2 = B->ringinfo;
    RingInfo* ring3 = result->ringinfo;
    unsigned int sizeofmatr1 = A->sizeofmatr;
    unsigned int sizeofmatr2 = B->sizeofmatr;
    unsigned int sizeofmatr3 = result->sizeofmatr;
    if (ring1 == ring2 && ring3 == ring1 && sizeofmatr1 == sizeofmatr2 && sizeofmatr3 == sizeofmatr1)
    {
        void (*Sum)(void*, void*, void*);
        Sum = ring1->sum;
        for (int i = 0; i < sizeofmatr1; ++i)
            for (int j = 0; j < sizeofmatr2; ++j)
                Sum(Getvalue(A, i, j), Getvalue(B, i, j), Getvalue(result, i, j));
    }
    else
    {
        if(ring1 != ring2 || ring3 != ring1)
            err = rings_are_not_equal_in_function;
        else if(sizeofmatr1 != sizeofmatr2 || sizeofmatr3 != sizeofmatr1)
            err = sizes_of_matrix_are_not_equal_in_function;
    }
}

void Sqmatrixmult(const sqmatr* A, const sqmatr* B, sqmatr* result)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0 || !B || !B->ringinfo || B->sizeofmatr == 0 ||
       !result || !result->ringinfo || !result->sizeofmatr)
    {
        err = bad_matrix_in_function;
        return;
    }
    RingInfo* ring1 = A->ringinfo;
    RingInfo* ring2 = B->ringinfo;
    RingInfo* ring3 = result->ringinfo;
    unsigned int sizeofmatr1 = A->sizeofmatr;
    unsigned int sizeofmatr2 = B->sizeofmatr;
    unsigned int sizeofmatr3 = result->sizeofmatr;
    if (ring1 == ring2 && ring3 == ring1 && sizeofmatr1 == sizeofmatr2 && sizeofmatr3 == sizeofmatr1)
    {
        void (*Sum)(void*, void*, void*);
        Sum = ring1->sum;
        void (*Mult)(void*, void*, void*);
        Mult = ring1->mult;
        sqmatr* tmp1 = Newsqmatrix(ring1, sizeofmatr1);
        sqmatr* tmp2 = Newsqmatrix(ring2, sizeofmatr2);
        Sqmatrixcopy(A, tmp1);
        Sqmatrixcopy(B, tmp2);
        Zerosqmatrix(result);
        for (int i = 0; i < sizeofmatr1; ++i)
            for (int j = 0; j < sizeofmatr1; ++j)
            {
                void* tmp = malloc(ring1->size * sizeofmatr1);
                for (int k = 0; k < sizeofmatr1; ++k)
                    Mult(Getvalue(tmp1, i, k), Getvalue(tmp2, k, j), tmp + k * ring1->size);
                for (int k = 0; k < sizeofmatr1; ++k)
                    Sum(Getvalue(result, i, j), tmp + k * ring1->size, Getvalue(result, i, j));
                free(tmp);
            }
        Sqmatrixdelete(tmp1);
        Sqmatrixdelete(tmp2);
    }
    else
    {
        if(ring1 != ring2 || ring3 != ring1)
            err = rings_are_not_equal_in_function;
        else if(sizeofmatr1 != sizeofmatr2 || sizeofmatr3 != sizeofmatr1)
            err = sizes_of_matrix_are_not_equal_in_function;
    }
}

void Sqmatrixscalarmult(const sqmatr* scalar, const sqmatr* A, sqmatr* result)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0 || !result || !result->ringinfo || !result->sizeofmatr)
    {
        err = bad_matrix_in_function;
        return;
    }
    RingInfo* ring1 = scalar->ringinfo;
    RingInfo* ring2 = A->ringinfo;
    RingInfo* ring3 = result->ringinfo;
    unsigned int sizeofscalar = scalar->sizeofmatr;
    unsigned int sizeofmatr1 = A->sizeofmatr;
    unsigned int sizeofmatr2 = result->sizeofmatr;
    if(sizeofscalar == 1 && sizeofmatr1 == sizeofmatr2 && ring1 == ring2 && ring3==ring1)
    {
        void (*Mult)(void*, void*, void*);
        Mult = ring1->mult;
        for (int i = 0; i < sizeofmatr1; ++i)
            for (int j = 0; j < sizeofmatr1; ++j)
                Mult(Getvalue(A, i, j), Getvalue(scalar, 0, 0), Getvalue(result, i, j));
    }
    else
    {
        if(sizeofscalar != 1)
            err = bad_size_of_matrix_in_function;
        else if(ring1 != ring2 || ring3 != ring1)
            err = rings_are_not_equal_in_function;
        else if(sizeofmatr1 != sizeofmatr2)
            err = sizes_of_matrix_are_not_equal_in_function;
    }
}

void Sqmatrixalgcompl(const sqmatr* A, unsigned int row_adress, unsigned int col_adress, sqmatr* result)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0 || !result || !result->ringinfo || !result->sizeofmatr)
    {
        err = bad_matrix_in_function;
        return;
    }
    unsigned int sizeofmatr = A->sizeofmatr;
    unsigned int sizeofres = result->sizeofmatr;
    RingInfo* ring = A->ringinfo;
    RingInfo* resring = result->ringinfo;

    if(row_adress <= sizeofmatr && col_adress <= sizeofmatr && sizeofres == 1 && ring == result->ringinfo)
    {
        sqmatr *Minor = Newsqmatrix(ring, sizeofmatr - 1);
        Zerosqmatrix(Minor);

        sqmatr *signum = Newsqmatrix(ring, 1);
        Zerosqmatrix(signum);
        if ((row_adress + col_adress) % 2 == 0)
            memcpy(Getvalue(signum, 0, 0), ring->one, ring->size);
        else
            ring->minus(ring->one, Getvalue(signum, 0, 0));

        for (int i = 0; i < sizeofmatr; i++)
            for (int j = 0; j < sizeofmatr; j++)
            {
                if (i < row_adress && j < col_adress)
                    memcpy(Getvalue(Minor, i, j), Getvalue(A, i, j), ring->size);
                else if (i < row_adress && j > col_adress)
                    memcpy(Getvalue(Minor, i, j - 1), Getvalue(A, i, j), ring->size);
                else if (i > row_adress && j < col_adress)
                    memcpy(Getvalue(Minor, i - 1, j), Getvalue(A, i, j), ring->size);
                else if (i > row_adress && j > col_adress)
                    memcpy(Getvalue(Minor, i - 1, j - 1), Getvalue(A, i, j), ring->size);
            }

        Sqmatrixdet(Minor, result);
        ring->mult(Getvalue(signum, 0, 0), Getvalue(result, 0, 0), Getvalue(result, 0, 0));

        Sqmatrixdelete(Minor);
        Sqmatrixdelete(signum);
    }
    else
    {
        if(sizeofres != 1)
            err = bad_size_of_matrix_in_function;
        else if(resring != ring)
            err = rings_are_not_equal_in_function;
        else if(row_adress > sizeofmatr)
            err = row_adress_is_larger_than_size_of_matrix;
        else if(col_adress > sizeofmatr)
            err = col_adress_is_larger_than_size_of_matrix;
    }
}

void Sqmatrixdet(const sqmatr* A, sqmatr* result)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0 || !result || !result->ringinfo || !result->sizeofmatr)
    {
        err = bad_matrix_in_function;
        return;
    }
    unsigned int sizeofmatr = A->sizeofmatr;
    RingInfo *ring = A->ringinfo;
    sqmatr *det = result; //просто переименовали
    Zerosqmatrix(det);
    if (det->sizeofmatr == 1 && ring == det->ringinfo)
    {
        if (sizeofmatr == 1)
            memcpy(Getvalue(det, 0, 0), Getvalue(A, 0, 0), ring->size);
        else
        {
            // Раскладываем по первой строке
            int i = 0;
            for (int j = 0; j < sizeofmatr; j++)
            {
                sqmatr* tmp = Newsqmatrix(ring, 1);
                Zerosqmatrix(tmp);
                Sqmatrixalgcompl(A, i, j, tmp);
                ring->mult(Getvalue(tmp, 0, 0), Getvalue(A, i, j), Getvalue(tmp, 0, 0));
                ring->sum(Getvalue(det, 0, 0), Getvalue(tmp, 0, 0), Getvalue(det, 0, 0));
                Sqmatrixdelete(tmp);
            }
        }
    }
    else
    {
        if(det->sizeofmatr != 1)
            err = bad_size_of_matrix_in_function;
        else if(ring != det->ringinfo)
            err = rings_are_not_equal_in_function;
    }
}

void Sqmatrixtranspose(const sqmatr* A, sqmatr* result)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0 || !result || !result->ringinfo || !result->sizeofmatr)
    {
        err = bad_matrix_in_function;
        return;
    }
    RingInfo* ring1 = A->ringinfo;
    RingInfo* ring2 = result->ringinfo;
    unsigned int sizeofmatr1 = A->sizeofmatr;
    unsigned int sizeofmatr2 = result->sizeofmatr;
    if(ring1 == ring2 && sizeofmatr1 == sizeofmatr2)
    {
        sqmatr* tmp = Newsqmatrix(ring1, sizeofmatr1);
        Sqmatrixcopy(A, tmp);
        for (int i = 0; i < sizeofmatr1; ++i)
            for (int j = 0; j < sizeofmatr2; ++j)
                memcpy(Getvalue(result, j, i), Getvalue(tmp, i, j), ring1->size);
        Sqmatrixdelete(tmp);
    }
    else
    {
        if(ring1 != ring2)
            err = rings_are_not_equal_in_function;
        else if(sizeofmatr1 != sizeofmatr2)
            err = sizes_of_matrix_are_not_equal_in_function;
    }
}

void Sqmatrixinverse(const sqmatr* A, sqmatr* result)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0 || !result || !result->ringinfo || !result->sizeofmatr)
    {
        err = bad_matrix_in_function;
        return;
    }
    unsigned int sizeofmatr1 = A->sizeofmatr;
    unsigned int sizeofmatr2 = result->sizeofmatr;
    RingInfo* ring1 = A->ringinfo;
    RingInfo* ring2 = result->ringinfo;
    sqmatr* delta = Newsqmatrix(ring1, 1);
    Zerosqmatrix(delta);
    Sqmatrixdet(A, delta);

    if(sizeofmatr1 == sizeofmatr2 && ring1 == ring2)
    {
        sqmatr* invA = Newsqmatrix(ring1, sizeofmatr1);
        Zerosqmatrix(invA);
        for (int i = 0; i < sizeofmatr1; ++i)
            for (int j = 0; j < sizeofmatr1; ++j)
            {
                sqmatr* tmp = Newsqmatrix(ring1, 1);
                Sqmatrixalgcompl(A, i, j, tmp);
                Putvalue(invA, i, j, tmp);
            }
        sqmatr* invDelta = Newsqmatrix(ring1, 1);
        E_matrix(invDelta);
        ring1->inverse(Getvalue(delta, 0, 0), Getvalue(invDelta, 0, 0));
        Sqmatrixscalarmult(invDelta, invA, invA);
        Sqmatrixtranspose(invA, invA);
        Sqmatrixcopy(invA, result);
        Sqmatrixdelete(invA);
        Sqmatrixdelete(invDelta);
    }
    else
    {
        if(ring1 != ring2)
            err = rings_are_not_equal_in_function;
        else if(sizeofmatr1 != sizeofmatr2)
            err = sizes_of_matrix_are_not_equal_in_function;
    }
}

void Sqmatrixlincombofrows(sqmatr* A, unsigned int row_adress, const void* coefs)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0 || !coefs)
    {
        if(!coefs)
            err = bad_coefs_in_function;
        else
            err = bad_matrix_in_function;
        return;
    }
    RingInfo* ring = A->ringinfo;
    unsigned int sizeofmatr = A->sizeofmatr;
    if(row_adress <= sizeofmatr)
    {
        sqmatr* tmp = Newsqmatrix(ring, sizeofmatr);
        Sqmatrixcopy(A, tmp);
        for (int i = 0; i < sizeofmatr; ++i)
        {
            for (int j = 0; j < sizeofmatr; ++j)
                ring->mult(Getvalue(tmp, i, j), coefs + i * ring->size, Getvalue(tmp, i, j));
            for (int j = 0; j < sizeofmatr; ++j)
                ring->sum(Getvalue(A, row_adress, j), Getvalue(tmp, i, j), Getvalue(A, row_adress, j));
        }
        Sqmatrixdelete(tmp);
    }
    else
        err = row_adress_is_larger_than_size_of_matrix;


}

void Sqmatrixlincombofcols(sqmatr* A, unsigned int col_adress, const void* coefs)
{
    if(!A || !A->ringinfo || A->sizeofmatr == 0 || !coefs)
    {
        if(!coefs)
            err = bad_coefs_in_function;
        else
            err = bad_matrix_in_function;
        return;
    }
    RingInfo* ring = A->ringinfo;
    unsigned int sizeofmatr = A->sizeofmatr;
    sqmatr* tmp = Newsqmatrix(ring, sizeofmatr);
    if(col_adress <= sizeofmatr)
    {
        Sqmatrixcopy(A, tmp);
        for (int j = 0; j < sizeofmatr; ++j)
        {
            for (int i = 0; i < sizeofmatr; ++i)
                ring->mult(Getvalue(tmp, i, j), coefs + j * ring->size, Getvalue(tmp, i, j));
            for (int i = 0; i < sizeofmatr; ++i)
                ring->sum(Getvalue(A, i, col_adress), Getvalue(tmp, i, j), Getvalue(A, i, col_adress));
        }
        Sqmatrixdelete(tmp);
    }
    else
        err = col_adress_is_larger_than_size_of_matrix;
}
