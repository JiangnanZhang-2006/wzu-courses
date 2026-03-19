#include <bits/stdc++.h>
using namespace std;

int main()
{
    string s;
    int dic[26] = { 0 };
    getline(cin, s);
    for (int i = 0; i < s.size(); i++) {
        if (s[i] <= 'Z' && s[i] >= 'A') {
            if (dic[s[i] - 'A'] == 0) {
                dic[s[i] - 'A'] = 1;
                cout << s[i] << ' ';
            }
        }
    }
    cout << endl;
    
    return 0;
}