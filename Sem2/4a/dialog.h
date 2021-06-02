#ifndef DIALOG_H
#define DIALOG_H

#include "tree.h"

int dialog(const char *msgs[], int n);
char *get_str();
void printData(char **array, int len);
//void readTree(Tree *tree, FILE *fd, char **key, char **str, int len, int *pos);

#endif
