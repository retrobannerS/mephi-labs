#include <stdlib.h>
#include "options.h"
#include "met.h"
#include "sorts.h"

int main (int argc, char **argv)
{
    char *sort = "qsort";
    char *id = "score";
    char *in_file, *out_file;
    unsigned short direction = 1;

    if (options(argc, argv, &sort, &id, &in_file, &out_file, &direction) == 1) goto A;

    student *data;
    unsigned len = 0;

    if(data_reading(in_file, &data, &len) == 1) goto A;
    if (sorting(data, len, sort, id, direction)) goto A;
    if(data_writing(out_file, data, len) == 1) goto A;

    for(unsigned i = 0; i < len; i++)
        free(data[i].FIO);
    free(data);

    return 0;

    A:
    for(unsigned i; i < len; i++)
        free(data[i].FIO);
    free(data);
    return 1;
}
