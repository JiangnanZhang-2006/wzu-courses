#include <bits/stdc++.h>
using namespace std;

int main() {
    string base, a, b;
    if (!(cin >> base >> a >> b)) return 0;
    int carry = 0;
    reverse(base.begin(), base.end());
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    string res;
    size_t maxlen = max({a.size(), b.size()});
    for (size_t i = 0; i < maxlen; ++i) {
        int da = (i < a.size()) ? (a[i] - '0') : 0;
        int db = (i < b.size()) ? (b[i] - '0') : 0;
        int dbase = (i < base.size()) ? (base[i] - '0') : 10; // default base 10 if not specified
        dbase = dbase ? dbase : 10; // base digit cannot be zero
        int sum = da + db + carry;
        carry = sum / dbase;
        int digit = sum % dbase;
        res.push_back(char(digit + '0'));
    }
    while (carry > 0) {
        int dbase = (res.size() < base.size()) ? (base[res.size()] - '0') : 10;
        int digit = carry % dbase;
        carry = carry / dbase;
        res.push_back(char(digit + '0'));
    }
    res.erase(res.find_last_not_of('0') + 1, string::npos);
    reverse(res.begin(), res.end());
    cout << res << '\n';
    return 0;

}