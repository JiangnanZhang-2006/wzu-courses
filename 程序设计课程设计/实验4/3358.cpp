#include <iostream>
#include <cstring>

using namespace std;

const int MAX_CELLS = 1000;
enum Cell : char {
    EMPTY = '.', WALL = '#', TARGET = 'T', BOX_ON_TARGET = 'O', BOX = 'B',
    PLAYER = 'P', PLAYER_ON_TARGET = '@', TRAP = 'X', PLAYER_TRAPPED = '!', BOX_TRAPPED = '*'
};

class Sokoban {
private:
    size_t n, m;
    char** board;
    struct Player { int x, y; } player;
    struct Box { int x, y; bool trapped; } boxes[MAX_CELLS];
    struct Wall { int x, y; } walls[MAX_CELLS];
    struct Target { int x, y; } targets[MAX_CELLS];
    struct Trap { int x, y; } traps[MAX_CELLS];
    int wall_count, box_count, target_count, trap_count;
    int filled_count;
    bool player_trapped;
    bool** is_target;
    bool** is_trap;
    int** box_at;  // box_at[i][j] = 该格箱子下标，无则为 -1

    inline int findBoxAt(int x, int y) const { return box_at[x][y]; }
    inline bool isTarget(int x, int y) const { return is_target[x][y]; }
    inline bool isTrap(int x, int y) const { return is_trap[x][y]; }

    void clearCell(int x, int y) {
        if (isTrap(x, y)) board[x][y] = (char)TRAP;
        else if (isTarget(x, y)) board[x][y] = (char)TARGET;
        else board[x][y] = (char)EMPTY;
    }

    void setBoxAt(int x, int y) {
        if (isTrap(x, y)) board[x][y] = (char)BOX_TRAPPED;
        else if (isTarget(x, y)) board[x][y] = (char)BOX_ON_TARGET;
        else board[x][y] = (char)BOX;
    }

    void setPlayerAt(int x, int y) {
        if (isTrap(x, y)) {
            board[x][y] = (char)PLAYER_TRAPPED;
            player_trapped = true;
        } else if (isTarget(x, y)) board[x][y] = (char)PLAYER_ON_TARGET;
        else board[x][y] = (char)PLAYER;
    }

    bool canPlayerStand(char c) const { return c == EMPTY || c == TARGET || c == TRAP; }
    bool canPushTo(char c) const { return c == EMPTY || c == TARGET || c == TRAP; }
    bool isBox(char c) const { return c == BOX || c == BOX_ON_TARGET || c == BOX_TRAPPED; }

    void move(int dx, int dy) {
        if (player_trapped) return;
        int nx = player.x + dx, ny = player.y + dy;
        if (nx < 0 || nx >= (int)n || ny < 0 || ny >= (int)m) return;

        if (isBox(board[nx][ny])) {
            int bi = findBoxAt(nx, ny);
            if (bi == -1 || boxes[bi].trapped) return;
            int nnx = nx + dx, nny = ny + dy;
            if (nnx < 0 || nnx >= (int)n || nny < 0 || nny >= (int)m) return;
            if (!canPushTo(board[nnx][nny])) return;

            if (isTarget(boxes[bi].x, boxes[bi].y)) filled_count--;
            clearCell(boxes[bi].x, boxes[bi].y);
            box_at[boxes[bi].x][boxes[bi].y] = -1;
            boxes[bi].x = nnx;
            boxes[bi].y = nny;
            box_at[nnx][nny] = bi;
            if (isTrap(nnx, nny)) boxes[bi].trapped = true;
            setBoxAt(nnx, nny);
            if (isTarget(nnx, nny)) filled_count++;
            clearCell(player.x, player.y);
            player.x = nx;
            player.y = ny;
            setPlayerAt(nx, ny);
        } else if (canPlayerStand(board[nx][ny])) {
            clearCell(player.x, player.y);
            player.x = nx;
            player.y = ny;
            setPlayerAt(nx, ny);
        }
    }

public:
    Sokoban(size_t _n, size_t _m) : n(_n), m(_m), wall_count(0), box_count(0), target_count(0), trap_count(0), filled_count(0), player_trapped(false) {
        player.x = player.y = 0;
        board = new char*[n];
        is_target = new bool*[n];
        is_trap = new bool*[n];
        box_at = new int*[n];
        for (size_t i = 0; i < n; i++) {
            board[i] = new char[m];
            is_target[i] = new bool[m]();
            is_trap[i] = new bool[m]();
            box_at[i] = new int[m];
            for (size_t j = 0; j < m; j++) box_at[i][j] = -1;
        }
        memset(boxes, 0, sizeof(boxes));
        memset(walls, 0, sizeof(walls));
        memset(targets, 0, sizeof(targets));
        memset(traps, 0, sizeof(traps));
        for (size_t i = 0; i < n; i++) {
            for (size_t j = 0; j < m; j++) {
                cin >> board[i][j];
                if (board[i][j] == 'P') {
                    player.x = i;
                    player.y = j;
                } else if (board[i][j] == '#') {
                    walls[wall_count].x = i;
                    walls[wall_count].y = j;
                    wall_count++;
                } else if (board[i][j] == 'X') {
                    traps[trap_count].x = i;
                    traps[trap_count].y = j;
                    trap_count++;
                    is_trap[i][j] = true;
                } else if (board[i][j] == '@') {
                    player.x = i;
                    player.y = j;
                    targets[target_count].x = i;
                    targets[target_count].y = j;
                    target_count++;
                    is_target[i][j] = true;
                } else if (board[i][j] == 'B') {
                    boxes[box_count].x = i;
                    boxes[box_count].y = j;
                    box_at[i][j] = box_count;
                    box_count++;
                } else if (board[i][j] == 'T') {
                    targets[target_count].x = i;
                    targets[target_count].y = j;
                    target_count++;
                    is_target[i][j] = true;
                } else if (board[i][j] == 'O') {
                    targets[target_count].x = i;
                    targets[target_count].y = j;
                    target_count++;
                    is_target[i][j] = true;
                    boxes[box_count].x = i;
                    boxes[box_count].y = j;
                    box_at[i][j] = box_count;
                    box_count++;
                    filled_count++;
                }
            }
        }
    }

    ~Sokoban() {
        for (size_t i = 0; i < n; i++) {
            delete[] board[i];
            delete[] is_target[i];
            delete[] is_trap[i];
            delete[] box_at[i];
        }
        delete[] board;
        delete[] is_target;
        delete[] is_trap;
        delete[] box_at;
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

    bool isTrapped() const {
        if (player_trapped) return true;
        for (int i = 0; i < box_count; i++)
            if (boxes[i].trapped) return true;
        return false;
    }

    void up()   { move(-1, 0 ); }
    void down() { move(1,  0 ); }
    void left() { move(0,  -1); }
    void right(){ move(0,  1 ); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
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
        if (sokoban.isTrapped()) {
            cout << "Trapped!" << endl;
            break;
        }
    }
    return 0;
}