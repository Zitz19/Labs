#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "dialog.h"

Node *newNode(char *key, char *str) {
    Node *ptr = calloc(1, sizeof(Node));
    ptr->len = 1;
    ptr->data = realloc(ptr->data, ptr->len * sizeof(char *));
    ptr->key = key;
    ptr->data[ptr->len - 1] = str;
    return ptr;
}

Node *freeNode(Node *ptr) {
    for (int i = 0; i < ptr->len; i++) {
        free(ptr->data[i]);
    }
    free(ptr->data);
    free(ptr->key);
    free(ptr);
    return NULL;
}

void Insert(Tree *tree, char *key, char *str) {
    Node *ptr = newNode(key, str);
    Node *x = treeSearch(tree->root, ptr->key);
    if (x == NULL) {
        treeInsert(tree, ptr);
    } else {
        x->len++;
        x->data = realloc(x->data, x->len * sizeof(char *));
        x->data[x->len - 1] = calloc(strlen(str) + 1, sizeof(char));
        strcpy(x->data[x->len - 1], str);
        ptr = freeNode(ptr);
    }
}

void Delete(Tree *tree, char *key) {
    Node *ptr = treeSearch(tree->root, key);
    if (ptr->len == 1) {
        treeDelete(tree, ptr);
        ptr = freeNode(ptr);
    } else {
        free(ptr->data[0]);
        ptr->len--;
    }
}

void Search(Tree *tree, char *key) {
    Node *ptr = treeSearch(tree->root, key);
    printData(ptr->data, ptr->len);
}

void Successor(Tree *tree, char *key) {
    Node *ptr = treeSearch(tree->root, key);
    Node *suc = treeSuccessor(ptr);
    printf("%s: ", suc->key);
    printData(suc->data, suc->len);
}