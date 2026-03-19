#include <iostream>
#include <string>

using namespace std;

int main() {
	string a, ans_q = "";
	int b, ans_r = 0;

	cin >> a >> b;

	for (const char& i : a) {
		ans_r = ans_r * 10 + i - '0';
		if (ans_r / b != 0 || ans_q != "") {
			ans_q += (char)(ans_r / b + '0');
		}
		ans_r = ans_r % b;
	}
	if (ans_q == "") {
		cout << "0 " << ans_r << endl;
	}
	else {
		cout << ans_q << ' ' << ans_r << endl;
	}
}