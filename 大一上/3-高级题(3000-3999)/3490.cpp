    #include <bits/stdc++.h>
    using namespace std;

    int main () {
        int target_grey_value;
        pair<int, int> resolution, grey_value_area;
        cin >> resolution.second >> resolution.first >> grey_value_area.first >> grey_value_area.second >> target_grey_value;
        vector<vector<int>> image(resolution.second, vector<int>(resolution.first));
        for (int i = 0; i < resolution.second; ++i) {
            for (int j = 0; j < resolution.first; ++j) {
                cin >> image[i][j];
                if (image[i][j] <= grey_value_area.second && image[i][j] >= grey_value_area.first) {
                    image[i][j] = target_grey_value;
                }
            }
        }
        for (const auto& row : image) {
            bool flag = false;
            for (const auto& pixel : row) {
                if (flag) cout << ' ';
                flag = true;
                cout << setw(3) << setfill('0') << pixel;
            }
            cout << '\n';
        }
    }