#include <cctype>
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
        void add(Point p) {
            board[p.getX()][p.getY()] = p.getValue();
        }
        void print() const {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    cout << board[i][j] << (j != 3 ? ' ' : '\n');
                }
            }
        }
        bool operator==(const Board& other) const {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (board[i][j] != other.board[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }
        bool operator!=(const Board& other) const {
            return !(*this == other);
        }
        int getPoint(int x, int y) const {
            return board[x][y];
        }
        Board(const Board& other) {
            memcpy(board, other.board, sizeof(board));
        }
        Board& operator=(const Board& other) {
            if (this != &other) {
                memcpy(board, other.board, sizeof(board));
            }
            return *this;
        }
        void left(bool merge = true) {
            //move
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
            if (!merge) return;
            //merge
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (board[i][j] == board[i][j + 1]) {
                        board[i][j] *= 2;
                        board[i][j + 1] = 0;
                    }
                }
            }
            //move
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
        void right(bool merge = true) {
            //move
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
            if (!merge) return;
            //merge
            for (int i = 0; i < 4; i++) {
                for (int j = 3; j >= 0; j--) {
                    if (board[i][j] == board[i][j - 1]) {
                        board[i][j] *= 2;
                        board[i][j - 1] = 0;
                    }
                }
            }
            //move
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
        void up(bool merge = true) {
            //move
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
            if (!merge) return;
            //merge
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 4; i++) {
                    if (board[i][j] == board[i + 1][j]) {
                        board[i][j] *= 2;
                        board[i + 1][j] = 0;
                    }
                }
            }
            //move
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
        void down(bool merge = true) {
            //move
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
            if (!merge) return;
            //merge
            for (int j = 0; j < 4; j++) {
                for (int i = 3; i >= 0; i--) {
                    if (board[i][j] == board[i - 1][j]) {
                        board[i][j] *= 2;
                        board[i - 1][j] = 0;
                    }
                }
            }
            //move
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
    string line;
    //init
    cin >> x1 >> y1 >> x2 >> y2;
    Board board(Point(x1, y1, 2), Point(x2, y2, 2));
    cin.ignore();
    while (getline(cin, line) && line != "@") {
        //move
        int newX = -1, newY = -1;
        if (isdigit(line[0])) {
            newX = line[0] - '0';
            newY = line[2] - '0';
            if (board.getPoint(newX, newY) == 0) {
                board.add(Point(newX, newY, 2));
                board.print();
            }
        } else {
            Board oldBoard = board;
            if (line == "A") {
                board.left(false);
            }
            else if (line == "D") {
                board.right(false);
            }
            else if (line == "W") {
                board.up(false);
            }
            else if (line == "S") {
                board.down(false);
            }
            cout << line << endl;
            if (board == oldBoard) {
                board.print();
            }
        }
    }
    return 0;
}