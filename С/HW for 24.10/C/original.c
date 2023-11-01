#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void arrayRemoveDups(int *A, unsigned int*len);
int *arrayInput (unsigned int *len);
void arrayOutput (int *A, unsigned int len);

int main()
{
    unsigned int len;
    int *A = arrayInput(&len);

    clock_t start = clock();
    arrayRemoveDups(A, &len);
    clock_t end = clock();
    printf("Program worked: %.3Lfs\n", (long double)(end - start) / CLOCKS_PER_SEC);

    arrayOutput(A, len);
    free(A);                                            //Очищаем память
    return 0;
}

int *arrayInput (unsigned int *len)
{
    printf("Write length of array:");
    scanf("%u", len);

    int *A = malloc(*len * sizeof(int));                    // указатель на начало блока, выделенной памяти

    if (NULL == A)                                               // если произошла ошибка выделения памяти...
    {
        printf("\nFailed to allocate memory\n");
        exit(1); //выходим из программы
    }

    for (int i = 0; i < *len; i++)                               //Каким либо образом заполняем массив
    {
        //printf("Write integer at index %d:", i);
        //scanf("%d", &A[i]);
        A[i] = rand();
    }

    return A;                                                    //Возвращаем указатель на начало массива
}

void arrayRemoveDups(int *A, unsigned int *len)
{
    for (int i = 0; i <= *len - 2; i++)
    {
        for (int j = i + 1; j <= *len - 1; j++)
        {
            if (A[i] == A[j])
            {
                for (int k = j; k <= *len - 2; k++)                 // обнаружив, дубликат переносим все элементы массива влево на 1 до самого дубликата.
                    A[k] = A[k+1];

                --(*len), --j;                                      // уменьшаем длинy и j.
            }
        }
    }
}

void arrayOutput(int *A, unsigned int len)
{
    printf("\nArray without duplicates has length %u:\n", len);
    printf("\n");
    for (int i = 0; i <= len - 1; i++)
    {
        printf("Element at index %d: %d\n", i, A[i]);
    }
}