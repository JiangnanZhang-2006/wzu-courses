#include <iostream>
using namespace std;

int main() {
    int a[6];

    while (true) {
        bool all_zero = true;
        for (int i = 0; i < 6; i++) {
            cin >> a[i];
            if (a[i] != 0) {
                all_zero = false;
            }
        }
        if (all_zero) {
            break;
        }
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                int index = (j - i + 6) % 6;
                cout << a[index];
                if (j < 5) {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }
    return 0;
}