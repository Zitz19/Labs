#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

const int MAX_SIZE = 17575; // Максимальный размер таблицы для ключа из 3 английских букв
//Инициализация таблицы
Table *makeTable() {
    Table *table = calloc(1, sizeof(Table));
    table->size = MAX_SIZE;
    table->ksize1 = 0;
    table->ksize2 = 0;
    table->kSpace1 = upd_KS1(table);
    table->kSpace2 = upd_KS2(table);
    return table;
}
//Перевыделение памяти keySpace1 при необходимости
keySpace1 *upd_KS1(Table *table) {
    table->kSpace1 = calloc(table->size, sizeof(keySpace1));
    //table->ksize1 = table->size;
    return table->kSpace1;
}
// Выделение памяти для keySpace2
keySpace2 *upd_KS2(Table *table) {
    table->ksize2 = 5861;
    return calloc(table->ksize2, sizeof(keySpace2));
}

//Полная очистка таблицы
void freeTable(Table *table) {
    int key2;
    for (int i = 0; i < table->size; i++) {
        if ((table->kSpace1[i].data != NULL) && (table->kSpace1[i].status != 0)) {
            key2 = hash(table->kSpace1[i].data->key2);
            table->kSpace2[key2].head = freeUnit(table->kSpace2[key2].head, table->kSpace1[i].data->key2);
        }
    }
    free(table->kSpace1);
    free(table->kSpace2);
    free(table);
}
// Создание нового элемента вне таблиц
Item *newItem(int key1, int key2, char *str) {
    Item *temp = calloc(1, sizeof(Item));
    temp->key1 = key1;
    temp->key2 = key2;
    temp->str = str;
    return temp;
}
// Удаление элемента вне таблиц
void freeItem(Item *temp) {
    free(temp->str);
    free(temp);
}
// Функции сортировки первого пространства ключей по родителю
void swap(keySpace1 *x, keySpace1 *y) {
    keySpace1 temp = *x;
    *x = *y;
    *y = temp;
}

void sort_KS1(Table *table) {
    for (int i = 0; i < table->ksize1 - 1; i++) {
        for (int j = 0; j < table->ksize1 - 1; j++) {
            if ((table->kSpace1[j].status == 1) && (table->kSpace1[j].par > table->kSpace1[j + 1].par)) {
                swap(&table->kSpace1[j], &table->kSpace1[j + 1]);
            }
        }
    }
}
// Добавление элемента в первое пространство ключей
int add_KS1(Table *table, Item *temp, int par) {
    for (int i = 0; i < table->size; i++) {
        if (table->kSpace1[i].key == temp->key1) {
            freeItem(temp);
            return 0;
        }
    }
    for (int i = 0; i < table->size; i++) {
        if (table->kSpace1[i].status != 1) {
            table->kSpace1[i].data = temp;
            table->kSpace1[i].key = temp->key1;
            table->kSpace1[i].par = par;
            table->kSpace1[i].status = 1;
            table->ksize1++;
            return 1;
        }
    }
    return 0; // Table overflow
}
// Хэш-функция
int hash(int key) {
    return key % 5861; // 5861 - близкое к 17575/3 простое число
}
// Добавление элемента в список коллизий
Unit *newUnit(Unit *head, Item *data) {
    Unit *prev = NULL;
    Unit *temp = head;
    int rel = 1;
    while (temp) {
        prev = temp;
        temp = temp->next;
        rel++;
    }
    temp = calloc(1, sizeof(Unit));
    temp->prev = prev;
    if (temp->prev) {temp->prev->next = temp;}
    else {head = temp;}
    temp->release = rel;
    temp->next = NULL;
    temp->data = data;
    return head;
}
// Очистка списка коллизий
Unit *freeList(Unit *head) {
    Unit *temp = head;
    while (temp) {
        temp = temp->next;
        freeItem(head->data);
        free(head);
        head = temp;
    }
    return head;
}

Unit *freeUnit(Unit *head, int key2) {
    Unit *temp = head;
    while (temp) {
        if (temp->data->key2 == key2) {
            if (temp == head) {head = head->next;}
            if (temp->prev) {temp->prev->next = temp->next;}
            if (temp->next) {temp->next->prev = temp->prev;}
            freeItem(temp->data);
            free(temp);
            return head;
        }
        temp = temp->next;
    }
    return head;
}
// Добавление элемента во второе пространство ключей
int add_KS2(Table *table, Item *data) {
    int x = hash(data->key2);
    keySpace2 *list = table->kSpace2 + x;
    list->head = newUnit(list->head, data);
}
// Добавление элемента в таблицу
int addItem(Table *table, int par, int key1, int key2, char *str) {
    Item *temp = newItem(key1, key2, str);
    if (add_KS1(table, temp, par) == 0) {return 0;}
    add_KS2(table, temp);
    sort_KS1(table);
    return 1;
}

keySpace1 **parSearch(Table *table, int par, int *len) {
    keySpace1 **array = NULL;
    *len = 0;
    for (int i = 0; i < table->ksize1; i++) {
        if (table->kSpace1[i].par == par) {
            (*len)++;
            array = realloc(array, *len * sizeof(keySpace1 *));
            array[*len - 1] = table->kSpace1 + i;
        }
    }
    return array;
}

int del_KS1(Table *table, int key1) {
    int x = -1;
    int key2;
    for (int i = 0; i < table->ksize1; i++) {
        if (table->kSpace1[i].par == key1) {return 0;}
        if (table->kSpace1[i].key == key1) {
            x = i;
        }
    }
    if (x != -1) {
        key2 = table->kSpace1[x].data->key2;
        table->kSpace2[hash(key2)].head = freeUnit(table->kSpace2[hash(key2)].head, key2);
        table->kSpace1[x].status = 0;
        return 1;
    }
    else {return 0;}
}

int del_KS2(Table *table, int key2, int rel) {
    int x = -1;
    int key1;
    Unit *temp = table->kSpace2[hash(key2)].head;
    while (temp) {
        if ((temp->release == rel) && (temp->data->key2 == key2)) {
            key1 = temp->data->key1;
            for (int i = 0; i < table->ksize1; i++) {
                if (table->kSpace1[i].key == key1) {
                    table->kSpace1[i].status = 0;
                    break;
                }
            }
            if (temp == table->kSpace2[hash(key2)].head) {table->kSpace2[hash(key2)].head = freeUnit(temp, key2);}
            else {freeUnit(temp, key2);}
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

Unit **key2_Search(Table *table, int key2, int rel, int *len) {
    Unit **array = NULL;
    *len = 0;
    int x = hash(key2);
    Unit *temp = table->kSpace2[x].head;
    if (rel == 0) {
        while (temp) {
            if (temp->data->key2 == key2) {
                (*len)++;
                array = realloc(array, *len * sizeof(keySpace2 *));
                array[*len - 1] = temp;
            }
            temp = temp->next;
        }
        return array;
    }
    else {
        while (temp) {
            if ((temp->data->key2 == key2) && (temp->release == rel)) {
                (*len)++;
                array = realloc(array, *len * sizeof(keySpace2 *));
                array[*len - 1] = temp;
                return array;
            }
            temp = temp->next;
        }
    }
    return NULL;
}