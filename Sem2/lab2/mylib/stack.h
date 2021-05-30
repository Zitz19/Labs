#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct Stack {
    int size;
#ifdef vector
    char **data;
    int top;
#endif

#ifdef list
    Item *top;
#endif
} Stack;

Stack *makeStack(int stack_size);
void freeStack(Stack *stack);
void push(Stack *stack, char *str);
char *pop(Stack *stack);