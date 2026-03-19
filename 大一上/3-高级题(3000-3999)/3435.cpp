#include <iostream>

using namespace std;

int main() {
	long long a, b, c;
	int t, cnt = 1;
	cin >> t;
	while (t--) {
		cin >> a >> b >> c;
		cout << "Case #" << cnt++ << ": " <<( a + b > c ? "true" : "false" ) << endl;
	}
}