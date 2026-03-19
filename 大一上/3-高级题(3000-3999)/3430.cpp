#include <iostream>

using namespace std;

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t / 100; i++) {
		cout << 'B';
	}
	for (int i = 0; i < t / 10 % 10; i++) {
		cout << 'S';
	}
	for (int i = 1; i <= t % 10; i++) {
		cout << i;
	}
	cout << endl;
}