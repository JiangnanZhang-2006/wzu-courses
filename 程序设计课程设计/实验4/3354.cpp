#include <iostream>
#include <cstring>

using namespace std;

const int MAX_CELLS = 1000;
enum Cell : char { EMPTY = '.', WALL = '#', TARGET = 'T', BOX_ON_TARGET = 'O', BOX = 'B', PLAYER = 'P' };

class Sokoban {
private:
    size_t n, m;
    char** board;
    struct Player { int x, y; } player;
    struct Box { int x, y; } boxes[MAX_CELLS];
    struct Wall { int x, y; } walls[MAX_CELLS];
    struct Target { int x, y; } targets[MAX_CELLS];
    int wall_count, box_count, target_count;
    int filled_count;

    int findBoxAt(int x, int y) const {
        for (int i = 0; i < box_count; i++)
            if (boxes[i].x == x && boxes[i].y == y) return i;
        return -1;
    }

    bool isTarget(int x, int y) const {
        return findTargetAt(x, y) >= 0;
    }

    int findTargetAt(int x, int y) const {
        for (int i = 0; i < target_count; i++)
            if (targets[i].x == x && targets[i].y == y) return i;
        return -1;
    }

    void clearCell(int x, int y) {
        board[x][y] = (char)(isTarget(x, y) ? TARGET : EMPTY);
    }

    void setBoxAt(int x, int y) {
        board[x][y] = (char)(isTarget(x, y) ? BOX_ON_TARGET : BOX);
    }

    bool canPlayerStand(char c) const { return c == EMPTY; }
    bool canPushTo(char c) const { return c == EMPTY || c == TARGET; }
    bool isBox(char c) const { return c == BOX || c == BOX_ON_TARGET; }

    void move(int dx, int dy) {
        int nx = player.x + dx, ny = player.y + dy;
        if (nx < 0 || nx >= (int)n || ny < 0 || ny >= (int)m) return;

        if (isBox(board[nx][ny])) {
            int nnx = nx + dx, nny = ny + dy;
            if (nnx < 0 || nnx >= (int)n || nny < 0 || nny >= (int)m) return;
            if (!canPushTo(board[nnx][nny])) return;

            int bi = findBoxAt(nx, ny);
            if (bi == -1) return;
            if (isTarget(boxes[bi].x, boxes[bi].y)) filled_count--;
            clearCell(boxes[bi].x, boxes[bi].y);
            boxes[bi].x = nnx;
            boxes[bi].y = nny;
            setBoxAt(nnx, nny);
            if (isTarget(nnx, nny)) filled_count++;
            clearCell(player.x, player.y);
            player.x = nx;
            player.y = ny;
            board[nx][ny] = (char)PLAYER;
        } else if (canPlayerStand(board[nx][ny])) {
            clearCell(player.x, player.y);
            player.x = nx;
            player.y = ny;
            board[nx][ny] = (char)PLAYER;
        }
    }

public:
    Sokoban(size_t _n, size_t _m) : n(_n), m(_m), wall_count(0), box_count(0), target_count(0), filled_count(0) {
        player.x = player.y = 0;
        board = new char*[n];
        memset(boxes, 0, sizeof(boxes));
        memset(walls, 0, sizeof(walls));
        memset(targets, 0, sizeof(targets));
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
                } else if (board[i][j] == 'B') {
                    boxes[box_count].x = i;
                    boxes[box_count].y = j;
                    box_count++;
                } else if (board[i][j] == 'T') {
                    targets[target_count].x = i;
                    targets[target_count].y = j;
                    target_count++;
                } else if (board[i][j] == 'O') {
                    targets[target_count].x = i;
                    targets[target_count].y = j;
                    target_count++;
                    boxes[box_count].x = i;
                    boxes[box_count].y = j;
                    box_count++;
                    filled_count++;
                }
            }
        }
    }

    ~Sokoban() {
        for (size_t i = 0; i < n; i++) delete[] board[i];
        delete[] board;
    }

    void print() const {
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++) cout << board[i][j];
            cout << endl;
        }
    }

    bool isVictory() const {
        return target_count > 0 && filled_count == target_count;
    }

    void up()   { move(-1, 0); }
    void down() { move(1, 0); }
    void left() { move(0, -1); }
    void right(){ move(0, 1); }
};

int main() {
    size_t n, m;
    cin >> n >> m;
    Sokoban sokoban(n, m);
    char command;
    while (cin >> command) {
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
        if (sokoban.isVictory()) {
            cout << "Victory!" << endl;
            break;
        }
    }
    return 0;
}