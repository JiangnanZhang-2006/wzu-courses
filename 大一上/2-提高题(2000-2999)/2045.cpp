#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// 比较两个大数的大小
int compare(const string& a, const string& b) {
    if (a.length() != b.length()) {
        return a.length() > b.length() ? 1 : -1;
    }
    return a.compare(b);
}

// 大数加法
string add(string a, string b) {
    int len = max(a.length(), b.length());
    while (a.length() < len) a = "0" + a;
    while (b.length() < len) b = "0" + b;

    string result = "";
    int carry = 0;

    for (int i = len - 1; i >= 0; i--) {
        int sum = (a[i] - '0') + (b[i] - '0') + carry;
        carry = sum / 10;
        result = to_string(sum % 10) + result;
    }

    if (carry > 0) {
        result = to_string(carry) + result;
    }

    return result;
}

// 大数乘法（乘以一位数）
string multiply(string a, int b) {