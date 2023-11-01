#include "list.h"
#include <stdlib.h>
#include <stdio.h>

list *list_new()
{
    list *tmp = (list *) calloc(1, sizeof(list));
    return (tmp)? tmp:NULL;
}

void list_delete(list *list)
{
    item *ptr = list->head, *ptr_prev;
    while (ptr)
    {
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
    free(list);
}

void list_print(const list *list)
{
    item *ptr = list->head;

    while (ptr)
    {
        printf("%c", ptr->symb);
        ptr = ptr->next;
    }
    printf("\"\n");
}

int list_push_back(list *list, char symb)
{
    item *ptr = (item *) malloc(sizeof(item));
    if (!ptr) return 1;

    ptr->symb = symb;
    ptr->next = NULL;
    if (!list->head)
    {
        list->head = ptr;
        list->tail = ptr;
    }
    else
    {
        list->tail->next = ptr;
        list->tail = ptr;
    }
    return 0;
}

void list_remove_dups(list *list)
{
    if(list->head == NULL || list->tail == NULL
       || list->head == list->tail) return;

    item *ptr = list->head->next, *ptr_prev = list->head;
    while(ptr)
    {
        while(ptr->symb == ptr_prev->symb)
        {
            if(!ptr->next)
            {
                list->tail = ptr_prev;
                ptr_prev->next = NULL;
                free(ptr);
                return;
            }
            else
            {
                ptr_prev->next = ptr->next;
                item *tmp = ptr;
                ptr = ptr->next;
                free(tmp);
            }
        }
        ptr_prev = ptr;
        ptr = ptr->next;
    }
}

void list_remove_spaces(list *list)
{
    if(list->head == NULL || list->tail == NULL) return;
    item *ptr1 = list->head, *ptr2 = list->tail;
    if(ptr1->symb == ' ')
    {
        if(!ptr1->next)
        {
            list->tail = NULL;
            list->head = NULL;
            free(ptr1);
            return;
        }
        else
        {
            item *tmp = ptr1;
            ptr1 = ptr1->next;
            list->head = ptr1;
            free(tmp);
        }
    }
    if(ptr2->symb == ' ')
    {
        while(ptr1->next != ptr2)
            ptr1 = ptr1->next;
        list->tail = ptr1;
        ptr1->next = NULL;
        free(ptr2);
    }
}