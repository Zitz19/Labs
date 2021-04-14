#ifndef NODE_H
#define NODE_H

#include "tree.h"

Node *newNode(char *key, char *str);
Node *freeNode(Node *ptr);
void Insert(Tree *tree, char *key, char *str);
void Delete(Tree *tree, char *key);
void Search(Tree *tree, char *key);
void Successor(Tree *tree, char *key);

#endif