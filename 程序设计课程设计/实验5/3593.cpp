#include <iostream>
#include <cstring>
#include <tuple>
#include <vector>
using namespace std;

class Klotski {
private:
    char board[5][4];
public:
    Klotski() {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 4; j++) {
                cin >> board[i][j];
            }
        }
    }
    tuple<int, int, int, int> find_pos(char c) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == c) {
                    int len_i = 1;
                    int len_j = 1;
                    while (i + len_i < 5 && board[i + len_i][j] == c) {
                        len_i++;
                    }
                    while (j + len_j < 4 && board[i][j + len_j] == c) {
                        len_j++;
                    }
                    return make_tuple(i, j, len_j, len_i);

                }
            }
        }
        return make_tuple(-1, -1, -1, -1);
    }
    void describe() {
        vector<tuple<int, int, int, int>> positions;
        positions.push_back(find_pos('@'));
        positions.push_back(find_pos('A'));
        positions.push_back(find_pos('B'));
        positions.push_back(find_pos('C'));
        positions.push_back(find_pos('D'));
        positions.push_back(find_pos('E'));
        positions.push_back(find_pos('1'));
        positions.push_back(find_pos('2'));
        positions.push_back(find_pos('3'));
        positions.push_back(find_pos('4'));
        // positions.push_back(find_pos('.'));
        for (const auto &pos : positions) {
            cout << get<0>(pos) << " " << get<1>(pos) << " " << get<2>(pos) << " " << get<3>(pos) << endl;
        }
    }
};

int main() {
    Klotski klotski;
    klotski.describe();
    return 0;
}