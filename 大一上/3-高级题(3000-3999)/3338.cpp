int calcDays(int year, int month, int day) {
	int cnt = 0;
	bool flag = false;

	if (year % 4 == 0) {
		if (year % 100 != 0) {
			flag = true;
		}
	}
	if (year % 400 == 0) {
		flag = true;
	}

	int dic[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (flag) {
		dic[2] = 29;
	}

	for (int j = 1; j < month; j++) {
		cnt += dic[j];
	}
	cnt += day;
	return cnt;
}