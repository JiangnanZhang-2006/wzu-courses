#include <bits/stdc++.h>

using namespace std;
int cnt[100005];

int main() {
	int n;
	cin >> n;
	while (n--) {
		int temp;
		cin >> temp;
		cnt[temp]++;
	}
	for (int i = 1; i < 100005; i = i + 2) {
		if (cnt[i] % 2 == 1) {
			cout << i << endl;
			break;
		}
	}
}