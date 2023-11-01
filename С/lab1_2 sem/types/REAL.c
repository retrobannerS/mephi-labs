#include "REAL.h"
#include <stdio.h>
#include "..\Errors.h"

long double real0 = 0.0, real1 = 1.0;

void Realsum(void* A, void* B, void* result)
{
    if(!A || !B || !result)
    {
        err = bad_arguments_in_operation;
        return;
    }
    long double *A1 = (long double*)A;
    long double *B1 = (long double*)B;
    long double *C1 = (long double*)result;

    *C1 = *A1 + *B1;
}

void Realmult(void* A, void* B, void* result)
{
    if(!A || !B || !result)
    {
        err = bad_arguments_in_operation;
        return;
    }
    long double *A1 = (long double*)A;
    long double *B1 = (long double*)B;
    long double *C1 = (long double*)result;

    *C1 = *A1 * *B1;
}

void Realminus(void* A, void* result)
{
    if(!A || !result)
    {
        err = bad_arguments_in_operation;
        return;
    }
    long double *A1 = (long double *) A;
    long double *B1 = (long double *) result;

    *B1 = (-1) * *A1;
}

void Realinverse(void* A, void* result)
{
    if(!A || !result)
    {
        err = bad_arguments_in_operation;
        return;
    }
    long double *A1 = (long double*)A;
    long double *B1 = (long double*)result;
    if (B1 && *A1 != 0)
        *B1 = 1/(*A1);
    else
    {
        err = division_by_zero;
    }
}

void Realprint(void* A)
{
    if(!A)
    {
        err = bad_arguments_in_operation;
        return;
    }
    printf("%8.3Lf", *(long double*)A);
}

void Realinput(void* A)
{
    if(!A)
    {
        err = bad_arguments_in_operation;
        return;
    }
    char check1 = scanf("%Lf", (long double*)A);
    int check2 = getchar();

    while(check1 != 1 || check2 != '\n')
    {
        if (check2 == -1)                                              //если произошли ошибка ввода или конец ввода
        {
            err = eof;
            return;
        }

        else
            printf("Введено некорректное вещественное число. Попробуйте заново:");

        scanf("%*[^\n]%*c");
        check1 = scanf("%Lf", (long double*)A);
        check2 = getchar();
    }
}

