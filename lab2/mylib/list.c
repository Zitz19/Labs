#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/*
Stack *makeList(int m) {
	Stack *stack = NULL;
	stack = (Stack *) calloc(1, sizeof(Stack));
	stack->size = m;
	stack->top = NULL;
	return stack;
}

void freeList(Stack *stack) {
	Item *temp = NULL;
	do {
		temp = stack->top->next;
		free(stack->top->data);
		free(stack->top);
		stack->top = temp;
	} while (stack->top);
	free(stack);
}

void addItem(Stack *stack, char *str) {
	Item *temp = NULL;
	temp = (Item *) calloc(1, sizeof(Item));
	memcpy(temp->data, str, (stack->size) * 2 * sizeof(char));
	temp->next = stack->top;
	stack->top = temp;
	free(temp);
}

void freeItem(Stack *stack) {
	Item *temp = NULL;
	temp = stack->top->next;
	free(stack->top->data);
	free(stack->top);
	stack->top = temp;
}
*/
Item *makeList(int size) {
	Item *head = NULL;
	return head;
}

void freeList(Item *head) {
	Item *temp = NULL;
	do {
		temp = head->next;
		free(head->data);
		free(head);
		head = temp;
	} while(head);
}

void addItem(Item *head, int size, char *str) {
	Item *temp = NULL;
	temp = (Item *) calloc(1, sizeof(Item));
	temp->data = (char *) calloc(2 * size, sizeof(char));
	memcpy(temp->data, str, 2 * size * sizeof(char));
	temp->next = head;
	head = temp;
}

void freeItem(Item *head) {
	Item *temp = NULL;
	temp = head;
	head = temp->next;
	free(temp->data);
	free(temp);
}
