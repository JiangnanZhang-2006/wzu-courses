	#include <bits/stdc++.h>

	using namespace std;

	int main() {
		while (true) {
			int a, b;
			cin >> a >> b;
			if (a == 0 && b == 0) break;
			bool find = false;
			for (int i = a * 100; i < (a+1) * 100; i++) {
				if (i % b == 0) {
					cout << (find?" ":"") <<setw(2)<<setfill('0')<< i % 100;
					find = true;
				}
			}
			cout << endl;
		}
	}