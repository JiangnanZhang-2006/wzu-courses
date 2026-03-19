#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<string> arr;
	string temp;
	while (cin >> temp) {
		arr.emplace_back(temp);
	}
	bool flag = true;
	for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
		if (flag) {
			cout << *it;
			flag = false;
			continue;
		}
		cout << ' ' << *it;
	}
	cout << endl;
}