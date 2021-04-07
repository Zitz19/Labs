#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

const char *MSGS[] = {"0. Quit", "1. Make the table", "2. Free the table", "3. Add the element",
                      "4. Search with parent"};
const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int dialog(const char *msgs[], int n) {
    char *error = "";
    int choice;
    do {
        puts(error);
        error = "You're wrong. Try again!";
        for (int i = 0; i < n; ++i) {
            puts(msgs[i]);
        }
        printf("Make your choice: ");
        choice = getchar() - '0';
        while (getchar() != '\n') {}
    } while (choice < 0 || choice >= n);
    return choice;
}

char *get_str() {
    char buf[81] = {0};
    char *res = NULL;
    int len = 0;
    int n = 0;
    do {
        n = scanf("%80[^\n]", buf);
        if (n < 0) {
            if (!res) {
                return NULL;
            }
        } else if (n > 0) {
            int chunk_len = strlen(buf);
            int str_len = len + chunk_len;
            res = realloc(res, str_len + 1);
            memcpy(res + len, buf, chunk_len);
            len = str_len;
        } else {
            scanf("%*c");
        }
    } while (n > 0);

    if (len > 0) {
        res[len] = '\0';
    } else {
        res = calloc(1, sizeof(char));
    }

    return res;
}

int main() {
    int c = 0;
    Table *table = NULL;
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch(c) {
            case 0:
                break;
            case 1:
                table = makeTable();
                break;
            case 2:
                freeTable(table);
                break;
            case 3:
                puts("Please, enter the parent, first and second key:");
                int parent, key1, key2;
                scanf("%d%d%d", &parent, &key1, &key2);
                while (scanf("%*c"));
                puts("Please, enter a string:");
                char *str = get_str();
                addItem(table, parent, key1, key2, str);
                break;
            case 4:
                puts("Please, enter a parent key:");
                int x = 0;
                scanf("%d", &x);
                while (scanf("%*c"));
                ks1_parSearch(table, x);
        }
    } while (c != 0);
    return 0;
}