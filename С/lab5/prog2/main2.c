#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "options.h"
#include "gen.h"
#include "sorts.h"

int main (int argc, char **argv)
{
    for(unsigned len = 1000; len <= 100000; len+=1000)
    {
        char *sort = "shell";
        unsigned num_arrays = 25;

        //if (options(argc, argv, &sort, &len, &num_arrays) == 1) goto A;

        int *data;
        long double time = 0;
        for (unsigned i = 1; i <= num_arrays; i++)
        {
            if (generating(&data, len) == 1);
            clock_t start = clock();
            if (sorting(data, len, sort) == 1);
            clock_t end = clock();
            time += (long double) (end - start) / CLOCKS_PER_SEC;
            free(data);
        }
        printf("%.2Lf\n", time / num_arrays * 1000);


    }
    return 0;
}
