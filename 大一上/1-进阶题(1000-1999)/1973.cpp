#include <bits/stdc++.h>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int len_col, len_row;
        cin >> len_row >> len_col;
        int** seq2 = new int* [len_row];
        //input
        for (int i = 0; i < len_row; i++) {
            seq2[i] = new int[len_col];
            for (int j = 0; j < len_col; j++) {
                int temp;
                cin >> temp;
                seq2[i][j] = temp;
            }
        }
        for (int i = 0; i < len_col; i++) {
            for (int j = 0; j < len_row; j++) {
                cout << seq2[j][i];
                cout << ' ';
            }
            cout << endl;
        }
        cout << endl;
        delete[] seq2;
    }
    return 0;
}