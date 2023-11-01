#include "INT.h"
#include <stdio.h>
#include "..\Errors.h"

int int0 = 0, int1 = 1;

void Intsum(void* A, void* B, void* result)
{
    if(!A || !B || !result)
    {
        err = bad_arguments_in_operation;
        return;
    }
    int* A1 = (int*)A;
    int* B1 = (int*)B;
    int* C1 = (int*)result;

    *C1 = *A1 + *B1;
}

void Intmult(void* A, void* B, void* result)
{
    if(!A || !B || !result)
    {
        err = bad_arguments_in_operation;
        return;
    }
    int* A1 = (int*)A;
    int* B1 = (int*)B;
    int* C1 = (int*)result;

    *C1 = *A1 * *B1;
}

void Intminus(void* A, void* result)
{
    if(!A || !result)
    {
        err = bad_arguments_in_operation;
        return;
    }
    int *A1 = (int *)A;
    int *B1 = (int *)result;

    *B1 = (-1) * *A1;
}

void Intinverse(void* A, void* result)
{
    err = can_not_inverse;
}

void Intprint(void* A)
{
    if(!A)
    {
        err = bad_arguments_in_operation;
        return;
    }
    printf("%8d", *(int*)A);
}

void Intinput(void* A)
{
    if(!A)
    {
        err = bad_arguments_in_operation;
        return;
    }

    char check1 = scanf("%d", (int*)A);
    int check2 = getchar();

    while(check1 != 1 || check2 != '\n')
    {
        if (check2 == -1)                                             //если произошли ошибка ввода или конец ввода
        {
            err = eof;
            return;
        }

        else
            printf("Введено некорректное целое число. Попробуйте заново:");

        scanf("%*[^\n]%*c");
        check1 = scanf("%d", (int *) A);
        check2 = getchar();
    }
}