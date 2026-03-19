#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, N, tol;
    if (!(cin >> M >> N >> tol)) return 0;

    vector<vector<int>> image(N, vector<int>(M));
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < M; ++x) {
            if (!(cin >> image[y][x])) image[y][x] = 0;
        }
    }

    unordered_map<int, int> freq;
    freq.reserve((size_t)N * M);
    for (int y = 0; y < N; ++y)
        for (int x = 0; x < M; ++x)
            ++freq[image[y][x]];

    vector<pair<int,int>> candidates;
    const int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    const int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < M; ++x) {
            int val = image[y][x];
            if (freq[val] != 1) continue; // must be unique globally

            bool ok = true;
            for (int k = 0; k < 8 && ok; ++k) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
                if (abs(image[ny][nx] - val) <= tol) ok = false;
            }
            if (ok) candidates.emplace_back(x, y);
        }
    }

    if (candidates.empty()) {
        cout << "Not Exist" << '\n';
    } else if (candidates.size() > 1) {
        cout << "Not Unique" << '\n';
    } else {
        auto p = candidates[0];
        cout << '(' << p.first + 1 << ", " << p.second + 1 << "): " << image[p.second][p.first] << '\n';
    }

    return 0;
}