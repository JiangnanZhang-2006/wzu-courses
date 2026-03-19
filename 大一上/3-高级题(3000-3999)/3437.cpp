#include <iostream>
#include <math.h>

using namespace std;
bool isprime(int seq);
int main() {
	int m, n, cnt = 0, num = 1;
	cin >> m >> n;
	while(cnt < n) {
		num++;
		if (isprime(num)) {
			cnt++;
			if (cnt < m) continue;
			if ((cnt - m) % 10 == 0) {
				cout << num;
				continue;
			}
			cout << ' ' << num;
			if ((cnt - m) % 10 == 9) {
				cout << endl;
			}
		}
	}
	if (cnt - m % 10 != 9) cout << endl;
}

bool isprime(int seq) {
	int k = sqrt(seq) + 1;
	for (int i = 2; i < k; i++) {
		if (seq % i == 0) {
			return false;
		}
	}
	return true;
}