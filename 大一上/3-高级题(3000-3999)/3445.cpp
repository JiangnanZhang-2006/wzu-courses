#include <iostream>
#include <string>

using namespace std;

int dic[10] = { 0 };

int main() {
	string s;
	cin >> s;
	for (const char& c : s) {
		dic[c - '0']++;
	}
	for (int i = 0; i < 10; i++) {
		if (dic[i] != 0) {
			cout << i << ':' << dic[i] << endl;
		}
	}
}