#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <unordered_map>
using namespace std;

long long isqrt(long long x) {
    if (x <= 0) return 0;
    long long r = (long long)floor(sqrt((double)x));
    while (r * r > x) --r;
    while ((r + 1) * (r + 1) <= x) ++r;
    return r;
}

int main() {
    int m, n;
    if (!(cin >> m >> n)) return 0;
    m = m == 1 ? 2 : m; // a must be >= 2
    const int LIMIT = 25000; // problem constraint upper bound
    unordered_map<long long, int> mapB; // c -> b
    for (int b = 1; b <= LIMIT; ++b) {
        long long s = 1LL * b * b + 1LL * (b - 1) * (b - 1);
        mapB[s] = b;
    }

    bool found = false;
    for (int a = m; a <= n; ++a) {
        long long a3 = 1LL * a * a * a;
        long long a1 = 1LL * (a - 1) * (a - 1) * (a - 1);
        long long c2 = a3 - a1; // should be perfect square
        long long c = isqrt(c2);
        if (c * c != c2) continue;
        auto it = mapB.find(c);
        if (it != mapB.end()) {
            cout << a << " " << it->second << '\n';
            found = true;
        }
    }
    if (!found) cout << "No Solution" << '\n';
    return 0;
}