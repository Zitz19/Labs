#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "node.h"

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

void printData(char **array, int len) {
    int i = 0;
    while (i < len) {
        if (array[i]) {
            puts(array[i]);
            i++;
        }
    }
}
/*
int readTree(Tree *tree, FILE *fd) {
    char *key = calloc(10, sizeof(char));
    char *str = calloc(100, sizeof(char));
    int i;
    do {
        if (feof(fd))
            return -1;
        i = 0;
        do {
            fread(key + i, sizeof(char), 1, fd);
            i++;
        } while((!feof(fd)) && (key[i - 1] != ' '));
        key[i - 1] = '\0';
        i = 0;
        do {
            fread(str + i, sizeof(char), 1, fd);
            i++;
        } while((!feof(fd)) && (str[i - 1] != '\n'));
        str[i - 1] = '\0';
        Insert(tree, key, str);
    } while(!feof(fd));
    return 1;
} */
/*
void readTree(Tree *tree, FILE *fd, char **key, char **str, int len, int *pos) {
    int i;
    i = 0;
    while(*pos < len) {
        fread(*key + i, sizeof(char), 1, fd);
        (*pos)++;
        i++;
    }
}*/