#ifndef VECTOR_H
#define VECTOR_H

char **makeVector(char **vect, int size);
char **freeVector(char **vect, int size);
char **addString(char **vect, int x, char *str, int size);
char *getString(char *str, char **vect, int x, int size);

#endif