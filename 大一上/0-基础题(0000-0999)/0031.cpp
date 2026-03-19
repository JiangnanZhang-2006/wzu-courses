#include <bits/stdc++.h>

using namespace std;
vector<vector<bool>> field;
vector<pair<int, int>> pos;
vector<bool> temp;

int main() {
	int cow, line;
	cin >> line >> cow;
	for (int i = 0; i < cow; i++) {
		temp.clear();
		for (int j = 0; j < line; j++) {
			temp.push_back(true);
		}
		field.emplace_back(temp);
	}
	int t;
	cin >> t;
	for (int i = 0; i < t; i++) {
		pair<int, int> tempP;
		cin >> tempP.first >> tempP.second;
		field[tempP.first][tempP.second] = false;
		pos.emplace_back(tempP);
	}

}