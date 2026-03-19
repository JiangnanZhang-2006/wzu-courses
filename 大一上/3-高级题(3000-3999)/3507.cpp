#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    if (!(cin >> n)) return 0;
    vector<int> back(n);  // 背面数字
    for (int i = 0; i < n; ++i) {
        cin >> back[i];
    }
    
    // 计算每张卡片的差值：正面数字是i+1，背面数字是back[i]
    map<int, int> diff_count;  // 差值 -> 出现次数
    for (int i = 0; i < n; ++i) {
        int front = i + 1;  // 正面数字
        int diff = abs(front - back[i]);  // 大减小，即绝对值
        diff_count[diff]++;
    }
    
    // 收集重复次数大于1的差值
    vector<pair<int, int>> result;
    for (const auto &[diff, count] : diff_count) {
        if (count > 1) {
            result.push_back({diff, count});
        }
    }
    
    // 按差值从大到小排序
    sort(result.begin(), result.end(), greater<pair<int, int>>());
    
    // 输出结果
    for (const auto &[diff, count] : result) {
        cout << diff << " " << count << "\n";
    }
    
    return 0;
}