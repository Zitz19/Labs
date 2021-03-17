#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **makeVector(int size) {
	char **vect = NULL;
	vect = (char **) calloc(size, sizeof(char *));
	for (int i = 0; i < size; i++) {
		vect[i] = (char *) calloc(2 * size, sizeof(char));
	}
	return vect;
}

void freeVector(char **vect, int size) {
	for (int i = 0; i < size; i++) {
		free(vect[i]);
	}
	free(vect);
}

void addString(char **vect, int size, int x, char *str) {
	memcpy(vect[x], str, 2 * size * sizeof(char));
}

void freeString(char **vect, int x) {
	free(vect[x]);
}
