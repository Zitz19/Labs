#include <stdio.h>
#include <string.h>

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
        scanf("%d%*c", &choice);
    } while (choice < 0 || choice >= n);
    return choice;
}