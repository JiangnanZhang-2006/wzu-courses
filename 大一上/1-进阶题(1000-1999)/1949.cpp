#include <bits/stdc++.h>

using namespace std;

static bool judge(int input, int sum);
static int count(int input);

int main() {
	int M;
	cin >> M;

	for (int i = 0; i < M; i++) {
		int A, B;
		cin >> A >> B;

		if (count(A) == B && count(B) == A) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
}

static int count(int input) {
	int sum = 0;

	for (int i = 1; i < input; i++) {
		if (judge(i, input)) {
			sum += i;
		}
	}

	return sum;
}

static bool judge(int input, int sum) {
	return sum % input == 0;
}