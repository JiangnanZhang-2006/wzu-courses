#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        list<pair<string, int>> mylst;
        string temp;
        cin >> temp;
        //转大写
        for (char &c : temp) {
            c = toupper(c);
        }
        while (temp != "#") {
            //查询是否有temp
            auto it = find_if(mylst.begin(), mylst.end(),
                [&temp](const pair<string, int>& pos) {
                    return pos.first == temp;
                });
            if (it == mylst.end()) {
                //未找到， 添加
                mylst.push_back({ temp, 1 });
            }
            else {
                it->second++;
            }
            cin >> temp;
            for (char& c : temp) {
                c = toupper(c);
            }
        }
        mylst.sort();
        cout << mylst.size() << endl;
        for (const pair<string, int> i : mylst) {
            cout << i.first << ' ' << i.second << endl;
        }
    }
    return 0;
}