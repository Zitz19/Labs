#ifndef TABLE_H
#define TABLE_H

typedef struct Item {
    char *str;
    int key1;
    int key2;
}Item;

typedef struct Unit {
    struct Item *data;
    int release;
    struct Unit *next;
    struct Unit *prev;
}Unit;

typedef struct keySpace1 {
    int key;
    int par;
    int status;
    Item *data;
}keySpace1;

typedef struct keySpace2 {
    Unit *head;
}keySpace2;

typedef struct Table {
    keySpace1 *kSpace1;
    keySpace2 *kSpace2;
    int size;
    int ksize1;
    int ksize2;
}Table;

Table *makeTable();
keySpace1 *upd_KS1(Table *table);
keySpace2 *upd_KS2(Table *table);
void freeTable(Table *table);
Item *newItem(int key1, int key2, char *str);
void freeItem(Item *temp);
void swap(keySpace1 *x, keySpace1 *y);
void sort_KS1(Table *table);
int add_KS1(Table *table, Item *temp, int par);
int hash(int key);
Unit *newUnit(Unit *head, Item *data);
Unit *freeList(Unit *head);
Unit *freeUnit(Unit *head, int key2);
int add_KS2(Table *table, Item *data);
int addItem(Table *table, int par, int key1, int key2, char *str);
keySpace1 **parSearch(Table *table, int par, int *len);
int del_KS1(Table *table, int key1);
int del_KS2(Table *table, int key2, int rel);
Unit **key2_Search(Table *table, int key2, int rel, int *len);

#endif