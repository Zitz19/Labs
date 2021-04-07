#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

const int MAX_SIZE = 17575; // Максимальный размер таблицы для ключа из 3 английских букв

Table *makeTable() {
    Table *table = calloc(1, sizeof(Table));
    table->size = MAX_SIZE;
    table->kSpace1 = calloc(table->size, sizeof(keySpace1));
    table->kSpace2 = calloc(table->size, sizeof(keySpace2));
    return table;
}

void l_freeList(List *head) {
    List *temp = head;
    do {
        temp = temp->next;
        free(head->info->data);
        free(head->info);
        free(head);
        head = temp;
    } while(head);
}

void freeTable(Table *table) {
    int key2;
    for (int i = 0; i < MAX_SIZE; i++) {
        if (table->kSpace1[i].info != NULL) {
            key2 = table->kSpace1[i].info->key2;
            l_freeList(table->kSpace2[key2].list);
        }
    }
    free(table->kSpace1);
    free(table->kSpace2);
    free(table);
}

List *l_newItem(List *head, Item *item) {
    List *temp = head;
    List *pr_temp = NULL;
    int i = 0;
    while (temp != NULL) {
        pr_temp = temp;
        temp = temp->next;
        i++;
    }
    temp = calloc(1, sizeof(List));
    temp->info = item;
    temp->prev = pr_temp;
    if (!head) {
        head = temp;
    }
    else {
        pr_temp->next = temp;
    }
    temp->next = NULL;
    temp->release = i;
    return head;
}

int addItem(Table *table, int par, int key1, int key2, char *str) {
    if (table->kSpace1[key1].status) {return 0;}
    Item *item = calloc(1, sizeof(Item));
    item->data = str;
    item->key1 = key1;
    item->key2 = key2;
    table->kSpace1[key1].status = 1;
    table->kSpace1[key1].key = key1;
    table->kSpace1[key1].par = par;
    table->kSpace1[key1].info = item;
    table->kSpace2[key2].key = key2;
    table->kSpace2[key2].list = l_newItem(table->kSpace2[key2].list, item);
}

void ks1_parSearch(Table *table, int parent) {
    puts("| STATUS | PARENT |   KEY  | INFO ");
    for (int i = 0; i < MAX_SIZE; i++) {
        if ((table->kSpace1[i].status != 0) && (table->kSpace1[i].par == parent)) {
            printf("|   %d    |  %d |  %d | %s\n", table->kSpace1[i].status, table->kSpace1[i].par, table->kSpace1[i].key, table->kSpace1[i].info->data);
        }
    }
}

void ks1_delete(Table *table, int key1) {

}