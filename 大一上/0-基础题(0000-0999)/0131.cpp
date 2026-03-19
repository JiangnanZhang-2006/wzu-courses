#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m;

    cin >> n >> m;

    while (not (n == 0 && m == 0)){
        int cnt = m - n + 1;

        for (int i = n; i <= m; i++) {
            int temp = i;
            bool flag = true;

            while (temp != 0) {
                if (temp % 10 == 4) {
                    cnt -= 1;
                    break;
                }
                if (temp % 10 == 6 && (not flag)) {
                    cnt -= 1;
                    break;
                }
                if (temp % 10 == 2) {
                    flag = false;
                }
                else {
                    flag = true;
                }
                temp /= 10;
            }
        }
        cout << cnt << endl;
        cin >> n >> m;
    }

    return 0;
}