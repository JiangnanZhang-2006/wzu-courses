#include <bits/stdc++.h>

using namespace std;
struct crew {
    string name;
    double tot;
    double prime;
    double floating;
    double reward;

};
int main() {
    vector<crew> crewlist;
    int len;
    cin >> len;
    for (int i = 0; i < len; i++) {
        string temp0;
        double temp1, temp2, temp3;
        cin >> temp0 >> temp1 >> temp2 >> temp3;
        crewlist.push_back({ temp0, temp1 + temp2 + temp3, temp1, temp2, temp3 });
    }
    //sort&output
    for (int i = 0; i < len; i++) {
        double max = 0;
        for (const auto& it : crewlist) {
            if (it.tot > max) {
                max = it.tot;
            }
        }
        for (auto& it : crewlist) {
            if (it.tot == max) {
                cout << it.name << " " << fixed << setprecision(2) << it.tot << endl;
                it.tot = -1;
            }
        }
    }
    return 0;
}