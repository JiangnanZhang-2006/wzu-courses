#include <bits/stdc++.h>
using namespace std;

int main()
{
    double arr[51][51] = { 0 };
    int m, n;
    cin >> m >> n;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            double temp;
            cin >> temp;
            arr[i][j] = temp;
            arr[i][n] = max(temp,arr[i][n]);
        }
        for (int j = 0; j < n; j++) {
            arr[i][j] = arr[i][j] / arr[i][n];
            cout << fixed << setprecision(2) << arr[i][j];
            if (j != n - 1) cout << ' ';
        }
        cout << endl;
    }
    
    return 0;
}