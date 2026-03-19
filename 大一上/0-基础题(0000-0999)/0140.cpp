#include <bits/stdc++.h>
using namespace std;

static bool isPrime(int input);

int main()
{
    int input;

    cin >> input;

    while (input != 0) {
        int cnt = 0;

        for (int i = 2; i <= input/2; i++) {
            if (isPrime(i) && isPrime(input - i) && i != input - i) {     //注意两个数不同
                cnt += 1;
            }
        }
        cout << cnt << endl;
        cin >> input;
    }
    return 0;
}

static bool isPrime(int input) {
    for (int i = 2; i < input; i++) {
        if (input % i == 0) {
            return false;
        }
    }
    return true;
}