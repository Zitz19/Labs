#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Node *newNode(float f, char *str) {
    Node *ptr = calloc(1, sizeof(Node));
    ptr->data[0]->f = f;
    ptr->data[0]->str = str;
    return ptr;
}

void Print(Node *ptr, long n) {
    long i;
    if (ptr) {
        if (ptr->n == 2) {
            Print(ptr->ch[2], n+8);
            for (i = 0; i < n; i++)
                printf(" ");
            for (i = 0; i < ptr->n; i++)
                printf("%d ", ptr->key[i]);
            printf("\n");
            Print(ptr->ch[1], n+8);
            Print(ptr->ch[0], n+8);
        }
        else {
            Print(ptr->ch[1], n+8);
            for (i = 0; i < n; i++)
                printf(" ");
            printf("%d ", ptr->key[0]);
            printf("\n");
            Print(ptr->ch[0], n+8);
        }
    }
}