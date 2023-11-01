#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

#include "mystring.h"

#define DELIM " \t"
#define PROMPT "> "

size_t mystrlen(const char *s) {
    int res = 0;
    while (*s) {
        ++s, ++res;
    }
    return res;
}

char *process(const char *);

int main() {
    char *input = readline(PROMPT);
    while (input != NULL) {
        printf("\"%s\"\n", input);
        char *output = process(input);
        printf("\"%s\"\n", output);
        free(input);
        free(output);
        input = readline(PROMPT);
    }
    return 0;
}

char *process(const char *str) {
    char *s = strdup(str);
    int s_len = mystrlen(s);
    char *res = calloc(s_len + 1, sizeof(char));
    int len = 0;
    char *word = strtok(s, DELIM);
    while (word != NULL) {
        printf("Word: \"%s\"\n", word);
        int w_len = mystrlen(word) - 1;
        if (w_len > 0) {
            memcpy(res + len, word + 1, w_len * sizeof(char));
            len += w_len;
            res[len] = ' ';
            ++len;
        }
        printf("Result: \"%s\"\n", res);
        word = strtok(NULL, DELIM);
    }
    free(s);
    if (len > 0) {
        --len;
    }
    res[len] = '\0';
    res = realloc(res, (len + 1) * sizeof(char));
    return res;
}