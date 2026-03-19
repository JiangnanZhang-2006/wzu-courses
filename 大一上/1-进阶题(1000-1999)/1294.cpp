#include <bits/stdc++.h>

using namespace std;
struct student {
    string name;
    double tot;
    double c;
    double english;
    double math;
    bool sorted;
};
int main() {
    vector<student> students;
    string temp0;
    double temp1, temp2, temp3;

    while (cin >> temp0 >> temp1 >> temp2 >> temp3) {
        students.push_back({ temp0, temp1 + temp2 + temp3, temp1, temp2, temp3, false });
    }
    //sort&output
    for (int i = 0; i < students.size(); i++) {
        double max = 0;
        for (const auto& it : students) {
            if (it.tot > max && !it.sorted) {
                max = it.tot;
            }
        }
        for (auto& it : students) {
            if (it.tot == max) {
                cout << it.name << " " << fixed << setprecision(1) << it.c << ' ' << it.english << " " << it.math << " " << it.tot << endl;
                it.sorted = true;
            }
        }
    }
    return 0;
}