#include <bits/stdc++.h>
using namespace std;

int main() {
    int Eddington_number, n;
    cin >> n;
    vector<int> days(n);
    for (int i = 0; i < n; ++i) {
        cin >> days[i];
    }
    sort(days.rbegin(), days.rend());
    Eddington_number = 0;
    for (int i = 0; i < n; ++i) {
        if (days[i] > i + 1) {
            Eddington_number = i + 1;
        } else {
            break;
        }
    }
    cout << Eddington_number << endl;
    return 0;
}