#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iso646.h>

int *arrayInput (unsigned short int *len);
void arrayOutput (int *A, unsigned short int len);
void merge(int *array, int *left, int *right, unsigned short int len_left, unsigned short int len_right);
void merge_sort(int *A, unsigned short int *len);
void arrayRemoveDups(int *A, unsigned short int *len);

int main()
{
    unsigned short int len;
    int *A = arrayInput(&len);
    merge_sort(A, &len);
    arrayRemoveDups(A, &len);
    arrayOutput(A, len);
    free(A);                                            //Очищаем память
    return 0;
}

int *arrayInput (unsigned short int *len)
{
    printf("Write length of array:");
    scanf("%u", len);
    int *A = (int*)malloc(*len * sizeof(int));              // указатель на начало блока, выделенной памяти
    if (NULL == A)                                               // если произошла ошибка выделения памяти...
    {
        printf("\nFailed to allocate memory\n");
        exit(1); //выходим из программы
    }
    for (int i = 0; i < *len; i++)
    {
        //printf("Write integer at index %d:", i);
        //scanf("%d", &A[i]);
        A[i] = rand();
    }
    return A;
}

void merge_sort(int *A, unsigned short int *len)
{
    if (*len == 1)
        return;

    int mid = (*len)/2;

    int left[mid];
    unsigned short int len_left = mid;

    int right[*len - mid];
    unsigned short int len_right = *len - mid;

    for(int i = 0; i <= mid - 1; i++)
        left[i] = A[i];

    for(int i = mid; i <= (*len) - 1; i++)
        right[i - mid] = A[i];

    merge_sort(left, &len_left);
    merge_sort(right, &len_right);

    merge(A, left, right, len_left, len_right);
}

void merge(int *array, int *left, int *right, unsigned short int len_left, unsigned short int len_right)
{
    int flag_left = 0, flag_right = 0, flag_array = 0;

    while(flag_left <= (len_left - 1) and flag_right <= (len_right - 1))
    {
        if (left[flag_left] <= right[flag_right])
        {
            array[flag_array] = left[flag_left];
            ++flag_left, ++flag_array;
        }
        else
        {
            array[flag_array] = right[flag_right];
            ++flag_right, ++flag_array;
        }
    }

    while(flag_left <= (len_left - 1))
    {
        array[flag_array] = left[flag_left];
        ++flag_left, ++flag_array;
    }

    while(flag_right <= (len_right - 1))
    {
        array[flag_array] = right[flag_right];
        ++flag_right, ++flag_array;
    }
}

void arrayRemoveDups(int *A, unsigned short int *len)
{
    clock_t start = clock();
    for (int i = 0; i <= *len - 2; i++)
    {
        for (int j = i + 1; j <= *len - 1; j++)
        {
            if (A[i] == A[j])
            {
                for (int k = j; k <= *len - 2; k++)                 // обнаружив, дубликат переносим все элементы массива влево на 1 до самого дубликата.
                {
                    A[k] = A[k+1];
                }
                --(*len), --j;                                      // уменьшаем длинy и j.
            }
        }
    }
    clock_t end = clock();
    printf("First program worked: %.3Lfs\n", (long double)(end - start) / CLOCKS_PER_SEC);
}

void arrayOutput(int *A, unsigned short int len)
{
    printf("\nArray without duplicates has length %u:\n", len);
    printf("\n");
    for (int i = 0; i < len; i++)
    {
        printf("Element at index %3d: %5d\n", i, A[i]);
    }
}