#include "met.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int data_reading(char *in_file, student **data, unsigned *len)
{
    FILE *in = fopen(in_file, "r");
    if(in == NULL)
    {
        fprintf(stderr, "Failed to open file %s\n", in_file);
        return 1;
    }

    char buf[8];
    fscanf(in, "%s%*c", buf);
    *len = atoi(buf);
    student *arr = malloc(*len * sizeof(student));
    if (NULL == arr)
    {
        fprintf(stderr,"Failed to allocate memory\n");
        return 1;
    }
    for(unsigned i = 0; i < *len; i++)
    {
        arr[i].FIO = calloc(50, sizeof(student));
        if (NULL == arr)
        {
            fprintf(stderr,"Failed to allocate memory\n");
            return 1;
        }
        fscanf(in,"%s %s %lf", arr[i].FIO, arr[i].group, &arr[i].score);
    }

    if (fclose(in) == EOF)
    {
        fprintf(stderr, "Failed to close file %s\n", in_file);
        return 1;
    }

    *data = arr;

    return 0;
}

int data_writing(char *out_file, student *data, unsigned len)
{
    FILE *out = fopen(out_file, "w");

    if (NULL == out)
    {
        fprintf(stderr, "Failed to open file %s\n", out_file);
        return 1;
    }

    for(unsigned i = 0; i < len; i++)
        fprintf(out, "%s %s %lf\n", data[i].FIO, data[i].group, data[i].score);

    if (fclose(out) == EOF)
    {
        fprintf(stderr, "Failed to close file %s\n", out_file);
        return 1;
    }

    return 0;
}