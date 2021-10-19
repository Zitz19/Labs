#ifndef LAB1_FUNC_H
#define LAB1_FUNC_H

typedef struct Matrix {
    int noz;
    int s;
    int m;
    int n;
    int * arrValues;
    int * arrCols;
    int * arrRows;
} Matrix;

Matrix *newMatrix(int m,  int n);
int updateMatrix(Matrix &M);
int insertMatrix(Matrix &M);
void printMatrix(Matrix &M);
void printVector(int *arr, int size);
void calcVector(int *res, Matrix &M);
void freeMatrix(Matrix &M);

#endif