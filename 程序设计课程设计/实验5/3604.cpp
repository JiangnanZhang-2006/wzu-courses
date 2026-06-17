#include <iostream>
#include <cstring>
#include <tuple>
using namespace std;

class Klotski {
private:
    static const int CELL = 80, ROWS = 5, COLS = 4;
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
    void get_land(int x, int y, int& i, int& j) {
        i = y / CELL;
        j = x / CELL;
    }
    bool on_board(int i, int j) {
        return i >= 1 && i <= ROWS && j >= 1 && j <= COLS;
    }
    char get_char(int x, int y) {
        int i, j;
        get_land(x, y, i, j);
        if (!on_board(i, j)) return 0;
        return board[i - 1][j - 1];
    }
    void get_cell(int x, int y, int& row, int& col) {
        int i, j;
        get_land(x, y, i, j);
        row = i - 1;
        col = j - 1;
    }
    static bool is_soldier(char c) {
        return c >= '1' && c <= '4';
    }
    static bool is_general(char c) {
        return c >= 'A' && c <= 'E';
    }
    bool is_horizontal(char ch) {
        auto t = find_pos(ch);
        return get<2>(t) == 2 && get<3>(t) == 1;
    }
    bool is_vertical(char ch) {
        auto t = find_pos(ch);
        return get<2>(t) == 1 && get<3>(t) == 2;
    }
    bool can_soldier_move_to(char soldier, int to_row, int to_col) {
        if (to_row < 0 || to_row >= ROWS || to_col < 0 || to_col >= COLS || board[to_row][to_col] != '.') return false;
        auto t = find_pos(soldier);
        int r = get<0>(t), c = get<1>(t);
        if (r < 0) return false;
        int dr = to_row - r, dc = to_col - c;
        return (dr == 0 && (dc == 1 || dc == -1)) || (dc == 0 && (dr == 1 || dr == -1));
    }
    const char* move_direction_soldier(char soldier, int to_row, int to_col) {
        auto t = find_pos(soldier);
        int r = get<0>(t), c = get<1>(t);
        int dr = to_row - r, dc = to_col - c;
        if (dr == -1) return "Up";
        if (dr == 1) return "Down";
        if (dc == -1) return "Left";
        if (dc == 1) return "Right";
        return "";
    }
    void do_soldier_move(char soldier, int to_row, int to_col) {
        auto t = find_pos(soldier);
        int r = get<0>(t), c = get<1>(t);
        board[r][c] = '.';
        board[to_row][to_col] = soldier;
    }
    bool can_cao_move_up(int to_row, int to_col) {
        auto t = find_pos('@');
        int r = get<0>(t), c = get<1>(t);
        if (r < 0 || r == 0) return false;
        if (board[r - 1][c] != '.' || board[r - 1][c + 1] != '.') return false;
        return to_row == r - 1 && (to_col == c || to_col == c + 1);
    }
    bool can_cao_move_down(int to_row, int to_col) {
        auto t = find_pos('@');
        int r = get<0>(t), c = get<1>(t);
        if (r < 0 || r + 2 >= ROWS) return false;
        if (board[r + 2][c] != '.' || board[r + 2][c + 1] != '.') return false;
        return to_row == r + 2 && (to_col == c || to_col == c + 1);
    }
    bool can_cao_move_left(int to_row, int to_col) {
        auto t = find_pos('@');
        int r = get<0>(t), c = get<1>(t);
        if (r < 0 || c == 0) return false;
        if (board[r][c - 1] != '.' || board[r + 1][c - 1] != '.') return false;
        return (to_row == r || to_row == r + 1) && to_col == c - 1;
    }
    bool can_cao_move_right(int to_row, int to_col) {
        auto t = find_pos('@');
        int r = get<0>(t), c = get<1>(t);
        if (r < 0 || c + 2 >= COLS) return false;
        if (board[r][c + 2] != '.' || board[r + 1][c + 2] != '.') return false;
        return (to_row == r || to_row == r + 1) && to_col == c + 2;
    }
    void do_cao_move_up() {
        auto t = find_pos('@');
        int r = get<0>(t), c = get<1>(t);
        board[r - 1][c] = '@';
        board[r - 1][c + 1] = '@';
        board[r + 1][c] = '.';
        board[r + 1][c + 1] = '.';
    }
    void do_cao_move_down() {
        auto t = find_pos('@');
        int r = get<0>(t), c = get<1>(t);
        board[r + 2][c] = '@';
        board[r + 2][c + 1] = '@';
        board[r][c] = '.';
        board[r][c + 1] = '.';
    }
    void do_cao_move_left() {
        auto t = find_pos('@');
        int r = get<0>(t), c = get<1>(t);
        board[r][c - 1] = '@';
        board[r + 1][c - 1] = '@';
        board[r][c + 1] = '.';
        board[r + 1][c + 1] = '.';
    }
    void do_cao_move_right() {
        auto t = find_pos('@');
        int r = get<0>(t), c = get<1>(t);
        board[r][c + 2] = '@';
        board[r + 1][c + 2] = '@';
        board[r][c] = '.';
        board[r + 1][c] = '.';
    }
    bool can_hgen_move_up(char ch, int to_row, int to_col) {
        if (!is_horizontal(ch)) return false;
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        if (r == 0 || board[r - 1][c] != '.' || board[r - 1][c + 1] != '.') return false;
        return to_row == r - 1 && (to_col == c || to_col == c + 1);
    }
    bool can_hgen_move_down(char ch, int to_row, int to_col) {
        if (!is_horizontal(ch)) return false;
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        if (r + 1 >= ROWS || board[r + 1][c] != '.' || board[r + 1][c + 1] != '.') return false;
        return to_row == r + 1 && (to_col == c || to_col == c + 1);
    }
    bool can_hgen_move_left(char ch, int to_row, int to_col) {
        if (!is_horizontal(ch)) return false;
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        if (c == 0 || board[r][c - 1] != '.') return false;
        return to_row == r && to_col == c - 1;
    }
    bool can_hgen_move_right(char ch, int to_row, int to_col) {
        if (!is_horizontal(ch)) return false;
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        if (c + 2 >= COLS || board[r][c + 2] != '.') return false;
        return to_row == r && to_col == c + 2;
    }
    void do_hgen_move_up(char ch) {
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        board[r - 1][c] = ch;
        board[r - 1][c + 1] = ch;
        board[r][c] = '.';
        board[r][c + 1] = '.';
    }
    void do_hgen_move_down(char ch) {
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        board[r + 1][c] = ch;
        board[r + 1][c + 1] = ch;
        board[r][c] = '.';
        board[r][c + 1] = '.';
    }
    void do_hgen_move_left(char ch) {
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        board[r][c - 1] = ch;
        board[r][c + 1] = '.';
    }
    void do_hgen_move_right(char ch) {
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        board[r][c + 2] = ch;
        board[r][c] = '.';
    }
    bool can_vgen_move_up(char ch, int to_row, int to_col) {
        if (!is_vertical(ch)) return false;
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        if (r == 0 || board[r - 1][c] != '.') return false;
        return to_row == r - 1 && to_col == c;
    }
    bool can_vgen_move_down(char ch, int to_row, int to_col) {
        if (!is_vertical(ch)) return false;
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        if (r + 2 >= ROWS || board[r + 2][c] != '.') return false;
        return to_row == r + 2 && to_col == c;
    }
    bool can_vgen_move_left(char ch, int to_row, int to_col) {
        if (!is_vertical(ch)) return false;
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        if (c == 0 || board[r][c - 1] != '.' || board[r + 1][c - 1] != '.') return false;
        return (to_row == r || to_row == r + 1) && to_col == c - 1;
    }
    bool can_vgen_move_right(char ch, int to_row, int to_col) {
        if (!is_vertical(ch)) return false;
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        if (c + 1 >= COLS || board[r][c + 1] != '.' || board[r + 1][c + 1] != '.') return false;
        return (to_row == r || to_row == r + 1) && to_col == c + 1;
    }
    void do_vgen_move_up(char ch) {
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        board[r - 1][c] = ch;
        board[r + 1][c] = '.';
    }
    void do_vgen_move_down(char ch) {
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        board[r + 2][c] = ch;
        board[r][c] = '.';
    }
    void do_vgen_move_left(char ch) {
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        board[r][c - 1] = ch;
        board[r + 1][c - 1] = ch;
        board[r][c] = '.';
        board[r + 1][c] = '.';
    }
    void do_vgen_move_right(char ch) {
        auto t = find_pos(ch);
        int r = get<0>(t), c = get<1>(t);
        board[r][c + 1] = ch;
        board[r + 1][c + 1] = ch;
        board[r][c] = '.';
        board[r + 1][c] = '.';
    }
};

