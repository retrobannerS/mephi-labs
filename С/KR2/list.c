//#include <list.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct list {
    Node *head;
} list;

list *list_new()
{
    list *tmp = (list *) calloc(1, sizeof(list));
    return (tmp)? tmp:NULL;
}

void list_delete(list *list)
{
    Node *ptr = list->head, *ptr_prev;
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
    Node *ptr = list->head;

    while (ptr)
    {
        printf("%d", ptr->data);
        ptr = ptr->next;
    }
    printf("\"\n");
}

int list_push_back(list *list, int symb)
{
    Node *ptr = (Node *) malloc(sizeof(Node));
    if (!ptr) return 1;
    Node *tail = list->head;
    while(tail)
    {
        if(!tail->next) break;
        tail = tail->next;
    }
    ptr->data = symb;
    ptr->next = NULL;
    if (!tail)
    {
        list->head = ptr;
    }
    else
    {
        tail->next = ptr;
        tail = ptr;
    }
    return 0;
}

void process1 (list *list) //удаление элемнтов, равных последнему
{
    if(list->head == NULL) return;
    if(list->head->next == NULL)
    {
        free(list->head);
        list->head = NULL;
        return;
    }
    Node *ch = list->head;
    while(ch->next != NULL)
    {
        ch = ch->next;
    }
    Node *ptr = list->head;
    Node *ptr_prev = NULL;
    while(ptr != ch)
    {
        if(ptr->data == ch->data)
        {
            Node *tmp = ptr;
            ptr = ptr->next;
            ptr_prev->next = ptr;
            free(tmp);
        }
        else
        {
            ptr_prev = ptr;
            ptr = ptr->next;
        }
    }
    ptr_prev->next = NULL;
    free(ptr);
}

void process2(list *list) //вставочка после числа <0 его модуль
{
    if(!list || !list->head) return;
    Node *ptr = list->head;
    while(ptr)
    {
        if(ptr->data < 0)
        {
            Node *tmp = malloc(sizeof (Node));
            tmp->data = (-1) * ptr->data;
            tmp->next = ptr->next;
            ptr->next = tmp;
        }
        ptr = ptr->next;
    }
}

void process3(list *list) //циклический сдвиг влево на 4
{
    if(list == NULL || list->head == NULL || list->head->next == NULL) return;
    for(int i = 0; i<4; i++)
    {
        Node *ptr_last = list->head;
        while(ptr_last->next != NULL)
        {
            ptr_last = ptr_last->next;
        }
        Node *second = list->head->next;
        list->head->next = NULL;
        ptr_last->next = list->head;
        list->head = second;
    }
}

void process4(list* list)  //вставить перед значением, делящимся на 3, его, поделенного не 3.
{
    if(list == NULL || list->head == NULL) return;
    Node *ptr = list->head;
    Node *prev;
    if(ptr->data % 3 == 0)
    {
        Node *tmp = malloc(sizeof (Node));
        tmp->data = ptr->data / 3;
        tmp->next = ptr;
        list->head = tmp;
        prev = ptr;
        ptr = ptr->next;
    }
    else
    {
        prev = NULL;
    }

    while(ptr)
    {
        if(ptr->data % 3 == 0)
        {
            Node *tmp = malloc(sizeof (Node));
            tmp->data = ptr->data / 3;
            tmp->next = ptr;
            prev->next = tmp;
        }
        prev = ptr;
        ptr = ptr->next;
    }
}

void process5(list *list)
{
    if(list == NULL || list->head == NULL || list->head->next == NULL) return;
    Node *ptr = list->head->next;
    Node *prev = list->head;

    while(ptr != NULL)
    {
        if (ptr->data < 0 && prev->data < 0)
        {
            Node *tmp = malloc(sizeof (Node));
            int sum = abs(ptr->data + prev->data);
            tmp->data = sum/2;
            tmp->next = ptr;
            prev->next = tmp;
        }
        else if (ptr->data >= 0 && prev->data >= 0)
        {
            Node *tmp = malloc(sizeof (Node));
            int sum = abs(ptr->data + prev->data);
            tmp->data = (-1) * sum/2;
            tmp->next = ptr;
            prev->next = tmp;
        }
        prev = ptr;
        ptr = ptr->next;
    }
}

int main ()
{
    while(1)
    {
        list *list = list_new();
        if(NULL == list) break;

        printf("input len:$");

        int len;
        int symb;
        scanf("%d", &len);
        for(int i = 0; i<len; i++)
        {
            printf("%d elem:$", i);
            scanf("%d", &symb);
            list_push_back(list, symb);
        }
        list_print(list);
        process5(list);
        list_print(list);

        list_delete(list);
    }

    return 0;
}