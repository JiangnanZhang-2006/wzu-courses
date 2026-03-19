#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<vector<vector<char>>> dic(26, vector<vector<char>>(7, vector<char>(5)));
    for (int c = 0; c < 26; c++) {
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 5; j++) {
                cin >> dic[c][i][j];
            }
        }
    }
    string s, temp;
    cin.ignore();
    getline(cin, s);
    
    bool hasOutput = false;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            temp += s[i];
        } else {
            if (!temp.empty()) {
                if (hasOutput) {
                    cout << endl;
                }
                for (int j = 0; j < 7; j++) {
                    for (int k = 0; k < temp.size(); k++) {
                        for (int l = 0; l < 5; l++) {
                            cout << dic[temp[k] - 'A'][j][l];
                        }
                        if (k != temp.size() - 1) {
                            cout << ' ';
                        }
                    }
                    cout << endl;
                }
                temp = "";
                hasOutput = true;
            }
        }
    }
    if (!temp.empty()) {
        if (hasOutput) {
            cout << endl;
        }
        for (int j = 0; j < 7; j++) {
            for (int k = 0; k < temp.size(); k++) {
                for (int l = 0; l < 5; l++) {
                    cout << dic[temp[k] - 'A'][j][l];
                }
                if (k != temp.size() - 1) {
                    cout << ' ';
                }
            }
            cout << endl;
        }
    }
    return 0;
}