#include <bits/stdc++.h>
using namespace std;

int main() {
    size_t n, m;
    cin >> n >> m;
    unordered_map<string, vector<string>> map;
    for (size_t i = 0; i < n; i++) {
        string a, b;
        cin >> a >> b;
        map[a].push_back(b);
        map[b].push_back(a);
    }
    for (size_t i = 0; i < m; i++) {
        size_t len;
        cin >> len;
        vector<string> vec(len);
        for (size_t j = 0; j < len; j++) {
            cin >> vec[j];
        }
        bool is_valid = true;
        for (string s : vec) {
            if (!map[s].empty()) {
                for (string t : map[s]) {
                    if (find(vec.begin(), vec.end(), t) != vec.end()) {
                        // cout << s << ' ' << t << endl;
                        is_valid = false;
                        break;
                    }
                }
                if (!is_valid) break;
            }
        }
        if (is_valid) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}