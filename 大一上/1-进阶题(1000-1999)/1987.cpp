// #include <bits/stdc++.h>

// using namespace std;

// int main() {
//     int arr[1000][2];
//     int n, m, cur = 0, start = 0;
//     cin >> n >> m;
//     //create
//     for (int i = 0; i < n; i++) {
//         int temp;
//         cin >> temp;
//         arr[i][0] = temp;
//         arr[i][1] = i + 1;
//     }
//     arr[n - 1][1] = -1;
//     //process
//     while (cur != n - m - 1) {
//         cur = arr[cur][1];
//     }
//     arr[n - 1][1] = 0;
//     start = arr[cur][1];
//     arr[cur][1] = -1;
//     //output
//     cur = start;
//     while (cur != -1) {
//         cout << arr[cur][0];
//         cur = arr[cur][1];
//         if (cur != -1) cout << ' ';
//     }
//     cout << endl;
//     return 0;
// }
#include <iostream>
#include <deque>
using namespace std;

int main() {
    deque<int> arr;
    size_t n, m;
    if (!(cin >> n >> m)) return 1;
    for (size_t i = 0; i < n; ++i) {
        int temp;
        if (!(cin >> temp)) return 1;
        arr.push_back(temp);
    }
    for (size_t i = 0; i < m; ++i) {
        arr.push_front(arr.back());
        arr.pop_back();
    }
    for (size_t i = 0; i < n; ++i) {
        cout << arr[i];
        if (i != n - 1) cout << ' ';
    }
    cout << endl;
}
