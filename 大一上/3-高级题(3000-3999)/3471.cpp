#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int,vector<bool>>> a(1005, {0, vector<bool>(15, false)});
    while (n--) {
        int score, teamid, stuid;
        scanf("%d-%d %d", &teamid, &stuid, &score);
        a[teamid].first += score;
        a[teamid].second[stuid] = true;
        
    }
    auto max_pos =  max_element(a.begin(), a.end(),
                        [](const pair<int,vector<bool>>& x, const pair<int,vector<bool>>& y) {
                            return x.first < y.first;
                        });
    cout << max_pos - a.begin() << " " << max_pos->first << endl;
    return 0;
}