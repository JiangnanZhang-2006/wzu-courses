#include <iostream>
#include <list>
#include <utility>
#include <iomanip>

using namespace std;

int main() {
	list<pair<string, double>> stu;
	string id;
	double score;
	//input
	cin >> id;
	while (id != "0") {
		cin >> score;
		stu.push_back({ id, score });
		cin >> id;
	}
	//output
	cout << "The records are:" << endl;
	for (auto it = stu.begin(); it != stu.end(); ++it) {
		cout << it->first << ' ' << fixed << setprecision(1) << it->second << endl;
	}
	//delete
	cin >> score;
	while (score != 0) {
		bool flag = true;
		while (flag) {
			flag = false;
			for (auto it = stu.begin(); it != stu.end(); ++it) {
				if (it->second < score) {
					stu.erase(it);
					flag = true;
					break;
				}
			}
		}
		//output
		cout << "The records are:" << endl;
		for (auto it = stu.begin(); it != stu.end(); ++it) {
			cout << it->first << ' ' << fixed << setprecision(1) << it->second << endl;
		}
		cin >> score;
	}
	
}