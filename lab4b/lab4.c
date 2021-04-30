#include <stdio.h>
#include <stdlib.h>
#include "dialog.h"
#include "tree.h"
#include "node.h"

const char *MSGS[] = {"0. Quit", "1. Add new node", "2. Print the table", "3. Search with key", "4. Max element",
                      "5. Min element", "6. Remove an element", "7. Timing", "8. Read from file"};

const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main() {
    int c = 0;
    int index;
    Node *ptr;
    int key;
    char *str;
    FILE  *fd;
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
                Insert(tree, key, NULL);
                break;
            case 2:
                Print(tree->root, 0);
                break;
            case 3:
                scanf("%d", &key);
                while (scanf("%*c"));
                ptr = BtreeSearch(tree->root, key, &index);
                if (ptr) {
                    printf("KEY %d: %f %s\n", ptr->key[index], ptr->data[index]->f, ptr->data[index]->str);
                }
                break;
            case 4:
                ptr = BtreeSearchMax(tree->root);
                for (int i = 0; i < ptr->n; i++)
                    printf("I = %d (%d) ", i, ptr->key[i]);
                printf("\n");
                break;
            case 5:
                ptr = BtreeSearchMin(tree->root);
                for (int i = 0; i < ptr->n; i++)
                    printf("I = %d (%d) ", i, ptr->key[i]);
                printf("\n");
                break;
            case 6:
                scanf("%d", &key);
                while (scanf("%*c"));
                tree->root = Delete(tree->root, key);
                break;
            case 7:
                Timing(tree);
                break;
            case 8:
                puts("Please, enter a name of file");
                str = get_str();
                ReadFromFile(tree, str);
                free(str);
                break;
        }
    } while (c != 0);
    if (tree->root)
        FreeTree(tree);
    free(tree);
    return 0;
}