#include <bits/stdc++.h>

using namespace std;

string baseConvert(string input, int current, int target) {  

    map<int, char> encode_dic;
    map<char, int> decode_dic;
    bool isNegetive = input[0] == '-';
    if (isNegetive) {
        input = input.substr(1);
    }
    for (int i = 0; i < 10; i++) {          //0-9
        encode_dic[i] = '0' + i;
        decode_dic['0' + i] = i;
    }

    for (int i = 0; i < 24; i++) {          //A-Z
        encode_dic[i + 10] = 'A' + i;
        decode_dic['A' + i] = i + 10;
        decode_dic['a' + i] = i + 10;
    }

    int ans_d = 0;

    for (int i = 0; i < input.length(); i++) {
        int temp = decode_dic[input[i]];
        ans_d *= current;
        ans_d += temp;
    }

    if (ans_d == 0) {
        return "0";
    }
    string ans_s = "";

    while (ans_d > 0) {
        ans_s = encode_dic[ans_d % target] + ans_s;
        ans_d /= target;
    }
    if (isNegetive) {
        return '-' + ans_s;
    }
    else {
        return ans_s;
    }

}

int main() {
    map<string, char> decode_right;
    decode_right["tret"] = '0';
    decode_right["jan"] = '1';
    decode_right["feb"] = '2';
    decode_right["mar"] = '3';
    decode_right["apr"] = '4';
    decode_right["may"] = '5';
    decode_right["jun"] = '6';
    decode_right["jly"] = '7';
    decode_right["aug"] = '8';
    decode_right["sep"] = '9';
    decode_right["oct"] = 'A';
    decode_right["nov"] = 'B';
    decode_right["dec"] = 'C';

    map<string, char> decode_left;
    decode_left["tret"] = '0';
    decode_left["tam"] = '1';
    decode_left["hel"] = '2';
    decode_left["maa"] = '3';
    decode_left["huh"] = '4';
    decode_left["tou"] = '5';
    decode_left["kes"] = '6';
    decode_left["hei"] = '7';
    decode_left["elo"] = '8';
    decode_left["syy"] = '9';
    decode_left["lok"] = 'A';
    decode_left["mer"] = 'B';
    decode_left["jou"] = 'C';

    map<char, string> encode_right;
    map<char, string> encode_left;
    
    //反转
    for (auto pair : decode_right) {
        encode_right[pair.second] = pair.first;
    }

    for (auto pair : decode_left) {
        encode_left[pair.second] = pair.first;
    }

    int n;
    cin >> n;
    cin.ignore();
    while (n--) {
        string s;
        getline(cin, s);
        if (isdigit(s[0])) {
            string temp = baseConvert(s, 10, 13);
            if (temp.size() == 1) {
                cout << encode_right[temp[0]] << endl;
            }
            else {
                if (temp[1] == '0') {
                    cout << encode_left[temp[0]] << endl;
                }
                else {
                    cout << encode_left[temp[0]] << ' ' << encode_right[temp[1]] << endl;
                }
            }
        }
        else {
            string temp = "";
            if (s.size() == 3) {
                if (find_if(decode_left.begin(), decode_left.end(), [s](auto ss) {return ss.first == s;}) != decode_left.end()) {
                    temp += decode_left[s];
                    temp += '0';
                }
                else {
                    temp += decode_right[s];
                }
            }
            else {
                string s1 = s.substr(0, 3), s2 = s.substr(4, 3);
                temp += decode_left[s1];
                temp += decode_right[s2];
            }
            cout << baseConvert(temp, 13, 10) << endl;
        }
    }
}