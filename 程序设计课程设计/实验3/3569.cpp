#include <iostream>
#include <cstring>
#include <vector>
#include <list>

using namespace std;

class Board {
    private:
        size_t n, m;
        vector<vector<char>> board;
        struct Snake {
            pair<int, int> direction;
            list<pair<size_t, size_t>> body;    //head -> tail
        } snake;
        
    public:
        Board(size_t _n, size_t _m) : n(_n), m(_m) {               //both n & m are odd
            n = _n;
            m = _m;
            board.assign(n, vector<char>(m, '.'));
            snake.direction = {0, 1};
            snake.body.push_back({n / 2, m / 2});
            snake.body.push_back({n / 2, m / 2 - 1});
            snake.body.push_back({n / 2, m / 2 - 2});
            draw();
        }
        void draw() {
            board.assign(n, vector<char>(m, '.'));
            for (const auto &pos : snake.body) {
                board[pos.first][pos.second] = pos == snake.body.front() ? '>' : '*';
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
        bool move(int steps) {
            for (int i = 0; i < steps; i++) {
                pair<int, int> newHead = {snake.body.front().first + snake.direction.first, snake.body.front().second + snake.direction.second};
                if (newHead.first < 0 || newHead.first >= n || newHead.second < 0 || newHead.second >= m) {
                    return false;
                }
                snake.body.push_front(newHead);
                snake.body.pop_back();
                draw();
            }
            return true;
        }
};

int main() {
    int n, m;
    cin >> n >> m;
    Board board(n, m);
    int steps;
    cin >> steps;
    board.move(steps);
    board.print();
    return 0;
}