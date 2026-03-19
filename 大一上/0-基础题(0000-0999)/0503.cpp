#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Employee {
    string id;
    string name;
    char sex;
    int age;
    string edu;
    double wage;
    string address;
    string tel;
};

vector<Employee> employees;

bool compareEmployees(const Employee& a, const Employee& b) {
    if (a.wage != b.wage) {
        return a.wage < b.wage;
    }
    return a.id < b.id;
}

int findEmployeeIndex(const string& id) {
    for (int i = 0; i < employees.size(); i++) {
        if (employees[i].id == id) {
            return i;
        }
    }
    return -1;
}

int main() {
    string command;

    while (cin >> command) {
        if (command == "INSERT") {
            Employee emp;
            cin >> emp.id >> emp.name >> emp.sex >> emp.age >> emp.edu >> emp.wage >> emp.address >> emp.tel;

            if (findEmployeeIndex(emp.id) == -1) {
                employees.push_back(emp);
                cout << "Inserted" << endl;
            }
            else {
                cout << "Failed" << endl;
            }
        }
        else if (command == "VIEW") {
            string id;
            cin >> id;

            int index = findEmployeeIndex(id);
            if (index != -1) {
                Employee& emp = employees[index];
                cout << emp.id << " " << emp.name << " " << emp.sex << " " << emp.age << " "
                    << emp.edu << " " << fixed << setprecision(2) << emp.wage << " "
                    << emp.address << " " << emp.tel << endl;
            }
            else {
                cout << "Failed" << endl;
            }
        }
        else if (command == "FIND") {
            string relation;
            double wage;
            cin >> relation >> wage;

            vector<Employee> result;
            for (const auto& emp : employees) {
                if (relation == ">" && emp.wage > wage) {
                    result.push_back(emp);
                }
                else if (relation == "<" && emp.wage < wage) {
                    result.push_back(emp);
                }
                else if (relation == "=" && emp.wage == wage) {
                    result.push_back(emp);
                }
            }

            if (result.empty()) {
                cout << "NOT FIND" << endl;
            }
            else {
                sort(result.begin(), result.end(), compareEmployees);
                for (const auto& emp : result) {
                    cout << emp.id << " " << emp.name << " " << emp.sex << " " << emp.age << " "
                        << emp.edu << " " << fixed << setprecision(2) << emp.wage << " "
                        << emp.address << " " << emp.tel << endl;
                }
            }
        }
        else if (command == "SORT") {
            vector<Employee> sortedEmployees = employees;
            sort(sortedEmployees.begin(), sortedEmployees.end(), compareEmployees);

            for (const auto& emp : sortedEmployees) {
                cout << emp.id << " " << emp.name << " " << emp.sex << " " << emp.age << " "
                    << emp.edu << " " << fixed << setprecision(2) << emp.wage << " "
                    << emp.address << " " << emp.tel << endl;
            }
        }
        else if (command == "DELETE") {
            string id;
            cin >> id;

            int index = findEmployeeIndex(id);
            if (index != -1) {
                employees.erase(employees.begin() + index);
                cout << "Deleted" << endl;
            }
            else {
                cout << "Failed" << endl;
            }
        }
        else if (command == "CHANGE") {
            string oldId, newId;
            Employee emp;
            cin >> oldId >> newId >> emp.name >> emp.sex >> emp.age >> emp.edu >> emp.wage >> emp.address >> emp.tel;
            emp.id = newId;

            int oldIndex = findEmployeeIndex(oldId);
            if (oldIndex == -1) {
                cout << "Failed" << endl;
                continue;
            }

            if (oldId != newId && findEmployeeIndex(newId) != -1) {
                cout << "Failed" << endl;
                continue;
            }

            employees[oldIndex] = emp;
            cout << "Changed" << endl;
        }
        else if (command == "QUIT" || command == "EXIT") {
            cout << "Good bye!" << endl;
            break;
        }
    }

    return 0;
}