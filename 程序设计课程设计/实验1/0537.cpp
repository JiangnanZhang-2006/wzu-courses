#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

class Student {
private:
    string id;
    string name;
    char sex;
    double score1;
    double score2;
    double score3;
    double total;

public:
    Student(string id, string name, char sex, double s1, double s2, double s3)
        : id(id), name(name), sex(sex), score1(s1), score2(s2), score3(s3) {
        total = s1 + s2 + s3;
    }

    string getId() const { return id; }
    
    void print() const {
        cout << id << " " << name << " " << sex << fixed << setprecision(1)
             << " " << score1 << " " << score2 << " " << score3 << endl;
    }

    void update(string newName, char newSex, double s1, double s2, double s3) {
        name = newName;
        sex = newSex;
        score1 = s1;
        score2 = s2;
        score3 = s3;
        total = s1 + s2 + s3;
    }
};

class StudentManager {
private:
    vector<Student> students;

public:
    void insert() {
        string id, name;
        char sex;
        double s1, s2, s3;
        cin >> id >> name >> sex >> s1 >> s2 >> s3;
        
        auto duplicate = find_if(students.begin(), students.end(), 
            [&id](const Student& s) { return s.getId() == id; });
        if (duplicate != students.end()) {
            cout << "Failed" << endl;
            return;
        }
        
        auto it = find_if(students.begin(), students.end(), 
            [&id](const Student& s) { return s.getId() > id; });
        
        auto inserted = students.insert(it, Student(id, name, sex, s1, s2, s3));
        inserted->print();
    }

    void list() {
        for (const auto& student : students) {
            student.print();
        }
    }

    void find() {
        string id;
        cin >> id;
        auto it = find_if(students.begin(), students.end(), 
            [&id](const Student& s) { return s.getId() == id; });
        if (it != students.end()) {
            it->print();
        } else {
            cout << "Failed" << endl;
        }
    }

    void change() {
        string id;
        cin >> id;
        auto it = find_if(students.begin(), students.end(), 
            [&id](const Student& s) { return s.getId() == id; });
        if (it != students.end()) {
            string name;
            char sex;
            double s1, s2, s3;
            cin >> name >> sex >> s1 >> s2 >> s3;
            it->update(name, sex, s1, s2, s3);
            it->print();
        } else {
            cout << "Failed" << endl;
        }
    }

    void remove() {
        string id;
        cin >> id;
        auto it = find_if(students.begin(), students.end(), 
            [&id](const Student& s) { return s.getId() == id; });
        if (it != students.end()) {
            cout << "Deleted" << endl;
            students.erase(it);
        } else {
            cout << "Failed" << endl;
        }
    }
};

int main() {
    StudentManager manager;
    string cmd;
    
    while (cin >> cmd) {
        if (cmd == "Insert") {
            cout << "Insert:" << endl;
            manager.insert();
        } else if (cmd == "List") {
            cout << "List:" << endl;
            manager.list();
        } else if (cmd == "Find") {
            cout << "Find:" << endl;
            manager.find();
        } else if (cmd == "Change") {
            cout << "Change:" << endl;
            manager.change();
        } else if (cmd == "Delete") {
            cout << "Delete:" << endl;
            manager.remove();
        } else if (cmd == "Quit") {
            cout << "Good bye!" << endl;
            break;
        }
    }
    
    return 0;
}