#include <bits/stdc++.h>
using namespace std;

int main() {
    int M, N, S;
    cin >> M >> N >> S;
    vector<string> names(M);
    vector<string> awarded_names;
    for (int i = 0; i < M; ++i) {
        cin >> names[i];
    }
    for (int i = S - 1; i < M; i += N) {
        if (find(awarded_names.begin(), awarded_names.end(), names[i]) == awarded_names.end()) {
            awarded_names.push_back(names[i]);
        }
        else {
            while (true) {
                ++i;
                if (i >= M) break;
                if (find(awarded_names.begin(), awarded_names.end(), names[i]) == awarded_names.end()) {
                    awarded_names.push_back(names[i]);
                    break;
                }
            }
        }
    }
    if (awarded_names.empty()) {
        cout << "Keep going..." << endl;
    } else {
        for (const auto& name : awarded_names) {
            cout << name << endl;
        }
    }
}