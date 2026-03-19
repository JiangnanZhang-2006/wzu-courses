#include <bits/stdc++.h>
using namespace std;

int main()
{
    long x, n, ans;
    cin >> x >> n;
    ans = x;
    for (int i = 0; i < n - 1; i++) {
        ans *= x;
    }
    cout << ans << endl;
    return 0;
}