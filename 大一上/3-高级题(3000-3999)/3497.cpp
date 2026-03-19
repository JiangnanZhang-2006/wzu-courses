#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    struct Question { int full; int optCnt; int correctCnt; set<char> correct; };
    vector<Question> qs(M);
    for (int i = 0; i < M; ++i) {
        int full, optCnt, correctCnt;
        cin >> full >> optCnt >> correctCnt;
        qs[i].full = full;
        qs[i].optCnt = optCnt;
        qs[i].correctCnt = correctCnt;
        for (int k = 0; k < correctCnt; ++k) {
            char c; cin >> c;
            qs[i].correct.insert(c);
        }
    }

    string line;
    getline(cin, line); // consume end of last line

    // errors per question per option (a-e)
    vector<array<int,26>> errors(M);
    for (int i = 0; i < M; ++i) errors[i].fill(0);

    cout.setf(std::ios::fixed); cout << setprecision(1);

    for (int stu = 0; stu < N; ++stu) {
        getline(cin, line);
        if (line.size() == 0) { stu--; continue; }
        // parse line containing M groups like: (k a b ...)
        vector<set<char>> answers;
        answers.reserve(M);

        size_t p = 0;
        for (int q = 0; q < M; ++q) {
            // find next '('
            while (p < line.size() && line[p] != '(') ++p;
            if (p >= line.size()) break;
            ++p; // skip '('
            // read number
            while (p < line.size() && isspace((unsigned char)line[p])) ++p;
            int k = 0;
            while (p < line.size() && isdigit((unsigned char)line[p])) {
                k = k * 10 + (line[p] - '0'); ++p;
            }
            set<char> sel;
            // read k option letters
            for (int t = 0; t < k; ++t) {
                while (p < line.size() && !isalpha((unsigned char)line[p])) ++p;
                if (p < line.size() && isalpha((unsigned char)line[p])) {
                    sel.insert(line[p]); ++p;
                }
            }
            // move to next ')'
            while (p < line.size() && line[p] != ')') ++p;
            if (p < line.size() && line[p] == ')') ++p;
            answers.push_back(move(sel));
        }

        double total = 0.0;
        for (int j = 0; j < M; ++j) {
            const set<char>& sel = answers[j];
            const set<char>& cor = qs[j].correct;

            bool hasWrong = false;
            for (char c : sel) if (! (cor.count(c))) { hasWrong = true; break; }

            if (hasWrong) {
                // student selected some wrong options -> zero score
                // count errors: each selected wrong option increments its error
                for (char c : sel) if (! (cor.count(c))) errors[j][c - 'a']++;
                // also count missed correct options
                for (char c : cor) if (! (sel.count(c))) errors[j][c - 'a']++;
            } else {
                if (sel.size() == cor.size() && equal(sel.begin(), sel.end(), cor.begin())) {
                    // full score
                    total += qs[j].full;
                } else {
                    // selected subset of correct (partial), no wrong -> 50%
                    total += qs[j].full / 2.0;
                    // count missed correct options as errors
                    for (char c : cor) if (! (sel.count(c))) errors[j][c - 'a']++;
                }
            }
        }
        cout << total << '\n';
    }

    // find max error count
    int maxErr = 0;
    for (int j = 0; j < M; ++j) for (int a = 0; a < 26; ++a) maxErr = max(maxErr, errors[j][a]);
    if (maxErr == 0) {
        cout << "Too simple" << '\n';
        return 0;
    }

    // collect all (count, qindex, option) where count == maxErr
    vector<tuple<int,int,char>> out;
    for (int j = 0; j < M; ++j) {
        for (int a = 0; a < 26; ++a) {
            if (errors[j][a] == maxErr) {
                out.emplace_back(maxErr, j + 1, char('a' + a));
            }
        }
    }

    // sort by question index then option
    sort(out.begin(), out.end(), [](const auto &A, const auto &B){
        if (get<1>(A) != get<1>(B)) return get<1>(A) < get<1>(B);
        return get<2>(A) < get<2>(B);
    });

    for (auto &t : out) {
        cout << get<0>(t) << ' ' << get<1>(t) << '-' << get<2>(t) << '\n';
    }

    return 0;
}
