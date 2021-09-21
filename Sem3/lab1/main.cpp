#include <iostream>
#include "func.h"
using std::cout;
using std::cin;
using std::endl;

int main() {
    cout << "Enter M and N: ";
    int m, n;
    cin >> m >> n;
    if (m <= 0 || n <= 0) {
        std::cerr << "___Error(Invalid values)___" << endl;
        return 1;
    }
    Matrix *M = newMatrix(m, n);
    insertMatrix(*M);
    int resVector[M->m];
    calcVector(resVector, *M);
    cout << "ArrValues: ";
    printVector(M->arrValues, M->noz);
    cout << "ArrCols:   ";
    printVector(M->arrCols, M->noz);
    cout << "ArrRows:   ";
    printVector(M->arrRows, M->m + 1);
    cout << "Original matrix:\n";
    printMatrix(*M);
    cout << "Result vector: ";
    printVector(resVector, M->m);
    freeMatrix(*M);
    return 0;
}
