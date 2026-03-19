#include <bits/stdc++.h>
using namespace std;

int main() {
    size_t len;
    cin >> len;
    cin.ignore();
    string ans = "";

    for (size_t i = 0; i < len; ++i) {
        string line;
        getline(cin, line);
        ans += line[line.find('T') - 2] - 'A' + '1';
    }

    cout << ans << '\n';
    return 0;
}