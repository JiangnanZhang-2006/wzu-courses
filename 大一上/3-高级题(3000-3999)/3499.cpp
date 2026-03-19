#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> linked_list(100005, {-1, -1});
int main() {
    int head, k;
    size_t len;
    if (!(cin >> head >> len >> k)) return 0;
    vector<pair<int, int>> vec;
    // input
    for (int i = 0; i < len; ++i) {
        int addr, val, next;
        cin >> addr >> val >> next;
        linked_list[addr] = {next, val};
    }
    // to list: traverse from head until -1, push back existing nodes
    int cur = head;
    while (cur != -1) {
        vec.push_back({cur, linked_list[cur].second});
        cur = linked_list[cur].first;
    }
    // update length to actual list size
    len = static_cast<int>(vec.size());
    // partition into negative, [0..k], and greater-than-k to avoid erase/insert during iteration
    vector<pair<int,int>> neg, mid, big;
    for (const auto &p : vec) {
        if (p.second < 0) neg.push_back(p);
        else if (p.second <= k) mid.push_back(p);
        else big.push_back(p);
    }
    vec.clear();
    vec.insert(vec.end(), neg.begin(), neg.end());
    vec.insert(vec.end(), mid.begin(), mid.end());
    vec.insert(vec.end(), big.begin(), big.end());
    // output
    for (int i = 0; i < len; ++i) {
        cout << setw(5) << setfill('0') << vec[i].first << ' ' << vec[i].second << ' ';
        if (i == len - 1) {
            cout << -1 << '\n';
        } else {
            cout << setw(5) << setfill('0') << vec[i + 1].first << '\n';
        }
    } 
}