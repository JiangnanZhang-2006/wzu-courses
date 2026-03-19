#include <iostream>
#include <string>

using namespace std;

int main() {
	string s1, s2, s3, s4;
	cin >> s1 >> s2 >> s3 >> s4;
	char day, hour;
	bool flag_day = false, flag_hour = false;
	for (int i = 0; i < min(s1.size(), s2.size()); i++) {
		if (s1[i] == s2[i]) {
			if (s1[i] >= 'A' && s1[i] <= 'F' && !flag_day) {
				flag_day = true;
				day = s1[i];
				continue;
			}
			if (((s1[i] >= 'A' && s1[i] <= 'N') || (s1[i] >= '0' && s1[i] <= '9'))&& flag_day && !flag_hour) {
				flag_hour = true;
				hour = s1[i];
				break;
			}
		}
	}
	if (day == 'A') {
		cout << "MON";
	}
	else if (day == 'B') {
		cout << "TUE";
	}
	else if (day == 'C') {
		cout << "WED";
	}
	else if (day == 'D') {
		cout << "THU";
	}
	else if (day == 'E') {
		cout << "FRI";
	}
	else if (day == 'G') {
		cout << "SAT";
	}
	else if (day == 'F') {
		cout << "SUN";
	}
	cout << ' ';
	if (hour <= '9' && hour >= '0') {
		cout << '0' << hour;
	}
	else {
		cout << hour - 'A' + 10;
	}
	cout << ':';
	int pos;
	for (int i = 0; i < min(s3.size(), s4.size()); i++) {
		if (s3[i] == s4[i] && s3[i] <= 'Z' && s3[i] >= 'A') {
			pos = i;
			break;
		}
	}
	if (pos < 10) {
		cout << '0' << pos;
	}
	else {
		cout << pos;
	}
	cout << endl;
}