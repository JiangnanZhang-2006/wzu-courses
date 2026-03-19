#include <iostream>
#include <list>
#include <utility>
#include <iomanip>

using namespace std;

int main() {
	list<pair<string, double>> stu;
	string id;
	double score;
	cin >> id;
	while (id != "0") {
		cin >> score;
		stu.push_back({ id, score });
		cin >> id;
	}
	cout << "The records are:" << endl;
	for (auto it = stu.begin(); it != stu.end(); ++it) {
		cout << it->first << ' ' << fixed << setprecision(1) << it->second << endl;
	}
}