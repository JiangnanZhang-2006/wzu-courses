#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    //{a, b}
    vector<pair<double, double>> intervals(n);
    for (int i = 0; i < n; ++i) {
        cin >> intervals[i].first >> intervals[i].second;
    }
    double max_r = 0;
    for (const auto &interval : intervals) {
        double pow_sum = pow(interval.first, 2) + pow(interval.second, 2);
        if (pow_sum > max_r) {
            max_r = pow_sum;
        }
    }
    cout << fixed << setprecision(2) << sqrt(max_r) << endl;
}