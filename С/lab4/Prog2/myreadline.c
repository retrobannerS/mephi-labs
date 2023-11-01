#include "myreadline.h"
#include <stdlib.h>
#include <stdio.h>
#include "mystring.h"

char *myreadline(const char* print)
{
    printf("%s", print);

    char *str = (char *) malloc(1);
    *str = '\0';
    char buf[31];
    unsigned int n, len = 0;

    do{
        n = scanf("%30[^\n]", buf);

        if(n == -1)
        {
            free(str);
            return NULL;
        }

        else if (n == 0)
            scanf("%*c");

        else
        {
            len += mystrlen(buf);
            str = (char *)realloc(str, len + 1);
            mystrcat(str, buf);
        }
    } while(n > 0);

    return str;
}