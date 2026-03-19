#include <bits/stdc++.h>
using namespace std;

bool judge(int temp) {
    if (temp == 2) {
        return true;
    }
    for (int i = 2; i < sqrt(temp) + 1; i++) {
        if (temp % i == 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    int T;

    cin >> T;

    for (int i = 0; i < T; i++) {

        int a;

        cin >> a;

        if (judge(a)) {
            cout << "yes" << endl;
        }
        else {
            cout << "no" << endl;
        }
    }
    return 0;
}