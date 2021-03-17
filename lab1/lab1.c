#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Line{
	int n;
	double *data;
} Line;

typedef struct Matrix {
	int m;
	Line *matr;
} Matrix;

int getInt(int *);
int getDouble(double *);
int input(Matrix *mat);
void swap(double *array, int x, int y);
int change(Matrix *mat1, Matrix *mat2);
void output(const char *msg, Matrix mat);
void erase(Matrix *mat);

int main() {
	Matrix matr = {0, NULL};
	Matrix result = {0, NULL};
	if (input(&matr) == 0) {
		printf("%s\n", "End of file occured");
		return 1;
	}
	change(&matr, &result);
	output("Source matrix", matr);
	output("Result matrix", result);
	erase(&matr);
	erase(&result);
	return 0;
}

int getInt(int *a) {
	int n;
	do {
		n = scanf("%d", a);
		if (n < 0) {return 0;}
		if (n == 0) {
			printf("%s\n", "Error. Please, repeat input.");
			scanf("%*c");
		}
	} while (n == 0);
	return 1;
}

int getDouble(double *a) {
	int n;
	do {
		n = scanf("%lf", a);
		if (n < 0)	{return 0;}
		if (n == 0) {
			printf("%s\n", "Error. Please, repeat input.");
			scanf("%*c");
		}
	} while (n == 0);
	return 1;
}

int input(Matrix *mat) {
	const char *error = "";
	int m;
	double *p;
	do {
		printf("%s\n", error);
		printf("Enter number of lines: ");
		error = "Error. Try again.";
		if (getInt(&m) == 0) {
			return 0;
		}
	} while (m < 1);
	mat->m = m;
	mat->matr = (Line *)calloc(m, sizeof(Line));
	for (int i = 0; i < mat->m; i++) {
		error = "";
		do {
			printf("%s\n", error);
			printf("Enter number of elements in line %d: ", i + 1);
			error = "Error. Try again.";
			if (getInt(&m) == 0) {
				mat->m = i;
				erase(mat);
				return 0;
			}
		} while (m < 1);
		mat->matr[i].n = m;
		p = (double *)calloc(m, sizeof(double));
		mat->matr[i].data = p;
		printf("Enter items for line #%d: \n", i + 1);
		for (int j = 0; j < m; j++) {
			if (getDouble(p + j) == 0) {
				mat->m = i + 1;
				erase(mat);
				return 0;
			}
		}
	}
	return 1;
}

void swap(double *array, int x, int y) {
	double temp;
	temp = array[x];
	array[x] = array[y];
	array[y] = temp;
}

int change(Matrix *mat1, Matrix *mat2) {
	int new_m = 0;
	int len;
	int first, last;
	double *buf = NULL;
	for (int i = 0; i < mat1->m; i++) {
		first = -1;
		last = -1;
		len = mat1->matr[i].n;
//		printf("_____LENGHT OF %d LINE IS %d\n", i, len);
		buf = (double *) calloc(len, sizeof(double));
		for (int j = 0; j < len; j++) {
			if ((first == -1) && (mat1->matr[i].data[j] > 0)) {
				first = j;
			}
			if ((last == -1) && (mat1->matr[i].data[j] < 0)) {
				last = j;
			}
			buf[j] = mat1->matr[i].data[j];
		}
		if (first == last) {}
		else {
			new_m++;
			mat2->matr = realloc(mat2->matr, new_m * sizeof(Line));
			mat2->matr[new_m - 1].data = (double *) calloc(len, sizeof(double));
			memcpy(mat2->matr[new_m - 1].data, buf, len * sizeof(double));
			if (first >= 0) {
				if (last == 0) {
					last = first;
				}
				swap(mat2->matr[new_m - 1].data, 0, first);
			}
			if (last >= 0) {
				swap(mat2->matr[new_m - 1].data, len - 1, last);
			}
			mat2->matr[new_m - 1].n = len;
		}
		free(buf);
	}
	mat2->m = new_m;
//	printf("_____________________%d\n", mat2->m);
	return 1;
}

void output(const char *msg, Matrix mat) {
	double *p;
	printf("%s:\n", msg);
	for (int i = 0; i < mat.m; i++) {
		p = mat.matr[i].data;
		for (int j = 0; j < mat.matr[i].n; j++) {
			printf("%6lf ", *(p + j));
		}
		printf("\n");
	}
}

void erase(Matrix *mat) {
	for (int i = 0; i < mat->m; i++) {
		free(mat->matr[i].data);
	}
	free(mat->matr);
	mat->m = 0;
	mat->matr = NULL;
}
