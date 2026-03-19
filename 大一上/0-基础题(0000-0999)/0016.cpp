#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;
vector<int> year;
int main() {
	//init
	year.push_back(0);
	for (int i = 0; i < 8000; i++) {
		year.push_back(365 + ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) + year[i]);
	}
	int cur;
	cin >> cur;
	while (cur != -1) {
		int curY, curM, curD;
		for (int i = 0; i < 8000; i++) {
			if (year[i] > cur) {
				curY = i + 1999;
				curD = cur - year[i - 1] + 1;
				break;
			}
		}
		curM = 1;
		int month[12] = {31, 28 + ((curY % 4 == 0 && curY % 100 != 0) || curY % 400 == 0), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		for (int i = 0; i < 12 && curD - month[i] > 0; i++) {
			curM++;
			curD -= month[i];
		}
		cout << curY << '-' << setw(2) << setfill('0') << curM << setw(1) << '-' << setw(2) << curD;
		string week[7] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
		cout << ' ' << week[cur % 7];
		cout << endl;
		cin >> cur;
	}
	
}