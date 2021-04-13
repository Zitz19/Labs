#ifndef DIALOG_H
#define DIALOG_H

#ifndef TABLE_H
#include "table.h"
#endif

int dialog(const char *msgs[], int n);
char *get_str();
int str_to_int(char *str);
char *int_to_str(int x);
void printTable(Table *table);
void printArray1(keySpace1 **array, int len);
void printArray2(Unit **array, int len);

#endif