#include "COMPLEX.h"
#include "..\Errors.h"
#include <stdio.h>

complex complex0 = {0, 0};
complex complex1 = {1, 0};

void Complexsum(void* A, void* B, void* result)
{
    if(!A || !B || !result)
    {
        err = bad_arguments_in_operation;
        return;
    }
    complex *A1 = (complex*)A;
    complex *B1 = (complex*)B;
    complex *C1 = (complex*)result;

    C1->Re = A1->Re + B1->Re;
    C1->Im = A1->Im + B1->Im;
}

void Complexmult(void* A, void* B, void* result)
{
    if(!A || !B || !result)
    {
        err = bad_arguments_in_operation;
        return;
    }
    complex *A1 = (complex*)A;
    long double x1 = A1->Re;
    long double y1 = A1->Im;
    complex *B1 = (complex*)B;
    long double x2 = B1->Re;
    long double y2 = B1->Im;
    complex *C1 = (complex*)result;

    C1->Re = x1 * x2 - y1 * y2;
    C1->Im = x1 * y2 + y1 * x2;

}

void Complexminus(void* A, void* result)
{
    if(!A || !result)
    {
        err = bad_arguments_in_operation;
        return;
    }
    complex *A1 = (complex*)A;
    complex *B1 = (complex*)result;

    B1->Re = (-1) * A1->Re;
    B1->Im = (-1) * A1->Im;

}

void Complexinverse(void* A, void* result)
{
    if(!A || !result)
    {
        err = bad_arguments_in_operation;
        return;
    }
    complex *A1 = (complex*)A;
    complex *B1 = (complex*)result;

    long double module = A1->Re * A1->Re + A1->Im * A1->Im;
    if (module != 0)
    {
        B1->Re = A1->Re / module;
        B1->Im = (-1) * A1->Im / module;
    }
    else
    {
        err = division_by_zero;
    }
}

void Complexprint (void* A)
{
    if(!A)
    {
        err = bad_arguments_in_operation;
        return;
    }
    printf("%8.3Lf + %8.3Lf*i", ((complex*)A)->Re, ((complex*)A)->Im);
}

void Complexinput(void* A)
{
    if(!A)
    {
        err = bad_arguments_in_operation;
        return;
    }

    printf("\nRe:\t");
    char check1 = scanf("%Lf", &(((complex*)A)->Re));
    int check2 = getchar();

    while(check1 != 1 || check2 != '\n')
    {
        if (check2 == -1)                                              //если произошли ошибка ввода или конец ввода
        {
            err = eof;
            return;
        }

        else
            printf("Введено некорректная часть комплексного числа. Попробуйте заново:");

        scanf("%*[^\n]%*c");
        printf("\nRe:\t");
        check1 = scanf("%Lf", &(((complex*)A)->Re));
        check2 = getchar();
    }

    printf("\nIm:\t");
    check1 = scanf("%Lf", &(((complex*)A)->Im));
    check2 = getchar();

    while(check1 != 1 || check2 != '\n')
    {
        if (check2 == -1)                                              //если произошли ошибка ввода или конец ввода
        {

        }

        else
            printf("You`ve written incorrect value. \nTry again:");

        scanf("%*[^\n]%*c");
        printf("\nIm:\t");
        check1 = scanf("%Lf", &(((complex*)A)->Im));
        check2 = getchar();
    }

}

