#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    while (getline(cin, s)) {
        char max = 'a';
        for (int i = 0; i < s.size(); i++) {
            if (s[i] > max) {
                max = s[i];
            }
        }
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == max) {
                cout << s[i] << "(max)";
            }
            else {
                cout << s[i];
            }
        }
        cout << endl;
    }
    return 0;
}