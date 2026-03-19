#include <bits/stdc++.h>
using namespace std;

int main() {
    int a, b, n, m;
    cin >> a >> b >> n >> m;
    vector<pair<bool, vector<int>>> matrix(n, {true, vector<int>(m)});
    set<int> s;
    s.insert(a);
    s.insert(b);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i].second[j];
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int num = matrix[j].second[i];
            if (s.find(num) == s.end() && matrix[j].first) {
                bool find = false;
                auto it =s.upper_bound(num);
                for (; it !=s.end(); ++it) {
                    auto jt = s.begin();
                    for (; jt != it; ++jt) {
                        if ((*it) - (*jt) == num) {
                            find = true;
                            break;
                        } 
                    }
                    if (find) {
                        break;
                    }
                }
                if (find) {
                    s.insert(num);
                } else {
                    cout << "Round #" << i + 1 << ": " << j + 1 << " is out." << endl;
                    matrix[j].first = false;
                }
            } else if (matrix[j].first){
                cout << "Round #" << i + 1 << ": " << j + 1 << " is out." << endl;
                matrix[j].first = false;
            }
        }
    }
    set<int> winners;
    for (int i = 0; i < n; i++) {
        if (matrix[i].first) {
            winners.insert(i);
        }
    }
    if (winners.empty()) {
        cout << "No winner." << endl;
    } else {
        cout << "Winner(s):";
        for (int i : winners) {
            cout << ' ' << i + 1;
        }
        cout << endl;
    }
}