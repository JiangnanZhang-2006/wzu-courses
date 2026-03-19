#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
    size_t n, m;
    cin >> n >> m;
    vector<int> vec(n, 0);
    for (size_t i = 0; i < m; i++) {
        for (size_t i = 0; i < n; i++) {
            int temp;
            cin >> temp;
            vec[i] += temp;
        }
    }
    int max_value = INT_MIN;
    for (int i : vec) {
        if (i > max_value) {
            max_value = i;
        }
    }
    cout << max_value << endl;
    bool is_first = true;
    for (size_t i = 0; i < n; i++) {
        if (vec[i] == max_value) {
            if (is_first) {
                cout << i + 1;
                is_first = false;
            } else {
                cout << ' ' << i + 1;
            }
        }
    }
    cout << endl;
    return 0;
}