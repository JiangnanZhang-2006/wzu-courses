#include <bits/stdc++.h>
using namespace std;

int main() {
    int stu_num, question_num;
    bool has_fault = false;
    cin >> stu_num >> question_num;
    //{score_of_this_question, {num_of_choices, {correct_choices}}}
    vector<pair<int, pair<int, vector<char>>>> questions(question_num, {0, {0, vector<char>(0, '\0')}});
    //{wrong_count}
    vector<int> wrong_stats(question_num, 0);
    for (int i = 0; i < question_num; ++i) {
        int score, num_of_choices, num_of_correct;
        cin >> score >> num_of_choices >> num_of_correct;
        questions[i].first = score;
        questions[i].second.first = num_of_choices;
        for (int j = 0; j < num_of_correct; ++j) {
            char correct_choice;
            cin >> correct_choice;
            questions[i].second.second.push_back(correct_choice);
        }
    }
    for (int i = 0; i < stu_num; ++i) {
        int total_score = 0;
        for (int j = 0; j < question_num; ++j) {
            int num_of_selected;
            char bracket;
            cin >> bracket; // (
            cin >> num_of_selected;
            vector<char> selected_choices;
            for (int k = 0; k < num_of_selected; ++k) {
                char selected_choice;
                cin >> selected_choice;
                selected_choices.push_back(selected_choice);
            }
            cin >> bracket; // )
            sort(selected_choices.begin(), selected_choices.end());
            vector<char> correct_choices = questions[j].second.second;
            sort(correct_choices.begin(), correct_choices.end());
            if (selected_choices == correct_choices) {
                total_score += questions[j].first;
            } else {
                has_fault = true;
                wrong_stats[j]++;
            }
        }
        cout << total_score << endl;
    }
    if (!has_fault) {
        cout << "Too simple" << endl;
    }
    else {
        int max_wrong = *max_element(wrong_stats.begin(), wrong_stats.end());
        bool flag = false;
        cout << max_wrong;
        for (int i = 0; i < question_num; ++i) { 
            if (wrong_stats[i] == max_wrong) {
                cout << (flag ? " " : " ") << (i + 1);
                flag = true;
            }
        }
        cout << endl;
    }
}