#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n / 2; i++) {
        if (n % i == 0) return false;
    }
    return true;
}
int main() {
    int n;
    if (!(cin >> n)) return 1;
    vector<bool> prime(10000005, false);
    for (int i = 2; i <= 10000000; i++) {
        prime[i] = is_prime(i);
    }
    if (prime[n] && (prime[n + 6] || prime[n - 6])) {
        cout << "YES" << endl;
        if (prime[n + 6] && prime[n - 6]) {
            cout << n - 6 << endl;
        } else {
            cout << (prime[n + 6] ? n + 6 : n - 6) << endl;
        }
    } else {
        cout << "NO" << endl;
        for (int i = 0;; i++) {
            if (prime[n + i] && (prime[n + i + 6])) {
                cout << n + i << endl;
                break;
            }
        }
    }
}