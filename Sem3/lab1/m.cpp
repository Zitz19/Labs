#include <iostream>
using namespace std;

int insertMatrix(int *, int *, int *, int, int);
void printMatrix(int *, int *, int *, int, int, int);
void printVector(int *, int);
void calcVector(int *, int *, int *, int *, int, int, int);

int main() {
    cout << "Enter M and N: ";
    int m, n;
    cin >> m >> n;
    int arrValues[m * n], arrCols[m * n], arrRows[n + 1];
    cout << "Enter a matrix by rows:" << endl;
    int noz;
    noz = insertMatrix(arrValues, arrCols, arrRows, m, n);
    int resVector[m];
    calcVector(resVector, arrValues, arrCols, arrRows, m, n, noz);
    cout << "ArrValues: ";
    printVector(arrValues, noz);
    cout << "ArrCols:   ";
    printVector(arrCols, noz);
    cout << "ArrRows:   ";
    printVector(arrRows, m + 1);
    cout << "Original matrix:\n";
    printMatrix(arrValues, arrCols, arrRows, m, n, noz);
    cout << "Result vector: ";
    printVector(resVector, m);
    return 0;
}

int insertMatrix(int *arrValues, int *arrCols, int *arrRows, int m, int n) {
    int noz = 0, buf;
    for (int i = 0; i < m; i++) {
        arrRows[i] = noz;
        for (int j = 0; j < n; j++) {
            cin >> buf;
            if (buf != 0) {
                arrValues[noz] = buf;
                arrCols[noz++] = j;
            }
        }
    }
    arrRows[m] = noz;
    return noz;
}

void printMatrix(int *arrValues, int *arrCols, int *arrRows, int m, int n, int noz) {
    int k = 0;
    for (int i = 0; i < m; i++) {
        int arrBuf[n] = {};
        for (int j = 0; j < arrRows[i + 1] - arrRows[i]; j++) {
            arrBuf[arrCols[k]] = arrValues[k];
            k++;
        }
        for (int j = 0; j < n; j++)
            cout << arrBuf[j] << ' ';
        cout << endl;
    }
}

void printVector(int *arr, int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << ' ';
    cout << endl;
}

void calcVector(int *res, int *arrValues, int *arrCols, int *arrRows, int m, int n, int noz) {
    int k = 0;
    for (int i = 0; i < m; i++) {
        if (arrRows[i + 1] - arrRows[i] < n) {
            k += arrRows[i + 1] - arrRows[i];
            if (arrCols[k - 1] == n - 1)
                res[i] = arrValues[k - 1];
            else
                res[i] = 0;
        }
        else {
            bool isPos = true;
            for (int j = 0; j < n; j++) {
                if (arrValues[k + j] <= 0)
                    isPos = false;
                k++;
            }
            if (isPos)
                res[i] = arrValues[k - n];
            else
                res[i] = arrValues[k - 1];
        }
    }
}
