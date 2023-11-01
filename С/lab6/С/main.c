#include <stdio.h>
#include "list.h"

int main ()
{
    while(1)
    {
        list *list = list_new();
        if(NULL == list) goto A;

        printf("Введите строку: ");

        char c;
        while((c = (char)getchar()) != '\n')
        {
            if (c == EOF)
            {
                list_delete(list);
                goto A;
            }
            if(list_push_back(list, c) == 1)
            {
                list_delete(list);
                goto B;
            }
        }

        printf("Начальная строка: \"");
        list_print(list);

        list_remove_dups(list);
        list_remove_spaces(list);

        printf("Конечная строка: \"");
        list_print(list);
        printf("\n");

        list_delete(list);
    }

    A:
    return 0;

    B:
    fprintf(stderr,"Failed to allocate some piece of list\n");
    return 1;
}