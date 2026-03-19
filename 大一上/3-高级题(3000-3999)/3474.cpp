#include <bits/stdc++.h>
using namespace std;

int main() {
    int len;
    cin >> len;
    vector<int> arr(len, 0);
    for (int i = 0; i < len; ++i) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end(), [](int a, int b) {
        return a > b;
    });
    int m, n;
    m = n = sqrt(len);
    while (len % n != 0 && n >= 1) {
        --n;
    }
    m = len / n;
    vector<vector<int>> vec(m, vector<int>(n, 0));
    int i = 0, j = 0;
    int dir = 0; // 0:right, 1:down, 2:left, 3:up
    for (int k = 0; k < len; ++k) {
        vec[i][j] = arr[k];
        if (dir == 0) {
            if (j + 1 >= n || vec[i][j + 1] != 0) {
                dir = 1;
                ++i;
            } else {
                ++j;
            }
        } else if (dir == 1) {
            if (i + 1 >= m || vec[i + 1][j] != 0) {
                dir = 2;
                --j;
            } else {
                ++i;
            }
        } else if (dir == 2) {
            if (j - 1 < 0 || vec[i][j - 1] != 0) {
                dir = 3;
                --i;
            } else {
                --j;
            }
        } else {
            if (i - 1 < 0 || vec[i - 1][j] != 0) {
                dir = 0;
                ++j;
            } else {
                --i;
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << vec[i][j];
            if (j != n - 1) cout << " ";
        }
        cout << "\n";
    }
    return 0;
}