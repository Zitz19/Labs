#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Item *newItem(Item *head, int id) {
    Item *ptr = head;
    Item *prev = NULL;
    while (ptr) {
        prev = ptr;
        ptr = ptr->next;
    }
    ptr = calloc(1, sizeof(Item));
    if (prev)
        prev->next = ptr;
    ptr->id = id;
    ptr->next = NULL;
    if (!head)
        head = ptr;
    return head;
}

void freeList(Item *head) {
    Item *tmp = head;
    while (tmp) {
        tmp = tmp->next;
        free(head);
        head = tmp;
    }
}

Item *removeItem(Item *head, int id) {
    Item *tmp = head;
    Item *prev = NULL;
    while (tmp && tmp->id != id) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp) {
        if (prev)
            prev->next = tmp->next;
        else
            head = tmp->next;
    }
    free(tmp);
    return head;
}

Item *newItem_modified(Item *head, int id, int c) {
    Item *ptr = head;
    Item *prev = NULL;
    while (ptr) {
        prev = ptr;
        ptr = ptr->next;
    }
    ptr = calloc(1, sizeof(Item));
    if (prev)
        prev->next = ptr;
    ptr->id = id;
    ptr->c = c;
    ptr->next = NULL;
    if (!head)
        head = ptr;
    return head;
}