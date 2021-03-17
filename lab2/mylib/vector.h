#ifndef VECTOR_H
#define VECTOR_H

char **makeVector(int size);
void freeVector(char **vect, int size);
void addString(char **vect, int size, int x, char *str);
void freeString(char **vect, int x);

#endif
