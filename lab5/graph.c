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

int DFS(Node *Adj, int size, int id, int key) {
    int time = 0;
    for (int i = 1; i < size; i++) {
        Adj[i].color = 0;
        Adj[i].p = 0;
    }
    if (DFS_Visit(Adj, id, key, &time) == 1)
        return 1;
    else
        return 0;
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

int DFS_modified(Node *Adj, int size, int id) {
    int time = 0;
    for (int i = 1; i < size; i++) {
        Adj[i].color = 0;
        Adj[i].p = 0;
    }
    for (int i = 1; i < size; i++) {
        if (Adj[i].id && Adj[i].color == 0) {
            DFS_Visit_modified(Adj, id, &time);
        }
    }
}

int DFS_Visit_modified(Node *Adj, int id, int *time) {
    (*time)++;
    Adj[id].d = *time;
    Adj[id].color = 1;
    Item *tmp = Adj[id].head;
    while (tmp) {
        if (Adj[tmp->id].color == 0) {
            Adj[tmp->id].p = id;
            DFS_Visit_modified(Adj, tmp->id, time);
        }
        tmp = tmp->next;
    }
    Adj[id].color = 2;
    (*time)++;
    Adj[id].f = *time;
}

void initSingleSource(Node *Adj, int s, int size) {
    for (int i = 0; i < size; i++) {
        Adj[i].d = 32000; // 32000 = infinity
        Adj[i].color = 0;
    }
    Adj[s].d = 0;
}
void Relax(Node *Adj, int x, int y) {
    if (Adj[y].d > Adj[x].d + 1) {
        Adj[y].d = Adj[x].d + 1;
        Adj[y].p = x;
    }
}

int ExtractMin(Node *Adj, int size) {
    int min = 0;
    for (int i = 0; i < size; i++) {
        if (Adj[i].color == 0 && Adj[i].d < Adj[min].d)
            min = i;
    }
    Adj[min].color = 1;
    return min;
}

void Dijkstra(Node *Adj, int size, int s, int key) {
    int x = 1;
    initSingleSource(Adj, s, size);
    while (x) {
        x = ExtractMin(Adj, size);
        for (Item *tmp = Adj[x].head; tmp != NULL; tmp = tmp->next)
            Relax(Adj, x, tmp->id);
    }
    printDFS_Path(Adj, s, key);
}

Item *findEdge(Node *Adj, int size, int u, int v) {
    if (Adj[u].id) {
        Item *tmp = Adj[u].head;
        while (tmp) {
            if (tmp->id == v)
                return tmp;
            tmp = tmp->next;
        }
        return NULL;
    }
    return NULL;
}

int minCapacity(Node *Adj, int size, int x) {
    int min = 32000;
    while (Adj[x].p) {
        Item *edge = findEdge(Adj, size, Adj[x].p, x);
        if (edge->c < min)
            min = edge->c;
        x = Adj[x].p;
    }
    return min;
}

Node *residualNetModify(Node *Adj, Node *ResNet, int size) {
    for (int i = 1; i < size; i++) {
        if (ResNet[i].id) {
            freeList(ResNet[i].head);
            ResNet[i].head = NULL;
        }
    }
    for (int i = 1; i < size; i++) {
        if (Adj[i].id) {
            for (Item *tmp = Adj[i].head; tmp != NULL; tmp = tmp->next) {
                ResNet[i].head = newItem_modified(ResNet[i].head, tmp->id, tmp->c - tmp->f);
                ResNet[tmp->id].head = newItem_modified(ResNet[tmp->id].head, i, tmp->f);
            }
        }
    }
    for (int i = 1; i < size; i++) {
        if (ResNet[i].id) {
            Item *tmp = ResNet[i].head;
            while (tmp) {
                if (tmp->c <= 0) {
                    Item *temp = tmp;
                    tmp = tmp->next;
                    ResNet[i].head = removeItem(ResNet[i].head, temp->id);
                } else
                    tmp = tmp->next;
            }
        }
    }
    return ResNet;
}

Node *Ford_Fulkerson(Node *Adj, int size, int s, int t) {
    for (int i = 1; i < size; i++) {
        if (Adj[i].id) {
            for (Item *tmp = Adj[i].head; tmp != NULL; tmp = tmp->next)
                tmp->f = 0;
        }
    }
    Node *ResNet = newGraph(size);
    memcpy(ResNet, Adj, size * sizeof(Node));
    for (int i = 1; i < size; i++) {
        if (Adj[i].id) {
            ResNet[i].head = NULL;
            for (Item *tmp = Adj[i].head; tmp != NULL; tmp = tmp->next)
                ResNet[i].head = newItem_modified(ResNet[i].head, tmp->id, tmp->c);
        }
    }
    while (DFS(ResNet, size, s, t)) {
        int Cmin = minCapacity(ResNet, size, t);
        printf("Cmin is %d\n", Cmin);
        int y = ResNet[t].id;
        int x = ResNet[t].p;
        while (y != s) {
            Item *edge = findEdge(Adj, size, x, y);
            if (edge)
                edge->f = edge->f + Cmin;
            Item *rev_edge = findEdge(Adj, size, y, x);
            if (rev_edge) {
                rev_edge->f = rev_edge->f - Cmin;
                if (rev_edge->f < 0)
                    rev_edge->f = 0;
            }
            y = x;
            x = ResNet[x].p;
        }
        ResNet = residualNetModify(Adj, ResNet, size);
    }
    for (int i = 1; i < size; i++) {
        if (ResNet[i].id)
            freeList(ResNet[i].head);
    }
    free(ResNet);
    return Adj;
}