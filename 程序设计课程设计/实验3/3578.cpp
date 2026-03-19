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
        pair<size_t, size_t> food;
        vector<pair<size_t, size_t>> obstacles; // # -> obstacles
        bool ate_food_but_not_move_yet;
    public:
        Board(size_t _n, size_t _m) : n(_n), m(_m) {               //both n & m are odd
            n = _n;
            m = _m;
            board.assign(n, vector<char>(m, '.'));
            snake.direction = {0, 1};
            ate_food_but_not_move_yet = false;
            for (size_t i = 0; i < n; i++) {
                for (size_t j = 0; j < m; j++) {
                    cin >> board[i][j];
                    if (board[i][j] == '#') {
                        obstacles.push_back(make_pair(i, j));
                    }
                }
                cin.ignore();
            }
            snake.body.push_back({n / 2, m / 2});
            snake.body.push_back({n / 2, m / 2 - 1});
            snake.body.push_back({n / 2, m / 2 - 2});
            draw();
        }
        void draw() {
            board.assign(n, vector<char>(m, '.'));
            board[food.first][food.second] = '@';
            for (const auto &pos : obstacles) {
                board[pos.first][pos.second] = '#';
            }
            char head_symbol;
            if (snake.direction == make_pair(0, 1)) {
                head_symbol = '>';
            }
            else if (snake.direction == make_pair(0, -1)) {
                head_symbol = '<';
            }
            else if (snake.direction == make_pair(1, 0)) {
                head_symbol = 'V';
            }
            else if (snake.direction == make_pair(-1, 0)) {
                head_symbol = '^';
            }
            for (const auto &pos : snake.body) {
                board[pos.first][pos.second] = pos == snake.body.front() ? head_symbol : '*';
            }
        }
        void print() {
            draw();
            for (const auto &row : board) {
                for (const auto &cell : row) {
                    cout << cell;
                }
                cout << endl;
            }
        }
        bool move(int steps) {
            for (int i = 0; i < steps; i++) {
                int nr = (int)snake.body.front().first + snake.direction.first;
                int nc = (int)snake.body.front().second + snake.direction.second;
                if (nr < 0 || nr >= (int)n || nc < 0 || nc >= (int)m) return false;  // 越界一律 Game Over
                pair<size_t, size_t> new_head = {(size_t)nr, (size_t)nc};
                if (board[new_head.first][new_head.second] == '#') continue;  // 墙一律跳过（13123/13124/13125 一致）
                if (board[new_head.first][new_head.second] == '*' && new_head != snake.body.back()) return false;  // 撞身体则结束
                snake.body.push_front(new_head);
                if (new_head == food) {
                    ate_food_but_not_move_yet = true;
                    add_food();
                }
                if (!ate_food_but_not_move_yet) {
                    snake.body.pop_back();
                }
                ate_food_but_not_move_yet = false;
                draw();
            }
            return true;
        }
        void add_food() {
            do {
                //food = make_pair(rand() % n, rand() % m);
                cin >> food.first >> food.second;
                cin.ignore();
            } while (board[food.first][food.second] != '.');
            board[food.first][food.second] = '@';
        }
        void up() {
            if (snake.direction != make_pair(1, 0)) {
                snake.direction = {-1, 0};
            }
        }
        void down() {
            if (snake.direction != make_pair(-1, 0)) {
                snake.direction = {1, 0};
            }
        }
        void left() {
            if (snake.direction != make_pair(0, 1)) {
                snake.direction = {0, -1};
            }
        }
        void right() {
            if (snake.direction != make_pair(0, -1)) {
                snake.direction = {0, 1};
            }
        }
};

int main() {
    int n, m;
    cin >> n >> m;
    cin.ignore();
    Board board(n, m);
    board.add_food();
    string line;
    while (getline(cin, line) && line != "-1") {
        cout << line << endl;
        if (isdigit(line[0])) {
            int steps = stoi(line);
            if (!board.move(steps)) {
                cout << "Game Over!" << endl;
                break;
            }
        } else {
            char dir = line[0];
            if (dir == 'W') {
                board.up();
            }
            else if (dir == 'S') {
                board.down();
            }
            else if (dir == 'A') {
                board.left();
            }
            else if (dir == 'D') {
                board.right();
            }
        }
        board.print();
    }
    return 0;
}