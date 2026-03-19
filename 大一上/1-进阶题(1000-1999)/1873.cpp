#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int m;
        cin >> m;
        int arr[1000] = { 0 };
        double sum = 0.0;
        for (int i = 0; i < m; i++) {
            cin >> arr[i];
            sum += arr[i];
        }
        double avg = sum / m;
        double var = 0.0;
        for (int i = 0; i < m; i++) {
            var += (arr[i] - avg) * (arr[i] - avg);
        }
        double stddev = sqrt(var / m);
        printf("%.3lf %.3lf\n", avg, stddev);
    }
    return 0;
}