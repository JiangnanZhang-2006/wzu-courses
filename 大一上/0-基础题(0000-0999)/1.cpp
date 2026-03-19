#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Person {
    int idx;
    int skill[6];
};

int main() {
    int N;
    cin >> N;
    vector<Person> persons(N);
    for (int i = 0; i < N; ++i) {
        persons[i].idx = i + 1; // 1-based
        for (int j = 0; j < 6; ++j) cin >> persons[i].skill[j];
    }

    // For optimization: for each skill, select the top k persons (k=20, since 3 out of N people)
    // All possible combinations of up to three people among the union of these candidates is manageable
    int k = 20;
    vector<int> candidates_idx;
    for (int skill = 0; skill < 6; ++skill) {
        vector<pair<int,int>> skillvec; // <level, idx>
        for (int i = 0; i < N; ++i) {
            skillvec.push_back({persons[i].skill[skill], i});
        }
        sort(skillvec.rbegin(), skillvec.rend());
        for (int x = 0; x < min(k, N); ++x) {
            candidates_idx.push_back(skillvec[x].second);
        }
    }
    // Remove duplicates
    sort(candidates_idx.begin(), candidates_idx.end());
    candidates_idx.erase(unique(candidates_idx.begin(), candidates_idx.end()), candidates_idx.end());

    int best_sum = -1;
    int res[3] = {-1, -1, -1};

    int sz = candidates_idx.size();
    for (int i = 0; i < sz; ++i) {
        for (int j = i + 1; j < sz; ++j) {
            for (int m = j + 1; m < sz; ++m) {
                int a = candidates_idx[i], b = candidates_idx[j], c = candidates_idx[m];
                int sum = 0;
                for (int t = 0; t < 6; ++t) {
                    sum += max({persons[a].skill[t], persons[b].skill[t], persons[c].skill[t]});
                }
                if (sum > best_sum) {
                    best_sum = sum;
                    res[0] = persons[a].idx;
                    res[1] = persons[b].idx;
                    res[2] = persons[c].idx;
                }
            }
        }
    }
    // Output the chosen indices (any order)
    cout << res[0] << " " << res[1] << " " << res[2] << endl;
    cout << best_sum << endl;
    return 0;
}
