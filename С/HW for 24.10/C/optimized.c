#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iso646.h>

int *arrayInput (unsigned int *len);
void merge(int *array, int *left, int *right, unsigned int len_left, unsigned int len_right);
void merge_sort(int *A, unsigned int *len);
int* arrayRemoveDups(int *A, unsigned int *len);
void arrayOutput (int *A, unsigned int len);

int main()
{
    unsigned int len;
    int *A = arrayInput(&len);

    clock_t start = clock();
    merge_sort(A, &len);
    A = arrayRemoveDups(A, &len);
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

    int *A = (int*)malloc(*len * sizeof(int));              // указатель на начало блока, выделенной памяти
    if (NULL == A)                                               // если произошла ошибка выделения памяти...
    {
        printf("\nFailed to allocate memory\n");
        exit(1);                                            //выходим из программы
    }

    for (int i = 0; i < *len; i++)
    {
        printf("Write integer at index %d:", i);
        scanf("%d", &A[i]);
        //A[i] = rand();
    }

    return A;
}

void merge_sort(int *A, unsigned int *len)
{
    if (*len == 1)                            //Крайний случай рекурсии
        return;

    int mid = (*len)/2;                       //Делим массив пополам на два подмассива

    int *left = (int *) malloc(mid * sizeof(int));
    if (NULL == left)                                               // если произошла ошибка выделения памяти...
    {
        printf("\nFailed to allocate memory for left\n");
        exit(1);                                            //выходим из программы
    }
    unsigned int len_left = mid;

    int *right = (int *) malloc((*len - mid) * sizeof(int));
    if (NULL == right)                                               // если произошла ошибка выделения памяти...
    {
        printf("\nFailed to allocate memory to right\n");
        exit(1);                                            //выходим из программы
    }
    unsigned int len_right = *len - mid;

    for(int i = 0; i <= mid - 1; i++)          //Заполняем подмассивы
        left[i] = A[i];

    for(int i = mid; i <= (*len) - 1; i++)
        right[i - mid] = A[i];

    merge_sort(left, &len_left);       //Ветвим до 1 элемента в подмассивах
    merge_sort(right, &len_right);

    merge(A, left, right, len_left, len_right); //Слияем всё это
}

void merge(int *array, int *left, int *right, unsigned int len_left, unsigned int len_right)
{
    int flag_left = 0, flag_right = 0, flag_array = 0;

    while(flag_left <= (len_left - 1) and flag_right <= (len_right - 1)) //слияние
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

    while(flag_left <= (len_left - 1))              //после того, как подмассив закончился, заполняем основной массив оставшимися элементами упорядоченного подмассива
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

int* arrayRemoveDups(int *A, unsigned int *len)
{
    int* tmp = (int*) malloc((*len) * sizeof (int));
    int j = 0;
    int new_len = 0;

    for (int i = 0; i <= *len - 2; i++)
    {
        if (A[i] != A[i + 1])
        {
            tmp[j++] = A[i];
            new_len++;
        }
    }
    *len = new_len;
    free(A);
    return tmp;
}

void arrayOutput(int *A, unsigned int len)
{
    printf("\nArray without duplicates has length %u:\n", len);
    printf("\n");
    for (int i = 0; i < len; i++)
    {
        printf("Element at index %7d: %5d\n", i, A[i]);
    }
}