#include <bits/stdc++.h>

using namespace std;

int tot[150];
int need[150];

int main() {
    char temp;
    int totCnt = 0, needCnt = 0;

    temp = getchar();
    while (temp != '\n') {
        tot[temp]++;
        totCnt++;
        temp = getchar();
    }

    temp = getchar();
    while (temp != '\n') {
        need[temp]++;
        needCnt++;
        temp = getchar();
    }
    int more = 0;
    for (int i = 0; i < 150; i++) {
        if (need[i] > tot[i]) {
            more += need[i] - tot[i];
        }
    }
    if (more) {
        cout << "No " << more << endl;
    }
    else {
        cout << "Yes " << totCnt - needCnt << endl;
    }
}