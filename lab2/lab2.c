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
    char *buf = NULL;
    char *first = NULL;
    char *second = NULL;
    do {
        printf("Postfix formula: ");
        str = get_str();
        if (str) {
            int len = strlen(str);
            Stack *stack = makeStack(len);
            buf = (char *) calloc(2 * len, sizeof(char));
            char *result = (char *) calloc(2 * len, sizeof(char));
            for (int i = 0; i < len; i++) {
                memset(buf, 0, sizeof(buf));
                memcpy(buf, str + i, sizeof(char));
                if ((buf[0] >= 42) && (buf[0] <= 47)) {
                    memset(result, 0, 2 * len * sizeof(char));
                    second = pop(stack);
                    first = pop(stack);
                    strcat(result, "(");
                    strcat(result, first);
                    strcat(result, buf);
                    strcat(result, second);
                    strcat(result, ")");
                    push(stack, result);
                    free(first);
                    free(second);
                }
                else {
                    push(stack, buf);
                }
            }
            printf("Infix formula: %s\n", result);
            free(result);
            free(buf);
            freeStack(stack);
            free(stack);
            free(str);
        }
        else {
            puts("END OF PROGRAM");
        }
    } while(str);
    return 0;
}