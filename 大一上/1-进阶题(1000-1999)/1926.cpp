#include <bits/stdc++.h>

using namespace std;

int main() {
    char ch;
    cin >> ch;
    if ((ch > 'a' && ch < 'z') || (ch > 'A' && ch < 'Z')) {
        cout << '1' << endl;
    }
    else if (ch > '0' && ch < '9') {
        cout << '0' << endl;
    }
    else {
        cout << "-1" << endl;
    }
    return 0;
}