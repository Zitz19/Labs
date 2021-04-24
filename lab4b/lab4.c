#include <stdio.h>
#include <stdlib.h>
#include "dialog.h"
#include "tree.h"
#include "node.h"

const char *MSGS[] = {"0. Quit", "1. Add new node", "2. Print the table", "3. Search with key"};

const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main() {
    int c = 0;
    int index;
    Node *ptr;
    int key;
    int j;
    Tree *tree = calloc(1, sizeof(Tree));
    tree = BtreeCreate(tree);
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch (c) {
            case 0:
                break;
            case 1:
                scanf("%d", &key);
                while (scanf("%*c"));
                ptr = tree->root;
                while (!ptr->leaf) {
                    j = 0;
                    while (key < ptr->key[j])
                        j++;
                    ptr = ptr->ch[j + 1];
                }
                BtreeInsert(tree, ptr, key);
                break;
            case 2:
                Print(tree->root, 0);
                break;
            case 3:
                scanf("%d", &key);
                while (scanf("%*c"));
                ptr = BtreeSearch(tree->root, key, &index);
                for (int i = 0; i < ptr->n; i++)
                    printf("%d ", ptr->key[i]);
                printf("\n");
        }
    } while (c != 0);
    return 0;
}