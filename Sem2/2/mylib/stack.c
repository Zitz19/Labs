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

Stack *makeStack(int stack_size) {
    Stack *stack = (Stack *) calloc(1, sizeof(Stack));
    stack->size = stack_size;
#ifdef vector
    stack->data = makeVector(stack->data, stack->size);
    stack->top = 0;
    return stack;
#endif
    
#ifdef list
    stack->top = NULL;
#endif
}

void freeStack(Stack *stack) {
#ifdef vector
    stack->data = freeVector(stack->data, stack->size);
#endif

#ifdef list
    do {
        if (stack->top) {
            stack->top = freeList(stack->top);
        }
        else {
            puts("ERROR. STACK IS EMPTY");
        }
    } while (stack->top);
#endif
}

void push(Stack *stack, char *str) {
#ifdef vector
    stack->data = addString(stack->data, stack->top, str, stack->size);
    stack->top++;
#endif

#ifdef list
    stack->top = addItem(stack->top, stack->size, str);
#endif
}

char *pop(Stack *stack) {
    char *str = (char *) calloc(2 * stack->size, sizeof (char));
#ifdef vector
    stack->top--;
    str = getString(str, stack->data, stack->top, stack->size);
#endif

#ifdef list
    str = getItem(str, &stack->top, stack->size);
#endif
    return str;
}
