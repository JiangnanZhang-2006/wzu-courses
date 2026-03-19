#include <bits/stdc++.h>
using namespace std;
double cal_distance(int x, int y) {
    return sqrt(x * x + y * y);
}
int main() {
    string best, worst;
    double best_dist = DBL_MAX, worst_dist = -1.0;
    int n;
    if (!(cin >> n)) return 0;
    for (int i = 0; i < n; ++i) {
        string name;
        int x, y;
        cin >> name >> x >> y;
        double dist = cal_distance(x, y);
        if (dist < best_dist) {
            best_dist = dist;
            best = name;
        }
        if (dist > worst_dist) {
            worst_dist = dist;
            worst = name;
        }
    }
    cout << best << " " << worst << "\n";
}
