#include <stdio.h>
#include <stdlib.h>

void process1(int **array, int *size)
{
    int *a = *array;
    int len = *size;
    int *arr = malloc(2 * len * sizeof (int));
    int j = 0;
    for (int i = 0; i<len; i++)
    {

        if(a[i] > 0)
        {
            arr[j++] = a[i];
            arr[j++] = a[i];
        }
        else if(a[i] < 0)
        {
            continue;
        }
        else
            arr[j++] = a[i];
    }
    free(*array);
    int *ar = malloc(j * sizeof (int));
    for (int i = 0; i<j; i++)
        ar[i] = arr[i];
    free(arr);
    *array = ar;
    *size = j;
}

void process2(int **array, int *size)
{
    int len = *size;
    if (len <= 0)
        return;
    int *a = *array;
    int *arr = malloc((2*len - 1) * sizeof (int));
    int j = 0;
    for(int i = 0; i < 2*len - 1; i++)
    {
        if (i%2 == 0)
            arr[i] = a[j];
        else
        {
            arr[i] = (a[j] + a[j + 1]) / 2;
            j++;
        }
    }
    free(*array);
    *array = arr;
    *size = 2*len - 1;
}

void process3(int **array, int *size)
{
    int *a = *array;
    int len = *size;
    int *arr = malloc(len * sizeof(int));
    arr[0] = a[0];
    int j = 1;
    for(int i = 1; i<len; i++)
    {
        if(a[i] <= a[i-1])
            arr[j++] = a[i];
    }
    arr = realloc(arr, j * sizeof(int));
    free(a);
    *array = arr;
    *size = j;
}

int main ()
{
    int *arr = malloc(7 * sizeof (int));
    int size = 7;
    for (int i = 0; i<size; i++)
        scanf("%d", arr + i);
    for (int i = 0; i<size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    process3(&arr, &size);
    for (int i = 0; i<size; i++)
        printf("%d ", arr[i]);
}
