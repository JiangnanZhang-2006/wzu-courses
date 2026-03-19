#include <bits/stdc++.h>

using namespace std;

int main() {
    int row;
    while (cin >> row) {

        int** arr = new int* [row];
        //create array
        for (int i = 0; i < row; i++) {
            int col = i + 1;
            arr[i] = new int[col];
            for (int j = 0; j < col; j++) {
                if (j == 0 || j == col - 1) {
                    arr[i][j] = 1;
                }
                else {
                    arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
                }
            }
        }
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < i + 1; j++) {
                cout << arr[i][j];
                if (i != j) cout << ' ';
            }
            cout << endl;
        }
        cout << endl;
        //relese mem
        for (int i = 0; i < row; i++) {
            delete[] arr[i];
        }
        delete[] arr;
    }
    return 0;
}