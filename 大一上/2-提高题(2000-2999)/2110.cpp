#include <bits/stdc++.h>

using namespace std;

static void dic_init();
static bool judge(int year);

map<int, int> dic;

int main() {
	int n;
	cin >> n;
	dic_init();
	for (int i = 0; i < n; i++) {
		int year, month, day, cnt = 0;

		scanf("%d/%d/%d", &year, &month, &day);

		if (judge(year)) {
			dic[2] = 29;
		}
		else {
			dic[2] = 28;
		}

		for (int j = 1; j < month; j++) {
			cnt += dic[j];
		}
		cnt += day;
		cout << cnt << endl;
	}
	return 0;
}
void dic_init() {
	dic[1] = 31;
	dic[2] = 28;
	dic[3] = 31;
	dic[4] = 30;
	dic[5] = 31;
	dic[6] = 30;
	dic[7] = 31;
	dic[8] = 31;
	dic[9] = 30;
	dic[10] = 31;
	dic[11] = 30;
	dic[12] = 31;
}
bool judge(int year) {
	if (year % 4 == 0) {
		if (year % 100 != 0) {
			return true;
		}
	}
	if (year % 400 == 0) {
		return true;
	}
	return false;
}