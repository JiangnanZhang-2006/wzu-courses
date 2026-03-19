#include <bits/stdc++.h>
using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    while (m || n) {
        int cnt = 0;
        for (int i = m; i <= n; i++) {
            int temp = i;
            bool flag = true;
            while (temp) {
                if (temp % 10 == 4) {
                    flag = false;
                    break;
                }
                else if (temp % 10 == 2 && temp / 10 % 10 == 6) {
                    flag = false;
                    break;
                }
                temp = temp / 10;
            }
            if (flag) cnt++;

        }
        cout << cnt << endl;
        cin >> m >> n;
    }
    return 0;
}