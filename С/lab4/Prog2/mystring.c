#include "mystring.h"
#include <stdlib.h>

size_t mystrlen(const char *str)
{
    if (NULL != str)
    {
        size_t i = 0;
        while (str[i] != '\0')
            i++;
        return i;
    }
    else return 0;
}

char *mystrcat(char *s1, const char *s2)
{
    unsigned len1 = (unsigned) mystrlen(s1), len2 = mystrlen(s2);
    for(unsigned i = 0; i <= len2; i++)
        s1[len1 + i] = s2[i];
    return s1;
}

char *mystrdup(const char *str)
{
    unsigned len = mystrlen(str);
    char *tmp = malloc((len + 1) * sizeof(char));
    for (unsigned i = 0; i <= len; i++)
        tmp[i] = str[i];
    return tmp; 
}

char *mystrtok(char* str, const char* sep)
{
    static char *word;
    if (str != NULL)
        word = str;
    while(mystrcspn(word, sep) == 0)
    {
        if (word[0] == '\0')
            return NULL;
        word++;
    }
    char *new_word = word;
    word += mystrcspn(word, sep);
    *word = '\0';
    word++;
    return new_word;
}

size_t mystrcspn(const char *str, const char *srch)
{
    unsigned len_str = mystrlen(str), len_srch = mystrlen(srch);
    for(unsigned i = 0; i < len_str; i++)
        for(unsigned j = 0; j < len_srch; j++)
            if (str[i] == srch[j]) return i;
    return len_str;
}