#ifndef NODE_H
#define NODE_H

void Print(Node *ptr, long n);
void Insert(Tree *tree, int key, Data* data);
Node *newNode(float f, char *str);
void swap(int *x, int *y);
void removeFromNode(Node *ptr, int key);
Node *Redistribute(Node *ptr);
Node *Merge(Node *ptr);
Node *Fix(Node *ptr);
Node *Delete(Node *r, int key);
void Timing(Tree *tree);
void FreeTree(Tree *tree);
void ReadFromFile(Tree *tree, char *name);

#endif