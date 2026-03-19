#include <bits/stdc++.h>

using namespace std;

int main() {
    double ans, x;
    cin >> x;
    if (x < 0 && x >= -5) {
        ans = 8 / (x * x + x + 1);
    }
    else if (x < 5 && x >= 0) {
        ans = 7 / (x * x + x + 1);
    }
    else if (x < 10 && x >= 5) {
        ans = 2 / (x + 8);
    }
    else {
        ans = 0;
    }
    cout << fixed << setprecision(3) << ans << endl;

    return 0;
}