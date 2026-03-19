#include <bits/stdc++.h>
using namespace std;

int main() {
    unordered_map<string, string> dic;
    dic["Jan"] = "01";
    dic["Feb"] = "02";
    dic["Mar"] = "03";
    dic["Apr"] = "04";
    dic["May"] = "05";
    dic["Jun"] = "06";
    dic["Jul"] = "07";
    dic["Aug"] = "08";
    dic["Sep"] = "09";
    dic["Oct"] = "10";
    dic["Nov"] = "11";
    dic["Dec"] = "12";
    int t;
    cin >> t;
    cin.ignore();
    while (t--) {
        string s; //Jan 1, 2000
        getline(cin, s);
        //split
        string year, month, day;
        int comma_pos = s.find(',');
        month = s.substr(0, 3);
        day = s.substr(4, comma_pos - 4);
        year = s.substr(comma_pos + 2);
        if (day.size() == 1) {
            day = "0" + day;
        }
        if (year.size() < 4) {
            int len = year.size();
            for (int i = 0; i < 4 - len; i++) {
                year = "0" + year;
            }
        } else {
            year = year.substr(0, 4);
        }
        string temp = year + dic[month] + day;
        string temp_reverse = temp;
        reverse(temp_reverse.begin(), temp_reverse.end());
        if (temp == temp_reverse) {
            cout << "Y " << temp << endl;
        } else {
            cout << "N " << temp << endl;
        }
    }
}