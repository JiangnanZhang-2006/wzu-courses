#include <bits/stdc++.h>

using namespace std;

int prime[17] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
char dic[11] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
vector<string> invalidIds;

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		string temp;
		int sum = 0;
		bool flag = true;
		cin >> temp;
		if (temp.size() != 18) {
			invalidIds.push_back(temp);
			continue;
		}
		for (int j = 0; j < 17; j++) {
			if (temp[j] > '9' || temp[j] < '0') {
				flag = false;
				break;
			}
			sum += (temp[j] - '0') * prime[j];
		}
		if (dic[sum % 11] != temp[17] || !flag) {
			invalidIds.push_back(temp);
		}
		
	}
	if (invalidIds.size() == 0) {
		cout << "All passed" << endl;
	}
	else {
		for (auto i : invalidIds) {
			cout << i << endl;
		}
	}
}