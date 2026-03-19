#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T--) {
        int a, b, gcd, lcm;
        cin >> a >> b;
        gcd = min({a, b});
        lcm = max({a, b});
        for (int i = gcd; i > 0; i--) {
            if (a % i == 0 && b % i == 0) {
                gcd = i;
                cout << gcd << ' ';
                break;
            }
        }
        while (true) {
            if (lcm % a == 0 && lcm % b == 0) {
                cout << lcm << endl;
                break;
            }
            lcm++;
        }
    }
    return 0;
}