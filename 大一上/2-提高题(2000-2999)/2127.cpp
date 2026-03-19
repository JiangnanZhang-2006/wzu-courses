#include <bits/stdc++.h>
using namespace std;

int main()
{
    int v, n;
    double arr[100][3] = { 0 };
    cin >> v >> n;
    for (int i = 0; i < n; i++) {
        double a, b;
        cin >> a >> b;
        arr[i][0] = a;
        arr[i][1] = b;
        arr[i][2] = b / a;//单位价值
    }
    int dic[100] = { 0 };
    //init
    for (int i = 0; i < 100; i++) {
        dic[i] = i;
    }
    //bubbleSort
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[dic[j + 1]][2] > arr[dic[j]][2]) {
                int temp = dic[j + 1];
                dic[j + 1] = dic[j];
                dic[j] = temp;
            }
        }
    }
    //count
    double tot = 0;
    for (int i = 0; i < n && v > 0; i++) {
        if (arr[dic[i]][0] <= v) {
            tot += arr[dic[i]][1];
            v -= arr[dic[i]][0];
        }
        else {
            tot += arr[dic[i]][2] * v;
            v = 0;
        }
    }
    cout << fixed << setprecision(2) << tot << endl;
    return 0;
}