#include <iostream>

using namespace std;
int is_prime(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}
int main() {
    int n;
    if (!(cin >> n)) return 1;
    if (is_prime(n) && (is_prime(n - 6) || is_prime(n + 6))) {
        cout << "Yes\n";
        cout << (is_prime(n - 6) ? n - 6 : n + 6) << '\n';
    } else {
        cout << "No\n";
        for (int i = 1;; i++) {
            if (is_prime(n - i) && (is_prime(n - i - 6) || is_prime(n - i + 6))) {
                cout << n - i << '\n';
                break;
            }
            if (is_prime(n + i) && (is_prime(n + i - 6) || is_prime(n + i + 6))) {
                cout << n + i << '\n';
                break;
            }
        }
    }
}