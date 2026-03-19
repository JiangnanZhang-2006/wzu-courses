// #include <bits/stdc++.h>
// using namespace std;
// int main() {
//     size_t n;
//     cin >> n;
//     // {school, {tot, b, a, t, {names}}}
//     vector<pair<string, tuple<double, int, int, int, vector<string>>>> vec;
//     for (size_t i = 0; i < n; i++) {
//         char type;
//         string school, name;
//         int input;
//         cin >> type >> name>> input >> school;
//         for (char &c : school) {
//             c = tolower(c);
//         }
//         auto it = find_if(vec.begin(), vec.end(),
//                   [&school](const auto &p) { return p.first == school; });
//         if (it == vec.end()) {
//             vec.emplace_back(school, make_tuple(0.0, 0, 0, 0, vector<string>()));
//             it = prev(vec.end());
//         }
//         if (find(get<4>(it->second).begin(), get<4>(it->second).end(), name) == get<4>(it->second).end()) {
//             get<4>(it->second).push_back(name);
//         }
//         auto &t = it->second;
//         if (type == 'B') {
//             get<1>(t) += input;
//             get<0>(t) += input / 1.5;
//         } else if (type == 'A') {
//             get<2>(t) += input;
//             get<0>(t) += input;
//         } else if (type == 'T') {
//             get<3>(t) += input;
//             get<0>(t) += input * 1.5;
//         }
//     }
//     sort(vec.begin(), vec.end(),
//          [](const auto &a, const auto &b) {
//              int ta = static_cast<int>(get<0>(a.second));
//              int tb = static_cast<int>(get<0>(b.second));
//              if (ta != tb) return ta > tb;
//              if (get<4>(a.second).size() != get<4>(b.second).size())
//                  return get<4>(a.second).size() < get<4>(b.second).size();
//              return a.first < b.first;
//          });
//     cout << vec.size() << '\n';
//     int rank = 1;
//     for (size_t i = 0; i < vec.size(); ++i) {
//         int cur = static_cast<int>(get<0>(vec[i].second));
//         if (i > 0) {
//             int prev = static_cast<int>(get<0>(vec[i - 1].second));
//             if (cur < prev) rank = i + 1;
//         }
//         cout << rank << ' ' << vec[i].first << ' ' << cur << ' ' << get<4>(vec[i].second).size() << '\n';
//     }
// }
// 输入格式：题目是"准考证号 得分 学校"，但代码按"类型 姓名 分数 学校"读取

// 去重：应该根据准考证号去重，而不是姓名
