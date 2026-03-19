#include <bits/stdc++.h>
using namespace std;

int main()
{
    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            cout << i << "*" << j << "=" << i * j;
            for (int k = 0; k < 2 - (int)log10(i * j); k++) {   //计算i*j的位数
                cout << " ";
            }
        }
        cout << endl;
    }
    return 0;
}