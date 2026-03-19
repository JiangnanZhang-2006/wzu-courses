#include <bits/stdc++.h>
using namespace std;

struct Student {
    char name[25];
    int exam;
    int classScore;
    char isLeader;
    char isWest;
    int papers;
    int total;
};

int main() {
    int N;
    cin >> N;
    Student stu[105] = { 0 };
    int allTotal = 0;
    int maxTotal = -1;
    int maxIndex = 0;

    for (int i = 0; i < N; i++) {
        cin >> stu[i].name >> stu[i].exam >> stu[i].classScore >> stu[i].isLeader >> stu[i].isWest >> stu[i].papers;
        stu[i].total = 0;

        if (stu[i].exam > 80 && stu[i].papers >= 1) {
            stu[i].total += 8000;
        }
        if (stu[i].exam > 85 && stu[i].classScore > 80) {
            stu[i].total += 4000;
        }
        if (stu[i].exam > 90) {
            stu[i].total += 2000;
        }
        if (stu[i].exam > 85 && stu[i].isWest == 'Y') {
            stu[i].total += 1000;
        }
        if (stu[i].classScore > 80 && stu[i].isLeader == 'Y') {
            stu[i].total += 850;
        }

        allTotal += stu[i].total;
        if (stu[i].total > maxTotal) {
            maxTotal = stu[i].total;
            maxIndex = i;
        }
    }

    cout << stu[maxIndex].name << endl;
    cout << maxTotal << endl;
    cout << allTotal << endl;

    return 0;
}