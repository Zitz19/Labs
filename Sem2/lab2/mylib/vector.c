#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

char **makeVector(char **vect, int size) {
    vect = (char **) calloc(size, sizeof(char *));
    for (int i = 0; i < size; i++) {
        vect[i] = (char *) calloc(2 * size, sizeof(char));
    }
    return vect;
}

char **freeVector(char **vect, int size) {
    for (int i = 0; i <size; i++) {
        free(vect[i]);
    }
    free(vect);
    return vect;
}

char **addString(char **vect, int x, char *str, int size) {
    memcpy(vect[x], str, 2 * size * sizeof(char));
    return vect;
}

char *getString(char *str, char **vect, int x, int size) {
    memcpy(str, vect[x], 2 * size * sizeof(char));
    memset(vect[x], 0, 2 * size * sizeof(char));
    return str;
}