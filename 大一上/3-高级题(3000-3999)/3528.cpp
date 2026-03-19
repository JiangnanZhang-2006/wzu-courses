#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    a = abs(a); b = abs(b);
    while (b) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// 生成所有K位数字，末尾c个9，前面K-c位的数字之和为rem
// 并且倒数第c+1位不能是9（如果c > 0且c < K）
void generate_numbers(int K, int rem, int c, vector<string> &out) {
    if (c > K) return;
    if (c == K) {
        if (rem == 0) {
            out.push_back(string(K, '9'));
        }
        return;
    }
    
    int left = K - c;
    if (rem < 0 || rem > 9 * left) return;
    
    string cur(left, '0');
    function<void(int, int)> dfs = [&](int pos, int remain) {
        if (pos == left) {
            if (remain == 0) {
                string s = cur;
                s.append(c, '9');
                out.push_back(s);
            }
            return;
        }
        int minD = (pos == 0 ? 1 : 0);  // 第一位不能是0
        // 如果是倒数第c+1位（即pos == left - 1），且c > 0，不能是9
        int maxD = (pos == left - 1 && c > 0) ? 8 : 9;
        // 计算后面位置能提供的最大数字和
        int maxFuture = (pos < left - 1) ? (9 * (left - pos - 1)) : 0;
        int minAllowed = max(minD, remain - maxFuture);
        int maxAllowed = min(maxD, remain);
        if (maxAllowed < minAllowed) return;
        for (int d = minAllowed; d <= maxAllowed; ++d) {
            cur[pos] = char('0' + d);
            dfs(pos + 1, remain - d);
        }
    };
    dfs(0, rem);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (!(cin >> t)) return 0;
    for (int case_num = 1; case_num <= t; ++case_num) {
        cout << "Case " << case_num << "\n";
        int K, m;
        if (!(cin >> K >> m)) break;
        
        vector<pair<int, string>> sols;  // (n, A)
        
        // 枚举A末尾有多少个9
        for (int c = 0; c <= K; ++c) {
            // 如果A末尾有c个9，那么A+1时：
            // - 末尾c个9变成0，贡献减少9*c
            // - 倒数第c+1位加1，贡献增加1
            // 所以 n = m + 1 - 9*c
            int n = m + 1 - 9 * c;
            
            // 检查n是否合理
            if (n < 1) continue;
            
            // 检查gcd(m, n)是否满足条件
            int g = gcd(m, n);
            if (g > 2 && is_prime(g)) {
                // 生成所有满足条件的A：末尾c个9，前面K-c位的数字之和为m-9*c
                // 并且倒数第c+1位不能是9（否则会继续进位）
                int rem = m - 9 * c;
                if (rem < 0) continue;
                
                vector<string> tmp;
                generate_numbers(K, rem, c, tmp);
                
                for (auto &A : tmp) {
                    sols.emplace_back(n, A);
                }
            }
        }
        
        if (sols.empty()) {
            cout << "No Solution\n";
        } else {
            // 先按n递增，再按A递增排序
            sort(sols.begin(), sols.end(), [](const auto &a, const auto &b) {
                if (a.first != b.first) return a.first < b.first;
                return a.second < b.second;
            });
            for (const auto &p : sols) {
                cout << p.first << " " << p.second << "\n";
            }
        }
    }
    return 0;
}