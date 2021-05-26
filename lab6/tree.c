#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "dialog.h"

Node *newNode(int key) {
    Node *ptr = calloc(1, sizeof(Node));
    ptr->key = key;
    ptr->h = 1;
    return ptr;
}

int Height(Node *ptr) {
    return ptr ? ptr->h : 0;
}

int bFactor(Node *ptr) {
    return Height(ptr->right) - Height(ptr->left);
}

void fixHeight(Node *ptr) {
    int hl = Height(ptr->left);
    int hr = Height(ptr->right);
    ptr->h = (hl > hr ? hl : hr) + 1;
}

Node *rightRotate(Node *p) {
    Node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}

Node *leftRotate(Node *q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

Node *Balance(Node *ptr) {
    fixHeight(ptr);
    if (bFactor(ptr) == 2) {
        if (bFactor(ptr->right) < 0)
            ptr->right = rightRotate(ptr->right);
        return leftRotate(ptr);
    }
    if (bFactor(ptr) == -2) {
        if (bFactor(ptr->left) > 0)
            ptr->left = leftRotate(ptr->left);
        return rightRotate(ptr);
    }
    return ptr;
}

Node *Insert(Node *ptr, int key) {
    if (!ptr)
        return newNode(key);
    if (key < ptr->key)
        ptr->left = Insert(ptr->left, key);
    else
        ptr->right = Insert(ptr->right, key);
    return Balance(ptr);
}

Node *minSearch(Node *ptr) {
    return ptr->left ? minSearch(ptr->left) : ptr;
}

Node *minRemove(Node *ptr) {
    if (ptr->left == NULL)
        return ptr->right;
    ptr->left = minRemove(ptr->left);
    return Balance(ptr);
}

Node *Remove(Node *p, int key) {
    if (!p)
        return NULL;
    if (key < p->key)
        p->left = Remove(p->left, key);
    else if (key > p->key)
        p->right = Remove(p->right, key);
    else {
        Node* q = p->left;
        Node* r = p->right;
        free(p);
        if (!r)
            return q;
        Node* min = minSearch(r);
        min->right = minRemove(r);
        min->left = q;
        return Balance(min);
    }
    return Balance(p);
}

void FreeTree(Node *root) {
    while (root)
        root = Remove(root, root->key);
}

Node *treeSearch(Node *ptr, int key) {
    while ((ptr != NULL) && (key != ptr->key)) {
        if (key < ptr->key) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }
    return ptr;
}

void Print(Node *ptr, long n) {
    long i;
    if (ptr) {
        Print(ptr->right, n+2);
        for (i = 0; i < n; i++)
            printf(" ");
        printf("%d\n", ptr->key);
        Print(ptr->left, n+2);
    }
}