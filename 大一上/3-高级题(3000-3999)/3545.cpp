#include <iostream>
#include <string>
using namespace std;

bool isLuckyNumber(const string& num) {
    int len = num.length();
    
    // 如果只有一位数字，0-9都是好运数
    if (len == 1) {
        return true;
    }
    
    // 从第一个字符开始，逐步添加后面的字符
    long long current = 0;
    for (int i = 0; i < len; i++) {
        current = current * 10 + (num[i] - '0');
        int digits = i + 1; // 当前数字的位数
        
        // 检查是否能被位数整除
        if (current % digits != 0) {
            return false;
        }
    }
    
    return true;
}

int main() {
    int k;
    cin >> k;
    
    for (int i = 0; i < k; i++) {
        string num;
        cin >> num;
        
        if (isLuckyNumber(num)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    
    return 0;
}

