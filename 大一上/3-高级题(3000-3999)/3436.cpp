#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iomanip>

using namespace std;

int main() {
	bool A2 = true;
	int A[5] = { 0 }, A4_cnt = 0, t, flag = 1;
	cin >> t;
	while (t--) {
		int temp;
		cin >> temp;
		if (temp % 10 == 0) {
			A[0] += temp;
		}
		else if (temp % 5 == 1) {
			A2 = false;
			A[1] += temp * flag;
			flag = -flag;
		}
		else if (temp % 5 == 2) {
			A[2]++;
		}
		else if (temp % 5 == 3) {
			A[3] += temp;
			A4_cnt++;
		}
		else if (temp % 5 == 4) {
			A[4] = temp > A[4] ? temp : A[4];
		}
	}
	cout << (A[0] == 0 ? "N" : to_string(A[0])) << ' ' << (A2 ? "N" : to_string(A[1])) << ' ' <<
		(A[2] == 0 ? "N" : to_string(A[2])) << ' ';
	if (A[3] == 0) {
		cout << 'N' << ' ';
	}
	else {
		cout << fixed << setprecision(1) << A[3] * 1.0 / A4_cnt << ' ';
	}
	cout << (A[4] == 0 ? "N" : to_string(A[4])) << endl;
}