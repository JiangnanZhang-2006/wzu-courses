#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    cin.ignore();
    while (t--) {
        string s1, s2;
        getline(cin, s1);
        getline(cin, s2);
        cout << "The new string is: " << s1 << s2 << endl;
    }
    return 0;
}