#include <iostream>
#include <string>

using namespace std;

int main() {
    string s;
    cin >> s;
    
    // 提取符号
    char sign = s[0];
    
    // 找到小数点和E的位置
    size_t dot_pos = s.find('.');
    size_t e_pos = s.find('E');
    
    // 提取各部分
    string integer = s.substr(1, dot_pos - 1);
    string decimal = s.substr(dot_pos + 1, e_pos - dot_pos - 1);
    char exp_sign = s[e_pos + 1];
    int exp = stoi(s.substr(e_pos + 2));
    
    // 合并所有数字
    string num = integer + decimal;
    
    // 计算小数点应该移动到的位置
    int new_dot_pos;
    if (exp_sign == '+') {
        new_dot_pos = integer.length() + exp;
    } else {
        new_dot_pos = integer.length() - exp;
    }
    
    // 根据new_dot_pos构造结果
    if (new_dot_pos <= 0) {
        // 结果小于1
        cout << (sign == '-' ? "-" : "") << "0.";
        for (int i = 0; i < -new_dot_pos; i++) {
            cout << '0';
        }
        cout << num << endl;
    } else if (new_dot_pos >= num.length()) {
        // 结果是整数，没有小数部分
        cout << (sign == '-' ? "-" : "") << num;
        for (int i = 0; i < new_dot_pos - num.length(); i++) {
            cout << '0';
        }
        cout << endl;
    } else {
        // 有整数和小数部分
        cout << (sign == '-' ? "-" : "");
        for (int i = 0; i < new_dot_pos; i++) {
            cout << num[i];
        }
        cout << '.';
        for (int i = new_dot_pos; i < num.length(); i++) {
            cout << num[i];
        }
        cout << endl;
    }
    
    return 0;
}