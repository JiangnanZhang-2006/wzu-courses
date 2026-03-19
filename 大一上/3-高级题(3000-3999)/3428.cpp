#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Students {
	string name;
	string id;
	int score;
};

vector<Students> arr;

int main() {
	int t;
	cin >> t;
	while (t--) {
		Students student;
		cin >> student.name >> student.id >> student.score;
		arr.emplace_back(student);
	}
	sort(arr.begin(), arr.end(), [](Students a, Students b) { return a.score > b.score; });
	cout << arr[0].name << ' ' << arr[0].id << endl
		<< arr[arr.size() - 1].name << ' ' << arr[arr.size() - 1].id << endl;
}