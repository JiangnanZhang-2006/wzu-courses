#include <bits/stdc++.h>
using namespace std;
bool is_prime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}
int main() {
    int num_of_students;
    cin >> num_of_students;
    vector<pair<string, bool>> ranklist;
    for (int i = 0; i < num_of_students; ++i) {
        string id;
        cin >> id;
        ranklist.push_back({id, false});
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        string query_id;
        cin >> query_id;
        auto it = find_if(ranklist.begin(), ranklist.end(), [&](const pair<string, bool>& p) {
            return p.first == query_id;
        });
        if (it != ranklist.end()) {
            if (it->second) {
                cout << it->first << ": Checked" << endl;
                continue;
            }
            it->second = true;
            int rank = distance(ranklist.begin(), it) + 1;
            if (rank == 1) {
                cout << it->first << ": Mystery Award" << endl;
            } else if (is_prime(rank)) {
                cout << it->first << ": Minion" << endl;
            } else {
                cout << it->first << ": Chocolate" << endl;
            }
        } else {
            cout << query_id << ": Are you kidding?" << endl;
        }
    }
}