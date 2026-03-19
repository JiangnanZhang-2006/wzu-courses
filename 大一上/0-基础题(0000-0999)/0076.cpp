#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    while (cin >> n) {
        int lst[32] = { 0 }, prelst[32] = { 0 };
        for (int i = 0; i <= n; i++) {
            if (i == 0) continue;
            lst[0] = 1;
            lst[i] = 1;
            for (int j = 1; j < i - 1; j++) {
                lst[j] = prelst[j] + prelst[j + 1];
            }
            for (int j = 0; j < i - 1; j++) {
                cout << lst[j] << ' ';
            }
            cout << lst[i - 1] << endl;
            copy(begin(lst), end(lst), begin(prelst));
        }
        cout << endl;
    }
    return 0;
}