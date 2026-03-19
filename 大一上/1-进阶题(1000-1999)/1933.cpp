#include <bits/stdc++.h>
using namespace std;
void fun_div(int temp) {
    int temp1= temp % 10;
    if (temp != 0) {
        fun_div(temp / 10);
            cout << temp1 << " ";
    }
}
int main()
{
    int n, temp;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        if (temp == 0) {
            cout << "0 ";               //0的后面也要有空格
        }
        else {
            fun_div(temp);
        }
        cout << endl;
    }
    return 0;
}