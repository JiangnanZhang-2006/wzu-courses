#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, len;
    cin >> n >> len;
    //{ans, value}
    vector<pair<int, int>> promlems(len);
    for (int i = 0; i < len; ++i) {
        cin >> promlems[i].second;
    }
    for (int i = 0; i < len; ++i) {
        cin >> promlems[i].first;
    }
    for (int i = 0; i < n; ++i) {
        int total_score = 0;
        for (int j = 0; j < len; ++j) {
            int ans;
            cin >> ans;
            if (ans == promlems[j].first) {
                total_score += promlems[j].second;
            }
        }
        cout << total_score << endl;
    }
}