#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
	unsigned int N;
	double D;
	cin >> N >> D;
	vector<vector<double>> vec{N, {0, 0, 0}};// volume, totalPrice, price
	for (int i = 0; i < N; i++) {
		cin >> vec[i][0];
	}
	for (int i = 0; i < N; i++) {
		cin >> vec[i][1];
		vec[i][2] = vec[i][1] / vec[i][0];
	}
	sort(vec.begin(), vec.end(), [](auto a, auto b){ return a[2] > b[2];});
	double sum = 0;
	int cur = 0;
	while (D != 0 && cur != N) {
		if (vec[cur][0] > D) {
			sum += vec[cur][2] * D;
			break;
		}
		else {
			sum += vec[cur][1];
			D -= vec[cur][0];
		}
		cur++;
	}
	cout << fixed << setprecision(2) << sum << endl;
}