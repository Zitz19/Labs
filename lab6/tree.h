#ifndef TREE_H
#define TREE_H

typedef struct Node {
    int key;
    int h;
    struct Node *left;
    struct Node *right;
} Node;

Node *newNode(int key);
int Height(Node *ptr);
int bFactor(Node *ptr);
void fixHeight(Node *ptr);
Node *rightRotate(Node *p);
Node *leftRotate(Node *q);
Node *Balance(Node *ptr);
Node *Insert(Node *ptr, int key);
Node *minSearch(Node *ptr);
Node *minRemove(Node *ptr);
Node *Remove(Node *p, int key);
void FreeTree(Node *root);
Node *treeSearch(Node *ptr, int key);
void Print(Node *ptr, long n);

#endif