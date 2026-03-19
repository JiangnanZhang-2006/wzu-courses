#include <bits/stdc++.h>
using namespace std;
static int strrindex(string s, string t);
int main()
{
    string s, t;
    getline(cin, s);
    getline(cin, t);
    cout << strrindex(s, t) << endl;
    return 0;
}
int strrindex(string s, string t) {
    for (int i = s.size() - t.size(); i >= 0; i--) {
        if (s.substr(i, t.size()) == t) {
            return i; 
        }
    }
    return -1;
}