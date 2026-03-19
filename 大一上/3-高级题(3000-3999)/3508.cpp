#include <bits/stdc++.h>
using namespace std;

int main() {
    size_t d, N;
    if (!(cin >> d >> N)) return 0;
    string s = to_string(d);
    for (int i = 0; i < N - 1; ++i) {
        vector<pair<char, int>> cnt;
        for (char c : s) {
            if (cnt.empty() || cnt.back().first != c) {
                cnt.push_back({c, 1});
            } else {
                cnt.back().second++;
            }
        }
        s = "";
        for (auto p : cnt) {
            s += p.first + to_string(p.second);
        }
    }
    cout << s << endl;
}