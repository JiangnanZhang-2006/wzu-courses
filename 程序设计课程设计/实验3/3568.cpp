#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class Board {
    private:
        size_t n, m;
        vector<vector<char>> board;
        struct Snake {
            pair<int, int> direction;
            vector<pair<size_t, size_t>> body;    //head -> tail
        } snake;
        
    public:
        Board(size_t _n, size_t _m) : n(_n), m(_m) {               //both n & m are odd
            n = _n;
            m = _m;
            board.resize(n, vector<char>(m, '.'));
            snake.direction = {0, 1};
            snake.body.push_back({n / 2, m / 2});
            snake.body.push_back({n / 2, m / 2 - 1});
            snake.body.push_back({n / 2, m / 2 - 2});
            draw();
        }
        void draw() {
            board.resize(n, vector<char>(m, '.'));
            for (const auto &pos : snake.body) {
                board[pos.first][pos.second] = pos == snake.body[0] ? '>' : '*';
            }
        }
        void print() {
            for (const auto &row : board) {
                for (const auto &cell : row) {
                    cout << cell;
                }
                cout << endl;
            }
        }
};

int main() {
    int n, m;
    cin >> n >> m;
    Board board(n, m);
    board.print();
    return 0;
}