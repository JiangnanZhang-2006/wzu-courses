#include <iostream>
#include <cstdio>
#include <math.h>
using namespace std;
int main() {
	int t;
	cin >> t;
	while (t--) {
		int a, b;
		cin >> a >> b;
		printf ("%d %d %d %d\n", a+b, a*b, a-b, a/b);
	}
	return 0;
}