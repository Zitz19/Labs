#include <iostream>
#include <exception>
#include "func.h"

Matrix *newMatrix(int m,  int n) {
    Matrix *M = new Matrix;
    M->noz = 0;
    M->s = 4;
    M->m = m;
    M->n = n;
    M->arrValues = new int [M->s];
    M->arrCols = new int [M->s];
    M->arrRows = new int [m + 1];
    return M;
}

int updateMatrix(Matrix &M) {
    int *tmp1, *tmp2;
    try {
        tmp1 = new int [2 * M.s];
        tmp2 = new int [2 * M.s];
    } catch(std::bad_alloc) {
        std::cerr << "Allocation failure\n";
        return 0;
    }
    M.s *= 2;
    for (int i = 0; i < M.noz; i++) {
        tmp1[i] = M.arrValues[i];
        tmp2[i] = M.arrCols[i];
    }
    delete [] M.arrValues;
    delete [] M.arrCols;
    M.arrValues = tmp1;
    M.arrCols = tmp2;
    return 1;
}

int insertMatrix(Matrix &M) {
    int buf;
    for (int i = 0; i < M.m; i++) {
        M.arrRows[i] = M.noz;
        for (int j = 0; j < M.n; j++) {
            std::cin >> buf;
            if (buf != 0) {
                M.arrValues[M.noz] = buf;
                M.arrCols[M.noz] = j;
                M.noz++;
                if (M.noz == M.s)
                    updateMatrix(M);
            }
        }
    }
    M.arrRows[M.m] = M.noz;
    return 1;
}

void printMatrix(Matrix &M) {
    int k = 0;
    for (int i = 0; i < M.m; i++) {
        int arrBuf[M.n] = {};
        for (int j = 0; j < M.arrRows[i + 1] - M.arrRows[i]; j++) {
            arrBuf[M.arrCols[k]] = M.arrValues[k];
            k++;
        }
        for (int j = 0; j < M.n; j++)
            std::cout << arrBuf[j] << ' ';
        std::cout << std::endl;
    }
}

void printVector(int *arr, int size) {
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << ' ';
    std::cout << std::endl;
}

void calcVector(int *res, Matrix &M) {
    int k = 0;
    for (int i = 0; i < M.m; i++) {
        if (M.arrRows[i + 1] - M.arrRows[i] < M.n) {
            k += M.arrRows[i + 1] - M.arrRows[i];
            if (M.arrCols[k - 1] == M.n - 1)
                res[i] = M.arrValues[k - 1];
            else
                res[i] = 0;
        }
        else {
            bool isPos = true;
            for (int j = 0; j < M.n; j++) {
                if (M.arrValues[k + j] <= 0)
                    isPos = false;
            }
            k += M.n;
            if (isPos)
                res[i] = M.arrValues[k - M.n];
            else
                res[i] = M.arrValues[k - 1];
        }
    }
}

void freeMatrix(Matrix &M) {
    delete [] M.arrValues;
    delete [] M.arrCols;
    delete [] M.arrRows;
    delete &M;
}