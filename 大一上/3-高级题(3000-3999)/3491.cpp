#include <bits/stdc++.h>
using namespace std;

int main() {
    string password;
    int tried_times = 0, limited_times;
    cin >> password >> limited_times;
    cin.ignore();
    string attempt;
    while (tried_times < limited_times && getline(cin, attempt)) {
        if (attempt == "#") {
            return 0;
        }
        if (attempt == password) {
            cout << "Welcome in" << endl;
            return 0;
        } else {
            cout << "Wrong password: " << attempt << endl;
            tried_times++;
        }
    }
    cout << "Account locked" << endl;
    return 0;
}