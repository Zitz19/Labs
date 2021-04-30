#include <stdio.h>
#include <math.h>

#define X_MAX 100
#define X_MIN -100

int solve(int a, int b, int c, int *x1, int *x2) {
	if (!a) {
		return 1;
	}

	if ((b % a) || (c % a)) {
		return 2;
	}

	int D = b*b - 4*a*c;
	int k1 = (-b + sqrt(D)) / 2;
	int k2 = (-b - sqrt(D)) / 2;
	*x1 = k1, *x2 = k2;
	return 0;
}

int main() {
	int a, b, c;
	int x1, x2;
	int status;

	printf("ax^2 + bx + c = 0\n");
	printf("Please enter a\n");
	scanf("%d", &a);
	printf("Please enter b\n");
        scanf("%d", &b);
	printf("Please enter c\n");
        scanf("%d", &c);

	if ((status = solve(a, b, c, &x1, &x2)) != 0) {
		switch (status) {
		case 1:
			printf("Not a quadratic equation\n");
			break;
		case 2:
			printf("No roots found\n");
			break;
		default:
			printf("Should never be reached\n");
		}
		return status;
	}

	if  (x1 != x2) {
		printf("Two roots found: %d %d\n", x1, x2); }
	else {
		printf("Single root found: %d\n", x1); }
	return 0;
}
