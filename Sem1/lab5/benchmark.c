#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"

int main() {
	int tests;
	int str_numb;
	int str_len;
	char symbol;
	FILE *fd;
	int wordlen;
	char *buffer = (char*) calloc(10, sizeof(char));
	srand(time(NULL));
	printf("Number of tests:\n");
	scanf("%d", &tests);
	fd = fopen("data", "a+");
	for (int a = 0; a < tests; a++) {
		printf("Enter number of strings:\n");
		scanf("%d", &str_numb);
		printf("Enter length of strings:\n");
		scanf("%d", &str_len);
		List *list = list_new();
		double time_total = 0;
		for (int i = 0; i < str_numb; i++) {
			for (int j = 0; j < str_len; j++) {
				symbol = rand() % 12 + 1;
				if (symbol < 3) {
					add_item(list, ' ');
				}
				else if (symbol > 3) {
					add_item(list, (char) (rand() % ('z' - 'a') + 'a'));
				}
				else {
					wordlen = rand() % 9 + 2;
					for (int i = 0; i < (wordlen / 2) + (wordlen % 2); i++) {
						buffer[i] = (char) (rand() % ('z' - 'a') + 'a');
						add_item(list, buffer[i]);
					}
					for (int i = (wordlen / 2) - 1; i >= 0; i--) {
						add_item(list, buffer[i]);
					}
				}
			}
			putList(list);
			clock_t t = clock();
			changeList(list);
			t = clock() - t;
			double time = (double) t / CLOCKS_PER_SEC;
			time_total += time;
			putList(list);
			deleteList(list);
		}
		fprintf(fd, "%.8lf %d\n", time_total / str_numb, str_len);
		free(list);
	}
	free(buffer);
	fclose(fd);
	return 0;
}
