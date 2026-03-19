#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	while (n--) {
		int num, count = 1, temp = 1;
		cin >> num;
		for (int a = 0; a < num; a++) {
			for (int i = num; i > temp - 1; i--) {
				cout << count << ' ';
				count += i;
			}
			count = ++temp;
			cout << endl;
		}

	}
}