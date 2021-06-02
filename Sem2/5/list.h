#ifndef LIST_H
#define LIST_H

typedef struct Item {
    int id;
    int f;
    int c;
    struct Item *next;
} Item;

Item *newItem(Item *head, int id);
void freeList(Item *head);
Item *removeItem(Item *head, int id);
Item *newItem_modified(Item *head, int id, int c);

#endif