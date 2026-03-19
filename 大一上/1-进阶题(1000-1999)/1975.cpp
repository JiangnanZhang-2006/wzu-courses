#include <bits/stdc++.h>

using namespace std;

int main() {

	int	n;
	double max = 0;
	cin >> n;
	double** seq = new double*[n];

	for (int i = 0; i < n; i++) {
		double x, y;
		cin >> x >> y;
		seq[i]= new double[2];
		seq[i][0] = x;
		seq[i][1] = y;
	}
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			double distance = sqrt(pow(seq[i][0] - seq[j][0], 2) + pow(seq[i][1] - seq[j][1],2));
			if (distance > max) {
				max = distance;
			}
		}
	}
	cout << fixed << setprecision(4) << max << endl;
	return 0;
}