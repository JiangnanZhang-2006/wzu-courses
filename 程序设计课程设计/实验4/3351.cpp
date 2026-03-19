#include <iostream>
#include <cstring>

using namespace std;

class Sokoban {
    private:
        size_t n, m;
        char** board;
        struct Player {
            int x, y;
        } player;
        struct Box {
            int x, y;
        } boxes[1000];
        struct Wall {
            int x, y;
        } walls[1000];
        int wall_count;
        int box_count;
    public:
        Sokoban(size_t _n, size_t _m) : n(_n), m(_m) {
            player.x = 0;
            player.y = 0;
            board = new char*[n];
            memset(boxes, 0, sizeof(boxes));
            memset(walls, 0, sizeof(walls));
            wall_count = 0;
            box_count = 0;
            for (size_t i = 0; i < n; i++) {
                board[i] = new char[m];
                for (size_t j = 0; j < m; j++) {
                    cin >> board[i][j];
                    if (board[i][j] == 'P') {
                        player.x = i;
                        player.y = j;
                    } else if (board[i][j] == '#') {
                        walls[wall_count].x = i;
                        walls[wall_count].y = j;
                        wall_count++;
                    }
                }
            }

        }
        ~Sokoban() {
            for (size_t i = 0; i < n; i++) {
                delete[] board[i];
            }
            delete[] board;
        }
        void print() {
            for (size_t i = 0; i < n; i++) {
                for (size_t j = 0; j < m; j++) {
                    cout << board[i][j];
                }
                cout << endl;
            }
        }
        void up() {
            if (player.x - 1 < 0 || board[player.x - 1][player.y] == '#') {
                return;
            }
            board[player.x][player.y] = '.';
            player.x--;
            if (board[player.x][player.y] == '.') {
                board[player.x][player.y] = 'P';
            }
        }
        void down() {
            if (player.x + 1 >= n || board[player.x + 1][player.y] == '#') {
                return;
            }
            board[player.x][player.y] = '.';
            player.x++;
            if (board[player.x][player.y] == '.') {
                board[player.x][player.y] = 'P';
            }
        }
        void left() {
            if (player.y - 1 < 0 || board[player.x][player.y - 1] == '#') {
                return;
            }
            board[player.x][player.y] = '.';
            player.y--;
            if (board[player.x][player.y] == '.') {
                board[player.x][player.y] = 'P';
            }
        }
        void right() {
            if (player.y + 1 >= m || board[player.x][player.y + 1] == '#') {
                return;
            }
            board[player.x][player.y] = '.';
            player.y++;
            if (board[player.x][player.y] == '.') {
                board[player.x][player.y] = 'P';
            }
        }
};

int main() {
    size_t n, m;
    cin >> n >> m;
    Sokoban sokoban(n, m);
    char command;
    while (cin >> command && command != EOF) {
        cout << command << endl;
        switch (command) {
            case 'W':
                sokoban.up();
                break;
            case 'S':
                sokoban.down();
                break;
            case 'A':
                sokoban.left();
                break;
            case 'D':
                sokoban.right();
                break;
            default:
                break;
        }
        sokoban.print();
    }
    return 0;
}