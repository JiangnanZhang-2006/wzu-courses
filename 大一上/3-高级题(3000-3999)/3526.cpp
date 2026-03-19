#include <iostream>
#include <tuple>
#include <unordered_map>
#include <algorithm>
using namespace std;


int main() {
    // {id, {price, cnt, tot}}
    unordered_map<string, tuple<int, int, int>> books;
    int n;
    if (!(cin >> n)) return 0;
    for (int i = 0; i < n; ++i) {
        string s;
        int p, c;
        cin >> s >> p >> c;
        if (books.find(s) == books.end()) {
            books[s] = make_tuple(p, c, p * c);
        } else {
            auto &[price, cnt, tot] = books[s];
            cnt += c;
            tot += p * c;
        }
    }
    auto it = max_element(books.begin(), books.end(), [](const auto &a, const auto &b) {
        return get<1>(a.second) < get<1>(b.second);
    });
    cout << it->first << " " << get<1>(it->second) << "\n";
    it = max_element(books.begin(), books.end(), [](const auto &a, const auto &b) {
        return get<2>(a.second) < get<2>(b.second);
    });
    cout << it->first << " " << get<2>(it->second) << "\n";
}