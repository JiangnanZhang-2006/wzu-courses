#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    cin >> s;
    int cur = 0;
    while (cur < size(s) && s[cur] >= '0' && s[cur] <= '9') {
        cur++;
    }
    if (s[cur] == '+') {
        cout << stoi(s.substr(0, cur)) + stoi(s.substr(cur + 1)) << endl;
    }
    else if (s[cur] == '-') {
        cout << stoi(s.substr(0, cur)) - stoi(s.substr(cur + 1)) << endl;
    }
    else if (s[cur] == '*') {
        cout << stoi(s.substr(0, cur)) * stoi(s.substr(cur + 1)) << endl;
    }
    else if (s[cur] == '/') {
        cout << stoi(s.substr(0, cur)) / stoi(s.substr(cur + 1)) << endl;
    }
    return 0;
}