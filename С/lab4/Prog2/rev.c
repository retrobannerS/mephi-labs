#include "rev.h"
#include <stdlib.h>
#include "mystring.h"

char *reverse(const char *str)
{
    char *tmp = mystrdup(str);
    unsigned int size = mystrlen(str);
    char *res = (char*)malloc((size + 1) * sizeof(char));
    *res = '\0';
    unsigned len = 0;

    char *word = mystrtok(tmp, " \t");

    while (NULL != word)
    {
        unsigned word_len = mystrlen(word);
        reverse_word(word, word_len);
        res = mystrcat(res, word);
        len += word_len;
        res[len++] = ' ';
        word = mystrtok(NULL, " \t");
    }
    res = realloc(res, (len) * sizeof(char));
    res[--len] = '\0';

    free(tmp);

    return res;
}

void reverse_word(char *word, unsigned len)
{
    for(unsigned i = 0; i < len/2; i++)
    {
        char tmp = word[i];
        word[i] = word[len - 1 - i];
        word[len - 1 - i] = tmp;
    }
}
