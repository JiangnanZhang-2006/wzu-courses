#include <bits/stdc++.h>

using namespace std;

static int sum(int input);

int main() {
	int n;
	cin >> n;
	for (int i = 10; i <= n; i++) {
		if (i % sum(i) == 0) {
			cout << i << endl;
		}
	}
}

int sum(int input) {
	int sum_ = 0;
	while (input > 0) {
		sum_ += input % 10;
		input /= 10;
	}
	return sum_;
}