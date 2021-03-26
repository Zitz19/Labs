#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

Item *freeList(Item *head) {
    Item *temp = NULL;
    temp = head->next;
    free(head->data);
    free(head);
    head = temp;
    return head;
}

Item *addItem(Item *head, int size, char *str) {
    Item *temp = (Item *) calloc(1, sizeof(Item));
    temp->data = (char *) calloc(2 * size, sizeof(char));
    memcpy(temp->data, str, 2 * size * sizeof(char));
    temp->next = head;
    head = temp;
    return head;
}

char *getItem(char *str, Item **head, int size) {
    memcpy(str, (*head)->data, 2 * size * sizeof(char));
    Item *temp = (*head)->next;
    free((*head)->data);
    free(*head);
    *head = temp;
    return str;
}