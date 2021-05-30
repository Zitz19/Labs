#ifndef TREE_H
#define TREE_H

typedef struct Data {
    float f;
    char *str;
} Data;

typedef struct Node {
    int leaf;
    int n;
    int key[3];
    Data *data[3];
    struct Node *ch[4];
    struct Node *p;
} Node;

typedef struct Tree {
    Node *root;
    int h;
} Tree;

Node *BtreeSearch(Node *ptr, int key, int *index);
Tree *BtreeCreate(Tree *tree);
void BtreeSplitChild(Node *par, int i);
void BtreeInsert(Tree *tree, Node *ptr, int key, Data *data);
void BtreeInsertNonfull_extra(Node *ptr, int key);
void BtreeInsertNonfull(Node *ptr, int key, Data *datag);
Node *BtreeSearchMax(Node *ptr);
Node *BtreeSearchMin(Node *ptr);

#endif