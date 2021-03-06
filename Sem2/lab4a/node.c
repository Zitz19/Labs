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
    char **temp;
    Node *ptr = treeSearch(tree->root, key);
    if (ptr && ptr->len == 1) {
        treeDelete(tree, ptr);
        ptr = freeNode(ptr);
    } else if (ptr) {
        free(ptr->data[0]);
        ptr->len--;
        temp = ptr->data;
        ptr->data = calloc(ptr->len, sizeof(char *));
        for (int i = 0; i < ptr->len; i++)
            ptr->data[i] = temp[i + 1];
        free(temp);
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

void Print(Node *ptr, long n) {
    long i;
    if (ptr) {
        Print(ptr->right, n+2);
        for (i = 0; i < n; i++)
            printf(" ");
        printf("%s\n", ptr->key);
        Print(ptr->left, n+2);
    }
}

void InorderWalk(Tree *tree, char *key) {
    Node *ptr = treeSearch(tree->root, key);
    Print(ptr, 0);
    //treeInorderWalk(ptr);
}

void FreeTree(Tree *tree) {
    while (tree->root) {
        Delete(tree, tree->root->key);
    }
}