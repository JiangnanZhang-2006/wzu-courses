#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;

    int limit = sqrt(num);
    for (int i = 3; i <= limit; i += 2) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int x, y;

    while (cin >> x >> y) {
        if (x == 0 && y == 0) {
            continue;
        }

        bool allPrime = true;
        for (int n = x; n <= y; n++) {
            int value = n * n + n + 41;
            if (!isPrime(value)) {
                allPrime = false;
                break;
            }
        }

        if (allPrime) {
            cout << "OK" << endl;
        }
        else {
            cout << "Sorry" << endl;
        }
    }

    return 0;
}