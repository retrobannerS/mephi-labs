#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "options.h"
#include "gen.h"
#include "sorts.h"

int main (int argc, char **argv)
{
    char *sort = "qsort";
    unsigned num_arrays, len;

    if (options(argc, argv, &sort, &len, &num_arrays) == 1) goto A;

    int *data;
    long double time = 0;
    for(unsigned i = 1; i <= num_arrays; i++)
    {
        if (generating(&data, len) == 1) goto A;
        clock_t start = clock();
        if (sorting(data, len, sort) == 1) goto A;
        clock_t end = clock();
        time += (long double) (end - start) / CLOCKS_PER_SEC;
        free(data);
    }
    printf("%Lf", time/num_arrays);
    return 0;

    A:
    free(data);
    return 1;
}
