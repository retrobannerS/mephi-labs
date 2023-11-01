#include "gen.h"
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int generating(int **array, unsigned len)
{
    srand(time(NULL));
    int *tmp = malloc(len * sizeof (int));
    if (NULL == tmp)
    {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }
    for(unsigned i = 0; i < len; i++)
        tmp[i] = rand();
    *array = tmp;
    return 0;
}