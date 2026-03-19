#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    while (n + m != 0) {
        int cur = 0;
        int* seq = new int[n + 1];
        for (int i = 0; i < n; i++) {
            cin >> seq[i];
        }
        seq[n] = -1;
        while (m > seq[cur] && cur != n) {      //找到m的位置->cur
            cur++;
        }
        for (int i = n; i > cur; i--) {         //其余数据往后移
            seq[i] = seq[i - 1];
        }
        seq[cur] = m;
        for (int i = 0; i <= n; i++) {           //输出
            cout << seq[i] << ' ';
        }

        cout << endl;
        delete[] seq;
        cin >> n >> m;
    }
    return 0;
}