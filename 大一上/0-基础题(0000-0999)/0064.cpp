#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    cin >> n;
    while (n != 0) {
        int lst[102];
        for (int i = 0; i < n; i++) {
            cin >> lst[i];
        }
        //bubblesort
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (abs(lst[j]) < abs(lst[j + 1])) {
                    //½»»»j,j+1
                    lst[j] += lst[j + 1];
                    lst[j + 1] = lst[j] - lst[j + 1];
                    lst[j] = lst[j] - lst[j + 1];
                }
            }
        }
        
        for (int i = 0; i < n - 1; i++) {
            cout << lst[i] << ' ';
        }
        cout << lst[n - 1] << endl;
        cin >> n;
    }
    return 0;
}