#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<string> parseSymbols(const string& line) {
    vector<string> symbols;
    
    for (size_t i = 0; i < line.length(); i++) {
        if (line[i] == '[') {
            // 寻找匹配的']'
            size_t j = i + 1;
            int bracket_count = 1;
            
            while (j < line.length() && bracket_count > 0) {
                if (line[j] == '[') bracket_count++;
                else if (line[j] == ']') bracket_count--;
                j++;
            }
            
            if (bracket_count == 0) {
                // 提取括号内容
                string symbol = line.substr(i + 1, j - i - 2);
                symbols.push_back(symbol);
            }
            
            i = j - 1;  // 跳过已处理的部分
        }
    }
    
    return symbols;
}

int main() {
    // 读取三行符号集
    vector<string> hands, eyes, mouths;
    
    for (int i = 0; i < 3; i++) {
        string line;
        getline(cin, line);
        
        vector<string> symbols = parseSymbols(line);
        
        switch(i) {
            case 0: hands = symbols; break;
            case 1: eyes = symbols; break;
            case 2: mouths = symbols; break;
        }
    }
    
    // 读取请求数量
    int K;
    cin >> K;
    
    // 处理每个请求
    for (int i = 0; i < K; i++) {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;
        
        // 检查序号有效性
        bool valid = true;
        
        // 注意：序号从1开始
        if (a < 1 || a > hands.size()) valid = false;
        if (b < 1 || b > eyes.size()) valid = false;
        if (c < 1 || c > mouths.size()) valid = false;
        if (d < 1 || d > eyes.size()) valid = false;
        if (e < 1 || e > hands.size()) valid = false;
        
        if (!valid) {
            cout << "Are you kidding me? @\\/@" << endl;
        } else {
            // 输出表情（注意：序号要减1转换为索引）
            cout << hands[a-1] << "(" 
                 << eyes[b-1] << mouths[c-1] << eyes[d-1] << ")" 
                 << hands[e-1] << endl;
        }
    }
    
    return 0;
}