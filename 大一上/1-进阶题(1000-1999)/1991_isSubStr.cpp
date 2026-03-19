#include <bits/stdc++.h>

using namespace std;

static bool isSubStr(string subStr, string str);

int main() {
    string subStr, str;
    while (cin >> subStr >> str) {
        if (isSubStr(subStr, str)) {
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }
    }
    return 0;
}
bool isSubStr(string subStr, string str) {
    char c = subStr[0];
    int cur = 0;
    for (int i = 0; i < size(str); i++) {
        if (c == str[i]) {
            cur++;
            c = subStr[cur];
            if (cur == size(subStr)) return true;
        }

    }
    return false;
}