#include <bits/stdc++.h>
using namespace std;

int main() {
    int len, valve;
    cin >> len >> valve;
    vector<int> vec(len);
    for (int i = 0; i < len; i++) {
        cin >> vec[i];
    }
    bool find = false;
    int st = -1;
    for (int i = 0; i < len; i++) {
        if (vec[i] > valve && st == -1) {
            st = i;
        } else if (vec[i] <= valve && st != -1) {
            find = true;
            cout << "[" << st << ", " << i - 1 << "]" << endl;
            st = -1;
        }
    }
    if (st != -1) {
        find = true;
        cout << "[" << st << ", " << len - 1 << "]" << endl;
    }
    if (!find) {
        cout << *max_element(vec.begin(), vec.end()) << endl;
    }
    return 0;
}