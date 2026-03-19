#include <iostream>
#include <cstring>
#include <tuple>
using namespace std;

class Klotski {
private:
    static const int OFFSET = 80, CELL = 80, ROWS = 5, COLS = 4;
    char board[ROWS][COLS];
public:
    Klotski() {
        memset(board, 0, sizeof(board));
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                cin >> board[i][j];
            }
        }
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
    void print() {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                cout << board[i][j];
            }
            cout << endl;
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
    void get_cell(int x, int y, int& row, int& col) {
        row = transform(y);
        col = transform(x);
    }
    static bool is_soldier(char c) {
        return c >= '1' && c <= '4';
    }
    bool can_soldier_move_to(char soldier, int to_row, int to_col) {
        if (!in_bounds(to_row, to_col) || board[to_row][to_col] != '.') return false;
        auto t = find_pos(soldier);
        int r = get<0>(t), c = get<1>(t);
        if (r < 0) return false;
        int dr = to_row - r, dc = to_col - c;
        return (dr == 0 && (dc == 1 || dc == -1)) || (dc == 0 && (dr == 1 || dr == -1));
    }
    const char* move_direction(char soldier, int to_row, int to_col) {
        auto t = find_pos(soldier);
        int r = get<0>(t), c = get<1>(t);
        int dr = to_row - r, dc = to_col - c;
        if (dr == -1) return "Up";
        if (dr == 1) return "Down";
        if (dc == -1) return "Left";
        if (dc == 1) return "Right";
        return "";
    }
    void do_move(char soldier, int to_row, int to_col) {
        auto t = find_pos(soldier);
        int r = get<0>(t), c = get<1>(t);
        board[r][c] = '.';
        board[to_row][to_col] = soldier;
    }
};

int main() {
    Klotski klotski;
    int x, y;
    char selected = 0;  // no selection

    while (cin >> x >> y && (x != -1 || y != -1)) {
        int row, col;
        klotski.get_cell(x, y, row, col);
        int i = row + 1, j = col + 1;  // 1-based for output
        if (i < 1) i = 1;
        if (i > 5) i = 5;
        if (j < 1) j = 1;
        if (j > 4) j = 4;

        char c = klotski.get_char(x, y);

        if (c == 0 || !klotski.in_bounds(row, col)) {
            selected = 0;
            cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Unselect Chess" << endl;
            klotski.print();
            continue;
        }

        if (c == '.') {
            if (selected && Klotski::is_soldier(selected) && klotski.can_soldier_move_to(selected, row, col)) {
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Chess " << selected << " Move " << klotski.move_direction(selected, row, col) << endl;
                klotski.do_move(selected, row, col);
            } else {
                selected = 0;
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Unselect Chess" << endl;
            }
            klotski.print();
            continue;
        }

        if (Klotski::is_soldier(c)) {
            selected = c;
            cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Select Chess " << c << endl;
            klotski.print();
            continue;
        }

        selected = c;
        cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Select Chess " << c << endl;
        klotski.print();
    }
    return 0;
}
