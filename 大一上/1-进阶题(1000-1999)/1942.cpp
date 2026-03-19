#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, c1, c2, c3;
    cin >> n;
    while (n) {
        for (int i = 0; i < n; i++) {
            int temp; c1 = 0; c2 = 0; c3 = 0;
            cin >> temp;
            if (temp > 0) {
                c3++;
            }
            else if (temp == 0) {
                c2++;
            }
            else {
                c1++;
            }
        }
        printf("%d %d %d\n", c1, c2, c3);
        cin >> n;
    }
    return 0;
}