#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    double x, ans = 0;
    cin >> x >> n;
    ans += x;
    for (int i = 0; i < n-1; i++) {
        ans += x;
        x = x / 2.0;
    }

    cout << fixed << setprecision(6) << ans << endl;
    return 0;
}
