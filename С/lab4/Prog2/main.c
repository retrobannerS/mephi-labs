#include "rev.h"
#include <stdio.h>
#include <stdlib.h>
#include "myreadline.h"
#include <time.h>


int main()
{
    while (1)
    {
        clock_t start = clock();

        char *input = myreadline("Введите строку: ");
        if (NULL == input) break;

        char *output = reverse(input);

        printf("Начальная строка:     \"%s\"\n", input);
        printf(" Конечная строка:     \"%s\"\n", output);

        free(input);
        free(output);

        clock_t end = clock();
        printf("Program worked: %.6Lfs\n\n", (long double)(end - start) / CLOCKS_PER_SEC);
    }
    return 0;
}