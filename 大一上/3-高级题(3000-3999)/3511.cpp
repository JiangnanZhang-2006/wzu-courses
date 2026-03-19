#include <bits/stdc++.h>
using namespace std;

int main() {
    size_t n;
    cin >> n;
    set<int> dic;
    int cnt = 0;
    for (size_t i = 1; i <= n; i++) {
        dic.insert(static_cast<int>(i / 2.0) + static_cast<int>(i / 3.0) + static_cast<int>(i / 5.0));
    }
    cout << dic.size() << endl;
}