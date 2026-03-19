#include <bits/stdc++.h>
using namespace std;

int main() {
    int len;
    cin >> len;
    vector<double> arr(len, 0);
    for (int i = 0; i < len; ++i) {
        cin >> arr[i];
    }
    double sum = 0.0;
    for (auto it = arr.begin(); it != arr.end(); ++it) {
        for (auto jt = it; jt != arr.end(); ++jt) {
            for (auto kt = it; kt != jt + 1; ++kt) {
                sum += (*kt);
            }
        }
    }
    cout << fixed << setprecision(2) << sum << endl;
}