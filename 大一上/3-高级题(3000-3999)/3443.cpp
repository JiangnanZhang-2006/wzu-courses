#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int vectoi(vector<int> vec) {
	int a = 0;
	for (const int& i : vec) {
		a = a * 10 + i;
	}
	return a;
}
vector<int> itovec(int i) {
	vector<int> vec;
	for (int j = 0; j < 4; j++) {
		vec.insert(vec.begin(), i % 10);
		i = i / 10;
	}
	return vec;
}
int main() {
	vector<int> a, b, ans;
	int temp;
	cin >> temp;
	ans = itovec(temp);
	bool isSame = true;
	for (int i = 0; i < 3; i++) {
		if (ans[i] != ans[i + 1]) {
			isSame = false;
			break;
		}
	}
	if (isSame) {
		cout << setw(4) << setfill('0') << vectoi(ans) << setw(3) << " - " << setw(4) << vectoi(ans) << setw(3) << " = " << setw(4) << 0 << endl;
		return 0;
	}
	while (vectoi(ans)!= 6174 || !isSame){ //这里复用isSame保证进行一次循环(当输入位6174)
		isSame = true;
		b = ans;
		a = ans;
		sort(a.begin(), a.end(), [](int a, int b) {return a > b;});
		sort(b.begin(), b.end(), [](int a, int b) {return a < b;});
		ans = itovec(vectoi(a) - vectoi(b));
		cout << setw(4) << setfill('0') << vectoi(a) << setw(3) << " - " << setw(4) << vectoi(b) << setw(3) << " = " << setw(4) << vectoi(ans) << endl;

	}

}