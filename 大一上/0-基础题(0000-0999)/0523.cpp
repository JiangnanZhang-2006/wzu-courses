#include <iostream>
#include <list>
#include <utility>
#include <iomanip>

using namespace std;
list<pair<string, double>> stu;

int main() {
	string cmd;
	while (true) {
		cin >> cmd;
		if (cmd == "INSERT") {
			string id;
			double score;
			cin >> id >> score;
			//auto it = stu.begin();
			//for (; it != stu.end() && it->first < id; ++it);
			//stu.insert(it, { id, score });
			stu.push_back({ id, score });
			cout << id << ' ' << fixed << setprecision(2) << score << endl;
		}
		else if (cmd == "LIST") {
			for (auto it = stu.begin(); it != stu.end(); ++it) {
				cout << it->first << ' ' << fixed << setprecision(2) << it->second << endl;
			}
		}
		else if (cmd == "QUIT") {
			cout << "Good bye!" << endl;
			break;
		}
	}
}