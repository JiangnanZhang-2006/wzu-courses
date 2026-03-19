#include <bits/stdc++.h>

using namespace std;

int main() {
	long long a, b;
	int n;
	cin >> a >> n;
	b = a / pow(10, n) + a % (int)pow(10, n) * pow(10, (int)log10(a) - n + 1);
	cout << fixed << setprecision(2) << b * 1.0 / a << endl;
}