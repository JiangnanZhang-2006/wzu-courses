#include <bits/stdc++.h>
using namespace std;

int main()
{
    char c;
    cin >> c;
    while (c != '@') {
        int T;
        cin >> T;
        for (int i = 0; i < T - 1; i++) {
            for (int j = 0; j < T + i; j++) {
                if (j == T - i - 1|| j == T + i -1) {
                    cout << c;
                }
                else {
                    cout << ' ';
                }
            }
            cout << endl;
        }
        for (int i = 0; i < T * 2 - 1; i++) {
            cout << c;
        }
        cout << endl << endl;//每个样板三角形之后有一个空行
        cin >> c;
    }
    return 0;
}