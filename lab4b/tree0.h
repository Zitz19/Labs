#ifndef TREE_H
#define TREE_H

typedef struct Data {
    float f;
    char *str;
} Data;

typedef struct Node {
    int n;
    int key[2];
    Data *data[2];
    struct Node *left;
    struct Node *middle;
    struct Node *right;
    struct Node *p;
} Node;

typedef struct Tree {
    Node *root;
    int h;
} Tree;

Node *newNode(float x, char *str);
void sort(Node *ptr);
unsigned int isLeaf(Node *ptr);
unsigned int findKey(Node *ptr, int key);
void nodeInsert(Node *ptr, int key, float f, char *str);
Tree *BtreeCreate(float f, char *str);
Node *BtreeSearch(Node *ptr, int key);

#endif
