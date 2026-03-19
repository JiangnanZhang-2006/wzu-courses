#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--) {
        int income;
        cin >> income;
        if (income <= 10000) cout << fixed << setprecision(3) << 1000 + income * 0.05 << endl;
        else if (income <= 50000) cout << fixed << setprecision(3) << 1000 + income * 0.075 << endl;
        else if (income <= 200000) cout << fixed << setprecision(3) << 1000 + income * 0.085 << endl;
        else cout << fixed << setprecision(3) << 1000 + income * 0.1 << endl;
    }
    return 0;
}