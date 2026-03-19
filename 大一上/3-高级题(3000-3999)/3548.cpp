#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;
	int a = 1, b = 1, c;
	while (b <= n) {
		c = a + b;
		a = b;
		b = c;
	}
	if (n - a <= b - n) {
		cout << a;
	}
	else {
		cout << b;
	}
	cout << endl;
}