#include <iostream>
#include <cstring>

using namespace std;

class Point {
    private:
        int x, y, value;

    public:
        Point(int x, int y, int value) : x(x), y(y), value(value) {}
        int getX() const { return x; }
        int getY() const { return y; }
        int getValue() const { return value; }
        void setX(int x) { this->x = x; }
        void setY(int y) { this->y = y; }
        void print() const { cout << x << " " << y << endl; }
};

class Board {
    private:
        int board[4][4];

    public:
        Board(Point a, Point b) {
            memset(board, 0, sizeof(board));
            board[a.getX()][a.getY()] = a.getValue();
            board[b.getX()][b.getY()] = b.getValue();
        }

        void print() const {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    cout << board[i][j] << (j != 3 ? ' ' : '\n');
                }
            }
        }
        void left() {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (board[i][j] == 0) {
                        for (int k = j + 1; k < 4; k++) {
                            if (board[i][k] != 0) {
                                board[i][j] = board[i][k];
                                board[i][k] = 0;
                                break;
                            }
                        }
                    }
                }
            }
        }
        void right() {
            for (int i = 0; i < 4; i++) {
                for (int j = 3; j >= 0; j--) {
                    if (board[i][j] == 0) {
                        for (int k = j - 1; k >= 0; k--) {
                            if (board[i][k] != 0) {
                                board[i][j] = board[i][k];
                                board[i][k] = 0;
                                break;
                            }
                        }
                    }
                }
            }
        }
        void up() {
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 4; i++) {
                    if (board[i][j] == 0) {
                        for (int k = i + 1; k < 4; k++) {
                            if (board[k][j] != 0) {
                                board[i][j] = board[k][j];
                                board[k][j] = 0;
                                break;
                            }
                        }
                    }
                }
            }
        }
        void down() {
            for (int j = 0; j < 4; j++) {
                for (int i = 3; i >= 0; i--) {
                    if (board[i][j] == 0) {
                        for (int k = i - 1; k >= 0; k--) {
                            if (board[k][j] != 0) {
                                board[i][j] = board[k][j];
                                board[k][j] = 0;
                                break;
                            }
                        }
                    }
                }
            }
        }
};
int main() {
    int x1, y1, x2, y2;
    string cmd;
    cin >> x1 >> y1 >> x2 >> y2;
    Board board(Point(x1, y1, 2), Point(x2, y2, 2));
    // board.print();
    while (cin >> cmd) {
        if (cmd == "A") {
            board.left();
        }
        else if (cmd == "Right") {
            board.right();
        }
        else if (cmd == "Up") {
            board.up();
        }
        else if (cmd == "Down") {
            board.down();
        }
        else if (cmd == "Quit") {
            break;
        }
        board.print();
    }
    return 0;
}