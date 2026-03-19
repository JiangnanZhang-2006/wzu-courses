	#include<iostream>
	#include<iomanip>

	using namespace std;

	int main() {
		int t;
		cin >> t;
		while (t--) {
			int idx[105], len, arr[105] = { -1 };
			for (int i = 1; i <= 105; ++i) {
				idx[i - 1] = i;
			}

			cin >> len;

			for (int i = 0; i < len; ++i) {
				cin >> arr[i];
			}
			//bubbleSort
			for (int i = 0; i < len; ++i) {
				for (int j = 0; j < len - i - 1; ++j) {
					if (arr[idx[j] - 1] > arr[idx[j + 1] - 1] ||
						(arr[idx[j] - 1] == arr[idx[j + 1] - 1] && idx[j] > idx[j + 1])) {
						//exchange j, j+1;
						idx[j] = idx[j] + idx[j + 1];
						idx[j + 1] = idx[j] - idx[j + 1];
						idx[j] = idx[j] - idx[j + 1];
					}
				}
			}
		
			//summarize

			double sum = 0;

			for (int i = 0; i < len; ++i) {
				for (int j = 0; j < i; ++j) {
					sum += arr[idx[j] - 1];	
				}
			}
			//output
			cout << idx[0];
			for (int i = 1; i < len; ++i) {
				cout << ' ' << idx[i];
			}
			cout << endl << fixed << setprecision(2) << sum / len << endl;

		}
	}