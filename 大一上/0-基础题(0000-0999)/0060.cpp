#include <iostream>
using namespace std;

int main() {
    int n;
    while (cin >> n && n != 0) {
        int arr[100];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }

        int minIndex = 0;
        for (int i = 1; i < n; i++) {
            if (arr[i] < arr[minIndex]) {
                minIndex = i;
            }
        }

        int temp = arr[0];
        arr[0] = arr[minIndex];
        arr[minIndex] = temp;

        for (int i = 0; i < n; i++) {
            if (i > 0) cout << " ";
            cout << arr[i];
        }
        cout << endl;
    }
    return 0;
}