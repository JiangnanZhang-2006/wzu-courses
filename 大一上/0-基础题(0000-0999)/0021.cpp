#include <bits/stdc++.h>

using namespace std;

bool dic[10][7] = {
	{1, 1, 1, 0, 1, 1, 1},	//0
	{0, 0, 1, 0, 0, 1, 0},	//1
	{1, 0, 1, 1, 1, 0, 1},
	{1, 0, 1, 1, 0, 1, 1},
	{0, 1, 1, 1, 0, 1, 0},
	{1, 1, 0, 1, 0, 1, 1},
	{1, 1, 0, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 1, 0},
	{1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 0, 1, 1},	//9
};

int main() {
	int t;
	while (cin >> t && t != 0) {
		string s;
		cin >> s;
		for (int i = 0; i < s.size(); i++) {
			cout << (i?"  ":" ");
			for (int j = 0; j < t; j++) {
				cout << (dic[s[i] - '0'][0] ? "-" : " ");
			}
			cout << " ";
		}
		cout << endl;
		for (int i = 0; i < t; i++) {
			for (int j = 0; j < s.size(); j++) {
				cout << (j ? " " : "") << (dic[s[j] - '0'][1] ? "|" : " ");
				for (int k = 0; k < t; k++) {
					cout << ' ';
				}
				cout << (dic[s[j] - '0'][2] ? "|" : " ");
			}
			cout << endl;
		}
		for (int i = 0; i < s.size(); i++) {
			cout << (i ? "  " : " ");
			for (int j = 0; j < t; j++) {
				cout << (dic[s[i] - '0'][3] ? "-" : " ");
			}
			cout << " ";
		}
		cout << endl;
		for (int i = 0; i < t; i++) {
			for (int j = 0; j < s.size(); j++) {
				cout << (j ? " " : "") << (dic[s[j] - '0'][4] ? "|" : " ");
				for (int k = 0; k < t; k++) {
					cout << ' ';
				}
				cout << (dic[s[j] - '0'][5] ? "|" : " ");
			}
			cout << endl;
		}
		for (int i = 0; i < s.size(); i++) {
			cout << (i ? "  " : " ");
			for (int j = 0; j < t; j++) {
				cout << (dic[s[i] - '0'][6] ? "-" : " ");
			}
			cout << " ";
		}
		cout << endl << endl;
	}
}