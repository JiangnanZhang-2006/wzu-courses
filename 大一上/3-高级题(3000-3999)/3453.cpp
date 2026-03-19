#include <bits/stdc++.h>

using namespace std;

int main() {
	string s1, s2;
	vector<char> s;
	cin >> s1 >> s2;
	for (char& c : s1) {
		if (islower(c)) {
			c = c - 32;
		}
	}
	for (char& c : s2) {
		if (islower(c)) {
			c = c - 32;
		}
	}
	for (char c1 : s1) {
		bool isFind = false;
		for (char c2 : s2) {
			if (c1 == c2) {
				isFind = true;
				break;
			}
		}
		if (!isFind) {
			if (find(s.begin(), s.end(), c1) == s.end() ) {
				s.push_back(c1);
			}
			
		}
	}
	for (char c : s) {
		cout << c;
	}
	cout << endl;
}