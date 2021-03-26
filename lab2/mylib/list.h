#ifndef LIST_H
#define LIST_H

typedef struct Item {
    char *data;
    struct Item *next;
} Item;

Item *freeList(Item *head);
Item *addItem(Item *head, int size, char *str);
char *getItem(char *str, Item **head, int size);

#endif
