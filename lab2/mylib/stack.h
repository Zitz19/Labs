#ifndef STACK_H
#define STACK_H
#ifdef list
#include "list.h"
#endif

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

Stack *makeStack(int m);
void freeStack(Stack *stack);
void push(Stack *stack, char *str);
char *pop(Stack *stack);

#endif
