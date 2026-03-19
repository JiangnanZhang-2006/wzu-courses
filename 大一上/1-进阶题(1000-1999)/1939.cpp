#include <bits/stdc++.h>

using namespace std;

int main() {
    double PI = 2;
    for (int i = 2; i <= 200; i += 2) {
        PI *= i / (i - 1.0);
        PI *= i / (i + 1.0);
    }
    cout << fixed << setprecision(3) << PI << endl;
    return 0;
}