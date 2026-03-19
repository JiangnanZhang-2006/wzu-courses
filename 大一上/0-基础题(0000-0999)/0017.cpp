#include <bits/stdc++.h>
#include <unordered_map>

using namespace std;

unordered_map<string, int> Haab{
	{"pop", 0},
	{"no", 20},
	{"zip", 40},
	{"zotz", 60},
	{"tzec", 80},
	{"xul", 100},
	{"yoxkin", 120},
	{"mol", 140},
	{"chen", 160},
	{"yax", 180},
	{"zac", 200},
	{"ceh", 220},
	{"mac", 240},
	{"kankin", 260},
	{"muan", 280},
	{"pax", 300},
	{"koyab", 320},
	{"cumhu", 340},
	{"uayet", 360}
};
string Tzolkin[20]{"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik",
	"lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem",
	"cib", "caban", "eznab", "canac", "ahau"};

int main() {
	int t;
	cin >> t;
	cout << t << endl;
	while (t--) {
		int dd, yy;
		string temp;
		char dot;
		cin >> dd >> dot >> temp >> yy;
		dd = dd + Haab.at(temp) + yy * 365;
		int pos = 0, year = 0, day = 1;
		while (dd) {
			dd--;
			pos = (pos + 1) % 20;
			day = day % 13 + 1;
			if (day == 1 && pos == 0) {
				year++;
			}
		}
		cout << day << ' ' << Tzolkin[pos] << ' ' << year << endl;
	}
}