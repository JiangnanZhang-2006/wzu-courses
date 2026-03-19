#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Student {
	string id;
	int de;
	int cai;
};
vector<Student> students_level_1;
vector<Student> students_level_2;
vector<Student> students_level_3;
vector<Student> students_level_4;

int main() {
	int n, l, h;
	cin >> n >>	l >> h;
	while (n--) {
		Student student;
		cin >> student.id >> student.de >> student.cai;

		if (student.de >= h && student.cai >= h) {
			students_level_1.emplace_back(student);
		}
		else if (student.de >= h && student.cai >= l) {
			students_level_2.emplace_back(student);
		}
		else if (student.de > student.cai && student.de >= l && student.cai >= l) {
			students_level_3.emplace_back(student);
		}
		else if (student.de >= l && student.cai >= l) {
			students_level_4.emplace_back(student);
		}
	}
	sort(students_level_1.begin(), students_level_1.end(), [](Student a, Student b) {
		if ( a.de + a.cai != b.de + b.cai ) {
			return a.de + a.cai > b.de + b.cai;
		}
		else if(a.de != b.de) {
			return a.de > b.de;
		}
		else {
			return a.id < b.id;
		}});

	sort(students_level_2.begin(), students_level_2.end(), [](Student a, Student b) {
		if (a.de + a.cai != b.de + b.cai) {
			return a.de + a.cai > b.de + b.cai;
		}
		else if (a.de != b.de) {
			return a.de > b.de;
		}
		else {
			return a.id < b.id;
		}});
	
	sort(students_level_3.begin(), students_level_3.end(), [](Student a, Student b) {
		if ( a.de + a.cai != b.de + b.cai ) {
			return a.de + a.cai > b.de + b.cai;
		}
		else if(a.de != b.de) {
			return a.de > b.de;
		}
		else {
			return a.id < b.id;}});

	sort(students_level_4.begin(), students_level_4.end(), [](Student a, Student b) {
		if (a.de + a.cai != b.de + b.cai) {
			return a.de + a.cai > b.de + b.cai;
		}
		else if (a.de != b.de) {
			return a.de > b.de;
		}
		else {
			return a.id < b.id;
		}});
	cout << students_level_1.size() + students_level_2.size() + students_level_3.size() + students_level_4.size() << endl;
	for (auto i : students_level_1) {
		cout << i.id << ' ' << i.de << ' ' << i.cai << endl;
	}
	for (auto i : students_level_2) {
		cout << i.id << ' ' << i.de << ' ' << i.cai << endl;
	}
	for (auto i : students_level_3) {
		cout << i.id << ' ' << i.de << ' ' << i.cai << endl;
	}
	for (auto i : students_level_4) {
		cout << i.id << ' ' << i.de << ' ' << i.cai << endl;
	}
}