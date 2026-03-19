#include <bits/stdc++.h>
using namespace std;

int main() {
    int token, n;
    if (!(cin >> token >> n)) return 0;
    for (int i = 0; i < n; ++i) {
        int n1, b, t, n2;
        cin >> n1 >> b >> t >> n2;
        if (t > token) {
            cout << "Not enough tokens.  Total = " << token << ".\n";
        } else {
           if (b == 0 && n1 > n2 || b == 1 && n1 < n2) {
                token += t;
                cout << "Win "<< t << "!  Total = " << token << ".\n";
           } else {
                token -= t;
                cout << "Lose " << t << ".  Total = " << token << ".\n";
                if (token <= 0) {
                    cout << "Game Over.\n";
                    return 0;
                    
                }
           }
        }
    }
}