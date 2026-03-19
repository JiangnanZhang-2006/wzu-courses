#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T, m, temp;
    double ans = 0;

    cin >> T;

    for (int i = 0; i < T; i++) {

        ans = 0;
        cin >> m;

        for (int j = 0; j < m; j++) {

            cin >> temp;
            ans += temp;
        }

        ans /= m;
        cout << fixed << setprecision(2) << ans << endl;
    }
    return 0;
}