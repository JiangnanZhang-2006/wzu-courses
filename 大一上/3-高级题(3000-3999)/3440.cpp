#include <iostream>
#include <string>
using namespace std;

int main() {
	char da, db;
	long long pa = 0, pb = 0;
	string a, b;

	cin >> a >> da >> b >> db;

	for (const char& i : a) {
		if (i == da) {
			pa = pa * 10 + i - '0';
		}
	}

	for (const char& i : b) {
		if (i == db) {
			pb = pb * 10 + i - '0';
		}
	}
	cout << pa + pb << endl;
}