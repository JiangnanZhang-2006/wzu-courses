#include <bits/stdc++.h>
using namespace std;

int main() {
    deque<int> q = {9, 1, 0, 2};
    int n;
    cin >> n;
    n = n - 4;
    cout << 2019;
    while (n--) {
        int sum = 0;
        for (int i : q) {
            sum += i;
        }
        q.push_front(sum % 10);
        q.pop_back();
        cout << sum % 10;
    }
    cout << endl;
    return 0;
}