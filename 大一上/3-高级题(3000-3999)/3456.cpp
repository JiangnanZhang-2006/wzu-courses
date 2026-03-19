#include <bits/stdc++.h> 
using namespace std;

long long scores[100005];


int main() {
	int t;
	cin >> t;
	while (t--) {
		int id, score;
		cin >> id >> score;
		scores[id] += score;
	}
	int max = -1, maxp = -1;
	for (int i = 0; i < 100005; i++) {
		if (scores[i] > max) {
			max = scores[i];
			maxp = i;
		}
	}
	cout << maxp << ' ' << max << endl;
}