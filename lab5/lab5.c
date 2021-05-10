#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "graph.h"
#include "list.h"
#include "dialog.h"

const char *MSGS[] = {"0. Quit", "1. Add a node", "2. Add an edge", "3. Remove a node", "4. Remove an edge",
                      "5. Test print", "6. DFS", "7. Draw a graph", "8. Write to file", "9. Read from file",
                      "10. Graph generation"};

const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main() {
    int c = 0;
    int id, x, y;
    int n, k;
    int size = 50;
    Item *tmp;
    FILE *fd = NULL;
    int m;
    Node *Adj = newGraph(size);
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch (c) {
            case 0:
                break;
            case 1:
                puts("Enter an ID(natural) X Y");
                if (scanf("%d%d%d", &id, &x, &y) != 3) {
                    puts("ERROR");
                    scanf("2%*c");
                    break;
                } else {
                    scanf("%*c");
                    Adj = updateGraph(Adj, id, &size);
                    Adj = newNode(Adj, id, x, y);
                }
                break;
            case 2:
                puts("Enter a node ID and number of adj. nodes");
                scanf("%d%d", &id, &n);
                if (Adj[id].id == 0) {
                    puts("ERROR");
                    scanf("%*c");
                    break;
                }
                puts("Enter an adjacent nodes ID");
                for (int i = 0; i < n; i++) {
                    scanf("%d", &k);
                    Adj[id].head = newItem(Adj[id].head, k);
                }
                scanf("%*c");
                break;
            case 3:
                puts("Enter a node ID");
                scanf("%d", &id);
                scanf("%*c");
                for (int i = 1; i < size; i++)
                    Adj[i].head = removeItem(Adj[i].head, id);
                freeList(Adj[id].head);
                Adj[id].head = NULL;
                Adj[id].id = 0;
                break;
            case 4:
                puts("Enter an ID_1 and ID_2");
                scanf("%d%d", &id, &k);
                scanf("%*c");
                Adj[id].head = removeItem(Adj[id].head, k);
                break;
            case 5:
                for (int i = 1; i < size; i++) {
                    if (Adj[i].id) {
                        printf("NODE #%d {%d; %d}: ", Adj[i].id, Adj[i].x, Adj[i].y);
                        tmp = Adj[i].head;
                        while (tmp) {
                            printf("%d ", tmp->id);
                            tmp = tmp->next;
                        }
                        printf("\n");
                    }
                }
                break;
            case 6:
                puts("Enter a source node ID and a key");
                scanf("%d%d", &id, &k);
                scanf("%*c");
                DFS(Adj, size, id, k);
                break;
            case 7:
                fd = fopen("scheme.gv", "w");
                fprintf(fd, "digraph scheme {\n");
                for (int i = 1; i < size; i++) {
                    if (Adj[i].id) {
                        tmp = Adj[i].head;
                        while (tmp) {
                            fprintf(fd, "\"%d(%d; %d)\"->\"%d(%d; %d)\";\n", Adj[i].id, Adj[i].x, Adj[i].y, Adj[tmp->id].id, Adj[tmp->id].x, Adj[tmp->id].y);
                            tmp = tmp->next;
                        }
                    }
                }
                fprintf(fd, "}");
                fclose(fd);
                break;
            case 8:
                fd = fopen("graph.txt", "w");
                m = 0;
                for (int i = 1; i < size; i++) {
                    if (Adj[i].id)
                        m++;
                }
                fprintf(fd, "%d\n", m);
                for (int i = 1; i < size; i++) {
                    if (Adj[i].id)
                        fprintf(fd, "%d %d %d\n", Adj[i].id, Adj[i].x, Adj[i].y);
                }
                for (int i = 1; i < size; i++) {
                    if (Adj[i].id) {
                        m = 0;
                        tmp = Adj[i].head;
                        while (tmp) {
                            m++;
                            tmp = tmp->next;
                        }
                        fprintf(fd, "%d %d\n", Adj[i].id, m);
                        tmp = Adj[i].head;
                        while (tmp) {
                            fprintf(fd, "%d ", tmp->id);
                            tmp = tmp->next;
                        }
                        fprintf(fd, "\n");
                    }
                }
                fclose(fd);
                break;
            case 9:
                fd = fopen("graph.txt", "r");
                fscanf(fd, "%d", &m);
                for (int i = 0; i < m; i++) {
                    fscanf(fd, "%d%d%d%*c", &id, &x, &y);
                    Adj = updateGraph(Adj, id, &size);
                    Adj = newNode(Adj, id, x, y);
                }
                for (int i = 0; i < m; i++) {
                    fscanf(fd, "%d%d", &id, &n);
                    for (int i = 0; i < n; i++) {
                        fscanf(fd, "%d", &k);
                        Adj[id].head = newItem(Adj[id].head, k);
                    }
                    fscanf(fd, "%*c");
                }
                fclose(fd);
                break;
            case 10:
                puts("Enter a size of graph:");
                scanf("%d%*c", &m);
                srand(time(NULL));
                for (int i = 1; i <= m; i++) {
                    id = i;
                    Adj = updateGraph(Adj, id, &size);
                    Adj = newNode(Adj, id, rand() % 100, rand() % 100);
                }
                for (int i = 1; i <= m; i++) {
                    for (int j = 0; j < rand() % m; j++)
                        Adj[i].head = newItem(Adj[i].head, rand() % m + 1);
                }
                break;
        }
    } while (c);
    for (int i = 1; i < size; i++) {
        if (Adj[i].id)
            freeList(Adj[i].head);
    }
    free(Adj);
    return 0;
}