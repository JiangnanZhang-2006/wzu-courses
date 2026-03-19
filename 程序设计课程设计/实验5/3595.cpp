#include <iostream>
#include <cstring>
#include <tuple>
#include <vector>
using namespace std;

class Klotski {
private:
    static const int OFFSET = 80, CELL = 80, ROWS = 5, COLS = 4;
    char board[5][4];
public:
    Klotski() {
        memset(board, 0, sizeof(board));
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                cin >> board[i][j];
            }
        }
    }
    tuple<int, int, int, int> find_pos(int x, int y) {
        return find_pos(get_char(x, y));
    }
    tuple<int, int, int, int> find_pos(char c) {
        if (c == 0 || c == '.') {
            return make_tuple(-1, -1, -1, -1);
        }
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] == c) {
                    int len_i = 1;
                    int len_j = 1;
                    while (i + len_i < ROWS && board[i + len_i][j] == c) {
                        len_i++;
                    }
                    while (j + len_j < COLS && board[i][j + len_j] == c) {
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
    int transform(int x) {
        return (x - OFFSET) / CELL;
    }
    bool in_bounds(int row, int col) {
        return row >= 0 && row < ROWS && col >= 0 && col < COLS;
    }
    char get_char(int x, int y) {
        if (x < OFFSET || y < OFFSET) return 0;
        int row = transform(y), col = transform(x);
        if (!in_bounds(row, col)) return 0;
        return board[row][col];
    }
};

int main() {
    Klotski klotski;
    // klotski.describe();
    int x, y;

    while (cin >> x >> y && x != -1 && y != -1) {
        char c = klotski.get_char(x, y);
        if (c == 0 || c == '.') {
            cout << "Unselect" << endl;
        } else {
            tuple<int, int, int, int> pos = klotski.find_pos(x, y);
            int i = get<0>(pos), j = get<1>(pos), w = get<2>(pos), h = get<3>(pos);
            cout << "Select " << c << " " << i << " " << j << " " << w << " " << h << endl;
        }
    }
    return 0;
}