#include <bits/stdc++.h>

using namespace std;

map<int, vector<int> > dic;

static bool judge(int input, int sum);
static int count(int input);

int main() {
	for (int i = 2; i < 1000; i++) {						//init
		dic[i] = vector<int>{};
	}

	for (int i = 2; i < 1000; i++) {
		if (count(i) == i) {
			cout << i << " its factors are ";
			for (int j = 0; j < dic[i].size(); j++) {
				cout << dic[i][j] << ' ';
			}
			cout << endl;

		}
	}
	return 0;
}

static int count(int input) {
	int sum = 0;
	for (int i = 1; i < input; i++) {
		if (judge(i, input)) {
			sum += i;
			dic[input].push_back(i);
		}
	}

	return sum;
}

static bool judge(int input, int sum) {
	return sum % input == 0;
}