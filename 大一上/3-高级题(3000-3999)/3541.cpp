#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int main() {
    int n1, n2;
    cin >> n1 >> n2;
    
    vector<int> vec;
    // 初始化：从n1到n2（包含n2）
    for (int i = n1; i <= n2; ++i) {
        vec.push_back(i);
    }
    
    // 批量处理：如果有一个数字是两位数（>9），就对所有数据进行一次处理
    while (true) {
        // 检查是否有两位数（>9）
        bool has_two_digit = false;
        for (const int& num : vec) {
            if (num > 9) {
                has_two_digit = true;
                break;
            }
        }
        
        // 如果所有数字都是1位数，结束处理
        if (!has_two_digit) {
            break;
        }
        
        // 对所有数字进行一次处理
        for (int& num : vec) {
            // 步骤1：计算各位数的立方相乘
            int product;
            if (num == 0) {
                product = 0;  // 0的各位数立方相乘为0
            } else {
                product = 1;
                int temp = num;
                while (temp > 0) {
                    int digit = temp % 10;
                    product *= (digit * digit * digit);
                    temp /= 10;
                }
            }
            
            // 步骤2：计算结果的各位数之和
            num = 0;
            while (product > 0) {
                num += product % 10;
                product /= 10;
            }
        }
    }
    
    // 统计每个数字的出现次数
    map<int, int> count;
    for (const auto& num : vec) {
        count[num]++;
    }
    
    // 找出最大出现次数
    int max_count = 0;
    for (const auto& [num, cnt] : count) {
        max_count = max(max_count, cnt);
    }
    
    // 输出最大出现次数
    cout << max_count << endl;
    
    // 输出所有数字之王（按递增序）
    bool is_first = true;
    for (const auto& [num, cnt] : count) {
        if (cnt == max_count) {
            if (is_first) {
                cout << num;
                is_first = false;
            } else {
                cout << ' ' << num;
            }
        }
    }
    cout << endl;
    
    return 0;
}
