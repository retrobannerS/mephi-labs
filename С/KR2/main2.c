#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *process(const char *str)
{
    char *s = strdup(str);
    int len = strlen(s);
    char *res = malloc(len * sizeof (char));
    int r_len = 0;
    char *word = strtok(s, " \t");
    while(word != NULL)
    {
        int len_word = strlen(word);
        for(int i = 0; i < len_word/2; i++)
        {
            char tmp = word[i];
            word[i] = word[len_word - i - 1];
            word[len_word - i - 1] = tmp;
        }
        strcat(res, word);
        strcat(res, " ");
        word = strtok(NULL, " \t");
    }
    res[strlen(res) - 1] = '\0';
    res = realloc(res, strlen(res) + 1);
    free(s);
    return res;
}

char *process2(const char *str)
{
    if (str[0] == '\0') return str;
    char *s = strdup(str);
    int len = strlen(s);

    char *res = malloc((len + 1) * sizeof (char));
    res[0] = '\0';
    char *word = strtok(s, " \t");
    char *word1 = word;
    while (word != NULL)
    {
        if (word[0] != word1[0])
        {
            res = strcat(res, word);
            res = strcat(res, " ");
        }
        word = strtok(NULL, " \t");
    }
    res[strlen(res) - 1] = '\0';
    res = realloc(res, strlen(res) + 1);
    free(s);
    return res;
}

char *process3(char *str)
{
    if(str[0] == '\0') return str;
    char *s = strdup(str);
    unsigned long len = strlen(s);
    char* res = malloc(2*len* sizeof(char));
    res[0]= '\0';
    char *word = strtok(s, " \t");
    if(!word) return s;
    for(int i = 1; word != NULL; i++)
    {
        res = strcat(res, word);
        res = strcat(res, " ");

        if (i % 2 == 0)
        {
            res = strcat(res, word);
            res = strcat(res, " ");
        }

        word = strtok(NULL, " \t");
    }
    res[strlen(res) - 1] = '\0';
    res = realloc(res, (strlen(res) + 1) * sizeof(char));
    free(s);
    return res;

}

char *process4(const char *str)
{
    char *s = malloc(2 * (strlen(str) + 1) * sizeof(char));
    int j = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        s[j++] = str[i];
        if ('A'<=str[i] && str[i]<='Z')
            s[j++] = str[i];
    }
    s[j] = '\0';
    s = realloc(s, strlen(s) + 1);
    return s;
}
int main()
{
    char str[] = "   YA lublu    chitat`   ";
    char *res = process4(str);
    printf("%s\n", res);
    free(res);
}