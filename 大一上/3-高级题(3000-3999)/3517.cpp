#include <bits/stdc++.h>
using namespace std;

int main() {
    string a, b;
    getline(cin, a);
    getline(cin, b);
    a = a + b;
    set<char> set;
    for (char c : a) {
        if (set.find(c) == set.end()) {
            set.insert(c);
            cout << c;
        }
    }
    cout << endl;
    return 0;
}