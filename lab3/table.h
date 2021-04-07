#ifndef TABLE_H
#define TABLE_H

typedef struct Item {
    char *data;
    int key1;
    int key2;
}Item;

typedef struct List {
    struct Item *info;
    int release;
    struct List* next;
    struct List* prev;
}List;

typedef struct keySpace1 {
    int key;
    int par;
    int status;
    Item *info;
}keySpace1;

typedef struct keySpace2 {
    int key;
    List *list;
}keySpace2;

typedef struct Table {
    keySpace1 *kSpace1;
    keySpace2 *kSpace2;
    int size;
    int ksize1;
    int ksize2;
}Table;

Table *makeTable();
void l_freeList(List *head);
void freeTable(Table *table);
List *l_newItem(List *head, Item *item);
int addItem(Table *table, int par, int key1, int key2, char *str);
void ks1_parSearch(Table *table, int parent);

#endif