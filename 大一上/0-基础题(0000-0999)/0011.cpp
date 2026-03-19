#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

vector<int> phones;

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string temp;
		cin >> temp;
		int phone = 0;
		for (char c : temp) {
			int bit;
			if (c == '-') continue;
			c = toupper(c);
			if (c <= 'O' and c >= 'A') {
				bit = (c-'A') / 3 + 2;
			}
			else if (c == 'P' or c == 'R' or c == 'S') {
				bit = 7;
			}
			else if (c <= 'Y' and c >= 'T') {
				bit = (c-'T') / 3 + 8;
			}
			else {
				bit = c - '0';
			}
			phone = phone * 10 + bit;
		}
		phones.push_back(phone);
	}
	sort(phones.begin(), phones.end(), [](int a, int b) {return a < b;});
	bool find = false;
	int cnt = 1;
	for (size_t i = 0; i < phones.size() - 1; ++i) {
		if (phones[i] == phones[i + 1]) {
			cnt++;
			find = true;
		}
		else {
			if (cnt != 1) {
				cout << setw(3) << setfill('0') << phones[i] / 10000 << '-' << setw(4) << phones[i] % 10000;
				cout << ' ' << cnt << endl;
				cnt = 1;
			}
		}
	}
	if (cnt != 1) {
		cout << setw(3) << setfill('0') << phones[phones.size() - 2] / 10000 << '-' << setw(4) << phones[phones.size() - 2] % 10000;
		cout << ' ' << cnt << endl;
	}
	if (!find) {
		cout << "No duplicates." << endl;
	}
}