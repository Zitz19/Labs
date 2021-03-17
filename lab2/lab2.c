#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

char *get_str() {
	char buf[81] = {0};
	char *res = NULL;
	int len = 0;
	int n = 0;
	do {
		n = scanf("%80[^\n]", buf);
		if (n < 0) {
			if (!res) {
				return NULL;
			}
		}
		else if (n > 0) {
			int chunk_len = strlen(buf);
			int str_len = len + chunk_len;
			res = realloc(res, str_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = str_len;
		}
		else {
			scanf("%*c");
		}
	} while(n > 0);
	if (len > 0) {
		res[len] = '\0';
	} 
	else {
		res = calloc(1, sizeof(char));
	}
	return res;
}

int main() {
	char *str = NULL;
	int len = 0;
	Stack *stack = NULL;
	do {
		printf("Postfix formula: ");
		str = get_str();
		if (str) {
			len = strlen(str);
			stack = makeStack(len);
			char *elem = NULL;
			char *oper = NULL;
			int i = 0;
			char *first = NULL;
			char *second = NULL;
//			first = (char *) calloc(2 * stack->size, sizeof(char));
//			second = (char *) calloc(2 * stack->size, sizeof(char));
			oper = (char *) calloc(2, sizeof(char));
			printf("STACK SIZE IS %d\n", stack->size);
			do {
				elem = (char *) calloc(2 * stack->size, sizeof(char));
				if ((str[i] >= 42) && (str[i] <= 47)) {
					second = pop(stack);
					first = pop(stack);
					oper[0] = str[i];
					oper[1] = '\0';
					printf("FIRST: %s\n", first);
					printf("SECOND: %s\n", second);
					strcat(elem, "(");
					strcat(elem, first);
					strcat(elem, oper);
					strcat(elem, second);
					strcat(elem, ")");
					push(stack, elem);
					free(first);
					free(second);
				}
				else {
					memcpy(elem, str + i, sizeof(char));
					push(stack, elem);
				}
				i++;
				free(elem);
			} while(i < len);
			printf("Infix formula: %s\n", pop(stack));
			freeStack(stack);
			free(str);
		}
		printf("\n");
	} while (str);
	return 0;
}
