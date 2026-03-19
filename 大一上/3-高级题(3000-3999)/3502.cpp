#include <bits/stdc++.h>
using namespace std;

string unzip(const string &s) {
    string res;
    int n = s.size();
    for (int i = 0; i < n; ++i) {
        if (isdigit(s[i])) {
            int times = s[i] - '0';
            while (isdigit(s[++i]) ) {
                times = times * 10 + (s[i] - '0');
            }
            for (int t = 0; t < times; ++t) {
                res += s[i];
            }
        }
        else {
            res += s[i];
        }
    }
    return res;
}

string zip(const string &s) {
    string res;
    int n = s.size();
    for (int i = 0; i < n; ) {
        char c = s[i];
        int count = 0;
        while (i < n && s[i] == c) {
            ++count;
            ++i;
        }
        if (count > 1) {
            res += to_string(count);
        }
        res += c;
    }
    return res;
}

int main() {
    char way;
    string line;
    if (!(cin >> way)) return 0;
    cin.ignore(); // consume end of line
    getline(cin, line);
    if (way == 'C') {
        cout << zip(line) << '\n';
    } else if (way == 'D') {
        cout << unzip(line) << '\n';
    }
    return 0;
}