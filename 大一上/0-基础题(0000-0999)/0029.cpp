#include <bits/stdc++.h>

using namespace std;

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n + 1; i++) {
		for (int j = 2; j < i; j++) {
			for (int k = j; k < i; k++) {
				for (int l = k; l < i; l++) {
					if (pow(i, 3) == pow(j, 3) + pow(k, 3) + pow(l, 3)) {
						printf("Cube = %d, Triple = (%d,%d,%d)\n", i, j, k, l);
					}
				}
			}
		}
	}
}