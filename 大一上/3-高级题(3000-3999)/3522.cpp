#include <bits/stdc++.h>
using namespace std;

int main() {
    size_t n;
    cin >> n;
    vector<int> top(n);
    vector<int> bottom(n);
    for (size_t i = 0; i < n; i++) {
        cin >> top[i];
    }
    for (size_t i = 0; i < n; i++) {
        cin >> bottom[i];
    }
    int min_top = *min_element(top.begin(), top.end());
    int max_bottom = *max_element(bottom.begin(), bottom.end());
    if (min_top <= max_bottom) {
        cout << "No " << max_bottom - min_top + 1<< endl;
    } else {
        cout << "Yes " << min_top - max_bottom << endl;
    }
    return 0;
}