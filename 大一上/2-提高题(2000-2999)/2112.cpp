#include <bits/stdc++.h>
using namespace std;

int main()
{
    int year;
    cin >> year;
    while (year) {
        int year1 = 0, year2 = 0, year3 = 0, adult = 1, newCow;
        for (int i = 2; i <= year; i++) {
            adult += year3;
            year3 = year2;
            year2 = year1;
            year1 = adult;
            
        }
        cout << year1 + year2 + year3 + adult << endl;
        cin >> year;
    }
    return 0;
}