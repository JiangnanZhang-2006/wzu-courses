#include <bits/stdc++.h>

using namespace std;

int main() {
	while (true) {
		int n, m, cur = 0;
		cin >> n >> m;
		if (n == m && n == 0) {
			return 0;
		}
		int* lst = new int[n + 1];

		for (int i = 0; i < n; i++) {	//list init
			lst[i] = i;
		}
		lst[n] = -1;

		while (n > 1) {
			cur = (cur + m - 1) % n;
			for (int i = cur + 1; i < n; i++) {
				lst[i - 1] = lst[i];
			}
			n--;
		}
		cout << lst[0] + 1 << endl;
		delete[] lst;					//release memory
	}
	return 0;
}