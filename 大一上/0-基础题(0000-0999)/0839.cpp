#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int arr[100] = { 0 };

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int m;
    cin >> m;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] != m) {
            arr[cnt] = arr[i];
            cnt++;
        }
    }

    for (int i = 0; i < cnt; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}