#include <bits/stdc++.h>

using namespace std;

int main() {
	int t, tot;
	int a_b_win = 0, a_c_win = 0, a_j_win = 0;
	int b_b_win = 0, b_c_win = 0, b_j_win = 0; 
	int tie = 0;
	cin >> t;
	tot = t;
	while (t--) {
		char a, b;
		cin >> a >> b;
		if (a == b) {
			tie++;
		}
		else if (a == 'B' && b == 'C') {
			a_b_win++;
		}
		else if (a == 'C' && b == 'B') {
			b_b_win++;
		}
		else if (a == 'J' && b == 'B') {
			a_j_win++;
		}
		else if (a == 'B' && b == 'J') {
			b_j_win++;
		}
		else if (a == 'C' && b == 'J') {
			a_c_win++;
		}
		else if (a == 'J' && b == 'C') {
			b_c_win++;
		}
	}
	int a_tot = a_b_win + a_c_win + a_j_win, b_tot = b_b_win + b_c_win + b_j_win;
	cout << a_tot << ' ' << tie << ' ' << tot - tie - a_tot << endl;
	cout << b_tot << ' ' << tie << ' ' << tot - tie - b_tot << endl;
	int a_max = max({a_b_win, a_c_win, a_j_win});
	int b_max = max({b_b_win, b_c_win, b_j_win});
	if (a_max == a_b_win) {
		cout << "B ";
	}
	else if (a_max == a_c_win) {
		cout << "C ";
	}
	else {
		cout << "J ";
	}
	if (b_max == b_b_win) {
		cout << 'B';
	}
	else if (b_max == b_c_win) {
		cout << 'C';
	}
	else {
		cout << 'J';
	}
	cout << endl;
}