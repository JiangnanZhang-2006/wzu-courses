#include <bits/stdc++.h>
using namespace std;

static int cnt(int ipt);

int main()
{
    int t;
    cin >> t;
    while (t--) {
        int a, b, max = 0, maxnum = 0;
        cin >> a >> b;
        for (int i = a; i <= b; i++) {
            if (cnt(i) > max) {
                max = cnt(i);
                maxnum = i;
            }
        }
        cout << maxnum << endl;
    }
    return 0;
}
int cnt(int ipt) {
    int sum = 0;
    for (int i = 1; i <= ipt; i++) {
        if (ipt % i == 0) {
            sum++;
        }
    }
    return sum;
}