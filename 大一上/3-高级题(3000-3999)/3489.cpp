#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    vector<pair<string, string>> couples(n);
    for (int i = 0; i < n; i++) {
        cin >> couples[i].first >> couples[i].second;
    }
    int q;
    cin >> q;
    unordered_set<string> unpaired_set;
    unpaired_set.reserve(q * 2);
    string s;
    for (int i = 0; i < q; ++i) {
        cin >> s;
        unpaired_set.insert(s);
    }

    for (const auto& couple : couples) {
        const string &a = couple.first;
        const string &b = couple.second;
        auto ita = unpaired_set.find(a);
        auto itb = unpaired_set.find(b);
        if (ita != unpaired_set.end() && itb != unpaired_set.end()) {
            unpaired_set.erase(ita);
            unpaired_set.erase(itb);
        }
    }

    vector<string> unpaired;
    unpaired.reserve(unpaired_set.size());
    for (const auto &id : unpaired_set) unpaired.push_back(id);

    sort(unpaired.begin(), unpaired.end());
    cout << unpaired.size() << '\n';
    bool first = true;
    for (const auto &id : unpaired) {
        if (!first) cout << ' ';
        cout << id;
        first = false;
    }
    cout << '\n';
}