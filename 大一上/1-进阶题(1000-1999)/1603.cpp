#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    char a, temp;
    a = 65;

    cin >> n;

    for (int i = 0; i < n; i++) {
        temp = (a - 64) % 26 + 65;
        for (int j = 0; j < n; j++) {
            cout << a;
            a = (a - 64) % 26 + 65;
        }
        a = temp;
        cout << endl;
    }
    return 0;
}