#include <bits/stdc++.h>

using namespace std;

static int fibonacci(int a, int b, int time);

int main() {
    int n;
    cin >> n;
    while (n--) {
        int a;
        cin >> a;
        cout << fibonacci(1, 1, a) << endl;
    }
    return 0;
}
int fibonacci(int a, int b, int time) {
    if (time != 1) {
        return fibonacci(b, a + b, time - 1);
    }
    else {
        return a;
    }
}