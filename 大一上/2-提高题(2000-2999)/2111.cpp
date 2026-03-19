#include <bits/stdc++.h>

using namespace std;

static double fuc(double x, double y);

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		double x, y;
		cin >> x >> y;
		cout << fixed << setprecision(2) << fuc(x, y) << endl;
	}
	return 0;
}
double fuc(double x, double y) {
	if (x < 0) {
		return x + y;
	}
	else {
		return fuc(x - 1, x + y) + x / y;
	}
}