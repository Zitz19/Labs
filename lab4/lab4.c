#include <stdio.h>
#include <stdlib.h>
#include "dialog.h"
#include "node.h"

const char *MSGS[] = {"0. Quit", "1. Add new node", "2. Delete node with key", "3. Search with key",
                      "4. Print table", "5. Find successor"/*, "6. Read tree from file"*/};

const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main() {
    int c = 0;
    char *str, *key;
    FILE *fd;
    int len;
    int pos;
    Tree *tree = calloc(1, sizeof(Tree));
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch(c) {
            case 0:
                break;
            case 1:
                puts("Please, enter a key:");
                key = get_str();
                puts("Please, enter a string:");
                str = get_str();
                Insert(tree, key, str);
                break;
            case 2:
                puts("Please, enter a key:");
                key = get_str();
                Delete(tree, key);
                free(key);
                break;
            case 3:
                puts("Please, enter a key:");
                key = get_str();
                Search(tree, key);
                free(key);
                break;
            case 4:
                puts("Please, enter a root key:");
                key = get_str();
                InorderWalk(tree, key);
                free(key);
                break;
            case 5:
                puts("Please, enter a key:");
                key = get_str();
                Successor(tree, key);
                free(key);
                break;
            /*case 6:
                puts("Please, enter file name:");
                str = get_str();
                fd = fopen(str, "r");
                free(str);
                len = ftell(fd);
                pos = 0;
                do {
                    readTree(tree, fd, &key, &str, len, &pos);
                } while
                fclose(fd);
                break;*/
        }
    } while (c != 0);
    FreeTree(tree);
    free(tree);
    return 0;
}