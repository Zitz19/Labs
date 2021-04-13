#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "dialog.h"

const char *MSGS[] = {"0. Quit", "1. Add the element", "2. Print the table", "3. Search with parent",
                      "4. Delete element with key1", "5. Delete element with key2 and release",
                      "6. Search with key2 or key2 and release"};

const int MSGS_SIZE = sizeof(MSGS) / sizeof(MSGS[0]);

int main() {
    int c = 0;
    Table *table = makeTable();
    do {
        c = dialog(MSGS, MSGS_SIZE);
        switch(c) {
            case 0:
                break;
            case 1:
                puts("Please, enter the parent, first and second key:");
                char str_parent[4];
                char str_key1[4];
                int key2;
                scanf("%s %s %d", str_parent, str_key1, &key2);
                /* scanf("%s", str_parent);
                scanf("%s", str_key1);
                scanf("%d", &key2); */
                while (scanf("%*c"));
                int parent = str_to_int(str_parent);
                int key1 = str_to_int(str_key1);
                puts("Please, enter a string:");
                char *str = get_str();
                if (addItem(table, parent, key1, key2, str) == 0) {
                    puts("ERROR");
                }
                break;
            case 2:
                printTable(table);
                break;
            case 3:
                puts("Please, enter parent key:");
                int par;
                char *buf;
                int array_len = 0;
                buf = get_str();
                par = str_to_int(buf);
                free(buf);
                keySpace1 **array = parSearch(table, par, &array_len);
                printArray1(array, array_len);
                free(array);
                break;
            case 4:
                puts("Please, enter key1:");
                buf = get_str();
                key1 = str_to_int(buf);
                free(buf);
                if (del_KS1(table, key1) == 0) {
                    puts("ERROR");
                }
                break;
            case 5:
                puts("Please, enter key2 and release:");
                int release;
                scanf("%d %d", &key2, &release);
                while (scanf("%*c"));
                del_KS2(table, key2, release);
                break;
            case 6:
                puts("Please, enter key2 and 0 or key2 and release");
                Unit **array2 = NULL;
                scanf("%d %d", &key2, &release);
                while (scanf("%*c"));
                array2 = key2_Search(table, key2, release, &array_len);
                printArray2(array2, array_len);
                free(array2);
                break;
        }
    } while (c != 0);
    freeTable(table);
    return 0;
}