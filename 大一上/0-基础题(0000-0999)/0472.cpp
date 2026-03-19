#include <iostream>
#include <cstdio>
#include <vector>
#include <string>

using namespace std;

struct Students {
	string name;
	string sid;
	long long llid;
	char sex;
	int x;
	int y;
	int z;
	int tot;
};
static void Insert();
static void Find();
static void Change();
static void Delete();
static void Statistics();
static string toCeil(string s);

vector <Students> arr;

int main() {
	string cmd;
	while (true) {
		cin >> cmd;
		if (cmd == "Insert") Insert();
		else if (cmd == "Find") Find();
		else if (cmd == "Change") Change();
		else if (cmd == "Delete") Delete();
		else if (cmd == "Statistics") Statistics();
		else if (cmd == "Quit" || cmd == "Exit") break;
	}
	cout << "Good bye!" << endl;
	return 0;
}
string toCeil(string s) {
	for (char& c : s) {
		if (c <= 'Z' && c >= 'A') c += 32;
	}
	return s;
}

void Insert() {
	string name, sid;
	long long llid;
	char sex;
	int x, y, z;
	cin >> name >> sid >> sex >> x >> y >> z;
	name = toCeil(name);
	llid = stoll(sid);
	for (auto it = arr.begin(); it != arr.end(); ++it) {
		if ((*it).sid == sid || (*it).name == name) {
			cout << "Failed" << endl;
			return;
		}
	}
	//insert;
	auto it = arr.begin();
	for (it = arr.begin(); it != arr.end() && (*it).llid < llid; ++it);
	arr.insert(it, {name, sid, llid, sex, x, y, z, x + y + z});
	cout << "Inserted" << endl;
	return;
}

void Find() {
	string s;
	bool isNumber = false;
	cin >> s;
	if (s[0] <= '9' && s[0] >= '0') {
		isNumber = true;
	}
	if (isNumber) {
		for (auto it = arr.begin(); it != arr.end(); ++it) {
			if ((*it).sid == s) {
				printf("%s %s %c %d %d %d %d\n", (*it).name.c_str(), (*it).sid.c_str(), (*it).sex, (*it).x, (*it).y, (*it).z, (*it).tot);
				return;
			}
		}
	}
	else {
		s = toCeil(s);
		for (auto it = arr.begin(); it != arr.end(); ++it) {
			if ((*it).name == s) {
				printf("%s %s %c %d %d %d %d\n", (*it).name.c_str(), (*it).sid.c_str(), (*it).sex, (*it).x, (*it).y, (*it).z, (*it).tot);
				return;
			}	
		}
	}
	cout << "Failed" << endl;
	return;
}
void Delete() {
	string s;
	bool isNumber = false;
	cin >> s;
	if (s[0] <= '9' && s[0] >= '0') {
		isNumber = true;
	}
	if (isNumber) {
		for (auto it = arr.begin(); it != arr.end(); ++it) {
			if ((*it).sid == s) {
				arr.erase(it);
				cout << "Deleted" << endl;
				return;
			}
		}
	}
	else {
		s = toCeil(s);
		for (auto it = arr.begin(); it != arr.end(); ++it) {
			if ((*it).name == s) {
				arr.erase(it); 
				cout << "Deleted" << endl;
				return;
			}
		}
	}
	cout << "Failed" << endl;
	return;
}
void Change() {
	string s;
	string name, sid;
	long long llid;
	char sex;
	int x, y, z;
	bool isNumber = false;
	cin >> s;
	if (s[0] <= '9' && s[0] >= '0') {
		isNumber = true;
	}
	cin >> name >> sid >> sex >> x >> y >> z;
	name = toCeil(name);
	llid = stoll(sid);
	if (isNumber) {
		for (auto it = arr.begin(); it != arr.end(); ++it) {
			if ((*it).sid == s) {
				(*it).name = name;
				(*it).sid = sid;
				(*it).llid = llid;
				(*it).sex = sex;
				(*it).x = x;
				(*it).y = y;
				(*it).z = z;
				(*it).tot = x + y + z;
				cout << "Changed" << endl;
				return;
			}
		}
	}
	else {
		s = toCeil(s);
		for (auto it = arr.begin(); it != arr.end(); ++it) {
			if ((*it).name == s) {
				(*it).name = name;
				(*it).sid = sid;
				(*it).llid = llid;
				(*it).sex = sex;
				(*it).x = x;
				(*it).y = y;
				(*it).z = z;
				(*it).tot = x + y + z;
				cout << "Changed" << endl;
				return;
			}
		}
	}
	cout << "Failed" << endl;
	return;
}

void Statistics() {
	double sumX = 0, sumY = 0, sumZ = 0;
	int bujigeX = 0, bujigeY = 0, bujigeZ = 0, youxiuX = 0, youxiuY = 0, youxiuZ = 0, cnt = 0;
	for (const auto& a : arr) {
		printf("%s %s %c %d %d %d %d\n", a.name.c_str(), a.sid.c_str(), a.sex, a.x, a.y, a.z, a.tot);
		++cnt;
		sumX += a.x;
		sumY += a.y;
		sumZ += a.z;
		if (a.x >= 90) ++youxiuX;
		if (a.y >= 90) ++youxiuY;
		if (a.z >= 90) ++youxiuZ;
		if (a.x < 60) ++bujigeX;
		if (a.y < 60) ++bujigeY;
		if (a.z < 60) ++bujigeZ;
	}
	printf("%.1f %.1f %.1f\n", sumX / cnt, sumY / cnt, sumZ / cnt);
	printf("%d %d %d\n", bujigeX, bujigeY, bujigeZ);
	printf("%d %d %d\n", youxiuX, youxiuY, youxiuZ);
}