#include <bits/stdc++.h>
using namespace std;
string add_palindromic_numbers(const string &a) {
    string b(a.rbegin(), a.rend());
    string res;
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    int carry = 0;
    while (i >= 0 || j >= 0 || carry) {
        int da = (i >= 0) ? (a[i] - '0') : 0;
        int db = (j >= 0) ? (b[j] - '0') : 0;
        int s = da + db + carry;
        res.push_back(char('0' + (s % 10)));
        carry = s / 10;
        --i; --j;
    }
    reverse(res.begin(), res.end());
    // remove leading zeros except keep single zero
    size_t pos = res.find_first_not_of('0');
    if (pos == string::npos) return "0";
    return res.substr(pos);
}
bool is_palindrome(const string &s) {
    int len = s.size();
    for (int i = 0; i < len / 2; ++i) {
        if (s[i] != s[len - 1 - i]) return false;
    }
    return true;
}
int main() {
    string n;
    if (!(cin >> n)) return 0;
    for (int i = 0; i < 10; ++i) {
        if (is_palindrome(n)) {
            cout << n << " is a palindromic number." << '\n';
            return 0;
        }
        string m = add_palindromic_numbers(n);
        cout << n << " + " << string(n.rbegin(), n.rend()) << " = " << m << '\n';
        n = m;
    }
    cout << "Not found in 10 iterations." << '\n';
}