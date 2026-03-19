#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, D;
    double e;
    cin >> N >> e >> D;

    vector<pair<int, int>> houses(N, {0, 0}); // {total_days, unused_days}

    int suspected_unused_count = 0, unused_count = 0;

    for (int i = 0; i < N; ++i) {
        cin >> houses[i].first;
        for (int j = 0; j < houses[i].first; ++j) {
            double usage;
            cin >> usage;
            if (usage < e) {
                houses[i].second++;
            }
        }
        if (houses[i].second * 1.0 / houses[i].first > 0.5) {
            suspected_unused_count++;
            if (houses[i].first > D) {
                suspected_unused_count--;
                unused_count++;
            }
        }
    }
    cout << fixed << setprecision(1)
         << (suspected_unused_count * 100.0 / N) << "% "
         << (unused_count * 100.0 / N) << "%" << endl;
}