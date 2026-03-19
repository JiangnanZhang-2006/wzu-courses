#include <iostream>

using namespace std;

int main() {
	int a, b;
	bool flag = true;
	while (cin >> a >> b) {
		if (flag) {
			if (b == 0) {

			}
			else {
				cout << a * b << ' ' << b - 1;
				flag = false;
				continue;
			}
			
		}
		if (b == 0) {
			if (flag) {
				cout << "0 0";
			}
		}
		else {
			cout << ' ' << a * b << ' ' << b - 1;
		}
	}
	cout << endl;
}