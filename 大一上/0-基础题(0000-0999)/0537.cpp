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
static void find();
static void change();
static void _delete();

int main() {
	string cmd;
	while (true) {
		cin >> cmd;
		if (cmd == "Insert") insert();
		else if (cmd == "List") list();
		else if (cmd == "Find") find();
		else if (cmd == "Change") change();
		else if (cmd == "Delete") _delete();
		else if (cmd == "Quit" || cmd == "Exit") {
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
	//check
	for (auto it = arr.begin(); it != arr.end(); ++it) {
		if ((*it).id == id) {
			cout << "Failed" << endl;
			return;
		}
	}
	////find
	//auto it = arr.begin();
	//for (it = arr.begin(); it != arr.end() && (*it).id < id; ++it);
	cout << "Insert:" << endl;
	//arr.insert(it, { id, name, sex, x, y, z, avg, tot });
	arr.push_back({ id, name, sex, x, y, z, avg, tot });
	printf("%s %s %c %.1f %.1f %.1f\n", id.c_str(), name.c_str(), sex, x, y, z);
}

void list() {
	cout << "List:" << endl;
	for (const Students s : arr) {
		printf("%s %s %c %.1f %.1f %.1f\n", s.id.c_str(), s.name.c_str(), s.sex, s.x, s.y, s.z);
	}
}

void find() {
	string id;
	cin >> id;
	cout << "Find:" << endl;
	for (auto it = arr.begin(); it != arr.end(); ++it) {
		if ((*it).id == id) {
			Students s = *it;
			printf("%s %s %c %.1f %.1f %.1f\n", s.id.c_str(), s.name.c_str(), s.sex, s.x, s.y, s.z);
			return;
		}
	}
	cout << "Failed" << endl;
}

void change() {
	string id;
	cin >> id;
	cout << "Change:" << endl;
	for (auto it = arr.begin(); it != arr.end(); ++it) {
		if ((*it).id == id) {
			string id, name;
			char sex;
			double x, y, z, avg, tot;
			cin >> name >> sex >> x >> y >> z;
			tot = x + y + z;
			avg = tot / 3;
			it->name = name;
			it->sex = sex;
			it->x = x;
			it->y = y;
			it->z = z;
			it->avg = avg;
			it->tot = tot;
			Students s = *it;

			printf("%s %s %c %.1f %.1f %.1f\n", s.id.c_str(), s.name.c_str(), s.sex, s.x, s.y, s.z);
			return;
		}
	}
	cout << "Failed" << endl;
}

void _delete() {
	string id;
	cin >> id;
	cout << "Delete:" << endl;
	for (auto it = arr.begin(); it != arr.end(); ++it) {
		if ((*it).id == id) {
			arr.erase(it);
			printf("Deleted\n");
			return;
		}
	}
	cout << "Failed" << endl;
}