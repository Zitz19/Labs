#ifndef GRAPH_H
#define GRAPH_H

#include "list.h"

typedef struct Node {
    int id; //Имя вершины
    int x; //Координата x
    int y; //Координата y
    int color; //Цвет узла
    int p; //Предшественник(родитель)
    int d; //Время открытия
    int f; //Время закрытия
    Item *head; //Указатель на начало списка смежности
} Node;

Node *newGraph(int size);
Node *updateGraph(Node *Adj, int id, int *size);
Node *newNode(Node *Adj, int id, int x, int y);
void printDFS_Path(Node *Adj, int id, int tmp);
void DFS(Node *Adj, int size, int id, int key);
int DFS_Visit(Node *Adj, int id, int key, int *time);

#endif
