/*Задача №10: После каждого слова нечетной длины добавить слог "NO". Слова могут разделять неограниченное кол-во
 * пробелов или табуляций, но в конечной строке слова должны быть разделены одиночными пробелами*/

#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"

char *get_str () {
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
	} while (n > 0);
	if (len > 0) {
		res[len] = '\0';
	}
	else {
		res = calloc(1, sizeof(char));
	}
	printf("\"%s\"\n", res);
	return res;
}

char *change_str(char *res) {
	char keys[2] = {' ', '\t'};
	char *new_res = NULL;
	int i_new_res = 0;
	if (res == NULL) {
		return NULL;
	}
	do {
		int word_len = strcspn(res, keys);
		if (word_len % 2 == 1) {
			new_res = realloc(new_res, i_new_res + word_len + 3);
			memcpy(new_res + i_new_res, res, word_len);
			new_res[i_new_res + word_len + 2] = ' ';
			new_res[i_new_res + word_len + 1] = 'O';
			new_res[i_new_res + word_len + 0] = 'N';
			i_new_res = i_new_res + word_len + 3;
			res = res + word_len;
		}
		else if ((word_len == 0) && (*res != '\0')) {
			res++;
		}
		else {
			new_res = realloc(new_res, i_new_res +  word_len + 1);
			memcpy(new_res + i_new_res, res, word_len);
			new_res[i_new_res + word_len + 0] = ' ';
			i_new_res = i_new_res + word_len + 1;
			res = res + word_len;
		}
	} while (strlen(res) != 0);
	if (i_new_res != 0) {
		new_res[i_new_res - 1] = '\0';	
	}
	else {
		new_res = calloc(1, sizeof(char));
		new_res[1] = '\0';
	}
	return new_res;
}

int main () {
	char *s1 = NULL;
	char *s2 = NULL;
	do {
		s1 = get_str();
		s2 = change_str(s1);
		if (s1) {
			printf("\"%s\"\n", s2);
			free(s1);
			free(s2);
		}
	}while (s1);
	return 0;
}
