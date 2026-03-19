#include <bits/stdc++.h>
#include <unordered_set>
using namespace std;

int main() {
    unordered_set<string> ids_list;
    size_t n;
    if (!(cin >> n)) return 1;
    for (size_t i = 0; i < n; ++i) {
        string id;
        cin >> id;
        ids_list.insert(id);
    }
    int cnt = 0;
    string maxid1 = "999999999999999999", maxid2 = "999999999999999999";
    if (!(cin >> n)) return 1;
    for (size_t i = 0; i < n; ++i) {
        string id;
        if (!cin >> id) break;
        auto it = ids_list.find(id);
        if (it != ids_list.end()) {
            if (id.substr(6, 8) < maxid1.substr(6, 8)) {
                maxid1 = id;
            }
            ++cnt;
        } else {
            if (id.substr(6, 8) < maxid2.substr(6, 8)) {
                maxid2 = id;
            }
        }
    }
    if (!cnt) {
        cout << cnt << "\n" << maxid2 << "\n";
    } else {
        cout << cnt << "\n" << maxid1 << "\n";
    }
}