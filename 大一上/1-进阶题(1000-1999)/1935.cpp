#include <bits/stdc++.h>
using namespace std;

static int fibonacci(int f0, int f1, int time);         //c++98环境下自定义函数必须提前声明

int main()
{
    int n, ans;
    cin >> n;
    while (n != -1) {
        ans = fibonacci(0, 1, n);
        cout << ans << endl;
        cin >> n;
    }
    return 0;
}

static int fibonacci(int f0, int f1, int time) {
    if (time == 0) {
        return f0;
    }
    else {
        return fibonacci(f1, f0 + f1, time - 1);        //c++98环境下非void函数必须有return值否则报错
    }
}