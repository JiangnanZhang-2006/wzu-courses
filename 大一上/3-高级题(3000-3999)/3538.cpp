#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;
bool all_prime = true;
bool is_prime(int n) {
    if (n < 2) {
        all_prime = false;
        return false;
    }
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            all_prime = false;
            return false;
        }
    }
    return true;
}
int main() {
    string n;
    cin >> n;
    do {
        cout << n << (is_prime(stoi(n)) ? " Yes" : " No") << endl;
        n = n.substr(1);
    } while (n.size() != 0);
    if (all_prime) {
        cout << "All Prime!" << endl;
    }
}