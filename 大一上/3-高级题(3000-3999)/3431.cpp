#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<int> primes;

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		bool flag = true;
		int k = sqrt(i) + 1;
		for (int j = 2; j < k; ++j) {
			if (i % j == 0) {
				flag = false;
				break;
			}
		}
		if (flag) {
			primes.emplace_back(i);
		}
	}
	
	int cnt = 0;
	for (int i = 0; i < primes.size() - 1; ++i) {
		if (primes[i + 1] - primes[i] == 2) {
			cnt++;
		}
	}
	cout << cnt << endl;
}