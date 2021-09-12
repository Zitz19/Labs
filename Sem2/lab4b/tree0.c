#include <stdio.h>
#include <stdlib.h>
#include "tree0.h"

Node *newNode(float x, char *str) {
    Node *ptr = calloc(1, sizeof(Node));
    ptr->n = 1;
    ptr->data[0] = calloc(1, sizeof(Data));
    ptr->data[0]->f = x;
    ptr->data[0]->str = str;
    return ptr;
}

void sort(Node *ptr) {
    int k;
    Data *temp;
    if (ptr->n == 2 && ptr->key[0] > ptr->key[1]) {
        k = ptr->key[0];
        ptr->key[0] = ptr->key[1];
        ptr->key[1] = k;
        temp = ptr->data[0];
        ptr->data[0] = ptr->data[1];
        ptr->data[1] = temp;
    }
}

unsigned int isLeaf(Node *ptr) {
    if ((ptr->left == NULL) && (ptr->middle == NULL) && (ptr->right == NULL))
        return 1;
    else
        return 0;
}

unsigned int findKey(Node *ptr, int key) {
    for (int i = 0; i < ptr->n; i++) {
        if (ptr->key[i] == key)
            return 1;
    }
    return 0;
}

void nodeInsert(Node *ptr, int key, float f, char *str) {
    ptr->key[1] = key;
    ptr->data[1]->f = f;
    ptr->data[1]->str = str;
    sort(ptr);
}

Tree *BtreeCreate(float f, char *str) {
    Node *ptr = newNode(f, str);
    Tree *tree = calloc(1, sizeof(Tree));
    tree->root = ptr;
    return tree;
}

Node *BtreeSearch(Node *ptr, int key) {
    if (!ptr)
        return NULL;
    if (findKey(ptr, key))
        return ptr;
    else if (key < ptr->key[0])
        return BtreeSearch(ptr->left, key);
    else if ((ptr->n == 2) && (key < ptr->key[1]) || (ptr->n == 1))
        return BtreeSearch(ptr->middle, key);
    else if (ptr->n == 2)
        return BtreeSearch(ptr->right, key);
}

Node *BtreeInsert(Node *root, float f, char *str, int key) {
    if (!root)
        newNode(f, str);
    if (isLeaf(ptr))
}