// Библиотека диалоговых функций

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dialog.h"

// Функция диалогового меню
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
// Функция для получения строки любой длины
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

// Функция для преобразования ключа из английских букв в число
int str_to_int(char *str) {
    int len = strlen(str);
    int res = 0;
    for (int i = 0; i < len; i++) {
        res = res + (str[i] - 'a') * pow(26, len - i - 1);
    }
    return res;
}

char *int_to_str(int x) {
    char *res = calloc(4, sizeof(char));
    for (int i = 2; i >= 0; i--) {
        res[i] = x % 26 + 'a';
        x = x / 26;
    }
    res[3] = '\0';
    return res;
}

void printTable(Table *table) {
    char *str_key1, *str_par;
    for (int i = 0; i < table->ksize1; i++) {
        if (table->kSpace1[i].status == 1) {
            str_par = int_to_str(table->kSpace1[i].par);
            str_key1 = int_to_str(table->kSpace1[i].key);
            printf("KEYSP1: %s %s   ", str_par, str_key1);
            free(str_par);
            free(str_key1);
            Unit *temp = table->kSpace2[hash(table->kSpace1[i].data->key2)].head;
            while ((temp->data->key2 != table->kSpace1[i].data->key2) || (temp->data->key1 != table->kSpace1[i].key)) {
                temp = temp->next;
            }
            printf("KEYSP2: %d %d   ", temp->data->key2, temp->release);
            printf("%s\n", temp->data->str);
        }
    }
}

void printArray1(keySpace1 **array, int len) {
    char *str_par, *str_key1;
    for (int i = 0; i < len; i++) {
        str_par = int_to_str(array[i]->par);
        str_key1 = int_to_str(array[i]->key);
        printf("KEYSP1: %s %s %s\n", str_par, str_key1, array[i]->data->str);
        free(str_par);
        free(str_key1);
    }
}

void printArray2(Unit **array, int len) {
    for (int i = 0; i < len; i++) {
        printf("KEYSP2: %d %d %s\n", array[i]->data->key2, array[i]->release, array[i]->data->str);
    }
}