int main() {
    Klotski klotski;
    int x, y;
    char selected = 0;

    while (cin >> x >> y && (x != -1 || y != -1)) {
        int row, col, i, j;
        klotski.get_land(x, y, i, j);
        klotski.get_cell(x, y, row, col);

        char c = klotski.get_char(x, y);

        if (c == 0) {
            selected = 0;
            cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Unselect Chess" << endl;
            klotski.print();
            continue;
        }

        if (c == '.') {
            if (selected && Klotski::is_soldier(selected) && klotski.can_soldier_move_to(selected, row, col)) {
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Chess " << selected << " Move " << klotski.move_direction_soldier(selected, row, col) << endl;
                klotski.do_soldier_move(selected, row, col);
            } else if (selected == '@' && klotski.can_cao_move_up(row, col)) {
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Chess @ Move Up" << endl;
                klotski.do_cao_move_up();
            } else if (selected == '@' && klotski.can_cao_move_down(row, col)) {
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Chess @ Move Down" << endl;
                klotski.do_cao_move_down();
            } else if (selected == '@' && klotski.can_cao_move_left(row, col)) {
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Chess @ Move Left" << endl;
                klotski.do_cao_move_left();
            } else if (selected == '@' && klotski.can_cao_move_right(row, col)) {
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Chess @ Move Right" << endl;
                klotski.do_cao_move_right();
            } else if (selected && Klotski::is_general(selected) && klotski.can_hgen_move_up(selected, row, col)) {
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Chess " << selected << " Move Up" << endl;
                klotski.do_hgen_move_up(selected);
            } else if (selected && Klotski::is_general(selected) && klotski.can_hgen_move_down(selected, row, col)) {
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Chess " << selected << " Move Down" << endl;
                klotski.do_hgen_move_down(selected);
            } else if (selected && Klotski::is_general(selected) && klotski.can_hgen_move_left(selected, row, col)) {
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Chess " << selected << " Move Left" << endl;
                klotski.do_hgen_move_left(selected);
            } else if (selected && Klotski::is_general(selected) && klotski.can_hgen_move_right(selected, row, col)) {
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Chess " << selected << " Move Right" << endl;
                klotski.do_hgen_move_right(selected);
            } else if (selected && Klotski::is_general(selected) && klotski.can_vgen_move_up(selected, row, col)) {
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Chess " << selected << " Move Up" << endl;
                klotski.do_vgen_move_up(selected);
            } else if (selected && Klotski::is_general(selected) && klotski.can_vgen_move_down(selected, row, col)) {
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Chess " << selected << " Move Down" << endl;
                klotski.do_vgen_move_down(selected);
            } else if (selected && Klotski::is_general(selected) && klotski.can_vgen_move_left(selected, row, col)) {
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Chess " << selected << " Move Left" << endl;
                klotski.do_vgen_move_left(selected);
            } else if (selected && Klotski::is_general(selected) && klotski.can_vgen_move_right(selected, row, col)) {
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Chess " << selected << " Move Right" << endl;
                klotski.do_vgen_move_right(selected);
            } else {
                selected = 0;
                cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Unselect Chess" << endl;
            }
            klotski.print();
            continue;
        }

        selected = c;
        cout << "Click at (" << x << "," << y << "),Land in (" << i << "," << j << "),Select Chess " << c << endl;
        klotski.print();
    }
    return 0;
}
