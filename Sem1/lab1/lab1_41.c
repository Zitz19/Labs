#include <stdio.h>
#include <stdbool.h>

int main() {
	int n;
	printf("Please enter n\n");
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		bool check = 1;
		int m = i;
		while (m > 0) {
			if ((m % 10) != 0) {
				if ((i % (m % 10)) == 0) {
					m = m / 10;
				}
				else {
					check = 0;
					break;
				}
			}
			else {
				check = 0;
				break;
			}
		}
		if  (check == 1) {
			printf("%d\n", i);
		}
	}
	return 0;
}
