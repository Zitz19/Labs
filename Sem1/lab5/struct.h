#ifndef _STRUCT_H_
#define _STRUCT_H_

typedef struct Item {
    char data;
    struct Item *prev;
    struct Item *next;
} Item;

typedef struct List {
    Item *head;
    Item *tail;
} List;

List* list_new();

void add_item(List *list, char symbol);

void deleteList(List *list);

void delete_item(List *list, Item *temp);

void putList(List *list);

void delete_space(List *list);

int checkPalindrome(List *list, Item *start, Item *end);

void changeList(List *list);

#endif
