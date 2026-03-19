#include <bits/stdc++.h>
using namespace std;

int main() {
    //id -> gp, gmid_term, gfinal
    unordered_map<string, tuple<int,int,int>> students;
    int lenp, lenmid_term, lenfinal;
    if (!(cin >> lenp >> lenmid_term >> lenfinal)) return 0;
    for (int i = 0; i < lenp; ++i) {
        string id; int gp;
        cin >> id >> gp;
        students[id] = make_tuple(gp, -1, -1);
    }
    for (int i = 0; i < lenmid_term; ++i) {
        string id; int gmid;
        cin >> id >> gmid;
        auto it = students.find(id);
        if (it != students.end()) {
            get<1>(it->second) = gmid;
        } else {
            students[id] = make_tuple(-1, gmid, -1);
        }
    }
    for (int i = 0; i < lenfinal; ++i) {
        string id; int gfinal;
        cin >> id >> gfinal;
        auto it = students.find(id);
        if (it != students.end()) {
            get<2>(it->second) = gfinal;
        } else {
            students[id] = make_tuple(-1, -1, gfinal);
        }
    }
    vector<tuple<string, int, int, int, int>> output; //id, gp, gmid, gfinal, gtotal
    for (const auto &p : students) {
        const string &id = p.first;
        int gp = get<0>(p.second);
        int gmid = get<1>(p.second) == -1 ? 0 : get<1>(p.second);
        int gfinal = get<2>(p.second) == -1 ? 0 : get<2>(p.second);
        if (gp < 200) continue;
        int gtotal = 0;
        if (gmid > gfinal) {
            gtotal = (int)round(0.4 * gmid + 0.6 * gfinal);
        } else {
            gtotal = gfinal;
        }
        if (gtotal >= 60) {
            output.emplace_back(id, gp, get<1>(p.second), get<2>(p.second), gtotal);
        }
    }
    sort(output.begin(), output.end(), [](const auto &A, const auto &B){
        return get<4>(A) == get<4>(B) ? get<0>(A) < get<0>(B) : get<4>(A) > get<4>(B);
    });
    for (const auto &t : output) {
        cout << get<0>(t) << ' ' << get<1>(t) << ' ' << get<2>(t) << ' ' << get<3>(t) << ' ' << get<4>(t) << '\n';
    }
}