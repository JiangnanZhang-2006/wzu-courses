#include <bits/stdc++.h>
using namespace std;

int gcd (int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int main() {
    string f1, f2;
    int K;
    if (!(cin >> f1 >> f2 >> K)) return 0;

    auto parse = [](const string &s) {
        size_t p = s.find('/');
        int num = stoi(s.substr(0, p));
        int den = stoi(s.substr(p + 1));
        return pair<int,int>(num, den);
    };

    auto p1 = parse(f1);
    auto p2 = parse(f2);

    long long n1 = p1.first, d1 = p1.second;
    long long n2 = p2.first, d2 = p2.second;

    // ensure left < right
    long long leftN, leftD, rightN, rightD;
    if (n1 * d2 <= n2 * d1) {
        leftN = n1; leftD = d1; rightN = n2; rightD = d2;
    } else {
        leftN = n2; leftD = d2; rightN = n1; rightD = d1;
    }

    bool firstOut = true;
    for (int i = 1; i < K; ++i) {
        if (gcd(i, K) != 1) continue;
        // check left < i/K < right (strictly between)
        long long lhs = leftN * (long long)K;
        long long mid = (long long)i * leftD;
        long long mid2 = (long long)i * rightD;
        long long rhs = rightN * (long long)K;
        if (lhs < mid && mid2 < rhs) {
            if (!firstOut) cout << ' ';
            cout << i << '/' << K;
            firstOut = false;
        }
    }

    cout << '\n';
    return 0;
}