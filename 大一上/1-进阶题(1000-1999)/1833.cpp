#include <bits/stdc++.h>
using namespace std;

int main() {
    string command;

    while (cin >> command) {
        if (command == "Quit" || command == "Exit") {
            cout << "Good bye!" << endl;
            break;
        }
        else if (command == "Insert") {
            string id, name;             //使用int型的的id会都是前面的0
            char sex;
            int birth_y, birth_m, birth_d;
            double score_chn, score_math, score_eng;

            cin >> id >> name >> sex >> birth_y >> birth_m >> birth_d >> score_chn >> score_math >> score_eng;

            double total_score = score_chn + score_math + score_eng;
            double avg_score = total_score / 3.0;

            cout << "Insert:" << endl;
            printf("%s %s %c %d %d %d %.1lf %.1lf %.1lf %.1lf %.1lf\n",
                id.c_str(), name.c_str(), sex, birth_y, birth_m, birth_d,
                score_chn, score_math, score_eng, avg_score, total_score);
        }
    }
    return 0;
}