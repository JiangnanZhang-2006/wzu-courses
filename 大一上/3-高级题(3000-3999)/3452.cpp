#include <bits/stdc++.h>

using namespace std;

int main() {
	vector<vector<string> > People;
	int t, invalidCnt = 0;
	cin >> t;
	while (t--) {
		string name;
		string time;
		cin >> name >> time;
		People.push_back({name, time});
	}
	for (auto it = People.begin(); it != People.end(); ++it) {
		if ((*it)[1] < "1814/09/06" || (*it)[1] > "2014/09/06") {
			(*it)[1] = "9999/99/99";
			invalidCnt++;
		}
	}
	sort(People.begin(), People.end(), [](auto a, auto b) {return a[1] < b[1]; });
	if (People.size() - invalidCnt == 0) {
		cout << 0 << endl;
	}
	else {
		cout << People.size() - invalidCnt << ' ' << People[0][0] << ' ' << People[People.size() - 1 - invalidCnt][0] << endl;
	}
}