#include <bits/stdc++.h>
using namespace std;

vector<double> arr;

int main() {
    int t;
    string s;
    cin >> t;
    cin.ignore(); // 忽略换行符
    getline(cin, s);
    
    stringstream ss(s);
    string token;
    
    while (ss >> token) {
        bool is_legal = true;
        int dot_count = 0;
        int dot_pos = -1;
        
        // 检查每个字符的合法性
        for (int i = 0; i < token.length(); i++) {
            if (token[i] == '-') {
                // 负号只能在开头
                if (i != 0) {
                    is_legal = false;
                    break;
                }
            } else if (token[i] == '.') {
                dot_count++;
                dot_pos = i;
                if (dot_count > 1) {
                    is_legal = false;
                    break;
                }
            } else if (!isdigit(token[i])) {
                is_legal = false;
                break;
            }
        }
        
        // 检查小数点后位数
        if (is_legal && dot_pos != -1) {
            int decimal_digits = token.length() - dot_pos - 1;
            if (decimal_digits > 2) {
                is_legal = false;
            }
        }
        
        if (is_legal) {
            try {
                double num = stod(token);
                if (num >= -1000 && num <= 1000) {
                    arr.push_back(num);
                } else {
                    is_legal = false;
                }
            } catch (...) {
                is_legal = false;
            }
        }
        
        if (!is_legal) {
            cout << "ERROR: " << token << " is not a legal number" << endl;
        }
    }
    
    if (arr.size() > 0) {
        double sum = 0;
        for (double i : arr) {
            sum += i;
        }
        cout << "The average of " << arr.size() << " number" 
             << (arr.size() == 1 ? "" : "s") << " is " 
             << fixed << setprecision(2) << sum / arr.size() << endl;
    } else {
        cout << "The average of 0 numbers is Undefined" << endl;
    }
    
    return 0;
}