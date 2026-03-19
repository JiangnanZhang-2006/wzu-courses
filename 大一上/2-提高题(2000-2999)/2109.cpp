#include <bits/stdc++.h>
using namespace std;

int main() {
	int T, left, right, ans;

	cin >> T;

	for (int t = 0; t < T; t++) {
		cin >> left >> right;
		bool flag = false;

		for (int i = left; i <= right; i++) {
			if ((i / 100) * (i / 100) * (i / 100) + (i / 10 % 10) * (i / 10 % 10) * (i / 10 % 10) + (i % 10) * (i % 10) * (i % 10) == i) {
				if (flag) {
					cout << ' ';
				}
				cout << i;
				flag = true;
			}
		}
		if (not flag) {
			cout << "no";
		}
		cout << endl;
	}
	return 0;
}