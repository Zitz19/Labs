#include <stdio.h>
#include <stdlib.h>
#include "dialog.h"
#include "tree.h"

const char *MSGS[] = {"0. Quit", "1. Insert", "2. Remove", "3. Search", "4. Print"};

const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main() {
    int c = 0;
    Node *tree = NULL;
    int key;
    Node *ptr;
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch(c) {
            case 0:
                break;
            case 1:
                scanf("%d%*c", &key);
                tree = !tree ? newNode(key) : Insert(tree, key);
                break;
            case 2:
                scanf("%d%*c", &key);
                tree = Remove(tree, key);
                break;
            case 3:
                scanf("%d%*c", &key);
                ptr = treeSearch(tree, key);
                if (ptr)
                    printf("NODE KEY IS %d\n", ptr->key);
                else
                    puts("NOT DETECTED");
                break;
            case 4:
                Print(tree, 0);
                break;
        }
    } while (c != 0);
    FreeTree(tree);
    return 0;
}