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
int DFS(Node *Adj, int size, int id, int key);
int DFS_Visit(Node *Adj, int id, int key, int *time);
int DFS_modified(Node *Adj, int size, int id);
int DFS_Visit_modified(Node *Adj, int id, int *time);
void initSingleSource(Node *Adj, int s, int size);
void Relax(Node *Adj, int x, int y);
int ExtractMin(Node *Adj, int size);
void Dijkstra(Node *Adj, int size, int s, int key);
Item *findEdge(Node *Adj, int size, int u, int v);
int minCapacity(Node *Adj, int size, int x);
Node *residualNetModify(Node *Adj, Node *ResNet, int size);
Node *Ford_Fulkerson(Node *Adj, int size, int s, int t);
int ** Floyd(Node *Adj, int size);

#endif
