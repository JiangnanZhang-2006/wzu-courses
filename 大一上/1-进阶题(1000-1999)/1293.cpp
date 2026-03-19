    #include <bits/stdc++.h>

    using namespace std;

    int main() {
        double seq[5][4];
        for (int i = 0; i < 5; i++) {
            double a_temp, b_temp, c_temp, tot_temp;
            cin >> a_temp >> b_temp >> c_temp;
            tot_temp = a_temp + b_temp + c_temp;
            seq[i][0] = a_temp; seq[i][1] = b_temp; seq[i][2] = c_temp; seq[i][3] = tot_temp;
        }
        //bubbleSort
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4 - i; j++) {
                if (seq[j][3] < seq[j + 1][3]) {
                    swap(seq[j], seq[j + 1]);
                }
            }
        }
        //output
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 4; j++) {
                cout << fixed << setprecision(1) << seq[i][j];
                if (j != 3) cout << ' ';
            }
            cout << endl;
        }
        return 0;
    }