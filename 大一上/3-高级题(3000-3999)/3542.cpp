#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>
#include <iomanip>
using namespace std;
unordered_map<string, int> dic;
int main() {
    //init
    dic["ling"] = 0;
    dic["yi"] = 1;
    dic["er"] = 2;
    dic["san"] = 3;
    dic["si"] = 4;
    dic["wu"] = 5;
    dic["liu"] = 6;
    dic["qi"] = 7;
    dic["ba"] = 8;
    dic["jiu"] = 9;
    long long ans = 0;
    for (int i = 0; i < 11; ++i) {
        string s;
        getline(cin, s);
        if (s.size() > 4 && s.substr(0, 4) == "sqrt") {
            int num = stoi(s.substr(4));
            int sqr = sqrt(num);
            ans = ans * 10 + sqr;
            continue;
        }
        if (dic.find(s) != dic.end()) {
            ans = ans * 10 + dic[s];
            continue;
        }
        auto _operator = s.find_first_not_of("0123456789");
        if (_operator != string::npos) {
            if (s[_operator] == '+') {
                ans = ans * 10 + stoi(s.substr(0, _operator)) + stoi(s.substr(_operator + 1));
            }
            else if (s[_operator] == '-') {
                ans = ans * 10 + stoi(s.substr(0, _operator)) - stoi(s.substr(_operator + 1));
            }
            else if (s[_operator] == '*') {
                ans = ans * 10 + stoi(s.substr(0, _operator)) * stoi(s.substr(_operator + 1));
            }
            else if (s[_operator] == '/') {
                ans = ans * 10 + stoi(s.substr(0, _operator)) / stoi(s.substr(_operator + 1));
            }   
            else if (s[_operator] == '%') {
                ans = ans * 10 + stoi(s.substr(0, _operator)) % stoi(s.substr(_operator + 1));
            }
            else if (s[_operator] == '^') {
                ans = ans * 10 + static_cast<int>(pow(stoi(s.substr(0, _operator)), stoi(s.substr(_operator + 1))));
            }
            continue;
        }
        ans = ans * 10 + stoi(s);
    }
    cout << setw(11) << setfill('0') << ans << endl;
    return 0;
}