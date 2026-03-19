#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    getline(cin, s);
    int sum = 0;
    for (char c : s) {
        c = tolower(c);
        if (c >= 'a' && c <= 'z') {
            sum += (c - 'a' + 1);
        }
    }
    int zero_count = 0, one_count = 0;
    for (; sum > 0; ) {
        if (sum % 2 == 0) {
            zero_count++;
        } else {
            one_count++;
        }
        sum /= 2;
    }
    cout << zero_count << " " << one_count << endl;    return 0;
}