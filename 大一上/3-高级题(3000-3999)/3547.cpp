#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

string roundMethod1(const string& num, int d) {
    // 四舍五入
    size_t dotPos = num.find('.');
    if (dotPos == string::npos) {
        // 没有小数点，直接返回并补0
        return num + "." + string(d, '0');
    }
    
    string intPart = num.substr(0, dotPos);
    string decPart = num.substr(dotPos + 1);
    
    // 如果小数位数不足D位，直接补0
    if (decPart.length() <= static_cast<size_t>(d)) {
        return num + string(d - static_cast<int>(decPart.length()), '0');
    }
    
    // 需要舍入
    string result = intPart + "." + decPart.substr(0, d);
    int checkPos = d; // 检查第d+1位（索引为d）
    
    if (decPart[checkPos] >= '5') {
        // 需要进位
        bool carry = true;
        for (int i = d - 1; i >= 0 && carry; i--) {
            if (result[dotPos + 1 + i] < '9') {
                result[dotPos + 1 + i]++;
                carry = false;
            } else {
                result[dotPos + 1 + i] = '0';
            }
        }
        
        // 如果小数部分全部进位，需要向整数部分进位
        if (carry) {
            for (int i = intPart.length() - 1; i >= 0 && carry; i--) {
                if (result[i] < '9') {
                    result[i]++;
                    carry = false;
                } else {
                    result[i] = '0';
                }
            }
            if (carry) {
                result = "1" + result;
                dotPos++; // 小数点位置后移
            }
        }
    }
    
    return result;
}

string roundMethod2(const string& num, int d) {
    // 截断
    size_t dotPos = num.find('.');
    if (dotPos == string::npos) {
        return num + "." + string(d, '0');
    }
    
    string intPart = num.substr(0, dotPos);
    string decPart = num.substr(dotPos + 1);
    
    if (decPart.length() <= static_cast<size_t>(d)) {
        return num + string(d - static_cast<int>(decPart.length()), '0');
    }
    
    return intPart + "." + decPart.substr(0, d);
}

string roundMethod3(const string& num, int d) {
    // 四舍六入五成双
    size_t dotPos = num.find('.');
    if (dotPos == string::npos) {
        return num + "." + string(d, '0');
    }
    
    string intPart = num.substr(0, dotPos);
    string decPart = num.substr(dotPos + 1);
    
    if (decPart.length() <= static_cast<size_t>(d)) {
        return num + string(d - static_cast<int>(decPart.length()), '0');
    }
    
    string result = intPart + "." + decPart.substr(0, d);
    int checkPos = d; // 第d+1位
    
    char checkDigit = decPart[checkPos];
    
    if (checkDigit < '5') {
        // 小于5，直接舍去
        return result;
    } else if (checkDigit > '5') {
        // 大于5，进位
        bool carry = true;
        for (int i = d - 1; i >= 0 && carry; i--) {
            if (result[dotPos + 1 + i] < '9') {
                result[dotPos + 1 + i]++;
                carry = false;
            } else {
                result[dotPos + 1 + i] = '0';
            }
        }
        if (carry) {
            for (int i = intPart.length() - 1; i >= 0 && carry; i--) {
                if (result[i] < '9') {
                    result[i]++;
                    carry = false;
                } else {
                    result[i] = '0';
                }
            }
            if (carry) {
                result = "1" + result;
                dotPos++;
            }
        }
        return result;
    } else {
        // 等于5，需要检查后面是否有非0数字
        bool hasNonZero = false;
        for (size_t i = checkPos + 1; i < decPart.length(); i++) {
            if (decPart[i] != '0') {
                hasNonZero = true;
                break;
            }
        }
        
        if (hasNonZero) {
            // 5后面有非0数字，进位
            bool carry = true;
            for (int i = d - 1; i >= 0 && carry; i--) {
                if (result[dotPos + 1 + i] < '9') {
                    result[dotPos + 1 + i]++;
                    carry = false;
                } else {
                    result[dotPos + 1 + i] = '0';
                }
            }
            if (carry) {
                for (int i = intPart.length() - 1; i >= 0 && carry; i--) {
                    if (result[i] < '9') {
                        result[i]++;
                        carry = false;
                    } else {
                        result[i] = '0';
                    }
                }
                if (carry) {
                    result = "1" + result;
                    dotPos++;
                }
            }
            return result;
        } else {
            // 5后面都是0，看第d位是单数还是双数
            char lastDigit = result[dotPos + d]; // 第d位（最后保留的一位）
            int lastDigitValue = lastDigit - '0';
            
            if (lastDigitValue % 2 == 1) {
                // 单数，进位
                bool carry = true;
                for (int i = d - 1; i >= 0 && carry; i--) {
                    if (result[dotPos + 1 + i] < '9') {
                        result[dotPos + 1 + i]++;
                        carry = false;
                    } else {
                        result[dotPos + 1 + i] = '0';
                    }
                }
                if (carry) {
                    for (int i = intPart.length() - 1; i >= 0 && carry; i--) {
                        if (result[i] < '9') {
                            result[i]++;
                            carry = false;
                        } else {
                            result[i] = '0';
                        }
                    }
                    if (carry) {
                        result = "1" + result;
                        dotPos++;
                    }
                }
            }
            // 双数，直接舍去（已经是result了）
            return result;
        }
    }
}

int main() {
    int n, d;
    cin >> n >> d;
    
    for (int i = 0; i < n; i++) {
        int method;
        string num;
        cin >> method >> num;
        
        string result;
        if (method == 1) {
            result = roundMethod1(num, d);
        } else if (method == 2) {
            result = roundMethod2(num, d);
        } else {
            result = roundMethod3(num, d);
        }
        
        cout << result << endl;
    }
    
    return 0;
}

