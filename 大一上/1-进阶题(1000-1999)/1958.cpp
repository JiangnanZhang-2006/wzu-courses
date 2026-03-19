#include <bits/stdc++.h>
using namespace std;

int main()
{
    for (int i = 1; i < 100; i++) {
        int temp = i, temp2 = temp * temp;
        bool flag = true;
        while (temp) {
            if (temp % 10 != temp2 % 10) {
                flag = false; 
                break;
            }
            temp = temp / 10;
            temp2 = temp2 / 10;
        }
        if (flag) {
            cout << i << ' ';
        }
    }
    cout << endl;
    return 0;
}