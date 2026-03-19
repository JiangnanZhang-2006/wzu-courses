#include <bits/stdc++.h>

using namespace std;

vector<vector<char>> arr;
vector<string> words;
vector<vector<vector<bool>>> solution;

int n, m;

bool search(int i, int j, int cur, vector<vector<bool>> used);

int main() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}
	int t;
	while (t--) {
		string temp;
		cin >> temp;
		words.emplace_back(temp);
	}
	//对于每一个输入的单词计算所有可能
	vector <int> solution_idx = { 0 };
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int cnt;
			for (const string s : words) {
				if (search(i, j, 0, s, vector<vector<bool>>(m, vector<bool>(n, false)))) ++cnt;

			}

			solution_idx.emplace_back(cnt + solution_idx[solution_idx.size()-1] / 2);
		}
	}
}

bool search(int i, int j, int cur, string s, vector<vector<bool>> used)
{
	if (i == m || j == n || i == -1 || j == -1) return false;
	if (arr[i][j] != s[cur]) return false;
	if (used[i][j]) return false;

	used[i][j] = true;
	if (arr[i][j] == s[cur]) {
		if (cur == s.size() - 1) {
			solution.emplace_back(used);
			return true;
		}
		if (search(++i, j, ++cur, s, used) + search(i, ++j, ++cur, s, used)
			+ search(--i, j, ++cur, s, used) + search(i, --j, ++cur, s, used)) {
			return true;
		}
		else return false;
	}
	else {
		return false;
	}
	return 0;
}
