#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    cin >> s;
    int l = 0, r = size(s) - 1;
    bool flag = true;
    while (l < r) {
        if (s[l] != s[r]) {
            flag = false;
            break;
        }
        l++; r--;
    }
    if (flag) {
        cout << "Yes." << endl;
    }
    else {
        cout << "No." << endl;
    }
    return 0;
}