#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    while (n != 0 || m != 0) {
        int lst[102] = { 0 }, pos = -1;
        for (int i = 0; i < n; i++) {
            cin >> lst[i];
            if (lst[i] > m && pos == -1) {
                pos = i;
            }
        }
        if (pos == -1) {
            pos = n;
        }
        for (int i = n; i > pos; i--) {
            lst[i] = lst[i - 1];
        }
        lst[pos] = m;
        for (int i = 0; i < n; i++) {
            cout << lst[i] << ' ';
        }
        cout << lst[n] << endl;
        cin >> n >> m;
    }
    return 0;
}