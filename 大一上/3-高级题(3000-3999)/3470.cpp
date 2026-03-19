#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, acnt, bcnt;
    cin >> n;
    
    acnt = bcnt = 0;

    while(n--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (b == a + c && d != a + c) {
            bcnt++;
        }
        if (d == a + c && b != a + c) {
            acnt++;
        }
    }

    cout << acnt << " " << bcnt << "\n";

    return 0;
}