#include "sorts.h"
#include "stddef.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int sorting(int *array, unsigned len, char *sort)
{
    if (!strcmp(sort, "qsort"))
        qsort(array, len, sizeof(int),
              (int (*) (const void *, const void *)) cmp_);
    else if(!strcmp(sort, "gnomes"))
        gnomes(array, len, cmp_);
    else if(!strcmp(sort, "shell"))
        shell(array, len, cmp_);
    else
    {
        printf("Wrong sorting algorithm");
        return 1;
    }

    return 0;
}

int cmp_(const int *p1, const int *p2)
{
    return ((*p1 - *p2) < 0)? -1:1;
}

void gnomes(int *data, unsigned int len, int (*cmp)(const int *, const int *))
{
    size_t i = 1;
    while (i < len)
    {
        if (i == 0)
            i = 1;
        if (cmp(data + i, data + i - 1) == 1)
            ++i;
        else
        {
            int tmp = data[i];
            data[i] = data[i-1];
            data[i-1] = tmp;
            --i;
        }
    }
}

void shell(int *data, unsigned int len, int (*cmp)(const int *, const int *))
{
    int i, j, step;
    int tmp;
    for (step = len / 2; step > 0; step /= 2)
    {
        for (i = step; i < len; i++)
        {
            tmp = data[i];
            for (j = i; j >= step; j -= step)
            {
                if (tmp < data[j - step])
                    data[j] = data[j - step];
                else
                    break;
            }
        data[j] = tmp;
        }
    }
}