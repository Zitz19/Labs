#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Node *newGraph(int size) {
    return calloc(size, sizeof(Node));
}

Node *updateGraph(Node *Adj, int id, int *size) {
    int old_size = *size;
    if (id >= *size)
        (*size) = 2 * id;
    Node *new_Adj = calloc(*size, sizeof(Node));
    memcpy(new_Adj, Adj, old_size * sizeof(Node));
    free(Adj);
    return new_Adj;
}

Node *newNode(Node *Adj, int id, int x, int y) {
    Adj[id].id = id;
    Adj[id].x = x;
    Adj[id].y = y;
    return Adj;
}

void printDFS_Path(Node *Adj, int id, int tmp) {
    if (tmp != id) {
        printf("(%d [%d/%d]) <- ", Adj[tmp].id, Adj[tmp].d, Adj[tmp].f);
        printDFS_Path(Adj, id, Adj[tmp].p);
    } else {
        printf("(%d [%d/%d])", Adj[tmp].id, Adj[tmp].d, Adj[tmp].f);
        return;
    }
}

void DFS(Node *Adj, int size, int id, int key) {
    int time = 0;
    for (int i = 1; i < size; i++) {
        Adj[i].color = 0;
        Adj[i].p = 0;
    }
    if (DFS_Visit(Adj, id, key, &time) == 1)
        printDFS_Path(Adj, id, key);
    else
        puts("Way wasn't found.");
}

int DFS_Visit(Node *Adj, int id, int key, int *time) {
    (*time)++;
    Adj[id].d = *time;
    Adj[id].color = 1;
    if (id == key)
        return 1;
    Item *tmp = Adj[id].head;
    while (tmp) {
        if (Adj[tmp->id].color == 0) {
            Adj[tmp->id].p = id;
            if (DFS_Visit(Adj, tmp->id, key, time))
                return 1;
        }
        tmp = tmp->next;
    }
    Adj[id].color = 2;
    (*time)++;
    Adj[id].f = *time;
    return 0;
}

void initSingleSource(Node *Adj, int s, int size) {
    for (int i = 1; i < size; i++) {
        if (Adj[i].id) {
            Adj[i].d = 32000; // 32000 = infinity
            Adj[i].color = 0;
        }
    }
    Adj[s].d = 0;
}
void Relax(Node *Adj, int x, int y) {
    if (Adj[y].d > Adj[x].d + 1) {
        Adj[y].d = Adj[x].d + 1;
        Adj[y].p = x;
    }
}
/*
void Dijkstra(Node *Adj, int size, int s, int key) {
    initSingleSource(Adj, s, size);
    for (Item *tmp = Adj[s].head; tmp; tmp = tmp->next) {
        int v = 0;
        for ()
    }
}*/