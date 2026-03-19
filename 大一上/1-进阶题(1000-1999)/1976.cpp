#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t;
    cin >> t;
    cin.ignore();
    while (t--) {
        string s;
        bool flag = true;
        getline(cin, s);
        for (int i = 0; i < s.size(); i++) {
            if (!((s[i] >= '0' && s[i] <= '9') || s[i] == '_' || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))||(i == 0 && s[i] >= '0' && s[i] <= '9')) {
                flag = false; 
                break;
            }
        }
        if (flag) {
            cout << "yes" << endl;
        }
        else {
            cout << "no" << endl;
        }
    }
    return 0;
}