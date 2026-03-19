#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long cnt = 0;
    cin >> n;
    vector<int> input(n);
    vector<int> vec;
    for (int i = 0; i < n; ++i) {
        cin >> input[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                int temp = input[i] * 10 + input[j];
                if (find(vec.begin(), vec.end(), temp) == vec.end()) {
                    vec.push_back(temp);
                    cnt += temp;
                }
            }
        }
    }
    cout << cnt << endl;
}