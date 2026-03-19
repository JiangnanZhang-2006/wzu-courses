#include <bits/stdc++.h>

using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    cout << a + b + c << ' ' << (a + b + c) / 3 << ' ' << a * b * c << ' ' << min({ a, b, c }) << ' ' << max({ a, b, c }) << endl;
    return 0;
}