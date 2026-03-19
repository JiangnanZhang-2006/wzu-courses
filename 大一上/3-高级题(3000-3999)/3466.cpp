#include <bits/stdc++.h>

using namespace std;
vector<int> cnt;
int main() {
    string s;
    getline(cin, s);
    for (int i = 0; i < 26; i++) {
        cnt.push_back(0);
    }
    for (char c : s) {
        c = tolower(c);
        if (c >= 'a' && c <= 'z') {
            cnt[c - 'a']++;
        }
    }
    int max = 0, max_pos = 0;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] > max) {
            max_pos = i;
            max = cnt[i];
        }
    }
    cout << (char)(max_pos + 'a') << ' ' << max << endl;
}