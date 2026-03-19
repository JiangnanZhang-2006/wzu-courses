#include <iostream>
#include <string>

using namespace std;

bool judge(string s);

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        if (judge(s)) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
    return 0;
}

bool judge(string s) {
    // 检查是否只包含 P, A, T
    for (char c : s) {
        if (!(c == 'P' || c == 'A' || c == 'T')) {
            return false;
        }
    }

    // 找到 P 和 T 的位置
    int p_pos = -1, t_pos = -1;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'P') {
            if (p_pos == -1) {
                p_pos = i;
            }
            else {
                return false; // 多个 P
            }
        }
        else if (s[i] == 'T') {
            if (t_pos == -1) {
                t_pos = i;
            }
            else {
                return false; // 多个 T
            }
        }
    }

    if (p_pos == -1 || t_pos == -1 || p_pos >= t_pos) {
        return false;
    }

    int a = p_pos; 
    int b = t_pos - p_pos - 1; 
    int c = s.size() - t_pos - 1; 

    if (b == 0) {
        return false; 
    }

    return a * b == c;
}