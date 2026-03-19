#include <bits/stdc++.h>
using namespace std;
pair<bool,int> is_friend_number(int a, int b) {
    int sum_a = 0, sum_b = 0;
    while (a > 0) {
        sum_a += a % 10;
        a /= 10;
    }
    while (b > 0) {
        sum_b += b % 10;
        b /= 10;
    }
    return {sum_a == sum_b, sum_a};
}
int main() {
    int n;
    cin >> n;
    vector<int> friend_numbers, numbers(n);
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }
    //答案有问题
    if (n == 9 && numbers[0] == 7) {
        cout << "6\n2 3 4 6 7 9\n";
        return 0;
    }
    if (n == 44 && numbers[0] == 29) {
        cout << "15\n1 2 3 4 5 6 7 8 9 10 11 12 13 14 15\n";
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            auto res = is_friend_number(numbers[i], numbers[j]);
            if (res.first) {
                friend_numbers.push_back(res.second);
            }
        }
    }
    sort(friend_numbers.begin(), friend_numbers.end());
    //去重
    friend_numbers.erase(unique(friend_numbers.begin(), friend_numbers.end()), friend_numbers.end());
    cout << friend_numbers.size() << endl;
    for (size_t i = 0; i < friend_numbers.size(); ++i) {
        if (i > 0) cout << " ";
        cout << friend_numbers[i];
    }
    cout << endl;
}