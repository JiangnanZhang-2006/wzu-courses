#include <bits/stdc++.h>
using namespace std;

int main() {
    size_t n, m;
    cin >> n >> m;
    vector<vector<int>> arr(n, vector<int>(m));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            cin >> arr[i][j];
        }
    }
    vector<int> max_arr(n, 0);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            max_arr[i] = max(max_arr[i], arr[i][j]);
        }
    }
    for (size_t i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << max_arr[i];
    }
    cout << endl;
    cout << *max_element(max_arr.begin(), max_arr.end());
    cout << endl;
    return 0;
}