#include <bits/stdc++.h>
using namespace std;

void check_passwords(string s) {
    bool tai_duan_le = false, tai_luan_le = false, shu_zi = false, zi_mu = false;
    if (s.size() < 6) {
        tai_duan_le = true;
    }
    for (const char &c : s) {
        if (isdigit((unsigned char)c)) shu_zi = true;
        else if (isalpha((unsigned char)c)) zi_mu = true;
        else if (!(c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '.')) tai_luan_le = true;
    }
    if (tai_duan_le) {
        cout << "Your password is tai duan le." << '\n';
    } else if (tai_luan_le) {
        cout << "Your password is tai luan le." << '\n';
    } else if (!shu_zi) {
        cout << "Your password needs shu zi." << '\n';
    } else if (!zi_mu) {
        cout << "Your password needs zi mu." << '\n';
    } else {
        cout << "Your password is wan mei." << '\n';
    }
}
int main() {
    int n;
    if (!(cin >> n)) return 0;
    cin.ignore(); // consume end of line
    for (int i = 0; i < n; ++i) {
        string s;
        getline(cin, s);
        check_passwords(s);
    }
}