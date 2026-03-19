#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    if (!(cin >> n >> m)) return 0;
    //{teacher_rating, {student_ratings}}
    //这里使用set会自动去重，所以改用vector
    vector<tuple<int, vector<int>>> ratings(n, tuple<int, vector<int>>(0, vector<int>()));
    for (int i = 0; i < n; ++i) {
        int teacher_rating;
        cin >> teacher_rating;
        get<0>(ratings[i]) = teacher_rating;
        for (int j = 0; j < n - 1; ++j) {
            int student_rating;
            cin >> student_rating;
            if (student_rating >= 0 && student_rating <= m) get<1>(ratings[i]).push_back(student_rating);
        }
    }
    //remove biggest and smallest
    for (int i = 0; i < n; ++i) {
        auto &student_ratings = get<1>(ratings[i]);
        sort(student_ratings.begin(), student_ratings.end());
        student_ratings.erase(student_ratings.begin());
        student_ratings.erase(prev(student_ratings.end()));
    }
    //calculate final ratings = (tec + avg of stu) / 2
    cout.setf(std::ios::fixed); cout << setprecision(0);
    for (int i = 0; i < n; ++i) {
        int teacher_rating = get<0>(ratings[i]);
        const auto &student_ratings = get<1>(ratings[i]);
        double student_avg = 0.0;
        for (int r : student_ratings) student_avg += r;
        student_avg /= student_ratings.size();
        double final_rating = (teacher_rating + student_avg) / 2.0;
        cout << round(final_rating) << '\n';
    }
}