#ifndef LAB6_LIST_H
#define LAB6_LIST_H

typedef struct item {
    char symb;
    struct item *next;
} item;

typedef struct list {
    item *head;
    item *tail;
} list;

list *list_new();

void list_delete(list *list);

void list_print(const list *list);

int list_push_back(list *list, char symb);

void list_remove_dups(list *list);

void list_remove_spaces(list *list);

#endif //LAB6_LIST_H
