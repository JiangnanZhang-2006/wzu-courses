#include <map>
#include <iostream>
#include <string>

using namespace std;

static void Insert();
static void Find();
static void Delete();

map < string, string > dic;

int main() {
	string cmd;
	while (true) {
		cin >> cmd;
		if (cmd == "Insert") Insert();
		else if (cmd == "Find") Find();
		else if (cmd == "Delete") Delete();
		else if (cmd == "Quit") break;
		
	}
}

void Insert() {
	string name, phone;
	cin >> name >> phone;
	//转小写
	for (char& c : name) {
		if (c <= 'Z' && c >= 'A') {
			c = c + 32;
		}
	}
	//查重
	bool flag = true;
	for (const auto& a : dic) {
		if (a.first == name) {
			flag = false;
			break;
		}
	}
	if (!flag) {
		cout << "Already Exist" << endl;
		return;
	}
	dic[name] = phone;
	cout << "Inserted" << endl;
	return;
}

void Find() {
	string name;
	cin >> name;
	//转小写
	for (char& c : name) {
		if (c <= 'Z' && c >= 'A') {
			c = c + 32;
		}
	}
	for (const auto& a : dic) {
		if (a.first == name) {
			cout << a.second << endl;
			return;
		}
	}
	cout << "Not Find" << endl;
	return;
}

void Delete() {
	string name;
	cin >> name;
	//转小写
	for (char& c : name) {
		if (c <= 'Z' && c >= 'A') {
			c = c + 32;
		}
	}
	auto it = dic.find(name);
	if (it != dic.end()) {
		dic.erase(it);
		cout << "Deleted" << endl;
		return;
	}
	cout << "Name Not Exist" << endl;
	return;
}