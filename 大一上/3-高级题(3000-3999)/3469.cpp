#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    if (N == 0) {
        cout << 0 << endl << endl;
        return 0;
    }


    vector<int> left_max(N);
    left_max[0] = A[0];
    for (int i = 1; i < N; ++i) {
        left_max[i] = max(left_max[i - 1], A[i]);
    }

    vector<int> right_min(N);
    right_min[N - 1] = A[N - 1];
    for (int i = N - 2; i >= 0; --i) {
        right_min[i] = min(right_min[i + 1], A[i]);
    }

    vector<int> ans;
    for (int i = 0; i < N; ++i) {
        if (A[i] >= left_max[i] && A[i] <= right_min[i]) {
            ans.push_back(A[i]);
        }
    }

    cout << ans.size() << endl;
    for (size_t i = 0; i < ans.size(); ++i) {
        if (i > 0) cout << " ";
        cout << ans[i];
    }
    cout << endl;  
    return 0;
}