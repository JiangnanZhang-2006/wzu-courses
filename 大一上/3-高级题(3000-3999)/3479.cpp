#include <bits/stdc++.h>
using namespace std;

int main() {
    int len, n;
    cin >> len >> n;
    vector<pair<string, int>> students(len);   //{name, length}
    vector<vector<string>> arr(n, vector<string>(len / n));
    arr[0].resize(len / n + len % n);
    
    for (int i = 0; i < len; ++i) {
        cin >> students[i].first >> students[i].second;
    }
    
    sort(students.begin(), students.end(), [](const auto& a, const auto& b) {
        return a.second == b.second ? a.first < b.first : a.second > b.second;
    });
    
    int idx = 0;  
    for (int k = 0; k < n; ++k) {
        int m = arr[k].size();  

        int mid = m / 2;      
        
        if (m > 0) {
            arr[k][mid] = students[idx++].first;
        }
        
        for (int offset = 1; offset < m; offset++) {
            if (idx >= len) break;

            if (mid - offset >= 0) {
                arr[k][mid - offset] = students[idx++].first;
            }

            if (idx < len && mid + offset < m) {
                arr[k][mid + offset] = students[idx++].first;
            }
        }
    }
    
    for (const auto& row : arr) {
        for (int k = 0; k < row.size(); ++k) {
            cout << row[k];
            if (k != row.size() - 1) cout << " ";
        }
        cout << endl;
    }
    return 0;
}