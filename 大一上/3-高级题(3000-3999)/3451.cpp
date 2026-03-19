#include <iostream>

using namespace std;

int main() {
	int t, cnt = 1, len = 1, f = 1;
	char c;
	cin >> t >> c;
	if (t == 0) {
		cout << endl;
	}
	else {
		while (cnt + (f + 2) * 2 <= t) {
			cnt += (f + 2) * 2;
			len++;
			f += 2;
		}
		int numberOfSpace = 0;
		for (int i = f; i > 0; i -= 2) {
			for (int j = 0; j < numberOfSpace; j++) {
				cout << ' ';
			}
			numberOfSpace++;
			for (int j = 0; j < i; j++) {
				cout << c;
			}
			cout << endl;
		}
		numberOfSpace -= 2;
		for (int i = 3; i <= f; i += 2) {
			for (int j = 0; j < numberOfSpace; j++) {
				cout << ' ';
			}
			numberOfSpace--;
			for (int j = 0; j < i; j++) {
				cout << c;
			}
			cout << endl;
		}
		cout << t - cnt << endl;
	}
}