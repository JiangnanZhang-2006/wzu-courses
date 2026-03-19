#include <bits/stdc++.h>
using namespace std;

int main()
{
    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        int input,cnt = 0;
        cin >> input;
        cout << "case#" << i << endl;
        for (int j = input; j > 0; j--) {
            for (int k = j; k > 0; k--) {
                for (int l = k; l > 0; l--) {
                    if (j * j == k * k + l * l) {
                        cnt += 1;
                    }
                }
            }
        }
        cout << cnt << endl;
    }
    return 0;
}