#include "sorts.h"
#include "stddef.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int sorting(student *array, unsigned len, char *sort, char *id, unsigned short direction)
{
    if(direction == 1)
    {
        if (!strcmp(sort, "qsort"))
        {
            if(!strcmp(id, "score"))
                qsort(array, len, sizeof(student),
                      (int (*) (const void *, const void *)) cmp_score);
            else if (!strcmp(id, "name"))
                qsort(array, len, sizeof(student),
                      (int (*) (const void *, const void *)) cmp_name);
            else if (!strcmp(id, "group"))
                qsort(array, len, sizeof(student),
                      (int (*) (const void *, const void *)) cmp_group);
            else
            {
                printf("Wrong sorting field\n");
                return 1;
            }
        }
        else if(!strcmp(sort, "gnomes"))
        {
            if(!strcmp(id, "score"))
                gnomes(array, len, cmp_score);
            else if (!strcmp(id, "name"))
                gnomes(array, len, cmp_name);
            else if (!strcmp(id, "group"))
                gnomes(array, len, cmp_group);
            else
            {
                printf("Wrong sorting field\n");
                return 1;
            }
        }
        else if(!strcmp(sort, "shell"))
        {
            if(!strcmp(id, "score"))
                shell(array, len, cmp_score);
            else if (!strcmp(id, "name"))
                shell(array, len, cmp_name);
            else if (!strcmp(id, "group"))
                shell(array, len, cmp_group);
            else
            {
                printf("Wrong sorting field\n");
                return 1;
            }
        }
        else
        {
            printf("Wrong sorting algorithm");
            return 1;
        }
    }
    else
    {
        if (!strcmp(sort, "qsort"))
        {
            if(!strcmp(id, "score"))
                qsort(array, len, sizeof(student),
                      (int (*) (const void *, const void *)) cmp_score_des);
            else if (!strcmp(id, "name"))
                qsort(array, len, sizeof(student),
                      (int (*) (const void *, const void *)) cmp_name_des);
            else if (!strcmp(id, "group"))
                qsort(array, len, sizeof(student),
                      (int (*) (const void *, const void *)) cmp_group_des);
            else
            {
                printf("Wrong sorting field\n");
                return 1;
            }
        }
        else if(!strcmp(sort, "gnomes"))
        {
            if(!strcmp(id, "score"))
                gnomes(array, len, cmp_score_des);
            else if (!strcmp(id, "name"))
                gnomes(array, len, cmp_name_des);
            else if (!strcmp(id, "group"))
                gnomes(array, len, cmp_group_des);
            else
            {
                printf("Wrong sorting field\n");
                return 1;
            }
        }
        else if(!strcmp(sort, "shell"))
        {
            if(!strcmp(id, "score"))
                shell(array, len, cmp_score_des);
            else if (!strcmp(id, "name"))
                shell(array, len, cmp_name_des);
            else if (!strcmp(id, "group"))
                shell(array, len, cmp_group_des);
            else
            {
                printf("Wrong sorting field\n");
                return 1;
            }
        }
        else
        {
            printf("Wrong sorting algorithm");
            return 1;
        }
    }
    return 0;
}

int cmp_score(const student *p1, const student *p2)
{
    return ((p1->score - p2->score) < 0)? -1:1;
}
int cmp_group(const student *p1, const student *p2)
{
    return (strcmp(p1->group, p2->group) < 0)? -1:1;
}
int cmp_name(const student *p1, const student *p2)
{
    return (strcmp(p1->FIO, p2->FIO) < 0)? -1:1;
}

int cmp_score_des(const student *p1, const student *p2)
{
    return ((p1->score - p2->score) < 0)? 1:-1;
}
int cmp_group_des(const student *p1, const student *p2)
{
    return (strcmp(p1->group, p2->group) < 0)? 1:-1;
}
int cmp_name_des(const student *p1, const student *p2)
{
    return (strcmp(p1->FIO, p2->FIO) < 0)? 1:-1;
}

void gnomes(student *data, unsigned int len, int (*cmp)(const student *, const student *))
{
    size_t i = 1;

    while (i < len)
    {
        if (i == 0)
            i = 1;
        if (cmp(data + i, data + i - 1) == 1)
            ++i;
        else
        {
            student tmp = data[i];
            data[i] = data[i-1];
            data[i-1] = tmp;
            --i;
        }
    }
}

void shell(student *data, unsigned int len, int (*cmp)(const student *, const student *))
{
    unsigned step = len/2;
    while (step > 0)
    {
        unsigned short int k = 1;
        while(k)
        {
            k = 0;
            for(unsigned i = 0; i < len - step; i++)
            {
                if(cmp(data + i, data + i + step) == 1)
                {
                    student tmp = data[i];
                    data[i] = data[i + step];
                    data[i + step] = tmp;
                    k = 1;
                }
            }
        }
        step /= 2;
    }
}