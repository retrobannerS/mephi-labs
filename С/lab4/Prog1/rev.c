#include "rev.h"
#include <stdlib.h>
#include <string.h>

char* reverse(const char *str)
{
    char *tmp = strdup(str);

    char *res = malloc(strlen(str) * sizeof(char));
    *res = '\0';
    unsigned len = 0;

    char *word = strtok(tmp, " \t");

    while (NULL != word)
    {
        unsigned word_len = strlen(word);
        reverse_word(word, word_len);
        res = strcat(res, word);
        len += word_len;
        res[len++] = ' ';
        word = strtok(NULL, " \t");
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