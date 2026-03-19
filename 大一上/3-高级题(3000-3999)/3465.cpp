#include <bits/stdc++.h>

using namespace std;

vector<vector<string>> arr;

int main() {
    int len, n;
    cin >> len;
    for (int i = 0; i < len; i++) {
        string id, trial, test; 
        cin >> id >> trial >> test;
        arr.push_back({id, trial, test});
    }
    cin >> n;
    for (int i = 0; i < n; i++) {
        string trial;
        cin >> trial;
        auto it = find_if(arr.begin(), arr.end(), [trial](auto a){return a[1] == trial;});
        cout << (*it)[0] << ' ' << (*it)[2] << endl;
    }
}