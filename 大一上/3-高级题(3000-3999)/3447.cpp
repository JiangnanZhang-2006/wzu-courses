#include <iostream>
#include <string>

using namespace std;

int main() {
	int dic[10] = { 0 };
	for (int i = 0; i < 10; i++) {
		cin >> dic[i];
	}
	int cur = 1;
	while (cur <= 9 && dic[cur] == 0) {
		cur++;
	}
	if (cur == 10) {
		cout << 0 << endl;
	}
	else {
		dic[cur]--;
		cout << cur;
		for (int i = 0; i < 10; i++) {
			for (int j = dic[i]; j > 0; j--) {
				cout << i;
			}
		}
	}
	cout << endl;
}