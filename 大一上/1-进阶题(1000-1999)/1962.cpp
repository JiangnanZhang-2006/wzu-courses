#include <bits/stdc++.h>
using namespace std;

static int total(int num) {
    int sum = 0;
    for (int i = 1; i < num + 1; i++) {
        sum += i;
    }
    return sum;
}

int main()
{
    int n;
    double sum = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        sum += 1.0 / total(i);
    }
    cout << fixed << setprecision(3) << sum << endl;
    return 0;
}