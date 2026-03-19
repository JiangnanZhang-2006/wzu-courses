#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, temp, flag = -1;
    cin >> n;
    temp = n / 2;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < temp; j++) {
            cout << "-";
        }
        for (int j = 0; j < n - temp * 2; j++) {
            cout << "*";
        }
        for (int j = 0; j < temp; j++) {
            cout << "-";
        }
        cout << endl;
        temp += flag;
        if (temp == 0) {
            flag = 1;
        }
    }
    return 0;
}