#include <bits/stdc++.h>

using namespace std;

int main() {
	vector<char> invalidChar;
	string invalidChars, input, output = "";
	getline(cin,invalidChars);
	getline(cin,input);
	for (char c : invalidChars) {
		if (c <= '9' and c >= '0') {
			invalidChar.push_back(c);
		}
		else if (isupper(c)) {
			invalidChar.push_back(c);
			invalidChar.push_back(c + 32);
		}
		else if (islower(c)) {
			invalidChar.push_back(c);
			invalidChar.push_back(c - 32);
		}
		else if (c == ',' or c == '_' or c == '.' or c == '-') {
			invalidChar.push_back(c);
		}
		else if (c == '+') {
			for (int i = 65; i < 91; i++) {
				invalidChar.push_back(i);

			}
		}
	}
	for (char c : input) {
		if (find(invalidChar.begin(), invalidChar.end(), c) == invalidChar.end()) {
			output += c;
		}
	}
	cout << output << endl;
}