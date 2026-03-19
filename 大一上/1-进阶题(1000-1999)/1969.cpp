#include <bits/stdc++.h>
using namespace std;

int main() {
	int T;
	cin >> T;
	while (T--) {
		int m;
		double sum = 0, sum_fangCha = 0, mean;
		cin >> m;
		int* seq = new int[m];
		for (int i = 0; i < m; i++) {
			int ipt;
			cin >> ipt;
			seq[i] = ipt;
			sum += ipt;
		}
		mean = sum / m;
		for (int i = 0; i < m; i++) {
			sum_fangCha += (mean - seq[i]) * (mean - seq[i]);
		}
		delete[] seq;
		sum_fangCha /= m;
		sum_fangCha = sqrt(sum_fangCha);
		cout << fixed << setprecision(3) << mean << ' ' << sum_fangCha << endl;
	}
}