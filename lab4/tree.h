#ifndef TREE_H
#define TREE_H

typedef struct Node {
    char *key;
    struct Node *p;
    int len;
    char **data;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct Tree {
    Node *root;
    int size;
} Tree;

void treeInorderWalk(Node *ptr);
Node *treeSearch(Node *prt, char *key);
Node *treeMaximum(Node *ptr);
Node *treeSuccessor(Node *prt);
Node *treePredecessor(Node *ptr);
void treeInsert(Tree *tree, Node *ptr);
void transplant(Tree *tree, Node *x, Node *y);
void treeDelete(Tree *tree, Node *ptr);

#endif