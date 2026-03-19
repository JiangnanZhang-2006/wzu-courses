#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin >> T;
    while (T--) {
        int a, n, sum = 0;
        cin >> a >> n;
        for (int i = 0; i < n; i++) {
            sum += a;
            a = a * 10 + a % 10;
        }
        if (n == 0) {
            printf("=0\n");
        }
        else if (n == 1) {
            printf("a=%d\n", sum);
        }
        else if (n == 2) {
            printf("a+aa=%d\n", sum);
        }
        else if (n == 3) {
            printf("a+aa+aaa=%d\n", sum);
        }
        else {
            printf("a+aa+aaa+...=%d\n", sum);
        }
    }
    return 0;
}