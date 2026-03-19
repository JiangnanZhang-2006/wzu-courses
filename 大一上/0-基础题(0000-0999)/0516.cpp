#include <iostream>
#include <cstdio>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

struct Students {
	string id;
	string name;
	char sex;
	double x;
	double y;
	double z;
	double avg;
	double tot;

	Students() = default;
};

vector<Students> arr;

static void insert();
static void list();

int main() {
	string cmd;
	while (true) {
		cin >> cmd;
		if (cmd == "INSERT") insert();
		else if (cmd == "LIST") list();
		else if (cmd == "QUIT") {
			cout << "Good bye!" << endl; break;
		}
	}
}

void insert() {
	string id, name;
	char sex;
	double x, y, z, avg, tot;
	cin >> id >> name >> sex >> x >> y >> z;
	tot = x + y + z;
	avg = tot / 3;
	arr.push_back({ id, name, sex, x, y, z, avg, tot });
	printf("%s %s %c %.2f %.2f %.2f %.2f %.2f\n", id.c_str(), name.c_str(), sex, x, y, z, avg, tot);
}

void list() {
	for (const Students s : arr) {
		printf("%s %s %c %.2f %.2f %.2f %.2f %.2f\n", s.id.c_str(), s.name.c_str(), s.sex, s.x, s.y, s.z, s.avg, s.tot);
	}
}