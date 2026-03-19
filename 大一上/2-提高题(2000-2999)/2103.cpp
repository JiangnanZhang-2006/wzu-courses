#include <bits/stdc++.h>
using namespace std;

int main()
{
    int a, cnt = 0;

    cin >> a;

    while (a != 0) {
        cnt += a % 10;
        a /= 10;
    }

    cout << cnt << endl;

    return 0;
}