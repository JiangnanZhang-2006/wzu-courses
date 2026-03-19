#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	int t;
	vector<int> arr;
	cin >> t;
	while (t--) {
		int temp;
		cin >> temp;
		arr.emplace_back(temp);
	}
	vector<vector<int>> klz_arr;
	for (auto i : arr) {
		vector<int> temp;
		while (i != 1) {
			if (i % 2) {
				i = (i * 3 + 1) / 2;
			}
			else {
				i = i / 2;
			}
			temp.emplace_back(i);
		}
		klz_arr.emplace_back(temp);
	}
	vector<int> ans_arr;
	for (auto i : arr) {
		bool flag = true;
		for (auto j : klz_arr) {
			for (auto k : j) {
				if (i == k) {
					flag = false;
					break;
				}
			}
			if (!flag) break;
		}
		if (flag) ans_arr.emplace_back(i);
	}
	sort(ans_arr.begin(), ans_arr.end(), [](int a, int b) {return a > b; });
	bool flag = true;
	for (auto i : ans_arr) {
		if (flag) {
			flag = false;
			cout << i;
			continue;
		}
		cout << ' ' << i;
	}
	cout << endl;
}