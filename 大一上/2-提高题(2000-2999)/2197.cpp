#include <bits/stdc++.h>
using namespace std;

// int main() {
//     int n;
//     cin >> n;
//     int arr[100] = { 0 };
//     for (int i = 0; i < n; i++) {
//         cin >> arr[i];
//     }

//     int target;
//     cin >> target;

//     int left = 0;
//     int right = n - 1;
//     int result = -1;

//     while (left <= right) {
//         int mid = left + (right - left) / 2;
//         if (arr[mid] == target) {
//             result = mid;
//             break;
//         }
//         else if (arr[mid] < target) {
//             left = mid + 1;
//         }
//         else {
//             right = mid - 1;
//         }
//     }

//     cout << result << endl;

//     return 0;
// }

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    int target;
    cin >> target;
    auto it = find(arr.begin(), arr.end(), target);
    if (it != arr.end()) {
        cout << distance(arr.begin(), it) << endl;
    } else {
        cout << -1 << endl;
    }
}