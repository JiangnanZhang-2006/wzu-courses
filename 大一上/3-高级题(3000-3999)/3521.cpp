#include <bits/stdc++.h>
using namespace std;

int main() {
    size_t n, k;
    int num;
    cin >> n >> k >> num;
    deque<deque<int>> arr(n, deque<int>(n));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            cin >> arr[i][j];
        }
    }
    size_t time = 0;
    for (size_t i = 0; i < n; i += 2) {
        time = time % k + 1;
        for (size_t j = 0; j < time; j++) {
            int temp = arr[i].back();
            arr[i].pop_back();
            arr[i].push_front(num);
        }
    }
    for (size_t i = 0; i < n; i++) {
        int sum = 0;
        for (size_t j = 0; j < n; j++) {
            sum += arr[j][i];
        }
        if (i != n - 1) cout << sum << ' ';
        else cout << sum;
    }
    cout << endl;
    return 0;
}
