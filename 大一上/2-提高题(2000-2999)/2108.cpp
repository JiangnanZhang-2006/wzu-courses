#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    string c;

    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        getline(cin, c);                                //使用cin函数会导致空格和标点不能被输入
        for (int j = 0; j < c.length(); j++) {          //对于string创建的变量不能使用lenstr()
            char temp = c[j];
            if ('a' <= temp && temp <= 'z') {
                cout << (int)temp - (int)'a' + 1;
            }
            else if ('A' <= temp && temp <= 'Z') {
                cout << (int)temp - (int)'A' + 27;
            }
            else {
                cout << temp;
            }
        }
        cout << endl;
    }
    return 0;
}