#include <bits/stdc++.h>

using namespace std;

vector<int> cnt{0, 0, 0, 0, 0, 0}; //{P A T e s t}

int main() {
    string s;
    getline(cin, s);
    for (char c : s) {
        if (c == 'P') {
            cnt[0]++;
        }
        if (c == 'A') {
            cnt[1]++;
        }
        if (c == 'T') {
            cnt[2]++;
        }
        if (c == 'e') {
            cnt[3]++;
        }
        if (c == 's') {
            cnt[4]++;
        }
        if (c == 't') {
            cnt[5]++;
        }
    }
    while (cnt[0] or cnt[1] or cnt[2] or cnt[3] or cnt[4] or cnt[5]) {
        if (cnt[0]) {
            cout << 'P';
            cnt[0]--;
        }
        if (cnt[1]) {
            cout << 'A';
            cnt[1]--;
        }
        if (cnt[2]) {
            cout << 'T';
            cnt[2]--;
        }
        if (cnt[3]) {
            cout << 'e';
            cnt[3]--;
        }
        if (cnt[4]) {
            cout << 's';
            cnt[4]--;
        }
        if (cnt[5]) {
            cout << 't';
            cnt[5]--;
        }
    }
    cout << endl;
}