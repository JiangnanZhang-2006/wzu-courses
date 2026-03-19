#include <bits/stdc++.h>

using namespace std;

int main() {
	int T;
	cin >> T;
	while (T--) {
		int m, max;
		cin >> m;
		int n;
		cin >> n;
		max = n; m--;
		while (m--) {
			cin >> n;
			if (n > max) {
				max = n;
			}
		}
		cout << max << endl;
	}
}