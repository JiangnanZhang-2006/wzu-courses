#include <iostream>
#include <climits>

using namespace std;

int main() {
	int t, min_pos = -1, min = INT_MAX;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		int temp;
		cin >> temp;
		if (temp <= min) {
			min_pos = i;
			min = temp;
		}
	}
	cout << min << ' ' << min_pos << endl;
}