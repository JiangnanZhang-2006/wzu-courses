#include <iostream>
using namespace std;

bool divisibleBy7(int num) {
    return num % 7 == 0;
}

bool hasDigit7(int num) {
    while (num > 0) {
        if (num % 10 == 7) {
            return true;
        }
        num /= 10;
    }
    return false;
}

int main() {
    int n;
    cin >> n;

    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (!divisibleBy7(i) && !hasDigit7(i)) {
            sum += i * i;
        }
    }

    cout << sum << endl;
    return 0;
}