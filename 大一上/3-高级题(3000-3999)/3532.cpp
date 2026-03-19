#include <bits/stdc++.h>
using namespace std;

int main() {
    map<char, int> cnt;
    // S, t, r, i, n, g;
    string s;
    getline(cin, s);
    for (char c : s) {
        if (c == 'S') {
            cnt['S']++;
        }
        else if (c == 't') {
            cnt['t']++;
        }
        else if (c == 'r') {
            cnt['r']++;
        }
        else if (c == 'i') {
            cnt['i']++;
        }
        else if (c == 'n') {
            cnt['n']++;
        }
        else if (c == 'g') {
            cnt['g']++;
        }
    }
    while (cnt['S'] || cnt['t'] || cnt['r'] || cnt['i'] || cnt['n'] || cnt['g']) {
        if (cnt['S']) {
            cout << 'S';
            cnt['S']--;
        }
        if (cnt['t']) {
            cout << 't';
            cnt['t']--;
        }
        if (cnt['r']) {
            cout << 'r';
            cnt['r']--;
        }
        if (cnt['i']) {
            cout << 'i';
            cnt['i']--;
        }
        if (cnt['n']) {
            cout << 'n';
            cnt['n']--;
        }
        if (cnt['g']) {
            cout << 'g';
            cnt['g']--;
        }
    }
    cout << endl;
    return 0;
}