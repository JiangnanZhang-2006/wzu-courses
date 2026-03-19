
#include <bits/stdc++.h>

using namespace std;

int main() {
	int t;
	char a;
	cin >> t >> a;
	for (int i = 0; i < t; i++) {
		cout << a;
	}
	cout << endl;
	for (int i = 0; i < (int)(t / 2.0 + 0.5) - 2; i++) {
		cout << a;
		for (int j = 0; j < t - 2; j++) {
			cout << ' ';
		}
		cout << a << endl;
	}
	for (int i = 0; i < t; i++) {
		cout << a;
	}
	cout << endl;
}