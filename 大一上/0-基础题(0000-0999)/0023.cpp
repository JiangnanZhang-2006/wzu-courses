#include <bits/stdc++.h>

using namespace std;

vector<int> a, b, ans;

int main() {
	char temp;
	temp = getchar();
	while (temp != '\n' && temp != EOF) {
		a.push_back(temp - '0');
		temp = getchar();
	}
	temp = getchar();
	while (temp != '\n' && temp != EOF) {
		b.push_back(temp - '0');
		temp = getchar();
	}
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	//调整长度至一样
	if (a.size() < b.size()) {
		a.resize(b.size(), 0);
	}
	else {
		b.resize(a.size(), 0);
	}
	int carry = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i] + b[i] + carry >= 10) {
			ans.push_back(a[i] + b[i] + carry - 10);
			carry = 1;
		}
		else {
			
			ans.push_back(a[i] + b[i] + carry);
			carry = 0;
		}
	}
	if (carry) {
		ans.push_back(carry);
	}
	reverse(ans.begin(), ans.end());
	for (int i : ans) {
		cout << i;
	}
	cout << endl;
}