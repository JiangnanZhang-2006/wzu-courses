#include <bits/stdc++.h>
using namespace std;

string add_with_2(string a) {
    string b = "2";
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    string res;
    int carry = 0;
    int maxLen = max(a.size(), b.size());
    for (int i = 0; i < maxLen || carry; i++) {
        int da = (i < a.size()) ? a[i] - '0' : 0;
        int db = (i < b.size()) ? b[i] - '0' : 0;
        int sum = da + db + carry;
        res.push_back(sum % 10 + '0');
        carry = sum / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}
int main() {
    string s, s1, s2;
    cin >> s;
    if (s.size() % 2 == 1) {
        cout << "Error: " << s.size() << " digit(s)" << endl;
        return 0;
    }
    s1 = s.substr(0, s.size() / 2);
    s2 = s.substr(s.size() / 2);
    string s1_original = s1;
    s1 = add_with_2(s1);
    if (s1 == s2) {
        cout << "Yes: " << s2 << " - " << s1_original << " = 2" << endl;
    } else {
        cout << "No: " << s2 << " - " << s1_original << " != 2" << endl;
    }
    
}