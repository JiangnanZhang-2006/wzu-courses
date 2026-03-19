#include <bits/stdc++.h>
using namespace std;

string addBase30(string a, string b) {
    const char* dic = "0123456789abcdefghijklmnopqrstuvwxyz";
    int charToDigit[256];
    memset(charToDigit, -1, sizeof(charToDigit));
    for (int i = 0; i < 30; i++) {
        charToDigit[dic[i]] = i;
        if (i >= 10 && i < 30) {
            charToDigit['A' + i - 10] = i;
            charToDigit['a' + i - 10] = i;
    }
    }
    
    int carry = 0;
    int maxLen = max(a.size(), b.size());
    string res;
    res.reserve(maxLen + 1);
    
    // Process from right to left
    for (int i = 0; i < maxLen || carry; i++) {
        int da = (i < a.size()) ? charToDigit[(unsigned char)a[a.size() - 1 - i]] : 0;
        int db = (i < b.size()) ? charToDigit[(unsigned char)b[b.size() - 1 - i]] : 0;
        int sum = da + db + carry;
        res.push_back(dic[sum % 30]);
        carry = sum / 30;
    }
    
    reverse(res.begin(), res.end());
    return res;
}
int main() {
    string a, b;
    cin >> a >> b;
    cout << addBase30(a, b) << endl;
}