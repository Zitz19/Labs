#ifndef LIST_H
#define LIST_H

typedef struct Item {
	char *data;
	struct Item *next;
} Item;

Item *makeList(int size);
void freeList(Item *head);
void addItem(Item *head, int size, char *str);
void freeItem(Item *head);

#endif
