#include <iostream>
#include <vector>

using namespace std;

int main() {
	int n, m;
	vector<int> arr;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int temp;
		cin >> temp;
		arr.emplace_back(temp);
	}
	for (int i = 0; i < n - m % n; i++) {
		arr.emplace_back(arr[0]);
		arr.erase(arr.begin());
	}
	bool flag = true;
	for (const auto& i : arr) {
		if (flag) {
			cout << i;
			flag = false;
			continue;
		}
		cout << ' ' << i;
	}
	cout << endl;
}