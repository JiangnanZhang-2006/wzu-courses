#include <bits/stdc++.h>
using namespace std;

struct df {
    string id;
    string name;
    char sex;
    int birth_y;
    int birth_m;
    int birth_d;
    double score_chn;
    double score_math;
    double score_eng;
    double avg_score;
    double total_score;
};

vector<df> dataframe;

void printStudent(const df& student) {
    cout << student.id << " " << student.name << " " << student.sex << " "
        << student.birth_y << " " << student.birth_m << " " << student.birth_d << " "
        << fixed << setprecision(1) << student.score_chn << " " << student.score_math << " "
        << student.score_eng << " " << student.avg_score << " " << student.total_score << endl;
}

auto findStudent(const string& id) {
    return find_if(dataframe.begin(), dataframe.end(),
        [id](const df& a) { return a.id == id; });
}

void Insert() {
    string id, name;
    char sex;
    int birth_y, birth_m, birth_d;
    double score_chn, score_math, score_eng;

    cin >> id >> name >> sex >> birth_y >> birth_m >> birth_d >> score_chn >> score_math >> score_eng;
    cout << "Insert:" << endl;

    if (findStudent(id) != dataframe.end()) {
        cout << "Failed" << endl;
        return;
    }

    double total_score = score_chn + score_math + score_eng;
    double avg_score = total_score / 3.0;
    dataframe.push_back({ id, name, sex, birth_y, birth_m, birth_d,
                        score_chn, score_math, score_eng, avg_score, total_score });
    printStudent(dataframe.back());
}

void List() {
    cout << "List:" << endl;
    for (const auto& student : dataframe) {
        printStudent(student);
    }
}

void Find() {
    string id;
    cin >> id;
    cout << "Find:" << endl;
    auto target = findStudent(id);
    if (target != dataframe.end()) {
        printStudent(*target);
    }
    else {
        cout << "Failed" << endl;
    }
}

void Change() {
    string id, name;
    char sex;
    int birth_y, birth_m, birth_d;
    double score_chn, score_math, score_eng;
    cin >> id >> name >> sex >> birth_y >> birth_m >> birth_d >> score_chn >> score_math >> score_eng;
    cout << "Change:" << endl;

    auto target = findStudent(id);
    if (target == dataframe.end()) {
        cout << "Failed" << endl;
        return;
    }

    double total_score = score_chn + score_math + score_eng;
    double avg_score = total_score / 3.0;
    *target = { id, name, sex, birth_y, birth_m, birth_d,
              score_chn, score_math, score_eng, avg_score, total_score };
    printStudent(*target);
}

void Delete() {
    string id;
    cin >> id;
    cout << "Delete:" << endl;
    auto it = remove_if(dataframe.begin(), dataframe.end(),
        [id](const df& a) { return a.id == id; });

    if (it != dataframe.end()) {
        dataframe.erase(it, dataframe.end());
        cout << "Deleted" << endl;
    }
    else {
        cout << "Failed" << endl;
    }
}

void bubbleSort(vector<df>& students, function<bool(const df&, const df&)> compare) {
    int n = students.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - 1 - i; j++) {
            if (compare(students[j + 1], students[j])) {
                swap(students[j], students[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void Sort() {
    string kind;
    cin >> kind;
    cout << "Sort:" << endl;

    vector<df> sorted_data = dataframe;

    if (kind == "byid") {
        bubbleSort(sorted_data, [](const df& a, const df& b) { return a.id < b.id; });
    }
    else if (kind == "bybirthday") {
        bubbleSort(sorted_data, [](const df& a, const df& b) {
            if (a.birth_y != b.birth_y) return a.birth_y < b.birth_y;
            if (a.birth_m != b.birth_m) return a.birth_m < b.birth_m;
            return a.birth_d < b.birth_d;
            });
    }
    else if (kind == "bysum") {
        bubbleSort(sorted_data, [](const df& a, const df& b) {
            return a.total_score < b.total_score;
            });
    }

    for (const auto& student : sorted_data) {
        printStudent(student);
    }
}

int main() {
    string command;
    while (cin >> command) {
        if (command == "Quit" || command == "Exit") {
            cout << "Good bye!" << endl;
            break;
        }
        else if (command == "Insert") Insert();
        else if (command == "List") List();
        else if (command == "Find") Find();
        else if (command == "Change") Change();
        else if (command == "Delete") Delete();
        else if (command == "Sort") Sort();
        else cout << "Unknown command!" << endl;
    }
    return 0;
}