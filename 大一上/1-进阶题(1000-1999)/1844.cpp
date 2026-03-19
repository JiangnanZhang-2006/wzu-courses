#include <bits/stdc++.h>

using namespace std;

static string baseConvert(string input, int current, int target);
static int numberCount(string input);

int main()
{
    int t;
    cin >> t;
    while (t--) {
        string input;
        cin >> input;

        if (numberCount(input) == numberCount(baseConvert(input, 10, 12)) 
            && numberCount(input) == numberCount(baseConvert(input, 10, 16))) {
            cout << input << " is a Sky Number." << endl;
        }
        else {
            cout << input << " is not a Sky Number." << endl;
        }
    }
    return 0;
}

string baseConvert(string input, int current, int target) {  //目前只有正整数

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
int numberCount(string input) {
    map<int, char> encode_dic;
    map<char, int> decode_dic;

    for (int i = 0; i < 10; i++) {          //0-9
        encode_dic[i] = '0' + i;
        decode_dic['0' + i] = i;
    }

    for (int i = 0; i < 24; i++) {          //A-Z
        encode_dic[i + 10] = 'A' + i;
        decode_dic['A' + i] = i + 10;
        decode_dic['a' + i] = i + 10;
    }

    int ans = 0;
    for (int i = 0; i < input.length(); i++) {
        ans += decode_dic[input[i]];
    }
    return ans;
}