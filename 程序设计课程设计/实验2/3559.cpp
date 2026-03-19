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
};
int main() {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    Board board(Point(x1, y1, 2), Point(x2, y2, 2));
    board.print();
    return 0;
}