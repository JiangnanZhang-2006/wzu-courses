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
int main() {
    string command;
    vector<df> dataframe;
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
            cout << "Insert:" << endl;
            //查找是否存在重复
            auto target = find_if(dataframe.begin(), dataframe.end(), [id](const df& a) { return a.id == id;});

            if (target == dataframe.end()) { //如果没有找到，则插入
                double total_score = score_chn + score_math + score_eng;
                double avg_score = total_score / 3.0;
                dataframe.push_back({ id, name, sex, birth_y, birth_m, birth_d,
                    score_chn, score_math, score_eng, avg_score, total_score });
                printf("%s %s %c %d %d %d %.1lf %.1lf %.1lf %.1lf %.1lf\n",
                id.c_str(), name.c_str(), sex, birth_y, birth_m, birth_d,
                score_chn, score_math, score_eng, avg_score, total_score);
            }
            else {
                cout << "Failed" << endl;
            }
        }
        else if (command == "List") {
            cout << "List:" << endl;
            for (const auto& row : dataframe) {
                cout << row.id << " " << row.name << " " << row.sex << " " << row.birth_y << " "
                    << row.birth_m << " " << row.birth_d << " " << fixed << setprecision(1)
                    << row.score_chn << " " << row.score_math << " " << row.score_eng << " "
                    << row.avg_score << " " << row.total_score << endl;
            }
        }
        else if (command == "Find") {
            string id;
            cin >> id;
            auto target = find_if(dataframe.begin(), dataframe.end(), [id](const df& a) { return a.id == id;});
            cout << "Find:" << endl;
            if (target != dataframe.end()) {
                cout << target->id << " " << target->name << " " << target->sex << " "
                << target->birth_y << " " << target->birth_m << " " << target->birth_d
                << " " << fixed << setprecision(1) << target->score_chn << " " 
                << target->score_math << " " << target->score_eng << " " << target->avg_score 
                << " " << target->total_score << endl;
            }
            else {
                cout << "Failed" << endl;
            }
        }
        else {
            cout << "Unknown command!" << endl;
        }
    }
    return 0;
}