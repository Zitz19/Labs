#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

#ifdef vector
#include "vector.h"
#endif

#ifdef list
#include "list.h"
#endif

Stack *makeStack(int m) {
	Stack *stack = NULL;
	stack = (Stack *) calloc(1, sizeof(Stack));
	stack->size = m;
	#ifdef vector
	stack->data = makeVector(stack->size);
	stack->top = 0;
	#endif

	#ifdef list
	stack->top = makeList(stack->size);
	#endif
	return stack;
}

void freeStack(Stack *stack) {
	#ifdef vector
	if (stack->data) {
		freeVector(stack->data, stack->size);
	}
	#endif
	
	#ifdef list
	if (stack->top) {
		freeList(stack->top);
	}
	#endif
	free(stack);
}

void push(Stack *stack, char *str) {
	#ifdef vector
	addString(stack->data, stack->size, stack->top, str);
	stack->top++;
	#endif

	#ifdef list
	addItem(stack->top, stack->size, str);
	#endif
}

char *pop(Stack *stack) {
	char *str = NULL;
	str = (char *) calloc(2 * stack->size, sizeof(char));
	#ifdef vector
	stack->top--;
	memcpy(str, stack->data[stack->top], 2 * stack->size * sizeof(char));
	freeString(stack->data, stack->top);
	#endif

	#ifdef list
	memcpy(str, stack->top->data, 2 * stack->size * sizeof(char));
	freeItem(stack->top);
	#endif
	return str;
}
