#include <bits/stdc++.h>
using namespace std;

int main() {
    int n[32][32] = { 0 };
    int curX, curY, r, num = 1;
    cin >> r;

    curY = 0;
    curX = r / 2;
    //process
    while (num <= r * r) {
        if (n[curY][curX] == 0) {
            n[curY][curX] = num;
            num++;
        }

        int oldY = curY;
        int oldX = curX;

        curY = (curY - 1 + r) % r;
        curX = (curX + 1) % r;

        if (n[curY][curX] != 0) {
            curY = (oldY + 1) % r;
            curX = oldX;
        }
    }

    //output
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < r; j++) {
            cout << n[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}