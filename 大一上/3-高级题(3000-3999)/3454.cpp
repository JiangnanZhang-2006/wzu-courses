#include <bits/stdc++.h>

using namespace std;

int main() {
	vector<int> arr;
	vector<long long> arrTimesP;
	int n, Max = 0;
	long long p;
	cin >> n >> p;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		arr.push_back(temp);
	}
	sort(arr.begin(), arr.end(), [](int a, int b) {return a < b;});
	for (int i : arr) {
		arrTimesP.push_back(i * p);
	}
	for (int i = 0; i < n; i++) {
		for (int j = n - 1; j >= i; j--) {
			if (arr[j] <= arrTimesP[i]) {
				Max = max(Max, j - i + 1);
				break;
			}
		}
	}
	/*
	for (int i = 0; i <= n; i++) {
		int max = INT_MIN, min = INT_MAX, rmax = INT_MIN, rmin = INT_MAX;
		for (auto it = arr.begin(); it != arr.end() - i; ++it) {
			if (max < (*it)) {
				max = *it;
			}
			if (min > (*it)) {
				min = *it;
			}
		}
		for (auto it = arr.rbegin(); it != arr.rend() - i; ++it) {
			if (rmax < (*it)) {
				rmax = *it;
			}
			if (rmin > (*it)) {
				rmin = *it;
			}
		}
		if (max <= min * p || rmax <= rmin * p) {
			cout << n - i<< endl;
			find = true;
			break;
		}
	}
	*/

	cout << Max << endl;
	
}