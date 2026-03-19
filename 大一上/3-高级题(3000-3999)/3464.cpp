#include <bits/stdc++.h>

using namespace std;

int main() {
    string s;
    getline(cin, s);
    
    int len = s.size();
    vector<int> input;
    
    for (char &c : s) {
        if (c == 'P') input.push_back(0);
        else if (c == 'A') input.push_back(1);
        else if (c == 'T') input.push_back(2);
    }
    
    unsigned long long total = 0;
    int p_cnt = 0, a_cnt = 0, t_cnt = 0;
    //当到A时，前面的P的个数*后面的T的个数->ans
    for (int i = 0; i < len; i++) {
        if (input[i] == 2) t_cnt++;
    }
    
    for (int i = 0; i < len; i++) {
        if (input[i] == 0) { 
            p_cnt++;
        }
        else if (input[i] == 1) {
            a_cnt++;
        }
        else if (input[i] == 2) {
            t_cnt--;
        }
        
        if (input[i] == 1) {
            total += p_cnt * t_cnt;
        }
    }
    
    cout << total % 1000000007 << endl;
    
    return 0;
}